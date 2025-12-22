#include <cstdlib>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

int solve(const std::vector<std::string>& grid);
int score(const std::vector<std::string>& grid, int r, int c, std::map<std::pair<int, int>, int>& memo);

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
	int res { 0 };

	for (std::size_t r = 0; r < grid.size(); ++r) {
		for (std::size_t c = 0; c < grid[r].size(); ++c) {
			if (grid[r][c] == '0') {
				std::map<std::pair<int, int>, int> memo;
				res += score(grid, r, c, memo);
			}
		}
	}

	return res;
}

int score(const std::vector<std::string>& grid, int r, int c, std::map<std::pair<int, int>, int>& memo) {
	int rows { static_cast<int>(grid.size()) };
	int cols { static_cast<int>(grid[0].size()) };

	if (r < 0 || r >= rows || c < 0 || c >= cols) {
		return 0;
	}
	if (grid[r][c] == '9') {
		return 1;
	}
	if (memo.contains({r, c})) {
		return memo[{r, c}];
	}


	memo[{r, c}] = 0;

	if (r-1 >= 0 && grid[r-1][c] - grid[r][c] == 1) {
		memo[{r, c}] += score(grid, r-1, c, memo);
	}
	if (r+1 < rows && grid[r+1][c] - grid[r][c] == 1) {
		memo[{r, c}] += score(grid, r+1, c, memo);
	}
	if (c-1 >= 0 && grid[r][c-1] - grid[r][c] == 1) {
		memo[{r, c}] += score(grid, r, c-1, memo);
	}
	if (c+1 < cols && grid[r][c+1] - grid[r][c] == 1) {
		memo[{r, c}] += score(grid, r, c+1, memo);
	}

	return memo[{r, c}];
}
