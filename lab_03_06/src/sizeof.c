#include "sizeof.h"

long int sizeof_mat(struct Normal_mat *comb_mat)
{
    return (comb_mat->m * comb_mat->n + 2) * sizeof(int);
}

long int sizeof_arr(struct Normal_arr *comb_arr)
{
    return (comb_arr->n + 1) * sizeof(int);
}

long int sizeof_mat_vec(struct Vector_mat *vec_mat)
{
    //printf("%d %d\n", vec_mat->count_col, vec_mat->count_elems);
    return (vec_mat->count_col + vec_mat->count_elems * 2 + 2) * sizeof(int);
}

long int sizeof_arr_vec(struct Vector_arr *vec_arr)
{
    return (vec_arr->count_elems * 2 + 1) * sizeof(int);
}
