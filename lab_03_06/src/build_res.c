#include "build_res.h"

char *lint_to_str(long int num, char buffer[])
{
    memset(buffer, '\0', SIZE_OF_BUF * sizeof(char));  // Заполняем буфер
    sprintf(buffer, "%li", num);
    return buffer;
}

// выигрыш в процентах
double perc(double time_mat, double time_vec);

double calc_perc(struct Normal_mat *comb_mat, struct Normal_arr *comb_arr, struct Normal_arr *res_arr, struct Vector_mat *mat_mini, struct Vector_arr *arr_mini, struct Vector_arr *res_arr_mini,\
                 double *time_mat, double *time_vec, int j, long int *perc_mem_vec, long int *perc_mem_norm);

// функция вычисляет время работы и оптимальную разряженность для использования векторного метода
void build_res(struct Normal_mat *comb_mat, struct Normal_arr *comb_arr, struct Normal_arr *res_arr, struct Vector_mat *mat_mini, struct Vector_arr *arr_mini, struct Vector_arr *res_arr_mini)
{
    int best_j = 0;
    int step_j = 15;
    int j;
    long int perc_mem_vec = 0.0;
    long int perc_mem_norm = 0.0;

    ft_table_t *table = ft_create_table();

    char buffer2[SIZE_OF_BUF];
    char buffer3[SIZE_OF_BUF];

    double time_mat;
    double time_vec;

    char time_mat2[SIZE_OF_BUF];
    char time_vec2[SIZE_OF_BUF];

    char perc_mat_vec[SIZE_OF_BUF];
    char perc_mem[SIZE_OF_BUF];
    char perc_j[SIZE_OF_BUF];

    double percent;
    double best_percent = 0.0;

    printf("\nРезультаты сравнения разных перемножений (время в тактах процессора, память в байтах):\n");
    ft_u8write_ln(table, "заполненность", "векторный метод", "", "матричный метод", "", "выигрыш в процентах", "");
    ft_set_cell_span(table, 0, 1, 2);
    ft_set_cell_span(table, 0, 3, 2);
    ft_set_cell_span(table, 0, 5, 2);
    ft_u8write_ln(table, "", "время", "память", "время", "память", "время", "память");

    for (j = 5; j <= 100; j += step_j)
    {
        //printf("%d\n", j);
        percent = calc_perc(comb_mat, comb_arr, res_arr, mat_mini, arr_mini, res_arr_mini, &time_mat, &time_vec, j, &perc_mem_vec, &perc_mem_norm);

        if ((best_j == 0) || (percent > best_percent))
        {
            best_percent = percent;
            best_j = j;
        }


        sprintf(time_mat2, "%.2f", time_mat);
        sprintf(time_vec2, "%.2f", time_vec);

        sprintf(perc_mat_vec, "%.2f%%", percent);
        sprintf(perc_j, "%d%%", j);

        sprintf(perc_mem, "%.2f%%", perc(perc_mem_norm, perc_mem_vec));

        sprintf(buffer2, "%li", perc_mem_norm);
        sprintf(buffer3, "%li", perc_mem_vec);
        ft_u8write_ln(table, perc_j, time_vec2, buffer3, time_mat2, buffer2, perc_mat_vec, perc_mem);

        ft_set_cell_prop(table, FT_ANY_ROW, j / 20 + 1, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_LEFT);
    }


    percent = calc_perc(comb_mat, comb_arr, res_arr, mat_mini, arr_mini, res_arr_mini, &time_mat, &time_vec, best_j + 5, &perc_mem_vec, &perc_mem_norm);
    //printf("2   %d\n", best_j);
    if (((percent > best_percent)))
    {
        best_percent = percent;
        best_j += 5;
        step_j = 1;
    }
    else
        step_j = -1;
    //printf("1   %d\n", best_j);
    j = best_j;
    percent = calc_perc(comb_mat, comb_arr, res_arr, mat_mini, arr_mini, res_arr_mini, &time_mat, &time_vec, j, &perc_mem_vec, &perc_mem_norm);
    while (((percent > best_percent)) && j < 100 && j > 1)
    {
        best_percent = percent;
        best_j = j;
        //printf("   %d\n", j);
        j += step_j;
        percent = calc_perc(comb_mat, comb_arr, res_arr, mat_mini, arr_mini, res_arr_mini, &time_mat, &time_vec, j, &perc_mem_vec, &perc_mem_norm);
    }
    sprintf(perc_j, "Лучший результат = %d%%", best_j);
    sprintf(time_mat2, "%.2f", time_mat);
    sprintf(time_vec2, "%.2f", time_vec);

    sprintf(perc_mat_vec, "%.2f%%", best_percent);
    sprintf(perc_j, "Лучший вариант: %d%%", j);

    sprintf(perc_mem, "%.2f%%", perc(perc_mem_norm, perc_mem_vec));
    sprintf(buffer2, "%li", perc_mem_norm);
    sprintf(buffer3, "%li", perc_mem_vec);
    ft_u8write_ln(table, perc_j, time_vec2, buffer3, time_mat2, buffer2, perc_mat_vec, perc_mem);


    ft_set_border_style(table, FT_NICE_STYLE);
    ft_set_cell_prop(table, FT_ANY_ROW, 0, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_set_cell_prop(table, FT_ANY_ROW, 1, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, 1, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    printf("%s\n", ft_to_string(table));

    ft_destroy_table(table);
}

int diff_double(double time1, double time2)
{
    if ((time1 - time2) < EPS && (time1 - time2) > -EPS)
        return 0;
    if (time1 - time2 < 0)
        return -1;
    return 1;
}

// выигрыш в процентах
double perc(double time_mat, double time_vec)
{
    if (diff_double(time_vec, 0) != 0)
        return time_mat * 100.00 / time_vec - 100.00;
    else if (diff_double(time_mat, 0) != 0)
        return -100.00;
    else
        return 0.0;
}

double calc_perc(struct Normal_mat *comb_mat, struct Normal_arr *comb_arr, struct Normal_arr *res_arr, struct Vector_mat *mat_mini, struct Vector_arr *arr_mini, struct Vector_arr *res_arr_mini,\
                 double *time_mat, double *time_vec, int j, long int *perc_mem_vec, long int *perc_mem_norm)
{
    double time_start;

    zero_all(comb_mat, comb_arr, res_arr, mat_mini, arr_mini, res_arr_mini);

    rand_input(comb_mat, comb_arr, j);
    matrix_to_vector(*comb_mat, mat_mini);
    array_to_vector(*comb_arr, arr_mini);
    time_start = clock();
    for (int i = 0; i < COUNT_SORT; i++)
    {
        // умножение нормальных матриц
        mult_mat(*comb_mat, *comb_arr, res_arr);
    }
    *time_mat = clock() - time_start;
    time_start = clock();
    for (int i = 0; i < COUNT_SORT; i++)
    {
        // умножение матриц в векторном виде
        mult_vec(*mat_mini, *arr_mini, res_arr_mini);
    }
    *time_vec = clock() - time_start;

    *time_mat /= COUNT_SORT;
    *time_vec /= COUNT_SORT;

    *perc_mem_norm = sizeof_mat(comb_mat) + sizeof_arr(comb_arr);
    *perc_mem_vec = sizeof_mat_vec(mat_mini) + sizeof_arr_vec(arr_mini);

    return perc(*time_mat, *time_vec);
}


