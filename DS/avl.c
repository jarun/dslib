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
#include "queue.h"
#include "avl.h"

/*
 * Struct to hold an AVL node and traversal
 * direction (left or right) to child node
 */
typedef struct {
	avl_p node;
	int direction;
} nodedata, *nodedata_p;

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

	return (lh >= rh ? lh : rh);
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
	return RotateLeft(node);
}

/*
 * Adjust a left left skewed subtree
 */
avl_p LeftLeft(avl_p node)
{
	return RotateRight(node);
}

/*
 * Adjust a left right skewed subtree
 */
avl_p LeftRight(avl_p node)
{
	node->left = RotateLeft(node->left);
	return RotateRight(node);
}

/*
 * Adjust a right left skewed subtree
 */
avl_p RightLeft(avl_p node)
{
	node->right = RotateRight(node->right);
	return RotateLeft(node);
}

/*
 * Rebalance subtree tmp based on balance factor & skew
 */
bool rebalance(stack_p stack, avl_pp head, avl_p tmp, int data)
{
	nodedata_p p = NULL;
	int direction;
	avl_p parent = NULL;
	bool modified = TRUE;

	if (BalanceFactor(tmp) == -2) { /* Right subtree longer */
		p = pop(stack);
		if (p) {
			parent = p->node;
			direction = p->direction;
		}

		if (data >= tmp->right->data) { /* Right-right skewed subtree */
			if (p)
				direction == RIGHT
					?  (parent->right = RightRight(tmp))
					: (parent->left = RightRight(tmp));
			else /* If p is NULL, this is the topmost node, update *head */
				*head = RightRight(tmp);
		} else { /* Right-left skewed subtree */
			if (p)
				direction == RIGHT
					? (parent->right = RightLeft(tmp))
					: (parent->left = RightLeft(tmp));
			else
				*head = RightLeft(tmp);
		}
	} else if (BalanceFactor(tmp) == 2) { /* Left subtree longer */
		p = pop(stack);
		if (p) {
			parent = p->node;
			direction = p->direction;
		}
		/* If p is NULL, this is the topmost node, update *head */

		if (data < tmp->left->data) { /* Left-left skewed subtree */
			if (p)
				direction == RIGHT
					? (parent->right = LeftLeft(tmp))
					: (parent->left = LeftLeft(tmp));
			else
				*head = LeftLeft(tmp);
		} else { /* Left-right skewed subtree */
			if (p)
				direction == RIGHT
					? (parent->right = LeftRight(tmp))
					: (parent->left = LeftRight(tmp));
			else
				*head = LeftRight(tmp);
		}
	} else
		modified = FALSE;

	if (p)
		free(p);

	tmp->height = height(tmp);

	return modified;
}

/*
 * Delete all nodes of an AVL tree
 */
int delete_avl_nodes(avl_p root)
{
	int count = 0;

	if (!root) {
		log(ERROR, "root invalid.\n");
		return 0;
	}

	if (root->left)
		count += delete_avl_nodes(root->left);

	if (root->right)
		count += delete_avl_nodes(root->right);

	free(root);
	root = NULL;

	return ++count;
}

/*=======================================================*/
/*            Library exposed APIs start here            */
/*=======================================================*/

/*
 * Generate an AVL tree iteratively from an array of integers
 */
avl_pp generate_avl(int *arr, int len)
{
	int i = 0;
	avl_pp head = NULL;

	if (!arr || !len) {
		log(ERROR, "Invalid array.\n");
		return NULL;
	}

	head = init_avl();

	for (; i < len; i++) {
		if (insert_avl(head, arr[i]) == FALSE) {
			log(ERROR, "Insertion failed.\n");
			destroy_avl(head);
			return NULL;
		}
	}

	return head;
}

/*
 * Initialize an AVL tree with empty root node
 */
avl_pp init_avl(void)
{
	avl_pp head = calloc(1, sizeof(avl_p));
	*head = NULL;

	return head;
}

/*
 * Insert a new node into AVL tree
 */
