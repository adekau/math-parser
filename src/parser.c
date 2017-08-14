#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "tokenizer.h"
#include "linkedlist.h"

parser *parser_init() {
	parser *p = calloc(1, sizeof(*p));
	return p;
}

// will need something to clone the linkedlist I think...
void parse(linkedlist *tokens) {
	linkedlist *tokens_clone
}
