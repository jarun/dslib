/*
 * Circular Doubly Linked List abstraction
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

#pragma once

/* Circular Doubly Linked List ADT */
typedef struct dlist {
	void *data;
	struct dlist *next;
	struct dlist *prev;
} dlist_t, *dlist_p, **dlist_pp;

/* Add node at head of list */
int add_head_dlist(dlist_pp head, dlist_p node);

/* Get the head of list */
void *get_head_dlist(dlist_pp head);

/* Get the tail of list */
void *get_tail_dlist(dlist_pp head);

/* Delete the head of list */
int delete_head_dlist(dlist_pp head);

/* Delete the tail of list */
int delete_tail_dlist(dlist_pp head);

/* Clean up list */
int destroy_dlist(dlist_pp head);

/* Count total nodes in list */
int count_nodes_dlist(dlist_pp head);
