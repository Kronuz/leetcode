/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o subarraySum ./subarraySum.cc && ./subarraySum
*/
#include <iostream>

#include <string>
#include <vector>
#include <deque>
#include <unordered_set>
#include <unordered_map>

using namespace std;


/*
 * Because sum(i,j) = sum(0,j) - sum(0,i)
 * If we want sum(i,j) = k
 * k = sum(0,j) - sum(0,i)
 * sum(0,i) = sum(0,j) - k
 */


class Solution {
public:
	int subarraySum(vector<int>& nums, int k) {
		int ans = 0;
		int nsum = 0;
		unordered_map<int, int> prefix_sum;
		prefix_sum[0] = 1; // at least one way to get 0, by not picking any n from nums
		for (int n : nums) {
			nsum += n;
			ans += prefix_sum[nsum - k];
			++prefix_sum[nsum];
		}
		return ans;
	}
};


int main() {
	{
		Solution solution;
		vector<int> nums = {1,1,1};
		int k = 2;
		auto result = solution.subarraySum(nums, k);
		assert(result == 2);
	}
	{
		Solution solution;
		vector<int> nums = {1};
		int k = 0;
		auto result = solution.subarraySum(nums, k);
		assert(result == 0);
	}
	return 0;
}
