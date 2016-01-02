/*
 * AVL Tree implementation
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

#include "stack.h"
#include "avl.h"

#define LEFT  0
#define RIGHT 1

typedef struct {
	avl_p node;
	int direction;
} nodedata;

/*
 * Generate an AVL tree from an array of integers
 */
avl_p *generate_avl(int *arr, int len)
{
	int i = 1;
	avl_p *head = NULL;
	avl_p root = NULL;
	avl_p tmp = NULL;
	avl_p parent = NULL;
	stack_p stack = get_stack(); // Stack to rebalance each subtree bottom-up after insertion

	if (!arr || !len) {
		log(ERROR, "Invalid array.\n");
		return NULL;
	}

	root = (avl_p) calloc(1, sizeof(avl_t));
	if (!root) {
		log(ERROR, "calloc failed.\n");
		return NULL;
	}
	root->data = arr[0];
	head = calloc(1, sizeof(avl_p));
	*head = root;

	for (; i < len; i++) {
		root = *head; // Restart next element insertion from head

		while (root) {
			if (arr[i] < root->data) {
				if (!root->left) {
					nodedata *n = malloc(sizeof(nodedata));
					n->node = root;
					n->direction = LEFT;
					push(stack, n);

					root->left = calloc(1, sizeof(avl_t));
					root->left->data = arr[i];
					root->height = height(root);
					root = root->left;

					nodedata *p;
					int direction;

					if ((p = pop(stack)) != NULL) {
						p->node->left = root;
						free(p);
						p = NULL;

						while ((p = pop(stack)) != NULL) {
							tmp = p->node;
							free(p);
							p = NULL;

							if (BalanceFactor(tmp) == -2) {
								if ((p = pop(stack)) != NULL) {
									parent = p->node;
									direction = p->direction;
									parent = parent;
								}

								if (arr[i] >= tmp->right->data) {
									if (p)
										direction == RIGHT ?  (parent->right = RightRight(tmp)) : (parent->left = RightRight(tmp));
									else
										*head = RightRight(tmp);
								} else {
									if (p)
										direction == RIGHT ? (parent->right = RightLeft(tmp)) : (parent->left = RightLeft(tmp));
									else
										*head = RightLeft(tmp);
								}
							} else if (BalanceFactor(tmp) == 2) {
								if ((p = pop(stack)) != NULL) {
									parent = p->node;
									direction = p->direction;
								}

								if (arr[i] < (tmp)->left->data) {
									if (p)
										direction == RIGHT ? (parent->right = LeftLeft(tmp)) : (parent->left = LeftLeft(tmp));
									else
										*head = LeftLeft(tmp);
								} else {
									if (p)
										direction == RIGHT ? (parent->right = LeftRight(tmp)) : (parent->left = LeftRight(tmp));
									else
										*head = LeftRight(tmp);
								}
							}

							if (p)
								free(p);

							(tmp)->height = height(tmp);
						}

						break;
					}
				}

				nodedata *n = malloc(sizeof(nodedata));
				n->node = root;
				n->direction = LEFT;
				push(stack, n);
				root = root->left;
			} else {
				if (!root->right) {
					nodedata *n = malloc(sizeof(nodedata));
					n->node = root;
					n->direction = RIGHT;
					push(stack, n);

					root->right = calloc(1, sizeof(avl_t));
					root->right->data = arr[i];
					root->height = height(root);
					root = root->right;

					nodedata *p;
					int direction;

					if ((p = pop(stack)) != NULL) {
						p->node->right = root;
						free(p);
						p = NULL;

						while ((p = pop(stack)) != NULL) {
							tmp = p->node;
							free(p);
							p = NULL;

							if (BalanceFactor(tmp) == -2) {
								if ((p = pop(stack)) != NULL) {
									parent = p->node;
									direction = p->direction;
								}

								if (arr[i] >= tmp->right->data) {
									if (p)
										direction == RIGHT ?  (parent->right = RightRight(tmp)) : (parent->left = RightRight(tmp));
									else
										*head = RightRight(tmp);
								} else {
									if (p)
										direction == RIGHT ? (parent->right = RightLeft(tmp)) : (parent->left = RightLeft(tmp));
									else
										*head = RightLeft(tmp);
								}
							} else if (BalanceFactor(tmp) == 2) {
								if ((p = pop(stack)) != NULL) {
									parent = p->node;
									direction = p->direction;
								}

								if (arr[i] < tmp->left->data) {
									if (p)
										direction == RIGHT ? (parent->right = LeftLeft(tmp)) : (parent->left = LeftLeft(tmp));
									else
										*head = LeftLeft(tmp);
								} else {
									if (p)
										direction == RIGHT ? (parent->right = LeftRight(tmp)) : (parent->left = LeftRight(tmp));
									else

										*head = LeftRight(tmp);
								}
							}

							if (p)
								free(p);

							tmp->height = height(tmp);
						}

						break;
					}
				}

				nodedata *n = malloc(sizeof(nodedata));
				n->node = root;
				n->direction = RIGHT;
				push(stack, n);
				root = root->right;
			}
		}
	}

	return head;
}

