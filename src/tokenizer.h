#include "linkedlist.h"

#ifndef __TOKENIZER_C_
#define __TOKENIZER_C_

#ifdef __C_PLUS_PLUS
extern "C" {
#endif

typedef struct {
	regex_t regc;
	int token;
} token_info;

typedef struct {
	linkedlist *infos;
	linkedlist *tokens;
} tokenizer;

typedef struct {
	int token;
	char *sequence;
} token;

#ifdef __C_PLUS_PLUS
}
#endif

#endif
