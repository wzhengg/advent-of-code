#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int solve(const std::vector<std::vector<int>>& reports);
bool is_safe(const std::vector<int>& report);
bool is_safe_dir(const std::vector<int>& report, int dir);

int main() {
	std::ifstream file("input.txt");
	if (!file) {
		return EXIT_FAILURE;
	}

	std::vector<std::vector<int>> reports;

	std::string line;
	while (std::getline(file, line)) {
		std::vector<int> report;
		std::stringstream ss(line);
		int x;
		while (ss >> x) {
			report.push_back(x);
		}
		reports.push_back(report);
	}

	std::cout << solve(reports) << '\n';

	return 0;
}

int solve(const std::vector<std::vector<int>>& reports) {
	int res = 0;
	for (const auto& report : reports) {
		if (is_safe(report)) {
			++res;
		}
	}
	return res;
}

bool is_safe(const std::vector<int>& report) {
	if (is_safe_dir(report, 1) || is_safe_dir(report, -1)) {
		return true;
	}

	for (std::size_t i = 0; i < report.size(); ++i) {
		std::vector<int> tmp;
		for (std::size_t j = 0; j < report.size(); ++j) {
			if (j != i) {
				tmp.push_back(report[j]);
			}
		}
		if (is_safe_dir(tmp, 1) || is_safe_dir(tmp, -1)) {
			return true;
		}
	}

	return false;
}

bool is_safe_dir(const std::vector<int>& report, int dir) {
	for (std::size_t i = 1; i < report.size(); ++i) {
		const int diff = dir * (report[i] - report[i-1]);
		if (diff < 1 || diff > 3) {
			return false;
		}
	}
	return true;
}
