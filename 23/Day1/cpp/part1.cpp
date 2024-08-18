#include <cctype>
#include <iostream>
#include <fstream>
#include <string>

using std::cout, std::endl, std::string;


int extractNumber(string* pLine) {
    int firstDigit, secondDigit;
    bool firstFound = false;
    bool secondFound = false;
    for (char character : *pLine) {
        // 48 is ascii code for 0
        if (isdigit(character) && !firstFound) {
            firstDigit = character - 48;
            firstFound = true;
        } else if (isdigit(character) && firstFound) {
            secondDigit = character - 48;
            secondFound = true;
        }
    }
    if (firstFound && !secondFound) {
        secondDigit = firstDigit;
    }
    int returnVal = ((firstDigit * 10) + secondDigit);
    return returnVal;
}


int main() {
    using std::ifstream;

    cout << "Reading file" << endl;
    ifstream File("../file.txt");

    string Line;
    int total = 0;
    while (getline(File, Line)) {
        string* pLine = &Line;
        total += extractNumber(pLine);
    }
    File.close();
    cout << total << endl;

    return 0;
}
