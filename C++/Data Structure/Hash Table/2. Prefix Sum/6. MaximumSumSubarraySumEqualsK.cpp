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

	seen [0,  -1]
	i = 0;
		sum = 0 + 10 = 10
		target = 10 - (-10) = 20.
		target not present in seen
		sum seen for first time, insert into seen with index
		seen [0,  -1]
			 [10,  0]

	i = 1;
		sum = 10 + 2 = 12
		target = 12 - (-10) = 22.
		target not present in seen
		sum seen for first time, insert into seen with index
		seen [0,  -1]
			 [10,  0]
			 [12,  1]

	i = 2;
		sum = 12 + (-2) = 10
		target = 10 - (-10) = 20.
		target not present in seen
		sum not seen for first time, dont update the index of sum in seen
		seen [0,  -1]
			 [10,  0]
			 [12,  1]

	i = 3;
		sum = 10 + (-20) = -10
		target = -10 - (-10) = 0.
		target present in seen.
			Lets calculate the subarray sizes.
			start = seen[0] + 1 = 0
			end   = 3
			size  = 3-0+1 = 4
		sum seen for first time, insert into seen with index
		seen [0,  -1]
			 [10,  0]
			 [12,  1]
			 [-10, 3]
	i = 4;
		sum = -10 + 10 = 0
		target = 0 - (-10) = 10.
		target present in seen.
			Lets calculate the subarray sizes.
			start = seen[10] + 1 = 1
			end   = 4
			size  = 4-1+1 = 3
		sum not seen for first time, dont update the index of sum in seen
		seen [0,  -1]
			 [10,  0]
			 [12,  1]
			 [-10, 3]
	Note: we have seen 10, two times, but we took the first occurence. So store the
	first occurrence of 10 since we want max and not min size.
*/

class Solution {
public:
	int maximumSizeSubarraysWithSumK(vector<int>& A, int k) {
		int n = A.size();
		vector<int> prefixSum(n, 0);

		//map [sum, first_index]
		unordered_map<int, int> seen;
		int maxSizeSubarray = 0;
		seen[0] = -1;

		for (int i = 0; i < n; i++) {
			prefixSum[i] = (i == 0) ? A[0] : prefixSum[i - 1] + A[i];

			if (seen.count(prefixSum[i] - k) != 0) {
				int startIndex = seen[prefixSum[i] - k] + 1;
				int endIndex = i;
				maxSizeSubarray = max(maxSizeSubarray, endIndex - startIndex + 1);
			}
			if (seen.find(prefixSum[i]) == seen.end()) {
				seen[prefixSum[i]] = i;
			}
		}
		return maxSizeSubarray;
	}
};

int main() {
	Solution obj;
	vector<int> A = { 10, 2, -2, -20, 10 };
	cout << obj.maximumSizeSubarraysWithSumK(A, -10) << endl;
	
	return 0;
}