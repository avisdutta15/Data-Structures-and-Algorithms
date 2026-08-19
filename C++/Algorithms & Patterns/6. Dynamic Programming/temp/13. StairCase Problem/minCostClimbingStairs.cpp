#include <bits/stdc++.h>
using namespace std;

/*
    On a staircase, the i-th step has some non-negative cost cost[i] assigned (0 indexed).

    Once you pay the cost, you can either climb one or two steps. You need to find minimum 
    cost to reach the top of the floor, and you can either start from the step with index 0, 
    or the step with index 1.

    Example 1:
    Input: cost = [10, 15, 20]
    Output: 15
    Explanation: Cheapest is start on cost[1], pay that cost and go to the top.
    Example 2:
    Input: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
    Output: 6
    Explanation: Cheapest is start on cost[0], and only step on 1s, skipping cost[3].

*/


class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        return min(util(0, cost), util(1, cost));
    }
    
    int util(int i, vector<int>& cost){
        if(i>=cost.size())
            return 0;
        int includeNext = util(i+1, cost);
        int excludeNext = util(i+2, cost);
        return cost[i] + min(includeNext, excludeNext);
    }
};

class Solution2 {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n+1, 0);
        dp[0] = cost[0];
        dp[1] = cost[1];
        
        for(int i=2; i<n; i++){
            dp[i] = cost[i] + min(dp[i-1], dp[i-2]);
        }
        
        dp[n] = min(dp[n-1], dp[n-2]);
        
        return dp[n];
    }
};

int main(){

}