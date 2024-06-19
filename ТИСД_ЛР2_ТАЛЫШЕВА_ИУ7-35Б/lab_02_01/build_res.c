#include "build_res.h"

void made_copy_books(const struct Book books[], struct Book books_copy[], int n);

void made_copy_keys(const struct Book_key book_keys[], struct Book_key keys_copy[], int n);

char *int_to_str(double num, char buffer[])
{
    memset(buffer, '\0', SIZE_OF_BUF * sizeof(char));  // Заполняем буфер
    sprintf(buffer, "%f", num);
    return buffer;
}

// выигрыш от таблицы ключей в процентах
double perc(double time_book, double time_key);

void build_res(struct Book books[], struct Book_key book_keys[], int n)
{
    ft_table_t *table = ft_create_table();

    char buffer[SIZE_OF_BUF];

    double time_book_simple = 0.0;
    double time_book_quick = 0.0;
    double time_key_simple = 0.0;
    double time_key_quick = 0.0;
    double time_start = 0.0;

    char time_book_s[SIZE_OF_BUF];
    char time_book_q[SIZE_OF_BUF];
    char time_key_s[SIZE_OF_BUF];
    char time_key_q[SIZE_OF_BUF];

    char perc_s[SIZE_OF_BUF];
    char perc_q[SIZE_OF_BUF];
    char perc_mem[SIZE_OF_BUF];

    struct Book books_copy[MAX_COUNT];
    struct Book_key keys_copy[MAX_COUNT];

    for (int i = 0; i < COUNT_SORT; i++)
    {
        made_copy_books(books, books_copy, n);
        time_start = clock();
        sort_simple_book(books_copy, n);
        time_book_simple += clock() - time_start;
    }

    for (int i = 0; i < COUNT_SORT; i++)
    {
        made_copy_books(books, books_copy, n);
        time_start = clock();
        sort_rec_book(books_copy, 0, n - 1);
        time_book_quick += clock() - time_start;
    }

    for (int i = 0; i < COUNT_SORT; i++)
    {
        made_copy_keys(book_keys, keys_copy, n);
        time_start = clock();
        sort_simple_key(keys_copy, n);
        time_key_simple += clock() - time_start;
    }

    for (int i = 0; i < COUNT_SORT; i++)
    {
        made_copy_keys(book_keys, keys_copy, n);
        time_start = clock();
        sort_rec_key(keys_copy, 0, n - 1);
        time_key_quick += clock() - time_start;
    }

    time_book_simple /= COUNT_SORT;
    time_book_quick /= COUNT_SORT;
    time_key_simple /= COUNT_SORT;
    time_key_quick /= COUNT_SORT;

    sprintf(time_book_s, "%f", time_book_simple);
    sprintf(time_book_q, "%f", time_book_quick);
    sprintf(time_key_s, "%f", time_key_simple);
    sprintf(time_key_q, "%f", time_key_quick);

    sprintf(perc_s, "%.2f%%", perc(time_book_simple, time_key_simple));
    sprintf(perc_q, "%.2f%%", perc(time_book_quick, time_key_quick));
    sprintf(perc_mem, "%.2f%%", perc(sizeof(struct Book) * n, (sizeof(struct Book) + sizeof(struct Book_key)) * n));

    printf("Результаты сравнения разных сортировок (время в тактах процессора, память в байтах):\n");
    ft_u8write_ln(table, "таблица", "сортировка выбором", "рекурсивная сортировка", "занимаемая память");
    ft_u8write_ln(table, "исходная таблица", time_book_s, time_book_q, int_to_str(sizeof(struct Book) * n, buffer));
    ft_u8write_ln(table, "таблица ключей", time_key_s, time_key_q, int_to_str((sizeof(struct Book) + sizeof(struct Book_key)) * n, buffer));
    ft_u8write_ln(table, "выигрыш от таблицы\nключей в процентах", perc_s, perc_q, perc_mem);

    ft_set_border_style(table, FT_NICE_STYLE);
    ft_set_cell_prop(table, FT_ANY_ROW, 0, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 1, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_LEFT);
    ft_set_cell_prop(table, FT_ANY_ROW, 2, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_LEFT);
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

    printf("%s\n", ft_to_string(table));
    ft_destroy_table(table);
}

void made_copy_books(const struct Book books[], struct Book books_copy[], int n)
{
    for (int i = 0; i < n; i++)
        books_copy[i] = books[i];
}

void made_copy_keys(const struct Book_key book_keys[], struct Book_key keys_copy[], int n)
{
    for (int i = 0; i < n; i++)
        keys_copy[i] = book_keys[i];
}

// выигрыш от таблицы ключей в процентах
double perc(double time_book, double time_key)
{
    return time_book * 100 / time_key - 100;
}
