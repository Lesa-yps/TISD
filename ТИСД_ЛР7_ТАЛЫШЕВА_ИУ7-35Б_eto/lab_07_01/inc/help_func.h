#ifndef HELP_FUNC_H
#define HELP_FUNC_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "const_struct.h"

int clean_buf(void);

int diff_time(double time1, double time2);

long int is_simple(long int start);

int hash_func(int num, long int size);

#endif // HELP_FUNC_H
