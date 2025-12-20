#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Equation {
	long long want;
	std::vector<long long> values;
};

long long solve(const std::vector<Equation>& eqs);
bool is_possible(long long want, const std::vector<long long>& values, int i);
int count_digits(long long v);
bool has_suffix(long long v, long long suffix);
long long remove_suffix(long long v, int digits);

int main() {
	std::ifstream file("input.txt");
	if (!file) {
		return EXIT_FAILURE;
	}

	std::vector<Equation> eqs;

	std::string line;
	while (std::getline(file, line)) {
		Equation eq;

		std::stringstream ss(line);

		std::string want;
		std::getline(ss, want, ':');
		eq.want = std::stoll(want);

		std::vector<long long> values;
		long long v;
		while (ss >> v) {
			values.push_back(v);
		}
		eq.values = values;


		eqs.push_back(eq);
	}

	std::cout << solve(eqs);

	return 0;
}

long long solve(const std::vector<Equation>& eqs) {
	long long res { 0 };

	for (const auto& eq : eqs) {
		int n { static_cast<int>(eq.values.size()) };
		if (is_possible(eq.want, eq.values, n-1)) {
			res += eq.want;
		}
	}

	return res;
}

bool is_possible(long long want, const std::vector<long long>& values, int i) {
	if (want == 0 && i == -1) {
		return true;
	}
	if (want < 0 || i == -1) {
		return false;
	}

	bool res { is_possible(want-values[i], values, i-1) };

	if (want%values[i] == 0 && !res) {
		res = res || is_possible(want/values[i], values, i-1);
	}

	if (has_suffix(want, values[i]) && !res) {
		int digits { count_digits(values[i]) };
		res = res || is_possible(remove_suffix(want, digits), values, i-1);
	}

	return res;
}

int count_digits(long long v) {
	return static_cast<int>(std::ceil(std::log10(v+1)));
}

bool has_suffix(long long v, long long suffix) {
	int digits { count_digits(suffix) };
	long long div { std::llround(std::pow(10, digits)) };
	return v%div == suffix;
}

long long remove_suffix(long long v, int digits) {
	long long div { std::llround(std::pow(10, digits)) };
	return v / div;
}
