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
	https://www.youtube.com/watch?v=WeO_E5Q1kGw
	Problem Statement:
	------------------	
	You are given an integer array cost where cost[i] is the cost of ith step on a staircase. 
	Once you pay the cost, you can either climb one or two steps.
	
	You can either start from the step with index 0, or the step with index 1.
	
	Return the minimum cost to reach the top of the floor.
	
	Examples:
	---------
	Input: cost = [10,15,20]
	Output: 15
	Explanation: You will start at index 1.
	- Pay 15 and climb two steps to reach the top.
	The total cost is 15.


	Input: cost = [1,100,1,1,1,100,1,1,100,1]
	Output: 6
	Explanation: You will start at index 0.
	- Pay 1 and climb two steps to reach index 2.
	- Pay 1 and climb two steps to reach index 4.
	- Pay 1 and climb two steps to reach index 6.
	- Pay 1 and climb one step to reach index 7.
	- Pay 1 and climb two steps to reach index 9.
	- Pay 1 and climb one step to reach the top.
	The total cost is 6.

	Constraints:
	------------
	2 <= cost.length <= 1000
	0 <= cost[i] <= 999

	Approach:
	--------
	costs = [10, 15]
					  step n	
				     --------
	step (n-1) 15   | 
			   -----
step (n-2) 10 |
		------
	    | 

	here n = 2.
		At each step, we can reach that step from either previous step or previous to previous step.
		we can reach step n from n-1th step or n-2th step.
			minCostToReach(n)   = min(15 + minCostToReach(n-1) , 10 + minCostToReach(n-2))
			minCostToReach(n-1) = 0. Because (n-1) is (2-1) = 1. We can either start from step 0 or step 1.
								     To keep the cost minimum, since we are at step 1, we will start from here.

			minCostToReach(n-2) = 0. Because (n-2) is (2-2) = 0. We can either start from step 0 or step 1.
									 To keep the cost minimum, since we are at step 0, we will start from here.

			Hence, minCostToReach(n)   = min(15 + minCostToReach(n-1) , 10 + minCostToReach(n-2))
									   = min(15 + 0, 10 + 0)
									   = min(15, 10)
									   = 10


			Recurrence : 
				minCostToReach(n)   = min(cost[n-1] + minCostToReach(n-1) , cost[n-2] + minCostToReach(n-2))
	TC: O(2^N)	
*/

class Solution1 {
private:
	int solve(int i, vector<int> &cost) {
		// Base Case: We can start from either 0th step or 1st step
		// So if we start from 0th step, the min cost will be 0
		if(i==0)
			return 0;

		// if we start from 1st step, the min cost will be 0
		if (i == 1)
			return 0;

		// We can reach the ith step from either (i-1)th step or (i-2)th step
		int costFromStepIMinus1 = cost[i - 1] + solve(i - 1, cost);
		int costFromStepIMinus2 = cost[i - 2] + solve(i - 2, cost);

		// return the minimum of the two costs.
		return min(costFromStepIMinus1, costFromStepIMinus2);
	}
public:
	int minCostClimbingStairs(vector<int>& cost) {
		int n = cost.size();
		return solve(n, cost);
	}
};

class Solution2 {
private:
	int solve(int i, vector<int>& cost, vector<int> &dp) {
		// Base Case: We can start from either 0th step or 1st step
		// So if we start from 0th step, the min cost will be 0
		if (i == 0)
			return dp[i] = 0;

		// if we start from 1st step, the min cost will be 0
		if (i == 1)
			return dp[i] = 0;

		if (dp[i] != -1)
			return dp[i];

		// We can reach the ith step from either (i-1)th step or (i-2)th step
		int costFromStepIMinus1 = cost[i - 1] + solve(i - 1, cost, dp);
		int costFromStepIMinus2 = cost[i - 2] + solve(i - 2, cost, dp);

		// return the minimum of the two costs.
		return dp[i] = min(costFromStepIMinus1, costFromStepIMinus2);
	}

public:
	int minCostClimbingStairs(vector<int>& cost) {
		int n = cost.size();
		vector<int> dp(n + 1, -1);
		return solve(n, cost, dp);
	}
};

class Solution3 {
public:
	int minCostClimbingStairs(vector<int>& cost) {
		int n = cost.size();

		// dp[i] = minimum cost to reach the ith step
		vector<int> dp(n + 1, -1);

		dp[0] = 0;
		dp[1] = 0;

		for (int i = 2; i <= n; i++) {
			int costFromStepIMinus1 = cost[i - 1] + dp[i - 1];
			int	costFromStepIMinus2 = cost[i - 2] + dp[i - 2];

			dp[i] = min(costFromStepIMinus1, costFromStepIMinus2);
		}

		return dp[n];
	}
};

int main() {
    Solution3 obj;
	vector<int> cost = {10, 15, 20};
	cout << obj.minCostClimbingStairs(cost) << "\n";

	return 0;
}