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
    struct {
        int aim = 0;
        int x = 0;
        int y = 0;
    } s;
    while (!input_file.eof()) {
        std::getline(input_file, line);
        const auto &ch = line[0];
        const auto delta = std::stoi(line.substr(line.find(' ')));
        switch (ch) {
            case 'f':
                s.x += delta;
                s.y += s.aim * delta;
                break;
            case 'u':
                s.aim -= delta;
                break;
            case 'd':
                s.aim += delta;
                break;
            default:
                assert(true);
        }
    }
    printf("%d", s.x * s.y);
    return 0;
}
