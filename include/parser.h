#ifndef __PARSER_H__
#define __PARSER_H__
#include <stdlib.h>
#include <env.h>
void parse(char *buffer, size_t bytes, struct environment_t *env);
#endif
