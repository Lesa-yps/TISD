#ifndef BUILD_RES_H
#define BUILD_RES_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "fort.h"

#include "work_with_file.h"
#include "work_with_tree.h"

#include "const_struct.h"

#define MIN_X -10
#define MAX_X 10

#define TEST_FILE_NAME "test.txt"

#define MIN_X_ADD -1024
#define MAX_X_ADD 1024

#define SIZE_OF_BUF 100

// Сравнивается эффективность алгоритмов добавления чисел в файл и в дерево
int build_res_add(void);
// Сравнивается эффективность поиска в зависимости от высоты деревьев и степени их ветвления
void build_res_find(void);

#endif // BUILD_RES_H
