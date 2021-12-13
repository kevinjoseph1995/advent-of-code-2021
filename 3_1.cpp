#include <iostream>
#include <fstream>
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
    std::string line;
    std::getline(input_file, line);
    std::vector<int> counts(line.size(), 0);
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == '1') {
            counts[i]++;
        } else {
            counts[i]--;
        }
    }

    while (!input_file.eof()) {
        std::getline(input_file, line);
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == '1') {
                counts[i]++;
            } else {
                counts[i]--;
            }
        }
    }

    int gamma = 0;
    int epsilon = 0;
    for (int i = 0; i < counts.size(); i++) {
        printf("%d ", counts[i]);
        if (counts[i] > 0) {
            gamma += (1 << (counts.size() - 1 - i));

        } else {
            epsilon += (1 << (counts.size() - 1 - i));
        }
    }
    printf("\n%d\n", gamma * epsilon);
    return 0;
}