/*
 * Calculate the height of a node in AVL tree
 */
int height(avl_p node)
{
	int lh, rh;

	if (!node)
		return 0;

	node->left == NULL ? lh = 0 : (lh = 1 + node->left->height);
	node->right == NULL ? rh = 0 : (rh = 1 + node->right->height);

	if (lh >= rh)
		return lh;
	else
		return rh;
}

/*
 * Rotate a node towards right
 */
avl_p RotateRight(avl_p node)
{
	avl_p left_node = node->left;
	node->left = left_node->right;
	left_node->right = node;

	node->height = height(node);
	left_node->height = height(left_node);

	return left_node;
}

/*
 * Rotate a node towards left
 */
avl_p RotateLeft(avl_p node)
{
	avl_p right_node = node->right;
	node->right = right_node->left;
	right_node->left = node;
	
	node->height = height(node);
	right_node->height = height(right_node);

	return right_node;
}

/*
 * Adjust a right right skewed subtree
 */
avl_p RightRight(avl_p node)
{
	node = RotateLeft(node);
	return node;
}

/*
 * Adjust a left left skewed subtree
 */
avl_p LeftLeft(avl_p node)
{
	node = RotateRight(node);
	return node;
}

/*
 * Adjust a left right skewed subtree
 */
avl_p LeftRight(avl_p node)
{
	node->left = RotateLeft(node->left);
	node = RotateRight(node);

	return node;
}

/*
 * Adjust a right left skewed subtree
 */
avl_p RightLeft(avl_p node)
{
	node->right = RotateRight(node->right);
	node = RotateLeft(node);

	return node;
}

/*
 * Calculate balance factor of subtree
 */
int BalanceFactor(avl_p node)
{
	int lh, rh;

	if (!node)
		return 0;

	node->left == NULL ? lh = 0 : (lh = 1 + node->left->height);
	node->right == NULL ? rh = 0 : (rh = 1 + node->right->height);

	return (lh - rh);
}

/*
 * Delete an AVL tree from its root
 */
int delete_avl(avl_p root)
{
	int count = 0;

	if (!root) {
		log(ERROR, "root invalid.\n");
		return -1;
	}

	if (root->left)
		count += delete_avl(root->left);

	if (root->right)
		count += delete_avl(root->right);

	free(root);
	++count;

	return count;
}

/*
 * Print the values in an AVL tree in preorder
 */
int print_avl(avl_p root, avl_p parent)
{
	int count = 0;

	if (!root) {
		log(ERROR, "root invalid.\n");
		return -1;
	}

	++count;

	/* Print data value in the node */
	log(INFO, "data: %d, parent data: %d\n", root->data, parent->data);

	if (root->left) {
		log(INFO, "LEFT.\n");
		count += print_avl(root->left, root);
	}
	if (root->right) {
		log(INFO, "RIGHT.\n");
		count += print_avl(root->right, root);
	}

	return count;
}
