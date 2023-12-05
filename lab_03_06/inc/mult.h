#ifndef MULT_H
#define MULT_H

#include <stdio.h>

#include "const_struct.h"

// умножает матрицы по-человечески
void mult_mat(struct Normal_mat comb_mat, struct Normal_arr comb_arr, struct Normal_arr *comb_res);

// умножает матрицы в векторном виде
void mult_vec(struct Vector_mat vec_mat, struct Vector_arr vec_arr, struct Vector_arr *res);

#endif // MULT_H
