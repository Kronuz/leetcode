/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o ./build/findMinStep ./findMinStep.cc && ./build/findMinStep
*/
#include <iostream>

#include <string>
#include <vector>
#include <deque>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/* Zuma Game
 * https://leetcode.com/problems/zuma-game/
 */

class Solution {
public:
	int findMinStep(string board, string hand) {
		vector<size_t> h(128, 0);
		for (char color : hand) ++h[color];
		size_t res = 0, mi = numeric_limits<size_t>::max();
		dfs(board, h, res, mi);
		return mi == numeric_limits<size_t>::max() ? -1 : mi;
	}

	void dfs(string& board, vector<size_t>& hand, size_t res, size_t& mi) {
		if (board.size() == 0) {
			mi = min(res, mi);
		}
		size_t i = 0;
		size_t j = i;
		while (i < board.size()) {
			while (j < board.size() && board[j] == board[i]) {
				++j;
			}
			size_t reqb = 3 - (j - i);
			if (hand[board[i]] >= reqb) {
				hand[board[i]] -= reqb;
				string a = i == 0 ? "" : board.substr(0, i);
				string b = j == board.size() ? "" : board.substr(j);
				string nb = update(a + b);
				dfs(nb, hand, res + reqb, mi);
				hand[board[i]] += reqb;
			}
			i = j;
		}
	}

	string update(string s) {
		string olds = s;
		if (s.size() <= 2) return s;
		size_t l = 0, r = 0, count = 0;
		while (l <= r && r < s.size()) {
			if (s[l] == s[r]) {
				++r;
				++count;
			} else {
				// process
				while (l < r && count >= 3) {
					s.erase(l, r - l);
					l = r;
				}
				l = r;
				count = 0;
			}
		}

		if (l < r && count >= 3) return s.erase(l, count);
		if (olds == s) return s;
		return update(s);
	}
};


int main() {
	{
		Solution solution;
		auto result = solution.findMinStep("WRRBBW", "RB");
		assert(result == -1);
	}
	{
		Solution solution;
		auto result = solution.findMinStep("WWRRBBWW", "WRBRW");
		assert(result == 2);
	}
	{
		Solution solution;
		auto result = solution.findMinStep("G", "GGGGG");
		assert(result == 2);
	}
	{
		Solution solution;
		auto result = solution.findMinStep("RBYYBBRRB", "YRBGB");
		assert(result == 3);
	}
	return 0;
}
