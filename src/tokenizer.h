#include "linkedlist.h"

#ifndef __TOKENIZER_H_
#define __TOKENIZER_H_

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
