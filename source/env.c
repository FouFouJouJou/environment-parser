#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <parser.h>
#include <io.h>
#include <env.h>

struct env_t *create_env() {
  struct env_t *env=calloc(1, sizeof(struct env_t));
  return env;
}

void parse_env(char *file_path, struct env_t *env) {
  char *buffer=0;
  size_t bytes_read=read_from_file(file_path, &buffer);
  parse(buffer, bytes_read, env);
  free(buffer);
}

struct entry_t *create_entry(char *key, char *value) {
  struct entry_t *entry=calloc(1, sizeof(struct entry_t *));
  entry->key=key;
  entry->value=value;
  return entry;
}

char *get(struct env_t *env, char *key, char *default_value) {
  for (size_t i=0; i<env->size; ++i) {
    char *env_key = env->entries[i]->key;
    char *value = env->entries[i]->value;
    if (!strncmp(key, env_key, strlen(key)) && value != 0) {
      return value;
    }
  }
  return default_value;
}

void free_entry(struct entry_t *entry) {
  free(entry->key);
  free(entry->value);
  free(entry);
}

void free_env(struct env_t *env) {
  for (int i=0; i<env->size; ++i) {
    free(env->entries[i]);
  }
  free(env->entries);
}
