#include <token.h>
#include <lexer.h>

struct token_t *lex_equals(char c) {
  if(c == '=') return create_token(&c, &c+1, TOKEN_EQUALS);
  return 0;
}

struct token_t *lex_quotes(char c) {
  struct token_t *token=0;
  enum token_type_t type=TOKEN_NONE;
  if(c == '\'') type = TOKEN_S_QUOTES;
  if(c == '"') type = TOKEN_D_QUOTES;
  if(!type) goto out;
  token=create_token(&c, &c+1, type);
  out:
    return token;
}

struct token_t **lex(char *buffer, size_t size) {
  char *start=buffer;
  struct token_t **tokens=0;
  while(start != buffer+size) {
    start+=strspn(start, whitespaces);
    struct token_t *token=0;
    if((token=lex_equals(*start));
    if((token=lex_quotes(*start));
    if((token=lex_string(start));
    if(!token) exit(1);
    start+=token->length;
  }
  return tokens;
}
