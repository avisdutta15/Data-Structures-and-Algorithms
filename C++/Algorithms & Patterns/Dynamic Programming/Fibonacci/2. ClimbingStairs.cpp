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
	https://www.youtube.com/watch?v=6OjGE04Kx_M
	Problem Statement:
	------------------
	You are climbing a staircase. It takes n steps to reach the top.
	Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?


	Examples:
	---------
	Input: n = 2
	Output: 2
	Explanation: There are two ways to climb to the top.
	1. 1 step + 1 step
	2. 2 steps

	Input: n = 3
	Output: 3
	Explanation: There are three ways to climb to the top.
	1. 1 step + 1 step + 1 step
	2. 1 step + 2 steps
	3. 2 steps + 1 step

	Constraints:
	------------
	1 <= n <= 45

	Approach:
	--------
											
*/

// Recursive
class Solution1 {
public:
	int climbStairs(int n) {
		// if n = 0 i.e. no stairs then 0 ways to reach here
		if (n == 0)
			return 0;

		// if n = 1 i.e. 1 stairs. then 1 ways (1 step) to reach here
		if (n == 1)
			return 1;

		// if n = 2 i.e. 2 stairs. then 2 ways (1 step or 2 step) to reach here
		if (n == 2)
			return 2;

		return climbStairs(n - 1) + climbStairs(n - 2);
	}
};

// Top Down: Memoization
class Solution2 {
public:
	int climbStairsMemo(int n, vector<int>& dp) {
		// if n = 0 i.e. no stairs then 0 ways to reach here
		if (n == 0)
			return dp[n] = 0;

		// if n = 1 i.e. 1 stairs. then 1 ways (1 step) to reach here
		if (n == 1)
			return dp[n] = 1;

		// if n = 2 i.e. 2 stairs. then 2 ways (1 step or 2 step) to reach here
		if (n == 2)
			return dp[n] = 2;

		return dp[n] = climbStairsMemo(n - 1, dp) + climbStairsMemo(n - 2, dp);
	}

	int climbStairs(int n) {
		vector<int> dp(n + 1, -1);
		return climbStairsMemo(n, dp);
	}
};

// Bottom Up
class Solution3 {
public:
	int climbStairs(int n) {
		vector<int> dp(n + 1, -1);
		if (n == 0)
			return 0;
		if (n == 1)
			return 1;
		if (n == 2)
			return 2;

		dp[0] = 0;
		dp[1] = 1;
		dp[2] = 2;

		for (int stair = 3; stair <= n; stair++) {
			dp[stair] = dp[stair - 1] + dp[stair - 2];
		}

		return dp[n];
	}
};

// Bottom Up: O(N) time and O(1) space
class Solution4 {
public:
	int climbStairs(int n) {
		if (n == 0)
			return 0;
		if (n == 1)
			return 1;
		if (n == 2)
			return 2;

		int prev_prev = 1;
		int prev = 2;
		int current = 0;

		for (int stair = 3; stair <= n; stair++) {
			// dp[i] = dp[i-2] + dp[i-1] 
			current = prev_prev + prev;

			// dp[i-2] = dp[i-1]
			prev_prev = prev;

			// dp[i-1] = dp[i]
			prev = current;
		}

		return current;
	}
};

int main() {
    Solution4 obj;
	cout << obj.climbStairs(5) << endl;
	return 0;
}