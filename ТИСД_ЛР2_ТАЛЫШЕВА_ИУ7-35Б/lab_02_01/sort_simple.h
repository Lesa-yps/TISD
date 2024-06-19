#ifndef SORT_SIMPLE_H
#define SORT_SIMPLE_H

#include "const_struct.h"
#include "swap.h"

// сортировка полной таблицы выбором
void sort_simple_book(struct Book books[], int n);

// сортировка таблицы ключей выбором
void sort_simple_key(struct Book_key book_keys[], int n);

#endif // SORT_SIMPLE_H
