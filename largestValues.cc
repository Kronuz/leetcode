/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o largestValues ./largestValues.cc && ./largestValues
*/
#include <iostream>

#include <string>
#include <vector>
#include <deque>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
	vector<int> largestValues(TreeNode* root) {
		vector<int> result;
		if (!root) return result;

		deque<TreeNode*> pending;
		pending.push_back(root);
		pending.push_back(nullptr);

		int max = numeric_limits<int>::min();
		while (!pending.empty()) {
			auto node = pending.front();
			pending.pop_front();
			if (node) {
				if (node->left) {
					pending.push_back(node->left);
				}
				if (node->right) {
					pending.push_back(node->right);
				}
				if (max < node->val) {
					max = node->val;
				}
			} else {
				result.push_back(max);
				if (pending.empty()) {
					break;
				}
				pending.push_back(nullptr);
				max = numeric_limits<int>::min();
			}
		}
		return result;
	}
};


int main() {
	{
		Solution solution;
		TreeNode* root = new TreeNode(1);
		root->left = new TreeNode(3);
		root->right = new TreeNode(2);
		root->left->left = new TreeNode(5);
		root->left->right = new TreeNode(3);
		root->right->right = new TreeNode(9);
		auto result = solution.largestValues(root);
		assert(result == vector<int>({1, 3, 9}));
	}
	return 0;
}
