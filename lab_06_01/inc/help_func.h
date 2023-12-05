#ifndef HELP_FUNC_H
#define HELP_FUNC_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "const_struct.h"

void zero_applic(struct Applic *app1, const double min_time_come, const double max_time_come, const double min_time_work, const double max_time_work);
void zero_inf_q(struct Inf_oueue *inf_q1);
void zero_AO(struct AO *ao1);
void zero_all(struct Inf_oueue *inf_q1, struct AO *ao1);

int diff_time(double time1, double time2);

void report_part_work(struct Inf_oueue inf_q1);
void report_all_work(struct AO ao1, struct Inf_oueue inf_q1, double min_time_come, double max_time_come, double min_time_work, double max_time_work);
// посчитает теоретическое время работы аппарата и погрешность по сравнению с практической
double err_time_work_AO(double min_time_come, double max_time_come, double min_time_work, double max_time_work, double *teor_time_work, double prac_time_work);

void print_ptr(char *strk, struct Applic *app1, int talk);

int hat_for_get(double *time_come_app, struct Applic **app_come, const double min_time_come,\
             const double max_time_come, const double min_time_work, const double max_time_work);

#endif // HELP_FUNC_H
