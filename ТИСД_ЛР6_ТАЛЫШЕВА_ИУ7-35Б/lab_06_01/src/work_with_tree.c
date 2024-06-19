#include "work_with_tree.h"

void btree_export_to_dot(FILE *f, const char *tree_name, struct Node *tree);

int tree_from_file(struct Node **Head_tree, FILE *file, int talk) {
    int rc = OK;
    int x;
    while (fscanf(file, "%d", &x) == 1 && rc == OK) {
        *Head_tree = tree_add_elem(*Head_tree, x, talk);
        if (*Head_tree == NULL) {
            rc = ERR_MEM;
            printf("Ошибка выделения памяти!\n");
        }
    }
    return rc;
}

// тут надо вывести красоту
void tree_print(struct Node *Head_tree)
{
    FILE *f = fopen("visual.gv", "w");
    //printf("tyt\n");
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
        tree_traversal(Head_tree->left);
        printf("%d\n", Head_tree->data);
        tree_traversal(Head_tree->right);
    }
}

struct Node *tree_add_elem(struct Node *Head_tree, int num, int talk)
{
    if (Head_tree == NULL)
        return node_create(num);
    int cmp = num - Head_tree->data;
    if (cmp == 0 && talk)
        printf("Внимание! Элемент %d уже есть в дереве! Нового элемента не появилось.\n", num);
    else if (cmp < 0)
        Head_tree->left = tree_add_elem(Head_tree->left, num, talk);
    else
        Head_tree->right = tree_add_elem(Head_tree->right, num, talk);

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

struct Node* tree_del_elem(struct Node* Head_tree, int num) {
    if (Head_tree == NULL) {
        return NULL;
    }
    if (num < Head_tree->data) {
        Head_tree->left = tree_del_elem(Head_tree->left, num);
    } else if (num > Head_tree->data) {
        Head_tree->right = tree_del_elem(Head_tree->right, num);
    } else {
        if (Head_tree->left == NULL && Head_tree->right == NULL) {
            free(Head_tree);
            return NULL;
        } else if (Head_tree->left == NULL) {
            struct Node* temp = Head_tree->right;
            free(Head_tree);
            return temp;
        } else if (Head_tree->right == NULL) {
            struct Node* temp = Head_tree->left;
            free(Head_tree);
            return temp;
        } else {
            struct Node* temp = tree_find_min(Head_tree->right);
            Head_tree->data = temp->data;
            Head_tree->right = tree_del_elem(Head_tree->right, temp->data);
        }
    }
    return Head_tree;
}

struct Node *tree_find_elem(struct Node *Head_tree, int num)
{
    if (Head_tree == NULL)
        return NULL;
    int cmp = num - Head_tree->data;
    if (cmp == 0)
        return Head_tree;
    else if (cmp < 0)
        return tree_find_elem(Head_tree->left, num);
    else
        return tree_find_elem(Head_tree->right, num);
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
    const char *fmt = param;

    printf(fmt, node->data);
}
void tree_free(struct Node **Head_tree) {
    if (*Head_tree == NULL)
        return;

    tree_free(&((*Head_tree)->left));
    tree_free(&((*Head_tree)->right));

    node_free(Head_tree);
}

void node_free(struct Node **node) {
    if (*node)
    {
        free(*node);
        *node = NULL;
    }
}

// вывод красивого дерева
void node_to_dot(struct Node *tree, void *param)
{
    FILE *f = param;

    if (tree->left)
        fprintf(f, "%d -> %d [color = blue];\n", tree->data, tree->left->data);

    if (tree->right)
        fprintf(f, "%d -> %d [color = red];\n", tree->data, tree->right->data);
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

    if (tree != NULL && tree->left == NULL && tree->right == NULL)
        fprintf(f, "%d;\n", tree->data);
    else
        btree_apply_pre(tree, node_to_dot, f);

    fprintf(f, "}\n");
}
