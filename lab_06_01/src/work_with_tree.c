#include "work_with_tree.h"

void btree_export_to_dot(FILE *f, const char *tree_name, struct Node *tree);

int tree_from_file(struct Node **Head_tree, FILE *file)
{
    int rc = OK;
    int x;
    while (fscanf(file, "%d", &x) == 1 && rc == OK)
        rc = tree_add_elem(Head_tree, x);
    return rc;
}

// тут надо вывести красоту
void tree_print(struct Node *Head_tree)
{
    FILE *f = fopen("visual.gv", "w");
    btree_export_to_dot(f, "visual_tree", Head_tree);
    fclose(f);
}

// а тут просто обойти и получить отсортированный список
void tree_traversal(struct Node *Head_tree)
{
    if (Head_tree == NULL)
        return;
    else
    {
        tree_print(Head_tree->left);
        printf("left = %d\n", Head_tree->data);
        tree_print(Head_tree->right);
        printf("right = %d\n", Head_tree->data);
    }
}

struct Node *tree_add_elem(struct Node *Head_tree, int num)
{
    struct Node *new_node = node_create(num);
    int cmp;
    if (Head_tree == NULL || new_node == NULL)
        return new_node;
    cmp = strcmp(new_node->data, Head_tree->data);
    if (cmp == 0)
        printf("Внимание! Элемент уже есть в дереве! Нового элемента не появилось.\n");
    else if (cmp < 0)
        Head_tree->left = tree_add_elem(Head_tree->left, new_node);
    else
        Head_tree->right = tree_add_elem(Head_tree->right, new_node);

    return Head_tree;
}

// Функция tree_find_min находит наименьший элемент
struct Node *tree_find_min(struct Node *Head_tree)
{
    struct Node *current = Head_tree;
    while (current->left != NULL)
        current = current->left;
    return current;
}

struct Node *tree_del_elem(struct Node *Head_tree, int num)
{
    // нашли удаляемый элемент
    struct Node *del_node = tree_find_elem(Head_tree, num);
    int cmp;
    // или не нашли(
    if (Head_tree == NULL || del_node == NULL)
        return NULL;
    // Если значения совпадают, то нашли удаляемый узел
    else
    {
        // Если у узла нет потомков, просто освобождаем память узла и возвращаем NULL
        if (Head_tree->left == NULL && Head_tree->right == NULL)
        {
            free(Head_tree);
            return NULL;
        }
        // Если у узла есть только один потомок (левый или правый),
        // то возвращаем этого потомка, и связи с удаляемым узлом разрушаются
        else if (Head_tree->left == NULL)
        {
            struct Node* temp = Head_tree->right;
            free(Head_tree);
            return temp;
        }
        else if (Head_tree->right == NULL)
        {
            struct Node* temp = Head_tree->left;
            free(Head_tree);
            return temp;
        }
        // Если у узла есть оба потомка, находим наименьший элемент в правом поддереве
        // и заменяем текущий узел на него. Затем рекурсивно вызываем функцию для
        // удаления найденного узла из правого поддерева
        else
        {
            // Функция tree_find_min находит наименьший элемент
            struct Node* temp = tree_find_min(Head_tree->right);
            Head_tree->data = temp->data;
            Head_tree->right = tree_del_elem(Head_tree->right, temp->data);
        }
    }
    return Head_tree;
}

// функция считает количество узлов на данном уровне
int tree_find_count_node_level(struct Node *Head_tree, int level_find)
{
    if (level_find == 0 && Head_tree != NULL)
        return 1;
    else
    {
        int count = 0;
        if (Head_tree->left != NULL)
            count += tree_find_count_node_level(Head_tree->left, level_find - 1);
        if (Head_tree->right != NULL)
            count += tree_find_count_node_level(Head_tree->right, level_find - 1);
        return count;
    }
}

void tree_level_node(struct Node *Head_tree)
{
    if (Head_tree == NULL)
    {
        printf("Дерево пусто!\n");
        return;
    }
    printf("Количество узлов на каждом уровне в дереве:\n");
    // количества узлов на данном уровне
    int count_node_level;
    // какой уровень сейчас
    int level_now = 0;
    do
    {
        // функция считает количество узлов на данном уровне
        count_node_level = tree_find_count_node_level(Head_tree, level_now);
        if (count_node_level != 0)
        {
            printf("Уровень №%d - %d узлов.\n", level_now, count_node_level);
            level_now++;
        }
    } while (count_node_level != 0);
}

// базовое для работы с деревьями
struct Node* node_create(int num)
{
    struct Node *node;
    node = malloc(sizeof(struct Node));
    
    if (node)
    {
        node->data = num;
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}
void node_print(struct Node *node, void *param)
{
    const int *fmt = param;

    printf(fmt, node->data);
}
void tree_free(struct Node *Head)
{
    if (Head->left == NULL && Head->right == NULL)
        node_free(Head);
    else
    {
        if (Head->left != NULL)
            tree_free(Head->left);
        if (Head->right != NULL)
            tree_free(Head->right);
    }
}
void node_free(struct Node *node)
{
    if (node)
        free(node);
    node = NULL;
}

// вывод красивого дерева
void node_to_dot(struct Node *tree, void *param)
{
    FILE *f = param;

    if (tree->left)
        fprintf(f, "%d -> %d;\n", tree->data, tree->left->data);

    if (tree->right)
        fprintf(f, "%d -> %d;\n", tree->data, tree->right->data);
}
void btree_apply_pre(struct Node *tree, ptr_action_t f, void *arg)
{
    if (tree == NULL)
        return;
    
    f(tree, arg);
    btree_apply_pre(tree->left, f, arg);
    btree_apply_pre(tree->right, f, arg);
}
void btree_export_to_dot(FILE *f, const char *tree_name, struct Node *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);

    btree_apply_pre(tree, node_to_dot, f);

    fprintf(f, "}\n");
}
