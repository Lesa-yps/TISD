#include "mult.h"

// суммирует произведения элементов строки на столбец
int multi_sum(int arr[], int *mat, int j, int m_mat, int n);

// умножает матрицы по-человечески
void mult_mat(struct Normal_mat comb_mat, struct Normal_arr comb_arr, struct Normal_arr *comb_res)
{
    comb_res->n = comb_mat.m;
    // прошлись по столбцам первой марицы
    for (int i = 0; i < comb_mat.m; i++)
        // перемножили массив на столбец
        comb_res->arr[i] = multi_sum(comb_arr.arr, comb_mat.mat, i, comb_mat.m, comb_arr.n);
}

// умножает массив на матрицу в векторном виде
void mult_vec(struct Vector_mat vec_mat, struct Vector_arr vec_arr, struct Vector_arr *res)
{
    //printf("м_мат = %d кол-во элементов мат = %d кол-во элементов арр = %d\n", vec_mat.count_col, vec_mat.count_elems, vec_arr.count_elems);
    // результат умножения строки на столбец
    int res_mult;
    // где строка матрицы
    int sup_col1 = 0, inf_col1;
    // пока элементов нет
    res->count_elems = 0;
    int j_sup = 0;
    int col1 = 0;
    // прошлись по столбцам матрицы
    while (col1 < vec_mat.count_col)
    {
        //printf("col1 = %d j_sup = %d\n", col1, j_sup);
        sup_col1 = -1;
        // нашли начало и конец столбца
        inf_col1 = vec_mat.ind_elems_col[col1];
        if (inf_col1 == MY_NULL)
        {
            col1++;
            continue;
        }
        j_sup = col1 + 1;
        for (;(j_sup < vec_mat.count_elems); j_sup++)
        {
            //printf("j_sup = %d\n", j_sup);
            if (vec_mat.ind_elems_col[j_sup] != MY_NULL)
            {
                sup_col1 = vec_mat.ind_elems_col[j_sup];
                break;
            }
        }
        if (sup_col1 == -1)
            sup_col1 = vec_mat.count_elems;
        //printf("столбец от = %d до = %d\n", inf_col1, sup_col1);
        // перемножили строку на столбец
        res_mult = 0;
        for (int str1 = inf_col1; str1 < sup_col1; str1++)
            for (int str2 = 0; str2 < vec_arr.count_elems; str2++)
            {
                if (vec_arr.num_str[str2] == vec_mat.num_str[str1])
                {
                    res_mult += vec_mat.elems[str1] * vec_arr.elems[str2];
                    //printf("произведение = %d элементы = %d * %d индекс строки мат = %d индекс строки массива = %d\n", res_mult, vec_mat.elems[str1], vec_mat.elems[str2], vec_mat.num_str[str1], vec_arr.num_str[str2]);
                    break;
                }
            }
        if (res_mult != 0)
        {
            res->elems[res->count_elems] = res_mult;
            res->num_str[res->count_elems] = col1;
            res->count_elems++;
        }
        col1 = j_sup;
    }
}

// суммирует произведения элементов строки на столбец
int multi_sum(int arr[], int *mat, int j, int m_mat, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i] * mat[i * m_mat + j];
    return sum;
}
