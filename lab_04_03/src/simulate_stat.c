#include "simulate_stat.h"

int pop_stat(char Stack1[][SIZE_OF_STR], struct Inf_stack *infa_q1, char *strk[]);
// добавляем пришедшую заявку в очередь
int push_stat(struct Inf_stack *infa_q1, char Stack1[][SIZE_OF_STR], char *strk);

void read_stack(char Stack1[][SIZE_OF_STR], struct Inf_stack *infa_q1);
void work_stat(char Stack1[][SIZE_OF_STR], struct Inf_stack *infa_q1, int own);

int simulate_stat(int own, struct Inf_stack *infa_q1)
{
    int rc = OK;
    int user = NEITRAL_USER;
    // создать массив - стек
    char Stack[MAX_COUNT_ELEM_STAT][SIZE_OF_STR];
    zero_inf_q(infa_q1);
    while (user != 0)
    {
        if (user != ERROR_USER && ! own)
        {
            printf("\nПодменю:\n");
            printf("1 - добавить элемент в стек\n\
2 - удалить элемент из стека\n\
3 - вывести текущее состояние стека\n\
4 - вывести слова задом наперёд в обратном порядке из стека (после этого он будет очищен)\n\
0 - завершить выполнение данной реализации\n\
Введите цифру, соответствующую выбранному пункту меню: ");
        }
        if (own)
        {
            for (int i = 0; (i < own) && (rc == OK); i++)
            {
                char *num = "aaaaa";
                rc = push_stat(infa_q1, Stack, num);
            }
            if (rc == OK)
                work_stat(Stack, infa_q1, 0);
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
            char *strk = calloc(SIZE_OF_STR, sizeof(char));
            printf("Введите добавляемый элемент: ");
            while (scanf("%s", strk) != 1 || (clean_buf() != 0) || strlen(strk) == 0 || strlen(strk) > SIZE_OF_STR)
                printf("Ошибка ввода! Повторите ввод слова: ");
            rc = push_stat(infa_q1, Stack, strk);
            free(strk);
        }
        else if (user == 2)
        {
            char *strk;
            rc = pop_stat(Stack, infa_q1, &strk);
            if (rc == OK)
                printf("Вы удалили элемент х = %s.\n", strk);
        }
        else if (user == 3)
            read_stack(Stack, infa_q1);
        else if (user == 4)
            work_stat(Stack, infa_q1, 1);
        else if (user == 0)
             printf("Завершение работы данной реализации ^-^\n");
    }
    return rc;
}

int pop_stat(char Stack1[][SIZE_OF_STR], struct Inf_stack *infa_q1, char *strk[])
{
    if (infa_q1->len_q_now == 0)
    {
        printf("Ошибка! Стек пуст!\n");
        return ERROR;
    }
    *strk = Stack1[MAX_COUNT_ELEM_STAT - infa_q1->len_q_now];
    infa_q1->len_q_now--;
    return OK;
}

// добавляем новый элемент в стек
int push_stat(struct Inf_stack *infa_q1, char Stack1[][SIZE_OF_STR], char *strk)
{
    if (infa_q1->len_q_now == MAX_COUNT_ELEM_STAT)
    {
        printf("Статический стек переполнен!");
        return ERROR;
    }
    strcpy(Stack1[MAX_COUNT_ELEM_STAT - infa_q1->len_q_now - 1], strk);
    infa_q1->len_q_now++;
    if (infa_q1->len_q_now > infa_q1->len_q_max)
        infa_q1->len_q_max = infa_q1->len_q_now;
    if (((int) strlen(strk)) > infa_q1->len_strk_max)
        infa_q1->len_strk_max = (int) strlen(strk);
    return OK;
}

void read_stack(char Stack1[][SIZE_OF_STR], struct Inf_stack *infa_q1)
{
    int tmp_len = MAX_COUNT_ELEM_STAT - infa_q1->len_q_now;
    while (tmp_len < MAX_COUNT_ELEM_STAT)
    {
        printf("%s\n", Stack1[tmp_len]);
        tmp_len++;
    }
    if (infa_q1->len_q_now == 0)
        printf("Стек пуст!\n");
}

void work_stat(char Stack1[][SIZE_OF_STR], struct Inf_stack *infa_q1, int own)
{
    char *x;
    if (infa_q1->len_q_now == 0)
    {
        if (own)
            printf("Стек пуст!\n");
        return;
    }
    while (infa_q1->len_q_now != 0)
    {
        pop_stat(Stack1, infa_q1, &x);
        if (own)
            print_rev_str(x);
    }
}