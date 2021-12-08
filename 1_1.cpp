#include <iostream>
#include <fstream>


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

    auto start_pos = input_file.tellg();

    auto get_window_sum = [&]() -> std::pair<bool, int> {
        input_file.seekg(start_pos);
        auto sum = 0;
        std::string line;
        for (int i = 0; i < 3; i++) {
            if (input_file.eof()) {
                return std::make_pair(false, 0);
            } else {
                if (i == 1) {
                    start_pos = input_file.tellg();
                }
                std::getline(input_file, line);
                sum += std::stoi(line);
            }
        }
        return std::make_pair(true, sum);
    };

    int count = 0;

    auto[valid, prev_sum] = get_window_sum();
    while (valid) {
        auto[internal_valid, current_sum] = get_window_sum();
        if (internal_valid && current_sum > prev_sum) {
            count++;
        }
        prev_sum = current_sum;
        valid = internal_valid;
    }
    printf("%d\n", count);
    return 0;
}
