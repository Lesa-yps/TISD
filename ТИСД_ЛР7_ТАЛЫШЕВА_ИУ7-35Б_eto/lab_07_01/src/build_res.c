#include "build_res.h"

// выигрыш от 2 в процентах
char *perc_double(double time1, double time2, char buffer[])
{
    memset(buffer, '\0', SIZE_OF_BUF * sizeof(char)); // Заполняем буфер
    if (diff_time(time2, 0) != 0)
        sprintf(buffer, "%f", fabs(time1 * 100.0 / time2 - 100.0));
    else if (diff_time(time1, 0) != 0)
        sprintf(buffer, "%f", fabs(time2 * 100.0 / time1 - 100.0));
    else
        sprintf(buffer, "%f", 0.0);
    return buffer;
}
char *perc_int(int time1, int time2, char buffer[])
{
    memset(buffer, '\0', SIZE_OF_BUF * sizeof(char)); // Заполняем буфер
    if (diff_time(time2, 0) != 0)
        sprintf(buffer, "%f", fabs(time1 * 100.0 / time2 - 100.0));
    else if (diff_time(time1, 0) != 0)
        sprintf(buffer, "%f", fabs(time2 * 100.0 / time1 - 100.0));
    else
        sprintf(buffer, "%f", 0.0);
    return buffer;
}

// замеряет размер файла
long int mem_file(char *strk_file)
{
    FILE *file = fopen(strk_file, "rb");
    fseek(file, 0, SEEK_END);
    long int file_size = ftell(file);
    fclose(file);
    return file_size;
}

// замеряет время поиска в дереве
double clock_find_tree(char *strk_file, double *avg_k, int bal)
{
    struct Node *Head = NULL;
    FILE *file = fopen(strk_file, "r");
    tree_from_file(&Head, file, 0);
    if (bal)
        Head = balance_tree(Head);
    fseek(file, 0, SEEK_SET);
    double time_start = 0.0;
    double time_find_tree = 0.0;
    int x = 0;
    int count = 0;
    int k, k_res = 0, k_num = 0;
    time_start = clock();
    while (fscanf(file, "%d", &x) == 1)
    {
        count++;
        for (int i = 0; i < COUNT_SORT; i++)
        {
            k = 0;
            if (tree_find_elem(Head, x, &k) != NULL)
            {
                k_res += k;
                k_num++;
            }
        }
    }
    time_find_tree += clock() - time_start;
    *avg_k = 0;
    if (k_num != 0)
        *avg_k = (double) k_res / (double) k_num;
    tree_free(&Head);
    fclose(file);
    return time_find_tree / (count *  COUNT_SORT);
}

// замеряет время поиска в хэш-таблице с внешним хэшированием
double clock_find_chash(char *strk_file, double *avg_k)
{
    struct Hash_close *Table_close;
    FILE *file = fopen(strk_file, "r");
    chash_create(START_SIZE_HASH_BRES, &Table_close);
    chash_from_file(&Table_close, file);
    fseek(file, 0, SEEK_SET);
    double time_start = 0.0;
    double time_find_tree = 0.0;
    int x = 0;
    int count = 0;
    int k, k_res = 0, k_num = 0;
    time_start = clock();
    while (fscanf(file, "%d", &x) == 1)
    {
        count++;
        for (int i = 0; i < COUNT_SORT; i++)
        {
            k = 0;
            if (chash_find_elem(Table_close, x, &k, 0) != NULL)
            {
                k_res += k;
                k_num++;
            }
        }
    }
    time_find_tree += clock() - time_start;
    *avg_k = 0;
    if (k_num != 0)
        *avg_k = (double) k_res / (double) k_num;
    chash_free(&Table_close);
    fclose(file);
    return time_find_tree / (count *  COUNT_SORT);
}

// замеряет время поиска в хэш-таблице с внутренним хэшированием
double clock_find_ohash(char *strk_file, double *avg_k)
{
    struct Hash_open *Table_open;
    FILE *file = fopen(strk_file, "r");
    ohash_create(START_SIZE_HASH_BRES, &Table_open);
    ohash_from_file(&Table_open, file);
    fseek(file, 0, SEEK_SET);
    double time_start = 0.0;
    double time_find_tree = 0.0;
    int x = 0;
    int count = 0;
    int k, k_res = 0, k_num = 0;
    time_start = clock();
    while (fscanf(file, "%d", &x) == 1)
    {
        count++;
        for (int i = 0; i < COUNT_SORT; i++)
        {
            k = 0;
            if (ohash_find_elem(Table_open, x, &k, 0) != NULL)
            {
                k_res += k;
                k_num++;
            }
        }
    }
    time_find_tree += clock() - time_start;
    *avg_k = 0;
    if (k_num != 0)
        *avg_k = (double) k_res / (double) k_num;
    ohash_free(&Table_open);
    fclose(file);
    return time_find_tree / (count *  COUNT_SORT);
}

