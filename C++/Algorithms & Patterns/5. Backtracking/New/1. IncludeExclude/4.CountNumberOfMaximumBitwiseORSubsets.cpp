#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given an integer array nums, find the maximum possible bitwise OR of a subset of nums and return the 
	number of different non-empty subsets with the maximum bitwise OR.

	An array a is a subset of an array b if a can be obtained from b by deleting some (possibly zero) 
	elements of b. Two subsets are considered different if the indices of the elements chosen are different.

	The bitwise OR of an array a is equal to a[0] OR a[1] OR ... OR a[a.length - 1] (0-indexed).



	Examples:
	---------
	Input: nums = [3,1]
	Output: 2
	Explanation: The maximum possible bitwise OR of a subset is 3. There are 2 subsets with a bitwise OR of 3:
	- [3]
	- [3,1]

	Input: nums = [2,2,2]
	Output: 7
	Explanation: All non-empty subsets of [2,2,2] have a bitwise OR of 2. There are 23 - 1 = 7 total subsets.

	Input: nums = [3,2,1,5]
	Output: 6
	Explanation: The maximum possible bitwise OR of a subset is 7. There are 6 subsets with a bitwise OR of 7:
	- [3,5]
	- [3,1,5]
	- [3,2,5]
	- [3,2,1,5]
	- [2,5]
	- [2,1,5]


	Approach:
	----------
	Include and exclude
*/

class Solution {
private:
	void solve(vector<int>& A, int currentXor, int& maxXor, int& numOfSubsets, int i) {
		if (i == A.size()) {
			if (currentXor > maxXor) {
				maxXor = currentXor;
				numOfSubsets = 1;
			}
			else if (currentXor == maxXor)
				numOfSubsets++;
			return;
		}

		//include
		solve(A, currentXor | A[i], maxXor, numOfSubsets, i + 1);

		//exclude
		solve(A, currentXor, maxXor, numOfSubsets, i + 1);
	}
public:
	int countMaxOrSubsets(vector<int>& nums) {
		int currentXor = 0, maxXor = 0, numOfSubsets = 0;
		solve(nums, currentXor, maxXor, numOfSubsets, 0);
		return numOfSubsets;
	}
};

int main() {
	Solution obj;
	vector<int> A = { 3,1 };
	cout<<obj.countMaxOrSubsets(A);
}