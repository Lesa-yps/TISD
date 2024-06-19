#include "sort_simple.h"

// сортировка полной таблицы выбором
void sort_simple_book(struct Book books[], int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int max_ind = 0;
        for (int j = 0; j <= i; j++)
        {
            if (books[j].lists > books[max_ind].lists)
                max_ind = j;
        }
        swap(books, sizeof(books[0]), i, max_ind);
    }
}

// сортировка таблицы ключей выбором
void sort_simple_key(struct Book_key book_keys[], int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int max_ind = 0;
        for (int j = 0; j <= i; j++)
        {
            if (book_keys[j].lists > book_keys[max_ind].lists)
                max_ind = j;
        }
        swap(book_keys, sizeof(book_keys[0]), i, max_ind);
    }
}
