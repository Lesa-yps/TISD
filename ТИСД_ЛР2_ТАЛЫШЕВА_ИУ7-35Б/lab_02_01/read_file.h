#ifndef READ_ARR_H
#define READ_ARR_H

#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

#include "const_struct.h"

//функция читает файл
int read_file(wchar_t strk[], int *n, struct Book books[], struct Book_key book_keys[]);

//чтение целого числа
int read_int(FILE *file, int *list);

#endif // READ_ARR_H
