#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define EXAMPLE

#ifdef EXAMPLE
#define filename "../example.txt"
#define rows 10
#define cols 10
#else
#define filename "../input.txt"
#define rows 136
#define cols 136
#endif

#define OPEN 4

struct Cell {
    bool can_be_removed;
    char val;
};

int check_neighbors(struct Cell cells[rows][cols], int row, int col);
int part1(struct Cell cells[rows][cols]);
int part2(struct Cell cells[rows][cols]);

int main(void) {
    char buf[BUFSIZ];
    struct Cell cells[rows][cols];

    FILE *fp = fopen(filename, "r");

    int r = 0, c;
    while (fgets(buf, BUFSIZ, fp)) {
        for (c = 0; c < cols; c++) {
            cells[r][c] = (struct Cell) {
                .can_be_removed = false,
                .val = buf[c]
            };
        }
        r++;
    }

    fclose(fp);

    int total = part1(cells);
    printf("Part1: %d\n", total);
    int removed = part2(cells);
    printf("Part2: %d\n", removed);

    return 0;
}

int check_neighbors(struct Cell cells[rows][cols], int row, int col) {
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
            } else if (cells[y][x].val == '@') {
                rolls++;
            }
        }
    }
    return rolls;
}

int part1(struct Cell cells[rows][cols]) {
    int total = 0;

    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (cells[i][j].val == '@') {
                if (check_neighbors(cells, i, j) < OPEN) {
                    total++;
                    cells[i][j].can_be_removed = true;
                }
            }
        }
    }

    return total;
}

int part2(struct Cell cells[rows][cols]) {
    int can_be_removed;
    int removed = 0;

    int i, j;
    do {
        can_be_removed = part1(cells);
        for (i = 0; i < rows; i++) {
            for (j = 0; j < cols; j++) {
                if (cells[i][j].can_be_removed) {
                    cells[i][j].can_be_removed = false;
                    cells[i][j].val = 'x';
                    removed++;
                }
            }
        }
    } while (can_be_removed > 0);

    return removed;
}