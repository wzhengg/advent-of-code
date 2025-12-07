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

	res := countAccessableRolls(grid)
	fmt.Println(res)
}

func countAccessableRolls(grid [][]byte) int {
	rows, cols := len(grid), len(grid[0])

	dirs := []struct{ r, c int }{
		{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1},
	}

	var res int

	for r := range rows {
		for c := range cols {
			if grid[r][c] != '@' {
				continue
			}

			var rolls int
			for _, d := range dirs {
				rr, cc := r+d.r, c+d.c
				if 0 <= rr && rr < rows && 0 <= cc && cc < cols && grid[rr][cc] == '@' {
					rolls++
				}
			}
			if rolls < 4 {
				res++
			}
		}
	}

	return res
}
