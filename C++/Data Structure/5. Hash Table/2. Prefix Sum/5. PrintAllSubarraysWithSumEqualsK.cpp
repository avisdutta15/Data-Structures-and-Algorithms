#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <numeric>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given an array of integers nums and an integer k, print all the subarrays whose sum equals to k.
	A subarray is a contiguous non-empty sequence of elements within an array.

	Examples:
	---------
	Example 1:
	Input: nums = [1,1,1], k = 2
	Output: [0,1] [1,2]

	Example 2:
	Input: nums = [1,2,3], k = 3
	Output: [0,1] [2,2]

	Constraints:
	1 <= nums.length <= 2 * 10^4
	-1000 <= nums[i] <= 1000
	-10^7 <= k <= 10^7

	Approach:
	---------
	A =			  [10,	   2,	   -2,    -20,		10]
	i =	  -1,		0,     1,		2,      3,		 4
	p =    0,		10,   12,	   10,    -10,		 0

	seen	[0,  {-1, 4}], 
			[10, {0, 2}]
			[12, {1}]
			[-10,{3}]
	
	ans = [0, 3] [1, 4] [3, 4]
*/

class Solution {
public:
	vector<vector<int>> printAllSubarraysWithSumK(vector<int>& A, int k) {
		int n = A.size();
		vector<int> prefixSum(n, 0);

		//map [sum, index[]]
		unordered_map<int, vector<int>> seen;
		vector<vector<int>> allSubarrays;
		
		seen[0].push_back(- 1);

		for (int i = 0; i < n; i++) {
			prefixSum[i] = (i==0) ? A[0] : prefixSum[i-1] + A[i];

			if (seen.count(prefixSum[i] - k) != 0) {
				auto indices = seen[prefixSum[i] - k];
				for (auto startIndex : indices) {
					allSubarrays.push_back({ startIndex + 1, i });
				}
			}
			seen[prefixSum[i]].push_back(i);
		}
		return allSubarrays;
	}
};

int main() {
	Solution obj;
	vector<int> A = { 10, 2, -2, -20, 10 };
	auto allSubarrays = obj.printAllSubarraysWithSumK(A, -10);
	for (auto subarray : allSubarrays) {
		cout << subarray[0] << " " << subarray[1] << endl;
	}
	return 0;
} 