// Талышева Олеся ИУ7-35Б ТИСД Лаб #4_01
#include <stdio.h>
#include "const_struct.h"
#include "simulate_dinam.h"
#include "simulate_stat.h"
#include "build_res.h"
#include "help_func.h"

void ask_talk(int *talk)
{
    printf("Введите 1, если нужно выводить адреса элементов при удалении из очереди, иначе 0: ");
    while (scanf("%d", talk) != 1 || (clean_buf() != 0)|| *talk < 0 || *talk > 1)
        printf("Ошибка ввода! Введите 1 или 0: ");
    printf("Инструкция принята.\n");
}

int main(void)
{
    int rc = OK;
    int user = NEITRAL_USER;
    int talk;
    int own = 0;

    struct Inf_stack infa_q1;

    printf("Приветствую, пользователь!\n");

    printf("Программа работает со стеком и выполняет операции по добавлению, удалению элементов\n\
и выводу текущего состояния стека. Стек реализован:\n\
1) статическим массивом\n\
2) списком\n\
Программа распечатывает слова (которые находятся в стеке) в обратном порядке, каждое слово перевернутым.\n\
По требованию пользователя выдаются на экран адреса элементов очереди при их удалении.\n");

    while (user != 0)
    {
        if (user != ERROR_USER)
        {
            printf("\nМеню:\n");
            printf("1 - работать с реализацией стека как статического массива\n\
2 - работать с реализацией стека как односвязного списка\n\
3 - сравнить реализации статическим массивом и односвязным списком\n\
0 - завершить выполнение программы\n\
Введите цифру, соответствующую выбранному пункту меню: ");
        }
        if (scanf("%d", &user) != 1 || user < 0 || user > 3)
        {
            clean_buf();
            printf("Ошибка ввода! Введите цифру от 0 до 3: ");
            user = ERROR_USER;
        }
        else if (user == 1)
        {
             ask_talk(&talk);
             printf("    Статическая симуляция запущена...\n");
             rc = simulate_stat(talk, own, &infa_q1);
        }
        else if (user == 2)
        {
             ask_talk(&talk);
             printf("    Динамическая симуляция запущена...\n");
             rc = simulate_dinam(talk, own, &infa_q1);
        }
        else if (user == 3)
             rc = build_res();
        else if (user == 0)
             printf("Завершение работы ^-^\n");
    }
    return rc;
}
