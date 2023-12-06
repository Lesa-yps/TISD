#include "work_with_tree.h"

struct Node* node_create(int ptr_num);
void node_print(struct Node *node, void *param);
void node_free(struct Node *node, void *param);

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
    if (Head_tree == NULL)
        return;
    else
    {
        printf("%d\n", *(Head_tree->data));
        tree_print(Head_tree->left);
        tree_print(Head_tree->right);
    }
}

// а тут просто обойти и получить отсортированный список
void tree_traversal(struct Node *Head_tree);

int tree_add_elem(struct Node **Head_tree, int num);

int tree_del_elem(struct Node **Head_tree, int num);

int tree_find_elem(struct Node *Head_tree, int num);

void tree_level_node(struct Node *Head_tree);

struct Node* node_create(int ptr_num)
{
    struct Node *node;
    node = malloc(sizeof(struct Node));
    
    if (node)
    {
        int *num = malloc(sizeof(int));
        if (num == NULL)
        {
            free(node);
            return NULL;
        }
        *num = ptr_num;
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