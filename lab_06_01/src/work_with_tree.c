#include "work_with_tree.h"

struct Node* node_create(int num);
void node_print(struct Node *node, void *param);
void node_free(struct Node *node, void *param);

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

    if (Head_tree == NULL)
        return new_node;

    cmp = strcmp(new_node->data, Head_tree->data);
    if (cmp == 0)
        printf("Внимание! Элемент уже есть в дереве! Нового элемента не появилось.\n");
    else if (cmp < 0)
        Head_tree->left = btree_insert(Head_tree->left, new_node);
    else
        Head_tree->right = btree_insert(Head_tree->right, new_node);

    return Head_tree;
}

int tree_del_elem(struct Node **Head_tree, int num);

struct Node *tree_find_elem(struct Node *Head_tree, int num);
{
    int cmp;
    if (Head_tree == NULL)
        return NULL;
    cmp = num - Head_tree->data;
    if (cmp == 0)
        return Head_tree;
    else if (cmp < 0)
        return tree_find_elem(Head_tree->left, num);
    else
        return tree_find_elem(Head_tree->right, num);
}

void tree_level_node(struct Node *Head_tree);

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
void node_free(struct Node *node, void *param)
{
    free(node);
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