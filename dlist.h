#include "common.h"

#pragma once

typedef struct dlist *dlist_p;

typedef struct dlist {
	void *data;
	dlist_p next;
	dlist_p prev;
} dlist_t;

int add_head_dlist(dlist_p *head, dlist_p node);
int delete_head_dlist(dlist_p *head);
int delete_tail_dlist(dlist_p *head);
int destroy_dlist(dlist_p *head);

int count_nodes_dlist(dlist_p *head);
