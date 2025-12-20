#include <cstdlib>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

enum class Dir { UP, DOWN, LEFT, RIGHT };

int solve(const std::vector<std::string>& grid);
std::pair<int, int> find_start(const std::vector<std::string>& grid);
int walk(const std::vector<std::string>& grid, std::pair<int, int> pos, Dir dir, std::set<std::pair<int, int>>& visited);
Dir turn(Dir dir);
std::pair<int, int> next_position(std::pair<int, int> pos, Dir dir);
bool is_in_grid(const std::vector<std::string>& grid, std::pair<int, int> pos);
bool is_blocked(const std::vector<std::string>& grid, std::pair<int, int> pos, Dir dir);

int main() {
	std::ifstream file("input.txt");
	if (!file) {
		return EXIT_FAILURE;
	}

	std::vector<std::string> grid;

	std::string line;
	while (std::getline(file, line)) {
		grid.push_back(line);
	}

	std::cout << solve(grid);

	return 0;
}

int solve(const std::vector<std::string>& grid) {
	std::pair<int, int> start { find_start(grid) };
	std::set<std::pair<int, int>> visited;
	return walk(grid, start, Dir::UP, visited);
}

std::pair<int, int> find_start(const std::vector<std::string>& grid) {
	for (std::size_t r = 0; r < grid.size(); ++r) {
		for (std::size_t c = 0; c < grid[r].size(); ++c) {
			if (grid[r][c] == '^') {
				return {r, c};
			}
		}
	}

	return {-1, -1};
}

int walk(const std::vector<std::string>& grid, std::pair<int, int> pos, Dir dir, std::set<std::pair<int, int>>& visited) {
	if (!is_in_grid(grid, pos)) {
		return visited.size();
	}

	visited.insert(pos);

	while (is_blocked(grid, pos, dir)) {
		dir = turn(dir);
	}

	std::pair<int, int> next { next_position(pos, dir) };

	return walk(grid, next, dir, visited);
}

Dir turn(Dir dir) {
	switch (dir) {
		case Dir::UP:
			dir = Dir::RIGHT;
			break;
		case Dir::RIGHT:
			dir = Dir::DOWN;
			break;
		case Dir::DOWN:
			dir = Dir::LEFT;
			break;
		case Dir::LEFT:
			dir = Dir::UP;
			break;
	}

	return dir;
}

std::pair<int, int> next_position(std::pair<int, int> pos, Dir dir) {
	int r { std::get<0>(pos) };
	int c { std::get<1>(pos) };

	switch (dir) {
		case Dir::UP:
			--r;
			break;
		case Dir::DOWN:
			++r;
			break;
		case Dir::LEFT:
			--c;
			break;
		case Dir::RIGHT:
			++c;
			break;
	}

	return {r, c};
}

bool is_in_grid(const std::vector<std::string>& grid, std::pair<int, int> pos) {
	int r { std::get<0>(pos) };
	int c { std::get<1>(pos) };

	return r >= 0 && r < static_cast<int>(grid.size()) && c >= 0 && c < static_cast<int>(grid[r].size());
}

bool is_blocked(const std::vector<std::string>& grid, std::pair<int, int> pos, Dir dir) {
	std::pair<int, int> next { next_position(pos, dir) };

	int r { std::get<0>(next) };
	int c { std::get<1>(next) };

	return is_in_grid(grid, next) && grid[r][c] == '#';
}
