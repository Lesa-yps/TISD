#include <stdio.h>

// модули
#include "const_struct.h"

#include "read_matrix.h"
#include "print_matrix.h"
#include "print_arr.h"
#include "mult.h"
#include "build_res.h"
#include "vec_create_free.h"

//интерфейс
int main(void)
{
    //код возврата
    int rc = OK;
    // массив
    struct Normal_arr array;
    struct Vector_arr array_mini;
    struct Normal_arr arr_res;
    struct Vector_arr arr_res_mini;
    // матрицы
    struct Normal_mat matrix;
    struct Vector_mat matrix_mini;
    //приветствие + условие задачи
    printf("   Приветствую, пользователь!\n\
Программа умножает вектора-строки хранящегося в форме вектора A и вектора, содержащего номера столбцов этих элементов,\n\
и матрицы, хранящейся в указанной форме, с получением результата в форме хранения вектора-строки. Затем производит операцию умножения,\n\
применяя стандартный алгоритм работы с матрицами. Cравнивается время выполнения операций и объем памяти при использовании\n\
этих 2-х алгоритмов при различном проценте заполнения матриц.\n");
    // выделение памяти и проверка выделения, заполнение матриц
    rc = read_matrix(&matrix, &matrix_mini, &array, &array_mini);
    if (rc == ERROR_MEM || create_vec_arr(&arr_res_mini, array_mini.count_elems) == ERROR_MEM || (arr_res.arr = calloc(array.n, sizeof(int))) == NULL)
    {
        free_vec_arr(&arr_res_mini);
        free(arr_res.arr);
        printf("Ошибка выделения памяти.\n");
    }
    else
    {
        // вывод прочитанных матриц
        printf("\nВывод прочитанного массива:\n");
        print_arr(array, array_mini);
        printf("\nВывод прочитанной матрицы:\n");
        print_matrix(matrix, matrix_mini);
        printf("Вывод произведения матриц:\n");
        // умножение матриц-векторов
        mult_vec(matrix_mini, array_mini, &arr_res_mini);
        // умножение нормальных матриц
        mult_mat(matrix, array, &arr_res);
        // вывод произведения матриц
        print_arr(arr_res, arr_res_mini);
        // замеры времени и памяти разных сортировок при разном проценте заполнения
        build_res(&matrix, &array, &arr_res, &matrix_mini, &array_mini, &arr_res_mini);
        // освобождение всего выделенного
        free_all(&matrix, &array, &arr_res, &matrix_mini, &array_mini, &arr_res_mini);
    }

    //возврат кода ошибки
    return rc;
}
