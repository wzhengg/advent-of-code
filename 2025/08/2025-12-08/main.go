package main

import (
	"bufio"
	"container/heap"
	"fmt"
	"log"
	"os"
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
	node       map[Position]int
	pos        map[int]Position
	parent     []int
	rank       []int
	components int
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

	return &UnionFind{
		node:       node,
		pos:        pos,
		parent:     parent,
		rank:       rank,
		components: n,
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
	} else if uf.rank[u] > uf.rank[v] {
		uf.parent[v] = u
	} else {
		uf.parent[u] = v
		uf.rank[v]++
	}
	uf.components--

	return true
}

func (uf *UnionFind) Components() int {
	return uf.components
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

	res := solve(ps)
	fmt.Println(res)
}

func solve(ps []Position) int {
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

	var e Edge
	for minHeap.Len() > 0 && uf.components > 1 {
		e = heap.Pop(minHeap).(Edge)
		uf.Union(e.U, e.V)
	}

	return e.U.X * e.V.X
}
