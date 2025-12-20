#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

int solve(const std::vector<std::string>& grid);
std::vector<std::pair<int, int>> find_antinodes(const std::vector<std::string>& grid, std::pair<int, int> p, std::pair<int, int> q);

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
	std::unordered_map<char, std::vector<std::pair<int, int>>> antennas;

	for (std::size_t r = 0; r < grid.size(); ++r) {
		for (std::size_t c = 0; c < grid[r].size(); ++c) {
			char ch { grid[r][c] };
			if (ch == '.') {
				continue;
			}
			antennas[ch].push_back({r, c});
		}
	}

	std::set<std::pair<int, int>> set;

	for (const auto& [_, locs] : antennas) {
		for (std::size_t i = 0; i < locs.size(); ++i) {
			for (std::size_t j = i+1; j < locs.size(); ++j) {
				std::vector<std::pair<int, int>> antinodes { find_antinodes(grid, locs[i], locs[j]) };
				for (const auto& antinode : antinodes) {
					set.insert(antinode);
				}
			}
		}
	}

	return static_cast<int>(set.size());
}

std::vector<std::pair<int, int>> find_antinodes(const std::vector<std::string>& grid, std::pair<int, int> p, std::pair<int, int> q) {
	int dr { p.first - q.first };
	int dc { p.second - q.second };

	std::vector<std::pair<int, int>> antinodes;

	int pr { p.first };
	int pc { p.second };
	while (pr >= 0 && pr < static_cast<int>(grid.size()) && pc >= 0 && pc < static_cast<int>(grid[pr].size())) {
		antinodes.push_back({pr, pc});
		pr += dr;
		pc += dc;
	}

	int qr { q.first };
	int qc { q.second };
	while (qr >= 0 && qr < static_cast<int>(grid.size()) && qc >= 0 && qc < static_cast<int>(grid[qr].size())) {
		antinodes.push_back({qr, qc});
		qr -= dr;
		qc -= dc;
	}

	return antinodes;
}
