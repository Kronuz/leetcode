/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o ./build/tst ./tst.cc && ./build/tst
*/
#include <iostream>

#include <string>
#include <vector>
#include <array>
#include <unordered_set>
#include <unordered_map>

using namespace std;


class Solution {
	struct Next {
		constexpr Next() : day() {
			for (int n = 0; n < 256; ++n) {
				int next = 0;
				for (int i = 1; i < 7; ++i) {
					next |= !(((n >> (i - 1)) ^ (n >> (i + 1))) & 1) << i;
				}
				day[n] = next;
			}
		}

		int day[256];
	};

public:
	int toBits(const vector<int>& cells) {
		int bits = 0;
		for (int j = 0; j < 8; ++j) {
			bits |= cells[j] << j;
		}
		return bits;
	}

	vector<int> fromBits(int bits) {
		vector<int> cells(8);
		for (int j = 0; j < 8; ++j) {
			cells[j] = bits & 1;
			bits >>= 1;
		}
		return cells;
	}

	vector<int> prisonAfterNDays(vector<int>& cells, int N) {
		constexpr auto next = Next();
		array<int, 256> seen = {};
		int current = toBits(cells);
		while (N) {
			if (seen[current]) {
				N %= seen[current] - N;
			}
			seen[current] = N;
			if (N > 0) {
				--N;
				current = next.day[current];
			}
		}


		for (; N; --N) {
			current = next.day[current];
			if (seen[current]) {
				N %= seen[current] - N;
			} else {
				seen[current] = N;
			}
		}
		return fromBits(current);
	}
};

int main() {
	Solution solution;

	// vector<int> cells = {0,1,0,1,1,0,0,1};
	// auto result = solution.prisonAfterNDays(cells, 7);  // -> 0 0 1 1 0 0 0 0

	vector<int> cells = {1,0,0,1,0,0,1,0};
	auto result = solution.prisonAfterNDays(cells, 1000000000);  // -> 0 0 1 1 1 1 1 0

	// vector<int> cells = {0,0,1,1,1,0,0,0};
	// auto result = solution.prisonAfterNDays(cells, 682529619);  // -> 0 1 0 0 1 0 1 0

	// vector<int> cells = {0,1,1,1,0,0,0,0};
	// auto result = solution.prisonAfterNDays(cells, 99);  // -> 0 0 1 0 0 1 1 0

	for (auto cell : result) {
		std::cout << cell << ' ';
	}
	std::cout << std::endl;
	return 0;
}
