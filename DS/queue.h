/*
 * Queue abstraction
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

#pragma once

/* Queue ADT using a circular doubly linked list */
typedef struct {
	dlist_pp head;
} queue_t, *queue_p;

/* Create a new Queue */
queue_p get_queue(void);

/* Add a value to Queue */
bool enqueue(queue_p queue, void *val);

/* Remove a value from Queue */
void *dequeue(queue_p queue);

/* Check if the Queue is empty */
bool isQueueEmpty(queue_p queue);

/* Clean up Queue */
bool destroy_queue(queue_p queue);
