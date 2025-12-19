#include <cstdlib>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int solve(const std::vector<std::string>& v);

int main() {
	std::ifstream file("input.txt");
	if (!file) {
		return EXIT_FAILURE;
	}

	std::vector<std::string> input;

	std::string line;
	while (std::getline(file, line)) {
		input.push_back(line);
	}

	std::cout << solve(input);

	return 0;
}

int solve(const std::vector<std::string>& v) {
	int res = 0;

	for (std::size_t r = 1; r < v.size()-1; ++r) {
		for (std::size_t c = 1; c < v[0].size()-1; ++c) {
			if (v[r][c] != 'A') {
				continue;
			}

			if ((v[r-1][c-1] == 'M' && v[r-1][c+1] == 'M' && v[r+1][c-1] == 'S' && v[r+1][c+1] == 'S') ||
				(v[r-1][c-1] == 'S' && v[r-1][c+1] == 'S' && v[r+1][c-1] == 'M' && v[r+1][c+1] == 'M') ||
				(v[r-1][c-1] == 'M' && v[r-1][c+1] == 'S' && v[r+1][c-1] == 'M' && v[r+1][c+1] == 'S') ||
				(v[r-1][c-1] == 'S' && v[r-1][c+1] == 'M' && v[r+1][c-1] == 'S' && v[r+1][c+1] == 'M')) {
				++res;
			}
		}
	}

	return res;
}
