package main

import (
	"fmt"
	"log"
	"math"
	"os"
	"strconv"
	"strings"
)

func main() {
	data, err := os.ReadFile("input.txt")
	if err != nil {
		log.Fatalf("failed to read file: %v", err)
	}

	parts := strings.Fields(string(data))

	stones := make([]int, len(parts))
	for i, s := range parts {
		v, _ := strconv.Atoi(s)
		stones[i] = v
	}

	res := solve(stones, 75)
	fmt.Println(res)
}

func solve(stones []int, blinks int) int {
	memo := make([]map[int]int, blinks+1)
	for i := range len(memo) {
		memo[i] = make(map[int]int)
	}

	var f func(int, int) int
	f = func(v int, n int) int {
		if n <= 0 {
			return 1
		}
		if sol, ok := memo[n][v]; ok {
			return sol
		}

		if v == 0 {
			memo[n][v] = f(1, n-1)
		} else if countDigits(v)%2 == 0 {
			left, right := split(v)
			memo[n][v] = f(left, n-1) + f(right, n-1)
		} else {
			memo[n][v] = f(v*2024, n-1)
		}

		return memo[n][v]
	}

	res := 0
	for _, stone := range stones {
		res += f(stone, blinks)
	}

	return res
}

func countDigits(v int) int {
	return int(math.Ceil(
		math.Log10(float64(v + 1)),
	))
}

func split(v int) (int, int) {
	n := countDigits(v)
	pow := n / 2
	div := int(math.Pow(10, float64(pow)))
	return v / div, v % div
}
