// Талышева Олеся ИУ7-35Б ТИСД Лаб #07_01
#include <stdio.h>
#include "const_struct.h"
#include "work_with_tree.h"
#include "work_with_file.h"
#include "work_with_bal_tree.h"
#include "work_with_ohash.h"
#include "work_with_chash.h"
#include "build_res.h"

int what_struct(void)
{
    int user = 0;
    printf("Введите 1 (обычное дерево), 2 (сбалансированное дерево), 3 (хэш-таблица с внешним хэшированием) или\n"
    "4 (хэш-таблица с внутренним хэшированием): ");
    while (scanf("%d", &user) != 1 || user < 1 || user > 4 || clean_buf() != 0)
        printf("Ошибка! Повторите попытку: ");
    return user;
}

int main(void)
{
    int rc = OK;
    int talk = 1;
    int user = NEITRAL_USER;
    // файл
    FILE *file = NULL;
    // обычное бинарное дерево поиска
    struct Node *Head_tree_ord;
    // сбалансированное бинарное дерево поиска
    struct Node *Head_tree_bal;
    // хэш-таблица с внутренним хэшированием
    struct Hash_open *Table_open;
    // хэш-таблица с внешним хэшированием
    struct Hash_close *Table_close;
    // поприветствовали и вывели задание
    srand(time(NULL));
    printf("Приветствую, пользователь!");
    printf("Задание:\n"
           "В текстовом файле содержатся целые числа. Строится двоичное дерево из чисел файла,\n"
           "полученное дерево балансируется и строится хеш-таблица из чисел файла. Выводятся на экран деревья и хеш-таблица.\n"
           "Осуществляется поиск введенного целого числа в двоичном дереве поиска, в сбалансированном дереве и в хеш-таблице.\n"
           "Считается среднее количество сравнений для поиска данных в указанных структурах.\n"
           "Производится реструктуризацию хеш-таблицы, если среднее количество сравнений больше указанного.\n"
           "Сравнивается время поиска, объем памяти и количество сравнений при использовании различных структур данных.\n");
    // запросили имя файла и открыли
    file_whoose(&file);
    // считали дерево из файла
    rc = tree_from_file(&Head_tree_ord, file, talk);
    if (rc == OK)
    {
        tree_print(Head_tree_ord, "visual_ord.gv");
        printf("Дерево считано из файла. Файл с представлением дерева создан.\n");
    }
    // сбалансировали дерево
    Head_tree_bal = balance_and_copy_tree(Head_tree_ord);
    if (Head_tree_bal != NULL)
    {
        tree_print(Head_tree_bal, "visual_bal.gv");
        printf("Дерево сбалансированно. Файл с представлением сбалансированного дерева создан.\n");
    }
    // считали хэш-таблицу с внутренним хэшированием из файла
    rc = ohash_create(START_SIZE_HASH, &Table_open);
    rc = ohash_from_file(&Table_open, file);
    if (rc == OK)
    {
        ohash_print(Table_open, "visual_hash_in.txt");
        printf("хэш-таблица с внутренним хэшированием считана из файла. Файл с представлением хэш-таблицы создан.\n");
    }
    // считали хэш-таблицу с внешним хэшированием из файла
    rc = chash_create(START_SIZE_HASH, &Table_close);
    rc = chash_from_file(&Table_close, file);
    if (rc == OK)
    {
        chash_print(Table_close, "visual_hash_out.txt");
        printf("хэш-таблица с внешним хэшированием считана из файла. Файл с представлением хэш-таблицы создан.\n");
    }
    while (user != 0)
    {
        if (user != ERROR_USER)
        {
            printf("\nМеню:\n");
            printf("1 - обойти дерево\n"
                   "2 - добавить новый элемент\n"
                   "3 - удалить элемент\n"
                   "4 - найти элемент\n"
                   "5 - определить количество узлов в дереве на каждом уровне\n"
                   "6 - добавить новый элемент в файл (во все структуры тоже добавится)\n"
                   "7 - выбрать новый файл для работы (все структуры тоже перезапишутся)\n"
                   "8 - вывести структуру\n"
                   "9 - cравнение эффективностей алгоритмов поиска\n"
                   "10 - посчитать среднее количество сравнений при поиске в разных структурах\n"
                   "11 - реструктурировать хэш-таблицу\n"
                   "0 - завершить выполнение программы\n"
                   "Введите цифру, соответствующую выбранному пункту меню: ");
        }
        if (scanf("%d", &user) != 1 || user < 0 || user > 11 || clean_buf() != 0)
        {
            printf("Ошибка ввода! Введите цифру от 0 до 11: ");
            user = ERROR_USER;
        }
        else if (user == 1) // обход и вывод дерева
        {
            int user2 = 0;
            struct Node *Head_tree = Head_tree_ord;
            printf("Введите 1, если хотите обойти сбалансированное дерево\n"
                   "(для несбалансированного дерева любой другой непробельный символ): ");
            if (scanf("%d", &user2) == 1 && user2 == 1 && clean_buf() == 0)
                Head_tree = Head_tree_bal;
            printf("Обход дерева:\n");
            if (Head_tree == NULL)
                printf("Дерево пустое.");
            else
                tree_traversal(Head_tree);
        }
        else if (user == 2) // добавление элемента
        {
            int num = 0;
            struct Node *Head_tree_tmp;
            int user2 = what_struct();
            printf("Введите элемент, который хотите добавить:\n");
            while (scanf("%d", &num) != 1)
                printf("Ошибка! Повторите ввод: ");
            if (user2 == 1)
            {
                Head_tree_tmp = tree_add_elem(Head_tree_ord, num, talk);
                if (Head_tree_tmp == NULL)
                    printf("Ошибка выделения памяти!\n");
                else
                    Head_tree_ord = Head_tree_tmp;
            }
            else if (user2 == 2)
            {
                Head_tree_tmp = bal_tree_add_elem(Head_tree_bal, num, talk);
                if (Head_tree_tmp == NULL)
                    printf("Ошибка выделения памяти!\n");
                else
                    Head_tree_bal = Head_tree_tmp;
            }
            else if (user2 == 3)
            {
                struct Hash_close *Table_ctmp = chash_add_elem(Table_close, num, 0);
                if (Table_ctmp == NULL)
                    printf("Ошибка выделения памяти!\n");
                else
                    Table_close = Table_ctmp;
            }
            else if (user2 == 4)
            {
                struct Hash_open *Table_otmp = ohash_add_elem(Table_open, num, 0);
                if (Table_otmp == NULL)
                    printf("Ошибка выделения памяти!\n");
                else
                    Table_open = Table_otmp;
            }
        }
        else if (user == 3) // удаление элемента
        {
            int num = 0;
            int user2 = what_struct();
            printf("Введите элемент, который хотите удалить:\n");
            while (scanf("%d", &num) != 1)
                printf("Ошибка! Повторите ввод: ");
            if (user2 == 1)
            {
                if (Head_tree_ord == NULL)
                    printf("Ошибка! Дерево пустое.");
                else
                {
                    int count;

                    if (tree_find_elem(Head_tree_ord, num, &count) == NULL)
                    {
                        rc = ERR_NO_ELEM;
                        printf("Ошибка удаления! Такого элемента нет в дереве.\n");
                    }
                    else
                    {
                        Head_tree_ord = tree_del_elem(Head_tree_ord, num);
                        printf("Удалили.\n");
                    }
                }
            }
            else if (user2 == 2)
            {
                if (Head_tree_bal == NULL)
                    printf("Ошибка! Дерево пустое.");
                else
                {
                    int count;
                    if (tree_find_elem(Head_tree_bal, num, &count) == NULL)
                    {
                        rc = ERR_NO_ELEM;
                        printf("Ошибка удаления! Такого элемента нет в дереве.\n");
                    }
                    else
                    {
                        Head_tree_bal = bal_tree_del_elem(Head_tree_bal, num);
                        printf("Удалили.\n");
                    }
                }
            }
            else if (user2 == 3)
                Table_close = chash_del_elem(Table_close, num);
            else if (user2 == 4)
                Table_open = ohash_del_elem(Table_open, num);
        }
        else if (user == 4) // поиск элемента
        {
            int user2 = what_struct();
            int count;
            int num = 0;
            struct Node *find_node;
            int *find_elem;
            printf("Введите элемент, который хотите найти:\n");
            while (scanf("%d", &num) != 1)
                printf("Ошибка! Повторите ввод: ");
            if (user2 == 1)
            {
                find_node = tree_find_elem(Head_tree_ord, num, &count);
                if (find_node == NULL)
                {
                    rc = ERR_NO_ELEM;
                    printf("Такого элемента нет.\n");
                }
                else
                    printf("Нашли элемент: %d.\n", find_node->data);
            }
            if (user2 == 2)
            {
                find_node = tree_find_elem(Head_tree_bal, num, &count);
                if (find_node == NULL)
                {
                    rc = ERR_NO_ELEM;
                    printf("Такого элемента нет.\n");
                }
                else
                    printf("Нашли элемент: %d.\n", find_node->data);
            }
            if (user2 == 3)
            {
                find_elem = chash_find_elem(Table_close, num, &count, talk);
                if (find_elem == NULL)
                {
                    rc = ERR_NO_ELEM;
                    printf("Такого элемента нет.\n");
                }
                else
                    printf("Нашли элемент: %d.\n", *find_elem);
            }
            if (user2 == 4)
            {
                find_elem = ohash_find_elem(Table_open, num, &count, talk);
                if (find_elem == NULL)
                {
                    rc = ERR_NO_ELEM;
                    printf("Такого элемента нет.\n");
                }
                else
                    printf("Нашли элемент: %d.\n", *find_elem);
            }
        }
        else if (user == 5) // определить количество узлов в дереве на каждом уровне
        {
            int user2 = 0;
            struct Node *Head_tree = Head_tree_ord;
            printf("Введите 1, если хотите посчитать для сбалансированного дерева\n"
                   "(для несбалансированного дерева любой другой непробельный символ): ");
            if (scanf("%d", &user2) == 1 && user2 == 1 && clean_buf() == 0)
                Head_tree = Head_tree_bal;
            if (Head_tree == NULL)
                printf("Дерево пустое.\n");
            else
                tree_level_node(Head_tree);
        }
        else if (user == 6) // добавить новый элемент в файл (+)
        {
            int num = 0;
            printf("Введите элемент, который хотите добавить:\n");
            while (scanf("%d", &num) != 1)
                printf("Ошибка! Повторите ввод: ");
            printf("Добавление в файл...\n");
            file_add_elem(file, num);
            printf("Добавление в дерево...\n");
            Head_tree_ord = tree_add_elem(Head_tree_ord, num, talk);
            printf("Добавление в сбалансированное дерево...\n");
            Head_tree_bal = bal_tree_add_elem(Head_tree_bal, num, talk);
            printf("Добавление в хэш-таблицу с внешним хэшированием...\n");
            Table_close = chash_add_elem(Table_close, num, 0);
            printf("Добавление в хэш-таблицу с внутренним хэшированием...\n");
            Table_open = ohash_add_elem(Table_open, num, 0);
        }
        else if (user == 7) // выбрать новый файл для работы (+)
        {
            file_whoose(&file);
            tree_free(&Head_tree_ord);
            tree_free(&Head_tree_bal);
            chash_free(&Table_close);
            ohash_free(&Table_open);
            chash_create(START_SIZE_HASH, &Table_close);
            ohash_create(START_SIZE_HASH, &Table_open);
            // считали дерево из файла
            rc = tree_from_file(&Head_tree_ord, file, talk);
            if (rc == OK)
            {
                tree_print(Head_tree_ord, "visual_ord.gv");
                printf("Дерево считано из файла. Файл с представлением дерева создан.\n");
            }
            // сбалансировали дерево
            Head_tree_bal = balance_and_copy_tree(Head_tree_ord);
            if (Head_tree_bal != NULL)
            {
                tree_print(Head_tree_bal, "visual_bal.gv");
                printf("Дерево сбалансированно. Файл с представлением сбалансированного дерева создан.\n");
            }
            // считали хэш-таблицу с внутренним хэшированием из файла
            rc = ohash_from_file(&Table_open, file);
            if (rc == OK)
            {
                ohash_print(Table_open, "visual_hash_in.txt");
                printf("хэш-таблица с внутренним хэшированием считана из файла. Файл с представлением хэш-таблицы создан.\n");
            }
            // считали хэш-таблицу с внешним хэшированием из файла
            rc = chash_from_file(&Table_close, file);
            if (rc == OK)
            {
                chash_print(Table_close, "visual_hash_out.txt");
                printf("хэш-таблица с внешним хэшированием считана из файла. Файл с представлением хэш-таблицы создан.\n");
            }
        }
        else if (user == 8) // вывести
        {
            tree_print(Head_tree_ord, "visual_ord.gv");
            tree_print(Head_tree_bal, "visual_bal.gv");
            chash_print(Table_close, "visual_hash_out.txt");
            ohash_print(Table_open, "visual_hash_in.txt");
            printf("Файлы с представлениями всех структур созданы.\n");
        }
        else if (user == 9) // Сравнивается эффективность поиска
        {
            build_res_find();
        }
        else if (user == 10) // посчитать среднее количество сравнений при поиске в разных структурах
        {
            printf("Среднее количество сравнений при поиске:\n");
            double count_tree_ord = tree_count_average_find(Head_tree_ord, file);
            printf("В обычном дереве = %lf\n", count_tree_ord);
            double count_tree_bal = tree_count_average_find(Head_tree_bal, file);
            printf("В сбалансированном дереве = %lf\n", count_tree_bal);
            double count_chash = chash_count_average_find(Table_close, file);
            printf("В хэш-таблице с внешним хэшированием = %lf\n", count_chash);
            double count_ohash = ohash_count_average_find(Table_open, file);
            printf("В хэш-таблице с внутренним хэшированием = %lf\n", count_ohash);
        }
        else if (user == 11) // реструктурировать хэш-таблицу
        {
            int user2;
            printf("Введите 1, если хотите реструктурировать хэш-таблицу с внешним хэшированием\n"
                   "(для хэш-таблицы с внутренним хэшированием любой другой непробельный символ): ");
            if (scanf("%d", &user2) == 1 && user2 == 1 && clean_buf() == 0)
                rc = chash_resize(&Table_close);
            else
                rc = ohash_resize(&Table_open);
            if (rc == ERR_MEM)
                printf("Ошибка выделения памяти! Реструктуризация прервана.\n");
            else
                printf("Хэш-таблица реструктурирована.\n");
        }
        else if (user == 0)
            printf("Завершение работы ^-^\n");
    }
    fclose(file);
    tree_free(&Head_tree_ord);
    tree_free(&Head_tree_bal);
    chash_free(&Table_close);
    ohash_free(&Table_open);
    return rc;
}
