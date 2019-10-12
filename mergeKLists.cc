/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o ./build/mergeKLists ./mergeKLists.cc && ./build/mergeKLists
*/
#include <iostream>

#include <string>
#include <vector>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;


struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x, ListNode* n = nullptr) : val(x), next(n) {}
};


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		ListNode dummy(-1);
		ListNode* cur = &dummy;
		while (l1 && l2) {
			if (l1->val < l2->val) {
				cur->next = l1;
				l1 = l1->next;
			} else {
				cur->next = l2;
				l2 = l2->next;
			}
			cur = cur->next;
		}
		if (l1) cur->next = l1;
		if (l2) cur->next = l2;
		return dummy.next;
	}

public:
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		int n = lists.size();
		if (!n) return nullptr;
		while (n > 1) {
			int k = (n + 1) / 2;
			for (int i = 0; i < n / 2; ++i) {
				lists[i] = mergeTwoLists(lists[i], lists[i + k]);
			}
			n = k;
		}
		return lists[0];
	}
};

// class Solution {
// 	struct compareFn {
// 		bool operator() (ListNode *a, ListNode *b) {
// 			return a->val > b->val;
// 		}
// 	};
// public:
// 	ListNode* mergeKLists(vector<ListNode*>& lists) {
// 		priority_queue<ListNode*, vector<ListNode*>, compareFn> pq;
// 		for (auto l : lists) {
// 			if (l) {
// 				pq.push(l);
// 			}
// 		}
// 		ListNode* root = pq.empty() ? nullptr : pq.top();
// 		ListNode* prev = nullptr;
// 		while (!pq.empty()) {
// 			auto current = pq.top();
// 			pq.pop();
// 			if (current->next) pq.push(current->next);
// 			if (prev) prev->next = current;
// 			prev = current;
// 		}
// 		return root;
// 	}
// };


int main() {
	{
		Solution solution;

		vector<ListNode*> lists = {
			new ListNode(1, new ListNode(4, new ListNode(5))),
			new ListNode(1, new ListNode(3, new ListNode(4))),
			new ListNode(2, new ListNode(6)),
		};
		auto result = solution.mergeKLists(lists);
		while (result) {
			cout << result->val << " ";
			result = result->next;
		}
		cout << endl;
	}
	{
		Solution solution;

		vector<ListNode*> lists = {
			nullptr,
			new ListNode(-1, new ListNode(5, new ListNode(11))),
			nullptr,
			new ListNode(6, new ListNode(10)),
		};
		auto result = solution.mergeKLists(lists);
		while (result) {
			cout << result->val << " ";
			result = result->next;
		}
		cout << endl;
	}
	return 0;
}
