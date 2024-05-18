#include <stdlib.h>
#include <env.h>

struct environment_t *create_env() {
  struct environment_t *env=calloc(1, sizeof(struct environment_t));
  return env;
}

struct entry_t *create_entry(char *key, char *value) {
  struct entry_t *entry=calloc(1, sizeof(struct entry_t *));
  entry->key=key;
  entry->value=value;
  return entry;
}

void add(char *key, char *value, struct environment_t *env) {
  env->size++;
  env->entries=realloc(env->entries, sizeof(struct entry_t*)*env->size);
  env->entries[env->size-1]=create_entry(key, value);
}

void add_key(struct environment_t *env, char c) {
}

void add_value(struct environment_t *env, char c) {
}

void process_key(struct environment_t *env, char c) {
}

void process_value(struct environment_t *env, char c) {
}

void process_whitespace(struct environment_t *env, char c) {
}

void process_exit(struct environment_t *env, char c) {
  exit(2);
}

void free_entry(struct entry_t *entry) {
  free(entry->key);
  free(entry->value);
  free(entry);
}

void free_env(struct environment_t *env) {
  for(int i=0; i<env->size; ++i) 
    free(env->entries[i]);
  free(env->entries);
}
