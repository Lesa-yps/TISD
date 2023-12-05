#include "simulate_dinam.h"

int pop_din(struct Node** head, struct Inf_stack *infa_q1, int *res, int talk);
int push_din(struct Inf_stack *infa_q1, struct Node **head, int num);

void read_din(struct Node *head);
void work_din(struct Node **head, struct Inf_stack *infa_q1, int own, int talk);

void free_one_din(int *app_del);
void free_stack_din(struct Node *head);

int simulate_dinam(int talk, int own, struct Inf_stack *infa_q1)
{
    int rc = OK;
    int user = NEITRAL_USER;
    // создать массив - стек
    struct Node* head = NULL;
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
                rc = push_din(infa_q1, &head, num);
            }
            if (rc == OK)
                work_din(&head, infa_q1, 0, 0);
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
            rc = push_din(infa_q1, &head, num);
        }
        else if (user == 2)
        {
            int res = 0;
            rc = pop_din(&head, infa_q1, &res, talk);
            if (rc == OK)
                printf("Вы удалили элемент х = %d.\n", res);
        }
        else if (user == 3)
            read_din(head);
        else if (user == 4)
            work_din(&head, infa_q1, 1, talk);
        else if (user == 0)
             printf("Завершение работы данной реализации ^-^\n");
    }
    free_stack_din(head);
    return rc;
}

int pop_din(struct Node** head, struct Inf_stack *infa_q1, int *res, int talk)
{
    int rc = OK;
    struct Node tmp;
    if ((*head) != NULL)
    {
        tmp = **head;
        *res = tmp.data;
        print_ptr("Удалили: ", &tmp.data, talk);
        free(*head);
        (*head) = tmp.next;
        infa_q1->len_q_now--;
    }
    else
    {
        printf("Ошибка! Стек пуст!\n");
        rc = ERROR;
    }
    return rc;
}

int push_din(struct Inf_stack *infa_q1, struct Node **head, int num)
{
    if (infa_q1->len_q_now > MAX_COUNT_ELEM_DIN)
    {
        printf("Достигнуто верхняя граница динамической очереди (установленная мной)! Элемент не был вставлен(\n");
        return ERROR;
    }
    if (infa_q1->len_q_now != 0 && (*head)->data <= num)
    {
        printf("Ошибка! Последовательность не убывающая! Элемент не добавлен(");
        return ERROR;
    }
    struct Node *tmp = (struct Node*)malloc(sizeof(struct Node));
    if (tmp == NULL)
    {
        printf("Ошибка выделения памяти!\n");
        return ERROR;
    }
    tmp->next = *head;
    tmp->data = num;

    *head = tmp;

    infa_q1->len_q_now++;
    if (infa_q1->len_q_now > infa_q1->len_q_max)
        infa_q1->len_q_max = infa_q1->len_q_now;
    return OK;
}

void free_one_din(int *app_del)
{
    if (app_del)
    {
        free(app_del);
        app_del = NULL;
    }
}

void free_stack_din(struct Node *head)
{
    struct Node *current = head;
    while (current != NULL)
    {
        struct Node *tmp = current;
        current = current->next;
        //free_one_din(tmp->data);
        free(tmp);
    }
}

void read_din(struct Node *head)
{
    struct Node *current = head;
    if (current == NULL)
    {
        printf("Стек пуст!");
        return;
    }
    while (current != NULL)
    {
        printf("%d\n", current->data);
        current = current->next;
    }
}

void work_din(struct Node **head, struct Inf_stack *infa_q1, int own, int talk)
{
    if (*head == NULL)
    {
        if (own)
            printf("Стек пуст!");
        return;
    }
    while (*head != NULL)
    {
        int res = 0;
        pop_din(head, infa_q1, &res, talk);
        if (own)
            printf("%d\n", res);
    }
}