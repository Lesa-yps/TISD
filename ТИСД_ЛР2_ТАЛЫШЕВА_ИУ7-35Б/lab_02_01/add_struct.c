#include "add_struct.h"

int add_struct(wchar_t strk[], struct Book books[], struct Book_key book_keys[], int *n)
{
    FILE *file;
    int rc = OK;
    ft_table_t *table = ft_create_table();
    char mbs[MAX_LEN + 1];
    wcsrtombs(mbs, (const wchar_t **)&strk, sizeof(mbs), NULL);
    if (*n == MAX_COUNT)
    {
        printf("В файле уже максимальное количество записей (%d). Добавление невозможно.\n", MAX_COUNT);
        rc = ERROR;
    }
    else
    {
        while ((file = fopen(mbs, "a")) == NULL)
        {
            printf("Ошибка открытия файла на дозапись. Пожалуйста, попробуйте ввести путь к файлу снова.\n");
            ask_file(strk, "a");
        }
        read_struct(books, book_keys, n);
        printf("Получившаяся запись:\n");
        ft_u8write_ln(table, "фамилия\n автора", "название\n книги", "издательство", "кол-во\n страниц", "вид \nлит-ры", "отрасль(1)", "место \nиздания(1)", "год \nиздания(1)", "жанр(2)", "мин \nвозраст(3)", "сказки/\nстихи(3)");
        print_table_struct(books[*n - 1], table, 1);
        ft_set_border_style(table, FT_NICE_STYLE);
        ft_set_cell_prop(table, FT_ANY_ROW, 0, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
        ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
        printf("%s\n", ft_to_string(table));
        ft_destroy_table(table);

        print_struct(books[*n - 1], file);
        fclose(file);
        printf("Запись добавлена.\n");
    }
    return rc;
}
