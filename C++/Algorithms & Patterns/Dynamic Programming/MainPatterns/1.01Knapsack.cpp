#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

/*
	https://www.youtube.com/watch?v=97ogFz0NkAo

	Problem Statement: 
	-----------------
	Given two arrays, val[] and wt[], where each element represents the value and 
	weight of an item respectively, also given an integer W representing the maximum 
	capacity of the knapsack (the total weight it can hold).
	
	Put the items into the knapsack such that the sum of values associated with them 
	is the maximum possible, without exceeding the capacity W.

	Note: We can either include an item completely or exclude it entirely - we cannot 
		  include a fraction of an item.

	Examples:
	---------
	Input:  W = 4, val[] = [1, 2, 3], wt[] = [4, 5, 1]
	Output: 3
	Explanation: There are two items with weight less than or equal to 4. If we select the item with weight 4, 
	the possible value is 1, and if we select the item with weight 1, the possible value is 3. 
	Hence, the maximum possible value is 3. We cannot put both items with weights 4 and 1 together because 
	the capacity of the bag is 4.

	Input: W = 3, val[] = [1, 2, 3], wt[] = [4, 5, 6]
	Output: 0 
	Explanation: All the item weights are greater than the knapsack capacity.

	
	Approach:
	---------
		for every item, we have two choices

			1. Include the current item (if its weight is less than or equal to the current capacity)
			   in the knapsack and recur for remaining items
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
		
		// Case 1. Include current item `p[n-1]` in the knapsack and recur for
		// remaining items with decreased capacity `W-w[n-1]`
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
	int ZeroOneKnapsack(vector<int>& weight, vector<int>& value, int W) {
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
		
		// Case 1. Include current item `p[n-1]` in the knapsack and recur for
		// remaining items with decreased capacity `W-w[n-1]`
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
	int ZeroOneKnapsack(vector<int>& weight, vector<int>& value, int W) {
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
	int ZeroOneKnapsack(vector<int>& weight, vector<int>& value, int W) {
		int N = weight.size();

		// dp[n][w] stores the maximum profit that can be obtained by using
		// first n items and weight w
		vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));

		// fill the dp table in a bottom-up manner
		for (int n = 0; n <= N; n++) {
			for (int w = 0; w <= W; w++) {
				// Base Case: if no items left or capacity becomes 0
				//            then we can make 0 profit
				if(n == 0 || w == 0)
					dp[n][w] = 0;
				
				else {
					int include = 0;
					int exclude = 0;

					// Case	1. Include the current item `i` in the knapsack if its weight
					//         doesn't exceed the knapsack capacity `w`
					if (weight[n - 1] <= w) {
						include = value[n - 1] + dp[n - 1][w - weight[n - 1]];
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
	vector<int> weight = { 4, 5, 1 };
	vector<int> value = { 1, 2, 3 };
	cout << obj1.ZeroOneKnapsack(weight, value, 4)<<endl;

	Solution2 obj2;
	weight = { 4, 5, 1 };
	value = { 1, 2, 3 };
	cout << obj2.ZeroOneKnapsack(weight, value, 4) << endl;

	Solution3 obj3;
	weight = { 4, 5, 1 };
	value = { 1, 2, 3 };
	cout << obj3.ZeroOneKnapsack(weight, value, 4) << endl;

	return 0;
}

