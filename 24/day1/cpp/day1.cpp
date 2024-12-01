#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void part1(std::vector<int> left_sorted, std::vector<int> right_sorted);
void part2(std::vector<int> left_sorted, std::vector<int> right_sorted);

int main() {
    std::vector<int> left;
    std::vector<int> right;
    // The input list contains 1000 lines, so reserving the space eliminates
    // vector reallocation.
    left.reserve(1000);
    right.reserve(1000);

    std::ifstream input;
    std::string line;

    // Declaring variables to store both numbers and locations
    int first_number_end_location;
    int first_number;
    int second_number_begin_location;
    int second_number;

    input.open("../input.txt");
    // Check to make sure the file opened.
    if (!input) {
        std::cerr << "File failed to open" << std::endl;
    }

    // Read the input file and parse the numbers.
    while (getline(input, line)) {
        // The first number ends at the first space and the second number begins
        // after the last space.
        first_number_end_location = line.find(" ");
        second_number_begin_location = line.rfind(" ");

        // Get the substring of line containing each number and convert into an
        // integer.
        first_number = std::stoi(line.substr(0, first_number_end_location));
        second_number = std::stoi(line.substr(second_number_begin_location));

        // Add those values to their respective vectors.
        left.push_back(first_number);
        right.push_back(second_number);
    }

    // Sort both lists in ascending order.
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    // Do the calculation for part1.
    part1(left, right);
    // Do the calculation for part2.
    part2(left, right);
    return 0;
}

void part1(std::vector<int> left_sorted, std::vector<int> right_sorted) {
    int total = 0;
    for (int i = 0; i < left_sorted.size(); i++) {
        total += std::abs(left_sorted[i] - right_sorted[i]);
    }
    std::cout << "Part 1 total: " << total << "\n";
}

void part2(std::vector<int> left_sorted, std::vector<int> right_sorted) {
    int total = 0;
    // We need to get the unique values of the left vector
    left_sorted.erase(std::unique(left_sorted.begin(), left_sorted.end()));
    // We need to loop through the unique values in the left vector, count how
    // many times that value appears in the right vector, then multiply
    // and add that to the total
    int duplicates;
    for (const auto& left_number : left_sorted) {
        duplicates = 0;
        for (const auto& right_number : right_sorted) {
            if (left_number == right_number) {
                duplicates++;
            }
        }
        total += left_number * duplicates;
    }
    std::cout << "Part 2 total: " << total << std::endl;
}
