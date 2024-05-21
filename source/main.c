#include <stdio.h>
#include <stdlib.h>
#include <env.h>
#include <api.h>

int main(int argc, char **argv) {
  if(argc != 3) {
    exit(1);
  }
  char *file_path=*(argv+1);
  struct environment_t *env=create_env();
  parse_env(file_path, env);
  char *value=get(*(argv+2), "no match", env);
  printf("%s\n", value ? value : "nill");
  return EXIT_SUCCESS;
}
