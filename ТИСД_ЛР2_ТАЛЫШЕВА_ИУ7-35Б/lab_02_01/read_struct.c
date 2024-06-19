#include "read_struct.h"

void read_str(wchar_t strk[], int maxi);

void read_struct(struct Book books[], struct Book_key book_keys[], int *n)
{
    int rc;
    printf("Введите фамилию автора книги (кол-во символов [1; %d]): ", MAX_LEN);
    read_str((books[*n]).surname, MAX_LEN);
    printf("Введите название книги (кол-во символов [1; %d]): ", MAX_LEN);
    read_str((books[*n]).name_book, MAX_LEN);
    printf("Введите издателя книги (кол-во символов [1; %d]): ", MAX_LEN);
    read_str((books[*n]).mader, MAX_LEN);
    printf("Введите количество страниц в книге [1; %d]: ", MAX_LISTS);
    while (((rc = read_int(stdin, &(books[*n]).lists)) != OK) || (books[*n]).lists < 1 || (books[*n]).lists > MAX_LISTS)
        printf("Ошибка ввода количества страниц. Попробуйте ввести снова [1; %d]: ", MAX_LISTS);
    printf("Введите вид литературы (1 - техническая, 2 - художественная, 3 - детская): ");
    while (((read_int(stdin, &(books[*n]).variant)) != OK)|| (books[*n]).variant < 1 || (books[*n]).variant > 3)
        printf("Ошибка ввода вида литературы. Попробуйте ввести снова (1/2/3): ");
    if ((books[*n]).variant == 1)
    {
        printf("Введите отрасль книги (кол-во символов [1; %d]): ", MAX_LEN);
        read_str((books[*n]).unic.texnic.otrasl, MAX_LEN);
        printf("Введите 'отечественная'/'переводная' книга: ");
        read_str((books[*n]).unic.texnic.where, strlen("отечественная"));
        while (wcscmp((books[*n]).unic.texnic.where, L"отечественная") * wcscmp((books[*n]).unic.texnic.where, L"переводная") != 0)
        {
            printf("Ошибка ввода. Попробуйте ввести снова ('отечественная'/'переводная'): ");
            read_str((books[*n]).unic.texnic.where, strlen("отечественная"));
        }
        printf("Введите год издания [0; %d]: ", MAX_YEAR);
        while ((read_int(stdin, &((books[*n]).unic.texnic.year)) != OK) || (books[*n]).unic.texnic.year < 0 || (books[*n]).unic.texnic.year > MAX_YEAR)
            printf("Ошибка ввода года издания. Попробуйте ввести снова [0; %d]: ", MAX_YEAR);
    }
    else if ((books[*n]).variant == 2)
    {
        printf("Введите 'роман'/'пьеса'/'поэзия': ");
        read_str((books[*n]).unic.draw, strlen("поэзия"));
        while (wcscmp((books[*n]).unic.draw, L"поэзия") != 0 && wcscmp((books[*n]).unic.draw, L"пьеса") != 0 && wcscmp((books[*n]).unic.draw, L"роман") != 0)
        {
            printf("Ошибка ввода. Попробуйте ввести снова ('роман'/'пьеса'/'поэзия'): ");
            read_str((books[*n]).unic.draw, strlen("поэзия"));
        }
    }
    else
    {
        printf("Введите минимальный возраст [0; %d]: ", MAX_CHILD_AGE);
        while ((read_int(stdin, &((books[*n]).unic.child.min_year)) != OK) || (books[*n]).unic.child.min_year < 0 || (books[*n]).unic.child.min_year > MAX_CHILD_AGE)
            printf("Ошибка ввода минимального возраста. Попробуйте ввести снова [0; %d]: ", MAX_CHILD_AGE);
        printf("Введите 'сказки'/'стихи': ");
        read_str((books[*n]).unic.child.what, strlen("сказки"));
        while (wcscmp((books[*n]).unic.child.what, L"сказки") != 0 && wcscmp((books[*n]).unic.child.what, L"стихи") != 0)
        {
            printf("Ошибка ввода. Попробуйте ввести снова ('сказки'/'стихи'): ");
            read_str((books[*n]).unic.child.what, strlen("сказки"));
        }
    }
    (book_keys[*n]).start_ind = *n;
    (book_keys[*n]).lists = (books[*n]).lists;
    (*n)++;
}

void read_str(wchar_t strk[], int maxi)
{
    while ((fgetws(strk, maxi + 1, stdin) == NULL) || (strk[0] == L'\n') || (strk[wcslen(strk) - 1] != L'\n'))
    {
        printf("Ошибка ввода. Попробуйте ввести снова: ");
        if (strk[wcslen(strk) - 1] != L'\n')
            clean_buf();
    }
    strk[wcslen(strk) - 1] = '\0';
}
