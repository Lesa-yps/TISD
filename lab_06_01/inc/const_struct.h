#ifndef CONST_STRUCT_H
#define CONST_STRUCT_H

// коды ошибок
#define OK 0
#define ERROR 1
#define ERR_SIZE -1
#define ERR_MEM 35
#define ERR_NO_ELEM 2

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

#define SIZE_OF_BUF 1024

// Ограничение на размер дерева
//#define MAX_SIZE_TREE 80000

// Структура - элемент дерева
struct Node
{
    int *data; // Указатель на данные
    struct Node *right;   // Указатель на правое поддерево (больше)
    struct Node *left;   // Указатель на левое поддерево (меньше)
};

#endif // CONST_STRUCT_H
