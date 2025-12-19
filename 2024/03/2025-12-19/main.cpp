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

	for (std::size_t r = 0; r < v.size(); ++r) {
		for (std::size_t c = 0; c < v[0].size(); ++c) {
			if (v[r][c] != 'X') {
				continue;
			}

			if (r >= 3 && v[r-1][c] == 'M' && v[r-2][c] == 'A' && v[r-3][c] == 'S') {
				++res;
			}
			if (r+3 < v.size() && v[r+1][c] == 'M' && v[r+2][c] == 'A' && v[r+3][c] == 'S') {
				++res;
			}
			if (c >= 3 && v[r][c-1] == 'M' && v[r][c-2] == 'A' && v[r][c-3] == 'S') {
				++res;
			}
			if (c+3 < v[0].size() && v[r][c+1] == 'M' && v[r][c+2] == 'A' && v[r][c+3] == 'S') {
				++res;
			}
			if (r >= 3 && c >= 3 && v[r-1][c-1] == 'M' && v[r-2][c-2] == 'A' && v[r-3][c-3] == 'S') {
				++res;
			}
			if (r >= 3 && c+3 < v[0].size() && v[r-1][c+1] == 'M' && v[r-2][c+2] == 'A' && v[r-3][c+3] == 'S') {
				++res;
			}
			if (r+3 < v.size() && c >= 3 && v[r+1][c-1] == 'M' && v[r+2][c-2] == 'A' && v[r+3][c-3] == 'S') {
				++res;
			}
			if (r+3 < v.size() && c+3 < v[0].size() && v[r+1][c+1] == 'M' && v[r+2][c+2] == 'A' && v[r+3][c+3] == 'S') {
				++res;
			}
		}
	}

	return res;
}
