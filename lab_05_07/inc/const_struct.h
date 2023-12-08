#ifndef CONST_STRUCT_H
#define CONST_STRUCT_H

// коды ошибок
#define OK 0
#define ERROR 1

// эпсилон
#define EPS 1e-8

// макрос минимум
#define MIN(x,y) (((x) < (y)) ? (x) : (y))

// количество замеров
#define COUNT_SORT 15

// нейтральное значение числа - выбранного пункта меню
#define NEITRAL_USER -1
// ошибочное значение числа - выбранного пункта меню
#define ERROR_USER -2

#define MAX_COUNT_WORK1 5
#define MAX_COUNT_APP 10000
#define REPORT_COUNT_APP 100
#define NEED_COUNT_AWAY_APP 1000

// Ограничение на размер динамической очереди
#define MAX_DIN_QUEUE 80000

// Структура Заявка
struct Applic
{
    double time_come;     // Время прихода
    double time_work;     // Время обслуживания
    int count_work;       // Количество проходов аппарата
};

// Структура ОА
struct AO
{
    double time_stay;     // Время простоя
    int count_work;       // Количество заявок
};

// Структура Данные об очереди
struct Inf_oueue
{
    int len_q_now;       // Текущая длина очереди
    int len_q_max;       // Максимальная длина очереди
    int count_change_q;  // Количество изменений очереди
    long int len_q_sum;       // Сумма всех длин очередей
    int count_come_app;  // Количество вхождений заявок
    int count_away_app;  // Количество заявок, вышедших из системы
    double time_sim;     // Общее время симуляции
};

// Структура - элемент односвязного списка
struct Node
{
    struct Applic *data; // Указатель на структуру - заявку
    struct Node *next;   // Указатель на следующий элемент односвязного списка
};

#endif // CONST_STRUCT_H
