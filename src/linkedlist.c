#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

char ll_empty(linkedlist *ll) {
	return !ll->last || !ll->root;
}

static inline ll_node *ll_node_init(const void *data) {
	ll_node *node = calloc(1, sizeof(*node));
	node->data = (void *)data;
	return node;
}

linkedlist *ll_init() {
	linkedlist *ll = calloc(1, sizeof(*ll));
	ll->list_len = 0;

	return ll;
}

void ll_add(linkedlist *ll, const void *data) {
	if (ll_empty(ll)) {
		ll_node *new_node = ll_node_init(data);
		ll->last = ll->root = new_node;
		ll->list_len ++;
		return;
	} 

	ll_node *new_node = ll_node_init(data);
	ll->last->next = new_node;
	ll->last = new_node;
	ll->list_len ++;
}

void ll_iterate(linkedlist *ll, void *(*callback)(ll_node *node)) {
	if (ll_empty(ll)) {
		return;
	}

	ll_node *cur_node = ll->root;
	for (int i = 0; i < ll->list_len; i++) {
		callback(cur_node);
		if (cur_node->next) cur_node = cur_node->next;
	}
}

void ll_free(linkedlist *ll, ll_node *recurse) {
	if (ll_empty(ll)) {
		free(ll);
		return;
	}

	ll_node *cursor, *tmp;
	cursor = ll->root;
	ll->root = NULL;
	ll->last = NULL;
	while (cursor != NULL) {
		tmp = cursor->next;
		free(cursor);
		cursor = tmp;
	}

	free(ll);
}
