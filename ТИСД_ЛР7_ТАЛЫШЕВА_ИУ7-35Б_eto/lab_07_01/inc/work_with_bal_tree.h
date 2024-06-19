#ifndef WORK_WITH_BAL_TREE_H
#define WORK_WITH_BAL_TREE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "const_struct.h"
#include "work_with_tree.h"

// добавляет элемент в сбалансированное дерево
struct Node *bal_tree_add_elem(struct Node *Head_tree, int num, int talk);

// удаляет элемент из сбалансированного дерева
struct Node *bal_tree_del_elem(struct Node *Head_tree, int num);

// балансирует дерево
struct Node *balance_tree(struct Node *Head_tree);

// создаёт новое сбалансированное дерево при сохранении старого
struct Node *balance_and_copy_tree(struct Node *original);

#endif // WORK_WITH_BAL_TREE_H