#include "help_func.h"

double generate_random_double(double min, double max)
{
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

void zero_applic(struct Applic *app1, const double min_time_come, const double max_time_come, const double min_time_work, const double max_time_work)
{
    app1->time_come = generate_random_double(min_time_come, max_time_come);
    app1->time_work = generate_random_double(min_time_work, max_time_work);
    app1->count_work = 0;
}

void zero_inf_q(struct Inf_oueue *inf_q1)
{
    inf_q1->time_sim = 0;
    inf_q1->len_q_max = 0;
    inf_q1->len_q_now = 0;
    inf_q1->len_q_sum = 0;
    inf_q1->count_away_app = 0;
    inf_q1->count_change_q = 0;
    inf_q1->count_come_app = 0;
}

void zero_AO(struct AO *ao1)
{
    ao1->time_stay = 0;
    ao1->count_work = 0;
}

void zero_all(struct Inf_oueue *inf_q1, struct AO *ao1)
{
    zero_inf_q(inf_q1);
    zero_AO(ao1);
}

int diff_time(double time1, double time2)
{
    if ((time1 - time2) < EPS && (time1 - time2) > -EPS)
        return 0;
    if (time1 - time2 < 0)
        return -1;
    return 1;
}

void report_part_work(struct Inf_oueue inf_q1)
{
    printf("Текущая длина очереди = %d; средняя длина очереди = %.6f.\n", inf_q1.len_q_now, ((double) inf_q1.len_q_sum) / ((double) inf_q1.count_change_q));
}

// посчитает теоретическое время работы аппарата и погрешность по сравнению с практической
double err_time_work_AO(double min_time_come, double max_time_come, double min_time_work, double max_time_work, double *teor_time_work, double prac_time_work)
{
    double sr_time_come = min_time_come + (max_time_come - min_time_come) / 2;
    double sr_time_work = min_time_work + (max_time_work - min_time_work) / 2;
    //printf("work = %f come = %f\n", sr_time_work, sr_time_come);
    if (diff_time(sr_time_come, sr_time_work * MAX_COUNT_WORK1) > 0)
        *teor_time_work = sr_time_come * NEED_COUNT_AWAY_APP;
    else
        *teor_time_work = sr_time_work * MAX_COUNT_WORK1 * NEED_COUNT_AWAY_APP;
    if (diff_time(prac_time_work, 0) != 0)
        return fabs(*teor_time_work * 100.0 / prac_time_work - 100.0);
    else if (diff_time(*teor_time_work, 0) != 0)
        return fabs(prac_time_work * 100.0 / *teor_time_work - 100.0);
    else
        return 0;
}

// общее время моделирования и количестве вошедших в систему и вышедших из нее заявок,
// количестве срабатываний ОА, время простоя аппарата, время работы апарата
void report_all_work(struct AO ao1, struct Inf_oueue inf_q1, double min_time_come, double max_time_come, double min_time_work, double max_time_work)
{
    double teor_time_work;
    double err = err_time_work_AO(min_time_come, max_time_come, min_time_work, max_time_work, &teor_time_work, inf_q1.time_sim);
    printf("Результат:\n\
время работы аппарата = %.6f е.в.\n\
количество вошедших в систему заявок = %d\n\
количество вышедших из системы заявок = %d\n\
количествo срабатываний ОА = %d\n\
время простоя аппарата = %.6f е.в.\n\
практическое время моделирования = %.6f е.в.\n\
теоретическое время моделирования = %.6f е.в.\n\
погрешность = %.6f%%\n", inf_q1.time_sim - ao1.time_stay, inf_q1.count_come_app, inf_q1.count_away_app, \
            ao1.count_work, ao1.time_stay, inf_q1.time_sim, teor_time_work, err);
}

void print_ptr(char *strk, struct Applic *app1, int talk)
{
    if (talk)
        printf("   %s %p\n", strk, (void *) app1);
}

int hat_for_get(double *time_come_app, struct Applic **app_come, const double min_time_come,\
             const double max_time_come, const double min_time_work, const double max_time_work)
{
    int block = OK;
    *app_come = calloc(1, sizeof(struct Applic));
    if ((*app_come) != NULL)
    {
        zero_applic(*app_come, min_time_come, max_time_come, min_time_work, max_time_work);
        *time_come_app = (*app_come)->time_come;
    }
    else
    {
        block = ERROR;
        printf("Ошибка выделения памяти!\n");
    }
    return block;
}