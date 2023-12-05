#include "simulate_stat.h"

struct Applic* pop_stat(struct Applic* Queue[], struct Inf_oueue *infa_q1);
// добавляем пришедшую заявку в очередь
int push_stat(struct Inf_oueue *infa_q1, struct Applic **Queue, struct Applic *app1);

void free_one_stat(struct Applic *app_del);
void free_queue_stat(struct Applic *Queue[], int len);

int simulate_stat(int talk, int own, double min_time_come, double max_time_come, double min_time_work, double max_time_work,\
                  struct Inf_oueue *infa_q1, struct AO *ao1)
{
    double rc;
    // создать массив - очередь
    struct Applic *Queue[MAX_COUNT_APP];
    for (int i = 0; i < MAX_COUNT_APP; i++)
        Queue[i] = NULL;
    double time_minus = 0;
    zero_all(infa_q1, ao1);
    double time_come_app = 0;
    double time_work_app = 0;
    struct Applic *app_now = NULL;
    struct Applic *app_now_old = NULL;
    // идем за новой заявкой
    struct Applic *app_come;
    if (hat_for_get(&time_come_app, &app_come, min_time_come, max_time_come, min_time_work, max_time_work))
        return ERROR;
    // пока количество обработанных заявок меньше MAX_COUNT_APP
    while (infa_q1->count_away_app < MAX_COUNT_APP)
    {
        // если время прихода новой заявки кончилось
        if ((diff_time(time_come_app, 0) <= 0) && (app_come != NULL))
        {
            // добавляем пришедшую заявку в очередь
            if (push_stat(infa_q1, Queue, app_come) == ERROR)
            {
                free_queue_stat(Queue, infa_q1->len_q_now);
                return ERROR;
            }
            if (app_come->count_work == 0)
            {
                print_ptr("добавляем", app_come, talk);
            }
            // идем за новой заявкой
            if (hat_for_get(&time_come_app, &app_come, min_time_come, max_time_come, min_time_work, max_time_work))
            {
                free_queue_stat(Queue, infa_q1->len_q_now);
                return ERROR;
            }
        }
        // если АО не занят
        if (diff_time(time_work_app, 0) <= 0 && infa_q1->len_q_now > 0)
        {
            if (app_now_old != app_now)
            {
                app_now_old = app_now;
                // добавляем пришедшую заявку в очередь
                if (app_now_old != NULL)
                {
                    if (app_now_old->count_work < MAX_COUNT_WORK1)
                    {
                        if (push_stat(infa_q1, Queue, app_now_old) == ERROR)
                        {
                            free_queue_stat(Queue, infa_q1->len_q_now);
                            return ERROR;
                        }
                    }
                    else
                        free_one_stat(app_now_old);
                }
            }
            app_now = pop_stat(Queue, infa_q1);
            time_work_app = app_now->time_work;
            app_now->count_work++;
            ao1->count_work += 1;
            // если количество заявок кратно REPORT_COUNT_APP и больше нуля выводим информацию
            if (ao1->count_work % REPORT_COUNT_APP == 0 && ao1->count_work > 0 && own)
                report_part_work(*infa_q1);
            if (app_now->count_work == MAX_COUNT_WORK1)
            {
                print_ptr("удаляем", app_now, talk);
                infa_q1->count_away_app++;
            }
        }
        // обновляем время, если аппарат занят
        rc = diff_time(time_work_app, 0);
        if (rc > 0)
        {
            // находим минимальное
            time_minus = MIN(time_come_app, time_work_app);
            time_work_app -= time_minus;
        }
        else // иначе
        {
            time_minus = time_come_app;
            ao1->time_stay += time_minus;
        }
        time_come_app -= time_minus;
        infa_q1->time_sim += time_minus;
    }
    if (own)
        report_all_work(*ao1, *infa_q1, min_time_come, max_time_come, min_time_work, max_time_work);
    free_queue_stat(Queue, infa_q1->len_q_now);
    return OK;
}

struct Applic* pop_stat(struct Applic* Queue[], struct Inf_oueue *infa_q1)
{
    struct Applic* tmp = Queue[0];
    for (int i = 0; i < (infa_q1->len_q_now - 1); i++)
        Queue[i] = Queue[i + 1];
    Queue[infa_q1->len_q_now - 1] = NULL;
    infa_q1->len_q_now--;
    infa_q1->count_change_q++;
    infa_q1->len_q_sum += infa_q1->len_q_now;
    return tmp;
}

// добавляем пришедшую заявку в очередь
int push_stat(struct Inf_oueue *infa_q1, struct Applic **Queue, struct Applic *app1)
{
    if (infa_q1->len_q_now == MAX_COUNT_APP)
    {
        printf("Статическая очередь переполнена! Работа симулятора прервана(");
        return ERROR;
    }
    //printf("len = %d\n", infa_q1->len_q_now);
    Queue[infa_q1->len_q_now] = app1;
    infa_q1->len_q_now++;
    if (infa_q1->len_q_now > infa_q1->len_q_max)
        infa_q1->len_q_max = infa_q1->len_q_now;
    infa_q1->count_change_q++;
    infa_q1->len_q_sum += infa_q1->len_q_now;
    if (app1->count_work == 0)
        infa_q1->count_come_app++;
    return OK;
}

void free_one_stat(struct Applic *app_del)
{
    if (app_del)
    {
        free(app_del);
        app_del = NULL;
    }
}

void free_queue_stat(struct Applic *Queue[], int len)
{
    for (int i = 0; i < len; i++)
        free_one_stat(Queue[i]);
}

/*
void free_all_stat(struct Applic *Queue[], struct Applic *app_now, struct Applic *app_now_old, struct Applic *app_come, int len)
{
    free_one_stat(app_now);
    free_one_stat(app_now_old);
    free_one_stat(app_come);
    free_queue_stat(Queue, len);
}
*/