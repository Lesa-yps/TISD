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

// заполняет файл числами
void fill_file(char *in_file, char *out_file)
{
    FILE *file1 = fopen(in_file, "r");
    FILE *file2 = fopen(out_file, "w");
    int x = 0;
    while (fscanf(file1, "%d", &x) == 1)
    {
        file_add_elem(file2, x);
    }
    fclose(file1);
    fclose(file2);
}

// замеряет время добавления в файл
double clock_add_file(char *strk_file)
{
    double time_start = 0.0;
    double time_add_file = 0.0;
    for (int i = 0; i < COUNT_SORT; i++)
    {
        fill_file(strk_file, TEST_FILE_NAME);
        FILE *file = fopen(TEST_FILE_NAME, "a");
        int x = 1000000 + i;
        time_start = clock();
        file_add_elem(file, x);
        time_add_file += clock() - time_start;
        fclose(file);
    }
    return time_add_file / COUNT_SORT;
}

// замеряет время добавления в дерево
double clock_add_tree(char *strk_file)
{
    struct Node *Head = NULL;
    FILE *file = fopen(strk_file, "r");
    tree_from_file(&Head, file, 0);
    fclose(file);
    double time_start = 0.0;
    double time_add_tree = 0.0;
    for (int i = 0; i < COUNT_SORT; i++)
    {
        int x = 1000000 + i;
        time_start = clock();
        tree_add_elem(Head, x, 0);
        time_add_tree += clock() - time_start;
        tree_del_elem(Head, x);
    }
    tree_free(&Head);
    return time_add_tree / COUNT_SORT;
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
double clock_find_tree(char *strk_file)
{
    struct Node *Head = NULL;
    FILE *file = fopen(strk_file, "r");
    tree_from_file(&Head, file, 0);
    fseek(file, 0, SEEK_SET);
    double time_start = 0.0;
    double time_find_tree = 0.0;
    int x = 0;
    int count = 0;
    time_start = clock();
    while (fscanf(file, "%d", &x) == 1)
    {
        count++;
        for (int i = 0; i < COUNT_SORT; i++)
            tree_find_elem(Head, x);
    }
    time_find_tree += clock() - time_start;
    tree_free(&Head);
    fclose(file);
    return time_find_tree / (count *  COUNT_SORT);
}

// Сравнивается эффективность алгоритмов добавления чисел в файл и в дерево
int build_res_add(void)
{
    srand(time(NULL));
    int rc = OK;
    ft_table_t *table = ft_create_table();

    char buffer[SIZE_OF_BUF];

    // времена числа
    // общее время добавления 100 элементов
    double time_add_file_100_side = 0.0;
    double time_add_tree_100_side = 0.0;
    double time_add_file_100_balance = 0.0;
    double time_add_tree_100_balance = 0.0;
    double time_add_file_100_random = 0.0;
    double time_add_tree_100_random = 0.0;
    long int mem_tree_100 = 0;
    long int mem_file_100 = 0;
    // общее время добавления 10 элементов
    double time_add_file_10_side = 0.0;
    double time_add_tree_10_side = 0.0;
    double time_add_file_10_balance = 0.0;
    double time_add_tree_10_balance = 0.0;
    double time_add_file_10_random = 0.0;
    double time_add_tree_10_random = 0.0;
    long int mem_tree_10 = 0;
    long int mem_file_10 = 0;
    // общее время добавления 50 элементов
    double time_add_file_50_side = 0.0;
    double time_add_tree_50_side = 0.0;
    double time_add_file_50_balance = 0.0;
    double time_add_tree_50_balance = 0.0;
    double time_add_file_50_random = 0.0;
    double time_add_tree_50_random = 0.0;
    long int mem_tree_50 = 0;
    long int mem_file_50 = 0;

    // времена строками
    // общее время добавления 100 элементов
    char time_add_file_100_side_char[SIZE_OF_BUF];
    char time_add_tree_100_side_char[SIZE_OF_BUF];
    char time_add_file_100_balance_char[SIZE_OF_BUF];
    char time_add_tree_100_balance_char[SIZE_OF_BUF];
    char time_add_file_100_random_char[SIZE_OF_BUF];
    char time_add_tree_100_random_char[SIZE_OF_BUF];
    char mem_tree_100_char[SIZE_OF_BUF];
    char mem_file_100_char[SIZE_OF_BUF];
    // общее время добавления 10 элементов
    char time_add_file_10_side_char[SIZE_OF_BUF];
    char time_add_tree_10_side_char[SIZE_OF_BUF];
    char time_add_file_10_balance_char[SIZE_OF_BUF];
    char time_add_tree_10_balance_char[SIZE_OF_BUF];
    char time_add_file_10_random_char[SIZE_OF_BUF];
    char time_add_tree_10_random_char[SIZE_OF_BUF];
    char mem_tree_10_char[SIZE_OF_BUF];
    char mem_file_10_char[SIZE_OF_BUF];
    // общее время добавления 50 элементов
    char time_add_file_50_side_char[SIZE_OF_BUF];
    char time_add_tree_50_side_char[SIZE_OF_BUF];
    char time_add_file_50_balance_char[SIZE_OF_BUF];
    char time_add_tree_50_balance_char[SIZE_OF_BUF];
    char time_add_file_50_random_char[SIZE_OF_BUF];
    char time_add_tree_50_random_char[SIZE_OF_BUF];
    char mem_tree_50_char[SIZE_OF_BUF];
    char mem_file_50_char[SIZE_OF_BUF];

    // элементы идут по возрастанию
    // 100 элементов
    // добавление в файл
    time_add_file_100_side = clock_add_file("test/test_100_sort.txt");
    sprintf(time_add_file_100_side_char, "%f", time_add_file_100_side);
    // добавление в дерево
    time_add_tree_100_side = clock_add_tree("test/test_100_sort.txt");
    sprintf(time_add_tree_100_side_char, "%f", time_add_tree_100_side);
    // 10 элементов
    // добавление в файл
    time_add_file_10_side = clock_add_file("test/test_10_sort.txt");
    sprintf(time_add_file_10_side_char, "%f", time_add_file_10_side);
    // добавление в дерево
    time_add_tree_10_side = clock_add_tree("test/test_10_sort.txt");
    sprintf(time_add_tree_10_side_char, "%f", time_add_tree_10_side);
    // 50 элементов
    // добавление в файл
    time_add_file_50_side = clock_add_file("test/test_50_sort.txt");
    sprintf(time_add_file_50_side_char, "%f", time_add_file_50_side);
    // добавление в дерево
    time_add_tree_50_side = clock_add_tree("test/test_50_sort.txt");
    sprintf(time_add_tree_50_side_char, "%f", time_add_tree_50_side);

    // элементы сбалансированны
    // 5 элементов
    // добавление в файл
    time_add_file_100_balance = clock_add_file("test/test_100_bal.txt");
    sprintf(time_add_file_100_balance_char, "%f", time_add_file_100_balance);
    // добавление в дерево
    time_add_tree_100_balance = clock_add_tree("test/test_100_bal.txt");
    sprintf(time_add_tree_100_balance_char, "%f", time_add_tree_100_balance);
    // 10 элементов
    // добавление в файл
    time_add_file_10_balance = clock_add_file("test/test_10_bal.txt");
    sprintf(time_add_file_10_balance_char, "%f", time_add_file_10_balance);
    // добавление в дерево
    time_add_tree_10_balance = clock_add_tree("test/test_10_bal.txt");
    sprintf(time_add_tree_10_balance_char, "%f", time_add_tree_10_balance);
    // 50 элементов
    // добавление в файл
    time_add_file_50_balance = clock_add_file("test/test_50_bal.txt");
    sprintf(time_add_file_50_balance_char, "%f", time_add_file_50_balance);
    // добавление в дерево
    time_add_tree_50_balance = clock_add_tree("test/test_50_bal.txt");
    sprintf(time_add_tree_50_balance_char, "%f", time_add_tree_50_balance);

    // элементы рандомны
    // 100 элементов
    // добавление в файл
    time_add_file_100_random = clock_add_file("test/test_100_rand.txt");
    sprintf(time_add_file_100_random_char, "%f", time_add_file_100_random);
    // добавление в дерево
    time_add_tree_100_random = clock_add_tree("test/test_100_rand.txt");
    sprintf(time_add_tree_100_random_char, "%f", time_add_tree_100_random);
    // 10 элементов
    // добавление в файл
    time_add_file_10_random = clock_add_file("test/test_10_rand.txt");
    sprintf(time_add_file_10_random_char, "%f", time_add_file_10_random);
    // добавление в дерево
    time_add_tree_10_random = clock_add_tree("test/test_10_rand.txt");
    sprintf(time_add_tree_10_random_char, "%f", time_add_tree_10_random);
    // 50 элементов
    // добавление в файл
    time_add_file_50_random = clock_add_file("test/test_50_rand.txt");
    sprintf(time_add_file_50_random_char, "%f", time_add_file_50_random);
    // добавление в дерево
    time_add_tree_50_random = clock_add_tree("test/test_50_rand.txt");
    sprintf(time_add_tree_50_random_char, "%f", time_add_tree_50_random);

    mem_tree_100 = sizeof(struct Node) * (100 + 1);
    mem_tree_10 = sizeof(struct Node) * (10 + 1);
    mem_tree_50 = sizeof(struct Node) * (50 + 1);
    mem_file_100 = mem_file("test/test_100_sort.txt");
    mem_file_10 = mem_file("test/test_10_sort.txt");
    mem_file_50 = mem_file("test/test_50_sort.txt");
    sprintf(mem_tree_100_char, "%ld", mem_tree_100);
    sprintf(mem_file_100_char, "%ld", mem_file_100);
    sprintf(mem_tree_10_char, "%ld", mem_tree_10);
    sprintf(mem_file_10_char, "%ld", mem_file_10);
    sprintf(mem_tree_50_char, "%ld", mem_tree_50);
    sprintf(mem_file_50_char, "%ld", mem_file_50);

    printf(" Результаты сравнения добавления в файл и в дерево (время в тактах процессора, память в байтах):\n");
    ft_u8write_ln(table, "?", "ФАЙЛ", "ДЕРЕВО", "%");
    ft_u8write_ln(table, "Отсортированный (10 элем) время", time_add_file_10_side_char, time_add_tree_10_side_char, perc_double(time_add_file_10_side, time_add_tree_10_side, buffer));
    ft_u8write_ln(table, "Сбалансированный (10 элем) время", time_add_file_10_balance_char, time_add_tree_10_balance_char, perc_double(time_add_file_10_balance, time_add_tree_10_balance, buffer));
    ft_u8write_ln(table, "Рандомный (10 элем) время", time_add_file_10_random_char, time_add_tree_10_random_char, perc_double(time_add_file_10_random, time_add_tree_10_random, buffer));
    ft_u8write_ln(table, "(10 элем) память", mem_file_10_char, mem_tree_10_char, perc_double(mem_file_10, mem_tree_10, buffer));
    ft_u8write_ln(table, "Отсортированный (50 элем) время", time_add_file_50_side_char, time_add_tree_50_side_char, perc_double(time_add_file_50_side, time_add_tree_50_side, buffer));
    ft_u8write_ln(table, "Сбалансированный (50 элем) время", time_add_file_50_balance_char, time_add_tree_50_balance_char, perc_double(time_add_file_50_balance, time_add_tree_50_balance, buffer));
    ft_u8write_ln(table, "Рандомный (50 элем) время", time_add_file_50_random_char, time_add_tree_50_random_char, perc_double(time_add_file_50_random, time_add_tree_50_random, buffer));
    ft_u8write_ln(table, "(50 элем) память", mem_file_50_char, mem_tree_50_char, perc_double(mem_file_50, mem_tree_50, buffer));
    ft_u8write_ln(table, "Отсортированный (100 элем) время", time_add_file_100_side_char, time_add_tree_100_side_char, perc_double(time_add_file_100_side, time_add_tree_100_side, buffer));
    ft_u8write_ln(table, "Сбалансированный (100 элем) время", time_add_file_100_balance_char, time_add_tree_100_balance_char, perc_double(time_add_file_100_balance, time_add_tree_100_balance, buffer));
    ft_u8write_ln(table, "Рандомный (100 элем) время", time_add_file_100_random_char, time_add_tree_100_random_char, perc_double(time_add_file_100_random, time_add_tree_100_random, buffer));
    ft_u8write_ln(table, "(100 элем) память", mem_file_100_char, mem_tree_100_char, perc_double(mem_file_100, mem_tree_100, buffer));
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
    return rc;
}

// Сравнивается эффективность поиска в зависимости от высоты деревьев и степени их ветвления
void build_res_find(void)
{
    srand(time(NULL));
    // таблица
    ft_table_t *table = ft_create_table();

    // времена числа
    // общее время добавления 100 элементов
    double time_find_tree_100_side = 0.0;
    double time_find_tree_100_balance = 0.0;
    double time_find_tree_100_random = 0.0;
    long int mem_tree_100 = 0;
    // общее время добавления 10 элементов
    double time_find_tree_10_side = 0.0;
    double time_find_tree_10_balance = 0.0;
    double time_find_tree_10_random = 0.0;
    long int mem_tree_10 = 0;
    // общее время добавления 50 элементов
    double time_find_tree_50_side = 0.0;
    double time_find_tree_50_balance = 0.0;
    double time_find_tree_50_random = 0.0;
    long int mem_tree_50 = 0;

    // времена строками
    // общее время добавления 100 элементов
    char time_find_tree_100_side_char[SIZE_OF_BUF];
    char time_find_tree_100_balance_char[SIZE_OF_BUF];
    char time_find_tree_100_random_char[SIZE_OF_BUF];
    char mem_tree_100_char[SIZE_OF_BUF];
    // общее время добавления 10 элементов
    char time_find_tree_10_side_char[SIZE_OF_BUF];
    char time_find_tree_10_balance_char[SIZE_OF_BUF];
    char time_find_tree_10_random_char[SIZE_OF_BUF];
    char mem_tree_10_char[SIZE_OF_BUF];
    // общее время добавления 50 элементов
    char time_find_tree_50_side_char[SIZE_OF_BUF];
    char time_find_tree_50_balance_char[SIZE_OF_BUF];
    char time_find_tree_50_random_char[SIZE_OF_BUF];
    char mem_tree_50_char[SIZE_OF_BUF];

    // элементы идут по возрастанию
    // 100 элементов
    time_find_tree_100_side = clock_find_tree("test/test_100_sort.txt");
    sprintf(time_find_tree_100_side_char, "%f", time_find_tree_100_side);
    // 10 элементов
    time_find_tree_10_side = clock_find_tree("test/test_10_sort.txt");
    sprintf(time_find_tree_10_side_char, "%f", time_find_tree_10_side);
    // 50 элементов
    time_find_tree_50_side = clock_find_tree("test/test_50_sort.txt");
    sprintf(time_find_tree_50_side_char, "%f", time_find_tree_50_side);

    // элементы сбалансированны
    // 100 элементов
    time_find_tree_100_balance = clock_find_tree("test/test_100_bal.txt");
    sprintf(time_find_tree_100_balance_char, "%f", time_find_tree_100_balance);
    // 10 элементов
    time_find_tree_10_balance = clock_find_tree("test/test_10_bal.txt");
    sprintf(time_find_tree_10_balance_char, "%f", time_find_tree_10_balance);
    // 50 элементов
    time_find_tree_50_balance = clock_find_tree("test/test_50_bal.txt");
    sprintf(time_find_tree_50_balance_char, "%f", time_find_tree_50_balance);

    // элементы рандомны
    // 100 элементов
    time_find_tree_100_random = clock_find_tree("test/test_100_rand.txt");
    sprintf(time_find_tree_100_random_char, "%f", time_find_tree_100_random);
    // 10 элементов
    time_find_tree_10_random = clock_find_tree("test/test_10_rand.txt");
    sprintf(time_find_tree_10_random_char, "%f", time_find_tree_10_random);
    // 50 элементов
    time_find_tree_50_random = clock_find_tree("test/test_50_rand.txt");
    sprintf(time_find_tree_50_random_char, "%f", time_find_tree_50_random);

    mem_tree_100 = sizeof(struct Node) * (100 + 1);
    mem_tree_10 = sizeof(struct Node) * (10 + 1);
    mem_tree_50 = sizeof(struct Node) * (50 + 1);
    sprintf(mem_tree_100_char, "%ld", mem_tree_100);
    sprintf(mem_tree_10_char, "%ld", mem_tree_10);
    sprintf(mem_tree_50_char, "%ld", mem_tree_50);

    printf(" Результаты сравнения эффективности поиска в дереве в зависимости от высоты и степени ветвления (время в тактах процессора, память в байтах):\n");
    ft_u8write_ln(table, "Количество элементов", "10", "50", "100");
    ft_u8write_ln(table, "Отсортированный (время)", time_find_tree_10_side_char, time_find_tree_50_side_char, time_find_tree_100_side_char);
    ft_u8write_ln(table, "Сбалансированный (время)", time_find_tree_10_balance_char, time_find_tree_50_balance_char, time_find_tree_100_balance_char);
    ft_u8write_ln(table, "Рандомный (время)", time_find_tree_10_random_char, time_find_tree_50_random_char, time_find_tree_100_random_char);
    ft_u8write_ln(table, "Память", mem_tree_10_char, mem_tree_50_char, mem_tree_100_char);

    // perc_double(stay_time_AO_static, stay_time_AO_dinam, buffer));
    ft_set_border_style(table, FT_NICE_STYLE);
    ft_set_cell_prop(table, FT_ANY_ROW, 0, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 1, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 2, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 3, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 4, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

    printf("%s\n", ft_to_string(table));
    ft_destroy_table(table);
}