#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int asciiConversion(int asciiNumber) {
    int convertedNum;

    switch (numToConvert) {
        case 48:
            convertedNum = 0;
            break;
        case 49:
            convertedNum = 1;
            break;
        case 50:
            convertedNum = 2;
            break;
        case 51:
            convertedNum = 3;
            break;
        case 52:
            convertedNum = 4;
            break;
        case 53:
            convertedNum = 5;
            break;
        case 54:
            convertedNum = 6;
            break;
        case 55:
            convertedNum = 7;
            break;
        case 56:
            convertedNum = 8;
            break;
        case 57:
            convertedNum = 9;
            break;
    }

    return convertedNum;
}

int twoDigitConversion(char nextLine[]) {
    const int LENGTH = strlen(nextLine);
    int digit1 = 0, digit2 = 0, twoDigit = 0;
    bool digit1found = false, digit2found = false;

    for (int i = 0; i < LENGTH; i++) {
        if (nextLine[i] >= 48 && nextLine[i] <= 57) {
            if (!digit1found) {
                digit1 = asciiConversion(nextLine[i]);
                digit1found = true;
            } else if (nextLine[i] >= 48 && nextLine[i] <= 57 && digit1found) {
                digit2 = asciiConversion(nextLine[i]);
                digit2found = true;
            }
        }
    }
    if (digit1found && !digit2found) {
        digit2 = digit1;
    }
    twoDigit = (digit1 * 10) + digit2;
    return twoDigit;
}


int main() {
    
    int total = 0;
    char nextLine[61];

    //open file pointer to text file containing information
    FILE *fptr;    
    fptr = fopen("../file.txt", "r");

    if (fptr != NULL) {
        while(fgets(nextLine, 61, fptr)) {
            total += twoDigitConversion(nextLine);
        }
    } else {
        printf("Not able to open file.");
    }

    fclose(fptr);

    printf("Total: %d\n", total);
    return 0;
}
