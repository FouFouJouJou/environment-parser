#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <token.h>
#include <state_machine.h>
#include <parser.h>
#include <io.h>
#include <lexer.h>
#include <env.h>

void process_key(struct environment_t *env, struct token_t *token) {
  add(0,0, env);
  env->entries[env->size-1]->key=token->literal;
}
void process_value(struct environment_t *env, struct token_t *token) {
  env->entries[env->size-1]->value=token->literal;
}
void process_equals(struct environment_t *env, struct token_t *token) {}
void process_error(struct environment_t *env, struct token_t *token) {
  exit(200);
}
void process_exit(struct environment_t *env, struct token_t *token) {}

struct state_machine_t *create_state_machine() {
  struct transition_t transitions[NUM_STATE][NUM_TOKEN] = {
    { // STATE_NONE
      {.next_state=STATE_KEY, .action=process_key}
      ,{.next_state=STATE_ERROR, .action=process_error}
      ,{.next_state=STATE_DONE, .action=process_exit}
    }
    ,{ // STATE_KEY
       {.next_state=STATE_ERROR,  .action=process_error}
      ,{.next_state=STATE_EQUALS, .action=process_equals}
      ,{.next_state=STATE_ERROR,  .action=process_error}
    }
    ,
    { // STATE_VALUE
      {.next_state=STATE_KEY,    .action=process_key}
      ,{.next_state=STATE_ERROR, .action=process_error}
      ,{.next_state=STATE_DONE,  .action=process_exit}
    }
    ,{ // STATE_EQUALS
      {.next_state=STATE_VALUE,  .action=process_value}
      ,{.next_state=STATE_ERROR, .action=process_error}
      ,{.next_state=STATE_ERROR, .action=process_error}
    }
  };
  struct state_machine_t *state_machine=calloc(1, sizeof(struct state_machine_t));
  state_machine->current_state=STATE_NONE;
  memcpy(state_machine->transitions, transitions, (NUM_STATE*NUM_TOKEN)*sizeof(struct transition_t));
  return state_machine;
}

void parse(char *buffer, size_t bytes, struct environment_t *env) {
  struct token_t **tokens=lex(buffer, bytes);
  struct state_machine_t *state_machine = create_state_machine();
  while(state_machine->current_state != STATE_DONE && state_machine->current_state != STATE_ERROR) {
    state_machine->transitions[state_machine->current_state][(*tokens)->type].action(env,*tokens);
    state_machine->current_state=state_machine->transitions[state_machine->current_state][(*tokens)->type].next_state;
    tokens++;
  }
}
