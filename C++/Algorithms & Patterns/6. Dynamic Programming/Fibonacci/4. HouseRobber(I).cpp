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
	https://www.youtube.com/watch?v=SI6Pm8AKqnQ
	Problem Statement:
	------------------
	You are a professional robber planning to rob houses along a street. Each house has a certain amount of 
	money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have 
	security systems connected and it will automatically contact the police if two adjacent houses were 
	broken into on the same night.

	Given an integer array nums representing the amount of money of each house, return the maximum amount 
	of money you can rob tonight without alerting the police.


	Examples:
	---------
	Input: nums = [1,2,3,1]
	Output: 4
	Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
	Total amount you can rob = 1 + 3 = 4.

	Input: nums = [2,7,9,3,1]
	Output: 12
	Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
	Total amount you can rob = 2 + 9 + 1 = 12.



	Constraints:
	------------
	1 <= nums.length <= 100
	0 <= nums[i] <= 400

	Approach:
	--------
	A robber has 2 options: a) rob current house i; b) don't rob current house.
		If an option "a" is selected it means she can't rob next i+1 house but can safely proceed to 
						 the one after next i.e. i+2 and gets all cumulative loot that follows.
		If an option "b" is selected the robber gets all the possible loot from robbery of i+1 and all the following buildings.
		
	So it boils down to calculating what is more profitable:
		- robbery of current house + loot from houses before the next
		- loot from the next house robbery and any loot captured after that
		
	rob(i) = Math.max( currentHouseValue + rob(i + 2), rob(i + 1) )
*/

// Recursive
class Solution1 {
private:
	// maximum amount that can be robbed from ith house to last house
	int solve(int i, vector<int>& nums) {
		// if we have reached the nth house then we visited all house but couldnot rob any
		// so the amount robbed is 0.
		if (i >= nums.size())
			return 0;

		// rob the ith house
		int include_ith_house = nums[i] + solve(i + 2, nums);
		
		// dont rob the ith house
		int exclude_ith_house = solve(i + 1, nums);

		// return max amount that can be collected by either 
		// robbing the ith house or not robbing the ith house
		return max(include_ith_house, exclude_ith_house);
	}

public:
	int rob(vector<int>& nums) {
		return solve(0, nums);
	}
};

// Top Down: Memoization
class Solution2 {
private:
	// maximum amount that can be robbed from ith house to last house
	int solve(int i, vector<int>& nums, vector<int>& dp) {
		// if we have reached the nth house then we visited all house but couldnot rob any
		// so the amount robbed is 0.
		if (i >= nums.size())
			return dp[i] = 0;

		if (dp[i] != -1)
			return dp[i];

		// rob the ith house
		int include_ith_house = nums[i] + solve(i + 2, nums, dp);

		// dont rob the ith house
		int exclude_ith_house = solve(i + 1, nums, dp);

		// return max amount that can be collected by either 
		// robbing the ith house or not robbing the ith house
		return dp[i] = max(include_ith_house, exclude_ith_house);
	}

public:
	int rob(vector<int>& nums) {
		int N = nums.size();
		vector<int> dp(N + 2, -1);
		return solve(0, nums, dp);
	}
};

// Bottom Up
class Solution3 {
public:
	int rob(vector<int>& nums) {
		int N = nums.size();

		// maximum amount that can be robbed from ith house to last house
		vector<int> dp(N + 2, -1);

		dp[N + 1] = 0;
		dp[N] = 0;

		for (int i = N - 1; i >= 0; i--) {
			// rob the ith house
			int include_ith_house = nums[i] + dp[i + 2];

			// dont rob the ith house
			int exclude_ith_house = dp[i + 1];

			// return max amount that can be collected by either
			// robbing the ith house or not robbing the ith house
			dp[i] = max(include_ith_house, exclude_ith_house);
		}

		return dp[0];
	}
};

// Bottom Up: O(N) time and O(1) space
// Can we use constant space? Yes. dp[i] depends on dp[i+1] and dp[i+2]
class Solution4 {
public:
	int rob(vector<int>& nums) {
		int N = nums.size();

		// maximum amount that can be robbed from ith house to last house
		vector<int> dp(N + 2, -1);

		int next_next = 0;      //dp[i + 2] = 0;
		int next = 0;           //dp[i + 1] = 0;
		int current = 0;        //dp[i]

		for (int i = N - 1; i >= 0; i--) {
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

		return current;
	}
};


int main() {
    Solution1 obj;
	vector<int> nums = { 2,7,9,3,1 };
	cout << obj.rob(nums) << endl;
	return 0;
}