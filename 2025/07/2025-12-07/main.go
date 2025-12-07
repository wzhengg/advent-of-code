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

	sr, sc := findS(grid)

	visited := make([][]bool, len(grid))
	for r := range visited {
		visited[r] = make([]bool, len(grid[r]))
	}

	res := splits(grid, sr, sc, visited)
	fmt.Println(res)
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

func splits(grid [][]byte, r, c int, visited [][]bool) int {
	if r < 0 || r >= len(grid) || c < 0 || c >= len(grid[r]) || visited[r][c] {
		return 0
	}

	visited[r][c] = true

	if grid[r][c] != '^' {
		return splits(grid, r+1, c, visited)
	}

	return 1 + splits(grid, r, c-1, visited) + splits(grid, r, c+1, visited)
}
