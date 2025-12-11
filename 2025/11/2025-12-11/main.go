package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strings"
)

func main() {
	file, err := os.Open("input.txt")
	if err != nil {
		log.Fatalf("failed to open file: %v", err)
	}
	defer func() { _ = file.Close() }()

	graph := make(map[string][]string)

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		parts := strings.Split(line, ": ")

		vertex := parts[0]
		edges := strings.Fields(parts[1])
		graph[vertex] = edges
	}

	res := solve(graph)
	fmt.Println(res)
}

// The graph is a DAG
// It's possible to get from fft to dac, but not the other way around
// svr -> fft -> dac -> out
// svr->fft * fft->dac * dac->out

func solve(graph map[string][]string) int {
	memo := make(map[string]int, len(graph))
	svr_fft := dfs(graph, "svr", "fft", memo)

	clear(memo)
	fft_dac := dfs(graph, "fft", "dac", memo)

	clear(memo)
	dac_out := dfs(graph, "dac", "out", memo)

	return svr_fft * fft_dac * dac_out
}

func dfs(graph map[string][]string, vertex, sink string, memo map[string]int) int {
	if vertex == sink {
		return 1
	}
	if sol, ok := memo[vertex]; ok {
		return sol
	}

	for _, edge := range graph[vertex] {
		memo[vertex] += dfs(graph, edge, sink, memo)
	}

	return memo[vertex]
}
