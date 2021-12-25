#include <fstream>
#include <iostream>

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
  int count = 0;
  std::string line;
  std::getline(input_file, line);
  auto prev_val = std::stoi(line);

  while (!input_file.eof()) {
    std::getline(input_file, line);
    auto current_val = std::stoi(line);
    if (current_val > prev_val) {
      count++;
    }
    prev_val = current_val;
  }
  std::cout << count << "\n";
  return 0;
}
