/*
c++ -std=c++17 -pedantic -Wall -Wextra -g -fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr,function -fno-sanitize-recover=all -O2 -I. -I./src -I../src -I.. -o sumSubseqWidths ./sumSubseqWidths.cc && ./sumSubseqWidths
*/
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Solution {
public:
	int sumSubseqWidths(vector<int>& A) {
		long long mod = 1000000007; // pow(10, 9) + 7;

		// [2,1,3,6,7,9,8]

		sort(A.begin(), A.end());
		// [1,2,3,6,7,8,9]

		// Num of subsequences is 2^n
		// Sort the array cost O(nlogn);
		// The number of subset that fixed A[i] as minimum element and A[j] as maximum element (i<j) is 2^{j-i}:

		// when j-i=1, we can get T{1} = (A[2]-A[1])*2^{0} + (A[3]-A[2])*2^{0} + ...+ (A[n]-A[n-1])*2^{0} = (A[n]-A[1])*2^{0}
		// when j-i=2, we can get T{2} = (A[3]-A[1])*2^{1} + (A[4]-A[2])*2^{1} + ...+ (A[n]-A[n-2])*2^{1} = (A[n]+A[n-1]-A[2]-A[1])*2^{1}
		// when j-i=3, we can get T{3} = (A[4]-A[1])*2^{2} + (A[5]-A[2])*2^{2} + ...+ (A[n]-A[n-3])*2^{2} = (A[n]+A[n-1]+A[n-2]-A[3]-A[2]-A[1])*2^{2}
		// when j-i=k, we can get T{k} = (sum[n-k+1][n] - sum[1][k])*2^{k-1}
		// Finally, ans=T{1}+T{2}+...+T{k}
		// In the code, lsum referred to sum[1][k], rsum referred to sum[n-k+1][n], and d referred to 2^{k-1}

		long long lsum = 0, rsum = 0, T = 0, ans = 0, d = 1;
		for (size_t l = 0, r = A.size() - 1; l < A.size(); ++l, --r) {
			// [1,2,3,6,7,8,9]     lsum=1   rsum=9   d=1   ans=0+(9-1)*2^0 = 0+8 = 8
			//   [2,3,6,7,8]       lsum=3   rsum=17  d=2   ans=8+(17-3)*2^1 = 8+28 = 36
			//     [3,6,7]         lsum=6   rsum=24  d=4   ans=36+(24-6)*2^2 = 36+72 = 108
			//       [6]           lsum=12  rsum=30  d=8   ans=108+(30-12)*2^3 = 108+144 = 252
			//     [7,6,3]         lsum=19  rsum=33  d=16  ans=252+(33-19)*2^4 = 252+224 = 476
			//   [8,7,6,3,2]       lsum=27  rsum=35  d=32  ans=476+(35-27)*2^5 = 476+256 = 732
			// [9,8,7,6,3,2,1]     lsum=36  rsum=36  d=64  ans=732+(36-36)*2^6 = 732+0 = 732
			lsum += A[l];
			rsum += A[r];
			T = (rsum - lsum) * d;
			ans = (ans + T) % mod;
			d = (d << 1) % mod;
		}
		return ans;
	}
};


int main() {
	{
		Solution solution;
		vector<int> A = {1,2,3};
		auto sum = solution.sumSubseqWidths(A);
		assert(sum == 6);
	}
	{
		Solution solution;
		vector<int> A = {1,2,3,6,7,8,9};
		auto sum = solution.sumSubseqWidths(A);
		assert(sum == 732);
	}
	return 0;
}
