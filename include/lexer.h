#ifndef __LEXER_H__
#define __LEXER_H__
#define whitespaces "\n\t\r "

struct token_t **lex(char *buffer, size_t size);
#endif
