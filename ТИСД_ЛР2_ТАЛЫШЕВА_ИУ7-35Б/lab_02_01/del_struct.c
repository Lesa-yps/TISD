#include "del_struct.h"

int del_struct(wchar_t strk[], struct Book books[], struct Book_key book_keys[], int *n)
{
    if (*n == MIN_COUNT)
    {
        printf("Невозможно удалить поле. Программа работает с таблицами больше или равно %d записей\n", MIN_COUNT);
        return ERROR;
    }
    int rc = OK;
    FILE *file;
    ft_table_t *table = ft_create_table();
    int ind_del = -1;
    int lists_del;
    char mbs[MAX_LEN + 1];
    wcsrtombs(mbs, (const wchar_t **)&strk, sizeof(mbs), NULL);
    while ((file = fopen(mbs, "w")) == NULL)
    {
        printf("Ошибка открытия файла на запись. Пожалуйста, попробуйте ввести путь к файлу снова.\n");
        ask_file(strk, "w");
    }
    printf("Введите количество страниц в книге [1; %d]: ", MAX_LISTS);
    while ((read_int(stdin, &lists_del) != OK) || lists_del < 1 || lists_del > MAX_LISTS)
    {
        printf("Ошибка ввода количества страниц. Попробуйте ввести снова [1; %d]: ", MAX_LISTS);
        //функция чистит буфер
        clean_buf();
    }
    for (int i = 0; (i < (*n)) && (ind_del == -1); i++)
        if ((books[i]).lists == lists_del)
            ind_del = i;
    if (ind_del == -1)
    {
        printf("Запись с таким значением поля отсутствует.\n");
        rc = MY_ERROR;
    }
    else
    {
        printf("Удаляемая запись:\n");
        ft_u8write_ln(table, "фамилия\n автора", "название\n книги", "издательство", "кол-во\n страниц", "вид \nлит-ры", "отрасль(1)", "место \nиздания(1)", "год \nиздания(1)", "жанр(2)", "мин \nвозраст(3)", "сказки/\nстихи(3)");
        print_table_struct(books[ind_del], table, 1);
        ft_set_border_style(table, FT_NICE_STYLE);
        ft_set_cell_prop(table, FT_ANY_ROW, 0, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
        ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
        printf("%s\n", ft_to_string(table));
        ft_destroy_table(table);

        for (int i = ind_del; i < ((*n) - 1); i++)
        {
            books[i] = books[i + 1];
            book_keys[i] = book_keys[i + 1];
        }
        (*n)--;
    }
    for (int i = 0; i < (*n); i++)
        print_struct(books[i], file);
    fclose(file);
    if (ind_del != -1)
        printf("Запись удалена.\n");
    return rc;
}
