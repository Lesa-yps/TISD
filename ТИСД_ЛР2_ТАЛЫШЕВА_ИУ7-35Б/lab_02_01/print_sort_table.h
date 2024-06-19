#ifndef PRINT_SORT_TABLE_H
#define PRINT_SORT_TABLE_H

#include <stdio.h>
#include "fort.h"

#include "const_struct.h"
#include "sort_simple.h"
#include "print_table_struct.h"

void print_sort_table(struct Book books[], struct Book_key book_keys[], int n, int sort);

#endif // PRINT_SORT_TABLE_H
