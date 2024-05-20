#ifndef __TOKEN_H__
#define __TOKEN_H__

enum token_type_t {
  TOKEN_STRING=0
  ,TOKEN_EQUALS=1
  ,TOKEN_EOF=2
  ,NUM_TOKEN
  ,TOKEN_EMPTY_STRING
  ,TOKEN_NONE
};

struct token_t {
  char *literal;
  enum token_type_t type;
  size_t length;
};

struct token_t *create_token(char *start, char *end, enum token_type_t type);

void printf_token(struct token_t token);

#endif
