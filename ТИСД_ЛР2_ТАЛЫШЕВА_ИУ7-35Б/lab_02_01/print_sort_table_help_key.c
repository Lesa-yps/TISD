#include "print_sort_table_help_key.h"

void print_sort_table_help_key(struct Book books[], struct Book_key book_keys[], int n)
{
    ft_table_t *table = ft_create_table();
    sort_simple_key(book_keys, n);
    printf("Результат:\n");
    ft_u8write_ln(table, "фамилия\n автора", "название\n книги", "издательство", "кол-во\n страниц", "вид \nлит-ры", "отрасль(1)", "место \nиздания(1)", "год \nиздания(1)", "жанр(2)", "мин \nвозраст(3)", "сказки/\nстихи(3)");
    for (int i = 0; i < n; i++)
    {
        //printf("%d %d %d\n", i, (book_keys[i]).start_ind, (book_keys[i]).lists);
        print_table_struct(books[(book_keys[i]).start_ind], table, i);
    }

    ft_set_border_style(table, FT_NICE_STYLE);
    ft_set_cell_prop(table, FT_ANY_ROW, 0, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

    printf("%s\n", ft_to_string(table));
    ft_destroy_table(table);
}
