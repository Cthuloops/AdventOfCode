#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> first;
    std::vector<int> second;
    int total = 0;
    std::string line;
    std::ifstream in;
    std::string filename = "../input.txt";

    in.open(filename);
    if (!in) {
        std::cerr << "File failed to open" << std::endl;
        return 1;
    }
    int first_number_location;
    int second_number_location;
    int val1, val2;
    while (getline(in, line)) {
        first_number_location = line.find(" ");
        second_number_location = line.rfind(" ");
        // std::cout << "First: " << line.substr(0, first_number_location)
        //           << "; Second: " << line.substr(second_number_location) << "\n";
        val1 = std::stoi(line.substr(0, first_number_location));
        val2 = std::stoi(line.substr(second_number_location));
        first.push_back(val1);
        second.push_back(val2);
    }
    std::sort(first.begin(), first.end());
    std::sort(second.begin(), second.end());
    for (int i = 0; i < first.size(); i++) {
        total += std::abs(first[i] - second[i]);
    }
    std::cout << "Total: " << total << std::endl;

    return 0;
}
