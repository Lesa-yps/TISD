#include "build_res.h"

#define SIZE_OF_BUF 100

// выигрыш от 2 в процентах
char *perc_double(double time1, double time2, char buffer[])
{
    memset(buffer, '\0', SIZE_OF_BUF * sizeof(char));  // Заполняем буфер
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
    memset(buffer, '\0', SIZE_OF_BUF * sizeof(char));  // Заполняем буфер
    if (diff_time(time2, 0) != 0)
        sprintf(buffer, "%f", fabs(time1 * 100.0 / time2 - 100.0));
    else if (diff_time(time1, 0) != 0)
        sprintf(buffer, "%f", fabs(time2 * 100.0 / time1 - 100.0));
    else
        sprintf(buffer, "%f", 0.0);
    return buffer;
}

// функции для заполнения файла
int f_plus(int x)
{
    return x + 1;
}
int f_balance(int x)
{
    if (x > 0)
        x++;
    else
        x--;
    return -x;
}
int f_rand(int x)
{
    return MIN_X + rand() / (RAND_MAX / (MAX_X - MIN_X + 1) + 1);
}

int f_rand_add(void)
{
    int x = MIN_X;
    while (x <= MAX_X && x >+ MIN_X)
        x = MIN_X_ADD + rand() / (RAND_MAX / (MAX_X_ADD - MIN_X_ADD + 1) + 1);
    return x;
}

// заполняет файл числами по переданному закону
int fill_file(int count, int (*f)(int))
{
    FILE *file = fopen(TEST_FILE_NAME, "w");
    if (file == NULL)
        return ERR_OPEN;
    int x = f(0);
    for (int i = 0; i < count; i++)
    {
        file_add_elem(file, x);
        x = f(x);
    }
    fclose(file);
    return OK;
}

// замеряет время добавления в файл
double clock_add_file(int count, int (*f)(int))
{
    double time_start = 0.0;
    double time_add_file = 0.0;
    for (int i = 0; i < COUNT_SORT; i++)
    {
        fill_file(count, f);
        int x = f_rand_add();
        FILE *file = fopen(TEST_FILE_NAME, "r+");
        time_start = clock();
        file_add_elem(file, x);
        time_add_file += time_start - clock();
        fclose(file);
    }
    fill_file(count, f);
    return time_add_file;
}

// замеряет время добавления в дерево
double clock_add_tree(int count, int (*f)(int))
{
    struct Node *Head;
    FILE *file = fopen(TEST_FILE_NAME, "r+");
    tree_from_file(&Head, file);
    double time_start = 0.0;
    double time_add_tree = 0.0;
    for (int i = 0; i < COUNT_SORT; i++)
    {
        int x = f_rand_add();
        time_start = clock();
        tree_add_elem(Head, x);
        time_add_tree += time_start - clock();
        tree_del_elem(Head, x);
    }
    fclose(file);
    tree_free(Head);
    return time_add_tree;
}

