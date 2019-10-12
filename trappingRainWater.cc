/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o ./build/trappingRainWater ./trappingRainWater.cc && ./build/trappingRainWater
*/
#include <iostream>

#include <vector>
#include <deque>

using namespace std;

// https://leetcode.com/problems/trapping-rain-water/submissions/

class Solution {
public:
	int trappingRainWater(vector<int>& height) {
		auto n = height.size();
		int lmax = 0, rmax = 0;
		int water = 0;
		for (size_t l = 0; l < n; ++l) {
			auto r = n - l - 1;
			if (lmax < height[l]) {
				water -= l * (height[l] - lmax);
				lmax = height[l];
			}
			if (rmax < height[r]) {
				water -= l * (height[r] - rmax);
				rmax = height[r];
			}
			if (lmax > height[l]) {
				water += lmax - height[l];
			}
			if (rmax > height[r]) {
				water += rmax - height[r];
			}
		}
		return water / 2;
	}
};


int main() {
	{
		Solution solution;
		vector<int> height = {0,1,0,2,1,0,1,3,2,1,2,1};
		auto result = solution.trappingRainWater(height);
		assert(result == 6);
	}
	return 0;
}
