#ifndef CONST_STRUCT_H
#define CONST_STRUCT_H

//коды возврата
#define OK 0
#define ERROR 1
// максимальная размерность
#define MAX_N 1000
// максимальная размерность, когда программа предлагает вывести матрицу/массив в обычном виде
#define MAX_PRINT 30
// количество сравнений
#define COUNT_SORT 10
// размер вспомогательного буфера
#define SIZE_OF_BUF 100
// "этот столбец содержит только нули"
#define MY_NULL -1
// ограничение для рандомайзера
#define MAX_RAND 10
// код ошибки при ошибках памяти
#define ERROR_MEM 3
// эпсилон
#define EPS 0.00001

// специализированный вид матрицы
struct Vector_mat
{
    int *elems;
    int *num_str;
    int *ind_elems_col;
    int count_col;
    int count_elems;
};
// обычное представление матрицы
struct Normal_mat
{
    int *mat;
    int n;
    int m;
};

// специализированный вид массива

struct Vector_arr
{
    int *elems;
    int *num_str;
    int count_elems;
};
// обычное представление массива
struct Normal_arr
{
    int *arr;
    int n;
};

#endif // CONST_STRUCT_H
