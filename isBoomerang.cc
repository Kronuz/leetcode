/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o ./build/isBoomerang ./isBoomerang.cc && ./build/isBoomerang
*/
#include <iostream>

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;


/* Remember high school math.
 * Three or more points are collinear, if slope of any two pairs of points is same.
 * If (x1, y1), (x2, y2), (x3, y3) are collinear then (y2 - y1) / (x2 - x1) == (y3 - y1) / (x3 - x1)
 * For avoiding zero division error, just use this normalized equation : (y2 - y1) * (x3 - x1) == (y3 - y1) * (x2 - x1)
 *
 * x1 = points[0][0]
 * y1 = points[0][1]
 * x2 = points[1][0]
 * y2 = points[1][1]
 * x3 = points[2][0]
 * y3 = points[2][1]
 */
class Solution {
public:
	bool isBoomerang(vector<vector<int>>& points) {
		return !((points[1][1] - points[0][1]) * (points[2][0] - points[0][0]) == (points[2][1] - points[0][1]) * (points[1][0] - points[0][0]));
	}
};


int main() {
	{
		Solution solution;
		vector<vector<int>> points = {{1,1},{2,3},{3,2}};
		auto common = solution.isBoomerang(points);
		std::cout << common << std::endl;
	}
	{
		Solution solution;
		vector<vector<int>> points = {{1,1},{2,2},{3,3}};
		auto common = solution.isBoomerang(points);
		std::cout << common << std::endl;
	}
	return 0;
}
