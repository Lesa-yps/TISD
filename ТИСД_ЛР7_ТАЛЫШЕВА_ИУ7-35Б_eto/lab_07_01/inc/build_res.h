#ifndef BUILD_RES_H
#define BUILD_RES_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "fort.h"

#include "work_with_file.h"
#include "work_with_tree.h"
#include "work_with_bal_tree.h"
#include "work_with_ohash.h"
#include "work_with_chash.h"

#include "const_struct.h"
#include "help_func.h"

#define TEST_FILE_NAME "test.txt"

#define START_SIZE_HASH_BRES 1009

// Сравнивается эффективность поиска в зависимости от высоты деревьев и степени их ветвления
void build_res_find(void);

#endif // BUILD_RES_H
