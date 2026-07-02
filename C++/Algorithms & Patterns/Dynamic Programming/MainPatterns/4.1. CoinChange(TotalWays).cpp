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
    -----------------
	You are given an integer array coins representing coins of different denominations 
	and an integer amount representing a total amount of money.

	Return the number of combinations that make up that amount. If that amount of money 
	cannot be made up by any combination of the coins, return 0.

	You may assume that you have an infinite number of each kind of coin.
	The final answer is guaranteed to fit into a signed 32-bit integer.
	
	Examples:
	---------
	Input: amount = 5, coins = [1,2,5]
	Output: 4
	Explanation: there are four ways to make up the amount:
	5=5
	5=2+2+1
	5=2+1+1+1
	5=1+1+1+1+1

	Input: amount = 3, coins = [2]
	Output: 0
	Explanation: the amount of 3 cannot be made up just with coins of 2.

	Input: amount = 10, coins = [10]
	Output: 1


	Constraints:
	------------
	1 <= coins.length <= 300
	1 <= coins[i] <= 5000
	All the values of coins are unique.
	0 <= amount <= 5000

	Approach:
	--------
	Unbounded knapsack variation	
*/

// Recusion
class Solution1 {
private:
	int solve(int i, vector<int>& coins, int amount) {
		if (amount == 0)
			return 1;

		if (amount < 0 || i == 0)
			return 0;

		int include = 0;
		int exclude = 0;
		if (coins[i - 1] <= amount) {
			include = solve(i, coins, amount - coins[i - 1]);
		}
		exclude = solve(i - 1, coins, amount);

		return include + exclude;
	}
public:
	int change(int amount, vector<int>& coins) {
		int n = coins.size();
		return solve(n, coins, amount);
	}
};

// Top Down : Memoization
class Solution2 {
private:
	int solve(int i, vector<int>& coins, int amount, vector<vector<int>> &dp) {
		if (amount == 0)
			return 1;

		if (amount < 0 || i == 0)
			return 0;

		if(dp[i][amount] != -1)
			return dp[i][amount];

		int include = 0;
		int exclude = 0;
		if (coins[i - 1] <= amount) {
			include = solve(i, coins, amount - coins[i - 1], dp);
		}
		exclude = solve(i - 1, coins, amount, dp);

		return dp[i][amount] = include + exclude;
	}
public:
	int change(int amount, vector<int>& coins) {
		int n = coins.size();
		vector<vector<int>> dp(n + 1, vector<int>(amount + 1, -1));
		return solve(n, coins, amount, dp);
	}
};

// Bottom Up : Tabulation
class Solution3 {
public:
	int change(int amount, vector<int>& coins) {
		int N = coins.size();
		vector<vector<int>> dp(N + 1, vector<int>(amount + 1, -1));
		
		for (int n = 0; n <= coins.size(); n++) {
			for (int amt = 0; amt <= amount; amt++) {
				if (amt == 0)
					dp[n][amt] = 1;

				else if (amt < 0 || n == 0)
					dp[n][amt] = 0;
				
				else {
					int include = 0;
					int exclude = 0;
					if (coins[n - 1] <= amt) {
						include = dp[n][amt - coins[n - 1]];
					}
					exclude = dp[n - 1][amt];

					dp[n][amt] = include + exclude;
				}				
			}
		}
		return dp[N][amount];
	}
};

int main() {
	Solution3 obj;
	int amount = 5;
	vector<int> coins = {1, 2, 5};
	cout << obj.change(amount, coins) << endl;
	return 0;
}