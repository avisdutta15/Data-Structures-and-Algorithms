#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <stack>
#include <string>

using namespace std;

/*
	Problem Statement:
	------------------
	Given a circular integer array nums of length n, return the maximum possible sum of a non-empty subarray of nums.

	A circular array means the end of the array connects to the beginning of the array. 
	Formally, the next element of nums[i] is nums[(i + 1) % n] and the previous element of nums[i] is nums[(i - 1 + n) % n].

	A subarray may only include each element of the fixed buffer nums at most once. 
	Formally, for a subarray nums[i], nums[i + 1], ..., nums[j], there does not exist i <= k1, k2 <= j with k1 % n == k2 % n.


	Examples:
	---------
	Input: nums = [1,-2,3,-2]
	Output: 3
	Explanation: Subarray [3] has maximum sum 3.

	Input: nums = [5,-3,5]
	Output: 10
	Explanation: Subarray [5,5] has maximum sum 5 + 5 = 10.

	Input: nums = [-3,-2,-3]
	Output: -2
	Explanation: Subarray [-2] has maximum sum -2.

	Approach:
	---------
	In a circular array, the highest-sum contiguous subarray can manifest in two patterns:
	Case 1: No Wrapping (Linear Subarray)
		The maximum subarray does not cross the boundary between the last and first elements.
		Solution: Run standard Kadane's algorithm to find the max_linear_sum.

	Case 2: Wrapping Around (Circular Subarray)
	The maximum subarray includes elements from the end of the array and wraps around to the 
	beginning.
	The Trick: If the maximum subarray wraps around, the elements left over in the middle must 
			   form the contiguous subarray with the minimum possible sum.
	Solution: Find the minimum subarray sum using a reversed Kadane's logic. 
			  Subtract this from the total_sum of the array: 
				
								max_circular_sum = total_sum - min_subarray_sum

	The final answer is simply max(max_linear_sum, max_circular_sum)

	Edge Case:
			If all the elements are -ve. [-1, -2, -3]
			Then 
				max_linear_sum = -1
				min_linear_sum = -6
				total_sum      = -6
				max_circular_sum = -6 - (-6) = 0

				max sum as per above formula: max(max_linear_sum, max_circular_sum)
										    = max(-1, 0)
											= 0. (But this is not the maximum sum!)

				The maximum sum in this case is max_linear_sum.

				When will this case arise?
				When all the elements are negative.

				Example 1:
				[-1, 2, -3]
											
*/

class Solution {
public:
	int maxSubarraySumCircular(vector<int>& A) {
		int max_linear_subarray_sum = INT_MIN;
		int min_linear_subarray_sum = INT_MAX;

		int current_subarray_sum_max = 0;
		int current_subarray_sum_min = 0;

		int total_sum = 0;

		for (int i = 0; i < A.size(); i++) {

			// Step 1: Calculate the max subarray sum
			// start current subarray sum from i
			// end current subarray sum at i
			int start_current_subarray_sum_max = A[i];
			int end_current_subarray_sum_atI_max = current_subarray_sum_max + A[i];

			current_subarray_sum_max = max(start_current_subarray_sum_max, end_current_subarray_sum_atI_max);
			max_linear_subarray_sum = max(max_linear_subarray_sum, current_subarray_sum_max);

			// Step 2: Calculate the min subarray sum
			// start current subarray sum from i
			// end current subarray sum at i
			int start_current_subarray_sum_min = A[i];
			int end_current_subarray_sum_atI_min = current_subarray_sum_min + A[i];

			current_subarray_sum_min = min(start_current_subarray_sum_min, end_current_subarray_sum_atI_min);
			min_linear_subarray_sum = min(min_linear_subarray_sum, current_subarray_sum_min);

			// Step 3: Calculate the total sum
			total_sum = total_sum + A[i];
		}

		int max_circular_sum = total_sum - min_linear_subarray_sum;

		// if all the elements are negative then
		// min_linear_sum == total_sum
		// [-1, -2, -3] -> min_linear_sum = -6. total_sum = -6.
		// But this is not the maximum sum. maximum is -1.
		// this -1 is captured in max_linear_sum
		if (min_linear_subarray_sum == total_sum) {
			return max_linear_subarray_sum;
		}

		// else the maximum will be either the maximum sum from linear array
		// or the maximum sum formed by the circular array.
		return max(max_linear_subarray_sum, max_circular_sum);
	}

};

int main() {
    Solution obj;
	vector<int> A = { 1, -2, 3, -2 };
	cout << obj.maxSubarraySumCircular(A) << endl;	//3

	A = { 5, -3, 5 };
	cout << obj.maxSubarraySumCircular(A) << endl;  //10

	A = { -3,-2,-3 };
	cout << obj.maxSubarraySumCircular(A) << endl;	//-2

	return 0;
}