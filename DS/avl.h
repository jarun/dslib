/*
 * AVL Tree abstraction
 * Ref: https://en.wikipedia.org/wiki/AVL_tree
 *
 * Author: Arun Prakash Jana <engineerarun@gmail.com>
 * Copyright (C) 2015 by Arun Prakash Jana <engineerarun@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dslib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "common.h"
#include "stack.h"

#pragma once

struct avl;

typedef struct avl {
	int data;
	struct avl *left;
	struct avl *right;
	int height;
} avl_t, *avl_p, **avl_pp;

/* Rebalance a subtree if balance factory is 2 or -2 */
void rebalance(stack_p stack, avl_pp head, avl_p tmp, int data);

/* Generate AVL tree from an array of input values */
avl_p *generate_avl(int *arr, int len);

/* Calculate height of an AVL tree node */
int height(avl_p node);

/* Rotate a subtree towards right */
avl_p RotateRight(avl_p node);

/* Rotate a subtree towards left */
avl_p RotateLeft(avl_p node);

/* AVL subtree structure (skew) handlers */
avl_p RightRight(avl_p node);
avl_p LeftLeft(avl_p node);
avl_p LeftRight(avl_p node);
avl_p RightLeft(avl_p node);

/* Calculate balance factor of a subtree */
int BalanceFactor(avl_p node);

/* Destroy the tree */
int delete_avl(avl_p root);

/* Print a tree */
int print_avl(avl_p root, avl_p parent);

/* Traverse tree in BFS to find a given value */
int search_BFS_avl(avl_pp root, int val, bool stop);

/* Traverse tree in DFS to find a given value */
int search_DFS_avl(avl_pp root, int val, bool stop);
