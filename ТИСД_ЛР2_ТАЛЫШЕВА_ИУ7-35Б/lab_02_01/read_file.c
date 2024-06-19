#include "read_file.h"

//чтение года
int read_int(FILE *file, int *list);
//чтение строки
int read_str_file(wchar_t *str, FILE *file);
//вариантная часть
int read_variant(FILE *file, struct Book *book);

//функция читает информацию из файла
int read_file(wchar_t strk[], int *n, struct Book books[], struct Book_key book_keys[])
{
    FILE *file;
    char mbs[MAX_LEN + 1];
    int rc = OK;
    int rc_func;
    int finish = 0;
    struct Book one;
    //количество структур
    *n = 0;
    wcsrtombs(mbs, (const wchar_t **)&strk, sizeof(mbs), NULL);
    file = fopen(mbs, "r");
    //пока не ошибка и не конец структур
    while ((! rc) && (! finish))
    {
        //чтение имени автора
        rc_func = read_str_file(one.surname, file);
        //структуры кончились
        if (rc_func == MY_ERROR)
        {
            finish = 1;
            continue;
        }
        //ошибка чтения названия
        else if (rc_func == ERROR)
        {
            //printf("1");
            rc = ERROR;
        }

        //чтение названия
        rc_func = read_str_file(one.name_book, file);
        //ошибка чтения
        if (rc_func != OK)
        {
            //printf("2");
            rc = ERROR;
        }

        //чтение издателя
        rc_func = read_str_file(one.mader, file);
        //ошибка чтения издателя
        if (rc_func != OK)
        {
            //printf("3");
            rc = ERROR;
        }

        //чтение количества страниц
        rc_func = read_int(file, &one.lists);
        //ошибка чтения количества страниц
        if (rc_func == ERROR || one.lists < 1 || one.lists > MAX_LISTS)
        {
            //printf("4");
            rc = ERROR;
        }

        //дальше вариантная часть
        rc_func = read_variant(file, &one);
        //ошибка чтения вариантной части
        if (rc_func == ERROR)
        {
            //printf("5");
            rc = ERROR;
        }

        //если прочитано слишком много
        if (*n == MAX_COUNT)
            rc = ERROR;
        //если ошибок не было
        else if (! rc)
        {
            //printf("%d\n", *n);
            //вставляем считанный элемент в массивы
            books[*n] = one;
            book_keys[*n].lists = one.lists;
            book_keys[*n].start_ind = *n;
            //увеличиваем количество элементов в массиве
            (*n)++;
        }
        //printf("\n     NEW\n");
    }
    //если у файла в конце несколько пустых строк - ошибка
    if (fgetc(file) == '\n')
        rc = ERROR;
    fclose(file);
    //вернули код ошибки
    return rc;
}

//чтение целого числа
int read_int(FILE *file, int *list)
{
    int rc = OK;
    //прочитали символ
    char a = fgetwc(file);
    while (isspace(a) && (a != EOF) && (a != L'\n'))
        a = fgetwc(file);
    //обозначает что хоть одну цифру прочитали
    int flag = 1;
    *list = 0;
    // пока символ - цифра
    //printf("&%c&\n", a);
    while (isdigit(a))
    {
        flag = 0;
        //добавляем её к году
        *list = (a - '0') + *list * 10;
        //считали символ
        a = fgetwc(file);
        //printf("&%c&\n", a);
    }
    //если не прочитали ни одной цифры или последний считанный символ - не конец файла или перевод строки - ошибка
    if (flag || (! ((a == '\n') || (a == EOF))))
    {
        while (! ((a == '\n') || (a == EOF)))
            //считали символ
            a = fgetwc(file);
        rc = ERROR;
    }
    //printf("num = %d rc = %d\n", *list, rc);
    //вернули код ошибки
    return rc;
}

//чтение строки
int read_str_file(wchar_t *str, FILE *file)
{
    // Устанавливаем локаль для русского языка
    //setlocale(LC_ALL, "ru_RU.UTF-8");
    //код ошибки
    int rc = OK;
    //если не конец файла, иначе код возврата MY_ERROR
    if (fgetws(str, MAX_LEN + 2, file) != NULL)
    {
        //мы хоть что-то прочитали, иначе ошибка
        if (wcslen(str) > 1)
        {
            //прочитали всю строчку до переноса строки и  заменяем его на конец строки "\0", иначе ошибка
            if (str[wcslen(str) - 1] == '\n')
                str[wcslen(str) - 1] = '\0';
            else if (str[wcslen(str) - 1] != '\0')
            {
                rc = ERROR;
                //printf("opA! |%c|\n", str[wcslen(str) - 1]);
                //for (int i = 0; i < (int) wcslen(str) + 1; i++)
                    //printf("%d = !%c! %d\n", i, str[i], str[i]);
            }
        }
        else
            rc = MY_ERROR;
    }
    else
        rc = MY_ERROR;
    //вернули код ошибки
    return rc;
}

//вариантная часть
int read_variant(FILE *file, struct Book *book)
{
    int rc = OK;
    rc = read_int(file, &((*book).variant));
    if ((*book).variant == 1)
    {
        rc = read_str_file((*book).unic.texnic.otrasl, file);
        //if (rc == ERROR)
            //printf("6.0 ");
        rc += read_str_file((*book).unic.texnic.where, file);
        if (wcscmp((*book).unic.texnic.where, L"отечественная") * wcscmp((*book).unic.texnic.where, L"переводная") != 0)
            rc = ERROR;
        //if (rc == ERROR)
            //printf("6.1 ");
        else
        {
            rc += read_int(file, &((*book).unic.texnic.year));
            if ((*book).unic.texnic.year < 0 || (*book).unic.texnic.year > MAX_YEAR)
                rc = ERROR;
        }
        if (rc != OK)
        {
            rc = ERROR;
            //printf("6.2 ");
        }
    }
    else if ((*book).variant == 2)
    {
        rc = read_str_file((*book).unic.draw, file);
        if (wcscmp((*book).unic.draw, L"поэзия") != 0 && wcscmp((*book).unic.draw, L"пьеса") != 0 && wcscmp((*book).unic.draw, L"роман") != 0)
            rc = ERROR;
        //if (rc == ERROR)
            //printf("7");
    }
    else if ((*book).variant == 3)
    {
        rc = read_int(file, &((*book).unic.child.min_year));
        if ((*book).unic.child.min_year < 0 || (*book).unic.child.min_year > MAX_YEAR)
            rc = ERROR;
        rc += read_str_file((*book).unic.child.what, file);
        if (rc != OK || (wcscmp((*book).unic.child.what, L"сказки") != 0 && wcscmp((*book).unic.child.what, L"стихи") != 0))
        {
            rc = ERROR;
            //printf("8");
        }
    }
    else
    {
        rc = ERROR;
        //printf("9 var = %d\n", (*book).variant);
    }
    return rc;
}