// Сравнивается эффективность алгоритмов добавления чисел в файл и в дерево
int build_res_add(void)
{
    srand(time);
    printf("Результат сравнения функций добавления в дерево и в файл:\n");
    int rc = OK;
    FILE *file;
    ft_table_t *table = ft_create_table();

    char buffer[SIZE_OF_BUF];

    // времена числа
    double time_start = 0.0;
    // общее время добавления 5 элементов
    double time_add_file_5_side = 0.0;
    double time_add_tree_5_side = 0.0;
    double time_add_file_5_balance = 0.0;
    double time_add_tree_5_balance = 0.0;
    double time_add_file_5_random = 0.0;
    double time_add_tree_5_random = 0.0;
    long int mem_tree_5 = 0;
    long int mem_file_5 = 0;
    // общее время добавления 10 элементов
    double time_add_file_10_side = 0.0;
    double time_add_tree_10_side = 0.0;
    double time_add_file_10_balance = 0.0;
    double time_add_tree_10_balance = 0.0;
    double time_add_file_10_random = 0.0;
    double time_add_tree_10_random = 0.0;
    long int mem_tree_10 = 0;
    long int mem_file_10 = 0;
    // общее время добавления 20 элементов
    double time_add_file_20_side = 0.0;
    double time_add_tree_20_side = 0.0;
    double time_add_file_20_balance = 0.0;
    double time_add_tree_20_balance = 0.0;
    double time_add_file_20_random = 0.0;
    double time_add_tree_20_random = 0.0;
    long int mem_tree_20 = 0;
    long int mem_file_20 = 0;

    // времена строками
    // общее время добавления 5 элементов
    char time_add_file_5_side_char[SIZE_OF_BUF];
    char time_add_tree_5_side_char[SIZE_OF_BUF];
    char time_add_file_5_balance_char[SIZE_OF_BUF];
    char time_add_tree_5_balance_char[SIZE_OF_BUF];
    char time_add_file_5_random_char[SIZE_OF_BUF];
    char time_add_tree_5_random_char[SIZE_OF_BUF];
    char mem_tree_5_char[SIZE_OF_BUF];
    char mem_file_5_char[SIZE_OF_BUF];
    // общее время добавления 10 элементов
    char time_add_file_10_side_char[SIZE_OF_BUF];
    char time_add_tree_10_side_char[SIZE_OF_BUF];
    char time_add_file_10_balance_char[SIZE_OF_BUF];
    char time_add_tree_10_balance_char[SIZE_OF_BUF];
    char time_add_file_10_random_char[SIZE_OF_BUF];
    char time_add_tree_10_random_char[SIZE_OF_BUF];
    char mem_tree_10_char[SIZE_OF_BUF];
    char mem_file_10_char[SIZE_OF_BUF];
    // общее время добавления 20 элементов
    char time_add_file_20_side_char[SIZE_OF_BUF];
    char time_add_tree_20_side_char[SIZE_OF_BUF];
    char time_add_file_20_balance_char[SIZE_OF_BUF];
    char time_add_tree_20_balance_char[SIZE_OF_BUF];
    char time_add_file_20_random_char[SIZE_OF_BUF];
    char time_add_tree_20_random_char[SIZE_OF_BUF];
    char mem_tree_20_char[SIZE_OF_BUF];
    char mem_file_20_char[SIZE_OF_BUF];

    // элементы идут по возрастанию
    // 5 элементов
    // добавление в файл
    time_add_file_5_side = clock_add_file(5, f_plus);
    sprintf(time_add_file_5_side_char, "%f", time_add_file_5_side / COUNT_SORT);
    // добавление в дерево
    time_add_tree_5_side = clock_add_tree(5, f_plus);
    sprintf(time_add_tree_5_side_char, "%f", time_add_tree_5_side / COUNT_SORT);
    // 10 элементов
    // добавление в файл
    time_add_file_10_side = clock_add_file(10, f_plus);
    sprintf(time_add_file_10_side_char, "%f", time_add_file_10_side / COUNT_SORT);
    // добавление в дерево
    time_add_tree_10_side = clock_add_tree(10, f_plus);
    sprintf(time_add_tree_10_side_char, "%f", time_add_tree_10_side / COUNT_SORT);
    // 20 элементов
    // добавление в файл
    time_add_file_20_side = clock_add_file(20, f_plus);
    sprintf(time_add_file_20_side_char, "%f", time_add_file_20_side / COUNT_SORT);
    // добавление в дерево
    time_add_tree_20_side = clock_add_tree(20, f_plus);
    sprintf(time_add_tree_20_side_char, "%f", time_add_tree_20_side / COUNT_SORT);

    // элементы сбалансированны
    // 5 элементов
    // добавление в файл
    time_add_file_5_balance = clock_add_file(5, f_balance);
    sprintf(time_add_file_5_balance_char, "%f", time_add_file_5_balance / COUNT_SORT);
    // добавление в дерево
    time_add_tree_5_balance = clock_add_tree(5, f_balance);
    sprintf(time_add_tree_5_balance_char, "%f", time_add_tree_5_balance / COUNT_SORT);
    // 10 элементов
    // добавление в файл
    time_add_file_10_balance = clock_add_file(10, f_balance);
    sprintf(time_add_file_10_balance_char, "%f", time_add_file_10_balance / COUNT_SORT);
    // добавление в дерево
    time_add_tree_10_balance = clock_add_tree(10, f_balance);
    sprintf(time_add_tree_10_balance_char, "%f", time_add_tree_10_balance / COUNT_SORT);
    // 20 элементов
    // добавление в файл
    time_add_file_20_balance = clock_add_file(20, f_balance);
    sprintf(time_add_file_20_balance_char, "%f", time_add_file_20_balance / COUNT_SORT);
    // добавление в дерево
    time_add_tree_20_balance = clock_add_tree(20, f_balance);
    sprintf(time_add_tree_20_balance_char, "%f", time_add_tree_20_balance / COUNT_SORT);

    // элементы рандомны
    // 5 элементов
    // добавление в файл
    time_add_file_5_random = clock_add_file(5, f_rand);
    sprintf(time_add_file_5_random_char, "%f", time_add_file_5_random / COUNT_SORT);
    // добавление в дерево
    time_add_tree_5_random = clock_add_tree(5, f_rand);
    sprintf(time_add_tree_5_random_char, "%f", time_add_tree_5_random / COUNT_SORT);
    // 10 элементов
    // добавление в файл
    time_add_file_10_random = clock_add_file(10, f_rand);
    sprintf(time_add_file_10_random_char, "%f", time_add_file_10_random / COUNT_SORT);
    // добавление в дерево
    time_add_tree_10_random = clock_add_tree(10, f_rand);
    sprintf(time_add_tree_10_random_char, "%f", time_add_tree_10_random / COUNT_SORT);
    // 20 элементов
    // добавление в файл
    time_add_file_20_random = clock_add_file(20, f_rand);
    sprintf(time_add_file_20_random_char, "%f", time_add_file_20_random / COUNT_SORT);
    // добавление в дерево
    time_add_tree_20_random = clock_add_tree(20, f_rand);
    sprintf(time_add_tree_20_random_char, "%f", time_add_tree_20_random / COUNT_SORT);

    mem_tree_5 = sizeof(struct Node) * (5 + 1);
    mem_file_5 = sizeof(int) * 5 + sizeof(file);
    mem_tree_10 = sizeof(struct Node) * (10 + 1);
    mem_file_10 = sizeof(int) * 10 + sizeof(file);
    mem_tree_20 = sizeof(struct Node) * (20 + 1);
    mem_file_20 = sizeof(int) * 20 + sizeof(file);
    sprintf(mem_tree_5_char, "%ld", mem_tree_5);
    sprintf(mem_file_5_char, "%ld", mem_file_5);
    sprintf(mem_tree_10_char, "%ld", mem_tree_10);
    sprintf(mem_file_10_char, "%ld", mem_file_10);
    sprintf(mem_tree_20_char, "%ld", mem_tree_20);
    sprintf(mem_file_20_char, "%ld", mem_file_20);

    printf("    Результаты сравнения добавления в файл и в дерево (время в тактах процессора, память в байтах):\n");
    ft_u8write_ln(table, "?", "статический массив", "односвязный список", "%");
    ft_u8write_ln(table, "Время работы АО", work_time_AO_static_c, work_time_AO_dinam_c, perc_double(work_time_AO_static, work_time_AO_dinam, buffer));
    ft_u8write_ln(table, "Количество вошедших заявок", app_come_static_c, app_come_dinam_c, perc_int(app_come_static, app_come_dinam, buffer));
    ft_u8write_ln(table, "Количество вышедших заявок", app_away_static_c, app_away_dinam_c, perc_int(app_away_static, app_away_dinam, buffer));
    ft_u8write_ln(table, "Количество срабатываний АО", count_work_AO_static_c, count_work_AO_dinam_c, perc_int(count_work_AO_static, count_work_AO_dinam, buffer));
    ft_u8write_ln(table, "Время простоя", stay_time_AO_static_c, stay_time_AO_dinam_c, perc_double(stay_time_AO_static, stay_time_AO_dinam, buffer));
    ft_u8write_ln(table, "Практическое время моделирования", teor_all_time_static_c, teor_all_time_dinam_c, perc_double(teor_all_time_static, teor_all_time_dinam, buffer));
    ft_u8write_ln(table, "Теоретическое время моделирования", teor_all_time_AO_static_c, teor_all_time_AO_dinam_c, perc_double(teor_all_time_AO_static, teor_all_time_AO_dinam, buffer));
    ft_u8write_ln(table, "Погрешность (%)", err_all_time_AO_static_c, err_all_time_AO_dinam_c, perc_double(err_all_time_AO_static, err_all_time_AO_dinam, buffer));

    ft_set_border_style(table, FT_NICE_STYLE);
    ft_set_cell_prop(table, FT_ANY_ROW, 0, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 1, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_LEFT);
    ft_set_cell_prop(table, FT_ANY_ROW, 2, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_LEFT);
    ft_set_cell_prop(table, FT_ANY_ROW, 3, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_LEFT);
    ft_set_cell_prop(table, FT_ANY_ROW, 4, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_LEFT);
    ft_set_cell_prop(table, FT_ANY_ROW, 5, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_LEFT);
    ft_set_cell_prop(table, FT_ANY_ROW, 6, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_LEFT);
    ft_set_cell_prop(table, FT_ANY_ROW, 7, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_LEFT);
    ft_set_cell_prop(table, FT_ANY_ROW, 8, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_LEFT);
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

    printf("%s\n", ft_to_string(table));
    ft_destroy_table(table);
    return rc;
}


// Сравнивается эффективность поиска в зависимости от высоты деревьев и степени их ветвления
void build_res_find(void);