#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given an array arr[] of length n and a number k, the task is to find all the subsequences of the array
	with sum of its elements equal to k.

	Note: A subsequence is a subset that can be derived from an array by removing zero or more elements,
	without changing the order of the remaining elements.



	Examples:
	---------
	Input: arr[] = [1, 2, 3], k = 3
	Output: [ [1, 2], [3] ]
	Explanation: All the subsequences of the given array are:
	[ [1], [1, 2], [1, 2, 3], [1, 3], [2], [2, 3], [3], [] ]
	Out of which only two subsequences have sum of their elements equal to 3.

	Input: arr[] = [1, 2, 3], k = 7
	Output: []
	Explanation: Sum of all the elements of the array is 6, which is smaller than the required sum,
	thus they are no subsequences with sum of its elements equal to 7.

	Input: arr[] = [17, 18, 6, 11, 2, 4], k = 6
	Output: [ [2, 4], [6] ]

	Approach:
	----------
	Include and exclude
*/

class Solution {
private:
	void solve(const vector<int>& A, vector<vector<int>> &allSubsets, vector<int> &subset, int i, int sum) {

		//base case: reached the end of the input list so push the current subsequnce to the result
		if (i == A.size()) {
			if(sum == 0)
				allSubsets.push_back(subset);
			return;
		}

		//include
		//condition? = Yes, canRepeat? = No
		if (sum >= A[i]) {
			subset.push_back(A[i]);
			solve(A, allSubsets, subset, i + 1, sum - A[i]);
			subset.pop_back();	//backtrack
		}		

		//exclude
		solve(A, allSubsets, subset, i + 1, sum);
	}
public:
	void printAllSubsequencesWithSumK(const vector<int>& A, int sum) {
		vector<vector<int>> allSubsets;
		vector<int> subset;
		solve(A, allSubsets, subset, 0, sum);

		for (auto v : allSubsets) {
			for (auto i : v) cout << i << " ";
			cout << endl;
		}
	}
};

int main() {
	Solution obj;
	vector<int> A = {1, 2, 3};
	obj.printAllSubsequencesWithSumK(A, 3);
}