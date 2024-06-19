#include "swap.h"

void swap(void *pbeg, int size, int i, int j)
{
    char *new_pbeg = pbeg;
    char x;
    for (int k = 0; k < size; k++)
    {
        x = *(new_pbeg + i * size + k);
        *(new_pbeg + i * size + k) = *(new_pbeg + j * size + k);
        *(new_pbeg + j * size + k) = x;
    }
}
