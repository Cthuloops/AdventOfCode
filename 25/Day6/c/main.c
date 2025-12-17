
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define EXAMPLE

#ifdef EXAMPLE
#define filename ("../example.txt")
#define ANSWER (4277556)
#else
#define filename ("../input.txt")
#define ANSWER (5346286649122)
#endif

typedef unsigned long long u64;

#define BUFSIZE (4096)
#define ROW_AMOUNT (3)
#define NUMBER_BASE (10)

void part1(char **buf, size_t num_rows);

static inline void remove_newline(char *str) {
    str = strchr(str, '\n');
    if (str) {
        *str = '\0';
    }
}

int main(void) {
    time_t start, end;

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Failed to open file %s\n", filename);
        exit(1);
    }

    char tmp[BUFSIZE];
    size_t rows_amount = 0;

    while (fgets(tmp, BUFSIZE, fp)) {
        rows_amount++;
    }

    rewind(fp);

    char **buf = malloc(sizeof(char *) * rows_amount);

    size_t length;
    int row = 0;
    while (fgets(tmp, BUFSIZE, fp)) {
        remove_newline(tmp);  // replace newline with NULL.
        length = strnlen(tmp, BUFSIZE) + 1;  // Add one for NULL.
        buf[row] = malloc(length);
        if (!buf[row]) {
            fprintf(stderr, "Failed to allocate %zu bytes for row %d\n", length,
                    row);
            exit(1);
        }
        strncpy(buf[row], tmp, length);
        row++;
    }

    fclose(fp);

    part1(buf, rows_amount);

    while (rows_amount--) {
        free(buf[rows_amount]);
    }
    free(buf);

    return 0;
}

static const char *find_next_op(const char *str) {
    while (*str) {
        switch (*str) {
            case '*':
            case '+':
                return str;
            case ' ':
                str++;
                break;
            case '\0':
                return NULL;
        }
    }
    return NULL;
}

static inline u64 add(const u64 num1, const u64 num2) {
    return num1 + num2;
}
static inline u64 mul(const u64 num1, const u64 num2) {
    return num1 * num2;
}

void part1(char **buf, size_t num_rows) {
    u64 total = 0;
    u64 current_value = 0;
    size_t i;
    const char *op_row = buf[num_rows - 1];
    u64 (*op)(u64, u64);

    char *ends[num_rows - 1];
    for (i = 0; i < num_rows - 1; i++) {
        ends[i] = buf[i];
    }

    while ((op_row = find_next_op(op_row)) != NULL) {
        if (*op_row == '*') {
            op = mul;
        } else {
            op = add;
        }

        current_value = strtoull(ends[0], &ends[0], 10);
        for (i = 1; i < num_rows - 1; i++) {
            current_value = op(current_value, strtoull(ends[i], &ends[i], 10));
        }
        total += current_value;
        op_row++;
    }

    printf("Total: %llu\n", total);
    #ifdef ANSWER
    printf("%s\n", total == ANSWER ? "Correct" : "Incorrect");
    #endif
}