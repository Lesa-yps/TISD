#ifndef CONST_STRUCT_H
#define CONST_STRUCT_H

//коды возврата
#define OK 0
#define ERROR 1

#define MAX_N 1000

#define MAX_PRINT 30

#define COUNT_SORT 10

#define SIZE_OF_BUF 100

#define MY_NULL -1

#define MAX_RAND 10

#define ERROR_MEM 3

// матрица

struct Vector_mat
{
    int *elems;
    int *num_str;
    int *ind_elems_col;
    int count_col;
    int count_elems;
};

struct Normal_mat
{
    int *mat;
    int n;
    int m;
};

// массив

struct Vector_arr
{
    int *elems;
    int *num_str;
    int count_elems;
};

struct Normal_arr
{
    int *arr;
    int n;
};

#endif // CONST_STRUCT_H
