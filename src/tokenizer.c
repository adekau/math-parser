#include <stdio.h>
#include <ctype.h>
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

// Function from stackoverflow https://stackoverflow.com/a/122721
// Assumes the string can be written to directly, no memory allocation done.
char *trim(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator
  *(end + 1) = 0;

  return str;
}

static token_info *token_info_init(char *regex, int token) {
	token_info *t = calloc(1, sizeof(*t));
	regex_t regc;
	char *freg = calloc(strlen(regex) + 3, sizeof(*freg));
	int ereg; // Function error checking variable.
	char msgbuf[100];
	
	ereg = sprintf(freg, "^(%s)", regex);

	if (!ereg) {
		fprintf(stderr, "Could not generate the regex string\n");
		return NULL;
	}

	ereg = regcomp(&regc, freg, REG_EXTENDED);

	if (ereg) {
		fprintf(stderr, "Could not compile regex %s\n", freg);
		regerror(ereg, &regc, msgbuf, sizeof(msgbuf));
		fprintf(stderr, "Regex compile failed: %s\n", msgbuf);
		return NULL;
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
	if (ll_empty(t->infos)) return;

	char msgbuf[100];
	char *str2 = trim(strdup((const char *)str));
	char match;
	ll_node *cur;
	int ereg, matched_len;
	size_t nmatch = 1;                                                        
    regmatch_t pmatch[1];

	ll_free(t->tokens); // Clear the existing linked list.
	t->tokens = ll_init();

	while (strcmp("", str2) != 0) {
		match = 0;
		
		cur = t->infos->root;
		for(int i = 0; i < t->infos->list_len; i++) {
			ereg = regexec(&((token_info *)cur->data)->regc, str2, nmatch, pmatch, 0);
			if (!ereg) {
				match = 1;

				matched_len = pmatch[0].rm_eo - pmatch[0].rm_so;
				char *matched = calloc(matched_len, sizeof(*matched));
				memcpy(matched, &str2[pmatch[0].rm_so], matched_len);

				for (int i = 0; i < matched_len; i++) str2++;
				str2 = trim(str2);

				token *tok = token_init(((token_info *)cur->data)->token, matched);
				ll_add(t->tokens, (const void *)tok);

				break;
			} else if (ereg == REG_NOMATCH) {
				//
			} else {
				regerror(ereg, &((token_info *)cur->data)->regc, msgbuf, sizeof(msgbuf));
				fprintf(stderr, "Regex match failed: %s\n", msgbuf);
				exit(EXIT_FAILURE);
			}

			if (cur->next) cur = cur->next;
		}

		if (!match) {
			fprintf(stderr, "Unexpected character encountered during tokenization. Remaining string: %s\n", str2); 
			return;
		}

	}
}

void *print_token_infos(ll_node *node) {
	token_info *info = (token_info *)(node->data);
	printf("Token: %i\n", info->token);
	return NULL;
}

void *print_tokens(ll_node *node) {
	token *tok = (token *)(node->data);
	printf("Token type: %i, Token: %s\n", tok->token, tok->sequence);
	return NULL;
}

int main(int argc, char **argv) {
	tokenizer *tokenizer = tokenizer_init();
	tokenizer_add(tokenizer, "sin|cos|exp|ln|sqrt", 1);   //function
	tokenizer_add(tokenizer, "\\(", 2);                   //open bracket
	tokenizer_add(tokenizer, "\\)", 3);                   //close bracket
	tokenizer_add(tokenizer, "[+-]", 4);                  //plus or minus
	tokenizer_add(tokenizer, "[*/]", 5);                  //mult or divide
	tokenizer_add(tokenizer, "\\^", 6);                   //raised (exponent)
	tokenizer_add(tokenizer, "[0-9]+", 7);                //number
	tokenizer_add(tokenizer, "[a-zA-Z][a-zA-Z0-9_]*", 8); //variable

	//ll_iterate(tokenizer->infos, &print_token_infos);
	char str[100];
	strcpy(str, "     sin(x) * (1 + var_12) ");
	tokenizer_run(tokenizer, str);
	ll_iterate(tokenizer->tokens, &print_tokens);

	return EXIT_SUCCESS;
}
