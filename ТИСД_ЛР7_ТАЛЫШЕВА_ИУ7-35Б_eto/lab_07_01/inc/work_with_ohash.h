#ifndef WORK_WITH_OHASH_H
#define WORK_WITH_OHASH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "const_struct.h"
#include "help_func.h"
#include "fort.h"

// Структура - хэш-таблица с внутренним хэшированием
struct Hash_open
{
    int **data; // данные
    long int size;   // размер хэш-таблицы
};

int ohash_from_file(struct Hash_open **Table, FILE *file);

void ohash_print(struct Hash_open *Table, char *file_name);

struct Hash_open *ohash_add_elem(struct Hash_open *Table, int num, int res);

struct Hash_open *ohash_del_elem(struct Hash_open *Table, int num);

int *ohash_find_elem(struct Hash_open *Table, int num, int *count, int talk);

int ohash_resize(struct Hash_open **Table);

int ohash_create(long int tsize, struct Hash_open **Table);
int *ohash_node_create(int num);

void ohash_free(struct Hash_open **Table);
void ohash_node_free(int **elem);

double ohash_count_average_find(struct Hash_open *Table, FILE *file);

#endif // WORK_WITH_OHASH_H