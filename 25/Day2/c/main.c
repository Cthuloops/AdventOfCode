#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define INPUT
#ifdef INPUT
#define filename "../input.txt"
#else
#define filename "../example.txt"
#endif

void remove_newline(char *);
void lltostr(long long, char *, size_t);

int main(void) {

    char buf[BUFSIZ] = { 0 };
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Unable to open: %s\n", filename);
        exit(1);
    }

    fgets(buf, BUFSIZ, fp);
    remove_newline(buf);

    char *token = strtok(buf, ",");
    long long num1, num2;
    char num_str[BUFSIZ] = { 0 };
    while (token) {
        errno = 0;
        num1 = strtoll(token, NULL, 10);
        printf("Strtoll: %lld\n", num1);
        lltostr(num1, num_str, BUFSIZ);
        printf("Lltostr: %s\n\n", num_str);
        token = strtok(NULL, ",");
    }


    fclose(fp);

    return 0;
}

void remove_newline(char *buf) {
    char *str = buf;
    str = strchr(str, '\n');
    *str = '\0';
}

void lltostr(long long number, char *buf, size_t buf_size) {
    size_t index = 0;

    long long digits = number;
    while (digits > 0) {
        index++;
        digits /= 10;
    }

    buf[index] = 0;
    while (number > 0 && index < buf_size) {
        buf[--index] = '0' + (number % 10);
        number /= 10;
    }
}
