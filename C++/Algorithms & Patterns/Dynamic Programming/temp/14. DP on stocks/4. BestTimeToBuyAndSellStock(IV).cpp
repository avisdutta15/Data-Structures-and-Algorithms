#include <bits/stdc++.h>
using namespace std;

/*
    You are given an integer array prices where prices[i] is the price of a given 
    stock on the ith day, and an integer k.
    Find the maximum profit you can achieve. You may complete at most k transactions: 
    i.e. you may buy at most k times and sell at most k times.

    Note: You may not engage in multiple transactions simultaneously (i.e., you must 
    sell the stock before you buy again).

    Example 1:
    Input: k = 2, prices = [2,4,1]
    Output: 2
    Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.

    Example 2:
    Input: k = 2, prices = [3,2,6,5,0,3]
    Output: 7
    Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
    
    Constraints:
    1 <= k <= 100
    1 <= prices.length <= 1000
    0 <= prices[i] <= 1000
*/


class Solution{
    int maxProfitRecursive(vector<int>& prices, int i, bool canIBuyOnIthDay, int maxTransactions){
        if(i == prices.size())
            return 0;

        if(maxTransactions == 0)
            return 0;

        int profitOnIthDay = 0;
        //If I can buy on ith day
        if(canIBuyOnIthDay == true){
            //if we choose to buy
            int profitOnIthDayIfIBuy     =  -prices[i] + maxProfitRecursive(prices, i+1, false, maxTransactions);
            //if we choose not to buy
            int profitOnIthDayIfIDontBuy =           0 + maxProfitRecursive(prices, i+1, true, maxTransactions);
            profitOnIthDay = max(profitOnIthDayIfIBuy, profitOnIthDayIfIDontBuy);
        }
        else{
            //if we choose to sell
            int profitOnIthDayIfISell     =  prices[i] + maxProfitRecursive(prices, i+1, true, maxTransactions-1);
            //if we choose not to sell
            int profitOnIthDayIfIDontSell =          0 + maxProfitRecursive(prices, i+1, false, maxTransactions);
            profitOnIthDay = max(profitOnIthDayIfISell, profitOnIthDayIfIDontSell);
        }
        return profitOnIthDay;
    }

    int maxProfitTopDown(vector<int>& prices, int i, bool canIBuyOnIthDay, int maxTransactions, unordered_map<string, int> &lookup){
        if(i == prices.size())
            return 0;

        if(maxTransactions == 0)
            return 0;

        string key = to_string(i) + " " + to_string(canIBuyOnIthDay) + " " + to_string(maxTransactions);
        if(lookup.find(key) != lookup.end())
            return lookup[key];

        int profitOnIthDay = 0;
        //If I can buy on ith day
        if(canIBuyOnIthDay == true){
            //if we choose to buy
            int profitOnIthDayIfIBuy     =  -prices[i] + maxProfitTopDown(prices, i+1, false, maxTransactions, lookup);
            //if we choose not to buy
            int profitOnIthDayIfIDontBuy =           0 + maxProfitTopDown(prices, i+1, true, maxTransactions, lookup);
            profitOnIthDay = max(profitOnIthDayIfIBuy, profitOnIthDayIfIDontBuy);
        }
        else{
            //if we choose to sell
            int profitOnIthDayIfISell     =  prices[i] + maxProfitTopDown(prices, i+1, true, maxTransactions-1, lookup);
            //if we choose not to sell
            int profitOnIthDayIfIDontSell =          0 + maxProfitTopDown(prices, i+1, false, maxTransactions, lookup);
            profitOnIthDay = max(profitOnIthDayIfISell, profitOnIthDayIfIDontSell);
        }
        return lookup[key] = profitOnIthDay;
    }

    int maxProfitBottomUp(vector<int>& prices, int K){
        int N = prices.size();
        vector<vector<vector<int>>> dp(N+1, vector<vector<int>>(2, vector<int>(K+1, 0)));

        //dp[i][j][k] : represents on ith day if we can do jth action(0: buy, 1: sell) with at max k transactions 
        for(int i=N; i>=0; i--){
            for(int canIBuyOnIthDay = 0; canIBuyOnIthDay<=1; canIBuyOnIthDay++){
                for(int maxTransaction = 0; maxTransaction<=K; maxTransaction++){
                    if(i == N)
                        dp[i][canIBuyOnIthDay][maxTransaction] = 0;

                    else if(maxTransaction == 0)
                        dp[i][canIBuyOnIthDay][maxTransaction] = 0;

                    else{
                        int profitOnIthDay = 0;
                        //If I can buy on ith day
                        if(canIBuyOnIthDay == 1){
                            //if we choose to buy
                            int profitOnIthDayIfIBuy     =  -prices[i] + dp[i+1][0][maxTransaction];
                            //if we choose not to buy
                            int profitOnIthDayIfIDontBuy =           0 + dp[i+1][1][maxTransaction];
                            profitOnIthDay = max(profitOnIthDayIfIBuy, profitOnIthDayIfIDontBuy);
                        }
                        else{
                            //if we choose to sell
                            int profitOnIthDayIfISell     =  prices[i] + dp[i+1][1][maxTransaction-1];
                            //if we choose not to sell
                            int profitOnIthDayIfIDontSell =          0 + dp[i+1][0][maxTransaction];
                            profitOnIthDay = max(profitOnIthDayIfISell, profitOnIthDayIfIDontSell);
                        }
                        dp[i][canIBuyOnIthDay][maxTransaction] = profitOnIthDay;
                    }
                }
            }
        }

        return dp[0][1][K];
    }
    public:
        int maxProfit(vector<int>& prices, int K) {
            //return maxProfitRecursive(prices, 0, true, K);

            // unordered_map<string, int> lookup;
            // return maxProfitTopDown(prices, 0, true, K, lookup);

            return maxProfitBottomUp(prices, K);
        }
};


int main(){
    Solution obj;
    vector<int> prices = {2,4,1};
    cout<<obj.maxProfit(prices, 2)<<endl;           //2

    prices = {3,2,6,5,0,3};
    cout<<obj.maxProfit(prices, 2)<<endl;           //7
}