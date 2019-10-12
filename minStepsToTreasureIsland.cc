/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o ./build/minStepsToTreasureIsland ./minStepsToTreasureIsland.cc && ./build/minStepsToTreasureIsland
*/
#include <iostream>

#include <vector>
#include <deque>

using namespace std;

/*
 * https://leetcode.com/discuss/interview-question/347457/Amazon-or-OA-2019-or-Treasure-Island
 *
 * You have a map that marks the location of a treasure island. Some of the map
 * area has jagged rocks and dangerous reefs. Other areas are safe to sail in.
 * There are other explorers trying to find the treasure. So you must figure out a
 * shortest route to the treasure island.
 *
 * Assume the map area is a two dimensional grid, represented by a matrix of
 * characters. You must start from the top-left corner of the map and can move one
 * block up, down, left or right at a time. The treasure island is marked as X in a
 * block of the matrix. X will not be at the top-left corner. Any block with
 * dangerous rocks or reefs will be marked as D. You must not enter dangerous
 * blocks. You cannot leave the map area. Other areas O are safe to sail in. The
 * top-left corner is always safe. Output the minimum number of steps to get to the
 * treasure.

 * Example:
 *
 * Input:
 *   [['O', 'O', 'O', 'O'],
 *    ['D', 'O', 'D', 'O'],
 *    ['O', 'O', 'O', 'O'],
 *    ['X', 'D', 'D', 'O']]
 *
 * Output: 5
 * Explanation: The minimum route takes 5 steps.
 *              Route is (0, 0), (0, 1), (1, 1), (2, 1), (2, 0), (3, 0)
 *
 */

class Solution {
	struct position {
		int x;
		int y;
		int steps;
	};

public:
	int minStepsToTreasureIsland(vector<vector<char>> grid) {
		// Using BFS
		deque<position> pending;
		pending.push_back({ 0, 0, 0 });  // start at (0, 0)
		while (!pending.empty()) {
			auto cur = pending.front();
			pending.pop_front();
			if (cur.y >= 0 && cur.y < static_cast<int>(grid.size()) &&
				cur.x >= 0 && cur.x < static_cast<int>(grid[cur.y].size())) {
				if (grid[cur.y][cur.x] == 'X') {
					return cur.steps;
				}
				if (grid[cur.y][cur.x] == 'O') {
					grid[cur.y][cur.x] = ' ';  // flag as used
					pending.push_back({ cur.x,     cur.y - 1, cur.steps + 1 });  // up
					pending.push_back({ cur.x - 1, cur.y,     cur.steps + 1 });  // left
					pending.push_back({ cur.x,     cur.y + 1, cur.steps + 1 });  // bottom
					pending.push_back({ cur.x + 1, cur.y,     cur.steps + 1 });  // right
				}
			}
		}
		return -1;
	}
};


int main() {
	{
		Solution solution;
		vector<vector<char>> grid = {
			{'O', 'O', 'O', 'O'},
			{'D', 'O', 'D', 'O'},
			{'O', 'O', 'O', 'O'},
			{'X', 'D', 'D', 'O'},
		};

		auto result = solution.minStepsToTreasureIsland(grid);
		assert(result == 5);
	}
	{
		Solution solution;
		vector<vector<char>> grid = {
			{'O', 'O', 'O', 'O'},
			{'D', 'D', 'D', 'O'},
			{'O', 'O', 'O', 'O'},
			{'X', 'D', 'D', 'O'},
		};

		auto result = solution.minStepsToTreasureIsland(grid);
		assert(result == 9);
	}
	{
		Solution solution;
		vector<vector<char>> grid = {
			{'O', 'O', 'O', 'O'},
			{'D', 'D', 'D', 'O'},
			{'O', 'D', 'O', 'O'},
			{'X', 'D', 'D', 'O'},
		};

		auto result = solution.minStepsToTreasureIsland(grid);
		assert(result == -1);
	}
	{
		Solution solution;
		vector<vector<char>> grid = {
			{'O', 'O', 'O', 'O', 'O'},
			{'D', 'D', 'D', 'D', 'O'},
			{'O', 'D', 'O', 'O', 'O'},
			{'X', 'D', 'O'},
			{'O', 'O', 'O'},
		};

		auto result = solution.minStepsToTreasureIsland(grid);
		assert(result == 13);
	}
	return 0;
}
