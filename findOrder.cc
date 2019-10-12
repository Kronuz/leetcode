/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o ./build/findOrder ./findOrder.cc && ./build/findOrder
*/
#include <iostream>

#include <string>
#include <vector>
#include <deque>
#include <unordered_set>
#include <unordered_map>

using namespace std;


class Solution {
	bool visit(vector<vector<int>>& graph, vector<int>& visited, int course, vector<int>& courses) {
		if (visited[course] == 1) return false;
		if (visited[course] == 2) return true;
		visited[course] = 1;
		for (auto c : graph[course]) {
			if (!visit(graph, visited, c, courses)) {
				return false;
			}
		}
		visited[course] = 2;
		courses.push_back(course);
		return true;
	}

public:
	vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
		vector<vector<int>> graph(numCourses);
		for (auto p : prerequisites) {
			graph[p[0]].push_back(p[1]);
		}
		vector<int> visited(numCourses);
		vector<int> courses;
		for (int course = 0; course < numCourses; ++course) {
			if (!visit(graph, visited, course, courses)) {
				return {};
			}
		}
		return courses;
	}
};


int main() {
	{
		Solution solution;
		vector<vector<int>> prerequisites = {{0,1},{0,2},{1,2}};
		auto result = solution.findOrder(3, prerequisites);
		for (auto x : result) cout << x << endl;
		assert(result == vector<int>({2, 1, 0}));
	}
	{
		Solution solution;
		vector<vector<int>> prerequisites = {{1,0}};
		auto result = solution.findOrder(2, prerequisites);
		assert(result == vector<int>({0, 1}));
	}
	{
		Solution solution;
		vector<vector<int>> prerequisites = {{0,1},{1,0}};
		auto result = solution.findOrder(2, prerequisites);
		assert(result == vector<int>({}));
	}
	return 0;
}
