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

#endif
