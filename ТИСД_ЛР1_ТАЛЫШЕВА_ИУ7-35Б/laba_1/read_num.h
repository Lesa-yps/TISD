#ifndef READ_NUM_H
#define READ_NUM_H

#include <stdio.h>
#include <ctype.h>

#include "const_struct.h"

//функция чтения числа
void read_num(struct number *sth, int MAX_MAN);

//функция чистит буфер
void clean_buf(void);

#endif // READ_NUM_H