// Сравнивается эффективность поиска в зависимости от высоты деревьев и степени их ветвления
void build_res_find(void)
{
    srand(time(NULL));
    // таблица
    ft_table_t *table = ft_create_table();

    // времена числа
    // поиск 100 элементов
    double time_find_tree_100 = 0.0;
    double avg_find_tree_100 = 0.0;
    double time_find_btree_100 = 0.0;
    double avg_find_btree_100 = 0.0;
    double time_find_chash_100 = 0.0;
    double avg_find_chash_100 = 0.0;
    double time_find_ohash_100 = 0.0;
    double avg_find_ohash_100 = 0.0;
    long int mem_tree_100 = 0;
    long int mem_btree_100 = 0;
    long int mem_chash_100 = 0;
    long int mem_ohash_100 = 0;
    // поиск 1000 элементов
    double time_find_tree_1000 = 0.0;
    double avg_find_tree_1000 = 0.0;
    double time_find_btree_1000 = 0.0;
    double avg_find_btree_1000 = 0.0;
    double time_find_chash_1000 = 0.0;
    double avg_find_chash_1000 = 0.0;
    double time_find_ohash_1000 = 0.0;
    double avg_find_ohash_1000 = 0.0;
    long int mem_tree_1000 = 0;
    long int mem_btree_1000 = 0;
    long int mem_chash_1000 = 0;
    long int mem_ohash_1000 = 0;
    // поиск 50 элементов
    double time_find_tree_50 = 0.0;
    double avg_find_tree_50 = 0.0;
    double time_find_btree_50 = 0.0;
    double avg_find_btree_50 = 0.0;
    double time_find_chash_50 = 0.0;
    double avg_find_chash_50 = 0.0;
    double time_find_ohash_50 = 0.0;
    double avg_find_ohash_50 = 0.0;
    long int mem_tree_50 = 0;
    long int mem_btree_50 = 0;
    long int mem_chash_50 = 0;
    long int mem_ohash_50 = 0;

    // времена строками
    // поиск 100 элементов
    char time_find_tree_100_c[SIZE_OF_BUF];
    char avg_find_tree_100_c[SIZE_OF_BUF];
    char time_find_btree_100_c[SIZE_OF_BUF];
    char avg_find_btree_100_c[SIZE_OF_BUF];
    char time_find_chash_100_c[SIZE_OF_BUF];
    char avg_find_chash_100_c[SIZE_OF_BUF];
    char time_find_ohash_100_c[SIZE_OF_BUF];
    char avg_find_ohash_100_c[SIZE_OF_BUF];
    char mem_tree_100_c[SIZE_OF_BUF];
    char mem_btree_100_c[SIZE_OF_BUF];
    char mem_chash_100_c[SIZE_OF_BUF];
    char mem_ohash_100_c[SIZE_OF_BUF];
    // поиск 1000 элементов
    char time_find_tree_1000_c[SIZE_OF_BUF];
    char avg_find_tree_1000_c[SIZE_OF_BUF];
    char time_find_btree_1000_c[SIZE_OF_BUF];
    char avg_find_btree_1000_c[SIZE_OF_BUF];
    char time_find_chash_1000_c[SIZE_OF_BUF];
    char avg_find_chash_1000_c[SIZE_OF_BUF];
    char time_find_ohash_1000_c[SIZE_OF_BUF];
    char avg_find_ohash_1000_c[SIZE_OF_BUF];
    char mem_tree_1000_c[SIZE_OF_BUF];
    char mem_btree_1000_c[SIZE_OF_BUF];
    char mem_chash_1000_c[SIZE_OF_BUF];
    char mem_ohash_1000_c[SIZE_OF_BUF];
    // поиск 50 элементов
    char time_find_tree_50_c[SIZE_OF_BUF];
    char avg_find_tree_50_c[SIZE_OF_BUF];
    char time_find_btree_50_c[SIZE_OF_BUF];
    char avg_find_btree_50_c[SIZE_OF_BUF];
    char time_find_chash_50_c[SIZE_OF_BUF];
    char avg_find_chash_50_c[SIZE_OF_BUF];
    char time_find_ohash_50_c[SIZE_OF_BUF];
    char avg_find_ohash_50_c[SIZE_OF_BUF];
    char mem_tree_50_c[SIZE_OF_BUF];
    char mem_btree_50_c[SIZE_OF_BUF];
    char mem_chash_50_c[SIZE_OF_BUF];
    char mem_ohash_50_c[SIZE_OF_BUF];

    // элементы идут по возрастанию
    // 100 элементов
    time_find_tree_100 = clock_find_tree("test/test_100_rand.txt", &avg_find_tree_100, 0);
    sprintf(time_find_tree_100_c, "%lf", time_find_tree_100);
    sprintf(avg_find_tree_100_c, "%lf", avg_find_tree_100);
    time_find_btree_100 = clock_find_tree("test/test_100_rand.txt", &avg_find_btree_100, 1);
    sprintf(time_find_btree_100_c, "%lf", time_find_btree_100);
    sprintf(avg_find_btree_100_c, "%lf", avg_find_btree_100);
    time_find_chash_100 = clock_find_chash("test/test_100_rand.txt", &avg_find_chash_100);
    sprintf(time_find_chash_100_c, "%lf", time_find_chash_100);
    sprintf(avg_find_chash_100_c, "%lf", avg_find_chash_100);
    time_find_ohash_100 = clock_find_ohash("test/test_100_rand.txt", &avg_find_ohash_100);
    sprintf(time_find_ohash_100_c, "%lf", time_find_ohash_100);
    sprintf(avg_find_ohash_100_c, "%lf", avg_find_ohash_100);
    mem_tree_100 = sizeof(struct Node) * 100;
    sprintf(mem_tree_100_c, "%ld", mem_tree_100);
    mem_btree_100 = sizeof(struct Node) * 100;
    sprintf(mem_btree_100_c, "%ld", mem_btree_100);
    mem_chash_100 = sizeof(struct Node_chash) * 100 + sizeof(struct Hash_close) + sizeof(struct Node_chash *) * START_SIZE_HASH_BRES;
    sprintf(mem_chash_100_c, "%ld", mem_chash_100);
    mem_ohash_100 = sizeof(int) * 100 + sizeof(struct Hash_open) + sizeof(int *) * START_SIZE_HASH_BRES;
    sprintf(mem_ohash_100_c, "%ld", mem_ohash_100);
    // 1000 элементов
    time_find_tree_1000 = clock_find_tree("test/test_1000_rand.txt", &avg_find_tree_1000, 0);
    sprintf(time_find_tree_1000_c, "%lf", time_find_tree_1000);
    sprintf(avg_find_tree_1000_c, "%lf", avg_find_tree_1000);
    time_find_btree_1000 = clock_find_tree("test/test_1000_rand.txt", &avg_find_btree_1000, 1);
    sprintf(time_find_btree_1000_c, "%lf", time_find_btree_1000);
    sprintf(avg_find_btree_1000_c, "%lf", avg_find_btree_1000);
    time_find_chash_1000 = clock_find_chash("test/test_1000_rand.txt", &avg_find_chash_1000);
    sprintf(time_find_chash_1000_c, "%lf", time_find_chash_1000);
    sprintf(avg_find_chash_1000_c, "%lf", avg_find_chash_1000);
    time_find_ohash_1000 = clock_find_ohash("test/test_1000_rand.txt", &avg_find_ohash_1000);
    sprintf(time_find_ohash_1000_c, "%lf", time_find_ohash_1000);
    sprintf(avg_find_ohash_1000_c, "%lf", avg_find_ohash_1000);
    mem_tree_1000 = sizeof(struct Node) * 1000;
    sprintf(mem_tree_1000_c, "%ld", mem_tree_1000);
    mem_btree_1000 = sizeof(struct Node) * 1000;
    sprintf(mem_btree_1000_c, "%ld", mem_btree_1000);
    mem_chash_1000 = sizeof(struct Node_chash) * 1000 + sizeof(struct Hash_close) + sizeof(struct Node_chash *) * START_SIZE_HASH_BRES;
    sprintf(mem_chash_1000_c, "%ld", mem_chash_1000);
    mem_ohash_1000 = sizeof(int) * 1000 + sizeof(struct Hash_open) + sizeof(int *) * START_SIZE_HASH_BRES;
    sprintf(mem_ohash_1000_c, "%ld", mem_ohash_1000);
    // 50 элементов
    time_find_tree_50 = clock_find_tree("test/test_50_rand.txt", &avg_find_tree_50, 0);
    sprintf(time_find_tree_50_c, "%lf", time_find_tree_50);
    sprintf(avg_find_tree_50_c, "%lf", avg_find_tree_50);
    time_find_btree_50 = clock_find_tree("test/test_50_rand.txt", &avg_find_btree_50, 1);
    sprintf(time_find_btree_50_c, "%lf", time_find_btree_50);
    sprintf(avg_find_btree_50_c, "%lf", avg_find_btree_50);
    time_find_chash_50 = clock_find_chash("test/test_50_rand.txt", &avg_find_chash_50);
    sprintf(time_find_chash_50_c, "%lf", time_find_chash_50);
    sprintf(avg_find_chash_50_c, "%lf", avg_find_chash_50);
    time_find_ohash_50 = clock_find_ohash("test/test_50_rand.txt", &avg_find_ohash_50);
    sprintf(time_find_ohash_50_c, "%lf", time_find_ohash_50);
    sprintf(avg_find_ohash_50_c, "%lf", avg_find_ohash_50);
    mem_tree_50 = sizeof(struct Node) * 50;
    sprintf(mem_tree_50_c, "%ld", mem_tree_50);
    mem_btree_50 = sizeof(struct Node) * 50;
    sprintf(mem_btree_50_c, "%ld", mem_btree_50);
    mem_chash_50 = sizeof(struct Node_chash) * 50 + sizeof(struct Hash_close) + sizeof(struct Node_chash *) * START_SIZE_HASH_BRES;
    sprintf(mem_chash_50_c, "%ld", mem_chash_50);
    mem_ohash_50 = sizeof(int) * 50 + sizeof(struct Hash_open) + sizeof(int *) * START_SIZE_HASH_BRES;
    sprintf(mem_ohash_50_c, "%ld", mem_ohash_50);

    printf(" Результаты сравнения эффективности поиска в разных структурах (время в тактах процессора, память в байтах):\n");
    ft_u8write_ln(table, "Количество элементов", "50", "100", "1000");
    ft_u8write_ln(table, "Дерево (время поиска)", time_find_tree_50_c, time_find_tree_100_c, time_find_tree_1000_c);
    ft_u8write_ln(table, "Сбалансированное дерево (время поиска)", time_find_btree_50_c, time_find_btree_100_c, time_find_btree_1000_c);
    ft_u8write_ln(table, "Хэш-таблица с внешним хэшированием (время поиска)", time_find_chash_50_c, time_find_chash_100_c, time_find_chash_1000_c);
    ft_u8write_ln(table, "Хэш-таблица с внутренним хэшированием (время поиска)", time_find_ohash_50_c, time_find_ohash_100_c, time_find_ohash_1000_c);
    ft_u8write_ln(table, "Дерево (число сравнений)", avg_find_tree_50_c, avg_find_tree_100_c, avg_find_tree_1000_c);
    ft_u8write_ln(table, "Сбалансированное дерево (число сравнений)", avg_find_btree_50_c, avg_find_btree_100_c, avg_find_btree_1000_c);
    ft_u8write_ln(table, "Хэш-таблица с внешним хэшированием (число сравнений)", avg_find_chash_50_c, avg_find_chash_100_c, avg_find_chash_1000_c);
    ft_u8write_ln(table, "Хэш-таблица с внутренним хэшированием (число сравнений)", avg_find_ohash_50_c, avg_find_ohash_100_c, avg_find_ohash_1000_c);
    ft_u8write_ln(table, "Дерево (объём памяти)", mem_tree_50_c, mem_tree_100_c, mem_tree_1000_c);
    ft_u8write_ln(table, "Сбалансированное дерево (объём памяти)", mem_btree_50_c, mem_btree_100_c, mem_btree_1000_c);
    ft_u8write_ln(table, "Хэш-таблица с внешним хэшированием (объём памяти)", mem_chash_50_c, mem_chash_100_c, mem_chash_1000_c);
    ft_u8write_ln(table, "Хэш-таблица с внутренним хэшированием (объём памяти)", mem_ohash_50_c, mem_ohash_100_c, mem_ohash_1000_c);

    // perc_double(stay_time_AO_static, stay_time_AO_dinam, buffer));
    ft_set_border_style(table, FT_NICE_STYLE);
    ft_set_cell_prop(table, FT_ANY_ROW, 0, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 1, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 2, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 3, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 4, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 5, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 6, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 7, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 8, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 9, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 10, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 11, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 12, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

    printf("%s\n", ft_to_string(table));
    ft_destroy_table(table);
}