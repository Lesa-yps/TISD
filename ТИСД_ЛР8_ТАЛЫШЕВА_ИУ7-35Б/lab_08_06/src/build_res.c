#include "build_res.h"

// замеряет время и память алгоритма
int clock_mem(int count, char *mem_с, char *time_c)
{
    // считали граф как матрицу смежностей
    int n = 0;
    int **matrix = NULL;
    int v1, v2;
    int res;
    FILE *file_in = NULL;
    char file_name[SIZE_OF_BUF];
    snprintf(file_name, SIZE_OF_BUF, "test/graph_%d.txt", count);
    //printf("%s\n", file_name);
    file_in = fopen(file_name, "r");
    if (file_in == NULL)
        return ERROR;
    int rc = read_matrix(file_in, &matrix, &n);
    if (rc != OK)
        return rc;
    double time_start = 0.0;
    double time_work = 0.0;
    // сами замеры
    time_start = clock();
    for (int i = 0; i < COUNT_SORT; i++)
    {
        rc = dijkstra_all(matrix, n, &v1, &v2, &res);
        if (rc != OK)
            return rc;
    }
    time_work += clock() - time_start;
    // всё почистили - закрыли
    free_matrix(&matrix, n);
    fclose(file_in);
    // посчитали результаты и перевели в строки
    sprintf(time_c, "%lf", time_work / COUNT_SORT);
    sprintf(mem_с, "%ld", (sizeof(int*) + sizeof(int) * n + sizeof(int) + sizeof(bool)) * n);
    return rc;
}

// Сравнивается эффективность поиска в зависимости от высоты деревьев и степени их ветвления
int build_res(void)
{
    int rc = OK;
    srand(time(NULL));
    // таблица
    ft_table_t *table = ft_create_table();

    // времена и память строками
    // 10 вершин
    char time_10_c[SIZE_OF_BUF];
    char mem_10_c[SIZE_OF_BUF];
    rc = clock_mem(10, mem_10_c, time_10_c);
    if (rc != OK)
        return rc;
    // 50 вершин
    char time_50_c[SIZE_OF_BUF];
    char mem_50_c[SIZE_OF_BUF];
    rc = clock_mem(50, mem_50_c, time_50_c);
    if (rc != OK)
        return rc;
    // 100 вершин
    char time_100_c[SIZE_OF_BUF];
    char mem_100_c[SIZE_OF_BUF];
    clock_mem(100, mem_100_c, time_100_c);
    if (rc != OK)
        return rc;

    printf(" Результаты сравнения эффективности алгоритма (время в тактах процессора, память в байтах):\n");
    ft_u8write_ln(table, "Количество вершин", "10", "50", "100");
    ft_u8write_ln(table, "Время", time_10_c, time_50_c, time_100_c);
    ft_u8write_ln(table, "Память", mem_10_c, mem_50_c, mem_100_c);

    ft_set_border_style(table, FT_NICE_STYLE);
    ft_set_cell_prop(table, FT_ANY_ROW, 0, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 1, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 2, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

    printf("%s\n", ft_to_string(table));
    ft_destroy_table(table);
    return rc;
}
