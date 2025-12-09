package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

type Position struct {
	X, Y int
}

func main() {
	file, err := os.Open("input.txt")
	if err != nil {
		log.Fatalf("failed to open file: %v", err)
	}
	defer func() { _ = file.Close() }()

	scanner := bufio.NewScanner(file)
	ps := make([]Position, 0)

	for scanner.Scan() {
		line := scanner.Text()
		parts := strings.Split(line, ",")

		x, _ := strconv.Atoi(parts[0])
		y, _ := strconv.Atoi(parts[1])

		ps = append(ps, Position{x, y})
	}

	res := solve(ps)
	fmt.Println(res)
}

func solve(ps []Position) int {
	n := len(ps)
	res := 0

	for i := 0; i < n; i++ {
		for j := i + 1; j < n; j++ {
			p, q := ps[i], ps[j]

			width := abs(p.X-q.X) + 1
			height := abs(p.Y-q.Y) + 1
			area := width * height

			res = max(res, area)
		}
	}

	return res
}

func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}
