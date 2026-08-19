#include <bits/stdc++.h>
using namespace std;

/*
    You are given an integer array coins representing coins of different denominations 
    and an integer amount representing a total amount of money.

    Return the number of combinations that make up that amount. If that amount of money 
    cannot be made up by any combination of the coins, return 0.

    You may assume that you have an infinite number of each kind of coin.

    The answer is guaranteed to fit into a signed 32-bit integer.

    Example 1:
    Input: amount = 5, coins = [1,2,5]
    Output: 4
    Explanation: there are four ways to make up the amount:
    5=5
    5=2+2+1
    5=2+1+1+1
    5=1+1+1+1+1

    Example 2:
    Input: amount = 3, coins = [2]
    Output: 0
    Explanation: the amount of 3 cannot be made up just with coins of 2.

    Example 3:
    Input: amount = 10, coins = [10]
    Output: 1
    
    Constraints:
    1 <= coins.length <= 300
    1 <= coins[i] <= 5000
    All the values of coins are unique.
    0 <= amount <= 5000

*/

class Solution {
    //number of combinations possible for (N, amount)
    int changeRecursive(vector<int> &coins, int N, int amount){
        //if the amount is 0 and number of coins is 0, then there is 1 way possible (by not selecting any coin)
        if(N == 0 && amount == 0)
            return 1;

        //if the amount is not 0 and the number of coins !=0, then there are no way possible
        if(N == 0 && amount != 0)
            return 0;
        
        int include = 0, exclude = 0;
        if(coins[N-1]<=amount)
            include = changeRecursive(coins, N, amount-coins[N-1]);
        exclude = changeRecursive(coins, N-1, amount);

        return include + exclude;
    }

    //number of combinations possible for (N, amount)
    int changeTopDown(vector<int> &coins, int N, int amount, unordered_map<string, int> &lookup){
        //if the amount is 0 and number of coins is 0, then there is 1 way possible (by not selecting any coin)
        if(N == 0 && amount == 0)
            return 1;

        //if the amount is not 0 and the number of coins !=0, then there are no way possible
        if(N == 0 && amount != 0)
            return 0;
        
        string key = to_string(N) + " " + to_string(amount);
        if(lookup.find(key) != lookup.end())
            return lookup[key];

        int include = 0, exclude = 0;
        if(coins[N-1]<=amount)
            include = changeTopDown(coins, N, amount-coins[N-1], lookup);
        exclude = changeTopDown(coins, N-1, amount, lookup);
        
        lookup[key] = include + exclude;
        return lookup[key];
    }

    int coinChangeBottomDown(vector<int> &coins, int N, int amount){
        vector<vector<int>> dp(N+1, vector<int>(amount+1));

        for(int n=0; n<=N; n++){
            for(int am=0; am<=amount; am++){
                if(n == 0 && am == 0)
                    dp[n][am] = 1;
                else if(n == 0 && am != 0)
                    dp[n][am] = 0;
                else{
                    int include = 0, exclude = 0;
                    if(coins[n-1]<=am)
                        include = dp[n][am-coins[n-1]];
                    exclude = dp[n-1][am];

                    dp[n][am] = include + exclude;
                }
            }
        }

        return dp[N][amount];
    }
public:
    int change(int amount, vector<int>& coins) {
        int N = coins.size();
        unordered_map<string, int> lookup;
        // return changeRecursive(coins, N, amount);
        // return changeTopDown(coins, N, amount, lookup);
        return coinChangeBottomDown(coins, N, amount);
    }
};


int main(){
    Solution obj;
    vector<int> coins = {1,2,5};
    cout<<obj.change(5, coins)<<endl;   //4

    coins = {2};
    cout<<obj.change(3, coins)<<endl;   //0

    coins = {10};
    cout<<obj.change(10, coins)<<endl;   //1

    return 0;
}