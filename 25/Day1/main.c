#include <stdio.h>
#include <stdlib.h>


int main(void) {
    const char *filename = "input.txt";

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Couldn't open %s.\n", filename);
        exit(EXIT_FAILURE);
    }

    // Dial starts at 50
    // Rolls over at 99 to 0 and at 0 to 99
    int dial = 50;
    
    // Each line has up to 6 chars.
    // L/R, 1-3 numbers, newline, and \0.
    char buf[6];

    // Password is the number of times the dial lands on 0.
    int password = 0;

    int clicks;
    int direction;
    while (fgets(buf, 6, fp)) {
        // printf("Dial: %d\n", dial);
        // printf("%s", buf);
        direction = buf[0] == 'L';
        buf[0] = '0';  // Overwrite with 0 so atoi can process the number.
        clicks = atoi(buf);
        clicks %= 100;

        if (direction) {
            dial -= clicks;
            if (dial < 0) {
                dial += 100;
            }
        } else {
            dial += clicks;
            if (dial > 99) {
                dial -= 100;
            }
        }

        if (dial == 0) {
            password++;
        }
    }
    printf("%d\n", password);

    if (ferror(fp)) {
        fprintf(stderr, "I/O error reading file.\n");
    }

    if (fclose(fp) == EOF) {
        fprintf(stderr, "Error closing file stream.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}