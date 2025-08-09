package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	filePath := "../example.txt"

	input, err := getFileData(filePath)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	for _, s := range input {
		head, tail := getSplit(s, ":")
		gameID := getGameID(head)
		fmt.Println(gameID, tail)
	}
}

func getFileData(filePath string) ([]string, error) {
	data, err := os.ReadFile(filePath)
	if err != nil {
		return nil, err
	}

	strData := strings.TrimSpace(string(data))

	return strings.Split(strData, "\n"), nil
}

func getGameID(header string) int {
	strNum, _ := strings.CutPrefix(header, "Game ")
	num, _ := strconv.Atoi(strNum)
	return num
}

func getSplit(data string, sep string) (string, string) {
	res := strings.Split(data, sep)
	return res[0], res[1]
}

func parseTail(tail string) bool {
	r := 0
	g := 0
	b := 0
	goodGame := true
	games := strings.Split(tail, ";")
	for _, s := range games {
		results := strings.Split(s, ",")
		for _, g := range results {

		}
	}

	return goodGame
}
