/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o LFUCache ./LFUCache.cc && ./LFUCache
*/
#include <iostream>

#include <string>
#include <list>
#include <vector>
#include <deque>
#include <unordered_map>

using namespace std;


class LFUCache {
	size_t _size;
	vector<pair<int, int>> _vector;  // vector<pair<key, freq>>
	unordered_map<int, pair<int, size_t>> _map;  // unordered_map<key, pair<value, idx>>

	void heapify(size_t i) {
		size_t left = 2 * i + 1;
		size_t right = 2 * i + 2;
		size_t minim = i;
		if (left < _size && _vector[minim].second >= _vector[left].second) {
			minim = left;
		}
		if (right < _size && _vector[minim].second >= _vector[right].second) {
			minim = right;
		}
		if (minim != i) {
			_map[_vector[minim].first].second = i;
			_map[_vector[i].first].second = minim;
			swap(_vector[minim], _vector[i]);
			heapify(minim);
		}
	}

	void increment(size_t i) {
		++_vector[i].second;
		heapify(i);
	}

	void insert(int key, int value) {
		if (_size == _vector.size()) {
			_map.erase(_vector[0].first);
			_vector[0] = _vector[--_size];
			heapify(0);
		}
		_vector[_size++] = make_pair(key, 1);
		_map.insert(make_pair(key, make_pair(value, _size - 1)));
		size_t i = _size - 1;

		// Insert a node in the heap by swapping elements
		auto parent = (i - 1) / 2;
		while (i && _vector[parent].second > _vector[i].second) {
			_map[_vector[i].first].second = parent;
			_map[_vector[parent].first].second = i;
			swap(_vector[i], _vector[parent]);
			i = parent;
			parent = (i - 1) / 2;
		}
	}

public:
	LFUCache(int capacity) : _size(0), _vector(capacity) { }

	int get(int key) {
		auto it = _map.find(key);
		if (it != _map.end()) {
			increment(it->second.second);
			return it->second.first;
		}
		return -1;
	}

