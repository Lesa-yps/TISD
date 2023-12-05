#include "vec_create_free.h"

int create_vec_arr(struct Vector_arr *res, int n)
{
    res->elems = calloc(n, sizeof(int));
    res->num_str = calloc(n, sizeof(int));
    res->count_elems = 0;
    if (res->elems == NULL || res->num_str == NULL)
        return ERROR_MEM;
    return OK;
}

void free_vec_arr(struct Vector_arr *res)
{
    free(res->elems);
    free(res->num_str);
}

int create_vec_mat(struct Vector_mat *res, int n, int m)
{
    res->count_elems = 0;
    res->count_col = m;
    res->elems = calloc(n * m, sizeof(int));
    res->num_str = calloc(n * m, sizeof(int));
    res->ind_elems_col = calloc(res->count_col, sizeof(int));
    if (res->elems == NULL || res->num_str == NULL || res->ind_elems_col == NULL)
        return ERROR_MEM;
    return OK;
}

void free_vec_mat(struct Vector_mat *res)
{
    free(res->elems);
    free(res->num_str);
    free(res->ind_elems_col);
}

void zero_mat(struct Normal_mat *mat)
{
    for (int i = 0; i < (mat->n * mat->m); i++)
        mat->mat[i] = 0;
    //mat->n = 0;
    //mat->m = 0;
}

void zero_mat_vec(struct Vector_mat *vec)
{
    for (int i = 0; i < vec->count_elems; i++)
    {
        vec->elems[i] = 0;
        vec->num_str[i] = 0;
    }
    for (int i = 0; i < vec->count_col; i++)
        vec->ind_elems_col[i] = 0;
    //vec->count_elems = 0;
    //vec->count_col = 0;
}

void zero_arr(struct Normal_arr *arr)
{
    for (int i = 0; i < arr->n; i++)
        arr->arr[i] = 0;
    //arr->n = 0;
}

void zero_arr_vec(struct Vector_arr *vec)
{
    for (int i = 0; i < vec->count_elems; i++)
    {
        vec->elems[i] = 0;
        vec->num_str[i] = 0;
    }
    //vec->count_elems = 0;
}

void zero_all(struct Normal_mat *comb_mat, struct Normal_arr *comb_arr, struct Normal_arr *res_arr, struct Vector_mat *mat_mini, struct Vector_arr *arr_mini, struct Vector_arr *res_arr_mini)
{
    zero_mat(comb_mat);
    zero_arr(comb_arr);
    zero_arr(res_arr);
    zero_mat_vec(mat_mini);
    zero_arr_vec(arr_mini);
    zero_arr_vec(res_arr_mini);
}

void free_all(struct Normal_mat *comb_mat, struct Normal_arr *comb_arr, struct Normal_arr *res_arr, struct Vector_mat *mat_mini, struct Vector_arr *arr_mini, struct Vector_arr *res_arr_mini)
{
    free_vec_mat(mat_mini);
    free(comb_arr->arr);
    free_vec_arr(arr_mini);
    free(comb_mat->mat);
    free_vec_arr(res_arr_mini);
    free(res_arr->arr);
}
