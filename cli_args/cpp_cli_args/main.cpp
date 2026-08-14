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
