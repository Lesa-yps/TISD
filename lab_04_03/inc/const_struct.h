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

// Ограничение на размер стека
#define MAX_COUNT_ELEM_STAT 10000
#define MAX_COUNT_ELEM_DIN 80000

#define SIZE_OF_STR 1024

// Структура информация
struct Inf_stack
{
    int len_q_now;       // Текущая длина
    int len_q_max;       // Максимальная длина
    int len_strk_max;    // Максимальная длина строки
};

// Структура - элемент односвязного списка
struct Node
{
    char *data; // данные
    struct Node *next;   // Указатель на следующий элемент односвязного списка
};

// структура удалённых адресов
struct Del_adresses
{
    void *arr[MAX_COUNT_ELEM_DIN]; // массив
    int count; // количество
};

#endif // CONST_STRUCT_H
