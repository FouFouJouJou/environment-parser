#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <token.h>
#include <lexer.h>

struct token_t *create_token(char *start, char *end, enum token_type_t type) {
  struct token_t *token=calloc(1, sizeof(struct token_t));
  size_t length=end-start;
  if(type == TOKEN_EOF) {
    goto out;
  }
  switch(length) {
    case 0:
      token->literal=0;
      if(*start=='\'' || *start == '"')
        token->length=3;
      else token->length=1;
      break;
    default:
      token->literal=calloc(length, sizeof(char));
      token->literal=strncpy(token->literal, start, length);
      token->literal[length]='\0';
      if(*token->literal == '"' || *token->literal == '\'' || *(start-1) == '=')
      	token->length=length+1;
      else token->length=length;
      break;
  }
  out:
    token->type=type;
  return token;
}

char *token_type_to_string(enum token_type_t type) {
  switch(type) {
    case TOKEN_STRING:
      return "TOKEN_STRING";
    case TOKEN_EMPTY_STRING:
      return "TOKEN_EMPTY_STRING";
    case TOKEN_EQUALS:
      return "TOKEN_EQUALS";
    case TOKEN_EOF:
      return "TOKEN_EOF";
  }
}

void printf_token(struct token_t token) {
  printf("(%s, %s)\n", token.literal, token_type_to_string(token.type));
}
