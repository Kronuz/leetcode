/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o ./build/nextPermutation ./nextPermutation.cc && ./build/nextPermutation
*/
#include <iostream>

#include <string>
#include <vector>
#include <array>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/* 31. Next Permutation
 * https://leetcode.com/problems/next-permutation/submissions/
 */

class Solution {
public:
    bool nextPermutation(vector<int>& nums) {
        auto first = nums.begin();
        auto last = nums.end();
        auto i = last;
        if (first == last || first == --i) {
            return false;
        }
        while (true) {
            auto ip = i;
            if (*--i < *ip) {
                auto j = last;
                while (*i >= *--j);
                swap(*i, *j);
                reverse(ip, last);
                return true;
            }
            if (i == first) {
                reverse(first, last);
                return false;
            }
        }
    }
};


int main() {
	{
		Solution solution;
		vector<int> nums = {1,2,3};
		while (solution.nextPermutation(nums)) {
			for (auto n : nums) cout << n << " ";
			cout << endl;
		}
		assert(nums == vector<int>({1,2,3}));
	}
	{
		Solution solution;
		vector<int> nums = {1,2,3};
		solution.nextPermutation(nums);
		assert(nums == vector<int>({1,3,2}));
	}
	{
		Solution solution;
		vector<int> nums = {3,2,1};
		solution.nextPermutation(nums);
		assert(nums == vector<int>({1,2,3}));
	}
	{
		Solution solution;
		vector<int> nums = {1,1,5};
		solution.nextPermutation(nums);
		assert(nums == vector<int>({1,5,1}));
	}
	return 0;
}
