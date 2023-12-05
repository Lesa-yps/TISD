#include "print_arr.h"

// выведет массив в обычном виде
void output_arr(struct Normal_arr comb_arr);
// выведет массив в виде нескольких векторов
void output_vec_arr(struct Vector_arr comb_vec);

// выведет массив
void print_arr(struct Normal_arr comb_arr, struct Vector_arr comb_vec)
{
    int x;
    if (comb_arr.n > MAX_PRINT)
    {
        printf("*Примечание: так как размерность массива больше %d, программа выводит только векторный вид.\n", MAX_PRINT);
        output_vec_arr(comb_vec);
    }
    else
    {
        printf("Введите 1, если хотите вывести в обычном виде, 2, если в векторном, или 3, если в обоих: ");
        x = read_int(1, 3);
        if (x == 1)
            output_arr(comb_arr);
        else if (x == 2)
            output_vec_arr(comb_vec);
        else
        {
            output_arr(comb_arr);
            output_vec_arr(comb_vec);
        }
    }
}

// выведет массив в обычном виде
void output_arr(struct Normal_arr comb_arr)
{
    printf("\nРезультат в нормальном виде:\n");
    for (int i = 0; i < comb_arr.n; i++)
        printf("%-3d", comb_arr.arr[i]);
}
// выведет массив в виде нескольких векторов
void output_vec_arr(struct Vector_arr comb_vec)
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
    printf("\n");
}
