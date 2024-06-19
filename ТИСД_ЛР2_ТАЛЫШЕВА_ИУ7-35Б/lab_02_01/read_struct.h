#ifndef ADD_FILE_H
#define ADD_FILE_H

#include <stdio.h>
#include <wchar.h>
#include <string.h>

#include "const_struct.h"
#include "clean_buf.h"
#include "read_file.h"
#include "print_struct.h"

void read_struct(struct Book books[], struct Book_key book_keys[], int *n);

void read_str(wchar_t strk[], int maxi);

#endif // ADD_FILE_H
