#include "simulate_stat.h"

int pop_stat(int Stack1[], struct Inf_stack *infa_q1, int *res, int talk);
// добавляем пришедшую заявку в очередь
int push_stat(struct Inf_stack *infa_q1, int Stack1[], int num);

void read_stack(int Stack1[], struct Inf_stack *infa_q1);
void work_stat(int Stack1[], struct Inf_stack *infa_q1, int own, int talk);

int simulate_stat(int talk, int own, struct Inf_stack *infa_q1)
{
    int rc = OK;
    int user = NEITRAL_USER;
    // создать массив - стек
    int Stack[MAX_COUNT_ELEM_STAT];
    zero_inf_q(infa_q1);
    while (user != 0)
    {
        if (user != ERROR_USER && ! own)
        {
            printf("\nПодменю:\n");
            printf("1 - добавить элемент в стек\n\
2 - удалить элемент из стека\n\
3 - вывести текущее состояние стека\n\
4 - вывести числа в обратном порядке из стека (после этого он будет очищен)\n\
0 - завершить выполнение программы\n\
Введите цифру, соответствующую выбранному пункту меню: ");
        }
        if (own)
        {
            for (int i = 0; (i < own) && (rc == OK); i++)
            {
                int num = - i;
                rc = push_stat(infa_q1, Stack, num);
            }
            if (rc == OK)
                work_stat(Stack, infa_q1, 0, 0);
            user = 0;
        }
        else if (scanf("%d", &user) != 1 || user < 0 || user > 4)
        {
            clean_buf();
            printf("Ошибка ввода! Введите цифру от 0 до 4: ");
            user = ERROR_USER;
        }
        else if (user == 1)
        {
            int num = 0;
            printf("Введите добавляемый элемент: ");
            while (scanf("%d", &num) != 1 || (clean_buf() != 0))
                printf("Ошибка ввода! Повторите ввод целого числа: ");
            rc = push_stat(infa_q1, Stack, num);
        }
        else if (user == 2)
        {
            int res = 0;
            rc = pop_stat(Stack, infa_q1, &res, talk);
            if (rc == OK)
                printf("Вы удалили элемент х = %d.\n", res);
        }
        else if (user == 3)
            read_stack(Stack, infa_q1);
        else if (user == 4)
            work_stat(Stack, infa_q1, 1, talk);
        else if (user == 0)
             printf("Завершение работы данной реализации ^-^\n");
    }
    return rc;
}

int pop_stat(int Stack1[], struct Inf_stack *infa_q1, int *res, int talk)
{
    if (infa_q1->len_q_now == 0)
    {
        printf("Ошибка! Стек пуст!\n");
        return ERROR;
    }
    *res = Stack1[MAX_COUNT_ELEM_STAT - infa_q1->len_q_now];
    print_ptr("Удалили: ", res, talk);
    infa_q1->len_q_now--;
    return OK;
}

// добавляем новый элемент в стек
int push_stat(struct Inf_stack *infa_q1, int Stack1[], int num)
{
    if (infa_q1->len_q_now == MAX_COUNT_ELEM_STAT)
    {
        printf("Статический стек переполнен!");
        return ERROR;
    }
    if (infa_q1->len_q_now != 0 && Stack1[MAX_COUNT_ELEM_STAT - infa_q1->len_q_now] <= num)
    {
        printf("Ошибка! Последовательность не убывающая! Элемент не добавлен(");
        return ERROR;
    }
    Stack1[MAX_COUNT_ELEM_STAT - infa_q1->len_q_now - 1] = num;
    infa_q1->len_q_now++;
    if (infa_q1->len_q_now > infa_q1->len_q_max)
        infa_q1->len_q_max = infa_q1->len_q_now;
    return OK;
}

void read_stack(int Stack1[], struct Inf_stack *infa_q1)
{
    int tmp_len = MAX_COUNT_ELEM_STAT - infa_q1->len_q_now;
    while (tmp_len < MAX_COUNT_ELEM_STAT)
    {
        printf("%d\n", Stack1[tmp_len]);
        tmp_len++;
    }
    if (infa_q1->len_q_now == 0)
        printf("Стек пуст!\n");
}

void work_stat(int Stack1[], struct Inf_stack *infa_q1, int own, int talk)
{
    int x;
    if (infa_q1->len_q_now == 0)
    {
        if (own)
            printf("Стек пуст!\n");
        return;
    }
    while (infa_q1->len_q_now != 0)
    {
        pop_stat(Stack1, infa_q1, &x, talk);
        if (own)
            printf("%d\n", x);
    }
}