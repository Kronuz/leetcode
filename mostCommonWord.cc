/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o tst ./tst.cc && ./tst
*/
#include <iostream>

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;


class Solution {
public:
    string mostCommonWord(string paragraph, vector<string>& banned) {
        unordered_set<string> banned_set(banned.begin(), banned.end());
        unordered_map<string, size_t> words_map;
        string word;
        size_t common_cnt = 0;
        string common_word;
        paragraph.push_back(' ');
        for (auto c : paragraph) {
            switch (c) {
                case '!':
                case '?':
                case '\'':
                case ',':
                case ';':
                case '.':
                case ' ':
                    if (!word.empty() && banned_set.find(word) == banned_set.end()) {
                    	std::cout << "    " << word << std::endl;
                        auto cnt = ++words_map[word];
                        if (common_cnt < cnt) {
                            common_cnt = cnt;
                            common_word = word;
                        }
                    }
                    word.clear();
                    break;
                default:
                    if (c >= 'A' && c <= 'Z') {
                        c = c - 'A' + 'a';
                    }
                    word.push_back(c);
            }
        }
        return common_word;
    }
};


int main() {
	Solution solution;
	vector<string> banned = {"hit"};
	auto common = solution.mostCommonWord("Bob", banned);
	std::cout << common << std::endl;
	return 0;
}
