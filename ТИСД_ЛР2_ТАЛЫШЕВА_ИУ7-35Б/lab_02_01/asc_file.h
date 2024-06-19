#ifndef ASC_FILE_H
#define ASC_FILE_H

#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>

#include "const_struct.h"

//пока не прочитает нормальный файл, будет просить ввести
void ask_file(wchar_t strk[], char mode[]);

#endif // ASC_FILE_H
