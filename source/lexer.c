#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <token.h>
#include <lexer.h>

struct token_t *lex_equals(char *start) {
  if(*start == '=') return create_token(start, start+1, TOKEN_EQUALS);
  return 0;
}

struct token_t *lex_string(char *start) {
  enum token_type_t type=TOKEN_STRING;
  struct token_t *token=0;
  char *end=start, *delims="\n=";
  if(*start == '\n' && *start == *(start+1))
    return create_token(start, end, TOKEN_EMPTY_STRING);
  end+=strcspn(start, delims);
  if(end == start)
    type=TOKEN_EMPTY_STRING;
  token=create_token(start, end, type);
  out:
    return token;
}

struct token_t **lex(char *buffer, size_t size) {
  char *start=buffer;
  struct token_t **tokens=0;
  while(start < buffer+size) {
    start+=strspn(start, "\t\r ");
    struct token_t *token=0;
    if((token=lex_equals(start)));
    //else if((token=lex_quoted_string(start)));
    else if((token=lex_string(start)));
    if(!token) exit(1);
    start+=token->length;
  }
  return tokens;
}
