def rgb(tail):
    red = 0
    green = 0
    blue = 0
    tail = tail.split(";")
    for group in tail:
        group = group.split(",")
        for each in group:
            each = each.strip().split(" ")
            if "red" in each and int(each[0]) > red:
                red = int(each[0])
            elif "green" in each and int(each[0]) > green:
                green = int(each[0])
            elif "blue" in each and int(each[0]) > blue:
                blue = int(each[0])
    return (red, green, blue)


def head(header):
    head = header.split()
    return int(head[1])


def main():
    total = 0
    power_total = 0
    with open("../input.txt", "r") as input:
        for line in input:
            line = line.strip()
            header, tail = line.split(":")
            red, green, blue = rgb(tail)
            if red <= 12 and green <= 13 and blue <= 14:
                total += head(header)
            power_total += red * green * blue
    print(total)
    print(power_total)


if __name__ == "__main__":
    main()

