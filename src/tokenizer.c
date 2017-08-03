#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include "tokenizer.h"

static token_info *token_info_init(char *regex, int token) {
	token_info *t = calloc(1, sizeof(*t));
	regex_t regc;
	char *freg = calloc(strlen(regex) + 3, sizeof(*freg));
	int ereg; // Function error checking variable.
	
	ereg = sprintf(freg, "^(%s)", regex);
	if (!ereg) {
		fprintf(stderr, "Could not generate the regex string\n");
	}

	ereg = regcomp(&regc, freg, 0);

	if (ereg) {
		fprintf(stderr, "Could not compile regex\n");
		exit(EXIT_FAILURE);
	}

	t->regc = regc;
	t->token = token;

	return t;	
}

tokenizer *tokenizer_init() {
	tokenizer *t = calloc(1, sizeof(*t));
	t->infos = ll_init();
	
	return t;
}

void tokenizer_add(tokenizer *t, char *regex, int token) {
	token_info *info = token_info_init(regex, token);
	ll_add(t->infos, (const void *)info);
}

void *print_tokens(ll_node *node) {
	token_info *info = (token_info *)(node->data);
	printf("Token: %c\n", info->token);
	return NULL;
}

int main(int argc, char **argv) {
	tokenizer *tokenizer = tokenizer_init();
	tokenizer_add(tokenizer, "[A-Z]", (int)'B');
	tokenizer_add(tokenizer, "[A-Z]", (int)'Y');
	tokenizer_add(tokenizer, "[A-Z]", (int)'O');
	tokenizer_add(tokenizer, "[A-Z]", (int)'B');
	tokenizer_add(tokenizer, "[0-9]", (int)'!');
	ll_iterate(tokenizer->infos, &print_tokens);
	return EXIT_SUCCESS;
}
