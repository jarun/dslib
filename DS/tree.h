/*
 * Abstraction of a Binary Search Tree
 */

#include "common.h"

#pragma once

struct tree;

typedef struct tree {
	int data;
	struct tree *left;
	struct tree *right;
} tree_t, *tree_p, **tree_pp;

/* Generate tree from an array of input values */
tree_p *generate_tree(int *arr, int len);

/* Destroy the tree */
int  delete_tree(tree_p root);

/* Print a tree */
int print_tree(tree_p root);

/* Traverse tree in BFS to find a given value */
int search_BFS(tree_pp root, int val, bool stop);

/* Traverse tree in DFS to find a given value */
int search_DFS(tree_pp root, int val, bool stop);
