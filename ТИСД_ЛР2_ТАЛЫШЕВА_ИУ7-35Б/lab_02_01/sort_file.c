#include "sort_file.h"

// функция сортировки данных в файле
void sort_file(wchar_t strk[], struct Book books[], struct Book_key book_keys[], int n)
{
    FILE *file;
    char mbs[MAX_LEN + 1];
    wcsrtombs(mbs, (const wchar_t **)&strk, sizeof(mbs), NULL);
    while ((file = fopen(mbs, "w")) == NULL)
    {
        printf("Ошибка открытия файла на запись. Пожалуйста, попробуйте ввести путь к файлу снова.\n");
        ask_file(strk, "w");
    }
    sort_simple_key(book_keys, n);
    sort_simple_book(books, n);
    for (int i = 0; i < n; i++)
        print_struct(books[i], file);
    fclose(file);
    printf("Файл отсортирован.\n");
}
