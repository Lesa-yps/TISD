// Талышева Олеся ИУ7-35Б ТИСД Лаб #5
#include <stdio.h>
#include "const_struct.h"
#include "simulate_dinam.h"
#include "simulate_stat.h"
#include "build_res.h"

int clean_buf(void)
{
    char a = getchar();
    int count = 0;
    while (a != '\n' && a != EOF)
    {
        count++;
        a = getchar();
    }
    return count;
}

void ask_talk(int *talk)
{
    printf("Введите 1, если нужно выводить адреса элементов при удалении/добавлении в очередь, иначе 0: ");
    while (scanf("%d", talk) != 1 || (clean_buf() != 0)|| *talk < 0 || *talk > 1)
        printf("Ошибка ввода! Введите 1 или 0: ");
    printf("Инструкция принята.\n");
}

void read_double(double *num, double mini)
{
    while (scanf("%lf", num) != 1 || (clean_buf() != 0) || diff_time(*num, mini) < 0)
        printf("Ошибка ввода! Введите число >= %f: ", mini);
    printf("Успешно считано.\n");
}

int main(void)
{
    int rc = OK;
    int user = NEITRAL_USER;
    int talk;
    int own = 1;

    double min_time_come = 0;
    double max_time_come = 6;

    double min_time_work = 0;
    double max_time_work = 1;

    struct Inf_oueue infa_q1;
    struct AO ao1;

    srand(time(NULL));
    printf("Приветствую, пользователь!\n");

    printf("Cистема массового обслуживания, состоящую из обслуживающего аппарата(ОА) и очереди заявок.\n\
Заявки поступают в 'хвост' очереди по случайному закону с интервалом времени Т1, равномерно распределенным от 0 до 6 единиц времени (е.в.).\n\
В ОА они поступают из 'головы' очереди по одной и обслуживаются также равновероятно за время Т2 от 0 до 1 е.в.\n\
Каждая заявка после ОА вновь поступает в 'хвост' очереди, совершая всего 5 циклов обслуживания, после чего покидает систему.\n\
В начале процесса в системе заявок нет.\n\
Программа реализует процесс обслуживания до ухода из системы первых 1000 заявок,\n\
выдавая после обслуживания каждых 100 заявок информацию о текущей и средней длине очереди, а в конце процесса:\n\
- общее время моделирования\n\
- количество вошедших в систему и вышедших из нее заявок\n\
- количество срабатываний ОА\n\
- время простоя аппарата.\n\
По требованию пользователя выдаются на экран адреса элементов очереди при их удалении и добавлении.\n");

    while (user != 0)
    {
        if (user != ERROR_USER)
        {
            printf("\nМеню:\n");
            printf("1 - обработать заявки с помощью статического массива\n\
2 - обработать заявки с помощью односвязного списка\n\
3 - сравнить реализации статическим массивом и односвязным списком\n\
4 - изменить начальные значения системы\n\
0 - завершить выполнение программы\n\
Введите цифру, соответствующую выбранному пункту меню: ");
        }
        if (scanf("%d", &user) != 1 || user < 0 || user > 4)
        {
            clean_buf();
            printf("Ошибка ввода! Введите цифру от 0 до 4: ");
            user = ERROR_USER;
        }
        else if (user == 1)
        {
             //ask_talk(&talk);
             talk = 0;
             printf("    Статическая симуляция запущена...\n");
             rc = simulate_stat(talk, own, min_time_come, max_time_come, min_time_work, max_time_work, &infa_q1, &ao1);
        }
        else if (user == 2)
        {
             ask_talk(&talk);
             printf("    Динамическая симуляция запущена...\n");
             rc = simulate_dinam(talk, own, min_time_come, max_time_come, min_time_work, max_time_work, &infa_q1, &ao1);
        }
        else if (user == 3)
             rc = build_res(min_time_come, max_time_come, min_time_work, max_time_work);
        else if (user == 4)
        {
             printf("Введите минимальное время прихода заявки: ");
             read_double(&min_time_come, 0);
             printf("Введите максимальное время прихода заявки: ");
             read_double(&max_time_come, min_time_come);
             printf("Введите минимальное время обработки заявки: ");
             read_double(&min_time_work, 0);
             printf("Введите максимальное время обработки заявки: ");
             read_double(&max_time_work, min_time_work);
             printf("Изменение настроек завершено.\n");
        }
        else if (user == 0)
             printf("Завершение работы ^-^\n");
    }
    return rc;
}
