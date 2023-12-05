#include "read_num.h"

//функция чистит буфер
void clean_buf(void)
{
    char c[100];
    fgets(c, sizeof(c), stdin);
}

//подсказка ввода
void help_input(int MAX_MAN);

//функция читает знак числа
int read_sign(struct number *sth);

//функция читает мантиссу числа
int read_man(struct number *sth, int flag, int MAX_MAN);

//функция читает порядок числа
int read_order(int flag, struct number *sth);

//функция читает число в формате +-m.n Е +-K
void read_num(struct number *sth, int MAX_MAN)
{
    //флаг отвечает за повторяемость цикла, запускающего чтение числа заново
    int flag = 1;
    //цикл запускает чтение числа заново
    while (flag)
    {
        //чисткка буфера
        clean_buf();
        //если ошибок не будет, цикл прекратится
        flag = 0;
        //подсказка ввода
        help_input(MAX_MAN);
        //чтение знака
        if (read_sign(sth) != OK)
        {
            printf("Error with input sign. Please try again.\n");
            flag = 1;
            continue;
        }
        //чтение мантиссы + обнуление длины и порядка
        (*sth).len_man = 0;
        (*sth).order = 0;
        if ((flag = read_man(sth, flag, MAX_MAN)) != OK)
            continue;
        //чтение порядка
        flag = read_order(flag, sth);
    }
}

//подсказка ввода
void help_input(int MAX_MAN)
{
    printf("                        !_!____5____10________20________30____");
    if (MAX_MAN == MAX_MAN23)
        printf("___40");
    printf("!E!_!_____!\n");
    printf("Enter the ");
    if (MAX_MAN == MAX_MAN1)
        printf(" first");
    else
        printf("second");
    printf(" number: ");
}

//функция читает знак числа
int read_sign(struct number *sth)
{
    //читаем в "а" по символу, пока не встретим знак или ошибку
    char a = getchar();
    //бесконечный цикл
    while (1)
    {
        //прочли "+" записали, вышли из цикла
        if (a == '+')
        {
            (*sth).minus = 1;
            break;
        }
        //прочли "-" записали, вышли из цикла
        else if (a == '-')
        {
            (*sth).minus = -1;
            break;
        }
        //прочли не знак и не пробельный символ, вернули из фуункции ошибку
        else if (! isspace(a))
            return ERROR;
        //прочитали новый символ
        a = getchar();
    }
    //если дошли до сюда, значит всё хорошо
    return OK;
}

//функция читает мантиссу числа
int read_man(struct number *sth, int flag, int MAX_MAN)
{
    //переменная запоминает: был ли пробел
    int was_space = 0;
    //переменная запоминает: была ли точка
    int was_point = 0;
    //в переменную считывается по символу
    char a = getchar();
    //цикл читает символы до "Е" (не включительно)
    while (a != 'E')
    {
        //если встретился пробел и часть мантиссы уже прочитана, запоминаем в переменную, что пробел был
        if (isspace(a) && ((*sth).len_man != 0))
            was_space = 1;
        //если встретили точку, запоминаем в переменную, что точка была
        else if (a == '.')
            was_point = 1;
        //если пробел был и встретился не пробел => ошибка, поднимаем флаг, выходим из цикла
        else if ((was_space == 1) && (! isspace(a)))
        {
            printf("Error with input mantissa. Please try again.\n");
            flag = ERROR;
            break;
        }
        //прочитали число
        else if ((a <= '9') && (a >= '0'))// || ((a == '0') && ((*sth).len_man != 0)))
        {
            //затираем первый нуль в числе, если он был
            if (((*sth).len_man == 1) && ((*sth).mantissa[0] == 0))
                (*sth).len_man--;
            //если перебор длины мантиссы => ошибка, поднимаем флаг, выходим из цикла
            if ((*sth).len_man == MAX_MAN)
            {
                printf("Error: mantissa is too long. Please try again.\n");
                flag = ERROR;
                break;
            }
            //записываем цифру и увеличиваем длину мантиссы
            (*sth).mantissa[(*sth).len_man++] = a - '0';
            //если была точка, уменьшаем порядок числа
            if (was_point)
                (*sth).order--;
        }
        //прочитали пробел и мантиссы ещё не было
        else if (isspace(a) && ((*sth).len_man == 0))
            ;
        //прочитали что-то не то => ошибка, поднимаем флаг, выходим из цикла
        else
        {
            printf("Error with input mantissa. Please try again.\n");
            flag = ERROR;
            break;
        }
        //считываем новый символ
        a = getchar();
    }
    //если в итоге мантисса пустая => ошибка, поднимаем флаг
    if ((*sth).len_man == 0)
    {
        printf("Error: mantissa is empty. Please try again.\n");
        flag = ERROR;
    }
    //вернули код ошибки
    return flag;
}

//функция читает порядок числа
int read_order(int flag, struct number *sth)
{
    //вспомогательная переменная для читаемого порядка
    int order_2;
    //прочитали порядок и проверили на ошибку чтения
    if (scanf("%d", &order_2) != 1)
    {
        printf("Error with input order. Please try again.\n");
        flag = ERROR;
    }
    //проверили длину порядка (<= 5)
    else if (order_2 < -99999 || order_2 > 99999)
    {
        printf("Error: order is too long. Please try again.\n");
        flag = ERROR;
    }
    //если всё хорошо, прибавили прочитанный порядок к тому, что насчитали после точки
    else
        (*sth).order += order_2;
    //вернули код ошибки
    return flag;
}
