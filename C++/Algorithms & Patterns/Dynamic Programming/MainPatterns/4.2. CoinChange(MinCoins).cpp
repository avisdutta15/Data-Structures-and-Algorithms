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
	
	Return the fewest number of coins that you need to make up that amount. 
	If that amount of money cannot be made up by any combination of the coins, return -1.
	
	You may assume that you have an infinite number of each kind of coin.
	
	Examples:
	---------
	Input: coins = [1,2,5], amount = 11
	Output: 3
	Explanation: 11 = 5 + 5 + 1

	Input: coins = [2], amount = 3
	Output: -1

	Input: coins = [1], amount = 0
	Output: 0


	Constraints:
	------------
	1 <= coins.length <= 12
	1 <= coins[i] <= 2^31 - 1
	0 <= amount <= 10^4

	Approach:
	--------
	Unbounded Knapsack Pattern

	solve(i, coins, amount) : = Minimum number of coins to make amount using coins from i to n
		// if amount is 0 then there is no way
		if(amout == 0)
			return 0;

		// if not possible then send INT_MAX signalling not possible
		if(amount < 0 || i == 0) 
			return INT_MAX;
		
		int include = INT_MAX;
		if(coins[i] <= amount)
			int take = solve(i, coins, amount - coins[i]);
			if(take != INT_MAX)
				include = 1 + take;
		
		int exclude = solve(i-1, coins, amount)
		return min(include, exclude);


	Why do we send INT_MAX in case of not possible? 
		if(amount < 0 || i == 0) 
			return INT_MAX;
	
	We return INT_MAX (which acts as infinity) when we hit an invalid state—like running out 
	of coins (i == 0) while still having an amount left over, or if the amount drops below zero.
	
	Here is exactly why we use INT_MAX instead of -1 or 0:
	Because the recursive function evaluates both the include and exclude choices and 
	then takes the minimum of the two using min(include, exclude), returning a small 
	number for a failed path would ruin the math:
		- If a failed path returned 0, then min(valid_path_cost, 0) would equal 0. 
		  The algorithm would falsely think it found a magical way to make the amount using 0 coins!
		- If a failed path returned -1, then min(valid_path_cost, -1) would pick -1, 
		  completely corrupting the minimum count.

	By returning INT_MAX, we are essentially saying: 
		"This path is a dead end and costs an infinite amount of coins."
*/

// Recusion
class Solution1 {
	int solve(int i, vector<int>& coins, int amount) {
		// Base Case 1: Target reached! 
		// If the remaining amount is exactly 0, it takes exactly 0 coins to make it.
		if (amount == 0)
			return 0;

		// Base Case 2: Out of options!
		// If we run out of coin types (amount < 0 || i == 0), 
		// it's impossible to make this amount. We return INT_MAX as a failure signal.
		if (amount < 0 || i == 0)
			return INT_MAX;

		int include = INT_MAX;
		int exclude = INT_MAX;

		// Choice 1: INCLUDE the current coin (coins[i - 1])
		// We can only pick this coin if its value is less than or equal to the remaining amount.
		if (coins[i - 1] <= amount) {

			//	Only add 1 if the sub-problem was actually solvable
			//	This prevents INT_MAX + 1 overflow
			int take = solve(i, coins, amount - coins[i - 1]);
			if (take != INT_MAX)
				include = 1 + take;
		}

		// Choice 2: EXCLUDE the current coin
		// We give up on picking coins[i - 1] and move to the remaining (i - 1) coins.
		exclude = solve(i - 1, coins, amount);

		return min(include, exclude);
	}

public:
	int coinChange(vector<int>& coins, int amount) {
		int n = coins.size();
		int ans = solve(n, coins, amount);
		return ans == INT_MAX ? -1 : ans;
	}
};

// Top Down : Memoization
class Solution2 {
	int solve(int i, vector<int>& coins, int amount, vector<vector<int>>& cache) {
		// Base Case 1: Target reached! 
		// If the remaining amount is exactly 0, it takes exactly 0 coins to make it.
		if (amount == 0)
			return cache[i][amount] = 0;

		// Base Case 2: Out of options!
		// If we run out of coin types (amount < 0 || i == 0), 
		// it's impossible to make this amount. We return INT_MAX as a failure signal.
		if (amount < 0 || i == 0)
			return cache[i][amount] = INT_MAX;


		// Check if already computed
		if (cache[i][amount] != -1)
			return cache[i][amount];

		int include = INT_MAX;
		int exclude = INT_MAX;

		// Choice 1: INCLUDE the current coin (coins[i - 1])
		// We can only pick this coin if its value is less than or equal to the remaining amount.
		if (coins[i - 1] <= amount) {

			//	Only add 1 if the sub-problem was actually solvable
			//	This prevents INT_MAX + 1 overflow
			int take = solve(i, coins, amount - coins[i - 1], cache);
			if (take != INT_MAX)
				include = 1 + take;
		}

		// Choice 2: EXCLUDE the current coin
		// We give up on picking coins[i - 1] and move to the remaining (i - 1) coins.
		exclude = solve(i - 1, coins, amount, cache);

		return cache[i][amount] = min(include, exclude);
	}

public:
	int coinChange(vector<int>& coins, int amount) {
		int n = coins.size();
		vector<vector<int>> cache(n + 1, vector<int>(amount + 1, -1));
		int ans = solve(n, coins, amount, cache);
		return ans == INT_MAX ? -1 : ans;
	}
};

// Bottom Up : Tabulation
class Solution3 {
public:
	int coinChange(vector<int>& coins, int amount) {
		int N = coins.size();
		vector<vector<int>> dp(N + 1, vector<int>(amount + 1, -1));

		for (int n = 0; n <= N; n++) {
			for (int amt = 0; amt <= amount; amt++) {
				// Base Case 1: Target reached! 
				// If the remaining amount is exactly 0, it takes exactly 0 coins to make it.
				if (amt == 0)
					dp[n][amt] = 0;

				// Base Case 2: Out of options!
				// If we run out of coin types (amount < 0 || i == 0), 
				// it's impossible to make this amount. We return INT_MAX as a failure signal.
				else if (amt < 0 || n == 0)
					dp[n][amt] = INT_MAX;

				else {
					int include = INT_MAX;
					int exclude = INT_MAX;

					// Choice 1: INCLUDE the current coin (coins[i - 1])
					// We can only pick this coin if its value is less than or equal to the remaining amount.
					if (coins[n - 1] <= amt) {

						//	Only add 1 if the sub-problem was actually solvable
						//	This prevents INT_MAX + 1 overflow
						int take = dp[n][amt - coins[n - 1]];
						if (take != INT_MAX)
							include = 1 + take;
					}

					// Choice 2: EXCLUDE the current coin
					// We give up on picking coins[i - 1] and move to the remaining (i - 1) coins.
					exclude = dp[n - 1][amt];

					dp[n][amt] = min(include, exclude);
				}				
			}
		}

		int ans = dp[N][amount];
		return ans == INT_MAX ? -1 : ans;
	}
};

int main() {
	Solution3 obj;
	int amount = 5;
	vector<int> coins = {1, 2, 5};
	cout << obj.coinChange(coins, amount) << endl;
	return 0;
}