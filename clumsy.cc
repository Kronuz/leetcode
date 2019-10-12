/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o ./build/clumsy ./clumsy.cc && ./build/clumsy
*/
#include <iostream>

#include <string>
#include <vector>
#include <deque>
#include <unordered_set>
#include <unordered_map>

using namespace std;


class Solution {
public:
	int clumsy(int N) {
		if (N == 4) return 7;
		if (N == 3) return 6;
		if (N == 2) return 2;
		if (N == 1) return 1;
		int sum = 0;
		for (int i = N - 3; i > 0; i -= 4) {
			sum += i;
		}
		sum += N * (N - 1) / (N - 2);
		for (int i = N - 4; i > 0; i -= 4) {
			if (i >= 3) {
				sum -= i * (i - 1) / (i - 2);
			} else if (i == 2) {
				sum -= 2;
			} else if (i == 1) {
				sum -= 1;
			}
		}
		return sum;
	}
};


int main() {
	{
		Solution solution;
		auto result = solution.clumsy(4);
		assert(result == 7);
	}
	{
		Solution solution;
		auto result = solution.clumsy(10);
		assert(result == 12);
	}
	return 0;
}
