#include <algorithm>
#include <iostream>
#include <set>
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
	Explanation: There are two items with weight less than or equal to 4. If we select the item with weight 4, the possible value is 1, and if we select the item with weight 1, the possible value is 3. Hence, the maximum possible value is 3. We cannot put both items with weights 4 and 1 together because the capacity of the bag is 4.

	Input: W = 3, val[] = [1, 2, 3], wt[] = [4, 5, 6]
	Output: 0 
	Explanation: All the item weights are greater than the knapsack capacity.

	
	Approach:
	---------
	

*/

/////////////////////////////////////  RECURSIVE SOLUTION ////////////////////////////////

// Forward Traversal with Accumulation using global variables
class Solution1Recursion1 {
private:
	void solve(vector<int>& weight, vector<int>& value, int W, int i, int profit, int &maxProfit) {
		if (i == weight.size() || W == 0) {
			maxProfit = max(maxProfit, profit);
			return;
		}

		// include
		if (weight[i] <= W) {
			solve(weight, value, W-weight[i], i+1, profit+value[i], maxProfit);
		}

		// exclude
		solve(weight, value, W, i + 1, profit, maxProfit);
	}

public:
	int ZeroOneKnapsack(vector<int>& weight, vector<int>& value, int W) {
		int maxProfit = 0;
		solve(weight, value, W, 0, 0, maxProfit);
		return maxProfit;
	}
};

// Forward Traversal without Accumulation. Results bubble up
class Solution1Recursion2 {
private:
	int solve(vector<int>& weight, vector<int>& value, int W, int i) {
		if (i >= weight.size() || W == 0) {
			return 0;
		}

		int include = 0;
		int exclude = 0;

		// include
		if (weight[i] <= W) {
			include = value[i] + solve(weight, value, W - weight[i], i + 1);
		}

		// exclude
		exclude = solve(weight, value, W, i + 1);
		
		return max(include, exclude);
	}

public:
	int ZeroOneKnapsack(vector<int>& weight, vector<int>& value, int W) {
		return	solve(weight, value, W, 0);
	}
};

// Backward Traversal. Results bubble up
class Solution1Recursion3 {
private:
	int solve(int N, vector<int>& weight, vector<int>& value, int W) {
		if (N == 0 || W == 0)
			return 0;

		int include = 0;
		int exclude = 0;

		// As we are traversing backwards, the current item under consideration
		// is at index N-1
		// include
		if (weight[N - 1] <= W) {
			include = value[N - 1] + solve(N - 1, weight, value, W - weight[N - 1]);
		}
		// exclude
		exclude = solve(N - 1, weight, value, W);

		return max(include, exclude);
	}

public:
	int ZeroOneKnapsack(vector<int>& weight, vector<int>& value, int W) {
		int N = weight.size();
		return solve(N, weight, value, W);
	}
};

/////////////////////////////////////  MEMOIZATION SOLUTION ////////////////////////////////

// We cannot memoize the Solution1Recursion1 (Forward Traversal with Accumulation using global variables)
// because we are passing maxProfit by reference and that value is not dependent on the subproblems.

// We will memoize the Solution1Recursion2 (Forward Traversal without Accumulation. Results bubble up)
class Solution2Memoization1 {
private:
	int solve(int i, int W, vector<int>& weight, vector<int>& value, vector<vector<int>> &memo) {
		if (i >= weight.size() || W == 0) {
			return memo[i][W] = 0;
		}

		// Check the cache
		if(memo[i][W] != -1)
			return memo[i][W];

		int include = 0;
		int exclude = 0;

		// include
		if (weight[i] <= W) {
			include = value[i] + solve(i + 1, W - weight[i], weight, value, memo);
		}

		// exclude
		exclude = solve(i + 1, W, weight, value, memo);

		return memo[i][W] = max(include, exclude);
	}

public:
	int ZeroOneKnapsack(vector<int>& weight, vector<int>& value, int W) {
		// i and W are changing states.
		// i from 0 to N
		// W from W to 0
		int N = weight.size();
		vector<vector<int>> memo(N+1, vector<int>(W+1, -1));
		return solve(0, W, weight, value, memo);
	}
};

