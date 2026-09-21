#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <numeric>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.
	A subarray is a contiguous non-empty sequence of elements within an array.

	Examples:
	---------
	Example 1:
	Input: nums = [1,1,1], k = 2
	Output: 2

	Example 2:
	Input: nums = [1,2,3], k = 3
	Output: 2

	Constraints:
	1 <= nums.length <= 2 * 10^4
	-1000 <= nums[i] <= 1000
	-10^7 <= k <= 10^7

	Approach:
	---------
	We are looking for a subarray ending at index i with a sum of k.
	Let curr be the prefix sum at the current index i.
	We need to find an older prefix sum, let's call it prev, such that:
		curr - prev = k
	If we rearrange this equation, we get the key to the solution:
		prev = curr - k
	What this means:
	As we iterate through the array and calculate the current running sum (curr), 
	we simply need to ask: "How many times have I seen a prefix sum of curr - k before?"

	Step-by-Step Walkthrough:
	------------------------
	Let's trace nums = [1, 1, 1], k = 2.

	Initialization:
	count = 0 (The answer)
	curr_sum = 0 (Running total)
	prefix_map = {0: 1} (Key: Prefix Sum, Value: Count).
		Why {0: 1}? This handles the case where a subarray starts strictly from index 0. 
					It represents a "sum of 0" before the array begins.
	
	Iteration:
	Index 0 (Value 1):
	curr_sum becomes 0 + 1 = 1.
	Target to find: curr_sum - k -> 1 - 2 = -1.
	Is -1 in prefix_map? No.
	Add curr_sum to map: prefix_map is now {0: 1, 
											1: 1}.
	
	Index 1 (Value 1):
	curr_sum becomes 1 + 1 = 2.
	Target to find: 2 - 2 = 0.
	Is 0 in prefix_map? Yes, with frequency 1.
	count increases by 1. (Total: 1)
	Add curr_sum to map: prefix_map is now {0: 1, 
											1: 1, 
											2: 1}.
	
	Index 2 (Value 1):
	curr_sum becomes 2 + 1 = 3.
	Target to find: 3 - 2 = 1.
	Is 1 in prefix_map? Yes, with frequency 1.
	count increases by 1. (Total: 2)
	Add curr_sum to map.

*/

class Solution {
public:
	//T.C. - O(n^2)
	int subarraySumNaive(vector<int>& A, int k) {
		int n = A.size();
		int countOfSubarraySumK = 0;

		for (int i = 0; i < n; i++) {
			int currentSubarraySum = 0;

			for (int j = i; j < n; j++) {
				currentSubarraySum += A[j];
				if (currentSubarraySum == k)
					countOfSubarraySumK++;
			}
		}
		return countOfSubarraySumK;
	}

	// if P[R] - P[L-1] = K then the subarray is A[L,R]
	// P[R] - K = P[L-1]
	// there for if we have seen a sum P[L-1] i.e. P[R] - K before
	// then it means a subarray with sum k exists.
	// T.C. - O(N) S.C. - O(2N)
	int subarraySum(vector<int>& A, int k) {
		int n = A.size();
		vector<int> prefixSum(n, 0);
		unordered_map<int, int> seen;
		int countOfSubarraySum = 0;

		seen.insert({ 0, 1 });
		
		for (int i = 0; i < n; i++) {
			prefixSum[i] = (i==0) ? A[0] : prefixSum[i - 1] + A[i];

			if(seen.count(prefixSum[i] - k)!=0){
				countOfSubarraySum += seen[prefixSum[i]-k];
			}
			seen[prefixSum[i]]++;
		}

		return countOfSubarraySum;
	}

	int subarraySumSpaceOptimized(vector<int>& A, int k) {
		int n = A.size();
		unordered_map<int, int> seen;
		int countOfSubarraySum = 0;
		int sum = 0;	// use a single sum variable instead of a prefixSum[]

		seen.insert({ 0, 1 });

		for (int i = 0; i < n; i++) {
			sum = sum + A[i];

			if (seen.count(sum - k) != 0) {
				countOfSubarraySum += seen[sum - k];
			}
			seen[sum]++;
		}

		return countOfSubarraySum;
	}
};

int main() {
	Solution obj;
	vector<int> A = { 10, 2, -2, -20, 10 };
	cout << obj.subarraySum(A, -10) << endl;

	return 0;
} 