/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o romanToInt ./romanToInt.cc && ./romanToInt
*/
#include <iostream>

#include <string>
#include <vector>
#include <deque>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
public:
	int romanToInt(string s) {
		unordered_map<char, int> m = {
			{ 'I', 1 },
			{ 'V', 5 },
			{ 'X', 10 },
			{ 'L', 50 },
			{ 'C', 100 },
			{ 'D', 500 },
			{ 'M', 1000 },
		};
		int total = 0;
		int prev = 0;
		for (auto c : s) {
			auto num = m[c];
			if (prev && num > prev) {
				total += num - prev;
				prev = 0;
			} else {
				total += prev;
				prev = num;
			}
		}
		total += prev;
		return total;
	}
};


int main() {
	{
		Solution solution;
		auto result = solution.romanToInt("III");
		assert(result == 3);
	}
	{
		Solution solution;
		auto result = solution.romanToInt("IV");
		assert(result == 4);
	}
	{
		Solution solution;
		auto result = solution.romanToInt("IX");
		assert(result == 9);
	}
	{
		Solution solution;
		auto result = solution.romanToInt("LVIII");
		assert(result == 58);
	}
	{
		Solution solution;
		auto result = solution.romanToInt("MCMXCIV");
		assert(result == 1994);
	}
	return 0;
}
