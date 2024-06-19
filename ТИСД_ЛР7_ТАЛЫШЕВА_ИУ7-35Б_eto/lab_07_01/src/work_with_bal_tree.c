#include "work_with_bal_tree.h"

// ищет максимальную высоту дерева
char tree_height(struct Node *Head_tree)
{
    int h = 0;
    if (Head_tree != NULL)
    {
        int l_height = tree_height(Head_tree->left);
        int r_height = tree_height(Head_tree->right);
        int max_height = l_height > r_height ? l_height : r_height;
        h = max_height + 1;
    }
    return h;
}

// ищет высоту поддерева слева, высоту поддерева справа и возвращает лево - право
int tree_diff_level(struct Node *Head_tree)
{
    int l_height = tree_height(Head_tree->left);
    int r_height = tree_height(Head_tree->right);
    int b_factor = l_height - r_height;
    return b_factor;
}

// начало
//       |-----2-----|
//   |---1---|       4
// |-0      Null
//-1
// шаг первый (запомнили левое поддерево)
//   |---1
// |-0
//-1
// шаг второй (на место левой ветви корня ставим правую ветвь левого запомненого поддерева)
//      |------2------|
//     Null           4
// шаг третий (запомненому справа поставили корень)
//   |-----1-----|
// |-0    |------2------|
//-1     Null           4
// и шаг четвертый (вернули запомненный как корень)
struct Node *bal_tree_ll_rotation(struct Node *Head_tree)
{
    struct Node *tmp;
    tmp = Head_tree->left;
    Head_tree->left = tmp->right;
    tmp->right = Head_tree;
    return tmp;
}

// начало
//       |-----2-----|
//       1       |---3---|
//              Null     4---|
//                           5
// шаг первый (запомнили правое поддерево)
//   |---3---|
//  Null     4---|
//               5
// шаг второй (на место правой ветви корня ставим левую ветвь правого запомненого поддерева)
//      |------2------|
//      1            Null
// шаг третий (запомненому слева поставили корень)
//    |---3---|
// |--2--|    4---|
// 1    Null      5
// и шаг четвертый (вернули запомненный как корень)
struct Node *bal_tree_rr_rotation(struct Node *Head_tree)
{
    struct Node *tmp;
    tmp = Head_tree->right;
    Head_tree->right = tmp->left;
    tmp->left = Head_tree;
    return tmp;
}

//          8
//     3       12
//  2     5
//      4
// left - right rotation
//
// корень - [8]
// запоминаем левый узел корня root->right[8] ( 2 <- 3 -> 5 ... )
// 1) выполняем rr_rotation для этого корня [3]
//  rr_rotation для ( 2 <- 3 -> 5 ... )
//      3
//   2     5
//       4
// получаем
//         5
//       3
//     2   4
//
// присваеваем это поддерево левому узлу корня [8]
//         8
//      5     12
//    3
//  2   4
// 2) ll_rotation для корня [8]
//
// получаем
//          5
//      3     8
//    2   4     12
struct Node *bal_tree_lr_rotation(struct Node *Head_tree)
{
    struct Node *tmp;
    tmp = Head_tree->left;
    Head_tree->left = bal_tree_rr_rotation(tmp);
    return bal_tree_ll_rotation(Head_tree);
}

// то же самое, что lr_rotation, только право<->лево
struct Node *bal_tree_rl_rotation(struct Node *Head_tree)
{
    struct Node *tmp;
    tmp = Head_tree->right;
    Head_tree->right = bal_tree_ll_rotation(tmp);
    return bal_tree_rr_rotation(Head_tree);
}

// балансирует дерево (которе шаг назад было сбалансированным) с помощью функций выше
struct Node *tree_balance_in_balance(struct Node *Head_tree)
{
    int bal_factor = tree_diff_level(Head_tree);
    if (bal_factor > 1)
    {
        if (tree_diff_level(Head_tree->left) > 0)
            Head_tree = bal_tree_ll_rotation(Head_tree);
        else
            Head_tree = bal_tree_lr_rotation(Head_tree);
    }
    else if (bal_factor < -1)
    {
        if (tree_diff_level(Head_tree->right) > 0)
            Head_tree = bal_tree_rl_rotation(Head_tree);
        else
            Head_tree = bal_tree_rr_rotation(Head_tree);
    }
    return Head_tree;
}

//          8
//     3       12
//  2     5
//      4
// балансирует дерево
struct Node *balance_tree(struct Node *Head_tree)
{
    if (Head_tree == NULL)
        return NULL;
    // Рекурсивно балансируем левое и правое поддеревья
    Head_tree->left = balance_tree(Head_tree->left);
    Head_tree->right = balance_tree(Head_tree->right);
    // Балансируем текущий узел
    return tree_balance_in_balance(Head_tree);
}

// удаляет элемент из сбалансированного дерева
struct Node *bal_tree_del_elem(struct Node *Head_tree, int num)
{
    if (Head_tree == NULL)
    {
        return NULL;
    }
    if (num < Head_tree->data)
    {
        Head_tree->left = tree_del_elem(Head_tree->left, num);
    }
    else if (num > Head_tree->data)
    {
        Head_tree->right = tree_del_elem(Head_tree->right, num);
    }
    else
    {
        if (Head_tree->left == NULL && Head_tree->right == NULL)
        {
            free(Head_tree);
            return NULL;
        }
        else if (Head_tree->left == NULL)
        {
            struct Node *temp = Head_tree->right;
            free(Head_tree);
            return temp;
        }
        else if (Head_tree->right == NULL)
        {
            struct Node *temp = Head_tree->left;
            free(Head_tree);
            return temp;
        }
        else
        {
            struct Node *temp = tree_find_min(Head_tree->right);
            Head_tree->data = temp->data;
            Head_tree->right = bal_tree_del_elem(Head_tree->right, temp->data);
        }
    }
    // После каждого удаления элемента выполняем балансировку
    return balance_tree(Head_tree);
    return Head_tree;
}

// добавляет элемент в сбалансированное дерево
struct Node *bal_tree_add_elem(struct Node *Head_tree, int num, int talk)
{
    if (Head_tree == NULL)
        return node_create(num);
    int cmp = num - Head_tree->data;
    if (cmp == 0 && talk)
        printf("Внимание! Элемент %d уже есть в дереве! Нового элемента не появилось.\n", num);
    else if (cmp < 0)
    {
        Head_tree->left = tree_add_elem(Head_tree->left, num, talk);
        Head_tree = tree_balance_in_balance(Head_tree);
    }
    else
    {
        Head_tree->right = tree_add_elem(Head_tree->right, num, talk);
        Head_tree = tree_balance_in_balance(Head_tree);
    }
    return balance_tree(Head_tree);
}

struct Node *copy_tree(struct Node *original)
{
    if (original == NULL)
        return NULL;
    struct Node *new_node = malloc(sizeof(struct Node));
    if (new_node == NULL)
    {
        printf("Ошибка выделения памяти.\n");
        return NULL;
    }
    new_node->data = original->data;
    new_node->left = copy_tree(original->left);
    new_node->right = copy_tree(original->right);
    return new_node;
}

struct Node *balance_and_copy_tree(struct Node *original)
{
    struct Node *copied_tree = copy_tree(original);
    return balance_tree(copied_tree);
}