#ifndef BUILD_RES_H
#define BUILD_RES_H

#include <stdio.h>
#include <time.h>
#include "fort.h"
#include <string.h>

#include "const_struct.h"
#include "mult.h"
#include "read_matrix.h"
#include "sizeof.h"

// функция вычисляет время работы и оптимальную разряженность для использования векторного метода
void build_res(struct Normal_mat *comb_mat, struct Normal_arr *comb_arr, struct Normal_arr *res_arr, struct Vector_mat *mat_mini, struct Vector_arr *arr_mini, struct Vector_arr *res_arr_mini);

#endif // BUILD_RES_H
