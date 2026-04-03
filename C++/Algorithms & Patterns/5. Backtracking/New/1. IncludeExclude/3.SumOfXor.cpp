#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	The XOR total of an array is defined as the bitwise XOR of all its elements, or 0 if the array is empty.

	For example, the XOR total of the array [2,5,6] is 2 XOR 5 XOR 6 = 1.
	Given an array nums, return the sum of all XOR totals for every subset of nums. 

	Note: Subsets with the same elements should be counted multiple times.

	An array a is a subset of an array b if a can be obtained from b by deleting some (possibly zero) elements of b.



	Examples:
	---------
	Input: nums = [1,3]
	Output: 6
	Explanation: The 4 subsets of [1,3] are:
	- The empty subset has an XOR total of 0.
	- [1] has an XOR total of 1.
	- [3] has an XOR total of 3.
	- [1,3] has an XOR total of 1 XOR 3 = 2.
	0 + 1 + 3 + 2 = 6

	Input: nums = [5,1,6]
	Output: 28
	Explanation: The 8 subsets of [5,1,6] are:
	- The empty subset has an XOR total of 0.
	- [5] has an XOR total of 5.
	- [1] has an XOR total of 1.
	- [6] has an XOR total of 6.
	- [5,1] has an XOR total of 5 XOR 1 = 4.
	- [5,6] has an XOR total of 5 XOR 6 = 3.
	- [1,6] has an XOR total of 1 XOR 6 = 7.
	- [5,1,6] has an XOR total of 5 XOR 1 XOR 6 = 2.
	0 + 5 + 1 + 6 + 4 + 3 + 7 + 2 = 28

	Input: nums = [3,4,5,6,7,8]
	Output: 480
	Explanation: The sum of all XOR totals for every subset is 480.


	Approach:
	----------
	Include and exclude
*/

class Solution {
private:
	void solve(vector<int>& A, int currentXor, int &xorSum, int i) {
		if (i == A.size()) {
			xorSum = xorSum + currentXor;
			return;
		}

		//include
		solve(A, currentXor ^ A[i], xorSum, i + 1);

		//exclude
		solve(A, currentXor, xorSum, i + 1);
	}
public:
	int subsetXORSum(vector<int>& nums) {
		int currentXor = 0, xorSum = 0;
		solve(nums, currentXor, xorSum, 0);
		return xorSum;
	}
};

int main() {
	Solution obj;
	vector<int> A = {5, 1, 6};
	cout<<obj.subsetXORSum(A);
}