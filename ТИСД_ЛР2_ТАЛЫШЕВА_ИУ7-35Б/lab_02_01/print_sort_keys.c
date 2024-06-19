#include "print_sort_keys.h"

void print_sort_keys(struct Book_key book_keys[], int n, int sort)
{
    ft_table_t *table = ft_create_table();
    char ind[SIZE_OF_BUF];
    char list[SIZE_OF_BUF];

    if (sort)
        sort_simple_key(book_keys, n);
    printf("Результат:\n");
    ft_u8write_ln(table, "индекс основной таблицы", "количество страниц");
    for (int i = 0; i < n; i++)
    {
        sprintf(list, "%d", (book_keys[i]).lists);
        sprintf(ind, "%d", (book_keys[i]).start_ind);
        ft_u8write_ln(table, ind, list);
    }

    ft_set_border_style(table, FT_NICE_STYLE);
    ft_set_cell_prop(table, FT_ANY_ROW, 0, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 1, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

    printf("%s\n", ft_to_string(table));
    ft_destroy_table(table);
}
