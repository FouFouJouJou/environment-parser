#include <token.h>

struct token_t *create_token(char *start, char *end, enum token_type_t type) {
 struct token_t *token=calloc(1, sizeof(struct token_t*));
 return token;
}
