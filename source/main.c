#include <stdio.h>
#include <stdlib.h>
#include <env.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    exit(1);
  }

  char *file_path=*(argv+1);
  struct env_t *env=parse_env(file_path);
  printf_env(*env);
  free_env(env);

  return EXIT_SUCCESS;
}
