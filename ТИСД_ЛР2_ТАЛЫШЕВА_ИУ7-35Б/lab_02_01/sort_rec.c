#include "sort_rec.h"

void sort_rec_book(struct Book books[], int left, int right)
{
    if (left >= right)
        return;
    int size = right - left + 1;
    int pivot_index = left + (size / 2);
    int pivot_value = books[pivot_index].lists;
    int i = left;
    int j = right;
    while (i <= j)
    {
        while (books[i].lists < pivot_value)
            i++;
        while (books[j].lists > pivot_value)
            j--;
        if (i <= j)
        {
            swap(books, sizeof(books[0]), i, j);
            i++;
            j--;
        }
    }
    sort_rec_book(books, left, j);
    sort_rec_book(books, i, right);
}

void sort_rec_key(struct Book_key book_keys[], int low, int high)
{
    int i = low, j = high;
    int pivot = book_keys[(low + high) / 2].lists;
    do
    {
        while (book_keys[i].lists < pivot)
            i++;
        while (book_keys[j].lists > pivot)
            j--;
        if (i <= j)
        {
            swap(book_keys, sizeof(book_keys[0]), i, j);
            i++;
            j--;
        }
    } while (i <= j);
    if (low < j)
        sort_rec_key(book_keys, low, j);
    if (i < high)
        sort_rec_key(book_keys, i, high);
}
