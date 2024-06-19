#ifndef VEC_ARR_CREATE_FREE_H
#define VEC_ARR_CREATE_FREE_H

#include <stdlib.h>

#include "const_struct.h"

int create_vec_arr(struct Vector_arr *res, int n);
void free_vec_arr(struct Vector_arr *res);
int create_vec_mat(struct Vector_mat *res, int n, int m);
void free_vec_mat(struct Vector_mat *res);


void zero_mat(struct Normal_mat *mat);
void zero_mat_vec(struct Vector_mat *vec);
void zero_arr(struct Normal_arr *arr);
void zero_arr_vec(struct Vector_arr *vec);

void zero_all(struct Normal_mat *comb_mat, struct Normal_arr *comb_arr, struct Normal_arr *res_arr, struct Vector_mat *mat_mini, struct Vector_arr *arr_mini, struct Vector_arr *res_arr_mini);

void free_all(struct Normal_mat *comb_mat, struct Normal_arr *comb_arr, struct Normal_arr *res_arr, struct Vector_mat *mat_mini, struct Vector_arr *arr_mini, struct Vector_arr *res_arr_mini);

#endif // VEC_ARR_CREATE_FREE_H
