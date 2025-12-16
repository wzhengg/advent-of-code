#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int solve(const std::vector<std::vector<int>>& reports);
bool is_safe(const std::vector<int>& report);
bool is_safe_decreasing(const std::vector<int>& report);
bool is_safe_increasing(const std::vector<int>& report);

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
	return is_safe_decreasing(report) || is_safe_increasing(report);
}

bool is_safe_decreasing(const std::vector<int>& report) {
	for (std::size_t i = 0; i+1 < report.size(); ++i) {
		const int diff = report[i] - report[i+1];
		if (diff < 1 || diff > 3) {
			return false;
		}
	}
	return true;
}

bool is_safe_increasing(const std::vector<int>& report) {
	for (std::size_t i = 0; i+1 < report.size(); ++i) {
		int diff = report[i+1] - report[i];
		if (diff < 1 || diff > 3) {
			return false;
		}
	}
	return true;
}
