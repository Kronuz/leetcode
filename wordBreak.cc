/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o ./build/wordBreak ./wordBreak.cc && ./build/wordBreak
*/
#include <iostream>

#include <string>
#include <vector>
#include <array>
#include <unordered_set>
#include <unordered_map>

using namespace std;


class Solution {
public:
	bool wordBreak(string s, vector<string>& wordDict) {
		unordered_set<string_view> words(wordDict.begin(), wordDict.end());
		size_t n = s.size();
		auto p = s.data();
		auto end = p + n;
		while (n) {
			cout << string_view(p, n) << endl;
			if (words.find(string_view(p, n)) != words.end()) {
				p += n;
				if (p == end) {
					return true;
				}
				n = end - p;
			} else {
				--n;
			}
		}
		n = s.size();
		end = s.data();
		p = end + n;
		while (n) {
			cout << string_view(p - n, n) << endl;
			if (words.find(string_view(p - n, n)) != words.end()) {
				p -= n;
				if (p == end) {
					return true;
				}
				n = p - end;
			} else {
				--n;
			}
		}
		return false;
	}
};


int main() {
	Solution solution;

	// vector<string> wordDict = {"leet", "code"};
	// auto result = solution.wordBreak("leetcode", wordDict);

	// vector<string> wordDict = {"aaaa","aaa"};
	// auto result = solution.wordBreak("aaaaaaa", wordDict);

	// vector<string> wordDict = {"cats","dog","sand","and","cat"};
	// auto result = solution.wordBreak("catsandog", wordDict);

	// vector<string> wordDict = {"a","abc","b","cd"};
	// auto result = solution.wordBreak("abcd", wordDict);

	vector<string> wordDict = {"c","bcd","d","ab"};
	auto result = solution.wordBreak("abcd", wordDict);

	std::cout << result << std::endl;
	return 0;
}
