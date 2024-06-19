#include "find_roma.h"

int find_roma(struct Book books[], int n)
{
    ft_table_t *table = ft_create_table();
    //результат
    int count = 0;
    //код ошибки
    int rc = OK;
    wchar_t roma[MAX_LEN + 1];

    printf("Введите автора романа (максимально %d символов): ", MAX_LEN);
    read_str(roma, MAX_LEN);

    printf("Результат:\n");

    for (int i = 0; i < n; i++)
        if ((books[i]).variant == 2)
            //если нашли элемент, возвращаем его индекс
            if ((wcscmp(roma, (books[i]).surname) == 0) && (wcscmp(L"роман", ((books[i]).unic).draw) == 0))
            { 
                if (! count)
                    ft_u8write_ln(table, "фамилия\n автора", "название\n книги", "издательство", "кол-во\n страниц", "вид \nлит-ры", "отрасль(1)", "место \nиздания(1)", "год \nиздания(1)", "жанр(2)", "мин \nвозраст(3)", "сказки/\nстихи(3)");
                print_table_struct(books[i], table, count);
                count++;
            }
    ft_set_border_style(table, FT_NICE_STYLE);
    ft_set_cell_prop(table, FT_ANY_ROW, 0, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    printf("%s\n", ft_to_string(table));
    ft_destroy_table(table);

    // искомого элемента нет
    if (count == 0)
    {
        printf("Романы этого автора не найдены.\n");
        rc = MY_ERROR;
    }
    //возврат кода ошибки
    return rc;
}
