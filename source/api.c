#include <stdlib.h>
#include <io.h>
#include <env.h>
#include <parser.h>
#include <api.h>

void parse_env(char *file_path, struct environment_t *env) {
  char *buffer=0;
  size_t bytes_read=read_from_file(file_path, &buffer);
  parse(buffer, bytes_read, env);
  free(buffer);
}
