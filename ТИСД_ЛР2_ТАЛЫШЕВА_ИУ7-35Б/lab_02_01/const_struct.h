#ifndef CONST_STRUCT_H
#define CONST_STRUCT_H

//коды возврата
#define OK 0
#define ERROR 1
#define MY_ERROR 2

//максимальная длина строки
#define MAX_LEN 25
//максимальное количество структур
#define MAX_COUNT 100
//минимальное количество структур
#define MIN_COUNT 40
//максимальное количество страниц
#define MAX_LISTS 2000000000
//максимальное количество страниц
#define MAX_YEAR 1000000
//максимальный минимальный возраст детской литературы
#define MAX_CHILD_AGE 17
//количество сортировок
#define COUNT_SORT 50

#define SIZE_OF_BUF 100

#include <wchar.h>

//структура
struct Book
{
    wchar_t surname[MAX_LEN + 1];
    wchar_t name_book[MAX_LEN + 1];
    wchar_t mader[MAX_LEN + 1];
    int lists;
    int variant;//1, 2 or 3
    union spec
    {
        struct texnical
        {
            wchar_t otrasl[MAX_LEN + 1];
            wchar_t where[MAX_LEN + 1];// отечественная/переводная
            int year;
        } texnic;
        wchar_t draw[MAX_LEN + 1]; // роман/пьеса/поэзия
        struct children
        {
            int min_year;
            wchar_t what[MAX_LEN + 1];// сказки/стихи
        } child;
    } unic;
};

//структура - ключ
struct Book_key
{
    int start_ind;
    int lists;
};

#endif // CONST_STRUCT_H
