#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Invalid input\n";
    return -1;
  }
  const auto input_filename = std::string(argv[1]);
  std::ifstream input_file(input_filename, std::ios::in);
  if (input_file.bad()) {
    std::cout << "Failed to open file\n";
    return -1;
  }

  // Read all lines into memory
  std::vector<std::string> lines;
  while (!input_file.eof()) {
    auto &line = lines.emplace_back();
    std::getline(input_file, line);
  }
  dsdsds
}
