/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o ./build/LRUCache ./LRUCache.cc && ./build/LRUCache
*/
#include <iostream>

#include <string>
#include <list>
#include <deque>
#include <unordered_map>

using namespace std;


class LRUCache {
	struct Item {
		int value;
		list<int>::iterator it;
	};

	size_t _capacity;
	list<int> _usage_list;  // keys
	unordered_map<int, Item> _map;  // key->item

public:
	LRUCache(int capacity) : _capacity(capacity) { }

	int get(int key) {
		const auto it = _map.find(key);
		if (it != _map.end()){
			_usage_list.splice(_usage_list.begin(), _usage_list, it->second.it);
			return it->second.value;
		}
		return -1;
	}

	void put(int key, int value) {
		const auto it = _map.find(key);
		if (it != _map.end()) {
			_usage_list.splice(_usage_list.begin(), _usage_list, it->second.it);
			it->second.value = value;
		} else {
			if (_map.size() >= _capacity) {
				_map.erase(_usage_list.back());
				_usage_list.pop_back();
			}
			_usage_list.push_front(key);
			_map[key] = {value, _usage_list.begin()};
		}
	}
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() {
	// ["LRUCache","put","put","get","put","get","put","get","get","get"]
	// [[2],[1,1],[2,2],[1],[3,3],[2],[4,4],[1],[3],[4]]
	{
		LRUCache lru(2);
		lru.put(1, 1);
		lru.put(2, 2);
		std::cout << lru.get(1) << std::endl;
		lru.put(3, 3);
		std::cout << lru.get(2) << std::endl;
		lru.put(4, 4);
		std::cout << lru.get(1) << std::endl;
		std::cout << lru.get(3) << std::endl;
		std::cout << lru.get(4) << std::endl;
	}
	return 0;
}
