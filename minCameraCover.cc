/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o minCameraCover ./minCameraCover.cc && ./minCameraCover
*/
#include <iostream>

#include <string>
#include <vector>
#include <deque>
#include <stack>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void dump(TreeNode* root) {
	deque<TreeNode*> pending;
	pending.push_back(root);
	while (!pending.empty()) {
		auto node = pending.front();
		pending.pop_front();
		if (node) {
			pending.push_back(node->left);
			pending.push_back(node->right);
			cout << node->val << " ";
		} else {
			cout << "null" << " ";
		}
	}
	cout << endl;
}


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
/* The solution starts with the idea that we need to setup
 * cameras at all the nodes that are parents of leafs.
 */
public:
	int count = 0;
	int dfs(TreeNode* node) {
		if (!node) {
			return 3; // no node here, its a dead value just ignore
		}
		int l = dfs(node->left);
		int r = dfs(node->right);
		if (l == 0 || r == 0) {
			++count;
			return 1; // hey parent, I'm setting up camera, free coverage for you
		}
		if (l == 1 || r == 1) {
			return 2; // hey parent, I'm being covered, but I am not covering you
		}
		return 0; // hey parent, no one is covering me up, please cover me
	}

	int minCameraCover(TreeNode* root) {
		if (dfs(root) == 0) {
			++count; // if parent is not being covered, then let's seup a camera at parent
		}
		return count;
	}
};


int main() {
	{
		//      5
		//     / \
		//   *3  *6
		//   / \   \
		//  2   4   7
		Solution solution;
		TreeNode* root = new TreeNode(5);
		root->left = new TreeNode(3);
		root->right = new TreeNode(6);
		root->left->left = new TreeNode(2);
		root->left->right = new TreeNode(4);
		root->right->right = new TreeNode(7);
		auto cams = solution.minCameraCover(root);
		cout << cams << endl;
		dump(root);
	}
	{
		//     *4
		//     / \
		//    3   5
		//   /     \
		// *2      *6
		//  |       |
		//  1       7
		Solution solution;
		TreeNode* root = new TreeNode(4);
		root->left = new TreeNode(3);
		root->right = new TreeNode(5);
		root->left->left = new TreeNode(2);
		root->right->right = new TreeNode(6);
		root->left->left->left = new TreeNode(1);
		root->right->right->right = new TreeNode(7);
		auto cams = solution.minCameraCover(root);
		cout << cams << endl;
		dump(root);
	}
	return 0;
}
