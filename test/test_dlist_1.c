/*
 * Test cases for dlist
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

#include <common.h>
#include <dlist.h>

int current_log_level = INFO;

/* Test dlist */
int main(void)
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
