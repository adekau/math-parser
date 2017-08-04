#ifndef __LINKED_LIST_C_
#define __LINKED_LIST_C_

#ifdef __C_PLUS_PLUS
extern "C" {
#endif

typedef struct ll_node_t {
	void *data;
	struct ll_node_t *next;
} ll_node;

typedef struct {
	ll_node *root;
	ll_node *last;
	size_t list_len;
} linkedlist;

linkedlist *ll_init();
char ll_empty(linkedlist *ll);
void ll_add(linkedlist *ll, const void *data);
void ll_iterate(linkedlist *ll, void *(*callback)(ll_node *node));
void ll_free(linkedlist *ll);

#ifdef __C_PLUS_PLUS
}
#endif

#endif
