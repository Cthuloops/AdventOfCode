#include <iostream>
#include <fstream>
#include <string>
#include <regex>

int part1(const std::sregex_iterator& begin, const std::sregex_iterator& end);
int part2(const std::sregex_iterator& begin, const std::sregex_iterator& end);

int main() {
    std::ifstream file("../input.txt");
    std::string line((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
    std::regex part1_pattern("mul\\((\\d{1,3}),(\\d{1,3})\\)");
    auto part1_begin = std::sregex_iterator(line.begin(), line.end(), part1_pattern);
    auto part1_end = std::sregex_iterator();

    std::regex part2_pattern("(do\\(\\)|don't\\(\\))|mul\\((\\d{1,3}),(\\d{1,3})\\)");
    auto part2_begin = std::sregex_iterator(line.begin(), line.end(), part2_pattern);
    auto part2_end = std::sregex_iterator();

    std::cout << "Total 1: " << part1(part1_begin, part1_end) << '\n'
              << "Total 2: " << part2(part2_begin, part2_end) << std::endl;
    return 0;
}


int part1(const std::sregex_iterator& begin, const std::sregex_iterator& end) {
    // std::cout << '\n';
    int total = 0;
    for (auto i = begin; i != end; i++) {
        auto match = *i;
        // std::cout << match[0] << '\n';
        total += (std::stoi(match[1]) * std::stoi(match[2]));
    }
    return total;
}

int part2(const std::sregex_iterator& begin, const std::sregex_iterator& end) {
    std::cout << '\n';
    int total = 0;
    std::string enable = "do()";
    std::string disable = "don't()";
    bool should_multiply = true;
    for (auto i = begin; i != end; i++) {
        auto match = *i;
        if (match[0] == enable && !should_multiply) {
            std::cout << "Enabled:\n";
            should_multiply = true;
        } else if (match[0] == disable && should_multiply) {
            std::cout << "Disabled:\n";
            should_multiply = false;
        } else if (should_multiply && match[0] != enable &&
                   match[0] != disable) {
            std::cout << match[0] << '\n';
            total += (std::stoi(match[match.size() - 2]) *
                      std::stoi(match[match.size() - 1]));
        }
    }
    return total;
}
