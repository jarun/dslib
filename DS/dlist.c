#include "dlist.h"

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

	node->next = *head;
	node->prev = (*head)->prev;
	(*head)->prev->next = node;
	(*head)->prev = node;
	*head = node;

	return 1;
}

void *get_head_dlist(dlist_pp head)
{
	if (!head || !*head) {
		log(ERROR, "head or first node is NULL!\n");
		return NULL;
	}

	return (*head)->data;
}

void *get_tail_dlist(dlist_pp head)
{
	if (!head || !*head) {
		log(ERROR, "head or first node is NULL!\n");
		return NULL;
	}

	return (*head)->prev->data;
}

int delete_head_dlist(dlist_pp head)
{
	dlist_p tmp;

	if (!head || !*head) {
		log(ERROR, "No nodes to delete!\n");
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
	*head = (*head)->next;

	free(tmp);

	return 1;
}

int delete_tail_dlist(dlist_pp head)
{
	dlist_p tmp;

	if (!head || !*head) {
		log(ERROR, "head or first node is NULL!\n");
		return -1;
	}

	if (*head == (*head)->next) {
		free(*head);
		*head = NULL;
		return 1;
	}

	tmp = (*head)->prev;
	tmp->data = NULL;
	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;

	free(tmp);

	return 1;
}

int destroy_dlist(dlist_pp head)
{
	dlist_p tmp;
	int deleted = 0;

	if (!head || !*head) {
		log(INFO, "No nodes to delete.\n");
		return -1;
	}

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

int count_nodes_dlist(dlist_pp head)
{
	dlist_p tmp;
	int count = 0;

	if (!head || !*head) {
		log(ERROR, "head or first node is NULL!\n");
		return -1;
	}

	tmp = *head;

	do {
		count++;
		tmp = tmp->next;
	} while (tmp != *head);

	return count;
}
