#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

long long solve(const std::vector<long long>& vec, int blinks);
long long f(long long stone, int blinks, std::vector<std::unordered_map<long long, long long>>& memo);
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

	std::cout << solve(stones, 75);

	return 0;
}

long long solve(const std::vector<long long>& vec, int blinks) {
	long long res { 0 };

	for (const auto stone : vec) {
		std::vector<std::unordered_map<long long, long long>> memo;
		for (int i = 0; i <= blinks; ++i) {
			memo.push_back({});
		}
		res += f(stone, blinks, memo);
	}

	return res;
}

long long f(long long stone, int blinks, std::vector<std::unordered_map<long long, long long>>& memo) {
	if (blinks == 0) {
		return 1;
	}
	if (memo[blinks].contains(stone)) {
		return memo[blinks][stone];
	}

	if (stone == 0) {
		memo[blinks][stone] = f(1, blinks-1, memo);
	} else if (count_digits(stone) % 2 == 0) {
		std::pair<int, int> p { split(stone) };
		memo[blinks][stone] = f(p.first, blinks-1, memo) + f(p.second, blinks-1, memo);
	} else {
		memo[blinks][stone] = f(stone*2024, blinks-1, memo);
	}

	return memo[blinks][stone];
}

int count_digits(long long v) {
	return static_cast<long long>(std::ceil(std::log10(v+1)));
}

std::pair<int, int> split(long long v) {
	int pow { count_digits(v) / 2 };
	long long div { std::llround(std::pow(10, pow)) };
	return {v/div, v%div};
}
