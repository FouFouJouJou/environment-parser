#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <token.h>
#include <lexer.h>

struct token_t *lex_equals(char *start) {
  if(*start == '=') return create_token(start, start+1, TOKEN_EQUALS);
  return 0;
}

struct token_t *lex_empty_string(char *start) {
  struct token_t *token=0;
  enum token_type_t type=TOKEN_NONE;
  char *string_before_char="\"'";
  if(*start == '\n') {
    if(strchr(string_before_char, *(start-1))) goto out;
    else type=TOKEN_EMPTY_STRING;
  }
  else if(strchr(string_before_char, *start) && *start == *(start+1))
    type=TOKEN_EMPTY_Q_STRING;
  if(type != TOKEN_NONE)
    token=create_token(start, start, type);
  out:
    return token;
}

struct token_t *lex_string(char *start) {
  struct token_t *token=0;
  char *end=start, *delims="\n=";
  if(*start == '\n' && *(start-1) != '=')
    goto out;
  end+=strcspn(start, delims);
  token=create_token(start, end, TOKEN_STRING);
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
    else if((token=lex_empty_string(start)));
    else if((token=lex_string(start)));
    if(!token) exit(1);
    tokens=realloc(tokens, (++total)*sizeof(struct token_t *));
    tokens[total-1]=token;
    printf_token(*token);
    start+=token->length;
  }
  return tokens;
}
