#include <filesystem>
#include <iostream>
#include <string_view>
#include <system_error>

namespace fs = std::filesystem;

void walk_directory(const fs::path &target_path) {
  std::error_code ec;

  // Initialize the recursive directory iterator.
  // std::filesystem::directory_options::skip_permission_denied prevents
  // permission errors from crashing the traversal loop.
  auto it = fs::recursive_directory_iterator(
      target_path, fs::directory_options::skip_permission_denied, ec);

  if (ec) {
    std::cerr << "Error opening directory " << target_path << ": "
              << ec.message() << '\n';
    return;
  }

  // End iterator representing the boundary of traversal
  const auto end_it = fs::recursive_directory_iterator();

  while (it != end_it) {
    // Query status safely using std::error_code without throwing exceptions
    const fs::directory_entry &entry = *it;
    const fs::file_status status = entry.status(ec);

    if (ec) {
      std::cerr << "Warning: Could not stat " << entry.path() << ": "
                << ec.message() << '\n';

      // Increment the iterator cleanly despite error on this entry
      it.increment(ec);
      continue;
    }

    // Branch based on file type
    if (fs::is_directory(status)) {
      std::cout << "[DIR ] " << entry.path().string() << '\n';
    } else if (fs::is_regular_file(status)) {
      std::cout << "[FILE] " << entry.path().string() << '\n';
    } else if (fs::is_symlink(status)) {
      std::cout << "[LINK] " << entry.path().string() << '\n';
    }

    // Advance to next filesystem item
    it.increment(ec);
  }
}

int main(int argc, char *argv[]) {
  // Determine target path based on CLI arguments
  const fs::path target_dir = (argc > 1) ? argv[1] : ".";

  std::cout << "Walking directory: " << target_dir.string() << '\n';
  walk_directory(target_dir);

  return 0;
}
