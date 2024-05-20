#include <token.h>
#include <state_machine.h>

void process_value(struct environment_t *env, struct token_t *token) {
  printf("value\n"); 
}
void process_key(struct environment_t *env, struct token_t *token) {
  printf("key\n"); 
}

struct state_machine_t create_state_machine() {
  struct transition_t transitions[NUM_STATE][NUM_TOKEN] = {
    {
      {STATE_KEY, process_key}
      ,{STATE_DONE, 0}
      ,{STATE_DONE, 0}
      ,{STATE_DONE, 0}
      ,{STATE_DONE, 0}
    }
    ,
    {
      {STATE_DONE, 0}
      ,{STATE_DONE, 0}
      ,{STATE_DONE, 0}
      ,{STATE_EQUALS, process_equals}
      ,{STATE_DONE, 0}
    }
    ,
    {
      {STATE_VALUE, process_value}
      ,{STATE_VALUE, process_value}
      ,{STATE_VALUE, process_value}
      ,{STATE_DONE, 0}
      ,{STATE_DONE, 0}
    }
    ,
    {
      {STATE_DONE, 0}
      ,{STATE_DONE, 0}
      ,{STATE_DONE, 0}
      ,{STATE_DONE, 0}
      ,{STATE_DONE, 0}
    }
  };
  struct state_machine_t *state_machine=calloc(1, sizeof(struct state_machine_t ));
  return state_machine;
}
