/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o ./build/canPartitionKSubsets ./canPartitionKSubsets.cc && ./build/canPartitionKSubsets
*/
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Solution {
	bool partition(vector<int>& nums, int k, size_t start, int sum, int target, vector<bool> visited) {
		if (k == 1) return true;
		if (sum == target) return partition(nums, k - 1, 0, 0, target, visited);

		for (size_t i = start; i < nums.size(); ++i) {
			if (!visited[i] && sum + nums[i] <= target) {
                visited[i] = true;
                if (partition(nums, k, i + 1, sum + nums[i], target, visited)) return true;
                visited[i] = false;
			}
		}
		return false;
	}

public:
	bool canPartitionKSubsets(vector<int>& nums, int k) {
		int sum = 0;
		for (auto n : nums) sum += n;
		if (sum % k) return false;

		vector<bool> visited(nums.size(), false);
		return (partition(nums, k, 0, 0, sum / k, visited));
	}
};


int main() {
	{
		Solution solution;
		vector<int> nums = {4, 3, 2, 3, 5, 2, 1};
		auto can = solution.canPartitionKSubsets(nums, 4);
		assert(can == true);
	}
	return 0;
}
