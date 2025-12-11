#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>


// #define TEST

#ifdef TEST
#define filename "../example.txt"
#else
#define filename "../input.txt"
#endif

#define bufsize 1024
#define digitsize 9
#define max_digits 12

void remove_newline(char *buf) {
    char *nl;
    if ((nl = strchr(buf, '\n')) != NULL) {
        *nl = '\0';
    }
}


int main(void) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Failed to open %s", filename);
        exit(1);
    }

    char buf[bufsize];
    char out[max_digits + 1];
    size_t length;
    unsigned long long total = 0;

    int i, j;
    char max;
    int max_pos, out_pos;
    unsigned long long val;

    while (fgets(buf, bufsize, fp)) {
        remove_newline(buf);
        printf("%s\n", buf);

        for (i = 0; i < max_digits + 1; i++) {
            out[i] = 0;
        }

        // I used copilot to guide me to this sliding window solution but all of
        // the code is hand-rolled.
        length = strnlen(buf, bufsize);
        out_pos = 0;
        for (i = 0; i < length && out_pos < max_digits;) {
            max = 0;
            for (j = i; j <= length - (max_digits - out_pos); j++) {
                if (buf[j] > max) {
                    max = buf[j];
                    max_pos = j;
                }
            }
            out[out_pos++] = max;
            i = max_pos + 1;
        }
        val = strtoull(out, NULL, 10);
        total += val;
    }
    //  Answer for example: 3121910778619
    printf("Total: %llu\n", total);

    fclose(fp);

    return 0;
}