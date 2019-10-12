/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o ./build/treeSerializer ./treeSerializer.cc && ./build/treeSerializer
*/
#include <iostream>

#include <string>
#include <vector>
#include <array>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/* 297. Serialize and Deserialize Binary Tree
 * https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
 */


struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
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
class Codec {
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		string ser = "[";
		queue<TreeNode*> pending;
		pending.push(root);
		size_t size = 1;
		while (!pending.empty()) {
			auto node = pending.front();
			pending.pop();
			if (node) {
				pending.push(node->left);
				pending.push(node->right);
				ser += to_string(node->val) + ",";
				size = ser.size() - 1;
			} else {
				ser += "null,";
			}
		}
		ser.resize(size);
		ser += "]";
		return ser;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		if (data.size() <= 2) {
			return nullptr;
		}
		bool neg = false;
		TreeNode* node = nullptr;
		queue<TreeNode*> nodes;
		for (auto c : data) {
			if (c == '-') {
				neg = true;
			} else if (c >= '0' && c <= '9') {
				if (!node) node = new TreeNode(0);
				node->val = node->val * 10 + c - '0';
			} else if (c == ',') {
				if (neg) {
					node->val *= -1;
				}
				nodes.push(node);
				node = nullptr;
				neg = false;
			}
		}
		if (node) {
			if (neg) {
				node->val *= -1;
			}
			nodes.push(node);
		}
		auto root = nodes.empty() ? nullptr : nodes.front();
		if (root) {
			vector<TreeNode*> level;
			level.push_back(root);
			nodes.pop();
			while (!level.empty()) {
				vector<TreeNode*> nextLevel;
				for (auto parent : level) {
					if (nodes.empty()) {
						node = nullptr;
					} else {
						node = nodes.front();
						nodes.pop();
					}
					if (node) {
						parent->left = node;
						nextLevel.push_back(node);
					}
					if (nodes.empty()) {
						node = nullptr;
					} else {
						node = nodes.front();
						nodes.pop();
					}
					if (node) {
						parent->right = node;
						nextLevel.push_back(node);
					}
				}
				level = nextLevel;
			}
		}
		return root;
	}
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));


int main() {
	{
		Codec codec;
		string ser = "[]";
		auto root = codec.deserialize(ser);
		auto result = codec.serialize(root);
		cout << result << endl;
		assert(result == ser);
	}
	{
		//           1
		//         /  \
		//        /    \
		//       2      3
		Codec codec;
		string ser = "[1,2,3]";
		auto root = codec.deserialize(ser);
		auto result = codec.serialize(root);
		cout << result << endl;
		assert(result == ser);
	}
	{
		//           1
		//         /  \
		//        /    \
		//              2
		//             /
		//            /
		//           3
		Codec codec;
		string ser = "[1,null,2,3]";
		auto root = codec.deserialize(ser);
		auto result = codec.serialize(root);
		cout << result << endl;
		assert(result == ser);
	}
	{
		//           1
		//         /  \
		//        /    \
		//       2      3
		//     / \     / \
		//    /   \   /   \
		//           4     5
		//          / \   / \
		//                   6
		Codec codec;
		string ser = "[1,2,3,null,null,4,5,null,null,null,6]";
		auto root = codec.deserialize(ser);
		auto result = codec.serialize(root);
		cout << result << endl;
		assert(result == ser);
	}
	{
		//          5
		//        /  \
		//       /    \
		//      4      7
		//     / \    / \
		//    3      2
		//   | \    |
		//  -1      9
		Codec codec;
		string ser = "[5,4,7,3,null,2,null,-1,null,9]";
		auto root = codec.deserialize(ser);
		auto result = codec.serialize(root);
		cout << result << endl;
		assert(result == ser);
	}
	{
		//          1
		//        /  \
		//       /    \
		//     -1      2
		//     /
		//   -2
		Codec codec;
		string ser = "[1,-1,2,-2]";
		auto root = codec.deserialize(ser);
		auto result = codec.serialize(root);
		cout << result << endl;
		assert(result == ser);
	}

	return 0;
}
