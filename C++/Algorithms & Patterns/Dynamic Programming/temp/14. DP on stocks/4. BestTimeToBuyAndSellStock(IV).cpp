#include <algorithm>
#include <iostream>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement:
    -----------------
    You are given an integer array prices where prices[i] is the price of a given
    stock on the ith day, and an integer k.
    Find the maximum profit you can achieve. You may complete at most k transactions:
    i.e. you may buy at most k times and sell at most k times.

    Note: You may not engage in multiple transactions simultaneously (i.e., you must
    sell the stock before you buy again).

    Examples:
    ---------
    Example 1:
    Input: k = 2, prices = [2,4,1]
    Output: 2
    Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.

    Example 2:
    Input: k = 2, prices = [3,2,6,5,0,3]
    Output: 7
    Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.

    Constraints:
    ------------
    1 <= k <= 100
    1 <= prices.length <= 1000
    0 <= prices[i] <= 1000

    Approach:
    --------
    State: (index, canBuy, transactionsLeft)
      - index: current day (0 to n-1)
      - canBuy: 1 = can buy, 0 = holding (can sell)
      - transactionsLeft: 0 to k

    solve(i, canBuy, txLeft):
      if i == n or txLeft == 0: return 0

      if canBuy == 1:
        buy  = -prices[i] + solve(i+1, 0, txLeft)
        skip = solve(i+1, 1, txLeft)
        return max(buy, skip)

      else:
        sell = prices[i] + solve(i+1, 1, txLeft - 1)
        skip = solve(i+1, 0, txLeft)
        return max(sell, skip)
*/


class Solution {
    int maxProfitRecursive(vector<int>& prices, int i, bool canIBuyOnIthDay, int transactionsLeft) {
        // Base Case : No days left
        if (i == prices.size())
            return 0;

        // Base Case : No more transactions left
        if (transactionsLeft == 0)
            return 0;

        int profitOnIthDay = 0;
        //If I can buy on ith day
        if (canIBuyOnIthDay == true) {
            //if we choose to buy
            int profitOnIthDayIfIBuy = -prices[i] + maxProfitRecursive(prices, i + 1, false, transactionsLeft);
            //if we choose not to buy
            int profitOnIthDayIfIDontBuy = 0 + maxProfitRecursive(prices, i + 1, true, transactionsLeft);
            profitOnIthDay = max(profitOnIthDayIfIBuy, profitOnIthDayIfIDontBuy);
        }
        else {
            //if we choose to sell
            int profitOnIthDayIfISell = prices[i] + maxProfitRecursive(prices, i + 1, true, transactionsLeft - 1);
            //if we choose not to sell
            int profitOnIthDayIfIDontSell = 0 + maxProfitRecursive(prices, i + 1, false, transactionsLeft);
            profitOnIthDay = max(profitOnIthDayIfISell, profitOnIthDayIfIDontSell);
        }
        return profitOnIthDay;
    }

    int maxProfitTopDown(vector<int>& prices, int i, bool canIBuyOnIthDay, int transactionsLeft, unordered_map<string, int>& lookup) {
        // Base Case : No days left
        if (i == prices.size())
            return 0;
        
        // Base Case : No more transactions left
        if (transactionsLeft == 0)
            return 0;

        string key = to_string(i) + " " + to_string(canIBuyOnIthDay) + " " + to_string(transactionsLeft);
        if (lookup.find(key) != lookup.end())
            return lookup[key];

        int profitOnIthDay = 0;
        //If I can buy on ith day
        if (canIBuyOnIthDay == true) {
            //if we choose to buy
            int profitOnIthDayIfIBuy = -prices[i] + maxProfitTopDown(prices, i + 1, false, transactionsLeft, lookup);
            //if we choose not to buy
            int profitOnIthDayIfIDontBuy = 0 + maxProfitTopDown(prices, i + 1, true, transactionsLeft, lookup);
            profitOnIthDay = max(profitOnIthDayIfIBuy, profitOnIthDayIfIDontBuy);
        }
        else {
            //if we choose to sell
            int profitOnIthDayIfISell = prices[i] + maxProfitTopDown(prices, i + 1, true, transactionsLeft - 1, lookup);
            //if we choose not to sell
            int profitOnIthDayIfIDontSell = 0 + maxProfitTopDown(prices, i + 1, false, transactionsLeft, lookup);
            profitOnIthDay = max(profitOnIthDayIfISell, profitOnIthDayIfIDontSell);
        }
        return lookup[key] = profitOnIthDay;
    }

