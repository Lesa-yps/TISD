#include "work_with_ohash.h"

int ohash_from_file(struct Hash_open **Table, FILE *file)
{
    int res = 0;
    int rc = OK;
    int x;
    while (fscanf(file, "%d", &x) == 1 && rc == OK)
    {
        //printf("%d\n", x);
        *Table = ohash_add_elem(*Table, x, res);
        if (*Table == NULL)
        {
            rc = ERR_MEM;
            printf("Ошибка выделения памяти!\n");
        }
    }
    fseek(file, 0, SEEK_SET);
    return rc;
}

void ohash_print(struct Hash_open *Table, char *file_name)
{
    FILE *file = fopen(file_name, "w");
    char strk[SIZE_OF_BUF];
    // таблица
    ft_table_t *table = ft_create_table();
    fprintf(file, "хэш-таблица с внутренним хэшированием:\n");
    ft_u8write_ln(table, "Индекс", "Хэш", "Элементы");
    char hash_c[SIZE_OF_BUF];
    for (long int i = 0; i < Table->size; i++)
    {
        if (Table->data[i] == NULL)
        {
            snprintf(strk, SIZE_OF_BUF, "-");
            snprintf(hash_c, SIZE_OF_BUF, "-");
        }
        else
        {
            snprintf(strk, SIZE_OF_BUF, "%d", *(Table->data[i]));
            snprintf(hash_c, SIZE_OF_BUF, "%d", hash_func(*(Table->data[i]), Table->size));
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
struct Hash_open *ohash_add_elem(struct Hash_open *Table, int num, int res)
{
    int rc = OK;
    if (Table == NULL || Table->size == 0)
        return NULL;
    int ind = hash_func(num, Table->size);
    long int i = 0;
    int count = 0;
    while (i < Table->size && rc == OK && Table->data[(ind + i) % Table->size] != NULL)
    {
        if (*(Table->data[(ind + i) % Table->size]) == num)
        {
            rc = ERROR;
            printf("Внимание! Элемент %d уже есть в таблице! Нового элемента не появилось.\n", num);
        }
        i++;
        count++;
    }
    if (i < Table->size && rc == OK)
        Table->data[(ind + i) % Table->size] = ohash_node_create(num);
    else if (i == Table->size)
    {
        int rc = ohash_resize(&Table);
        if (rc != OK)
            printf("Ошибка реструктуризации хэш-таблицы.\n");
        Table = ohash_add_elem(Table, num, res);
    }
    if (count > MAX_DIFF_HASH && !res)
    {
        //printf("!count=%d\n!",count);
        int rc = ohash_resize(&Table);
        if (rc != OK)
            printf("Ошибка реструктуризации хэш-таблицы.\n");
    }
    return Table;
}

struct Hash_open *ohash_del_elem(struct Hash_open *Table, int num)
{
    if (Table == NULL || Table->size == 0)
        return NULL;

    int ind = hash_func(num, Table->size);
    long int i = 0;

    while (i < Table->size)
    {
        if (Table->data[(ind + i) % Table->size] != NULL && *(Table->data[(ind + i) % Table->size]) == num)
        {
            ohash_node_free(&(Table->data[(ind + i) % Table->size]));
            return Table;
        }
        i++;
    }

    // Если элемент не найден
    printf("Внимание! Элемента %d в таблице нет! Ничего не удалилось.\n", num);
    return Table;
}

int *ohash_find_elem(struct Hash_open *Table, int num, int *count, int talk)
{
    if (Table == NULL || Table->size == 0)
        return NULL;
    int ind = hash_func(num, Table->size);
    long int i = 0;
    *count = 0;
    while (i < Table->size && Table->data[(ind + i) % Table->size] != NULL && *(Table->data[(ind + i) % Table->size]) != num)
    {
        i++;
        (*count)++;
    }
    
    if (i >= Table->size || Table->data[(ind + i) % Table->size] == NULL)
        return NULL;
    else
    {
        if (*count > MAX_DIFF_HASH && talk)
            printf("Хеш таблица не эффективна! Количество сравнений = %d. Рекомендуется переформировать.\n", *count);
        return Table->data[(ind + i) % Table->size];
    }
}

int ohash_resize(struct Hash_open **Table)
{
    int res = 1;
    int rc = OK;
    long int new_tsize = is_simple((*Table)->size);
    //printf("%ld\n", new_tsize);
    struct Hash_open *new_Table = NULL;
    rc = ohash_create(new_tsize, &new_Table);
    if (rc == OK)
    {
        for (long int i = 0; i < (*Table)->size; i++)
            if ((*Table)->data[i] != NULL)
                new_Table = ohash_add_elem(new_Table, *((*Table)->data[i]), res);
        ohash_free(Table);
        *Table = new_Table;
    }
    return rc;
}

int *ohash_node_create(int num)
{
    int *elem = calloc(1, sizeof(int));
    *elem = num;
    return elem;
}

int ohash_create(long int tsize, struct Hash_open **Table)
{
    int rc = OK;
    *Table = calloc(1, sizeof(struct Hash_open));
    (*Table)->data = calloc(tsize, sizeof(int *));
    (*Table)->size = tsize;
    if ((*Table)->data == NULL)
        rc = ERR_MEM;
    else
        for (long int i = 0; i < (*Table)->size; i++)
            (*Table)->data[i] = NULL;
    return rc;
}

void ohash_free(struct Hash_open **Table)
{
    if (*Table == NULL)
        return;
    for (long int i = 0; i < (*Table)->size; i++)
        ohash_node_free(&((*Table)->data[i]));
    free((*Table)->data);
    free(*Table);
}

void ohash_node_free(int **elem)
{
    if (*elem != NULL)
    {
        free(*elem);
        *elem = NULL;
    }
}

double ohash_count_average_find(struct Hash_open *Table, FILE *file)
{
    int x = 0;
    int count;
    int res_count = 0;
    int count_num = 0;
    fseek(file, 0, SEEK_SET);
    while (fscanf(file, "%d", &x) == 1)
    {
        count = 0;
        int *result = ohash_find_elem(Table, x, &count, 0);
        if (result != NULL)
        {
            res_count += count;
            count_num++;
        }
    }
    fseek(file, 0, SEEK_SET);
    return count_num > 0 ? (double)res_count / (double)count_num : 0.0;
}