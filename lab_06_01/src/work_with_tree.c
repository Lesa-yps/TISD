#include "work_with_tree.h"

void tree_from_file(struct Node **Head_tree, FILE *file);

void tree_print(struct Node *Head_tree);

void tree_traversal(struct Node *Head_tree);

int tree_add_elem(struct Node **Head_tree, int num);

int tree_del_elem(struct Node **Head_tree, int num);

int tree_find_elem(struct Node *Head_tree, int num);

void tree_level_node(struct Node *Head_tree);