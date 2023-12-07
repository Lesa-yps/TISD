#ifndef SIZEOF_H
#define SIZEOF_H

#include <stdio.h>
#include "const_struct.h"

long int sizeof_mat(struct Normal_mat *comb_mat);
long int sizeof_arr(struct Normal_arr *comb_arr);
long int sizeof_mat_vec(struct Vector_mat *vec_mat);
long int sizeof_arr_vec(struct Vector_arr *vec_arr);

#endif // SIZEOF_H
