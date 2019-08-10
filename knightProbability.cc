/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o knightProbability ./knightProbability.cc && ./knightProbability
*/
#include <iostream>

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;


class Solution {
public:
	double knightProbability(int N, int K, int r, int c, double* memo) {
		if (K == 0) return 1;

		int key = r + N * (c + N * (K - 1));
		if (memo[key]) return memo[key];

		constexpr const int x[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
		constexpr const int y[] = { 1, -1, 1, -1, 2, -2, 2, -2 };

		double ans = 0;
		for (int k = 0; k < 8; ++k) {
			int nx = r + x[k];
			int ny = c + y[k];
			if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
				ans += knightProbability(N, K - 1, nx, ny, memo) / 8;
			}
		}
		memo[key] = ans;
		return ans;
	}

public:
	double knightProbability(int N, int K, int r, int c) {
		auto memo = make_unique<double[]>(25 * 25 * 100);
		return knightProbability(N, K, r, c, memo.get());
	}
};


int main() {
	{
		Solution solution;
		auto common = solution.knightProbability(25, 100, 0, 0);
		std::cout << common << std::endl;
	}
	{
		Solution solution;
		auto common = solution.knightProbability(3, 2, 0, 0);
		std::cout << common << std::endl;
	}
	{
		Solution solution;
		auto common = solution.knightProbability(8, 30, 6, 4);
		std::cout << common << std::endl;
	}
	return 0;
}
