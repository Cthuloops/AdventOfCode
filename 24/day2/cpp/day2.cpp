#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

bool is_valid_sequence(const std::vector<int>& line) {
    if (line.size() < 2) return false;

    bool ascending = line[0] < line[1];
    for (int i = 1; i < line.size(); i++) {
        int difference = std::abs(line[i] - line[i-1]);
        if ((ascending && line[i] <= line[i-1]) ||
            (!ascending && line[i] >= line[i-1]) ||
            difference < 1 || difference > 3) {
            return false;
        }
    }
    return true;
}

bool is_valid_part2(const std::vector<int>& line) {
    // Try removing each number and check if sequence becomes valid
    for (int skip = 0; skip < line.size(); skip++) {
        std::vector<int> modified;
        for (int i = 0; i < line.size(); i++) {
            if (i != skip) modified.push_back(line[i]);
        }
        if (is_valid_sequence(modified)) return true;
    }
    // If original sequence is valid, no need to remove anything
    return is_valid_sequence(line);
}

int main() {
    std::ifstream file("../input.txt");
    if (!file) {
        std::cerr << "File didn't open" << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> lines;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream input(line);
        lines.emplace_back();
        int number;
        while (input >> number) {
            lines.back().push_back(number);
        }
    }

    int part1 = 0;
    int part2 = 0;
    for (const auto& line : lines) {
        if (is_valid_sequence(line)) {
            part1++;
        }
        if (is_valid_part2(line)) {
            part2++;
        }
    }
    std::cout << "Part 2: " << part2 << std::endl;

    return 0;
}
