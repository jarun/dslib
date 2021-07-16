/*
 * Circular Doubly Linked List implementation
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

#include "dlist.h"

/*
 * Add a node to the head of dlist
 */
int add_head_dlist(dlist_pp head, dlist_p node)
{
	if (!node) {
		log(ERROR, "node is NULL!\n");
		return -1;
	}

	if (!head) {
		log(ERROR, "head is NULL!\n");
		return -1;
	}

	if (!*head) {
		node->next = node;
		node->prev = node;
		*head = node;

		return 1;
	}

	node->next = *head; /* Current head become head->next */
	node->prev = (*head)->prev;
	(*head)->prev->next = node;
	(*head)->prev = node;
	*head = node;

	return 1;
}

/*
 * Get the value in the head node of dlist
 * The node is not deleted
 */
void *get_head_dlist(dlist_pp head)
{
	if (!head || !*head) {
		log(DEBUG, "head or first node is NULL!\n");
		return NULL;
	}

	return (*head)->data;
}

/*
 * Get the value in the tail node of dlist
 * The node is not deleted
 */
void *get_tail_dlist(dlist_pp head)
{
	if (!head || !*head) {
		log(DEBUG, "head or first node is NULL!\n");
		return NULL;
	}

	return (*head)->prev->data;
}

/*
 * Delete the head node of dlist
 */
int delete_head_dlist(dlist_pp head)
{
	dlist_p tmp;

	if (!head || !*head) {
		log(DEBUG, "No nodes to delete!\n");
		return -1;
	}

	if (*head == (*head)->next) {
		free(*head);
		*head = NULL;
		return 1;
	}

	tmp = *head;
	(*head)->data = NULL;
	(*head)->prev->next = (*head)->next;
	(*head)->next->prev = (*head)->prev;
	*head = (*head)->next; /* head->next becomes next head */

	free(tmp);

	return 1;
}

/*
 * Delete the tail node of dlist
 */
int delete_tail_dlist(dlist_pp head)
{
	dlist_p tmp;

	if (!head || !*head) {
		log(DEBUG, "head or first node is NULL!\n");
		return -1;
	}

	if (*head == (*head)->next) {
		free(*head);
		*head = NULL;
		return 1;
	}

	tmp = (*head)->prev;
	tmp->data = NULL;
	tmp->prev->next = tmp->next; /* tail->prev becomes new tail */
	tmp->next->prev = tmp->prev;

	free(tmp);

	return 1;
}

/*
 * Deallocate all memory and destroy the dlist
 * Returns the number of nodes deleted
 */
int destroy_dlist(dlist_pp head)
{
	dlist_p tmp;
	int deleted = 0;

	if (!head) {
		log(DEBUG, "head is NULL.\n");
		return -1;
	}

	if (!*head) {
		log(DEBUG, "No nodes to delete.\n");
		return 0;
	}

	/* Set tail->next to NULL to end deletion loop */
	(*head)->prev->next = NULL;

	while (*head) {
		tmp = *head;
		(*head)->data = NULL;
		(*head)->prev = NULL;
		*head = (*head)->next;

		free(tmp);
		deleted++;
	}

	return deleted;
}

/*
 * Count the total number of nodes in the dlist
 */
int count_nodes_dlist(dlist_pp head)
{
	dlist_p tmp;
	int count = 0;

	if (!head || !*head) {
		log(DEBUG, "head or first node is NULL!\n");
		return -1;
	}

	tmp = *head;

	do {
		count++;
		tmp = tmp->next;
	} while (tmp != *head);

	return count;
}
