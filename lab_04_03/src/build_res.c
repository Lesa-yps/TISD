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

int build_res()
{
    int rc = OK;
    ft_table_t *table = ft_create_table();

    char buffer[SIZE_OF_BUF];

    double time_start = 0.0;
    // время
    double time_static = 0.0;
    double time_dinam = 0.0;
    // память
    int mem_static = 0;
    int mem_dinam = 0;

    // время
    char time_static_c[SIZE_OF_BUF];
    char time_dinam_c[SIZE_OF_BUF];
    // память
    char mem_static_c[SIZE_OF_BUF];
    char mem_dinam_c[SIZE_OF_BUF];

    struct Inf_stack infa_q1;

    int count_elems = 0;
    printf("Введите количество элементов в стеке: ");
    read_int(&count_elems, 1, MAX_COUNT_ELEM_STAT);

    time_start = clock();
    // прогон симуляции со статическим массивом
    for (int i = 0; i < COUNT_SORT; i++)
    {
        rc = simulate_stat(count_elems, &infa_q1);
        if (rc == ERROR)
            return rc;
    }
    time_static = (clock() - time_start);

    mem_static = (int) (MAX_COUNT_ELEM_STAT * SIZE_OF_STR * sizeof(char));
    time_static /= COUNT_SORT;
    sprintf(time_static_c, "%f", time_static);
    sprintf(mem_static_c, "%d", mem_static);

    time_start = clock();
    // прогон симуляции с односвязным списком
    for (int i = 0; i < COUNT_SORT; i++)
    {
        rc = simulate_dinam(count_elems, &infa_q1);
        if (rc == ERROR)
            return rc;
        mem_dinam += (int) (infa_q1.len_q_max * sizeof(struct Node) + infa_q1.len_strk_max * sizeof(char));
    }
    time_dinam = (clock() - time_start);

    time_dinam /= COUNT_SORT;
    mem_dinam /= COUNT_SORT;
    sprintf(time_dinam_c, "%f", time_dinam);
    sprintf(mem_dinam_c, "%d", mem_dinam);

    printf("    Результаты сравнения разных симуляций (время в тактах процессора, память в байтах):\n");
    ft_u8write_ln(table, "?", "статический массив", "односвязный список", "%");
    ft_u8write_ln(table, "Время", time_static_c, time_dinam_c, perc_double(time_static, time_dinam, buffer));
    ft_u8write_ln(table, "Память", mem_static_c, mem_dinam_c, perc_int(mem_static, mem_dinam, buffer));

    ft_set_border_style(table, FT_NICE_STYLE);
    ft_set_cell_prop(table, FT_ANY_ROW, 0, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 1, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_LEFT);
    ft_set_cell_prop(table, FT_ANY_ROW, 2, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_LEFT);
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

    printf("%s\n", ft_to_string(table));
    ft_destroy_table(table);
    return rc;
}
