#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	You are given an integer array nums and an integer target.

	You want to build an expression out of nums by adding one of the symbols '+' and '-' 
	before each integer in nums and then concatenate all the integers.

	For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and 
	concatenate them to build the expression "+2-1".
	Return the number of different expressions that you can build, which evaluates to target.


	Examples:
	---------
	Input: nums = [1,1,1,1,1], target = 3
	Output: 5
	Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
	-1 + 1 + 1 + 1 + 1 = 3
	+1 - 1 + 1 + 1 + 1 = 3
	+1 + 1 - 1 + 1 + 1 = 3
	+1 + 1 + 1 - 1 + 1 = 3
	+1 + 1 + 1 + 1 - 1 = 3

	Example 2:
	Input: nums = [1], target = 1
	Output: 1


	Approach:
	----------
	Include and exclude
*/

class Solution {
private:
	int solve(vector<int>& nums, int i, int& target, int current_subset_sum) {
		//exhausted all the elements
		if (i == nums.size()) {
			// if target sum == current_subset_sum
			if (current_subset_sum == target)
				return 1;
			else if (current_subset_sum != target)
				return 0;
		}

		//add +
		int plus = solve(nums, i + 1, target, current_subset_sum + nums[i]);

		//add -
		int minus = solve(nums, i + 1, target, current_subset_sum + (-nums[i]));

		//return total ways
		return plus + minus;
	}

public:
	int findTargetSumWays(vector<int>& nums, int target) {
		int i = 0;
		int current_subset_sum = 0;

		return solve(nums, i, target, current_subset_sum);
	}
};

int main() {
	Solution obj;
	vector<int> A = { 1,1,1,1,1 };
	cout << obj.findTargetSumWays(A, 3);
}
