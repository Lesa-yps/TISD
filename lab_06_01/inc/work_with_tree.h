#ifndef WORK_WITH_TREE_H
#define WORK_WITH_TREE_H

#include <stdio.h>
#include <string.h>

#include "const_struct.h"

typedef void (*ptr_action_t)(struct tree_node_t*, void*);

int tree_from_file(struct Node **Head_tree, FILE *file);

void tree_print(struct Node *Head_tree);

void tree_traversal(struct Node *Head_tree);

struct Node *tree_add_elem(struct Node *Head_tree, int num);

struct Node *tree_del_elem(struct Node *Head_tree, int num);

struct Node *tree_find_elem(struct Node *Head_tree, int num);

void tree_level_node(struct Node *Head_tree);

struct Node* node_create(int num);
void node_print(struct Node *node, void *param);
void tree_free(struct Node *Head);
void node_free(struct Node *node);

#endif // WORK_WITH_TREE_H