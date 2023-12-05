#include "calc.h"

//каждая цифра из второго числа умножается на первое число
//результат записывается в марицу друг под другом (без сдвига влево)
void calc_matrix(struct number one, struct number two, int arr[MAX_MAN23][MAX_MAN1 + 1]);

//вычисление where и extra
void calc_where_extra(int one_two, int *where, int *extra);

//фунция заполняет массив мантиссы, складывая диагонали
void sum_diag(struct number one, struct number two, struct number *tree, int *h,\
              int *where, int *extra, int *i_second, int arr[MAX_MAN23][MAX_MAN1 + 1]);

//функция перемножает мантиссы чисел
void calc(struct number one, struct number two, struct number *tree)
{
    //вспомогательные индексы для сложения чисел по диагонали матрицы
    int h;
    int i_second;
    //индекс записи в массив мантиссы получившегося числа
    int where;
    //если получившаяся мантисса > 40 цифр, программа её округлит
    //это число хранит индекс числа после которого начнётся округление
    int extra;

    //по аналогии с умножением столбиком создается и заполняется матрица 40*35
    int arr[MAX_MAN23][MAX_MAN1 + 1] = {{0}};
    calc_matrix(one, two, arr);

    //вычисление where и extra
    calc_where_extra(two.len_man + one.len_man - 1, &where, &extra);

    //вычисление длины итогового числа
    if (extra != -1)
    {
        (*tree).order += where + 1;
        (*tree).len_man = MAX_MAN23;
        if (where >= 2)
            where -= 2;
        else
            where = MAX_MAN23 + 1 - where;
    }
    else
        (*tree).len_man = where + 1;
    //последнюю цифру будущей мантиссы обнуляем
    (*tree).mantissa[where] = 0;
    (*tree).mantissa[MAX_MAN23] = 0;
    (*tree).mantissa[MAX_MAN23 + 1] = 0;
    //заполняем массив мантиссы, складывая диагонали, начинающиеся на первой строке
    for (int i = one.len_man; i >= 0; i--, where--)
    {
        //индексы пробегающие по диагонали, начинающейся на первой строке
        h = 0;
        i_second = i;
        //само суммирование диагоналей, начинающихся на первой строке
        sum_diag(one, two, tree, &h, &where, &extra, &i_second, arr);

    }
    //заполняем массив мантиссы, складывая диагонали, начинающиеся на первом столбце
    for (int i = 1; i < two.len_man; i++, where--)
    {
        //индексы пробегающие по диагонали, начинающейся на первом столбце
        h = 0;
        i_second = i;
        //само суммирование диагоналей, начинающихся на первом столбце
        sum_diag(one, two, tree, &i_second, &where, &extra, &h, arr);

    }
}

//каждая цифра из второго числа умножается на первое число
//результат записывается в марицу друг под другом (без сдвига влево)
void calc_matrix(struct number one, struct number two, int arr[MAX_MAN23][MAX_MAN1 + 1])
{
    //перебираем цифры во втором числе
    for (int i = two.len_man - 1; i >= 0; i--)
    {
        //перебираем цифры в первом числе
        for (int j = one.len_man - 1; j >= 0; j--)
        {
            //вычисли число
            arr[(two.len_man - 1) - i][j + 1] += two.mantissa[i] * one.mantissa[j];
            //последнюю цифру записали в эту ячейку
            arr[(two.len_man - 1) - i][j] = arr[(two.len_man - 1) - i][j + 1] / 10;
            //а количество десятков записали в ячейку перед данной
            arr[(two.len_man - 1) - i][j + 1] -= (arr[(two.len_man - 1) - i][j] * 10);
        }
    }
}

//вычисление where и extra
void calc_where_extra(int one_two, int *where, int *extra)
{
    //вычисление индекса записи в массив мантиссы получившегося числа
    *where = one_two / MAX_MAN23;
    *where = one_two - (*where) * MAX_MAN23;
    //если получившаяся мантисса > 40 цифр, программа её округлит
    //вычисление числа, хранящего индекс числа после которого начнётся округление
    if (one_two >= (MAX_MAN23))
        *extra = 0;
    else
        *extra = -1;
}

//фунция заполняет массив мантиссы, складывая диагонали
void sum_diag(struct number one, struct number two, struct number *tree, int *h,\
              int *where, int *extra, int *i_second, int arr[MAX_MAN23][MAX_MAN1 + 1])
{
    //прошлись по одной диагонали и записали получившуюся сумму в массив мантиссы
    while (*i_second <= one.len_man && *h < two.len_man)
        (*tree).mantissa[*where] += arr[(*h)++][(*i_second)++];

    //количество десятков записываем в массив мантиссы в элемент перед
    if (*where == 0 && *extra == 0)
        (*tree).mantissa[MAX_MAN23 + 1] = (*tree).mantissa[*where] / 10;
    else
        (*tree).mantissa[*where - 1] = (*tree).mantissa[*where] / 10;
    //в данном элементе убираем десятки и оставляем только единицы
    (*tree).mantissa[*where] -= (((*tree).mantissa[*where] / 10) * 10);
    //проверка: а не пора ли округлять?
    if (*where == *extra)
    {
        if ((*tree).mantissa[*where] >= 5)
            (*tree).mantissa[MAX_MAN23 + 1] += 1;
        *where = MAX_MAN23 + 2;
        *extra = MAX_MAN23 + 2;
    }
}
