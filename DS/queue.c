/*
 * Queue implementation
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

#include "queue.h"

/*
 * Create a new Queue
 * Alocate a head node
 */
queue_p get_queue(void)
{
	queue_p queue = calloc(1, sizeof(queue_t));

	queue->head = calloc(1, sizeof(dlist_pp));
	return queue;
}

/*
 * Add a value to Queue
 * Allocates a new dlist node and inserts value
 */
bool enqueue(queue_p queue, void *val)
{
	dlist_p nodeptr = calloc(1, sizeof(dlist_t));

	nodeptr->data = val;

	if (add_head_dlist(queue->head, nodeptr))
		return TRUE;
	else
		return FALSE;
}

/*
 * Remove the value at the front of the Queue
 * Deallocates the dlist node holding the value
 */
void *dequeue(queue_p queue)
{
	void *data = get_tail_dlist(queue->head);

	if (delete_tail_dlist(queue->head) == -1)
		log(DEBUG, "head or first node is NULL!\n");

	return data;
}

/*
 * Deallocate all dlist nodes
 * Destroy Queue
 */
bool destroy_queue(queue_p queue)
{
	if (destroy_dlist(queue->head) == -1)
		return FALSE;

	free(queue->head);
	free(queue);

	return TRUE;
}
