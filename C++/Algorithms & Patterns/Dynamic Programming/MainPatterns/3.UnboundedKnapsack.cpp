#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given a knapsack with a fixed capacity and a set of n items, where each item has an associated 
	value val[i] and weight wt[i], determine the maximum profit that can be obtained by filling the 
	knapsack. Each item can be selected an unlimited number of times.

	Note: We can either include an item completely or exclude it entirely - we cannot
		  include a fraction of an item.

	Examples:
	---------
	Input: capacity = 100, val[]  = [1, 30], wt[] = [1, 50]
	Output: 100  
	Explanation: There are many ways to fill knapsack. 
	Option 1: 2 instances of 50 unit weight item. 
	Option 2: 100 instances of 1 unit weight item. 
	Option 3: 1 instance of 50 unit weight item and 50 instances of 1 unit weight items. 
	We get maximum value with option 2.  

	Input: capacity = 8, val[] = [10, 40, 50, 70], wt[]  = [1, 3, 4, 5]        
	Output : 110
	Explanation: We get maximum value with one unit of weight 5 and one unit of weight 3.


	Approach:
	---------
		for every item, we have two choices

			1. Include the current item (if its weight is less than or equal to the current capacity)
			   in the knapsack and recur for remaining items. Donot exclude the current item.
			2. Exclude the current item from the knapsack and recur for remaining items

			Base Case:
			if no items left or capacity becomes 0
				then profit is 0
*/

// Backward Traversal of Input. Results bubble up from Recursion Tree leaf
class Solution1 {
private:
	//what is the max profit i can get if I have W max weight and N items.
	int solve(int N, vector<int>& weight, vector<int>& value, int W) {
		//base case: if no items left or capacity becomes 0
		//           then we can make 0 profit
		if (N == 0 || W == 0)
			return 0;

		int include = 0;
		int exclude = 0;

		// As we are traversing backwards, the current item under consideration
		// is at index N-1

		// Case 1. Include current item `p[n-1]` in the knapsack.
		// donot exclude the current item. Recurse for remaining item with decreased capacity.
		if (weight[N - 1] <= W) {
			include = value[N - 1] + solve(N - 1, weight, value, W - weight[N - 1]);
		}

		// Case 2. Exculde current item `p[n-1]` in the knapsack and recur for
		// remaining items `n-1` with same capacity `W`		
		exclude = solve(N - 1, weight, value, W);

		// return maximum profit we get by including or excluding current item
		return max(include, exclude);
	}

public:
	int ZeroOneKnapsackUnbounded(vector<int>& weight, vector<int>& value, int W) {
		int N = weight.size();
		return solve(N, weight, value, W);
	}
};

// Backward Traversal of Input. Results bubble up from Recursion Tree leaf
class Solution2 {
private:
	//what is the max profit i can get if I have W max weight and N items.
	int solve(int N, vector<int>& weight, vector<int>& value, int W, vector<vector<int>>& memo) {
		//base case: if no items left or capacity becomes 0
		//           then we can make 0 profit
		if (N == 0 || W == 0)
			return memo[N][W] = 0;

		// Check the cache
		if (memo[N][W] != -1) {
			return memo[N][W];
		}

		int include = 0;
		int exclude = 0;

		// As we are traversing backwards, the current item under consideration
		// is at index N-1

		// Case 1. Include current item `p[n-1]` in the knapsack.
		// donot exclude the current item. Recurse for remaining item with decreased capacity.
		if (weight[N - 1] <= W) {
			include = value[N - 1] + solve(N - 1, weight, value, W - weight[N - 1], memo);
		}

		// Case 2. Exculde current item `p[n-1]` in the knapsack and recur for
		// remaining items `n-1` with same capacity `W`
		exclude = solve(N - 1, weight, value, W, memo);

		// return maximum profit we get by including or excluding current item
		return memo[N][W] = max(include, exclude);
	}

public:
	int ZeroOneKnapsackUnbounded(vector<int>& weight, vector<int>& value, int W) {
		// i and W are changing states. So we need a 2D cache
		// i from 0 to N
		// W from W to 0
		int N = weight.size();

		// -1 : not visited, any other value: result already computed and stored
		vector<vector<int>> memo(N + 1, vector<int>(W + 1, -1));
		return solve(N, weight, value, W, memo);
	}
};

class Solution3 {
public:
	int ZeroOneKnapsackUnbounded(vector<int>& weight, vector<int>& value, int W) {
		int N = weight.size();

		// dp[n][w] stores the maximum profit that can be obtained by using
		// first n items and weight w
		vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));

		// fill the dp table in a bottom-up manner
		for (int n = 0; n <= N; n++) {
			for (int w = 0; w <= W; w++) {
				// Base Case: if no items left or capacity becomes 0
				//            then we can make 0 profit
				if (n == 0 || w == 0)
					dp[n][w] = 0;

				else {
					int include = 0;
					int exclude = 0;

					// Case	1. Include the current item `i` in the knapsack if its weight
					//         doesn't exceed the knapsack capacity `w`
					if (weight[n - 1] <= w) {
						include = value[n - 1] + dp[n][w - weight[n - 1]];
					}

					// Case 2. Exclude the current item `i` from the knapsack
					//         The profit will be the same as for the previous item `i-1`
					exclude = dp[n - 1][w];

					dp[n][w] = max(include, exclude);
				}
			}
		}

		// Return the maximum profit that can be obtained by using all the items
		// and the given knapsack capacity
		return dp[N][W];
	}
};

int main() {
	Solution1 obj1;
	vector<int> weight = { 1, 3, 4, 5 };
	vector<int> value = { 10, 40, 50, 70 };
	cout << obj1.ZeroOneKnapsackUnbounded(weight, value, 8) << endl;

	Solution2 obj2;
	weight = { 1, 3, 4, 5 };
	value = { 10, 40, 50, 70 };
	cout << obj2.ZeroOneKnapsackUnbounded(weight, value, 8) << endl;

	Solution3 obj3;
	weight = { 1, 3, 4, 5 };
	value = { 10, 40, 50, 70 };
	cout << obj3.ZeroOneKnapsackUnbounded(weight, value, 8) << endl;

	return 0;
}

