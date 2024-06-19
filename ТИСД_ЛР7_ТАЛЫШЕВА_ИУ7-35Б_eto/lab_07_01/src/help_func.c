#include "help_func.h"

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

int diff_time(double time1, double time2)
{
    if ((time1 - time2) < EPS && (time1 - time2) > -EPS)
        return 0;
    if (time1 - time2 < 0)
        return -1;
    return 1;
}

int this_num_is_simple(long int num)
{
    for (long int i = 2; i <= (long int)sqrt(num) + 1; i++)
    {
        //printf("%ld %ld %ld\n", num, i, num % i);
        if (num % i == 0)
            return 0;
    }
    return 1;
}
long int is_simple(long int start)
{
    long int i = start + 1;
    while (this_num_is_simple(i) == 0)
        i++;
    return i;
}

int hash_func(int num, long int size)
{
    int res = (int) (((long int) abs(num)) % size);
    //printf("%d = %d mod %ld\n", res, num, size);
    return res;
}