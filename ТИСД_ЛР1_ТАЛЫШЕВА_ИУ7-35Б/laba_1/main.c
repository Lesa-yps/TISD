#include <stdio.h>
//под-main, если пользователь выбрал в меню вычисления(1)
#include "user_1.h"
//отсюда нужна функция очистки буфера
#include "read_num.h"

//интерфейс
int main(void)
{
    //что выбрал пользватель в меню
    int user = 0;
    //код возврата
    int rc;
    //приветствие + условие задачи
    printf("Good day, user!\n\
     The program performs the operation of multiplying a real number\n\
by a real number in the form +-m.n E +-K, where\n\
the total length of the mantissa of the first multiplier (m+n) is up to\n\
35 significant digits, the second – up to 40 significant digits, and\n\
the magnitude of the order of K - up to 5 digits. The result is given in the form\n\
+-0.m1 E +-K1, where m1 is up to 40 significant digits, and K1 is up to 5 digits.\n");
    //пока пользователь не выбрал выход из программы(2) цикл выполняется
    while (user != 2)
    {
        //менюшка
        printf("\nMain menu:\n\
   - To calculate the product of real numbers, press 1\n\
   - To exit the program, press 2\n:");
        //ввод выбранного пользователем пункта меню и его проверка
        if (scanf("%d", &user) != 1 || user < 1 || user > 2)
        {
             printf("Error input. Please try again.\n");
             //чистим буфер
             clean_buf();
             continue;
        }
        //если 1 вызываем функцию для вычислений
        if (user == 1)
             rc = user_1();
        //иначе(2) завершение цикла
        else
             printf("Completion ^-^\n");
    }
    //возврат кода ошибки
    return rc;
}
