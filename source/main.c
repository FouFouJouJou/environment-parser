#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <lexer.h>

int main(int argc, char **argv) {
  if(argc != 2) {
    exit(1);
  }

  char *file_path=*(argv+1), *buffer=0;
  size_t bytes_read=read_from_file(file_path, &buffer);
  lex(buffer, bytes_read);
  free(buffer);

  return EXIT_SUCCESS;
}
