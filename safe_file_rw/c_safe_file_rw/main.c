#include <stdio.h>

int main() {
  FILE *file = fopen("./log.txt", "a");

  if (file == NULL) {
    perror("error opening file");
    return 1;
  }
  // do the stuff -- since that previous returns early the other stuff doesn't
  // need to go into a return block.
  int result = fputs("Log entry created\n", file);
  if (result == EOF) {
    perror("error writing to stream");
    return 1;
  }
  if (fclose(file) == EOF) {
    perror("Error writing to disk and closing file handle");
    return 1;
  }
  // by the way if you want to flush RAM buffer without closing the handle
  // you can use fflush()

  return 0;
}
