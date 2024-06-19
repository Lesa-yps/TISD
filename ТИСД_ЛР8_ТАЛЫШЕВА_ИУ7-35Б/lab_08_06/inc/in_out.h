#ifndef IN_OUT_H
#define IN_OUT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "const.h"

// читает ребра из файла и записывает в матрицу смежностей
int read_matrix(FILE *file, int ***matrix, int *n);

// считали граф как матрицу смежностей
int input_graph(int ***matrix, int *n);

// вывели граф красиво
void output_graph(int **matrix, int n, char *name_file);

// освобождение памяти из-под матрицы
void free_matrix(int ***matrix, int n);

#endif // IN_OUT_H