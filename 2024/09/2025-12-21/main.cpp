#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

long long solve(const std::vector<int>& vec);
std::vector<int> expand(const std::vector<int>& vec);
void compact(std::vector<int>& vec);
long long checksum(const std::vector<int>& vec);

int main() {
	std::ifstream file("input.txt");
	if (!file) {
		return EXIT_FAILURE;
	}

	std::vector<int> vec;

	std::string line;
	file >> line;
	for (char c : line) {
		vec.push_back(c - '0');
	}

	std::cout << solve(vec);

	return 0;
}

long long solve(const std::vector<int>& vec) {
	std::vector<int> expanded { expand(vec) };
	compact(expanded);
	return checksum(expanded);
}

std::vector<int> expand(const std::vector<int>& vec) {
	std::vector<int> expanded;
	int id { 0 };

	for (std::size_t i = 0; i < vec.size(); ++i) {
		if (i % 2 == 0) {
			expanded.insert(expanded.end(), vec[i], id++);
		} else {
			expanded.insert(expanded.end(), vec[i], -1);
		}
	}

	return expanded;
}

void compact(std::vector<int>& vec) {
	int l { 0 };
	int r { static_cast<int>(vec.size()) - 1 };

	while (l < r) {
		while (vec[l] != -1 && l < r) ++l;
		while (vec[r] == -1 && l < r) --r;

		std::swap(vec[l], vec[r]);

		++l;
		--r;
	}
}

long long checksum(const std::vector<int>& vec) {
	long long res { 0 };

	for (std::size_t i = 0; i < vec.size() && vec[i] != -1; ++i) {
		res += i * vec[i];
	}

	return res;
}
