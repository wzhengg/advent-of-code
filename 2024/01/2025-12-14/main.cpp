#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

long solve(const std::vector<long>& v1, const std::vector<long>& v2);

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

	std::cout << solve(v1, v2) << '\n';

	return 0;
}

long solve(const std::vector<long>& v1, const std::vector<long>& v2) {
	std::unordered_map<long, long> count;
	count.reserve(v2.size());
	for (long v : v2) {
		++count[v];
	}

	long res = 0;
	for (long v : v1) {
		res += v * count[v];
	}

	return res;
}
