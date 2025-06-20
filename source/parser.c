#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <state_machine.h>
#include <env.h>
#include <parser.h>

void add_key(struct environment_t *env, char c) {
  env->size++;
  env->entries=realloc(env->entries, env->size*sizeof(struct entry *));
  env->entries[env->size-1]=calloc(1, sizeof(struct entry_t));
  if(c == '\n') {
    env->entries[env->size-1]->key=calloc(1, sizeof(char));
    env->entries[env->size-1]->key[0]='\0';
  }
  else {
    env->entries[env->size-1]->key=calloc(2, sizeof(char));
    env->entries[env->size-1]->key[0]=c;
    env->entries[env->size-1]->key[1]='\0';
  }
}

void process_key(struct environment_t *env, char c) {
  char *key=env->entries[env->size-1]->key;
  size_t new_length = strlen(key)+1;
  key=realloc(key, new_length*sizeof(char));
  key[new_length-1]=c;
  key[new_length]='\0';
}
void add_empty_value(struct environment_t *env, char c) {
  env->entries[env->size-1]->value=0;
}
void add_value(struct environment_t *env, char c) {
  env->entries[env->size-1]->value=calloc(2, sizeof(char));
  env->entries[env->size-1]->value[0]=c;
  env->entries[env->size-1]->value[1]='\0';
}
void process_value(struct environment_t *env, char c) {
  char *value=env->entries[env->size-1]->value;
  size_t new_length = strlen(value)+1;
  value=realloc(value, new_length*sizeof(char));
  value[new_length-1]=c;
  value[new_length]='\0';
}
void process_equals(struct environment_t *env, char c) {
}
void process_error(struct environment_t *env, char c) {}
void process_exit(struct environment_t *env, char c) {}

struct state_machine_t *create_state_machine() {
  struct transition_t transitions[NUM_STATE][NUM_INPUTS] = {
    {
      {.next_state=STATE_KEY,   .action=add_key}
      ,{.next_state=STATE_ERROR, .action=process_error}
      ,{.next_state=STATE_ERROR, .action=process_error}
      ,{.next_state=STATE_NONE,  .action=0}
      ,{.next_state=STATE_DONE,  .action=process_exit}
    }
    ,{
      {.next_state=STATE_KEY,    .action=process_key}
      ,{.next_state=STATE_KEY,    .action=process_key}
      ,{.next_state=STATE_EQUALS, .action=process_equals}
      ,{.next_state=STATE_VALUE,  .action=add_value}
      ,{.next_state=STATE_DONE,   .action=process_exit}
    }
    ,{
      {.next_state=STATE_VALUE, .action=process_value}
      ,{.next_state=STATE_VALUE, .action=process_value}
      ,{.next_state=STATE_VALUE, .action=process_value}
      ,{.next_state=STATE_KEY,   .action=add_key}
      ,{.next_state=STATE_DONE,  .action=process_exit}
    }
    ,{
      {.next_state=STATE_VALUE, .action=add_value}
      ,{.next_state=STATE_VALUE, .action=add_value}
      ,{.next_state=STATE_VALUE, .action=add_value}
      ,{.next_state=STATE_EMPTY_VALUE, .action=add_empty_value}
      ,{.next_state=STATE_ERROR, .action=process_error}
    }
    ,
    {
      {.next_state=STATE_KEY, .action=add_key}
      ,{.next_state=STATE_ERROR, .action=process_error}
      ,{.next_state=STATE_ERROR, .action=process_error}
      ,{.next_state=STATE_ERROR, .action=process_error}
      ,{.next_state=STATE_DONE, .action=process_exit}
    }
  };
  struct state_machine_t *state_machine=calloc(1, sizeof(struct state_machine_t));
  state_machine->current_state=STATE_NONE;
  memcpy(state_machine->transitions, transitions, (NUM_STATE*NUM_INPUTS)*sizeof(struct transition_t));
  return state_machine;
}

void parse(char *buffer, size_t bytes, struct environment_t *env) {
  struct state_machine_t *state_machine=create_state_machine();
  char *digits="0123456789", *quotes="'\"";
  char *buffer_char=buffer;
  while(state_machine->current_state != STATE_DONE && state_machine->current_state != STATE_ERROR) {
    enum state_input_t input=
	*buffer_char=='\n' ? INPUT_LINE_FEED
	: *buffer_char == '\0' ? INPUT_EOF
	: *buffer_char=='=' ? INPUT_EQUALS
	: strchr(digits, *buffer_char) ? INPUT_DIGIT
	: INPUT_CODE_POINT;
    if(state_machine->transitions[state_machine->current_state][input].action) {
      state_machine->transitions[state_machine->current_state][input].action(env, *buffer_char);
    }
    state_machine->current_state =state_machine->transitions[state_machine->current_state][input].next_state;
    buffer_char++;
  }
}
