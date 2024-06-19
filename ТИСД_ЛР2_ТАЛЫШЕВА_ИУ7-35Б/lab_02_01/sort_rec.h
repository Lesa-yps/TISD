#ifndef SORT_REC_H
#define SORT_REC_H

#include "const_struct.h"
#include "swap.h"

void sort_rec_book(struct Book books[], int left, int right);

void sort_rec_key(struct Book_key book_keys[], int low, int high);

#endif // SORT_REC_H
