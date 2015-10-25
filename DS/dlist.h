#include "common.h"

#pragma once

typedef struct dlist *dlist_p;

typedef struct dlist {
	void *data;
	dlist_p next;
	dlist_p prev;
} dlist_t, *dlist_p, **dlist_pp;

int add_head_dlist(dlist_pp head, dlist_p node);

void *get_head_dlist(dlist_pp head);
void *get_tail_dlist(dlist_pp head);

int delete_head_dlist(dlist_pp head);
int delete_tail_dlist(dlist_pp head);
int destroy_dlist(dlist_pp head);

int count_nodes_dlist(dlist_pp head);
