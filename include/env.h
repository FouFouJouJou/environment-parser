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
void add(char *key, char *value, struct environment_t *env);
char *get(char *key, char *default_value, struct environment_t *env);
#endif
