#!/usr/bin/env python

def part1(left, right):
    total = 0
    for i in range(len(left)):
        total += abs(left[i] - right[i])
    print(f'Part 1 total: {total}')

def part2(left: list[int], right: list[int]):
    total = 0
    for left_number in set(left):
        for right_number in right:
            if left_number == right_number:
                total += left_number
    print(f'Part 2 total: {total}')

def main():
    left = []
    right = []

    with open(file='../input.txt', mode='r', encoding='utf-8') as f:
        for line in f:
            line_split = line.split()
            left.append(int(line_split[0].strip()))
            right.append(int(line_split[1].strip()))

    left.sort()
    right.sort()

    part1(left, right)
    part2(left, right)


if __name__ == '__main__':
    main()
