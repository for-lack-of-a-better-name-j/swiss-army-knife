#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void print_usage(FILE *stream, const char *prog_name) {
  fprintf(stream,
          "Usage: %s [OPTIONS] <target> \n\n"
          "Arguments:\n"
          "  <target>        Path to target file or directory\n\n"
          "Options:\n"
          "  -v, --verbose   Enable verbose diagnostic output\n"
          "  -c, --count <N> Number of execution passes (default: 1)\n"
          "  -h, --help      Display this help menu and exit\n",
          prog_name);
}

int main(int argc, char *argv[]) {
  static struct option long_options[] = {{"verbose", no_argument, 0, 'v'},
                                         {"count", required_argument, 0, 'c'},
                                         {"help", no_argument, 0, 'h'},
                                         {0, 0, 0, 0}};
  int opt;
  int count = 1;

  bool verbose = false;
  bool help = false;

  while ((opt = getopt_long(argc, argv, "vc:h", long_options, NULL)) != -1) {
    switch (opt) {
    case 'v':
      verbose = true;
      break;
    case 'c':
      count = atoi(optarg);
      if (count <= 0) {
        fprintf(stderr, "Failed processing count. Negative numbers and 0 don't "
                        "work here.\n");
        return 1;
      }
      break;
    case 'h':
      help = true;
      break;
    default:
      fprintf(stderr, "Couldn't process args.\n");
      return 1;
    }
  }

  if (help) {
    print_usage(stdout, argv[0]);
    return 0;
  }
  // optind will now be the first positional/non-option argument: i.e. target

  if (optind >= argc) {
    fprintf(stderr, "Error: missing required positional argument <target>\n");
    return 1;
  }
  const char *target = argv[optind];

  fprintf(stdout, "Target: %s\n", target);
  if (verbose) {
    int i;
    for (i = 0; i < count; i++) {
      fprintf(stdout, "Pass #: %d\n", i);
    }
  }
  return 0;
}
