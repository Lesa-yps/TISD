#include "user_1.h"

//округление числа
void circle_num(int start, struct number *tree);

//под-main, если пользователь выбрал в меню вычисления(1)
int user_1(void)
{
    //сохраняет наличие в числе ненулевых цифр
    int flag = 0;
    //первое вводимое число
    struct number one;
    //второе вводимое число
    struct number two;
    //число - результат их перемножения
    struct number tree;
    int i = 0;
    int k = 0;
    //код ошибки
    int rc = OK;
    //инструкция ввода чисел
    printf("Enter 2 real numbers for multiplication in the format +-m.n E +-K, where\n\
 the total length of the mantissa of the first multiplier (m+n) is up to\n\
 35 significant digits, the second – up to 40 significant digits, and\n\
 the magnitude of the order of K - up to 5 digits. Entering 'E' and characters is mandatory.\n\
 There is no space between the order sign and the order itself.\n");
    //читаем числа для перемножения
    tree.order = 0;
    read_num(&one, MAX_MAN1);
    read_num(&two, MAX_MAN23);
    //умножаем их мантиссы
    calc(one, two, &tree);
    //вычисляем итоговый знак
    tree.minus = one.minus * two.minus;
    //а не нуль ли число?
    for (int r = 0; r < tree.len_man; r++)
        if (tree.mantissa[r] != 0)
        {
            flag = 1;
            break;
        }
    if (! flag)
    {
        tree.order = 1;
        tree.len_man = 2;
    }
    else
        //вычисляем порядок с учётом маски вывода
        tree.order += one.order + two.order + tree.len_man;
    //если первый знак 0, исправляем порядок
    if (tree.mantissa[0] == 0)
        tree.order--;
    //если порядок стал слишком большой - число посчитать нельзя
    if (tree.order > 99999 || tree.order < -99999)
    {
        printf("Program can't calculate this numbers: order overflow.\n");
        rc = ERROR;
    }
    //если порядок в норме
    else
    {
        //выводим +-0.
        if (tree.minus < 0)
            printf("\nResult: -0.");
        else
            printf("\nResult: +0.");
        //если первый знак 0 - пропускаем его (он был на случай переполнения)
        if (tree.mantissa[0] == 0)
        {
            i = 1;
            //округление числа, если его длина больше 40 цифр
            if (tree.len_man == MAX_MAN23)
            {
                circle_num(MAX_MAN23, &tree);
                tree.order++;
                //если после округления первый знак перестал быть нулём, возвращаем его
                if (tree.mantissa[0] != 0)
                    i = 0;
                else
                    k = 1;
            }
        }
        //округляем, если первый знак не нуль, а его длина больше 40 цифр
        else if (tree.len_man == MAX_MAN23)
            circle_num(MAX_MAN23 - 1, &tree);
        //выводим мантиссу
        for (; i < tree.len_man + k; i++)
            printf("%d", tree.mantissa[i]);
        //выводим порядок
        printf(" E %+d\n", tree.order);
        //всё успешно отработало
        printf("The program completed the task successfully.\n");
    }
    //возвращаем код возврата
    return rc;
}

//округление числа
void circle_num(int start, struct number *tree)
{
    //само округление
    (*tree).mantissa[start] += ((*tree).mantissa[start + 1] > 4);
    //если в результате округления элемент стал двухзначным, переносим десяток на предыдущую цифру
    //и так пока элементы не перестанут быть двухзначными или до начала числа
    while (((*tree).mantissa[start] >= 10) && (start > 0))
    {
        (*tree).mantissa[start - 1] += (*tree).mantissa[start] / 10;
        (*tree).mantissa[start] -= ((*tree).mantissa[start] / 10) * 10;
        start--;
    }
}
