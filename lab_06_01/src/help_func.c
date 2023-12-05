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