    int maxProfitTopDown2(vector<int>& prices, int i, bool canIBuyOnIthDay, int transactionsLeft, vector<vector<vector<int>>> &dp) {
        // Base Case : No days left
        if (i == prices.size())
            return 0;

        // Base Case : No more transactions left
        if (transactionsLeft == 0)
            return 0;

        if(dp[i][canIBuyOnIthDay][transactionsLeft] != -1)
            return dp[i][canIBuyOnIthDay][transactionsLeft];

        int profitOnIthDay = 0;
        //If I can buy on ith day
        if (canIBuyOnIthDay == true) {
            //if we choose to buy
            int profitOnIthDayIfIBuy = -prices[i] + maxProfitTopDown2(prices, i + 1, false, transactionsLeft, dp);
            //if we choose not to buy
            int profitOnIthDayIfIDontBuy = 0 + maxProfitTopDown2(prices, i + 1, true, transactionsLeft, dp);
            profitOnIthDay = max(profitOnIthDayIfIBuy, profitOnIthDayIfIDontBuy);
        }
        else {
            //if we choose to sell
            int profitOnIthDayIfISell = prices[i] + maxProfitTopDown2(prices, i + 1, true, transactionsLeft - 1, dp);
            //if we choose not to sell
            int profitOnIthDayIfIDontSell = 0 + maxProfitTopDown2(prices, i + 1, false, transactionsLeft, dp);
            profitOnIthDay = max(profitOnIthDayIfISell, profitOnIthDayIfIDontSell);
        }
        return dp[i][canIBuyOnIthDay][transactionsLeft] = profitOnIthDay;
    }


    int maxProfitBottomUp(vector<int>& prices, int K) {
        int N = prices.size();
        vector<vector<vector<int>>> dp(N + 1, vector<vector<int>>(2, vector<int>(K + 1, 0)));

        //dp[i][j][k] : represents on ith day if we can do jth action(0: buy, 1: sell) with at max k transactions 
        for (int i = N; i >= 0; i--) {
            for (int canIBuyOnIthDay = 0; canIBuyOnIthDay <= 1; canIBuyOnIthDay++) {
                for (int maxTransaction = 0; maxTransaction <= K; maxTransaction++) {
                    if (i == N)
                        dp[i][canIBuyOnIthDay][maxTransaction] = 0;

                    else if (maxTransaction == 0)
                        dp[i][canIBuyOnIthDay][maxTransaction] = 0;

                    else {
                        int profitOnIthDay = 0;
                        //If I can buy on ith day
                        if (canIBuyOnIthDay == 1) {
                            //if we choose to buy
                            int profitOnIthDayIfIBuy = -prices[i] + dp[i + 1][0][maxTransaction];
                            //if we choose not to buy
                            int profitOnIthDayIfIDontBuy = 0 + dp[i + 1][1][maxTransaction];
                            profitOnIthDay = max(profitOnIthDayIfIBuy, profitOnIthDayIfIDontBuy);
                        }
                        else {
                            //if we choose to sell
                            int profitOnIthDayIfISell = prices[i] + dp[i + 1][1][maxTransaction - 1];
                            //if we choose not to sell
                            int profitOnIthDayIfIDontSell = 0 + dp[i + 1][0][maxTransaction];
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
        int n = prices.size();
        int transactionsLeft = K;
        //return maxProfitRecursive(prices, 0, true, transactionsLeft);

        // Top Down Approach 1:
        // unordered_map<string, int> lookup;
        // return maxProfitTopDown(prices, 0, true, transactionsLeft, lookup);


        // Top Down Approach 2:
        // dp[i][canBuy][txLeft] — n days × 2 states × (k+1) tx states
        // why k + 1 ? 
        // because tx can be from 0 to k (k+1 values)
        // vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(K + 1, -1)));
        // return maxProfitTopDown2(prices, 0, true, transactionsLeft, dp);

        return maxProfitBottomUp(prices, K);
    }
};


int main() {
    Solution obj;
    vector<int> prices = { 2,4,1 };
    cout << obj.maxProfit(prices, 2) << endl;           //2

    prices = { 3,2,6,5,0,3 };
    cout << obj.maxProfit(prices, 2) << endl;           //7
}
