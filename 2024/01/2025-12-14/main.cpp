#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

long solve(std::vector<long>& v1, std::vector<long>& v2);

int main() {
	std::ifstream file("input.txt");
	if (!file) {
		return EXIT_FAILURE;
	}

	std::vector<long> v1, v2;

	long x, y;
	while (file >> x >> y) {
		v1.push_back(x);
		v2.push_back(y);
	}

	std::cout << solve(v1, v2);

	return 0;
}

long solve(std::vector<long>& v1, std::vector<long>& v2) {
	assert(v1.size() == v2.size());

	std::sort(v1.begin(), v1.end());
	std::sort(v2.begin(), v2.end());

	long res{0};
	for (std::size_t i = 0; i < v1.size(); ++i) {
		res += std::abs(v1[i] - v2[i]);
	}

	return res;
}
