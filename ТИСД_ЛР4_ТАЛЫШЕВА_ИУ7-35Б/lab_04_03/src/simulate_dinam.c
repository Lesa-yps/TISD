#include "simulate_dinam.h"

int pop_din(struct Node** head, struct Inf_stack *infa_q1, char *strk[], struct Del_adresses *del_adress);
int push_din(struct Inf_stack *infa_q1, struct Node **head, char *strk);

void read_din(struct Node *head);
void work_din(struct Node **head, struct Inf_stack *infa_q1, int own, struct Del_adresses *del_adress);

void free_one_din(char **app_del);
void free_stack_din(struct Node *head);

int simulate_dinam(int own, struct Inf_stack *infa_q1)
{
    int rc = OK;
    struct Del_adresses del_adress;
    del_adress.count = 0;
    int user = NEITRAL_USER;
    // указатель на голову стека
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
4 - вывести слова задом наперёд в обратном порядке из стека (после этого он будет очищен)\n\
5 - вывести список удалённых адресов\n\
0 - завершить выполнение данной реализации\n\
Введите цифру, соответствующую выбранному пункту меню: ");
        }
        if (own)
        {
            for (int i = 0; (i < own) && (rc == OK); i++)
            {
                char *num = "aaaaa";
                rc = push_din(infa_q1, &head, num);
            }
            if (rc == OK)
                work_din(&head, infa_q1, 0, &del_adress);
            user = 0;
        }
        else if (scanf("%d", &user) != 1 || user < 0 || user > 5)
        {
            clean_buf();
            printf("Ошибка ввода! Введите цифру от 0 до 5: ");
            user = ERROR_USER;
        }
        else if (user == 1)
        {
            char *strk = calloc(SIZE_OF_STR, sizeof(char));
            printf("Введите добавляемый элемент: ");
            while (scanf("%s", strk) != 1 || (clean_buf() != 0) || strlen(strk) == 0 || strlen(strk) > SIZE_OF_STR)
                printf("Ошибка ввода! Повторите ввод слова: ");
            rc = push_din(infa_q1, &head, strk);
            free(strk);
        }
        else if (user == 2)
        {
            char *strk;
            rc = pop_din(&head, infa_q1, &strk, &del_adress);
            if (rc == OK)
                printf("Вы удалили элемент х = %s.\n", strk);
        }
        else if (user == 3)
            read_din(head);
        else if (user == 4)
            work_din(&head, infa_q1, 1, &del_adress);
        else if (user == 5)
             print_del_add(del_adress);
        else if (user == 0)
             printf("Завершение работы данной реализации ^-^\n");
    }
    free_stack_din(head);
    return rc;
}

int pop_din(struct Node** head, struct Inf_stack *infa_q1, char **strk, struct Del_adresses *del_adress)
{
    int rc = OK;
    struct Node *tmp;
    if ((*head) != NULL)
    {
        tmp = *head;
        *strk = tmp->data;
        del_adress->arr[del_adress->count] = (void *) &tmp->data;
        del_adress->count++;
        *head = tmp->next;
        free(tmp);
        infa_q1->len_q_now--;
    }
    else
    {
        printf("Ошибка! Стек пуст!\n");
        rc = ERROR;
    }
    return rc;
}

int push_din(struct Inf_stack *infa_q1, struct Node **head, char *strk)
{
    if (infa_q1->len_q_now > MAX_COUNT_ELEM_DIN)
    {
        printf("Достигнута верхняя граница динамической очереди (установленная мной)! Элемент не был вставлен(\n");
        return ERROR;
    }
    struct Node *tmp = (struct Node*)malloc(sizeof(struct Node));
    if (tmp == NULL)
    {
        printf("Ошибка выделения памяти!\n");
        return ERROR;
    }
    tmp->data = malloc(strlen(strk) * sizeof(char));
    if (tmp->data == NULL)
    {
        free(tmp);
        printf("Ошибка выделения памяти!\n");
        return ERROR;
    }
    strcpy(tmp->data, strk);
    tmp->next = *head;
    *head = tmp;

    infa_q1->len_q_now++;
    if (infa_q1->len_q_now > infa_q1->len_q_max)
        infa_q1->len_q_max = infa_q1->len_q_now;
    if (((int) strlen(strk)) > infa_q1->len_strk_max)
        infa_q1->len_strk_max = (int) strlen(strk);
    return OK;
}

void free_one_din(char **app_del)
{
    if (*app_del)
    {
        free(*app_del);
        *app_del = NULL;
    }
}

void free_stack_din(struct Node *head)
{
    struct Node *current = head;
    while (current != NULL)
    {
        struct Node *tmp = current;
        current = current->next;
        free_one_din(&(tmp->data));
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
        printf("%s\n", current->data);
        current = current->next;
    }
}

void work_din(struct Node **head, struct Inf_stack *infa_q1, int own, struct Del_adresses *del_adress)
{
    if (*head == NULL)
    {
        if (own)
            printf("Стек пуст!");
        return;
    }
    while (*head != NULL)
    {
        char *strk;
        pop_din(head, infa_q1, &strk, del_adress);
        if (own)
            print_rev_str(strk);
    }
}