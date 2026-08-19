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
	https://www.youtube.com/watch?v=5AxMZBirNKo
	https://www.youtube.com/watch?v=Sobml7FprQ0
	Problem Statement:
	------------------
	You are a professional robber planning to rob houses along a street. 
	Each house has a certain amount of money stashed. 
	All houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. 
	Meanwhile, adjacent houses have a security system connected, and it will automatically contact the police if 
	two adjacent houses were broken into on the same night.

	Given an integer array nums representing the amount of money of each house, return the maximum amount 
	of money you can rob tonight without alerting the police.


	Examples:
	---------
	Input: nums = [2,3,2]
	Output: 3
	Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because they are adjacent houses.

	Input: nums = [1,2,3,1]
	Output: 4
	Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
	Total amount you can rob = 1 + 3 = 4.

	Input: nums = [1,2,3]
	Output: 3

	Constraints:
	------------
	1 <= nums.length <= 100
	0 <= nums[i] <= 1000

	Approach:
	--------
	Conditions are :
		- If we rob a house, we cannot rob the adjacent house.
		- Also, if we had robbed first house we cannot rob last house.
	That means we can selectively run 2 linear cases and compare whichever gives larger result -
		Rob house 0 + Max robbing possible from houses[2...n-2] - SCENARIO 1
		Do not rob house 0 + Max robbing possible from houses[1...n-1] - SCENARIO 2

	That means given a linear stretch of houses from index=[start,end], we could have a function that
	return maxRobbing possible in that range of house.
*/

// Recursive
class Solution1 {
private:
	// maximum amount that can be robbed from ith house to nth house
	int solve(int i, int n, vector<int>& nums) {
		// if we have reached the nth house then we visited all house but couldnot rob any
		// so the amount robbed is 0.
		if (i > n)
			return 0;
		
		// rob the ith house
		int include_ith_house = nums[i] + solve(i + 2, n, nums);
		
		// dont rob the ith house
		int exclude_ith_house = solve(i + 1, n, nums);

		// return max amount that can be collected by either 
		// robbing the ith house or not robbing the ith house
		return max(include_ith_house, exclude_ith_house);
	}

public:
	int rob(vector<int>& nums) {
		int n = nums.size();		
		return max(solve(0, n-2, nums), solve(1, n-1, nums));
	}
};

// Top Down: Memoization
class Solution2 {
private:
	// maximum amount that can be robbed from ith house to nth house
	int solve(int i, int n, vector<int>& nums, vector<int>& dp) {
		// if we have crossed the nth house then we visited all house but couldnot rob any
		// so the amount robbed is 0.
		if (i > n)
			return 0;

		// check cache
		if (dp[i] != -1)
			return dp[i];

		// rob the ith house
		int include_ith_house = nums[i] + solve(i + 2, n, nums, dp);

		// dont rob the ith house
		int exclude_ith_house = solve(i + 1, n, nums, dp);

		// return max amount that can be collected by either 
		// robbing the ith house or not robbing the ith house
		return dp[i] = max(include_ith_house, exclude_ith_house);
	}

public:
	int rob(vector<int>& nums) {
		int n = nums.size();

		// Explicit edge cases for small arrays
		// If nums = [5], then n = 1.
		// When you call solve(0, n - 2), you are calling solve(0, -1).Your base case if (i > n) triggers and returns 0. 
		// The second call solve(1, 0) also returns 0. The final answer becomes 0 instead of 5.
		// The Fix : Explicitly handle n == 1 before splitting the logic.
		if (n == 0) return 0;
		if (n == 1) return nums[0];

		vector<int> dp(n + 2, -1);

		int include_first_exclude_last = solve(0, n - 2, nums, dp);

		// reset cache
		for (int i = 0; i < dp.size(); i++)
			dp[i] = -1;

		int exclude_first_include_last = solve(1, n - 1, nums, dp);
		return max(include_first_exclude_last, exclude_first_include_last);
	}
};

// Bottom Up
class Solution3 {
private:
	int solve(int start, int end, vector<int>& nums) {
		// size the DP array to easily accommodate global indices
		int N = nums.size();
		// maximum amount that can be robbed from start house to end house
		vector<int> dp(N + 2, 0);

		dp[N + 1] = 0;
		dp[N] = 0;

		for (int i = end; i >= start; i--) {
			// rob the ith house
			int include_ith_house = nums[i] + dp[i + 2];

			// dont rob the ith house
			int exclude_ith_house = dp[i + 1];

			// return max amount that can be collected by either
			// robbing the ith house or not robbing the ith house
			dp[i] = max(include_ith_house, exclude_ith_house);
		}

		// Return the answer resting at the 'start' index, not strictly 0.
		return dp[start];
	}
public:
	int rob(vector<int>& nums) {
		int n = nums.size();

		// Explicit edge cases for small arrays
		if (n == 0) return 0;
		if (n == 1) return nums[0];

		int include_first_exclude_last = solve(0, n - 2, nums);
		int exclude_first_include_last = solve(1, n - 1, nums);
		return max(include_first_exclude_last, exclude_first_include_last);
	}
};

// Bottom Up: O(N) time and O(1) space
// Can we use constant space? Yes. dp[i] depends on dp[i+1] and dp[i+2]
class Solution4 {
private:
	int solve(int start, int end, vector<int>& nums) {
		// size the DP array to easily accommodate global indices
		int N = nums.size();
		// maximum amount that can be robbed from start house to end house        
		int next_next = 0;      //dp[i+2]
		int next = 0;           //dp[i+1]
		int current = 0;        //dp[i]

		for (int i = end; i >= start; i--) {
			// rob the ith house
			int include_ith_house = nums[i] + next_next;

			// dont rob the ith house
			int exclude_ith_house = next;

			// return max amount that can be collected by either
			// robbing the ith house or not robbing the ith house
			current = max(include_ith_house, exclude_ith_house);

			next_next = next;
			next = current;
		}

		// Return the answer resting at the 'start' index, not strictly 0.
		return current;
	}
public:
	int rob(vector<int>& nums) {
		int n = nums.size();

		// Explicit edge cases for small arrays
		if (n == 0) return 0;
		if (n == 1) return nums[0];

		int include_first_exclude_last = solve(0, n - 2, nums);
		int exclude_first_include_last = solve(1, n - 1, nums);
		return max(include_first_exclude_last, exclude_first_include_last);
	}
};

int main() {
    Solution3 obj;
	vector<int> nums = { 2,3,2 };
	cout << obj.rob(nums) << endl;

	nums = { 1,2,3,1 };
	cout << obj.rob(nums) << endl;
	
	nums = { 1,2,3 };
	cout << obj.rob(nums) << endl;

	return 0;
}