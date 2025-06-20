#ifndef __ENV_H__
#define __ENV_H__

struct entry_t {
  char *key;
  char *value;
};

struct env_t {
  struct entry_t **entries;
  size_t size;
};

struct env_t *create_env();
ssize_t has_key(struct env_t *env, char *key);
char *get(struct env_t *env, char *key, char *default_value);
struct env_t *parse_env(char *file_path);
void printf_env(struct env_t env);
void free_env(struct env_t *env);

#endif
