#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include "tokenizer.h"

// It appears as though strdup is not very portable.
char *strdup(const char *src) {
    size_t len = strlen(src) + 1;
    char *s = malloc(len);
    if (s == NULL)
        return NULL;
    return (char *)memcpy(s, src, len);
}

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
		fprintf(stderr, "Could not compile regex %s\n", freg);
		exit(EXIT_FAILURE);
	}

	t->regc = regc;
	t->token = token;

	return t;	
}

token *token_init(const int tok, char *sequence) {
	token *t = calloc(1, sizeof(*t));
	t->token = tok;
	t->sequence = sequence;

	return t;
}

tokenizer *tokenizer_init() {
	tokenizer *t = calloc(1, sizeof(*t));
	t->infos = ll_init();
	t->tokens = ll_init();

	return t;
}

void tokenizer_add(tokenizer *t, char *regex, int token) {
	token_info *info = token_info_init(regex, token);
	ll_add(t->infos, (const void *)info);
}

void tokenizer_run(tokenizer *t, char *str) {
	char *str2 = strdup((const char *)str);
	char match;
	ll_free(t->tokens); // Clear the existing linked list.
	t->tokens = ll_init();

	while (strcmp("", str2) == 0) {
		match = 0;

		for(int i = 0; i < t->infos->list_len; i++) {
			// do regex matching here... later TODO
		}
	}
}

void *print_tokens(ll_node *node) {
	token_info *info = (token_info *)(node->data);
	printf("Token: %i\n", info->token);
	return NULL;
}

int main(int argc, char **argv) {
	tokenizer *tokenizer = tokenizer_init();
	tokenizer_add(tokenizer, "sin|cos|exp|ln|sqrt", 1);   //function
	tokenizer_add(tokenizer, "\\\\(", 2);                 //open bracket
	tokenizer_add(tokenizer, "\\\\)", 3);                 //close bracket
	tokenizer_add(tokenizer, "[+-]", 4);                  //plus or minus
	tokenizer_add(tokenizer, "[*/]", 5);                  //mult or divide
	tokenizer_add(tokenizer, "\\\\^", 6);                 //raised (exponent)
	tokenizer_add(tokenizer, "[0-9]+", 7);                //mult or divide
	tokenizer_add(tokenizer, "[a-zA-Z][a-zA-Z0-9_]*", 8); //variable

	ll_iterate(tokenizer->infos, &print_tokens);

	return EXIT_SUCCESS;
}
