#ifndef __TOKEN_H__
#define __TOKEN_H__

enum token_type_t {
  TOKEN_NONE
  ,TOKEN_EQUALS
  ,TOKEN_D_QUOTES
  ,TOKEN_S_QUOTES
  ,TOKEN_STRING
  ,TOKEN_EMPTY_STRING
  ,TOKEN_EMPTY_Q_STRING
};

struct token_t {
  char *literal;
  enum token_type_t type;
  size_t length;
};

struct token_t *create_token(char *start, char *end, enum token_type_t type);

#endif
