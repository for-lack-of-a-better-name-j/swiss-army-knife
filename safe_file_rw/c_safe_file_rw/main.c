#include <dirent.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  FILE *file = fopen("./log.txt", "a");

  if (file == NULL) {
    perror("error opening file");
    return 1;
  }
  // do the stuff -- since that previous returns early the other stuff doesn't
  // need to go into a return block.
  char result = fputs("Log entry created\n", file);
  if (result == EOF) {
    perror("error writing to file");
    return 1;
  }
  fclose(file);
  return 0;
}
