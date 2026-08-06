#include <dirent.h>   // POSIX directory stream API
#include <stdio.h>    // For printf, fprintf, perror
#include <stdlib.h>   // For standard utility functions
#include <string.h>   // For strcmp
#include <sys/stat.h> // POSIX file metadata API

// The recursive worker function
void walk_directory(const char *dir_path) {
  // 1. Open directory stream (Syscall)
  DIR *dir = opendir(dir_path);
  if (dir == NULL) {
    perror("Failed to open directory"); // Prints the exact OS error reason
    return;
  }

  struct dirent *entry;

  // 2. Read entries one by one until readdir returns NULL (end of stream)
  while ((entry = readdir(dir)) != NULL) {
    // 3. Skip "." (current dir) and ".." (parent dir) to prevent infinite
    // loops!
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    // 4. Construct the full path string manually on the stack
    // Allocate exactly 1024 bytes, no dynamic heap allocation needed here.
    char path_buf[1024];

    // snprintf safely concatenates strings without overflowing the buffer
    // bounds
    int len =
        snprintf(path_buf, sizeof(path_buf), "%s/%s", dir_path, entry->d_name);

    // If the path was longer than 1024 bytes, bail out for this file
    if (len >= sizeof(path_buf)) {
      fprintf(stderr, "Warning: Path too long, skipped -> %s\n", entry->d_name);
      continue;
    }

    // 5. Query the OS for file metadata to check if it's a directory
    struct stat statbuf;
    if (stat(path_buf, &statbuf) == -1) {
      perror("Failed to get file stats");
      continue;
    }

    // 6. Branch based on file type
    if (S_ISDIR(statbuf.st_mode)) {
      printf("[DIR ] %s\n", path_buf);
      walk_directory(path_buf); // Recurse into subfolder
    } else {
      printf("[FILE] %s\n", path_buf);
    }
  }
  closedir(dir);
}

int main(int argc, char *argv[]) {
  // Read the first CLI argument, or default to "." (current directory)
  const char *target_dir = (argc > 1) ? argv[1] : ".";

  printf("Walking directory: %s\n", target_dir);
  walk_directory(target_dir);
  return 0;
}
