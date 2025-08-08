package main

import (
	"fmt"
	"log"
	"os"
	"strings"
)

func main() {
	filePath := "../file.txt"

	input, err := getFileData(filePath)
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println("Part 1:", sum(input))
	fmt.Println("Part 2:", sum(sub(input)))

}
func getFileData(filePath string) ([]string, error) {
	data, err := os.ReadFile(filePath)
	if err != nil {
		return nil, err
	}

	strData := strings.TrimSpace(string(data))

	return strings.Split(strData, "\n"), nil
}

func sum(data []string) int {
	total := 0
	for _, s := range data {
		total += extractNumber(s)
	}
	return total
}

func extractNumber(data string) int {
	nums := make([]int, 0, len(data))
	for _, c := range data {
		num := int(c - '0')
		if num >= 0 && num <= 9 {
			nums = append(nums, num)
		}
	}

	if len(nums) >= 1 {
		return (nums[0] * 10) + nums[len(nums)-1]
	}
	return -1
}

func sub(data []string) []string {
	subbed := make([]string, 0, len(data))

	subs := map[string]string{
		"one":   "o1ne",
		"two":   "t2wo",
		"three": "t3hree",
		"four":  "f4our",
		"five":  "f5ive",
		"six":   "s6ix",
		"seven": "s7even",
		"eight": "e8ight",
		"nine":  "n9ine",
		"zero":  "z0ero",
	}

	for _, s := range data {
		for w, r := range subs {
			s = strings.ReplaceAll(s, w, r)
		}
		subbed = append(subbed, s)
	}

	return subbed
}
