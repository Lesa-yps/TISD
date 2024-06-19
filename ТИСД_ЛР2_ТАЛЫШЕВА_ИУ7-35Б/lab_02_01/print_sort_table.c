#include "print_sort_table.h"

void print_sort_table(struct Book books[], struct Book_key book_keys[], int n, int sort)
{
    ft_table_t *table = ft_create_table();

    if (sort)
    {
        sort_simple_book(books, n);
        for (int i = 0; i < n; i++)
            (book_keys[i]).start_ind = i;
    }
    printf("Результат:\n");
    ft_u8write_ln(table, "фамилия\n автора", "название\n книги", "издательство", "кол-во\n страниц", "вид \nлит-ры", "отрасль(1)", "место \nиздания(1)", "год \nиздания(1)", "жанр(2)", "мин \nвозраст(3)", "сказки/\nстихи(3)");
    for (int i = 0; i < n; i++)
        print_table_struct(books[i], table, i);

    ft_set_border_style(table, FT_NICE_STYLE);
    ft_set_cell_prop(table, FT_ANY_ROW, 0, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

    printf("%s\n", ft_to_string(table));
    ft_destroy_table(table);
}
