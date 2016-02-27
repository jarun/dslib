/*
 * Iterative Binary Search Tree implementation
 *
 * Author: Ananya Jana <ananya.jana@gmail.com>
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

#include "queue.h"
#include "stack.h"
#include "tree.h"

/*
 * Delete all nodes of a tree
 */
int delete_tree_nodes(tree_p root)
{
	int count = 0;

	if (!root) {
		log(ERROR, "root invalid.\n");
		return -1;
	}

	if (root->left)
		count += delete_tree_nodes(root->left);

	if (root->right)
		count += delete_tree_nodes(root->right);

	free(root);
	root = NULL;

	return ++count;
}

/*=======================================================*/
/*            Library exposed APIs start here            */
/*=======================================================*/

/*
 * Generate a tree from an array of integers
 */
tree_pp generate_tree(int *arr, int len)
{
	int i = 0;
	tree_pp head = NULL;

	if (!arr || !len) {
		log(ERROR, "Invalid array.\n");
		return NULL;
	}

	head = init_tree();

	for (; i < len; i++) {
		if (insert_tree_node(head, arr[i]) == FALSE) {
			log(ERROR, "Insertion failed.\n");
			destroy_tree(head);
			return NULL;
		}
	}

	return head;
}

/*
 * Initialize a tree with empty root node
 */
tree_pp init_tree(void)
{
	tree_pp head = calloc(1, sizeof(tree_p));
	*head = NULL;

	return head;
}

/*
 * Insert a new node into tree
 */
bool insert_tree_node(tree_pp head, int val)
{
	tree_p root = NULL;

	if (!head) {
		log(ERROR, "Initialize tree first.\n");
		return FALSE;
	}

	root = *head;

	if (!root) {
		root = (tree_p) calloc(1, sizeof(tree_t));
		root->data = val;
		*head = root;

		return TRUE;
	}

	while (root) {
		if (val < root->data) {
			if (!root->left) {
				root->left = calloc(1, sizeof(tree_t));
				root = root->left;
				root->data = val;
				return TRUE;
			}

			root = root->left;
		} else { /* Insert equal or greater elements to right */
			if (!root->right) {
				root->right = calloc(1, sizeof(tree_t));
				root = root->right;
				root->data = val;
				return TRUE;
			}

			root = root->right;
		}
	}

	return FALSE;
}

/*
 * Delete a node from tree
 */
bool delete_tree_node(tree_pp head, int val)
{
	tree_p root = NULL;
	tree_p prev = NULL;
	int direction;

	if (!head) {
		log(ERROR, "Initialize tree first.\n");
		return FALSE;
	}

	root = *head;

	while (root) {
		if (val < root->data) {
			if (!root->left)
				break;

			prev = root;
			direction = LEFT;
			root = root->left;
		} else if (val > root->data) { /* Greater elements are in right subtree */
			if (!root->right)
				break;

			prev = root;
			direction = RIGHT;
			root = root->right;
		} else { /* Match found */
			if (!root->left) {
				if (prev) {
					if (direction == LEFT)
						prev->left = root->right;
					else
						prev->right = root->right;
				} else /* This was the root node */
					*head = NULL;

				free(root);
				return TRUE;
			} else if (!root->right) {
				if (prev) {
					if (direction == LEFT)
						prev->left = root->left;
					else
						prev->right = root->left;
				} else /* This was the root node */
					*head = NULL;

				free(root);
				return TRUE;
			} else { /* Both subtrees have children */
				/* Delete inorder successor */
				tree_p min = root->right;
				while (min->left)
					min = min->left;

				root->data = min->data;
				/* Let's use some recursion here */
				delete_tree_node(&(root->right), min->data);

				return TRUE;
			}
		}
	}

	/* Fall through if root is NULL */
	return FALSE;
}

/*
 * Destroy a tree
 */
int destroy_tree(tree_pp head)
{
	int count = 0;

	if (!head) {
		log(ERROR, "head invalid.\n");
		return -1;
	}

	count = delete_tree_nodes(*head);

	free(head);
	head = NULL;

	return count;
}

/*
 * Print the values in a tree in preorder
 */
int print_tree(tree_p root)
{
	int count = 0;

	if (!root) {
		log(ERROR, "root invalid.\n");
		return -1;
	}

	log(DEBUG, "data: %d.\n", root->data);
	++count;

	if (root->left)
		count += print_tree(root->left);
	if (root->right)
		count += print_tree(root->right);

	return count;
}

/*
 * Tree Breadth First Search implementation
 * Implements iterative search using a Queue
 * Checks for a match before adding a node to Queue
 *
 * PARAMS
 * ------
 * root: pointer to the root node pointer of a tree
 * val : value to search
 * stop: stop if val is found
 */
bool search_BFS(tree_pp root, int val, bool stop)
{
	tree_p node = NULL;
	queue_p queue = NULL;
	int ret = FALSE;

	if (!root || !*root) {
		log(ERROR, "tree or root node is NULL!\n");
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

/*
 * Tree Depth First Search implementation
 * Implements iterative search using a Stack
 * Checks for a match before adding a node to Stack
 *
 * PARAMS
 * ------
 * root: pointer to the root node pointer of a tree
 * val : value to search
 * stop: stop if val is found
 */
bool search_DFS(tree_pp root, int val, bool stop)
{
	int ret = FALSE;
	tree_p node = NULL;
	stack_p stack = NULL;

	if (!root || !*root) {
		log(ERROR, "tree or root node is NULL.\n");
		return FALSE;
	}

	/* Check for a match in root node */
	node = *root;
	if (node->data == val) {
		log(INFO, "FOUND %d\n", val);

		if (stop)
			return TRUE;
	}

	stack = get_stack();

	/* Add root node to Stack */
	if (!push(stack, *root)) {
		log(ERROR, "push failed!\n");
		destroy_stack(stack);
		return FALSE;
	}

	/* Process all valid nodes */
	while (node) {
		log(INFO, "tracking...\n");

		/* Match and add complete
		   left subtree to Stack */
		while (node->left) {
			if (node->left->data == val) {
				log(INFO, "FOUND %d\n", val);
				ret = TRUE;

				if (stop) {
					node = NULL;
					break;
				}
			}

			/* Add node to stack */
			if (!push(stack, node->left)) {
				log(ERROR, "push failed!\n");
				destroy_stack(stack);
				return FALSE;
			}

			node = node->left;
		}

		while ((node = pop(stack)) != NULL) {
			/* Process right child of node */
			if (node->right) {
				if (node->right->data == val) {
					log(INFO, "FOUND %d\n", val);
					ret = TRUE;

					if (stop) {
						node = NULL;
						break;
					}
				}

				/* Add right child to Stack */
				if (!push(stack, node->right)) {
					log(ERROR, "push failed!\n");
					destroy_stack(stack);
					return FALSE;
				}

				node = node->right;
				/* Break inner loop if there's a right node */
				break;
			}
		}
	}

	/* Report if no match was found */
	if (!ret)
		log(INFO, "NOT FOUND\n");

	destroy_stack(stack);

	return ret;
}
