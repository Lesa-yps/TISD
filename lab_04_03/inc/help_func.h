#ifndef HELP_FUNC_H
#define HELP_FUNC_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "const_struct.h"

void zero_inf_q(struct Inf_stack *inf_q1);

int diff_time(double time1, double time2);

void print_del_add(struct Del_adresses del_adress);

void read_int(int *num, int mini, int maxi);
int clean_buf(void);

int generate_random_int(int min, int max);

void print_rev_str(char *strk);

#endif // HELP_FUNC_H
