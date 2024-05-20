#ifndef __PARSER_H__
#define __PARSER_H__
#include <stdlib.h>
#include <env.h>
#include <state_machine.h>

struct state_machine_t *create_state_machine();
void parse(char *file_path, struct environment_t *env);

#endif
