#ifndef CONST_STRUCT_H
#define CONST_STRUCT_H
//код возврата, если всё хорошо
#define OK 0
//код возврата, если произошла ошибка
#define ERROR 1
//масимальная длина мантиссы 1-ого числа
#define MAX_MAN1 35
//масимальная длина мантиссы 2-ого числа и результата
#define MAX_MAN23 40

//структура - число
struct number
{
    int minus; //знак числа
    int mantissa[MAX_MAN23 + 2]; //длина мантиссы с запасом два элемента для округления
    int order; //порядок
    int len_man; //длина мантиссы
};

#endif // CONST_STRUCT_H
