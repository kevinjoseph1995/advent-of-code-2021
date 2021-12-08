#include <iostream>
#include <fstream>
#include <cassert>


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
    std::pair<int, int> pos = {0, 0};
    while (!input_file.eof()) {
        std::getline(input_file, line);
        const auto &ch = line[0];
        const auto delta = std::stoi(line.substr(line.find(' ')));
        switch (ch) {
            case 'f':
                pos.first += delta;
                break;
            case 'u':
                pos.second -= delta;
                break;
            case 'd':
                pos.second += delta;
                break;
            default:
                assert(true);
        }
    }
    printf("%d", pos.first * pos.second);
    return 0;
}
