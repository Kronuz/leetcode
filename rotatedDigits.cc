/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o ./build/rotatedDigits ./rotatedDigits.cc && ./build/rotatedDigits
*/
#include <iostream>

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;


class Solution {
	int isValid(int n) {
		int valid = 0;
		while (n) {
			int d = n % 10;
			if (d == 3 || d == 4 || d == 7)
				return 0;
			if (d == 2 || d == 5 || d == 6 || d == 9)
				valid = 1;
			n /= 10;
		}
		return valid;
	}

public:
	int rotatedDigits(int N) {
		int cnt = 0;
		for (int n = 1; n <= N; ++n) {
			cnt += isValid(n);
		}
		return cnt;
	}
};


int main() {
	{
		Solution solution;
		auto common = solution.rotatedDigits(10);
		std::cout << common << std::endl;
	}
	return 0;
}
