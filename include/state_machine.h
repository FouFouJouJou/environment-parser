#ifndef __STATE_MACHINE_H__ 
#define __STATE_MACHINE_H__ 

#include <stdlib.h>
#include <token.h>
#include <env.h>

enum state_t {
  STATE_NONE=0
  , STATE_KEY=1
  , STATE_VALUE=2
  , STATE_EQUALS=3
  , NUM_STATE
  , STATE_DONE
  , STATE_ERROR
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
