#include <array>
#include <fstream>
#include <iostream>
#include <string>
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

  // Parse all the input numbers
  std::vector<int> input_numbers;
  input_numbers.reserve(lines[0].size());
  int c = 0;
  for (char ch : lines[0]) {
    if (ch == ',') {
      input_numbers.push_back(c);
      c = 0;
    } else {
      c = c * 10 + static_cast<int>(ch - '0');
    }
  }
  input_numbers.push_back(c);

  // Parse all the input bingo tables
  struct BingoTable {
    inline int &at(const int x, const int y) { return data_.at(y * 5 + x); }
    std::array<int, 5> row_count{5, 5, 5, 5, 5};
    std::array<int, 5> col_count{5, 5, 5, 5, 5};
    int total_sum{};

  private:
    std::array<int, 5 * 5> data_;
  };
  std::vector<BingoTable> tables;
  int row = 2;
  while (row < lines.size() - 1) {
    if (lines[row].empty()) {
      row++;
      continue;
    }
    auto &current_table = tables.emplace_back();
    for (int y = 0; y < 5; y++) {
      const auto &line = lines[row];
      auto insert_into_table_row = [&current_table](const int y,
                                                    const std::string &line) {
        int *table_row = &current_table.at(0, y);

        int c = 0;
        int j = 0;
        int col_idx = 0;
        while (j < line.size()) {
          if (line[j] == ' ') {
            table_row[col_idx] = c;
            current_table.total_sum += c;
            col_idx++;
            c = 0;
            while (line[j] == ' ' && j < line.size())
              j++;
          } else {
            c = c * 10 + static_cast<int>(line[j] - '0');
            j++;
          }
        }
        current_table.total_sum += c;
        table_row[col_idx] = c;
      };
      insert_into_table_row(y, line);

      row++;
    }
  }
  printf("Done parsing\n");
  // At this point we have parsed all our input data
  for (const auto input_number : input_numbers) {
    for (auto &table : tables) {
      auto bingo = [](const int current_number, BingoTable &table) -> bool {
        for (int y = 0; y < 5; y++) {
          for (int x = 0; x < 5; x++) {
            if (current_number == table.at(x, y)) {
              table.row_count[x] -= 1;
              table.col_count[y] -= 1;
              table.total_sum -= current_number;
              table.at(x, y) = -1;
              if (table.row_count[x] == 0 || table.col_count[y] == 0) {
                // Bingo
                return true;
              }
            }
          }
        }
        return false;
      };
      if (bingo(input_number, table)) {

        printf("Winning number  is  %d\n", table.total_sum * input_number);
        exit(0);
      }
    }
  }
  exit(-1);
}
