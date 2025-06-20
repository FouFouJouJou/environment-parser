#ifndef __ENV_H__
#define __ENV_H__

struct entry_t {
  char *key;
  char *value;
};

struct environment_t {
  struct entry_t **entries;
  size_t size;
};

struct environment_t *create_env();
char *get(struct environment_t *env, char *key, char *default_value);
void parse_env(char *file_path, struct environment_t *env);
#endif
