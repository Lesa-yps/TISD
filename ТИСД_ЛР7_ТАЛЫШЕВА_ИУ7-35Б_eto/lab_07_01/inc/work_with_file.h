#ifndef WORK_WITH_FILE_H
#define WORK_WITH_FILE_H

#include <stdio.h>
#include <string.h>

#include "const_struct.h"
#include "help_func.h"

void file_whoose(FILE **file);

void file_add_elem(FILE *file, int num);

#endif // WORK_WITH_FILE_H