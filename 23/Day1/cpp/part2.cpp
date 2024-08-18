#include <cctype>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>

using std::cout, std::endl, std::string, std::unordered_map;


void replaceWords(string* pLine) {
    unordered_map<string, char> words;
    words.emplace("zero", '0');
    words.emplace("one", '1');
    words.emplace("two", '2');
    words.emplace("three", '3');
    words.emplace("four", '4');
    words.emplace("five", '5');
    words.emplace("six", '6');
    words.emplace("seven", '7');
    words.emplace("eight", '8');
    words.emplace("nine", '9');
    for (auto wordsIter = words.begin(); wordsIter != words.end(); ++wordsIter) {
        int index = pLine->find(wordsIter->first);
        while (index != -1) {
            pLine->insert(index + 1, 1, wordsIter->second);
            index = pLine->find(wordsIter->first);
        }
    }
}

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
        replaceWords(pLine);
        int num = extractNumber(pLine);
        total += num;
    }
    File.close();
    cout << total << endl;

    return 0;
}
