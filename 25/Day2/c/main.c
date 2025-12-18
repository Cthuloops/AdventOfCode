#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// #define EXAMPLE
#ifdef EXAMPLE
#define filename ("../example.txt")
#define answer (1227775554)
#else
#define filename ("../input.txt")
#endif

#define DECIMAL_BASE (10)

void remove_newline(char *buf);
size_t lltostr(uint64_t num, char *buf, size_t buf_size);
uint64_t part1(uint64_t num1, uint64_t num2);

int main(void) {

    char buf[BUFSIZ] = { 0 };
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Unable to open: %s\n", filename);
        exit(1);
    }

    char *token;
    uint64_t num1, num2;
    uint64_t total = 0;
    char *end;
    while (fgets(buf, BUFSIZ, fp)) {
        remove_newline(buf);

        token = strtok(buf, ",");
        while (token) {
            num1 = strtoull(token, &end, DECIMAL_BASE);
            num2 = strtoull(end + 1, NULL, DECIMAL_BASE);
            total += part1(num1, num2);
            token = strtok(NULL, ",");
        }

        printf("Total: %llu\n", total);
        #ifdef answer
            printf("%s\n",  total == answer ? "Correct" : "Incorrect");
        #endif
    }

    fclose(fp);

    return 0;
}

void remove_newline(char *buf) {
    char *str = buf;
    str = strchr(str, '\n');
    if (!str) {
        return;
    }
    *str = '\0';
}

size_t lltostr(uint64_t number, char *buf, size_t buf_size) {
    size_t index = 0;

    uint64_t digits = number;
    while (digits > 0) {
        index++;
        digits /= 10;
    }
    if (index > buf_size) {
        fprintf(stderr, "Index %zu > buffer size %zu", index, buf_size);
        exit(1);
    }
    size_t length = index;

    buf[index] = '\0';
    while (number > 0 && index > 0) {
        buf[--index] = '0' + (number % 10);
        number /= 10;
    }
    return length;
}

uint64_t part1(uint64_t num1, uint64_t num2) {
    // printf("Num1: %llu; Num2: %llu\n", num1, num2);
    char num_str[BUFSIZ] = { 0 };
    size_t length;
    uint64_t total = 0;
    for (uint64_t i = num1; i <= num2; i++) {
        length = lltostr(i, num_str, BUFSIZ);
        // Odd length means no symmetry
        if (length & 1) {
            continue;
        }
        if (!memcmp(num_str, &num_str[(length / 2)], length / 2)) {
            total += i;
        }
    }
    return total;
}