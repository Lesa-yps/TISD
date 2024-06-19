#ifndef DEL_STRUCT_H
#define DEL_STRUCT_H

#include <stdio.h>
#include <wchar.h>
#include "fort.h"

#include "const_struct.h"
#include "asc_file.h"
#include "clean_buf.h"
#include "print_struct.h"
#include "read_struct.h"
#include "print_table_struct.h"

int del_struct(wchar_t strk[], struct Book books[], struct Book_key book_keys[], int *n);

#endif // DEL_STRUCT_H
