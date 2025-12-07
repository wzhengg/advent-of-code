package main

import (
	"bytes"
	"fmt"
	"log"
	"os"
)

func main() {
	data, err := os.ReadFile("input.txt")
	if err != nil {
		log.Fatalf("failed to read file: %v", err)
	}

	data = bytes.TrimSpace(data)
	grid := bytes.Split(data, []byte{'\n'})

	res := solution(grid)
	fmt.Println(res)
}

func solution(grid [][]byte) int {
	sr, sc := findS(grid)

	memo := make([]map[int]int, len(grid))
	for r := range memo {
		memo[r] = make(map[int]int)
	}

	return timelines(grid, sr, sc, memo)
}

func findS(grid [][]byte) (sr int, sc int) {
	for r := range len(grid) {
		for c := range len(grid[r]) {
			if grid[r][c] == 'S' {
				sr, sc = r, c
				return
			}
		}
	}
	panic("no S")
}

func timelines(grid [][]byte, r, c int, memo []map[int]int) int {
	rows, cols := len(grid), len(grid[r])

	if r < 0 || r >= rows || c < 0 || c >= cols {
		return 0
	}
	if r == rows-1 {
		return 1
	}
	if sol, ok := memo[r][c]; ok {
		return sol
	}

	if grid[r][c] != '^' {
		return timelines(grid, r+1, c, memo)
	}

	memo[r][c] = timelines(grid, r, c-1, memo) + timelines(grid, r, c+1, memo)

	return memo[r][c]
}
