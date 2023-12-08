#include "simulate_dinam.h"

struct Applic* pop_din(struct Node** head, struct Inf_oueue *infa_q1);
int push_din(struct Inf_oueue *infa_q1, struct Node **Queue_tail, struct Node **Queue_head, struct Applic *app_come);

void free_one_din(struct Applic *app_del);
void free_queue_din(struct Node *Queue_head);

int simulate_dinam(int talk, int own, double min_time_come, double max_time_come, double min_time_work, double max_time_work,\
                   struct Inf_oueue *infa_q1, struct AO *ao1)
{
    double rc;
    // создать массив - очередь
    struct Node* Queue_head = NULL;
    struct Node* Queue_tail = Queue_head;
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
    while (infa_q1->count_away_app < NEED_COUNT_AWAY_APP)
    {
        //printf("Verx %d\n", infa_q1->count_away_app);
        // если время прихода новой заявки кончилось
        if ((diff_time(time_come_app, 0) <= 0) && (app_come != NULL))
        {
            // добавляем пришедшую заявку в очередь
            if (push_din(infa_q1, &Queue_tail, &Queue_head, app_come) == ERROR)
            {
                free_queue_din(Queue_head);
                return ERROR;
            }
            if (app_come->count_work == 0)
            {
                print_ptr("добавляем", app_come, talk);
            }
            // идем за новой заявкой
            if (hat_for_get(&time_come_app, &app_come, min_time_come, max_time_come, min_time_work, max_time_work))
            {
                free_queue_din(Queue_head);
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
                        if (push_din(infa_q1, &Queue_tail, &Queue_head, app_now_old) == ERROR)
                        {
                            free_queue_din(Queue_head);
                            return ERROR;
                        }
                    }
                    else
                        free_one_din(app_now_old);
                }
            }
            app_now = pop_din(&Queue_head, infa_q1);
            time_work_app = app_now->time_work;
            app_now->count_work++;
            ao1->count_work += 1;
            if (app_now->count_work == MAX_COUNT_WORK1)
            {
                print_ptr("удаляем", app_now, talk);
                infa_q1->count_away_app++;
                // если количество заявок кратно REPORT_COUNT_APP и больше нуля выводим информацию
                if (infa_q1->count_away_app % REPORT_COUNT_APP == 0 && ao1->count_work > 0 && own)
                    report_part_work(*infa_q1);
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
    free_queue_din(Queue_head);
    return OK;
}

struct Applic* pop_din(struct Node** head, struct Inf_oueue *infa_q1)
{
    struct Node tmp;
    struct Applic *data_res = NULL;
    if ((*head) != NULL)
    {
        tmp = **head;
        data_res = tmp.data;
        free(*head);
        (*head) = tmp.next;
    }
    infa_q1->len_q_now--;
    infa_q1->count_change_q++;
    infa_q1->len_q_sum += infa_q1->len_q_now;
    return data_res;
}

int push_din(struct Inf_oueue *infa_q1, struct Node **Queue_tail, struct Node **Queue_head, struct Applic *app_come)
{
    if (infa_q1->len_q_now > MAX_DIN_QUEUE)
    {
        printf("Достигнуто верхняя граница динамической очереди (установленная мной)! Симуляция прервана.\n");
        return ERROR;
    }
    struct Node *tmp = (struct Node*)malloc(sizeof(struct Node));
    if (tmp == NULL)
    {
        printf("Ошибка выделения памяти!\n");
        return ERROR;
    }
    tmp->next = NULL;
    tmp->data = app_come;

    if (*Queue_head == NULL)
        (*Queue_head) = tmp;
    else
        (*Queue_tail)->next = tmp;
    (*Queue_tail) = tmp;

    infa_q1->len_q_now++;
    if (infa_q1->len_q_now > infa_q1->len_q_max)
        infa_q1->len_q_max = infa_q1->len_q_now;
    infa_q1->len_q_sum += infa_q1->len_q_now;
    infa_q1->count_change_q++;
    if (app_come->count_work == 0)
        infa_q1->count_come_app++;
    return OK;
}

void free_one_din(struct Applic *app_del)
{
    if (app_del)
    {
        free(app_del);
        app_del = NULL;
    }
}

void free_queue_din(struct Node *Queue_head)
{
    struct Node *current = Queue_head;
    while (current != NULL)
    {
        struct Node *tmp = current;
        current = current->next;
        free_one_din(tmp->data);
        tmp->next = NULL;
        free(tmp);
    }
}

/*
void free_all_din(struct Node *Queue_head, struct Applic *app_now, struct Applic *app_now_old, struct Applic *app_come)
{
    free_queue_din(Queue_head);
    free_one_din(app_now);
    free_one_din(app_now_old);
    free_one_din(app_come);
}
*/