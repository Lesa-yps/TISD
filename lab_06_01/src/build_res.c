#include "build_res.h"

#define SIZE_OF_BUF 100

// выигрыш от 2 в процентах
char *perc_double(double time1, double time2, char buffer[])
{
    memset(buffer, '\0', SIZE_OF_BUF * sizeof(char));  // Заполняем буфер
    if (diff_time(time2, 0) != 0)
        sprintf(buffer, "%f", fabs(time1 * 100.0 / time2 - 100.0));
    else if (diff_time(time1, 0) != 0)
        sprintf(buffer, "%f", fabs(time2 * 100.0 / time1 - 100.0));
    else
        sprintf(buffer, "%f", 0.0);
    return buffer;
}
char *perc_int(int time1, int time2, char buffer[])
{
    memset(buffer, '\0', SIZE_OF_BUF * sizeof(char));  // Заполняем буфер
    if (diff_time(time2, 0) != 0)
        sprintf(buffer, "%f", fabs(time1 * 100.0 / time2 - 100.0));
    else if (diff_time(time1, 0) != 0)
        sprintf(buffer, "%f", fabs(time2 * 100.0 / time1 - 100.0));
    else
        sprintf(buffer, "%f", 0.0);
    return buffer;
}

// Сравнивается эффективность алгоритмов добавления чисел в файл и в дерево
int build_res_add(void)
{
    printf("Результат сравнения функций добавления в дерево и в файл:\n");
    int rc = OK;
    ft_table_t *table = ft_create_table();

    char buffer[SIZE_OF_BUF];

    //общее время моделирования
    double time_add_file = 0.0;
    double time_add_tree = 0.0;

    char teor_all_time_static_c[SIZE_OF_BUF];
    char teor_all_time_dinam_c[SIZE_OF_BUF];
    //количество вошедших в систему заявок
    char app_come_static_c[SIZE_OF_BUF];
    char app_come_dinam_c[SIZE_OF_BUF];
    //количество вышедших из системы заявок
    char app_away_static_c[SIZE_OF_BUF];
    char app_away_dinam_c[SIZE_OF_BUF];
    //количествo срабатываний ОА
    char count_work_AO_static_c[SIZE_OF_BUF];
    char count_work_AO_dinam_c[SIZE_OF_BUF];
    //время простоя аппарата
    char stay_time_AO_static_c[SIZE_OF_BUF];
    char stay_time_AO_dinam_c[SIZE_OF_BUF];
    //практическое время работы аппарата
    char work_time_AO_static_c[SIZE_OF_BUF];
    char work_time_AO_dinam_c[SIZE_OF_BUF];
    //теоретическое время работы аппарата
    char teor_all_time_AO_static_c[SIZE_OF_BUF];
    char teor_all_time_AO_dinam_c[SIZE_OF_BUF];
    //погрешность
    char err_all_time_AO_static_c[SIZE_OF_BUF];
    char err_all_time_AO_dinam_c[SIZE_OF_BUF];

    struct Inf_oueue infa_q1;
    struct AO ao1;

    int mem_static = (int) (sizeof(struct Applic) + sizeof(struct Applic*)) * (MAX_COUNT_APP) + sizeof(struct Applic*) * 3;
    int mem_dinam = (int) (sizeof(struct Applic) + sizeof(struct Node*)) * (MAX_COUNT_APP) + sizeof(struct Applic*) * 3 + sizeof(struct Node*) * 2;
    char perc_mem[SIZE_OF_BUF];
    sprintf(perc_mem, "%.2f%%", fabs(mem_static * 100.0 / mem_dinam - 100.0));

    // прогон симуляции со статическим массивом
    for (int i = 0; i < COUNT_SORT; i++)
    {
        rc = simulate_stat(0, 0, min_time_come, max_time_come, min_time_work, max_time_work, &infa_q1, &ao1);
        if (rc == ERROR)
            return rc;
        
    }
    sprintf(teor_all_time_AO_static_c, "%f", teor_all_time_AO_static / COUNT_SORT);

    // прогон симуляции с односвязным списком
    for (int i = 0; i < COUNT_SORT; i++)
    {
        rc = simulate_dinam(0, 0, min_time_come, max_time_come, min_time_work, max_time_work, &infa_q1, &ao1);
        if (rc == ERROR)
            return rc;
    }
    sprintf(teor_all_time_dinam_c, "%f", teor_all_time_dinam / COUNT_SORT);


    printf("    Результаты сравнения разных симуляций (время в единицах времени, память в байтах):\n");
    ft_u8write_ln(table, "?", "статический массив", "односвязный список", "%");
    ft_u8write_ln(table, "Время работы АО", work_time_AO_static_c, work_time_AO_dinam_c, perc_double(work_time_AO_static, work_time_AO_dinam, buffer));
    ft_u8write_ln(table, "Количество вошедших заявок", app_come_static_c, app_come_dinam_c, perc_int(app_come_static, app_come_dinam, buffer));
    ft_u8write_ln(table, "Количество вышедших заявок", app_away_static_c, app_away_dinam_c, perc_int(app_away_static, app_away_dinam, buffer));
    ft_u8write_ln(table, "Количество срабатываний АО", count_work_AO_static_c, count_work_AO_dinam_c, perc_int(count_work_AO_static, count_work_AO_dinam, buffer));
    ft_u8write_ln(table, "Время простоя", stay_time_AO_static_c, stay_time_AO_dinam_c, perc_double(stay_time_AO_static, stay_time_AO_dinam, buffer));
    ft_u8write_ln(table, "Практическое время моделирования", teor_all_time_static_c, teor_all_time_dinam_c, perc_double(teor_all_time_static, teor_all_time_dinam, buffer));
    ft_u8write_ln(table, "Теоретическое время моделирования", teor_all_time_AO_static_c, teor_all_time_AO_dinam_c, perc_double(teor_all_time_AO_static, teor_all_time_AO_dinam, buffer));
    ft_u8write_ln(table, "Погрешность (%)", err_all_time_AO_static_c, err_all_time_AO_dinam_c, perc_double(err_all_time_AO_static, err_all_time_AO_dinam, buffer));

    ft_set_border_style(table, FT_NICE_STYLE);
    ft_set_cell_prop(table, FT_ANY_ROW, 0, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 1, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_LEFT);
    ft_set_cell_prop(table, FT_ANY_ROW, 2, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_LEFT);
    ft_set_cell_prop(table, FT_ANY_ROW, 3, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_LEFT);
    ft_set_cell_prop(table, FT_ANY_ROW, 4, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_LEFT);
    ft_set_cell_prop(table, FT_ANY_ROW, 5, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_LEFT);
    ft_set_cell_prop(table, FT_ANY_ROW, 6, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_LEFT);
    ft_set_cell_prop(table, FT_ANY_ROW, 7, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_LEFT);
    ft_set_cell_prop(table, FT_ANY_ROW, 8, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_LEFT);
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

    printf("%s\n", ft_to_string(table));
    ft_destroy_table(table);
    return rc;
}


// Сравнивается эффективность поиска в зависимости от высоты деревьев и степени их ветвления
void build_res_find(void);