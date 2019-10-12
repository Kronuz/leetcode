/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o ./build/subarraysDivByK ./subarraysDivByK.cc && ./build/subarraysDivByK
*/
#include <iostream>

#include <string>
#include <vector>
#include <deque>
#include <unordered_set>
#include <unordered_map>

using namespace std;


/*
 * Let sum(i,j) be the sum of all elements in array from index i upto but not
 * including index j, where i < j.
 *
 * To solve this problem, let's first apply it into the prefix sum setting. We
 * know any subarray sum sum(i,j) can be formulated into difference between 2
 * prefix sum: sum(0,j) - sum(0,i).
 *
 * In order for a subarray sum to be divisible by K, we can setup an equation.
 *
 * sum(i,j) = n * K
 * sum(0,j) - sum(0,i) = n * K
 * sum(0,j) - n * K = sum(0,i)
 * (sum(0,j) - n * K) % K = sum(0,i) % K
 * sum(0,j) % K = sum(0,i) % K
 *
 * so, we can define sum(0,i) % K as variable mod and keep track it in the
 * prefix_sum dictionary. For each index j, we simply add count of sum(0,i) % K
 * to our result.
 *
 * Operation % return negative number if the left operand is negative.
 * To sort it out just do (x % K + K) % K.
 * This obviously does not affect positive rests but gives us K - |x| if x is
 * negative.
 */


class Solution {
public:
	int subarraysDivByK(vector<int>& A, int K) {
		int ans = 0;
		int nsum = 0;
		vector<int> prefix_sum(K, 0);
		prefix_sum[0] = 1;
		for (int n : A) {
			nsum += n;
			int mod = ((nsum % K) + K) % K;
			ans += prefix_sum[mod]++;
		}
		return ans;
	}
};


int main() {
	{
		Solution solution;
		vector<int> A = {4,5,0,-2,-3,1};
		int K = 5;
		auto result = solution.subarraysDivByK(A, K);
		assert(result == 7);
	}
	return 0;
}
