// Талышева Олеся ИУ7-35Б ТИСД Лаб #06_01
// (у меня идеально сбалансированное дерево) Обрубов С.И.
#include <stdio.h>
#include "const_struct.h"
#include "work_with_tree.h"
#include "work_with_file.h"
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

int main(void)
{
    int rc = OK;
    int user = NEITRAL_USER;
    FILE *file = NULL;
    struct Node *Head_tree;

    srand(time(NULL));
    printf("Приветствую, пользователь!\n");

    printf("Задание:\n\
В текстовом файле содержатся целые числа. Строится двоичное дерево из чисел файла и
выводится на экран в виде дерева. Реализовать основные операции работы с деревом:
обход дерева, включение, исключение и поиск узлов. Также определяется количество узлов дерева
на каждом уровне и добавляется число в файл. Сравнивается эффективность алгоритмов
добавления чисел в файл и в дерево и поиск в зависимости от высоты деревьев и степени их ветвления.\n");
    whoose_file(&file);
    while (user != 0)
    {
        if (user != ERROR_USER)
        {
            printf("\nМеню:\n");
            printf("1 - обойти дерево (и вывести его)\n\
2 - добавить новый элемент в дерево\n\
3 - удалить элемент из дерева\n\
4 - найти элемент в дереве\n\
5 - определить количество узлов в дереве на каждом уровне\n\
6 - добавить новый элемент в файл\n\
7 - выбрать новый файл для работы (дерево тоже перезапишется)\n\
0 - завершить выполнение программы\n\
Введите цифру, соответствующую выбранному пункту меню: ");
        }
        if (scanf("%d", &user) != 1 || user < 0 || user > 7)
        {
            clean_buf();
            printf("Ошибка ввода! Введите цифру от 0 до 7: ");
            user = ERROR_USER;
        }
        else if (user == 1)
        {
            printf("Обход дерева:\n");
            tree_traversal(Head_tree);
            if (Head_tree == NULL)
                printf("Дерево пустое.");

        }
        else if (user == 2)
        {
            int num = 0;
            printf("Введите элемент, который хотите добавить:\n");
            while (scanf("%d", &num) != 1)
                printf("Ошибка! Повторите ввод: ");
            rc = tree_add_elem(&Head_tree);
            if (rc == ERR_SIZE)
                printf("Ошибка! Достигнут максимальный размер дерева.\n")
            else if (rc == ERR_MEM)
                printf("Ошибка выделения памяти.\n")
            else
                printf("Добавили.\n");
        }
        else if (user == 3)
        {
            int num = 0;
            printf("Введите элемент, который хотите удалить:\n");
            while (scanf("%d", &num) != 1)
                printf("Ошибка! Повторите ввод: ");
            rc = tree_del_elem(&Head_tree);
            if (rc = ERR_NO_ELEM)
                printf("Ошибка удаления! Такого элемента нет в дереве.\n");
            else
                printf("Удалили.\n");
        }
        else if (user == 4)
        {
            int num = 0;
            printf("Введите элемент, который хотите добавить:\n");
            while (scanf("%d", &num) != 1)
                printf("Ошибка! Повторите ввод: ");
            printf("Искомый элемент:\n");
            rc = tree_find_elem(&Head_tree);
            if (rc = ERR_NO_ELEM)
                printf("Такого элемента нет в дереве.\n")
        }
        else if (user == 5)
        {
            rc = tree_level_node(&Head_tree);
            if (Head_tree == ERR_NO_ELEM)
                printf("Такого элемента нет в дереве.\n")
        }
        else if (user == 0)
             printf("Завершение работы ^-^\n");
    }
    return rc;
}
