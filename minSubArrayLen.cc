/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o minSubArrayLen ./minSubArrayLen.cc && ./minSubArrayLen
*/
#include <iostream>

#include <string>
#include <vector>
#include <deque>
#include <stack>
#include <unordered_set>
#include <unordered_map>

using namespace std;


/* We grow, shrink, and slide a window based on the current sum of the window.
 * This is basically the same as solution 4 but more verbose. It is VERY easily
 * adapted to find the smallest consecutive subset that EXACTLY equals the
 * target, simply remove the store operation from the 'too big' case.
 *
 * Sliding Window with a target of 7
 *
 * [2]3 1 2 4 3   ->   2, too small, back++
 * [2 3]1 2 4 3   ->   5, too small, back++
 * [2 3 1]2 4 3   ->   6, too small, back++
 * [2 3 1 2]4 3   ->   8, too big, front++ (STORE)
 *  2[3 1 2]4 3   ->   6, too small, back++
 *  2[3 1 2 4]3   ->  10, too big, front++ (STORE)
 *  2 3[1 2 4]3   ->   7, matches, front++, back++ (STORE)
 *  2 3 1[2 4 3]  ->   9, too big, front++ (STORE)
 *  2 3 1 2[4 3]  ->   7, matches, front++, back++ (STORE)
 */


class Solution {
public:
	int minSubArrayLen(int target, vector<int>& nums) {
		if (nums.size() == 0) return 0;
		size_t front = 0, back = 0;
		size_t result = numeric_limits<int>::max();
		int sum = nums[front];

		while (true) {
			if (sum == target) {
				// matches, store, shift window forward w/ back++ front++,
				result = min(back - front + 1, result);
				if (back + 1 != nums.size()) sum += nums[++back];
				sum -= nums[front++];
			} else if (sum < target) {
				// too small, increase window w/ back++
				if (back + 1 == nums.size()) break;
				sum += nums[++back];
			} else {
				// too big, store, decrease window w/ front++
				result = min(back - front + 1, result);
				sum -= nums[front++];
			}
		}
		return result == numeric_limits<int>::max() ? 0 : result;
	}
};


int main() {
	{
		Solution solution;
		vector<int> nums = {2,3,1,2,4,3};
		auto len = solution.minSubArrayLen(7, nums);
		cout << len << endl;
	}
	{
		Solution solution;
		vector<int> nums = {2,3,1,2,0,7};
		auto len = solution.minSubArrayLen(7, nums);
		cout << len << endl;
	}
	return 0;
}
