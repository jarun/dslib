/*
 * Test cases for dslib
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
#include "queue.h"
#include "stack.h"
#include "tree.h"
#include "avl.h"

int current_log_level = INFO;

int main(int argc, char **argv)
{
	int count = 0;
	bool stop = TRUE;
	avl_pp root = NULL;
	int arr[] = {30, 110, 10, 90, 120, 150, 70, 140, 40, 130, 20, 50, 100, 80, 60};
	//int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150};

	log(DEBUG, "Calling generate_avl()\n");
	root = generate_avl(arr, sizeof(arr) / sizeof(arr[0]));

	if (argc == 2)
		search_BFS_avl(root, atoi(argv[1]), stop);
	else
		search_BFS_avl(root, 10, stop);

	count = print_avl(*root, *root);
	log(INFO, "nodes printed: %d\n", count);

	count = destroy_avl(root);
	log(INFO, "nodes deleted: %d\n", count);

	return 0;
}

#if 0
int main(int argc, char **argv)
{
	int count = 0;
	bool stop = TRUE;
	tree_pp root = NULL;
	int arr[] = {10, 20, 30, 40, 50};

	log(DEBUG, "Calling generate_tree()\n");
	root = generate_tree(arr, sizeof(arr) / sizeof(arr[0]));

	if (argc == 2)
		search_BFS(root, atoi(argv[1]), stop);
	else
		search_BFS(root, 10, stop);

	count = print_tree(*root);
	log(INFO, "nodes printed: %d\n", count);

	count = delete_tree(*root);
	log(INFO, "nodes deleted: %d\n", count);

	return 0;
}

int main()
{
	int count = 5;
	int arr[5] = {0, 1, 2, 3, 4};
	int *val;

	stack_p stack = get_stack();

	while (count--) {
		if (push(stack, &arr[count]) == FALSE) {
			log(ERROR, "push failed!\n");
			destroy_stack(stack);
			return -1;
		}

		log(DEBUG, "Node added\n");
	}

	count = 5;

	while (count) {
		val = pop(stack);
		if (val)
			log(DEBUG, "arr[%d] = %d\n", count, (int)*val);
		else
			log(ERROR, "pop failed!\n");

		count--;
	}

	destroy_stack(stack);

	return 0;
}

int main()
{
	int count = 5;
	int arr[5] = {0, 1, 2, 3, 4};
	int *val;

	queue_p queue = get_queue();

	while (count) {
		if (enqueue(queue, &arr[count]) == FALSE) {
			log(ERROR, "enqueue failed!\n");
			destroy_queue(queue);
			return -1;
		}

		log(DEBUG, "Node added\n");

		count--;
	}

	count = 5;

	while (count) {
		val = dequeue(queue);
		if (val)
			log(DEBUG, "arr[%d] = %d\n", count, (int)*val);
		else
			log(ERROR, "dequeue failed!\n");

		count--;
	}

	destroy_queue(queue);

	return 0;
}

int main()
{
	int count = 5;

	dlist_p *head_pp = calloc(1, sizeof(dlist_p *));

	while (count) {
		dlist_p node_p = calloc(1, sizeof(dlist_t));

		log(DEBUG, "node address %p\n", node_p);
		if (add_head_dlist(head_pp, node_p) == -1) {
			log(ERROR, "add_head_dlist failed!\n");
			return -1;
		}

		log(DEBUG, "Node added\n");

		count--;
	}

	log(DEBUG, "Total nodes1: %d\n", count_nodes_dlist(head_pp));

	if (delete_head_dlist(head_pp)) {
		log(DEBUG, "Total nodes after head delete: %d\n",
				count_nodes_dlist(head_pp));
	} else {
		log(ERROR, "delete_head_dlist failed!\n");
		return -1;
	}

	log(DEBUG, "Total nodes2: %d\n", count_nodes_dlist(head_pp));

	if (delete_tail_dlist(head_pp)) {
		log(DEBUG, "Total nodes after tail delete: %d\n",
				count_nodes_dlist(head_pp));
	} else {
		log(ERROR, "delete_tail_dlist failed!\n");
		return -1;
	}

	log(DEBUG, "Nodes destroyed: %d\n", destroy_dlist(head_pp));
	log(DEBUG, "Total nodes: %d\n", count_nodes_dlist(head_pp));

	free(head_pp);

	return 0;
}
#endif
