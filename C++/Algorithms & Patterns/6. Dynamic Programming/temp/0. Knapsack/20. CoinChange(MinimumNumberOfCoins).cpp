#include <bits/stdc++.h>
using namespace std;

/*
    Given an array of coins[] of size n and a target value sum, where coins[i] 
    represent the coins of different denominations. You have an infinite supply 
    of each of the coins. The task is to find the minimum number of coins required 
    to make the given value sum. If it’s not possible to make a change, return -1.

    Examples:  
    Input: coins[] = [25, 10, 5], sum = 30
    Output: 2
    Explanation : Minimum 2 coins needed, 25 and 5  

    Input: coins[] = [9, 6, 5, 1], sum = 19
    Output: 3
    Explanation: 19 = 9 + 9 + 1

    Input: coins[] = [5, 1], sum = 0
    Output: 0
    Explanation: For 0 sum, we do not need a coin

    Input: coins[] = [4, 6, 2], sum = 5
    Output: -1
    Explanation: Not possible to make the given sum.
*/

class Solution{
    int minNumberOfCoinsRecursive(vector<int> &coins, int N, int sum){
        //if there are no coins and the sum to be made is 0 then min coins required is 0.
        if(N == 0 && sum == 0)
            return 0;

        //if there are no coins and the sum to be made is 0 then min coins required is 0.
        if(N == 0 && sum != 0)
            return INT_MAX-1;       //Indicates Not possible. 
                                    //INT_MAX - 1 prevents overflow when adding 1 in 1 + recursive_call() during inclusion.
        
        int include = INT_MAX-1, exclude = INT_MAX-1;
        if(coins[N-1] <= sum)
            include = 1 + minNumberOfCoinsRecursive(coins, N, sum - coins[N-1]);        //since we are including the coin, do 1 + call()
        exclude = minNumberOfCoinsRecursive(coins, N-1, sum);
        return min(include, exclude);
    }

    int minNumberOfCoinsTopDown(vector<int> &coins, int N, int sum, unordered_map<string, int> &lookup){
        if(N == 0 && sum == 0)
            return 0;

        if(N == 0 && sum != 0)
            return INT_MAX-1;       //Indicates Not possible. 
                                    //INT_MAX - 1 prevents overflow when adding 1 in 1 + recursive_call() during inclusion.
        
        string key = to_string(N) + " " + to_string(sum);
        if(lookup.find(key)!=lookup.end())
            return lookup[key];

        int include = INT_MAX-1, exclude = INT_MAX-1;
        if(coins[N-1]<=sum)
            include = 1 + minNumberOfCoinsRecursive(coins, N, sum - coins[N-1]);
        exclude = minNumberOfCoinsRecursive(coins, N-1, sum);
        
        lookup[key] =  min(include, exclude);
        return lookup[key];
    }

    int minNumberOfCoinsBottomUp(vector<int> &coins, int N, int target){
        vector<vector<int>> dp(N+1, vector<int>(target+1));

        for(int n=0; n<=N; n++){
            for(int sum=0; sum<=target; sum++){
                if(n == 0 && sum == 0)
                    dp[n][sum] = 0;
                else if(n ==0 && sum!=0)
                    dp[n][sum] = INT_MAX-1;
                else{
                    int include = INT_MAX-1, exclude = INT_MAX-1;
                    if(coins[n-1] <= sum)
                        include = 1 + dp[n][sum-coins[n-1]];
                    exclude = dp[n-1][sum];

                    dp[n][sum] = min(include, exclude);
                }
            }
        }
        return dp[N][target] == INT_MAX-1 ? -1 : dp[N][target];
    }

public:
    int minNumberOfCoins(vector<int> &coins, int sum){
        int N = coins.size();
        unordered_map<string, int> lookup;
        // int res = minNumberOfCoinsRecursive(coins, N, sum);
        // int res = minNumberOfCoinsTopDown(coins, N, sum, lookup);
        // return (res == INT_MAX - 1 ) ? -1 : res;
        return minNumberOfCoinsBottomUp(coins, N, sum);
    }
};

int main(){
    Solution obj;
    vector<int> coins = {25, 10, 5};
    cout<<obj.minNumberOfCoins(coins, 30)<<endl;        //2 (25, 5)

    coins = {9, 6, 5, 1};
    cout<<obj.minNumberOfCoins(coins, 19)<<endl;        //3 (9, 9, 1)

    coins = {5, 1};
    cout<<obj.minNumberOfCoins(coins, 0)<<endl;         //0 For 0 sum, we do not need a coin

    coins = {4, 6, 2};
    cout<<obj.minNumberOfCoins(coins, 5)<<endl;         //-1

    return 0;
}