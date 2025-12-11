#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define EXAMPLE

#ifdef EXAMPLE
#define filename "../example.txt"
#define rows 10
#define cols 10
#define length 12
#else
#define filename "../input.txt"
#define rows 136
#define cols 136
#define length 138
#endif

#define OPEN 4

int check_neighbors(char buf[rows][length], int row, int col);
int part1(char buf[rows][length]);
// int part2(void);

void remove_newline(char buf[length]) {
    char *str = buf;
    if ((str = strchr(str, '\n')) != NULL) {
        *str = '\0';
    }
}

int main(void) {
    char buf[rows][length];

    FILE *fp = fopen(filename, "r");

    int i = 0;
    while (fgets(buf[i], length, fp)) {
        remove_newline(buf[i++]);
    }

    fclose(fp);

    int total = part1(buf);
    printf("%d\n", total);

    return 0;
}

int check_neighbors(char buf[rows][length], int row, int col) {
    int rolls = 0;
    int y, x;
    for (y = row - 1; y <= row + 1; y++) {
        for (x = col - 1; x <= col + 1; x++) {
            // Skip the cell being observed.
            if (y == row && x == col) {
                continue;
            }

            // If we're at a boundary of the grid, it's free.
            if (y < 0 || x < 0 || y >= rows || x >= cols) {
                continue;
            } else if (buf[y][x] == '@') {
                rolls++;
            }
        }
    }
    return rolls;
}

int part1(char buf[rows][length]) {
    int total = 0;

    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (buf[i][j] == '@') {
                if (check_neighbors(buf, i, j) < OPEN) {
                    total++;
                }
            }
        }
    }

    // for (i = 0; i < rows; i++) {
    //     printf("%s\n", buf[i]);
    // }

    return total;
}