#include <charconv> // for std::from_chars or std::stoi
#include <iostream>
#include <span>
#include <string_view>
#include <vector>

struct CliArgs {
  bool verbose = false;
  int count = 1;
  std::string_view target{};
};

void print_usage(std::string_view prog_name) {
  std::cout << "Usage: " << prog_name << " [OPTIONS] <target>\n"
            << "Options:\n"
            << "  -v, --verbose   Enable verbose output\n"
            << "  -c, --count <N> Execution passes (default: 1)\n"
            << "  -h, --help      Display help\n";
}

int main(int argc, char *argv[]) {
  std::string_view target;
  CliArgs cli;
  std::vector<std::string_view> args(argv + 1, argv + argc);
  for (size_t i = 0; i < args.size(); ++i) {
    std::string_view arg = args[i];

    if (arg == "-h" || arg == "--help") {
      print_usage(argv[0]);
      return 0;
    }
    if (arg == "-v" || arg == "--verbose") {
    }
  }
}
