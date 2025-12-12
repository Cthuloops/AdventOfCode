#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define EXAMPLE

#ifdef EXAMPLE
#define filename "../example.txt"
#else
#define filename "../input.txt"
#endif


#define ranges_size 256
#define bufsize 256

typedef unsigned long long u64;

struct Range {
    u64 min;
    u64 max;
};


int main(void) {

    struct Range ranges[ranges_size];
    int ranges_count = 0;
    char buf[bufsize];

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Failed to open %s\n", filename);
        exit(1);
    }

    char *mid;
    u64 num1, num2;
    int i;
    bool in_range;
    int total_fresh = 0;
    while (fgets(buf, bufsize, fp)) {
        // Only half the file is used for ranges. After the \n line there's the
        // actual input for the challenge.
        if (buf[0] == '\n') {
            break;
        }

        num1 = strtoull(buf, &mid, 10);
        num2 = strtoull((mid + 1), NULL, 10);

        ranges[ranges_count++] = (struct Range) {
            .min = num1,
            .max = num2
        };
    }

    // Check to see if the numbers are within a valid range.
    while (fgets(buf, bufsize, fp)) {
        in_range = false;
        num1 = strtoull(buf, NULL, 10);
        for (i = 0; i < ranges_count; i++) {
            if (num1 >= ranges[i].min && num1 <= ranges[i].max) {
                in_range = true;
                break;
            }
        }
        total_fresh += (in_range * 1);
    }

    fclose(fp);

    printf("Total: %d\n", total_fresh);

    return 0;
}