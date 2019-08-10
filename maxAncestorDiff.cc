/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o maxAncestorDiff ./maxAncestorDiff.cc && ./maxAncestorDiff
*/
#include <iostream>

#include <string>
#include <vector>

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
	pair<int, int> walk(TreeNode* node, int& ans) {
		int mi = node->val;
		int mx = node->val;
		if (node->left) {
			auto l = walk(node->left, ans);
			ans = max(ans, max(abs(node->val - l.first), abs(node->val - l.second)));
			if (mi > l.first) {
				mi = l.first;
			}
			if (mx < l.second) {
				mx = l.second;
			}
		}
		if (node->right) {
			auto r = walk(node->right, ans);
			ans = max(ans, max(abs(node->val - r.first), abs(node->val - r.second)));
			if (mi > r.first) {
				mi = r.first;
			}
			if (mx < r.second) {
				mx = r.second;
			}
		}
		return {mi, mx};
	}

public:
	int maxAncestorDiff(TreeNode* root) {
		int ans = 0;
		walk(root, ans);
		return ans;
	}
};


int main() {
	{
		Solution solution;
		TreeNode* root = new TreeNode(8);
		root->left = new TreeNode(3);
		root->right = new TreeNode(10);
		root->left->left = new TreeNode(1);
		root->left->right = new TreeNode(6);
		root->left->right->left = new TreeNode(4);
		root->left->right->right = new TreeNode(7);
		root->right->right = new TreeNode(14);
		root->right->right->left = new TreeNode(13);
		auto max = solution.maxAncestorDiff(root);
		assert(max == 7);
	}
	return 0;
}
