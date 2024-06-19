#include "print_table_struct.h"

void print_table_struct(struct Book book, ft_table_t *table, int ind)
{
    char list[SIZE_OF_BUF];
    char varik[SIZE_OF_BUF];
    char year[SIZE_OF_BUF];
    char mini[SIZE_OF_BUF];
    char autor[SIZE_OF_BUF * 7];
    char name[SIZE_OF_BUF * 7];
    char mader[SIZE_OF_BUF * 7];
    char otrasl[SIZE_OF_BUF * 7];
    char where[SIZE_OF_BUF * 7];
    char draw[SIZE_OF_BUF * 7];
    char what[SIZE_OF_BUF * 7];
    sprintf(autor, "%ls", book.surname);
    //printf("%ls %s\n", book.surname, autor);
    sprintf(name, "%ls", book.name_book);
    sprintf(mader, "%ls", book.mader);
    sprintf(list, "%d", book.lists);
    sprintf(varik, "%d", book.variant);
    if (book.variant == 1)
    {
        sprintf(year, "%d", book.unic.texnic.year);
        sprintf(otrasl, "%ls", book.unic.texnic.otrasl);
        sprintf(where, "%ls", book.unic.texnic.where);
        ft_u8write_ln(table, autor, name, mader, list, varik, otrasl, where, year, "-", "-", "-");
    }
    else if (book.variant == 2)
    {
        sprintf(draw, "%ls", book.unic.draw);
        ft_u8write_ln(table, autor, name, mader, list, varik, "-", "-", "-", draw, "-", "-");
    }
    else
    {
        sprintf(mini, "%d", book.unic.child.min_year);
        sprintf(what, "%ls", book.unic.child.what);
        ft_u8write_ln(table, autor, name,mader, list, varik, "-", "-", "-", "-", mini, what);
    }
    //ft_u8write_ln(table, "фамилия\n автора", "название\n книги", "издательство", "кол-во\n страниц", "вид \nлит-ры", "отрасль(1)", "место \nиздания(1)", "год \nиздания(1)", "жанр(2)", "мин \nвозраст(3)", "сказки/\nстихи(3)");
    //ft_set_border_style(table, FT_NICE_STYLE);
    //ft_set_cell_prop(table, FT_ANY_ROW, 0, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, ind, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    //ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

    //printf("%s\n", ft_to_string(table));
    //ft_destroy_table(table);
}
