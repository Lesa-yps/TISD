#ifndef SORT_FILE_H
#define SORT_FILE_H

#include <stdio.h>
#include <wchar.h>

#include "const_struct.h"
#include "asc_file.h"
#include "sort_simple.h"
#include "print_struct.h"

// функция сортировки данных в файле
void sort_file(wchar_t strk[], struct Book books[], struct Book_key book_keys[], int n);

#endif // SORT_FILE_H
