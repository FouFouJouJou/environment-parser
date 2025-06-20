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

struct env_t *parse_env(char *file_path) {
  struct env_t *env = create_env();
  char *buffer=0;
  size_t bytes_read=read_from_file(file_path, &buffer);
  parse(buffer, bytes_read, env);
  free(buffer);
  return env;
}

struct entry_t *create_entry(char *key, char *value) {
  struct entry_t *entry=calloc(1, sizeof(struct entry_t *));
  entry->key=key;
  entry->value=value;
  return entry;
}


ssize_t has_key(struct env_t *env, char *key) {
  for (size_t i=0; i<env->size; ++i) {
    char *env_key = env->entries[i]->key;
    if (!strncmp(key, env_key, strlen(key))) {
      return i;
    }
  }
  return -1;
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

void printf_env(struct env_t env) {
  for (size_t i=0; i<env.size; ++i) {
    printf("%s=%s\n", env.entries[i]->key, get(&env, env.entries[i]->key, "empty"));
  }
}
void free_entry(struct entry_t *entry) {
  free(entry->key);
  free(entry->value);
  free(entry);
}

void free_env(struct env_t *env) {
  for (int i=0; i<env->size; ++i) {
    free_entry(env->entries[i]);
  }
  free(env->entries);
  free(env);
}
