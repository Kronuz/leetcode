/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o deleteNode ./deleteNode.cc && ./deleteNode
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
	TreeNode* deleteNode(TreeNode* root, int key) {
		TreeNode** parent = nullptr;
		auto node = root;
		while (true) {
			if (!node || key == node->val) {
				break;
			}
			if (key < node->val) {
				parent = &node->left;
				node = node->left;
			} else {
				parent = &node->right;
				node = node->right;
			}
		}
		if (node) {
			if (!node->left) {
				if (parent) {
					(*parent) = node->right;
				} else {
					root = node->right;
				}
			} else if (!node->right) {
				if (parent) {
					(*parent) = node->left;
				} else {
					root = node->left;
				}
			} else {
				TreeNode** min_parent = &node->right;
				auto min = node->right;
				while (min->left) {
					min_parent = &min->left;
					min = min->left;
				}
				(*min_parent) = min->right;
				min->left = node->left;
				min->right = node->right;
				if (parent) {
					(*parent) = min;
				} else {
					root = min;
				}
			}
			delete node;
		}
		return root;
	}
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

int main() {
	{
		Solution solution;
		TreeNode* root = new TreeNode(5);
		root->left = new TreeNode(3);
		root->right = new TreeNode(6);
		root->left->left = new TreeNode(2);
		root->left->right = new TreeNode(4);
		root->right->right = new TreeNode(7);
		root = solution.deleteNode(root, 3);
		dump(root);
	}
	{
		Solution solution;
		TreeNode* root = new TreeNode(2);
		root->left = new TreeNode(1);
		root = solution.deleteNode(root, 2);
		dump(root);
	}
	return 0;
}
