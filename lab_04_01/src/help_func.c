#include "help_func.h"

void zero_inf_q(struct Inf_stack *inf_q1)
{
    inf_q1->len_q_max = 0;
    inf_q1->len_q_now = 0;
}

int diff_time(double time1, double time2)
{
    if ((time1 - time2) < EPS && (time1 - time2) > -EPS)
        return 0;
    if (time1 - time2 < 0)
        return -1;
    return 1;
}

void print_ptr(char *strk, int *num, int talk)
{
    if (talk)
        printf("   %s %p %d\n", strk, (void *) num, *num);
}

int clean_buf(void)
{
    char a = getchar();
    int count = 0;
    while (a != '\n' && a != EOF)
    {
        count++;
        a = getchar();
    }
    return count;
}

void read_int(int *num, int mini, int maxi)
{
    while (scanf("%d", num) != 1 || (clean_buf() != 0) || *num < mini || *num > maxi)
        printf("Ошибка ввода! Повторите ввод в диапазоне [%d; %d]: ", mini, maxi);
    printf("Успешно считано.\n");
}

int generate_random_int(int min, int max)
{
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}