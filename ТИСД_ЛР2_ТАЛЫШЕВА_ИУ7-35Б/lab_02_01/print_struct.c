#include "print_struct.h"

void print_struct(struct Book book, FILE *file)
{
    fprintf(file, "%ls\n%ls\n%ls\n%d\n%d\n", book.surname, book.name_book, book.mader, book.lists, book.variant);
    if (book.variant == 1)
        fprintf(file, "%ls\n%ls\n%d\n", book.unic.texnic.otrasl, book.unic.texnic.where, book.unic.texnic.year);
    else if (book.variant == 2)
        fprintf(file, "%ls\n", book.unic.draw);
    else
        fprintf(file, "%d\n%ls\n", book.unic.child.min_year, book.unic.child.what);
}
