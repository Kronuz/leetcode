/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o ./build/checkValidString ./checkValidString.cc && ./build/checkValidString
*/
#include <iostream>

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/*
 * See more code in my repo [LeetCode](https://github.com/lzl124631x/LeetCode)
 *
 * Let 1 be count of left parenthesis minus count of right parenthesis.
 *
 * When we meet:
 *
 * `(`, we increment `diff`.
 * `)`, we decrement `diff`.
 * `*`, we have three choices which makes the `diff` become a range -- `[diff - 1, diff + 1]`.
 * So we use `maxDiff`/`minDiff` to record the maximum/minimum `diff` we can get.
 *
 * When we meet:
 *
 * `(`, `++maxDiff` and `++minDiff`.
 * `)`, `--maxDiff` and `--minDiff`.
 * `*`, `++maxDiff` and `--minDiff`.
 * If `maxDiff` become negative, it means it's already invalid, we should return `false`.
 *
 * Whenever `minDiff` falls below `0`, we should force it to be `0` because we never accept negative `diff` during the process.
 *
 * After scanning through string `s`, as long as `minDiff` is `0`, this string can be a valid one.
 */

// OJ: https://leetcode.com/problems/valid-parenthesis-string/
// Author: github.com/lzl124631x
// Time: O(S)
// Space: O(1)
class Solution {
public:
	bool checkValidString(string s) {
		int maxDiff = 0, minDiff = 0;
		for (char c : s) {
			maxDiff += (c == '(' || c == '*') ? 1 : -1;
			minDiff += (c == ')' || c == '*') ? -1 : 1;
			if (maxDiff < 0) return false;
			minDiff = max(0, minDiff);
			cout << c << " [" << maxDiff << ", " << minDiff << "]" << endl;
		}
		return minDiff == 0;
	}
};


int main() {
	{
		Solution solution;
		auto common = solution.checkValidString("()");
		std::cout << common << std::endl;
	}
	{
		Solution solution;
		auto common = solution.checkValidString("(*)");
		std::cout << common << std::endl;
	}
	{
		Solution solution;
		auto common = solution.checkValidString("(())((())()()(*)(*()(())())())()()((()())((()))(*");
		std::cout << common << std::endl;
	}
	{
		Solution solution;
		auto common = solution.checkValidString("(*))");
		std::cout << common << std::endl;
	}
	return 0;
}
