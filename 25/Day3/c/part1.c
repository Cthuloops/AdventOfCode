#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define TEST

#ifdef TEST
#define filename "../example.txt"
#else
#define filename "../input.txt"
#endif

#define bufsize 1024
#define digitsize 9


int main(void) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Failed to open %s", filename);
        exit(1);
    }

    char buf[bufsize] = { 0 };
    size_t length;
    int total = 0;

    int num1, position;
    int num2;
    int i;

    while (fgets(buf, bufsize, fp)) {
        // printf("%s", buf);
        // if (feof(fp)) {
        //     printf("\n");
        // }

        length = strnlen(buf, bufsize);
        num1 = INT_MIN;
        position = INT_MIN;
        num2 = INT_MIN;
        for (i = 0; i < length; i++) {
            if (buf[i] - '0' > num1) {
                num1 = buf[i] - '0';
                position = i;
            }
        }
        // printf("Num1: %d, Pos: %d; ", num1, position);
        // If the biggest number is at the end of the string, find the biggest
        // number before it.
        if (position == length - 2) {
            for (i = 0; i < position; i++) {
                if (buf[i] - '0' > num2) {
                    num2 = buf[i] - '0';
                }
            }
            // printf("Num2-e: %d\n", num2);
            total += (num2 * 10) + num1;
        } else {
            for (i = position + 1; i < length; i++) {
                if (buf[i] - '0' > num2) {
                    num2 = buf[i] - '0';
                }
            }
            // printf("Num2: %d\n", num2);
            total += (num1 * 10) + num2;
        }
    }
    printf("Total: %d\n", total);

    fclose(fp);

    return 0;
}