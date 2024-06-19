#ifndef WORK_WITH_TREE_H
#define WORK_WITH_TREE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "const_struct.h"

// Структура - элемент дерева
struct Node
{
    int data; // Данные
    struct Node *right;   // Указатель на правое поддерево (больше)
    struct Node *left;   // Указатель на левое поддерево (меньше)
};

typedef void (*ptr_action_t)(struct Node*, void*);

int tree_from_file(struct Node **Head_tree, FILE *file, int talk);

void tree_print(struct Node *Head_tree, char *name_file);

void tree_traversal(struct Node *Head_tree);

struct Node *tree_add_elem(struct Node *Head_tree, int num, int talk);

struct Node *tree_del_elem(struct Node *Head_tree, int num);

struct Node *tree_find_elem(struct Node *Head_tree, int num, int *count);

void tree_level_node(struct Node *Head_tree);

struct Node* node_create(int num);
void node_print(struct Node *node, void *param);
void tree_free(struct Node **Head_tree);
void node_free(struct Node **node);

// Функция tree_find_min находит наименьший элемент
struct Node *tree_find_min(struct Node *Head_tree);

double tree_count_average_find(struct Node *Head_tree, FILE *file);

#endif // WORK_WITH_TREE_H