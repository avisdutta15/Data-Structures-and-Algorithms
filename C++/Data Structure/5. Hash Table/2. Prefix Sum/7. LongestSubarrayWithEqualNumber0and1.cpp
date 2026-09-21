#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <numeric>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given an array arr[] containing only 0s and 1s, find the longest subarray which contains equal no of 0s and 1s.

	Examples:
	---------
	Input: arr[] = [1, 0, 1, 1, 1, 0, 0]
	Output: 6
	Explanation: arr[1 ... 6] is the longest subarray with three 0s and three 1s.

	Input: arr[] = [0, 0, 1, 1, 0]
	Output: 4
	Explanation: arr[0 ... 3] or  arr[1 ... 4] is the longest subarray with two 0s and two 1s.

	Input: arr[] = [0]
	Output: 0
	Explanation: There is no subarray with an equal number of 0s and 1s.

	Approach:
	---------
	Modify the array. Replace all 0s with -1.
	Now array has only 1 ans -1.
	Now the problem is longest subarray with sum = 0.
	
*/

class Solution {
public:
	int longestSubarray(vector<int>& A) {
		int n = A.size();

		for (int i = 0; i < n; i++) {
			if (A[i] == 0) A[i] = -1;
		}

		int k = 0;
		int prefixSum = 0;
		int maxSubarraySize = 0;
		//<prefixSum, firstOccurrenceIndex>
		unordered_map<int, int> seen;
		seen[0] = -1;

		for (int i = 0; i < n; i++) {
			prefixSum = prefixSum + A[i];

			if (seen.count(prefixSum - k) != 0) {
				int startIndex = seen[prefixSum - k] + 1;
				int endIndex = i;
				maxSubarraySize = max(maxSubarraySize, endIndex - startIndex + 1);
			}

			if (seen.count(prefixSum) == 0) {
				seen[prefixSum] = i;
			}
		}

		return maxSubarraySize;
	}
};

int main() {
	Solution obj;
	vector<int> A = { 1, 0, 1, 1, 1, 0, 0 };
	cout << obj.longestSubarray(A) << endl;
	
	A = { 0 };
	cout << obj.longestSubarray(A) << endl;

	return 0;
}