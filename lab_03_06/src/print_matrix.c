#include "print_matrix.h"

// выведет матрицу в обычном виде
void output_mat(struct Normal_mat comb_mat);
// выведет матрицу в виде нескольких векторов
void output_vec_mat(struct Vector_mat comb_vec);

// выведет матрицу
void print_matrix(struct Normal_mat comb_mat, struct Vector_mat comb_vec)
{
    int x;
    if (comb_mat.m > MAX_PRINT || comb_mat.n > MAX_PRINT)
    {
        printf("*Примечание: так как размерность матрицы больше %d, программа выводит только векторный вид.\n", MAX_PRINT);
        output_vec_mat(comb_vec);
    }
    else
    {
        printf("Введите 1, если хотите вывести в обычном виде, 2, если в векторном, или 3, если в обоих: ");
        x = read_int(1, 3);
        if (x == 1)
            output_mat(comb_mat);
        else if (x == 2)
            output_vec_mat(comb_vec);
        else
        {
            output_mat(comb_mat);
            output_vec_mat(comb_vec);
        }
    }
}

// выведет матрицу в обычном виде
void output_mat(struct Normal_mat comb_mat)
{
    printf("\nРезультат в матричном виде:\n");
    for (int i = 0; i < comb_mat.n; i++)
    {
        for (int j = 0; j < comb_mat.m; j++)
            printf("%-3d", comb_mat.mat[i * comb_mat.m + j]);
        printf("\n");
    }
}
// выведет матрицу в виде нескольких векторов
void output_vec_mat(struct Vector_mat comb_vec)
{
    printf("\nРезультат в векторном виде:\n");
    printf("Вектор ненулевых элементов:\n");
    for (int i = 0; i < comb_vec.count_elems; i++)
        printf("%-3d ", comb_vec.elems[i]);
    if (comb_vec.count_elems == 0)
        printf("Пусто.");
    printf("\nВектор индексов строк элементов:\n");
    for (int i = 0; i < comb_vec.count_elems; i++)
        printf("%-3d ", comb_vec.num_str[i]);
    if (comb_vec.count_elems == 0)
        printf("Пусто.");
    printf("\nВектор первых элементов в столбцах:\n");
    for (int j = 0; j < comb_vec.count_col; j++)
        printf("%-3d ", comb_vec.ind_elems_col[j]);
    if (comb_vec.count_col == 0)
        printf("Пусто.");
    printf("\n");
}
