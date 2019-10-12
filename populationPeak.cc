/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o ./build/populationPeak ./populationPeak.cc && ./build/populationPeak
*/
#include <iostream>

#include <string>
#include <vector>
#include <array>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/*
 * 17:44 ~ 17:49  -> 18:03   (14m)
 *
 * Given a list of people with their birth and dead years
 * Find the year with the highest population (most people alive)
 *
 * [[1920, 1990], [1995, 2013], [1900, 1999], [1910, 2010], [1970, 2020]]
 *
 * O(n*log(n))
 */


class Solution {
public:
	int populationPeak(vector<vector<int>> years) {
		vector<pair<int, int>> lifespans;
		for (auto y : years) {                    // O(N)
			lifespans.push_back({y[0], 1});
			lifespans.push_back({y[1], -1});
		}
		sort(lifespans.begin(), lifespans.end()); // O(N*log(N))
		int max = 0;
		int year = 0;
		int total = 0;
		for (auto l : lifespans) {                // O(N)
			total += l.second;
			if (max < total) {
				max = total;
				year = l.first;
			}
		}
		return year;
	}
};


int main() {
	{
		Solution solution;
		vector<vector<int>> years = {{1920, 1990}, {1995, 2013}, {1900, 1999}, {1910, 2010}, {1970, 2020}};
		auto result = solution.populationPeak(years);
		cout << result << endl;
		assert(result == 1970); // or 1995
	}
	{
		Solution solution;
		vector<vector<int>> years = {{2000, 2010}, {1975, 2005}, {1975, 2003}, {1803, 1809}, {1750, 1869}, {1840, 1935}, {1803, 1921}, {1894, 1921}};
		auto result = solution.populationPeak(years);
		cout << result << endl;
		assert(result == 1803); // or 2000
	}
	return 0;
}
