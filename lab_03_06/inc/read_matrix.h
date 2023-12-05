#ifndef READ_MATRIX_H
#define READ_MATRIX_H

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "const_struct.h"
#include "vec_create_free.h"

// чтение и создание матриц
int read_matrix(struct Normal_mat *comb_arr1, struct Vector_mat *comb_vec1, struct Normal_arr *comb_arr2, struct Vector_arr *comb_vec2);

// функция читает целое число из диапазона
int read_int(int minik, int maxik);

// метод процентного заполнения матрицы
void rand_input(struct Normal_mat *name_struct1, struct Normal_arr *name_arr1, int user);

#endif // READ_MATRIX_H
