#ifndef __PARSER_H_
#define __PARSER_H_

#ifdef __C_PLUS_PLUS
extern "C" {
#endif

#define EPSILON       0
#define PLUSMINUS     1
#define MULTDIV       2
#define RAISED        3
#define FUNCTION      4
#define OPEN_BRACKET  5
#define CLOSE_BRACKET 6
#define NUMBER        7
#define VARIABLE      8

typedef struct _mp_parser {
	linkedlist *tokens;
	token lookahead;
} parser;


#ifdef __C_PLUS_PLUS
}
#endif

#endif
