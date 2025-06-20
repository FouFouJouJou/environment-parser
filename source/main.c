#include <stdio.h>
#include <stdlib.h>
#include <env.h>
#include <api.h>

int main(int argc, char **argv) {
  if(argc != 2) {
    exit(1);
  }
  char *file_path=*(argv+1);
  struct environment_t *env=create_env();
  parse_env(file_path, env);

  for(size_t i=0; i<env->size; ++i)
    printf("%s=%s\n", env->entries[i]->key, env->entries[i]->value ? env->entries[i]->value : "empty");

  return EXIT_SUCCESS;
}
