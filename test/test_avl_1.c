/*
 * Test cases for AVL tree
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
#include "avl.h"

int current_log_level = INFO;

int main(int argc, char **argv)
{
	int count = 0;
	bool stop = TRUE;
	avl_pp head = init_avl();
	int arr[] = {30, 110, 10, 90, 120, 150, 70,
		140, 40, 130, 20, 50, 100, 80, 60};
	/* int arr[] = {10, 20, 30, 40, 50, 60, 70, 80,
		90, 100, 110, 120, 130, 140, 150}; */
	int len = sizeof(arr) / sizeof(arr[0]);

	for (; count < len; count++) {
		if (insert_avl_node(head, arr[count]) == FALSE) {
			log(ERROR, "Insertion failed.\n");
			destroy_avl(head);
			return 0;
		}
	}

	if (argc == 2)
		search_BFS_avl(head, atoi(argv[1]), stop);
	else
		search_BFS_avl(head, 10, stop);

	count = print_avl(*head, *head);
	log(INFO, "nodes printed: %d\n\n\n", count);

	if (delete_avl_node(head, 110) == TRUE)
		log(INFO, "AVL node deleted\n");
	count = print_avl(*head, *head);
	log(INFO, "nodes printed: %d\n", count);

	count = destroy_avl(head);
	log(INFO, "nodes deleted: %d\n", count);

	return 0;
}