// We will memoize the Solution1Recursion3 (Backward Traversal. Results bubble up)

class Solution2Memoization2 {
private:
	int solve(int N, vector<int>& weight, vector<int>& value, int W, vector<vector<int>>& memo) {
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
		// include
		if (weight[N - 1] <= W) {
			include = value[N - 1] + solve(N - 1, weight, value, W - weight[N - 1], memo);
		}

		// exclude
		exclude = solve(N - 1, weight, value, W, memo);

		return memo[N][W] = max(include, exclude);
	}

public:
	int ZeroOneKnapsack(vector<int>& weight, vector<int>& value, int W) {
		// i and W are changing states.
		// i from 0 to N
		// W from W to 0
		int N = weight.size();
		vector<vector<int>> memo(N + 1, vector<int>(W + 1, -1));
		return solve(N, weight, value, W, memo);
	}
};

/////////////////////////////////////  BOTTOM UP SOLUTION ////////////////////////////////
class Solution3BottomUp1 {
public:
	int ZeroOneKnapsack(vector<int>& weight, vector<int>& value, int W) {
		// i and W are changing states.
		// i from 0 to N
		// W from W to 0
		int N = weight.size();
		vector<vector<int>> dp(N + 1, vector<int>(W + 1, -1));

		for (int n = 0; n <= N; n++) {
			for (int w = 0; w <= W; w++) {

				// Base Case:
				if(n == 0 || w == 0)
					dp[n][w] = 0;

				int include = 0;
				int exclude = 0;

				if (weight[n - 1] <= w) {
					include = value[n-1] + dp[n - 1][w - weight[n - 1]];
				}

				exclude = dp[n - 1][w];

				dp[n][w] = max(include, exclude);
			}
		}

		return dp[N][W];
	}
};

int main() {
	Solution1Recursion1 obj1;
	int W = 4;
	vector<int> value = { 1, 2, 3 };
	vector<int> weight = { 4, 5, 1 };
	cout << obj1.ZeroOneKnapsack(weight, value, W) <<endl;


	W = 3;
	value = { 1, 2, 3 };
	weight = { 4, 5, 6 };
	cout << obj1.ZeroOneKnapsack(weight, value, W) << endl;

	Solution1Recursion2 obj2;
	W = 4;
	value = { 1, 2, 3 };
	weight = { 4, 5, 1 };
	cout << obj2.ZeroOneKnapsack(weight, value, W) << endl;


	W = 3;
	value = { 1, 2, 3 };
	weight = { 4, 5, 6 };
	cout << obj2.ZeroOneKnapsack(weight, value, W) << endl;


	Solution1Recursion3 obj3; 
	W = 4;
	value = { 1, 2, 3 };
	weight = { 4, 5, 1 };
	cout << obj3.ZeroOneKnapsack(weight, value, W) << endl;


	W = 3;
	value = { 1, 2, 3 };
	weight = { 4, 5, 6 };
	cout << obj3.ZeroOneKnapsack(weight, value, W) << endl;

	Solution2Memoization1 obj4; 
	W = 4;
	value = { 1, 2, 3 };
	weight = { 4, 5, 1 };
	cout << obj4.ZeroOneKnapsack(weight, value, W) << endl;


	W = 3;
	value = { 1, 2, 3 };
	weight = { 4, 5, 6 };
	cout << obj4.ZeroOneKnapsack(weight, value, W) << endl;


	Solution2Memoization2 obj5;
	W = 4;
	value = { 1, 2, 3 };
	weight = { 4, 5, 1 };
	cout << obj5.ZeroOneKnapsack(weight, value, W) << endl;


	W = 3;
	value = { 1, 2, 3 };
	weight = { 4, 5, 6 };
	cout << obj5.ZeroOneKnapsack(weight, value, W) << endl;


	Solution3BottomUp1 obj6;
	W = 4;
	value = { 1, 2, 3 };
	weight = { 4, 5, 1 };
	cout << obj5.ZeroOneKnapsack(weight, value, W) << endl;


	W = 3;
	value = { 1, 2, 3 };
	weight = { 4, 5, 6 };
	cout << obj5.ZeroOneKnapsack(weight, value, W) << endl;

	return 0;
}

