package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

type Machine struct {
	Config  int
	Buttons []int
}

func main() {
	file, err := os.Open("input.txt")
	if err != nil {
		log.Fatalf("failed to open: %v", err)
	}
	defer func() { _ = file.Close() }()

	scanner := bufio.NewScanner(file)

	var machines []Machine

	for scanner.Scan() {
		line := scanner.Text()
		parts := strings.Fields(line)

		config, n := parseConfig(parts[0])

		buttons := make([]int, len(parts)-2)
		for i, b := range parts[1 : len(parts)-1] {
			buttons[i] = parseButton(b, n)
		}

		machines = append(machines, Machine{config, buttons})
	}

	var res int
	for _, m := range machines {
		res += solve(m)
	}

	fmt.Println(res)
}

func parseConfig(config string) (int, int) {
	config = strings.Trim(config, "[]")

	var res int

	for i, c := range config {
		if c == '#' {
			n := len(config) - i - 1
			res |= 1 << n
		}
	}

	return res, len(config)
}

func parseButton(button string, configLen int) int {
	button = strings.Trim(button, "()")
	parts := strings.Split(button, ",")

	var res int

	for _, s := range parts {
		n, _ := strconv.Atoi(s)
		res |= 1 << (configLen - n - 1)
	}

	return res
}

func solve(m Machine) int {
	n := len(m.Buttons)

	var f func(int, int) int
	f = func(config, i int) int {
		if config == 0 {
			return 0
		}
		if i >= n {
			return -1
		}

		press := f(config^m.Buttons[i], i+1)
		skip := f(config, i+1)

		if press == -1 && skip == -1 {
			return -1
		}
		if press == -1 {
			return skip
		}
		if skip == -1 {
			return press + 1
		}

		return min(1+press, skip)
	}

	return f(m.Config, 0)
}
