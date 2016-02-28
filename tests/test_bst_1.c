/*
 * Test cases for BST
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
#include "tree.h"

int current_log_level = INFO;

/* Test BST */
int main(int argc, char **argv)
{
	int count = 0;
	bool stop = TRUE;
	tree_pp head = NULL;
	int arr[] = {10, 20, 30, 40, 50};

	log(DEBUG, "Calling generate_tree()\n");
	head = generate_tree(arr, sizeof(arr) / sizeof(arr[0]));

	if (argc == 2)
		search_BFS(head, atoi(argv[1]), stop);
	else
		search_BFS(head, 10, stop);

	count = print_tree(*head);
	log(INFO, "nodes printed: %d\n", count);

	delete_tree_node(head, 30);
	log(INFO, "\n\n");

	count = print_tree(*head);
	log(INFO, "nodes printed: %d\n", count);

	count = destroy_tree(head);
	log(INFO, "nodes deleted: %d\n", count);

	return 0;
}
