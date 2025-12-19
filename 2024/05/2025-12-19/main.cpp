#include <cstdlib>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

int solve(const std::unordered_set<std::string>& rules, const std::vector<std::vector<std::string>>& updates);
bool is_in_order(const std::unordered_set<std::string>& rules, const std::vector<std::string>& update);

int main() {
	std::ifstream file("input.txt");
	if (!file) {
		return EXIT_FAILURE;
	}

	std::unordered_set<std::string> rules;
	std::vector<std::vector<std::string>> updates;

	std::string line;
	while (std::getline(file, line)) {
		if (line.empty()) {
			break;
		}
		rules.insert(line);
	}

	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string page;
		std::vector<std::string> update;

		while (std::getline(ss, page, ',')) {
			update.push_back(page);
		}

		updates.push_back(update);
	}

	std::cout << solve(rules, updates);

	return 0;
}

int solve(const std::unordered_set<std::string>& rules, const std::vector<std::vector<std::string>>& updates) {
	int res = 0;

	for (const auto& update : updates) {
		if (is_in_order(rules, update)) {
			int m = update.size() / 2;
			res += std::stoi(update[m]);
		}
	}

	return res;
}

bool is_in_order(const std::unordered_set<std::string>& rules, const std::vector<std::string>& update) {
	for (std::size_t i = 0; i < update.size(); ++i) {
		for (std::size_t j = i+1; j < update.size(); ++j) {
			std::string rule = update[j] + "|" + update[i];
			if (rules.find(rule) != rules.end()) {
				return false;
			}
		}
	}

	return true;
}
