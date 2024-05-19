#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <token.h>
#include <lexer.h>

struct token_t *create_token(char *start, char *end, enum token_type_t type) {
  struct token_t *token=calloc(1, sizeof(struct token_t*));
  size_t length=end-start;
  switch(length) {
    case 0:
      token->literal=0;
      if(type==TOKEN_EMPTY_Q_STRING)
        token->length=3;
      token->length=2;
      break;
    default:
      token->literal=calloc(length, sizeof(char));
      token->literal=strncpy(token->literal, start, length);
      token->literal[length]='\0';
      token->length=length+1;
      break;
  }
  token->type=type;
  printf("%s(%ld)\n", token->literal, token->length);
  return token;
}
