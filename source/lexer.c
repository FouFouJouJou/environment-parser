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
  struct token_t *token=0;
  char *end=start, *delims="\n=", *quotes="\"'";
  end+=strcspn(start, delims);
  if(strchr(quotes, *start) && *start == *(start+1)) 
    token=create_token(start, end, TOKEN_EMPTY_Q_STRING);
  else if(*start == '\n' && *(start-1) == '=')
    token=create_token(start, end, TOKEN_EMPTY_STRING);
  else token=create_token(start, end, TOKEN_STRING);
  out:
    return token;
}

struct token_t **lex(char *buffer, size_t size) {
  char *start=buffer;
  struct token_t **tokens=0;
  size_t total=0;
  while(start < buffer+size) {
    start+=strspn(start, "\t\r ");
    struct token_t *token=0;
    if((token=lex_equals(start)));
    else if((token=lex_string(start)));
    if(!token) exit(1);
    tokens=realloc(tokens, (++total)*sizeof(struct token_t *));
    tokens[total-1]=token;
    printf_token(*token);
    start+=token->length;
  }
  return tokens;
}
