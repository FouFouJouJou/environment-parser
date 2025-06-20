#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

#include <stdlib.h>
#include <env.h>

enum state_t {
  STATE_NONE=0
  ,STATE_KEY
  ,STATE_VALUE
  ,STATE_EQUALS
  ,STATE_EMPTY_VALUE
  ,NUM_STATE
  ,STATE_DONE
  ,STATE_ERROR
} state_t;

enum state_input_t {
  INPUT_CODE_POINT
  ,INPUT_DIGIT
  ,INPUT_EQUALS
  ,INPUT_LINE_FEED
  ,INPUT_EOF
  ,NUM_INPUTS
};

typedef void (state_machine_action) (
  struct env_t *env
  , char c
);

struct transition_t {
  enum state_t next_state;
  state_machine_action *action;
} transition_t;

struct state_machine_t {
  enum state_t current_state;
  struct transition_t transitions[NUM_STATE][NUM_INPUTS];
};

#endif
