#include <fstream>
#include <iostream>

int main() {
  std::ofstream file("log.txt", std::ios::app);
  // file is the variable name, so you could also
  // std::ofstream some_other_file("some_other_file.txt", std::ios::app);

  if (!file.is_open()) { // or simply `if (!file)`
    std::cerr << "Error opening log.txt\n";
    return 1;
  }
  char c[] = "Log entry added.\n";
  if (!file.write(c, 18).write("!\n", 2).good()) {
    std::cerr << "Error writing to log.txt buffer\n";
    return 1;
  }
  if (!file.flush().good()) {
    std::cerr << "Error writing to disk log.txt\n";
    return 1;
  }
  return 0;
}
