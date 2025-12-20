#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

int solve(const std::vector<std::string>& grid);
std::pair<std::pair<int, int>, std::pair<int, int>> find_antinodes(std::pair<int, int> p, std::pair<int, int> q);

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
				std::pair<std::pair<int, int>, std::pair<int, int>> antinodes { find_antinodes(locs[i], locs[j]) };

				std::pair<int, int> p { antinodes.first };
				int pr { p.first };
				int pc { p.second };
				if (pr >= 0 && pr < static_cast<int>(grid.size()) && pc >= 0 && pc < static_cast<int>(grid[pr].size())) {
					set.insert(p);
				}

				std::pair<int, int> q { antinodes.second };
				int qr { q.first };
				int qc { q.second };
				if (qr >= 0 && qr < static_cast<int>(grid.size()) && qc >= 0 && qc < static_cast<int>(grid[qr].size())) {
					set.insert(q);
				}
			}
		}
	}

	return static_cast<int>(set.size());
}

std::pair<std::pair<int, int>, std::pair<int, int>> find_antinodes(std::pair<int, int> p, std::pair<int, int> q) {
	int dr { p.first - q.first };
	int dc { p.second - q.second };
	return {{p.first+dr, p.second+dc}, {q.first-dr, q.second-dc}};
}
