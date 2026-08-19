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
	https://www.youtube.com/watch?v=yCQN096CwWM
	Problem Statement:
	------------------
	The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence, 
	such that each number is the sum of the two preceding ones, starting from 0 and 1. That is,

		F(0) = 0, F(1) = 1
		F(n) = F(n - 1) + F(n - 2), for n > 1.

	Given n, calculate F(n).



	Examples:
	---------
	Input: n = 2
	Output: 1
	Explanation: F(2) = F(1) + F(0) = 1 + 0 = 1.

	Input: n = 3
	Output: 2
	Explanation: F(3) = F(2) + F(1) = 1 + 1 = 2.

	Input: n = 4
	Output: 3
	Explanation: F(4) = F(3) + F(2) = 2 + 1 = 3.

	Constraints:
	------------
	0 <= n <= 30

	Approach:
	--------
											
*/

// Recursive
class Solution1 {
public:
	int fib(int n) {
		if (n == 0)
			return 0;
		if (n == 1)
			return 1;

		return fib(n - 1) + fib(n - 2);
	}
};

// Top Down: Memoization
class Solution2 {
private:
	int fibDP(int n, vector<int>& dp) {
		if (n == 0)
			return dp[n] = 0;
		if (n == 1)
			return dp[n] = 1;

		if (dp[n] != -1)
			return dp[n];

		return dp[n] = fibDP(n - 1, dp) + fibDP(n - 2, dp);
	}
public:
	int fib(int n) {
		vector<int> dp(n + 1, -1);
		return fibDP(n, dp);
	}
};

// Bottom Up
class Solution3 {
public:
	int fib(int n) {
		// Base Case:
		if (n == 0)
			return 0;
		if (n == 1)
			return 1;

		// dp[i] = ith Fibonacci Number
		vector<int> dp(n + 1, -1);

		dp[0] = 0;
		dp[1] = 1;

		for (int i = 2; i <= n; i++) {
			dp[i] = dp[i - 1] + dp[i - 2];
		}
		return dp[n];
	}
};

// Bottom Up: O(N) time and O(1) space
class Solution4 {
public:
	int fib(int n) {
		// Base Case:
		if (n == 0)
			return 0;
		if (n == 1)
			return 1;

		int prev_prev = 0;      // dp[i-2]
		int prev = 1;           // dp[i-1]
		int current = 0;        // dp[i]

		for (int i = 2; i <= n; i++) {
			// dp[i] = dp[i-1] + dp[i-2]
			current = prev + prev_prev;

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
	cout << obj.fib(5) << endl;
	return 0;
}