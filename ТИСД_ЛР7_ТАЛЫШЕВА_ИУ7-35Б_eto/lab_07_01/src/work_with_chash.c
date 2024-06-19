#include "work_with_chash.h"

int chash_from_file(struct Hash_close **Table, FILE *file)
{
    int res = 0;
    int rc = OK;
    int x;
    while (fscanf(file, "%d", &x) == 1 && rc == OK)
    {
        *Table = chash_add_elem(*Table, x, res);
        if (*Table == NULL)
        {
            rc = ERR_MEM;
            printf("Ошибка выделения памяти!\n");
        }
    }
    fseek(file, 0, SEEK_SET);
    return rc;
}

void chash_node_print(struct Node_chash *elem, char *strk)
{
    memset(strk, '\0', SIZE_OF_BUF);
    struct Node_chash *current = elem;
    char strk_save[SIZE_OF_BUF];
    memset(strk_save, '\0', SIZE_OF_BUF);
    while (current != NULL)
    {
        snprintf(strk_save, SIZE_OF_BUF, " -> %d", current->data);
        //printf("!%s!\n", strk_save);
        for (int j = 0; j < (int)strlen(strk_save); j++)
        {
            strk[strlen(strk)] = strk_save[j];
            //printf("%s %s %c\n", strk, strk_save, strk_save[j]);
        }
        strk[strlen(strk)] = '\0';
        current = current->next;
    }
}

void chash_print(struct Hash_close *Table, char *name_file)
{
    FILE *file = fopen(name_file, "w");
    char strk[SIZE_OF_BUF];
    // таблица
    ft_table_t *table = ft_create_table();
    fprintf(file, "хэш-таблица с внешним хэшированием:\n");
    ft_u8write_ln(table, "Индекс", "Хэш", "Элементы");
    for (long int i = 0; i < Table->size; i++)
    {
        char hash_c[SIZE_OF_BUF];
        if (Table->data[i] == NULL)
        {
            snprintf(strk, SIZE_OF_BUF, "-");
            snprintf(hash_c, SIZE_OF_BUF, "-");
        }
        else
        {
            chash_node_print(Table->data[i], strk);
            snprintf(hash_c, SIZE_OF_BUF, "%d", hash_func((Table->data[i])->data, Table->size));
        }
        char ind_c[SIZE_OF_BUF];
        snprintf(ind_c, SIZE_OF_BUF, "%ld", i);
        //printf("%s\n", strk);
        ft_u8write_ln(table, ind_c, hash_c, strk);
    }
    ft_set_border_style(table, FT_NICE_STYLE);
    for (long int i = 0; i < Table->size; i++)
        ft_set_cell_prop(table, FT_ANY_ROW, i, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_LEFT);
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    fprintf(file, "%s\n", ft_to_string(table));
    fclose(file);
}

// переменная рез предотвращает зацикливание показывая не из резайса ли было вызвано добавление, чтоб опять не ресайзить
struct Hash_close *chash_add_elem(struct Hash_close *Table, int num, int res)
{
    if (Table == NULL || Table->size == 0)
        return NULL;
    int ind = hash_func(num, Table->size);
    if (Table->data[ind] == NULL)
        Table->data[ind] = chash_node_create(num);
    else if ((Table->data[ind])->data == num)
        printf("Внимание! Элемент %d уже есть в таблице! Нового элемента не появилось.\n", num);
    else
    {
        int count = 1;
        struct Node_chash *current = Table->data[ind];
        while (current->next != NULL && (current->next)->data != num)
        {
            current = current->next;
            count++;
        }
        if (current->next != NULL)
            printf("Внимание! Элемент %d уже есть в таблице! Нового элемента не появилось.\n", num);
        else
            current->next = chash_node_create(num);
        if (count > MAX_DIFF_HASH && !res)
        {
            int rc = chash_resize(&Table);
            if (rc != OK)
                printf("Ошибка реструктуризации хэш-таблицы.\n");
        }
    }
    return Table;
}

