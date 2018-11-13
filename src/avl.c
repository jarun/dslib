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

		if (data >= tmp->right->keyNode) { /* Right-right skewed subtree */
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

		if (data < tmp->left->keyNode) { /* Left-left skewed subtree */
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

	avl_pp head = NULL;

	if (!arr || !len) {
		log(ERROR, "Invalid array.\n");
		return NULL;
	}

	head = init_avl();
	for (int i = 0; i < len; i++) {
		if (insert_avl_node(head, i, arr[i]) == FALSE) {
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
bool insert_avl_node(avl_pp head, int key, int data)
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
		root->keyNode = key;
		root->data = data;

		*head = root;

		return TRUE;
	}
	//until current node isn't Null
	while (root) {
		//if keyNod < of key to add, go left of tree
		if (key < root->keyNode) {
			//if left null, add node as left son
			if (!root->left) {
				/* Create an AVL node for new value */
				root->left = calloc(1, sizeof(avl_t));
				root->left->keyNode = key;
				root->left->data = data;
				root->height = height(root);

				modified = FALSE;

				/* Unwind stack & rebalance nodes (only once) */
				while ((p = pop(stack)) != NULL) {
					/* One rebalance for one insertion */
					if (!modified) {
						modified = rebalance(stack,head, p->node, key);
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
		} else {    //key to add is >= then current key node
			//if right son null add son on it
			if (!root->right) {
				root->right = calloc(1, sizeof(avl_t));
				root->right->keyNode = key;
				root->right->data = data;
				root->height = height(root);

				modified = FALSE;

				while ((p = pop(stack)) != NULL) {
					if (!modified) {
						modified = rebalance(stack,
						                     head, p->node, key);
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
 * Delete a node from AVL tree
 * Recursive method
 */
bool delete_avl_node(avl_pp head, int key)
{
	avl_p node;
	avl_p tmp;

	if (!head) {
		log(ERROR, "Initialize AVL tree first\n");
		return FALSE;
	}

	node = *head;
	if (!node) {
		log(ERROR, "No nodes to delete\n");
		return FALSE;
	}

	if (key > node->keyNode) {
		if (!node->right)
			return FALSE;

		if (delete_avl_node(&(node->right), key) == FALSE)
			return FALSE;

		if (BalanceFactor(node) == 2) {
			if (BalanceFactor(node->left) >= 0)
				node = LeftLeft(node);
			else
				node = LeftRight(node);
		}
	} else if (key < node->keyNode) {
		if (!node->left)
			return FALSE;

		if (delete_avl_node(&(node->left), key) == FALSE)
			return FALSE;

		if (BalanceFactor(node) == -2) {
			if (BalanceFactor(node->right) <= 0)
				node = RightRight(node);
			else
				node = RightLeft(node);
		}
	} else { /* Match found */
		if (node->right) {  /* Delete the inorder successor */
			tmp = node->right;
			while (tmp->left)
				tmp = tmp->left;

			node->keyNode = tmp->keyNode;
			if (delete_avl_node(&(node->right), tmp->keyNode) == FALSE)
				return FALSE;

			if (BalanceFactor(node) == 2) {
				if (BalanceFactor(node->left) >= 0)
					node = LeftLeft(node);
				else
					node = LeftRight(node);
			}
		} else {
			*head = node->left;
			return TRUE;
		}
	}

	node->height = height(node);
	*head = node;
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

	/* Print keyNode value in the node */
	log(INFO, "keyNode: %6d:%d,  parent: %6d\n", root->keyNode, root->data, parent->keyNode);

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
 * stop: TRUE: stop if Key is found and return val.
 *       FALSE: continue visiting of tree, print debug info and return the val of the last key.
 */

int search_BFS_avl(avl_pp root, int key, bool stop)
{
	//return -1 is error
	//return -2 is not Found
	avl_p node = NULL;
	queue_p queue = NULL;
	int ret = -2;   //start with no found

	if (!root || !*root) {
		log(ERROR, "avl tree or root node is NULL!\n");
		return -2;  //because avl is empty so key is not found
	}

	/* Check for a match in root node */
	node = *root;
	if (node->keyNode == key) {

		if(!stop) log(INFO, "FOUND %d\n", key);

		if (stop) return node->data;
		else ret = node->data;
	}

	queue = get_queue();

	/* Add root node to Queue */
	if (!enqueue(queue, *root)) {
		log(ERROR, "enqueue failed!\n");
		destroy_queue(queue);
		return -1;
	}

	/* Loop through all nodes in the Queue */
	while ((node = dequeue(queue)) != NULL) {
		if (!stop) log(INFO, "tracking...\n");

		/* Process left child of node */
		if (node->left) {
			if (node->left->keyNode == key) {
				if (!stop) log(INFO, "FOUND %d\n", key);
				destroy_queue(queue);
				if (stop) return node->left->data;
				else ret = node->left->data;
				break;
			}

			/* Add left child to Queue */
			if (!enqueue(queue, node->left)) {
				log(ERROR, "enqueue failed!\n");
				destroy_queue(queue);
				return -1;
			}
		}

		/* Process right child of node */
		if (node->right) {
			if (node->right->keyNode == key) {
				if (!stop) log(INFO, "FOUND %d\n", key);
				destroy_queue(queue);
				if (stop) return node->right->data;
				else ret = node->left->data;
				break;
			}

			/* Add right child to Queue */
			if (!enqueue(queue, node->right)) {
				log(ERROR, "enqueue failed!\n");
				destroy_queue(queue);
				return -1;
			}
		}
	}

	/* Report if no match was found */

	destroy_queue(queue);

	return ret;
}

/*=======================================================*/
/*         Library ThreadSafe APIs start here            */
/*=======================================================*/

/*
 * Generate an AVL tree iteratively from an array of integers
 */
avl_pp_S generate_avl_S(int *arr, int len)
{
	int i = 0;
	avl_pp_S head;

	if (!arr || !len) {
		log(ERROR, "Invalid array.\n");
		head.avlRoot = NULL;
		return head;
	}

	head = init_avl_S();

	for (; i < len; i++) {
		if (insert_avl_node(head.avlRoot, i, arr[i]) == FALSE) {
			log(ERROR, "Insertion failed.\n");
			destroy_avl(head.avlRoot);
			head.avlRoot = NULL;
			return head;
		}
	}

	return head;
}

avl_pp_S init_avl_S(void)
{
	avl_pp_S head ;

	head.semId = semInit();
	if(head.semId == -1)
	{
		perror("Sem Setup failed");
		head.avlRoot = NULL;
		return head;
	}

	head.avlRoot = calloc(1, sizeof(avl_p));
	*head.avlRoot = NULL;

	return head;
}

bool insert_avl_node_S(avl_pp_S head, int key, int data)
{
	bool ret;
	lockWriteSem(head.semId);
	ret = insert_avl_node(head.avlRoot, key, data);
	unlockWriteSem(head.semId);
	return ret;
}

bool delete_avl_node_S(avl_pp_S head, int key)
{
	bool ret;
	lockWriteSem(head.semId);
	ret = delete_avl_node(head.avlRoot, key);
	unlockWriteSem(head.semId);
	return ret;
}

int search_BFS_avl_S(avl_pp_S root, int key, bool stop)
{
	int ret;
	lockReadSem(root.semId);
	ret = search_BFS_avl( root.avlRoot, key, stop);
	unlockReadSem(root.semId);
	return ret;
}

int print_avl_S(avl_pp_S root)
{
	int ret;
	lockReadSem(root.semId);
	ret = print_avl(*root.avlRoot, *root.avlRoot);
	unlockReadSem(root.semId);
	return ret;
}
