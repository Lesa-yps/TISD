#ifndef WORK_WITH_TREE_H
#define WORK_WITH_TREE_H

#include <stdio.h>

#include "const_struct.h"

typedef void (*ptr_action_t)(struct tree_node_t*, void*);

int tree_from_file(struct Node **Head_tree, FILE *file);

void tree_print(struct Node *Head_tree);

void tree_traversal(struct Node *Head_tree);

int tree_add_elem(struct Node **Head_tree, int num);

int tree_del_elem(struct Node **Head_tree, int num);

struct Node *tree_find_elem(struct Node *Head_tree, int num);

void tree_level_node(struct Node *Head_tree);

#endif // WORK_WITH_TREE_H