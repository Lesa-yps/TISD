#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <unistd.h>
#include "fort.h"

// модули
#include "const_struct.h"

#include "asc_file.h"
#include "read_file.h"

#include "sort_file.h"
#include "add_struct.h"
#include "del_struct.h"
#include "find_roma.h"
#include "print_sort_keys.h"
#include "print_sort_table.h"
#include "print_sort_table_help_key.h"
#include "build_res.h"

//интерфейс
int main(void)
{
    // Устанавливаем локаль для русского языка
    setlocale(LC_ALL, "ru_RU.UTF-8");
    ft_table_t *table = ft_create_table();
    //что выбрал пользватель в меню
    int user = 0;
    //код возврата
    int rc = OK;
    //файловая переменная
    wchar_t strk[MAX_LEN + 1];
    //количество записей
    int n;
    //полная таблица структур
    struct Book books[MAX_COUNT];
    //таблица ключей-структур
    struct Book_key book_keys[MAX_COUNT];
    //приветствие + условие задачи
    printf("   Приветствую, пользователь!\n\
Программа обрабатывает таблицу (список литературы [40, 100]) из файла, вида:\n");
    ft_u8write_ln(table, "фамилия\n автора", "название\n книги", "издательство", "кол-во\n страниц", "вид \nлит-ры", "отрасль(1)", "место \nиздания(1)", "год \nиздания(1)", "жанр(2)", "мин \nвозраст(3)", "сказки/\nстихи(3)");
    ft_u8write_ln(table, "max 25 сим", "max 25 сим", "max 25 сим", "[1; 2 млрд]", "1 - техническая\n2 - художественная\n3 - детская", "max 25 сим", "отечественная/\nпереводная", "[0, 1 млн]", "роман/\nпьеса/\nпоэзия", "до 17 лет", "сказки/\nстихи");

    ft_set_border_style(table, FT_NICE_STYLE);
    ft_set_cell_prop(table, FT_ANY_ROW, 0, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 1, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

    printf("%s\n", ft_to_string(table));
    ft_destroy_table(table);

    //пока не прочитает нормальный файл, будет просить ввести
    ask_file(strk, "r");
    // чтение файла
    while (1)
    {
        if (read_file(strk, &n, books, book_keys) == ERROR)
            printf("Ошибка чтения списка из файла. Попробуйте ввести путь к файлу снова.\n");
        else if (n < MIN_COUNT)
            printf("Ошибка: в файле слишком мало записей %d (должно быть минимум %d). Попробуйте ввести путь к файлу снова.\n", n, MIN_COUNT);
        else if (n > MAX_COUNT)
            printf("Ошибка: в файле слишком много записей %d (должно быть максимум %d). Попробуйте ввести путь к файлу снова.\n", n, MAX_COUNT);
        else
            break;
        ask_file(strk, "r");
    }
    //пока пользователь не выбрал выход из программы(9) цикл выполняется
    while (user != 11)
    {
        //менюшка
        printf("\nМеню:\n\
               1) упорядочить данные в файле по возрастанию количества страниц\n\
               2) добавить записи в конец списка;\n\
               3) удалить записи по количеству страниц;\n\
               4) найти все романы указанного пользователем автора;\n\
               5) вывод отсортированной таблицы ключей при несортированной исходной таблице;\n\
               6) вывод упорядоченной исходной таблицы;\n\
               7) вывод исходной таблицы в упорядоченном виде, используя упорядоченную таблицу ключей;\n\
               8) вывод исходной таблицы;\n\
               9) вывод таблицы ключей;\n\
               10) вывод таблицы результатов сравнения эффективности работы программы при\n\
                обработке данных в исходной таблице и в таблице ключей\n\
                и при использовании различных алгоритмов сортировок;\n\
               11) выход из программы.\n\
Введите выбранный пункт меню: ");
        //ввод выбранного пользователем пункта меню и его проверка
        if (read_int(stdin, &user) != OK || user < 1 || user > 11)
        {
             printf("Ошибка ввода. Пожалуйста, попробуйте ввести снова.\n");
             user = 0;
             continue;
        }
        //если 1 вызываем функцию сортировки данных в файле
        if (user == 1)
            sort_file(strk, books, book_keys, n);
        //если 2 вызываем функцию добавления записи в конец таблицы
        else if (user == 2)
            rc = add_struct(strk, books, book_keys, &n);
        //если 3 вызываем функцию удаления записи по полю
        else if (user == 3)
            rc = del_struct(strk, books, book_keys, &n);
        //если 4 вызываем функцию поиска всех романов автора
        else if (user == 4)
             rc = find_roma(books, n);
        //если 5 вызываем функцию вывода отсортированной таблицы ключей
        else if (user == 5)
             print_sort_keys(book_keys, n, 1);
        //если 6 вызываем функцию вывода упорядоченной исходной таблицы
        else if (user == 6)
             print_sort_table(books, book_keys, n, 1);
        //если 7 вызываем функцию вывода упорядоченной исходной таблицы, используя упорядоченную таблицу ключей
        else if (user == 7)
             print_sort_table_help_key(books, book_keys, n);
        //если 8 вызываем функцию вывода исходной таблицы
        else if (user == 8)
             print_sort_table(books, book_keys, n, 0);
        //если 9 вызываем функцию вывода таблицы ключей
        else if (user == 9)
             print_sort_keys(book_keys, n, 0);
        //если 10 вызываем функцию вывода таблицы сравнения разных сортировок
        else if (user == 10)
             build_res(books, book_keys, n);
        //иначе(11) завершение цикла
        else
             printf("Завершение работы ^-^\n");
    }
    //возврат кода ошибки
    return rc;
}
