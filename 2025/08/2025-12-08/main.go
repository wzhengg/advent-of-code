package main

import (
	"bufio"
	"container/heap"
	"fmt"
	"log"
	"os"
	"slices"
	"strconv"
	"strings"
)

type Position struct {
	X, Y, Z int
}

type Edge struct {
	U, V Position
}

type MinHeap []Edge

func (h MinHeap) Len() int { return len(h) }
func (h MinHeap) Less(i, j int) bool {
	sq := func(x int) int { return x * x }
	ei, ej := h[i], h[j]

	ui, vi := ei.U, ei.V
	di := sq(ui.X-vi.X) + sq(ui.Y-vi.Y) + sq(ui.Z-vi.Z)

	uj, vj := ej.U, ej.V
	dj := sq(uj.X-vj.X) + sq(uj.Y-vj.Y) + sq(uj.Z-vj.Z)

	return di < dj
}
func (h MinHeap) Swap(i, j int) { h[i], h[j] = h[j], h[i] }
func (h *MinHeap) Push(x any)   { *h = append(*h, x.(Edge)) }
func (h *MinHeap) Pop() any {
	n := len(*h)
	x := (*h)[n-1]
	*h = (*h)[:n-1]
	return x
}

type UnionFind struct {
	node   map[Position]int
	pos    map[int]Position
	parent []int
	rank   []int
	size   []int
}

func NewUnionFind(ps []Position) *UnionFind {
	n := len(ps)

	node := make(map[Position]int, n)
	pos := make(map[int]Position, n)
	for i, p := range ps {
		node[p] = i
		pos[i] = p
	}

	parent := make([]int, n)
	for i := range len(parent) {
		parent[i] = i
	}

	rank := make([]int, n)
	size := make([]int, n)
	for i := range len(size) {
		size[i] = 1
	}

	return &UnionFind{
		node:   node,
		pos:    pos,
		parent: parent,
		rank:   rank,
		size:   size,
	}
}

func (uf *UnionFind) Find(p Position) Position {
	u := uf.node[p]

	var find func(int) int
	find = func(v int) int {
		if v != uf.parent[v] {
			uf.parent[v] = find(uf.parent[v])
		}
		return uf.parent[v]
	}

	return uf.pos[find(u)]
}

func (uf *UnionFind) Union(p, q Position) bool {
	rootp, rootq := uf.Find(p), uf.Find(q)
	u, v := uf.node[rootp], uf.node[rootq]

	if u == v {
		return false
	}

	if uf.rank[u] < uf.rank[v] {
		uf.parent[u] = v
		uf.size[v] += uf.size[u]
	} else if uf.rank[u] > uf.rank[v] {
		uf.parent[v] = u
		uf.size[u] += uf.size[v]
	} else {
		uf.parent[u] = v
		uf.size[v] += uf.size[u]
		uf.rank[v]++
	}

	return true
}

func (uf *UnionFind) Size(p Position) int {
	root := uf.node[uf.Find(p)]
	return uf.size[root]
}

func (uf *UnionFind) ProductOfLargestNSizes(n int) int {
	tmp := make([]int, 0, len(uf.size))
	for u, par := range uf.parent {
		if u == par {
			tmp = append(tmp, uf.size[u])
		}
	}
	slices.SortFunc(tmp, func(a, b int) int { return b - a })

	n = min(n, len(uf.size))
	tmp = tmp[0:n]

	res := 1
	for _, s := range tmp {
		res *= s
	}

	return res
}

func main() {
	file, err := os.Open("input.txt")
	if err != nil {
		log.Fatalf("failed to open file: %v", err)
	}
	defer func() { _ = file.Close() }()

	ps := make([]Position, 0)

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		parts := strings.Split(line, ",")

		x, _ := strconv.Atoi(parts[0])
		y, _ := strconv.Atoi(parts[1])
		z, _ := strconv.Atoi(parts[2])

		ps = append(ps, Position{x, y, z})
	}

	res := solve(ps, 1000)
	fmt.Println(res)
}

func solve(ps []Position, connections int) int {
	n := len(ps)

	minHeap := &MinHeap{}
	for i := 0; i < n; i++ {
		for j := i + 1; j < n; j++ {
			e := Edge{U: ps[i], V: ps[j]}
			*minHeap = append(*minHeap, e)
		}
	}
	heap.Init(minHeap)

	uf := NewUnionFind(ps)

	for minHeap.Len() > 0 && connections > 0 {
		e := heap.Pop(minHeap).(Edge)
		uf.Union(e.U, e.V)
		connections--
	}

	return uf.ProductOfLargestNSizes(3)
}
