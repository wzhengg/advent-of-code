#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

long long solve(const std::vector<long long>& vec);
long long f(long long stone, int blinks);
int count_digits(long long v);
std::pair<int, int> split(long long v);

int main() {
	std::ifstream file("input.txt");
	if (!file) {
		return EXIT_FAILURE;
	}

	std::vector<long long> stones;

	long long stone;
	while (file >> stone) {
		stones.push_back(stone);
	}

	std::cout << solve(stones);

	return 0;
}

long long solve(const std::vector<long long>& vec) {
	long long res { 0 };

	for (const auto stone : vec) {
		res += f(stone, 25);
	}

	return res;
}

long long f(long long stone, int blinks) {
	if (blinks == 0) {
		return 1;
	}

	if (stone == 0) {
		return f(1, blinks-1);
	}

	if (count_digits(stone) % 2 == 0) {
		std::pair<int, int> p { split(stone) };
		return f(p.first, blinks-1) + f(p.second, blinks-1);
	}

	return f(stone*2024, blinks-1);
}

int count_digits(long long v) {
	return static_cast<long long>(std::ceil(std::log10(v+1)));
}

std::pair<int, int> split(long long v) {
	int pow { count_digits(v) / 2 };
	long long div { std::llround(std::pow(10, pow)) };
	return {v/div, v%div};
}
