#ifndef WORK_WITH_CHASH_H
#define WORK_WITH_CHASH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fort.h"

#include "const_struct.h"
#include "help_func.h"

// Структура - элемент хэш-таблицы
struct Node_chash
{
    int data; // Данные
    struct Node_chash *next;   // Указатель на следующий элемент
};

// Структура - хэш-таблица с внешним хэшированием
struct Hash_close
{
    struct Node_chash **data; // массив указателей на данные
    long int size;   // размер хэш-таблицы
};

int chash_from_file(struct Hash_close **Table, FILE *file);

void chash_node_print(struct Node_chash *elem, char *strk);
void chash_print(struct Hash_close *Table, char *name_file);

struct Hash_close *chash_add_elem(struct Hash_close *Table, int num, int res);

struct Hash_close *chash_del_elem(struct Hash_close *Table, int num);

int *chash_find_elem(struct Hash_close *Table, int num, int *count, int talk);

int chash_resize(struct Hash_close **Table);

struct Node_chash *chash_node_create(int num);
int chash_create(long int tsize, struct Hash_close **Table);

void chash_free(struct Hash_close **Table);
void chash_node_free(struct Node_chash **elem);

double chash_count_average_find(struct Hash_close *Table, FILE *file);

#endif // WORK_WITH_CHASH_H