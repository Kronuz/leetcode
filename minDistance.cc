/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o ./build/minDistance ./minDistance.cc && ./build/minDistance
*/
#include <iostream>

#include <string>
#include <vector>
#include <deque>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/* Edit Distance
 * https://leetcode.com/problems/edit-distance/submissions/
 *
 * Using Levenshtein edit distance
 */


class Solution {
public:
	int minDistance(string word1, string word2) {
		size_t len1 = word1.size();
		size_t len2 = word2.size();
		vector<int> d1(len2 + 1);
		vector<int> d2(len2 + 1);
		auto thisrow = &d1[0];
		auto prevrow = &d2[0];
		for (size_t x = 0; x <= len2; ++x) thisrow[x] = x;
		for (size_t i = 1; i <= len1; ++i) {
			swap(thisrow, prevrow);
			thisrow[0] = i;
			for (size_t j = 1; j <= len2; ++j) {
				thisrow[j] = min({
					prevrow[j] + 1,
					thisrow[j - 1] + 1,
					prevrow[j - 1] + (word1[i - 1] == word2[j - 1] ? 0 : 1),
				});
			}
		}
		return thisrow[len2];
	}
};


int main() {
	{
		Solution solution;
		auto result = solution.minDistance("horse", "ros");
		assert(result == 3);
	}
	return 0;
}