struct Hash_close *chash_del_elem(struct Hash_close *Table, int num)
{
    if (Table == NULL || Table->size == 0)
        return Table;

    int ind = hash_func(num, Table->size);
    struct Node_chash *current = Table->data[ind];
    struct Node_chash *prev = NULL;

    // Поиск элемента в списке
    while (current != NULL && current->data != num)
    {
        prev = current;
        current = current->next;
    }

    // Если элемент не найден
    if (current == NULL)
    {
        printf("Внимание! Элемента %d в таблице нет! Ничего не удалилось.\n", num);
        return Table;
    }

    // Если элемент находится в начале списка
    if (prev == NULL)
    {
        Table->data[ind] = current->next;
    }
    else
    {
        prev->next = current->next;
    }

    // Освобождение памяти
    chash_node_free(&current);

    return Table;
}

int *chash_find_elem(struct Hash_close *Table, int num, int *count, int talk)
{
    if (Table == NULL || Table->size == 0)
        return NULL;
    int ind = hash_func(num, Table->size);
    *count = 0;
    struct Node_chash *current = Table->data[ind];
    while (current != NULL && current->data != num)
    {
        current = current->next;
        (*count)++;
    }
    if (*count > MAX_DIFF_HASH && talk)
        printf("Хеш таблица не эффективна! Количество сравнений = %d. Рекомендуется переформировать.\n", *count);
    if (current == NULL)
        return NULL;
    else
        return &(current->data);
}

int chash_resize(struct Hash_close **Table)
{
    int res = 1;
    int rc = OK;
    long int new_tsize = is_simple((*Table)->size);
    struct Hash_close *new_Table = NULL;
    rc = chash_create(new_tsize, &new_Table);
    if (rc == OK)
    {
        for (long int i = 0; i < (*Table)->size; i++)
        {
            struct Node_chash *current = (*Table)->data[i];
            while (current != NULL)
            {
                new_Table = chash_add_elem(new_Table, current->data, res);
                current = current->next;
            }
        }
        chash_free(Table);
        *Table = new_Table;
    }
    return rc;
}

struct Node_chash *chash_node_create(int num)
{
    struct Node_chash *elem = calloc(1, sizeof(struct Node_chash));
    elem->data = num;
    elem->next = NULL;
    return elem;
}

int chash_create(long int tsize, struct Hash_close **Table)
{
    int rc = OK;
    *Table = calloc(1, sizeof(struct Hash_close));
    (*Table)->data = calloc(tsize, sizeof(struct Node_chash *));
    (*Table)->size = tsize;
    if ((*Table)->data == NULL)
        rc = ERR_MEM;
    else
        for (long int i = 0; i < (*Table)->size; i++)
            (*Table)->data[i] = NULL;
    return rc;
}

void chash_free(struct Hash_close **Table)
{
    if (*Table == NULL)
        return;
    for (long int i = 0; i < (*Table)->size; i++)
    {
        while ((*Table)->data[i] != NULL)
        {
            struct Node_chash **current = &((*Table)->data[i]);
            while ((*current)->next != NULL)
                current = &((*current)->next);
            chash_node_free(current);
        }
    }
    free((*Table)->data);
    free(*Table);
    *Table = NULL;
}

void chash_node_free(struct Node_chash **elem)
{
    if (*elem != NULL)
    {
        free(*elem);
        *elem = NULL;
    }
}

double chash_count_average_find(struct Hash_close *Table, FILE *file)
{
    int x = 0;
    int count;
    int res_count = 0;
    int count_num = 0;
    fseek(file, 0, SEEK_SET);
    while (fscanf(file, "%d", &x) == 1)
    {
        count = 0;
        int *result = chash_find_elem(Table, x, &count, 0);
        if (result != NULL)
        {
            res_count += count;
            count_num++;
        }
    }
    fseek(file, 0, SEEK_SET);
    return count_num > 0 ? (double)res_count / (double)count_num : 0.0;
}