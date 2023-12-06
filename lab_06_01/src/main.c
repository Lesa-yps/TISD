// Талышева Олеся ИУ7-35Б ТИСД Лаб #06_01
// (у меня бинарное дерево поиска, Обрубов С.И.)
#include <stdio.h>
#include "const_struct.h"
#include "work_with_tree.h"
#include "work_with_file.h"
#include "build_res.h"

int main(void)
{
    int rc = OK;
    int user = NEITRAL_USER;
    FILE *file = NULL;
    struct Node *Head_tree;

    srand(time(NULL));
    printf("Приветствую, пользователь!\n");

    printf("Задание:\n\
В текстовом файле содержатся целые числа. Строится двоичное дерево из чисел файла и\n\
выводится на экран в виде дерева. Реализовать основные операции работы с деревом:\n\
обход дерева, включение, исключение и поиск узлов. Также определяется количество узлов дерева\n\
на каждом уровне и добавляется число в файл. Сравнивается эффективность алгоритмов\n\
добавления чисел в файл и в дерево и поиск в зависимости от высоты деревьев и степени их ветвления.\n");
    file_whoose(&file);
    rc = tree_from_file(&Head_tree, file);
    if (rc == ERR_SIZE)
        printf("Ошибка! Достигнут максимальный размер дерева.\n");
    else if (rc == ERR_MEM)
        printf("Ошибка выделения памяти.\n");
    else
        tree_print(Head_tree);
    while (user != 0)
    {
        if (user != ERROR_USER)
        {
            printf("\nМеню:\n");
            printf("1 - обойти дерево\n\
2 - добавить новый элемент в дерево\n\
3 - удалить элемент из дерева\n\
4 - найти элемент в дереве\n\
5 - определить количество узлов в дереве на каждом уровне\n\
6 - добавить новый элемент в файл\n\
7 - выбрать новый файл для работы (дерево тоже перезапишется)\n\
8 - вывести дерево\n\
9 - cравнивнение эффективностей алгоритмов добавления и поиска\n\
0 - завершить выполнение программы\n\
Введите цифру, соответствующую выбранному пункту меню: ");
        }
        if (scanf("%d", &user) != 1 || user < 0 || user > 9 || clean_buf() != 0)
        {
            printf("Ошибка ввода! Введите цифру от 0 до 9: ");
            user = ERROR_USER;
        }
        else if (user == 1) // обход и вывод дерева
        {
            printf("Обход дерева:\n");
            if (Head_tree == NULL)
                printf("Дерево пустое.");
            else
                tree_traversal(Head_tree);

        }
        else if (user == 2) // добавление элемента в дерево
        {
            int num = 0;
            struct Node *Head_tree_tmp;
            printf("Введите элемент, который хотите добавить:\n");
            while (scanf("%d", &num) != 1)
                printf("Ошибка! Повторите ввод: ");
            Head_tree_tmp = tree_add_elem(&Head_tree, num);
            if (Head_tree_tmp == NULL)
                printf("Ошибка выделения памяти!\n");
            else
            {
                Head_tree = Head_tree_tmp;
                printf("Добавили.\n");
            }
        }
        else if (user == 3) // удаление элемента из дерева
        {
            if (Head_tree == NULL)
                printf("Ошибка! Дерево пустое.");
            else
            {
                int num = 0;
                printf("Введите элемент, который хотите удалить:\n");
                while (scanf("%d", &num) != 1)
                    printf("Ошибка! Повторите ввод: ");
                struct Node *Head_tree_tmp = tree_del_elem(&Head_tree, num);
                if (Head_tree_tmp == NULL)
                {
                    rc = ERR_NO_ELEM;
                    printf("Ошибка удаления! Такого элемента нет в дереве.\n");
                }
                else
                    printf("Удалили.\n");
            }
        }
        else if (user == 4) // поиск элемента в дереве
        {
            int num = 0;
            struct Node *find_node;
            printf("Введите элемент, который хотите найти:\n");
            while (scanf("%d", &num) != 1)
                printf("Ошибка! Повторите ввод: ");
            find_node = tree_find_elem(Head_tree, num);
            if (find_node == NULL)
            {
                rc = ERR_NO_ELEM;
                printf("Такого элемента нет в дереве.\n");
            }
            else
                printf("Искомый элемент: %d.\n", find_node->data);
        }
        else if (user == 5) // определить количество узлов в дереве на каждом уровне
        {
            if (Head_tree == NULL)
                printf("Дерево пустое.\n");
            else
                tree_level_node(Head_tree);
        }
        else if (user == 6) // добавить новый элемент в файл
        {
            int num = 0;
            printf("Введите элемент, который хотите добавить:\n");
            while (scanf("%d", &num) != 1)
                printf("Ошибка! Повторите ввод: ");
            file_add_elem(file, num);
        }
        else if (user == 7) // выбрать новый файл для работы (дерево тоже перезапишется)
        {
            file_whoose(&file);
            rc = tree_from_file(&Head_tree, file);
            if (rc == ERR_SIZE)
                printf("Ошибка! Достигнут максимальный размер дерева.\n");
            else if (rc == ERR_MEM)
                printf("Ошибка выделения памяти.\n");
            else
                tree_print(Head_tree);
        }
        else if (user == 8) // вывести дерево
        {
            tree_print(Head_tree);
        }
        else if (user == 9)
        {
            // Сравнивается эффективность алгоритмов добавления чисел в файл и в дерево
            rc = build_res_add();
            // Сравнивается эффективность поиска в зависимости от высоты деревьев и степени их ветвления
            build_res_find();
        }
        else if (user == 0)
             printf("Завершение работы ^-^\n");
    }
    fclose(file);
    return rc;
}
