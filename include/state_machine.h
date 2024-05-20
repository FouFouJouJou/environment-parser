#ifndef __STATE_MACHINE_H__ 
#define __STATE_MACHINE_H__ 
#include <stdlib.h>
#include <token.h>
#include <env.h>

enum state_t {
  STATE_NONE
  , STATE_KEY
  , STATE_VALUE
  , STATE_EQUALS
  , NUM_STATE
  , STATE_DONE
} state_t;

typedef void (*state_machine_action) (
  struct environment_t *env
  ,struct token_t *token
);

struct transition_t {
  enum state_t next_state;
  state_machine_action action;
} transition_t;


struct state_machine_t {
  enum state_t current_state;
  struct transition_t transitions[NUM_STATE][NUM_TOKEN];
};


#endif
