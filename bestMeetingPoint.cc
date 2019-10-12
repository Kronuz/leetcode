/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o ./build/bestMeetingPoint ./bestMeetingPoint.cc && ./build/bestMeetingPoint
*/
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;


class Solution {
public:
	int bestMeetingPoint(vector<vector<int>> clients) {
		const int n = clients.size();
		if (n == 0) return 0;

		vector<int> xs;
		vector<int> ys;
		for (auto c: clients) {
			xs.push_back(c[0]);
			ys.push_back(c[1]);
		}

		// sort to get the median
		sort(xs.begin(), xs.end());
		sort(ys.begin(), ys.end());

		// get the median point
		int x = xs[n / 2];
		int y = ys[n / 2];

		// total distance from median point
		int total_dist = 0;
		for (auto c: clients) {
			total_dist += abs(c[0] - x) + abs(c[1] - y);
		}
		return total_dist;
	}
};


int main() {
	{
		Solution solution;
		vector<vector<int>> clients = {{1,0}, {1,1}};
		auto total_dist = solution.bestMeetingPoint(clients);
		assert(total_dist == 1);
	}
	{
		Solution solution;
		vector<vector<int>> clients = {{-4,3}, {-2,1}, {1,0}, {3,2}};
		auto total_dist = solution.bestMeetingPoint(clients);
		assert(total_dist == 14);
	}
	{
		Solution solution;
		vector<vector<int>> clients = {{1,2}, {3,1}, {3,2}, {2,3}, {7,12}};
		auto total_dist = solution.bestMeetingPoint(clients);
		assert(total_dist == 19);
	}
	return 0;
}
