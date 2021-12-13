#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>


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

    std::unordered_set<int> lines_to_consider_most_common;
    std::unordered_set<int> lines_to_consider_least_common;
    lines_to_consider_most_common.reserve(lines.size());
    for (int i = 0; i < lines.size(); i++) {
        lines_to_consider_most_common.insert(i);
        lines_to_consider_least_common.insert(i);
    }
    for (int bit_idx = 0; bit_idx < lines[0].size(); bit_idx++) {
        printf("Bit position %d\n", bit_idx);
        if (lines_to_consider_most_common.size() == 1 && lines_to_consider_least_common.size() == 1) break;
        if (lines_to_consider_most_common.size() > 1) {
            int pos_count = 0;
            for (const auto line_idx: lines_to_consider_most_common) {
                const auto &line = lines[line_idx];
                if (line[bit_idx] == '1') {
                    pos_count++;
                } else {
                    pos_count--;
                }
            }
            if (pos_count >= 0) {
                printf("Most common 1\n");
                for (auto it = lines_to_consider_most_common.begin(); it != lines_to_consider_most_common.end();) {
                    const auto &line = lines[*it];
                    if (line[bit_idx] == '0') {
                        printf("Deleting %s\n", lines[*it].c_str());
                        lines_to_consider_most_common.erase(it++);
                    } else {
                        ++it;
                    }
                }
            } else {
                printf("Most common 0\n");
                for (auto it = lines_to_consider_most_common.begin(); it != lines_to_consider_most_common.end();) {
                    const auto &line = lines[*it];
                    if (line[bit_idx] == '1') {
                        printf("Deleting %s\n", lines[*it].c_str());
                        lines_to_consider_most_common.erase(it++);
                    } else {
                        ++it;
                    }
                }
            }
        }

        if (lines_to_consider_least_common.size() > 1) {
            int pos_count = 0;
            for (const auto line_idx: lines_to_consider_least_common) {
                const auto &line = lines[line_idx];
                if (line[bit_idx] == '1') {
                    pos_count++;
                } else {
                    pos_count--;
                }
            }
            if (pos_count >= 0) {
                for (auto it = lines_to_consider_least_common.begin(); it != lines_to_consider_least_common.end();) {
                    const auto &line = lines[*it];
                    if (line[bit_idx] == '1') {
                        lines_to_consider_least_common.erase(it++);
                    } else {
                        ++it;
                    }
                }
            } else {
                for (auto it = lines_to_consider_least_common.begin(); it != lines_to_consider_least_common.end();) {
                    const auto &line = lines[*it];
                    if (line[bit_idx] == '0') {
                        lines_to_consider_least_common.erase(it++);
                    } else {
                        ++it;
                    }
                }
            }
        }
    }

    auto getDecimal = [](const std::string &line) {
        const auto size = line.size();
        int sum = 0;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == '1')
                sum += (1 << (size - 1 - i));
        }
        printf("Binary %s, Decimal: %d\n", line.c_str(), sum);
        return sum;
    };

    auto val = getDecimal(lines[*lines_to_consider_most_common.begin()]) *
               getDecimal(lines[*lines_to_consider_least_common.begin()]);
    printf("%d\n", val);


    return 0;
}
