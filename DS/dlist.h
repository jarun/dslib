#include "common.h"

#pragma once

/* Circular Doubly Linked List abstraction */
typedef struct dlist *dlist_p;

typedef struct dlist {
	void *data;
	dlist_p next;
	dlist_p prev;
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