	void put(int key, int value) {
		if (!_vector.empty()) {
			auto it = _map.find(key);
			if (it != _map.end()) {
				increment(it->second.second);
				it->second.first = value;
			} else {
				insert(key, value);
			}
		}
	}
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */


int main() {
	{
		cout << "---" << endl;
		LFUCache cache(2);
		cache.put(1, 1);
		cache.put(2, 2);
		cout << cache.get(1) << endl;             // 1
		cache.put(3, 3);
		cout << cache.get(2) << endl;             // -1
		cout << cache.get(3) << endl;             // 3
		cache.put(4, 4);
		cout << cache.get(1) << endl;             // -1
		cout << cache.get(3) << endl;             // 3
		cout << cache.get(4) << endl;             // 4
	}
	{
		cout << "---" << endl;
		LFUCache cache(0);
		cache.put(0, 0);
		cout << cache.get(0) << endl;             // 0
	}
	{
		cout << "---" << endl;
		LFUCache cache(2);
		cache.put(3, 1);
		cache.put(2, 1);
		cache.put(2, 2);
		cache.put(4, 4);
		cout << cache.get(2) << endl;             // 2
	}

	if (0) {
		cout << "---" << endl;
		LFUCache cache(105);
		cache.put(33, 219);
		cout << cache.get(39) << endl;            // -1
		cache.put(96, 56);
		cout << cache.get(129) << endl;           // -1
		cout << cache.get(115) << endl;           // -1
		cout << cache.get(112) << endl;           // -1
		cache.put(3, 280);
		cout << cache.get(40) << endl;            // -1
		cache.put(85, 193);
		cache.put(10, 10);
		cache.put(100, 136);
		cache.put(12, 66);
		cache.put(81, 261);
		cache.put(33, 58);
		cout << cache.get(3) << endl;             // 280
		cache.put(121, 308);
		cache.put(129, 263);
		cout << cache.get(105) << endl;           // -1
		cache.put(104, 38);
		cache.put(65, 85);
		cache.put(3, 141);
		cache.put(29, 30);
		cache.put(80, 191);
		cache.put(52, 191);
		cache.put(8, 300);
		cout << cache.get(136) << endl;           // -1
		cache.put(48, 261);
		cache.put(3, 193);
		cache.put(133, 193);
		cache.put(60, 183);
		cache.put(128, 148);
		cache.put(52, 176);
		cout << cache.get(48) << endl;            // 261
		cache.put(48, 119);
		cache.put(10, 241);
		cout << cache.get(124) << endl;           // -1
		cache.put(130, 127);
		cout << cache.get(61) << endl;            // -1
		cache.put(124, 27);
		cout << cache.get(94) << endl;            // -1
		cache.put(29, 304);
		cache.put(102, 314);
		cout << cache.get(110) << endl;           // -1
		cache.put(23, 49);
		cache.put(134, 12);
		cache.put(55, 90);
		cout << cache.get(14) << endl;            // -1
		cout << cache.get(104) << endl;           // 38
		cache.put(77, 165);
		cache.put(60, 160);
		cout << cache.get(117) << endl;           // -1
		cache.put(58, 30);
		cout << cache.get(54) << endl;            // -1
		cout << cache.get(136) << endl;           // -1
		cout << cache.get(128) << endl;           // 148
		cout << cache.get(131) << endl;           // -1
		cache.put(48, 114);
		cout << cache.get(136) << endl;           // -1
		cache.put(46, 51);
		cache.put(129, 291);
		cache.put(96, 207);
		cout << cache.get(131) << endl;           // -1
		cache.put(89, 153);
		cache.put(120, 154);
		cout << cache.get(111) << endl;           // -1
		cout << cache.get(47) << endl;            // -1
		cout << cache.get(5) << endl;             // -1
		cache.put(114, 157);
		cache.put(57, 82);
		cache.put(113, 106);
		cache.put(74, 208);
		cout << cache.get(56) << endl;            // -1
		cout << cache.get(59) << endl;            // -1
		cout << cache.get(100) << endl;           // 136
		cout << cache.get(132) << endl;           // -1
		cache.put(127, 202);
		cout << cache.get(75) << endl;            // -1
		cache.put(102, 147);
		cout << cache.get(37) << endl;            // -1
		cache.put(53, 79);
		cache.put(119, 220);
		cout << cache.get(47) << endl;            // -1
		cout << cache.get(101) << endl;           // -1
		cout << cache.get(89) << endl;            // 153
		cout << cache.get(20) << endl;            // -1
		cout << cache.get(93) << endl;            // -1
		cout << cache.get(7) << endl;             // -1
		cache.put(48, 109);
		cache.put(71, 146);
		cout << cache.get(43) << endl;            // -1
		cout << cache.get(122) << endl;           // -1
		cache.put(3, 160);
		cout << cache.get(17) << endl;            // -1
		cache.put(80, 22);
		cache.put(80, 272);
		cout << cache.get(75) << endl;            // -1
		cout << cache.get(117) << endl;           // -1
		cache.put(76, 204);
		cache.put(74, 141);
		cache.put(107, 93);
		cache.put(34, 280);
		cache.put(31, 94);
		cout << cache.get(132) << endl;           // -1
		cache.put(71, 258);
		cout << cache.get(61) << endl;            // -1
		cout << cache.get(60) << endl;            // 160
		cache.put(69, 272);
		cout << cache.get(46) << endl;            // 51
		cache.put(42, 264);
		cache.put(87, 126);
		cache.put(107, 236);
		cache.put(131, 218);
		cout << cache.get(79) << endl;            // -1
		cache.put(41, 71);
		cache.put(94, 111);
		cache.put(19, 124);
		cache.put(52, 70);
		cout << cache.get(131) << endl;           // 218
		cout << cache.get(103) << endl;           // -1
		cout << cache.get(81) << endl;            // 261
		cout << cache.get(126) << endl;           // -1
		cache.put(61, 279);
		cache.put(37, 100);
		cout << cache.get(95) << endl;            // -1
		cout << cache.get(54) << endl;            // -1
		cache.put(59, 136);
		cache.put(101, 219);
		cache.put(15, 248);
		cache.put(37, 91);
		cache.put(11, 174);
		cache.put(99, 65);
		cache.put(105, 249);
		cout << cache.get(85) << endl;            // 193
		cache.put(108, 287);
		cache.put(96, 4);
		cout << cache.get(70) << endl;            // -1
		cout << cache.get(24) << endl;            // -1
		cache.put(52, 206);
		cache.put(59, 306);
		cache.put(18, 296);
		cache.put(79, 95);
		cache.put(50, 131);
		cache.put(3, 161);
		cache.put(2, 229);
		cache.put(39, 183);
		cache.put(90, 225);
		cache.put(75, 23);
		cache.put(136, 280);
		cout << cache.get(119) << endl;           // 220
		cache.put(81, 272);
		cout << cache.get(106) << endl;           // -1
		cout << cache.get(106) << endl;           // -1
		cout << cache.get(70) << endl;            // -1
		cache.put(73, 60);
		cache.put(19, 250);
		cache.put(82, 291);
		cache.put(117, 53);
		cache.put(16, 176);
		cout << cache.get(40) << endl;            // -1
		cache.put(7, 70);
		cache.put(135, 212);
		cout << cache.get(59) << endl;            // 306
		cache.put(81, 201);
		cache.put(75, 305);
		cout << cache.get(101) << endl;           // 219
		cache.put(8, 250);
		cout << cache.get(38) << endl;            // -1
		cache.put(28, 220);
		cout << cache.get(21) << endl;            // -1
		cache.put(105, 266);
		cout << cache.get(105) << endl;           // 266
		cout << cache.get(85) << endl;            // 193
		cout << cache.get(55) << endl;            // 90
		cout << cache.get(6) << endl;             // -1
		cache.put(78, 83);
		cout << cache.get(126) << endl;           // -1
		cout << cache.get(102) << endl;           // 147
		cout << cache.get(66) << endl;            // -1
		cache.put(61, 42);
		cache.put(127, 35);
		cache.put(117, 105);
		cout << cache.get(128) << endl;           // 148
		cout << cache.get(102) << endl;           // 147
		cout << cache.get(50) << endl;            // 131
		cache.put(24, 133);
		cache.put(40, 178);
		cache.put(78, 157);
		cache.put(71, 22);
		cout << cache.get(25) << endl;            // -1
		cout << cache.get(82) << endl;            // 291
		cout << cache.get(129) << endl;           // 291
		cache.put(126, 12);
		cout << cache.get(45) << endl;            // -1
		cout << cache.get(40) << endl;            // 178
		cout << cache.get(86) << endl;            // -1
		cout << cache.get(100) << endl;           // 136
		cache.put(30, 110);
		cout << cache.get(49) << endl;            // -1
		cache.put(47, 185);
		cache.put(123, 101);
		cout << cache.get(102) << endl;           // 147
		cout << cache.get(5) << endl;             // -1
		cache.put(40, 267);
		cache.put(48, 155);
		cout << cache.get(108) << endl;           // 287
		cout << cache.get(45) << endl;            // -1
		cache.put(14, 182);
		cache.put(20, 117);
		cache.put(43, 124);
		cout << cache.get(38) << endl;            // -1
		cache.put(77, 158);
		cout << cache.get(111) << endl;           // -1
		cout << cache.get(39) << endl;            // 183
		cache.put(69, 126);
		cache.put(113, 199);
		cache.put(21, 216);
		cout << cache.get(11) << endl;            // 174
		cache.put(117, 207);
		cout << cache.get(30) << endl;            // 110
		cache.put(97, 84);
		cout << cache.get(109) << endl;           // -1
		cache.put(99, 218);
		cout << cache.get(109) << endl;           // -1
		cache.put(113, 1);
		cout << cache.get(62) << endl;            // -1
		cache.put(49, 89);
		cache.put(53, 311);
		cout << cache.get(126) << endl;           // 12
		cache.put(32, 153);
		cache.put(14, 296);
		cout << cache.get(22) << endl;            // -1
		cache.put(14, 225);
		cout << cache.get(49) << endl;            // 89
		cout << cache.get(75) << endl;            // 305
		cache.put(61, 241);
		cout << cache.get(7) << endl;             // 70
		cout << cache.get(6) << endl;             // -1
		cout << cache.get(31) << endl;            // 94
		cache.put(75, 15);
		cout << cache.get(115) << endl;           // -1
		cache.put(84, 181);
		cache.put(125, 111);
		cache.put(105, 94);
		cache.put(48, 294);
		cout << cache.get(106) << endl;           // -1
		cout << cache.get(61) << endl;            // 241
		cache.put(53, 190);
		cout << cache.get(16) << endl;            // 176
		cache.put(12, 252);
		cout << cache.get(28) << endl;            // 220
		cache.put(111, 122);
		cout << cache.get(122) << endl;           // -1
		cache.put(10, 21);
		cout << cache.get(59) << endl;            // 306
		cout << cache.get(72) << endl;            // -1
		cout << cache.get(39) << endl;            // 183
		cout << cache.get(6) << endl;             // -1
		cout << cache.get(126) << endl;           // 12
		cache.put(131, 177);
		cache.put(105, 253);
		cout << cache.get(26) << endl;            // -1
		cache.put(43, 311);
		cout << cache.get(79) << endl;            // 95
		cache.put(91, 32);
		cache.put(7, 141);
		cout << cache.get(38) << endl;            // -1
		cout << cache.get(13) << endl;            // -1
		cache.put(79, 135);
		cout << cache.get(43) << endl;            // 311
		cout << cache.get(94) << endl;            // 111
		cache.put(80, 182);
		cout << cache.get(53) << endl;            // 190
		cache.put(120, 309);
		cache.put(3, 109);
		cout << cache.get(97) << endl;            // 84
		cache.put(9, 128);
		cache.put(114, 121);
		cout << cache.get(56) << endl;            // -1
		cout << cache.get(56) << endl;            // -1
		cache.put(124, 86);
		cache.put(34, 145);
		cout << cache.get(131) << endl;           // 177
		cout << cache.get(78) << endl;            // 157
		cache.put(86, 21);
		cout << cache.get(98) << endl;            // -1
		cache.put(115, 164);
		cache.put(47, 225);
		cout << cache.get(95) << endl;            // -1
		cache.put(89, 55);
		cache.put(26, 134);
		cache.put(8, 15);
		cout << cache.get(11) << endl;            // 174
		cache.put(84, 276);
		cache.put(81, 67);
		cout << cache.get(46) << endl;            // 51
		cout << cache.get(39) << endl;            // 183
		cout << cache.get(92) << endl;            // -1
		cout << cache.get(96) << endl;            // 4
		cache.put(89, 51);
		cache.put(136, 240);
		cout << cache.get(45) << endl;            // -1
		cout << cache.get(27) << endl;            // -1
		cache.put(24, 209);
		cache.put(82, 145);
		cout << cache.get(10) << endl;            // 21
		cache.put(104, 225);
		cache.put(120, 203);
		cache.put(121, 108);
		cache.put(11, 47);
		cout << cache.get(89) << endl;            // 51
		cache.put(80, 66);
		cout << cache.get(16) << endl;            // 176
		cache.put(95, 101);
		cout << cache.get(49) << endl;            // 89
		cout << cache.get(1) << endl;             // -1
		cache.put(77, 184);
		cout << cache.get(27) << endl;            // -1
		cache.put(74, 313);
		cache.put(14, 118);
		cout << cache.get(16) << endl;            // 176
		cout << cache.get(74) << endl;            // 313
		cache.put(88, 251);
		cout << cache.get(124) << endl;           // 86
		cache.put(58, 101);
		cache.put(42, 81);
		cout << cache.get(2) << endl;             // 229
		cache.put(133, 101);
		cout << cache.get(16) << endl;            // 176
		cache.put(1, 254);
		cache.put(25, 167);
		cache.put(53, 56);
		cache.put(73, 198);
		cout << cache.get(48) << endl;            // 294
		cout << cache.get(30) << endl;            // 110
		cout << cache.get(95) << endl;            // 101
		cache.put(90, 102);
		cache.put(92, 56);
		cache.put(2, 130);
		cache.put(52, 11);
		cout << cache.get(9) << endl;             // 128
		cout << cache.get(23) << endl;            // 49
		cache.put(53, 275);
		cache.put(23, 258);
		cout << cache.get(57) << endl;            // 82
		cache.put(136, 183);
		cache.put(75, 265);
		cout << cache.get(85) << endl;            // 193
		cache.put(68, 274);
		cache.put(15, 255);
		cout << cache.get(85) << endl;            // 193
		cache.put(33, 314);
		cache.put(101, 223);
		cache.put(39, 248);
		cache.put(18, 261);
		cache.put(37, 160);
		cout << cache.get(112) << endl;           // -1
		cout << cache.get(65) << endl;            // 85
		cache.put(31, 240);
		cache.put(40, 295);
		cache.put(99, 231);
		cout << cache.get(123) << endl;           // 101
		cache.put(34, 43);
		cout << cache.get(87) << endl;            // 126
		cout << cache.get(80) << endl;            // 66
		cache.put(47, 279);
		cache.put(89, 299);
		cout << cache.get(72) << endl;            // -1
		cache.put(26, 277);
		cache.put(92, 13);
		cache.put(46, 92);
		cache.put(67, 163);
		cache.put(85, 184);
		cout << cache.get(38) << endl;            // -1
		cache.put(35, 65);
		cout << cache.get(70) << endl;            // -1
		cout << cache.get(81) << endl;            // 67
		cache.put(40, 65);
		cout << cache.get(80) << endl;            // 66
		cache.put(80, 23);
		cache.put(76, 258);
		cout << cache.get(69) << endl;            // 126
		cout << cache.get(133) << endl;           // 101
		cache.put(123, 196);
		cache.put(119, 212);
		cache.put(13, 150);
		cache.put(22, 52);
		cache.put(20, 105);
		cache.put(61, 233);
		cout << cache.get(97) << endl;            // 84
		cache.put(128, 307);
		cout << cache.get(85) << endl;            // 184
		cout << cache.get(80) << endl;            // 23
		cout << cache.get(73) << endl;            // 198
		cout << cache.get(30) << endl;            // 110
		cache.put(46, 44);
		cout << cache.get(95) << endl;            // 101
		cache.put(121, 211);
		cache.put(48, 307);
		cout << cache.get(2) << endl;             // 130
		cache.put(27, 166);
		cout << cache.get(50) << endl;            // 131
		cache.put(75, 41);
		cache.put(101, 105);
		cout << cache.get(2) << endl;             // 130
		cache.put(110, 121);
		cache.put(32, 88);
		cache.put(75, 84);
		cache.put(30, 165);
		cache.put(41, 142);
		cache.put(128, 102);
		cache.put(105, 90);
		cache.put(86, 68);
		cache.put(13, 292);
		cache.put(83, 63);
		cache.put(5, 239);
		cout << cache.get(5) << endl;             // 239
		cache.put(68, 204);
		cout << cache.get(127) << endl;           // 35
		cache.put(42, 137);
		cout << cache.get(93) << endl;            // -1
		cache.put(90, 258);
		cache.put(40, 275);
		cache.put(7, 96);
		cout << cache.get(108) << endl;           // 287
		cache.put(104, 91);
		cout << cache.get(63) << endl;            // -1
		cout << cache.get(31) << endl;            // 240
		cache.put(31, 89);
		cout << cache.get(74) << endl;            // 313
		cout << cache.get(81) << endl;            // 67
		cache.put(126, 148);
		cout << cache.get(107) << endl;           // 236
		cache.put(13, 28);
		cache.put(21, 139);
		cout << cache.get(114) << endl;           // 121
		cout << cache.get(5) << endl;             // 239
		cout << cache.get(89) << endl;            // 299
		cout << cache.get(133) << endl;           // 101
		cout << cache.get(20) << endl;            // 105
		cache.put(96, 135);
		cache.put(86, 100);
		cache.put(83, 75);
		cout << cache.get(14) << endl;            // 118
		cache.put(26, 195);
		cout << cache.get(37) << endl;            // 160
		cache.put(1, 287);
		cout << cache.get(79) << endl;            // 135
		cout << cache.get(15) << endl;            // 255
		cout << cache.get(6) << endl;             // -1
		cache.put(68, 11);
		cout << cache.get(52) << endl;            // 11
		cache.put(124, 80);
		cache.put(123, 277);
		cache.put(99, 281);
		cout << cache.get(133) << endl;           // 101
		cout << cache.get(90) << endl;            // 258
		cout << cache.get(45) << endl;            // -1
		cout << cache.get(127) << endl;           // 35
		cache.put(9, 68);
		cache.put(123, 6);
		cache.put(124, 251);
		cache.put(130, 191);
		cache.put(23, 174);
		cache.put(69, 295);
		cout << cache.get(32) << endl;            // 88
		cout << cache.get(37) << endl;            // 160
		cache.put(1, 64);
		cache.put(48, 116);
		cout << cache.get(68) << endl;            // 11
		cache.put(117, 173);
		cache.put(16, 89);
		cout << cache.get(84) << endl;            // 276
		cache.put(28, 234);
		cout << cache.get(129) << endl;           // 291
		cout << cache.get(89) << endl;            // 299
		cout << cache.get(55) << endl;            // 90
		cout << cache.get(83) << endl;            // 75
		cache.put(99, 264);
		cout << cache.get(129) << endl;           // 291
		cout << cache.get(84) << endl;            // 276
		cout << cache.get(14) << endl;            // 118
		cache.put(26, 274);
		cout << cache.get(109) << endl;           // -1
		cout << cache.get(110) << endl;           // 121
		cache.put(96, 120);
		cache.put(128, 207);
		cout << cache.get(12) << endl;            // 252
		cache.put(99, 233);
		cache.put(20, 305);
		cache.put(26, 24);
		cache.put(102, 32);
		cout << cache.get(82) << endl;            // 145
		cache.put(16, 30);
		cache.put(5, 244);
		cout << cache.get(130) << endl;           // 191
		cache.put(109, 36);
		cache.put(134, 162);
		cache.put(13, 165);
		cache.put(45, 235);
		cache.put(112, 80);
		cout << cache.get(6) << endl;             // -1
		cache.put(34, 98);
		cache.put(64, 250);
		cache.put(18, 237);
		cache.put(72, 21);
		cache.put(42, 105);
		cache.put(57, 108);
		cache.put(28, 229);
		cout << cache.get(83) << endl;            // 75
		cache.put(1, 34);
		cache.put(93, 151);
		cache.put(132, 94);
		cache.put(18, 24);
		cache.put(57, 68);
		cache.put(42, 137);
		cout << cache.get(35) << endl;            // -1
		cout << cache.get(80) << endl;            // 23
		cache.put(10, 288);
		cout << cache.get(21) << endl;            // 139
		cout << cache.get(115) << endl;           // 164    *** should be -1 ?
		cout << cache.get(131) << endl;           // 177
		cout << cache.get(30) << endl;            // 165
		cout << cache.get(43) << endl;            // 311
		cache.put(97, 262);
		cache.put(55, 146);
		cache.put(81, 112);
		cache.put(2, 212);
		cache.put(5, 312);
		cache.put(82, 107);
		cache.put(14, 151);
		cout << cache.get(77) << endl;            // 184
		cache.put(60, 42);
		cache.put(90, 309);
		cout << cache.get(90) << endl;            // 309
		cache.put(131, 220);
		cout << cache.get(86) << endl;            // 100
		cache.put(106, 85);
		cache.put(85, 254);
		cout << cache.get(14) << endl;            // 151
		cache.put(66, 262);
		cache.put(88, 243);
		cout << cache.get(3) << endl;             // 109
		cache.put(50, 301);
		cache.put(118, 91);
		cout << cache.get(25) << endl;            // -1
		cout << cache.get(105) << endl;           // 90
		cout << cache.get(100) << endl;           // 136
		cout << cache.get(89) << endl;            // 299
		cache.put(111, 152);
		cache.put(65, 24);
		cache.put(41, 264);
		cout << cache.get(117) << endl;           // 173
		cout << cache.get(117) << endl;           // 173
		cache.put(80, 45);
		cout << cache.get(38) << endl;            // -1
		cache.put(11, 151);
		cache.put(126, 203);
		cache.put(128, 59);
		cache.put(6, 129);
		cout << cache.get(91) << endl;            // 32     *** should be -1 ?
		cache.put(118, 2);
		cache.put(50, 164);
		cout << cache.get(74) << endl;            // 313
		cout << cache.get(80) << endl;            // 45
		cache.put(48, 308);
		cache.put(109, 82);
		cache.put(3, 48);
		cache.put(123, 10);
		cache.put(59, 249);
		cache.put(128, 64);
		cache.put(41, 287);
		cache.put(52, 278);
		cache.put(98, 151);
		cout << cache.get(12) << endl;            // 252
		cout << cache.get(25) << endl;            // -1
		cache.put(18, 254);
		cache.put(24, 40);
		cout << cache.get(119) << endl;           // 212
		cache.put(66, 44);
		cache.put(61, 19);
		cache.put(80, 132);
		cache.put(62, 111);
		cout << cache.get(80) << endl;            // 132
		cache.put(57, 188);
		cout << cache.get(132) << endl;           // -1
		cout << cache.get(42) << endl;            // 137
		cache.put(18, 314);
		cout << cache.get(48) << endl;            // 308
		cache.put(86, 138);
		cout << cache.get(8) << endl;             // 15
		cache.put(27, 88);
		cache.put(96, 178);
		cache.put(17, 104);
		cache.put(112, 86);
		cout << cache.get(25) << endl;            // -1
		cache.put(129, 119);
		cache.put(93, 44);
		cout << cache.get(115) << endl;           // 164    *** should be -1 ?
		cache.put(33, 36);
		cache.put(85, 190);
		cout << cache.get(10) << endl;            // 288
		cache.put(52, 182);
		cache.put(76, 182);
		cout << cache.get(109) << endl;           // -1
		cout << cache.get(118) << endl;           // 2
		cache.put(82, 301);
		cache.put(26, 158);
		cout << cache.get(71) << endl;            // 22
		cache.put(108, 309);
		cache.put(58, 132);
		cache.put(13, 299);
		cache.put(117, 183);
		cout << cache.get(115) << endl;           // 164    *** should be -1 ?
		cout << cache.get(89) << endl;            // 299
		cout << cache.get(42) << endl;            // 137
		cache.put(11, 285);
		cache.put(30, 144);
		cout << cache.get(69) << endl;            // 295
		cache.put(31, 53);
		cout << cache.get(21) << endl;            // 139
		cache.put(96, 162);
		cache.put(4, 227);
		cache.put(77, 120);
		cache.put(128, 136);
		cout << cache.get(92) << endl;            // 13
		cache.put(119, 208);
		cache.put(87, 61);
		cache.put(9, 40);
		cache.put(48, 273);
		cout << cache.get(95) << endl;            // 101
		cout << cache.get(35) << endl;            // -1
		cache.put(62, 267);
		cache.put(88, 161);
		cout << cache.get(59) << endl;            // 249
		cout << cache.get(85) << endl;            // 190
		cache.put(131, 53);
		cache.put(114, 98);
		cache.put(90, 257);
		cache.put(108, 46);
		cout << cache.get(54) << endl;            // -1
		cache.put(128, 223);
		cache.put(114, 168);
		cache.put(89, 203);
		cout << cache.get(100) << endl;           // 136
		cout << cache.get(116) << endl;           // -1
		cout << cache.get(14) << endl;            // 151
		cache.put(61, 104);
		cache.put(44, 161);
		cache.put(60, 132);
		cache.put(21, 310);
		cout << cache.get(89) << endl;            // 203
		cache.put(109, 237);
		cout << cache.get(105) << endl;           // 90
		cout << cache.get(32) << endl;            // 88
		cache.put(78, 101);
		cache.put(14, 71);
		cache.put(100, 47);
		cache.put(102, 33);
		cache.put(44, 29);
		cout << cache.get(85) << endl;            // 190
		cout << cache.get(37) << endl;            // 160
		cache.put(68, 175);
		cache.put(116, 182);
		cache.put(42, 47);
		cout << cache.get(9) << endl;             // 40
		cache.put(64, 37);
		cache.put(23, 32);
		cache.put(11, 124);
		cache.put(130, 189);
		cout << cache.get(65) << endl;            // 24
		cache.put(33, 219);
		cache.put(79, 253);
		cout << cache.get(80) << endl;            // 132
		cout << cache.get(16) << endl;            // 30
		cache.put(38, 18);
		cache.put(35, 67);
		cout << cache.get(107) << endl;           // 236
		cout << cache.get(88) << endl;            // -1
		cache.put(37, 13);
		cache.put(71, 188);
		cout << cache.get(35) << endl;            // 67
		cache.put(58, 268);
		cache.put(18, 260);
		cache.put(73, 23);
		cache.put(28, 102);
		cout << cache.get(129) << endl;           // 119
		cout << cache.get(88) << endl;            // -1
		cout << cache.get(65) << endl;            // 24
		cout << cache.get(80) << endl;            // 132
		cache.put(119, 146);
		cout << cache.get(113) << endl;           // 1
		cout << cache.get(62) << endl;            // -1
		cache.put(123, 138);
		cache.put(18, 1);
		cache.put(26, 208);
		cout << cache.get(107) << endl;           // 236
		cout << cache.get(107) << endl;           // 236
		cache.put(76, 132);
		cache.put(121, 191);
		cout << cache.get(4) << endl;             // -1
		cout << cache.get(8) << endl;             // 15
		cout << cache.get(117) << endl;           // 183
		cache.put(11, 118);
		cout << cache.get(43) << endl;            // 311
		cout << cache.get(69) << endl;            // 295
		cout << cache.get(136) << endl;           // 183
		cache.put(66, 298);
		cout << cache.get(25) << endl;            // -1
		cout << cache.get(71) << endl;            // 188
		cout << cache.get(100) << endl;           // 47
		cache.put(26, 141);
		cache.put(53, 256);
		cache.put(111, 205);
		cache.put(126, 106);
		cout << cache.get(43) << endl;            // 311
		cache.put(14, 39);
		cache.put(44, 41);
		cache.put(23, 230);
		cout << cache.get(131) << endl;           // 53
		cout << cache.get(53) << endl;            // 256
		cache.put(104, 268);
		cout << cache.get(30) << endl;            // 144
		cache.put(108, 48);
		cache.put(72, 45);
		cout << cache.get(58) << endl;            // 268
		cout << cache.get(46) << endl;            // 44
		cache.put(128, 301);
		cout << cache.get(71) << endl;            // 188
		cout << cache.get(99) << endl;            // 233
		cout << cache.get(113) << endl;           // 1
		cout << cache.get(121) << endl;           // 191
		cache.put(130, 122);
		cache.put(102, 5);
		cache.put(111, 51);
		cache.put(85, 229);
		cache.put(86, 157);
		cache.put(82, 283);
		cache.put(88, 52);
		cache.put(136, 105);
		cout << cache.get(40) << endl;            // 275
		cout << cache.get(63) << endl;            // -1
		cache.put(114, 244);
		cache.put(29, 82);
		cache.put(83, 278);
		cout << cache.get(131) << endl;           // 53
		cache.put(56, 33);
		cout << cache.get(123) << endl;           // 138
		cout << cache.get(11) << endl;            // 118
		cout << cache.get(119) << endl;           // 146
		cache.put(119, 1);
		cache.put(48, 52);
		cout << cache.get(47) << endl;            // 279
		cache.put(127, 136);
		cache.put(78, 38);
		cache.put(117, 64);
		cache.put(130, 134);
		cache.put(93, 69);
		cache.put(70, 98);
		cout << cache.get(68) << endl;            // 175
		cache.put(4, 3);
		cache.put(92, 173);
		cache.put(114, 65);
		cache.put(7, 309);
		cout << cache.get(31) << endl;            // 53
		cache.put(107, 271);
		cache.put(110, 69);
		cout << cache.get(45) << endl;            // -1
		cache.put(35, 288);
		cout << cache.get(20) << endl;            // 305
		cache.put(38, 79);
		cout << cache.get(46) << endl;            // 44
		cache.put(6, 123);
		cout << cache.get(19) << endl;            // 250
		cache.put(84, 95);
		cout << cache.get(76) << endl;            // 132
		cache.put(71, 31);
		cache.put(72, 171);
		cache.put(35, 123);
		cout << cache.get(32) << endl;            // 88
		cache.put(73, 85);
		cout << cache.get(94) << endl;            // 111
		cout << cache.get(128) << endl;           // 301
		cout << cache.get(28) << endl;            // 102
		cout << cache.get(38) << endl;            // -1
		cout << cache.get(109) << endl;           // -1
		cache.put(85, 197);
		cache.put(10, 41);
		cache.put(71, 50);
		cout << cache.get(128) << endl;           // 301
		cache.put(3, 55);
		cache.put(15, 9);
		cache.put(127, 215);
		cout << cache.get(17) << endl;            // -1
		cout << cache.get(37) << endl;            // 13
		cache.put(111, 272);
		cache.put(79, 169);
		cache.put(86, 206);
		cache.put(40, 264);
		cout << cache.get(134) << endl;           // -1
		cache.put(16, 207);
		cache.put(27, 127);
		cache.put(29, 48);
		cache.put(32, 122);
		cache.put(15, 35);
		cache.put(117, 36);
		cout << cache.get(127) << endl;           // 215
		cout << cache.get(36) << endl;            // -1
		cache.put(72, 70);
		cache.put(49, 201);
		cache.put(89, 215);
		cache.put(134, 290);
		cache.put(77, 64);
		cache.put(26, 101);
		cout << cache.get(99) << endl;            // 233
		cache.put(36, 96);
		cache.put(84, 129);
		cache.put(125, 264);
		cout << cache.get(43) << endl;            // 311
		cout << cache.get(38) << endl;            // -1
		cache.put(24, 76);
		cache.put(45, 2);
		cache.put(32, 24);
		cache.put(84, 235);
		cache.put(16, 240);
		cache.put(17, 289);
		cache.put(49, 94);
		cache.put(90, 54);
		cache.put(88, 199);
		cout << cache.get(23) << endl;            // 230
		cache.put(87, 19);
		cache.put(11, 19);
		cout << cache.get(24) << endl;            // 76
		cout << cache.get(57) << endl;            // 188
		cout << cache.get(4) << endl;             // -1
		cout << cache.get(40) << endl;            // 264
		cache.put(133, 286);
		cache.put(127, 231);
		cout << cache.get(51) << endl;            // -1
		cache.put(52, 196);
		cout << cache.get(27) << endl;            // -1
		cout << cache.get(10) << endl;            // 41
		cout << cache.get(93) << endl;            // -1
		cache.put(115, 143);
		cache.put(62, 64);
		cache.put(59, 200);
		cache.put(75, 85);
		cache.put(7, 93);
		cache.put(117, 270);
		cache.put(116, 6);
		cout << cache.get(32) << endl;            // 24
		cout << cache.get(135) << endl;           // -1
		cache.put(2, 140);
		cache.put(23, 1);
		cache.put(11, 69);
		cache.put(89, 30);
		cache.put(27, 14);
		cout << cache.get(100) << endl;           // 47
		cout << cache.get(61) << endl;            // 104
		cache.put(99, 41);
		cache.put(88, 12);
		cout << cache.get(41) << endl;            // 287
		cache.put(52, 203);
		cout << cache.get(65) << endl;            // 24
		cache.put(62, 78);
		cache.put(104, 276);
		cache.put(105, 307);
		cout << cache.get(7) << endl;             // 93
		cache.put(23, 123);
		cout << cache.get(22) << endl;            // -1
		cache.put(35, 299);
		cout << cache.get(69) << endl;            // 295
		cout << cache.get(11) << endl;            // 69
		cache.put(14, 112);
		cout << cache.get(115) << endl;           // 143    *** should be -1 ?
		cout << cache.get(112) << endl;           // -1
		cout << cache.get(108) << endl;           // 48
		cache.put(110, 165);
		cache.put(83, 165);
		cache.put(36, 260);
		cache.put(54, 73);
		cout << cache.get(36) << endl;            // -1
		cache.put(93, 69);
		cout << cache.get(134) << endl;           // -1
		cache.put(125, 96);
		cache.put(74, 127);
		cache.put(110, 305);
		cache.put(92, 309);
		cache.put(87, 45);
		cache.put(31, 266);
		cout << cache.get(10) << endl;            // 41
		cache.put(114, 206);
		cache.put(49, 141);
		cout << cache.get(82) << endl;            // 283
		cache.put(92, 3);
		cache.put(91, 160);
		cout << cache.get(41) << endl;            // 287
		cache.put(60, 147);
		cache.put(36, 239);
		cache.put(23, 296);
		cache.put(134, 120);
		cout << cache.get(6) << endl;             // -1
		cache.put(5, 283);
		cache.put(117, 68);
		cout << cache.get(35) << endl;            // 299
		cout << cache.get(120) << endl;           // 203
		cache.put(44, 191);
		cache.put(121, 14);
		cache.put(118, 113);
		cache.put(84, 106);
		cout << cache.get(23) << endl;            // 296
		cache.put(15, 240);
		cout << cache.get(37) << endl;            // 13
		cache.put(52, 256);
		cache.put(119, 116);
		cache.put(101, 7);
		cache.put(14, 157);
		cache.put(29, 225);
		cache.put(4, 247);
		cache.put(8, 112);
		cache.put(8, 189);
		cache.put(96, 220);
		cout << cache.get(104) << endl;           // 276
		cache.put(72, 106);
		cache.put(23, 170);
		cache.put(67, 209);
		cache.put(70, 39);
		cout << cache.get(18) << endl;            // 1
		cout << cache.get(6) << endl;             // -1
		cout << cache.get(34) << endl;            // 98
		cache.put(121, 157);
		cout << cache.get(16) << endl;            // 240
		cout << cache.get(19) << endl;            // 250
		cache.put(83, 283);
		cache.put(13, 22);
		cache.put(33, 143);
		cache.put(88, 133);
		cout << cache.get(88) << endl;            // 133
		cache.put(5, 49);
		cout << cache.get(38) << endl;            // -1
		cout << cache.get(110) << endl;           // 305
		cout << cache.get(67) << endl;            // -1
		cache.put(23, 227);
		cout << cache.get(68) << endl;            // 175
		cout << cache.get(3) << endl;             // 55
		cache.put(27, 265);
		cout << cache.get(31) << endl;            // 266
		cache.put(13, 103);
		cout << cache.get(116) << endl;           // -1
		cache.put(111, 282);
		cache.put(43, 71);
		cout << cache.get(134) << endl;           // -1
		cache.put(70, 141);
		cout << cache.get(14) << endl;            // 157
		cout << cache.get(119) << endl;           // 116
		cout << cache.get(43) << endl;            // 71
		cout << cache.get(122) << endl;           // -1
		cache.put(38, 187);
		cache.put(8, 9);
		cout << cache.get(63) << endl;            // -1
		cache.put(42, 140);
		cout << cache.get(83) << endl;            // 283
		cout << cache.get(92) << endl;            // 3
		cout << cache.get(106) << endl;           // -1
		cout << cache.get(28) << endl;            // 102
		cache.put(57, 139);
		cache.put(36, 257);
		cache.put(30, 204);
		cout << cache.get(72) << endl;            // -1     *** should be 106 ?
		cache.put(105, 243);
		cout << cache.get(16) << endl;            // 240
		cache.put(74, 25);
		cout << cache.get(22) << endl;            // -1
		cache.put(118, 144);
		cout << cache.get(133) << endl;           // 286
		cout << cache.get(71) << endl;            // 50
		cache.put(99, 21);
		cout << cache.get(26) << endl;            // 101
		cout << cache.get(35) << endl;            // 299
		cache.put(89, 209);
		cache.put(106, 158);
		cache.put(76, 63);
		cache.put(112, 216);
		cout << cache.get(128) << endl;           // 301
		cout << cache.get(54) << endl;            // -1
		cache.put(16, 165);
		cache.put(76, 206);
		cache.put(69, 253);
		cout << cache.get(23) << endl;            // 227
		cache.put(54, 111);
		cout << cache.get(80) << endl;            // 132
		cache.put(111, 72);
		cache.put(95, 217);
		cout << cache.get(118) << endl;           // 144
		cache.put(4, 146);
		cout << cache.get(47) << endl;            // 279
		cache.put(108, 290);
		cout << cache.get(43) << endl;            // 71
		cache.put(70, 8);
		cout << cache.get(117) << endl;           // 68
		cout << cache.get(121) << endl;           // 157
		cache.put(42, 220);
		cout << cache.get(48) << endl;            // 52
		cout << cache.get(32) << endl;            // 24
		cache.put(68, 213);
		cache.put(30, 157);
		cache.put(62, 68);
		cout << cache.get(58) << endl;            // 268
		cache.put(125, 283);
		cache.put(132, 45);
		cout << cache.get(85) << endl;            // 197
		cout << cache.get(92) << endl;            // 3
		cache.put(23, 257);
		cout << cache.get(74) << endl;            // 25
		cache.put(18, 256);
		cout << cache.get(90) << endl;            // 54
		cache.put(10, 158);
		cache.put(57, 34);
		cout << cache.get(27) << endl;            // -1
		cout << cache.get(107) << endl;           // 271
	}

	return 0;
}
