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

int build_res(double min_time_come, double max_time_come, double min_time_work, double max_time_work)
{
    int rc = OK;
    ft_table_t *table = ft_create_table();

    char buffer[SIZE_OF_BUF];

    //общее время моделирования
    double teor_all_time_static = 0.0;
    double teor_all_time_dinam = 0.0;
    //количество вошедших в систему заявок
    int app_come_static = 0;
    int app_come_dinam = 0;
    //количество вышедших из системы заявок
    int app_away_static = 0;
    int app_away_dinam = 0;
    //количествo срабатываний ОА
    int count_work_AO_static = 0;
    int count_work_AO_dinam = 0;
    //время простоя аппарата
    double stay_time_AO_static = 0.0;
    double stay_time_AO_dinam = 0.0;
    //практическое время работы аппарата
    double work_time_AO_static = 0.0;
    double work_time_AO_dinam = 0.0;
    //теоретическое время работы аппарата
    double teor_all_time_AO_static = 0.0;
    double teor_all_time_AO_dinam = 0.0;
    //погрешность
    double err_all_time_AO_static = 0.0;
    double err_all_time_AO_dinam = 0.0;

    double one_teor_all_time_AO = 0.0;

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
        //общее время моделирования
        teor_all_time_static += infa_q1.time_sim;
        //количество вошедших в систему заявок
        app_come_static += infa_q1.count_come_app;
        //количество вышедших из системы заявок
        app_away_static += infa_q1.count_away_app;
        //количествo срабатываний ОА
        count_work_AO_static += ao1.count_work;
        //время простоя аппарата
        stay_time_AO_static += ao1.time_stay;
        //практическое время работы аппарата
        work_time_AO_static += (infa_q1.time_sim - ao1.time_stay);
        //погрешность
        err_all_time_AO_static += err_time_work_AO(min_time_come, max_time_come, min_time_work, max_time_work, &one_teor_all_time_AO,\
                                                    infa_q1.time_sim);
        //теоретическое время работы аппарата
        teor_all_time_AO_static += one_teor_all_time_AO;
    }
    sprintf(teor_all_time_static_c, "%f", teor_all_time_static / COUNT_SORT);
    sprintf(app_come_static_c, "%d", app_come_static / COUNT_SORT);
    sprintf(app_away_static_c, "%d", app_away_static / COUNT_SORT);
    sprintf(count_work_AO_static_c, "%d", count_work_AO_static / COUNT_SORT);
    sprintf(stay_time_AO_static_c, "%f", stay_time_AO_static / COUNT_SORT);
    sprintf(work_time_AO_static_c, "%f", work_time_AO_static / COUNT_SORT);
    sprintf(err_all_time_AO_static_c, "%f", err_all_time_AO_static / COUNT_SORT);
    sprintf(teor_all_time_AO_static_c, "%f", teor_all_time_AO_static / COUNT_SORT);

    // прогон симуляции с односвязным списком
    for (int i = 0; i < COUNT_SORT; i++)
    {
        rc = simulate_dinam(0, 0, min_time_come, max_time_come, min_time_work, max_time_work, &infa_q1, &ao1);
        if (rc == ERROR)
            return rc;
        //общее время моделирования
        teor_all_time_dinam += infa_q1.time_sim;
        //количество вошедших в систему заявок
        app_come_dinam += infa_q1.count_come_app;
        //количество вышедших из системы заявок
        app_away_dinam += infa_q1.count_away_app;
        //количествo срабатываний ОА
        count_work_AO_dinam += ao1.count_work;
        //время простоя аппарата
        stay_time_AO_dinam += ao1.time_stay;
        //практическое время работы аппарата
        work_time_AO_dinam += (infa_q1.time_sim - ao1.time_stay);
        //погрешность
        err_all_time_AO_dinam += err_time_work_AO(min_time_come, max_time_come, min_time_work, max_time_work, &one_teor_all_time_AO,\
                                                    infa_q1.time_sim);
        //теоретическое время работы аппарата
        teor_all_time_AO_dinam += one_teor_all_time_AO;
    }
    sprintf(teor_all_time_dinam_c, "%f", teor_all_time_dinam / COUNT_SORT);
    sprintf(app_come_dinam_c, "%d", app_come_dinam / COUNT_SORT);
    sprintf(app_away_dinam_c, "%d", app_away_dinam / COUNT_SORT);
    sprintf(count_work_AO_dinam_c, "%d", count_work_AO_dinam / COUNT_SORT);
    sprintf(stay_time_AO_dinam_c, "%f", stay_time_AO_dinam / COUNT_SORT);
    sprintf(work_time_AO_dinam_c, "%f", work_time_AO_dinam / COUNT_SORT);
    sprintf(err_all_time_AO_dinam_c, "%f", err_all_time_AO_dinam / COUNT_SORT);
    sprintf(teor_all_time_AO_dinam_c, "%f", teor_all_time_AO_dinam / COUNT_SORT);


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