bool insert_avl(avl_pp head, int val)
{
	avl_p root = NULL;
	nodedata_p p = NULL;
	nodedata_p n = NULL;
	bool modified;
	/* Stack to rebalance each subtree bottom-up after insertion */
	stack_p stack = get_stack();

	if (!head) {
		log(ERROR, "Initialize AVL tree first\n");
		return FALSE;
	}

	root = *head;

	if (!root) {
		root = (avl_p) calloc(1, sizeof(avl_t));
		root->data = val;
		*head = root;

		return TRUE;
	}

	while (root) {
		if (val < root->data) {
			if (!root->left) {
				/* Create an AVL node for new value */
				root->left = calloc(1, sizeof(avl_t));
				root->left->data = val;
				root->height = height(root);

				modified = FALSE;

				/* Unwind stack & rebalance nodes (only once) */
				while ((p = pop(stack)) != NULL) {
					/* One rebalance for one insertion */
					if (!modified) {
						modified = rebalance(stack,
								head, p->node, val);
					}

					free(p);
				}

				break;
			}

			/* Push the parent node and traversal
			   direction in stack as we traverse down */
			n = malloc(sizeof(nodedata));
			n->node = root;
			n->direction = LEFT;
			push(stack, n);

			/* Traverse further left */
			root = root->left;
		} else {
			if (!root->right) {
				root->right = calloc(1, sizeof(avl_t));
				root->right->data = val;
				root->height = height(root);

				modified = FALSE;

				while ((p = pop(stack)) != NULL) {
					if (!modified) {
						modified = rebalance(stack,
								head, p->node, val);
					}

					free(p);
				}

				break;
			}

			n = malloc(sizeof(nodedata));
			n->node = root;
			n->direction = RIGHT;
			push(stack, n);

			root = root->right;
		}
	}

	destroy_stack(stack);

	return TRUE;
}

/*
 * Destroy an AVL tree
 */
int destroy_avl(avl_pp head)
{
	int count = 0;

	if (!head) {
		log(ERROR, "head invalid.\n");
		return -1;
	}

	count = delete_avl_nodes(*head);

	free(head);
	head = NULL;

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
	log(INFO, "data: %6d,  parent: %6d\n", root->data, parent->data);

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

/*
 * AVL Tree Breadth First Search implementation
 * Implements iterative search using a Queue
 * Checks for a match before adding a node to Queue
 *
 * PARAMS
 * ------
 * root: pointer to the root node pointer of an AVL tree
 * val : value to search
 * stop: stop if val is found
 */
bool search_BFS_avl(avl_pp root, int val, bool stop)
{
	avl_p node = NULL;
	queue_p queue = NULL;
	int ret = FALSE;

	if (!root || !*root) {
		log(ERROR, "avl tree or root node is NULL!\n");
		return FALSE;
	}

	/* Check for a match in root node */
	node = *root;
	if (node->data == val) {
		log(INFO, "FOUND %d\n", val);

		if (stop)
			return TRUE;
	}

	queue = get_queue();

	/* Add root node to Queue */
	if (!enqueue(queue, *root)) {
		log(ERROR, "enqueue failed!\n");
		destroy_queue(queue);
		return FALSE;
	}

	/* Loop through all nodes in the Queue */
	while ((node = dequeue(queue)) != NULL) {
		log(INFO, "tracking...\n");

		/* Process left child of node */
		if (node->left) {
			if (node->left->data == val) {
				log(INFO, "FOUND %d\n", val);
				ret = TRUE;

				if (stop)
					break;
			}

			/* Add left child to Queue */
			if (!enqueue(queue, node->left)) {
				log(ERROR, "enqueue failed!\n");
				destroy_queue(queue);
				return FALSE;
			}
		}

		/* Process right child of node */
		if (node->right) {
			if (node->right->data == val) {
				log(INFO, "FOUND %d\n", val);
				ret = TRUE;

				if (stop)
					break;
			}

			/* Add right child to Queue */
			if (!enqueue(queue, node->right)) {
				log(ERROR, "enqueue failed!\n");
				destroy_queue(queue);
				return FALSE;
			}
		}
	}

	/* Report if no match was found */
	if (!ret)
		log(INFO, "NOT FOUND\n");

	destroy_queue(queue);

	return ret;
}
