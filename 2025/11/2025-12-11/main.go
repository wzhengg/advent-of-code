package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strings"
)

const (
	source = "you"
	sink   = "out"
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

	visited := make(map[string]struct{})
	res := dfs(graph, source, visited)
	fmt.Println(res)
}

func dfs(graph map[string][]string, vertex string, visited map[string]struct{}) int {
	if vertex == sink {
		return 1
	}
	if _, ok := visited[vertex]; ok {
		return 0
	}

	visited[vertex] = struct{}{}

	res := 0
	for _, edge := range graph[vertex] {
		res += dfs(graph, edge, visited)
	}

	delete(visited, vertex)

	return res
}
