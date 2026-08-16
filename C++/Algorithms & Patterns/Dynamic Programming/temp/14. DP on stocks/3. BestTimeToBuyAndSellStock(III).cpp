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
    https://www.youtube.com/watch?v=-uQGzhYj8BQ&t=713s&pp=ygUdYnV5IGFuZCBzZWxsIHN0b2NrIGxlZXRjb2RlIDM%3D
    Problem Statement
    -----------------
    You are given an array prices where prices[i] is the price of a given stock on the ith day.
    Find the maximum profit you can achieve. You may complete at most two transactions.
    Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the
    stock before you buy again).

    Examples
    --------
    Example 1:
    Input: prices = [3,3,5,0,0,3,1,4]
    Output: 6
    Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
    Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.

    Example 2:
    Input: prices = [1,2,3,4,5]
    Output: 4
    Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
    Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are engaging
    multiple transactions at the same time. You must sell before buying again.

    Example 3:
    Input: prices = [7,6,4,3,1]
    Output: 0
    Explanation: In this case, no transaction is done, i.e. max profit = 0.


    Constraints:
    -----------
    1 <= prices.length <= 10^5
    0 <= prices[i] <= 10^5


    Approach:
    --------
    Best Time To Buy and Sell Stock(II) + knapsack with max weight. 
    Here maxTransaction = maxWeight in knapsack.

    3 states (day, canIBuyOnIthDay, transactions_left)
    days -> n 
    canIBuyOnIthDay -> 2    idx[0]: Sell idx[1]: Buy
    transactions_left -> 3   (0 left, 1 left, 2 left)
*/

class Solution {
    int maxProfitRecursive(vector<int>& prices, int i, bool canIBuyOnIthDay, int transactionsLeft) {
        //Base Case : No days left. Return 0 profit.
        if (i == prices.size())
            return 0;
        
        //Base Case : No more transactions left. Return 0 profit.
        if (transactionsLeft == 0)
            return 0;


        int profitOnIthDay = 0;
        //If I can buy on ith day
        if (canIBuyOnIthDay == true) {
            //if we choose to buy and goto next day
            int profitOnIthDayIfIBuy = -prices[i] + maxProfitRecursive(prices, i + 1, false, transactionsLeft);
            //if we choose not to buy
            int profitOnIthDayIfIDontBuy = 0 + maxProfitRecursive(prices, i + 1, true, transactionsLeft);
            profitOnIthDay = max(profitOnIthDayIfIBuy, profitOnIthDayIfIDontBuy);
        }
        else {
            //if we choose to sell we completed a transaction. so do transactionsLeft - 1
            int profitOnIthDayIfISell = prices[i] + maxProfitRecursive(prices, i + 1, true, transactionsLeft - 1);
            //if we choose not to sell
            int profitOnIthDayIfIDontSell = 0 + maxProfitRecursive(prices, i + 1, false, transactionsLeft);
            profitOnIthDay = max(profitOnIthDayIfISell, profitOnIthDayIfIDontSell);
        }
        return profitOnIthDay;
    }

    int maxProfitTopDown(vector<int>& prices, int i, bool canIBuyOnIthDay, int transactionsLeft, unordered_map<string, int>& lookup) {
        //Base Case : No days left. Return 0 profit.
        if (i == prices.size())
            return 0;

        //Base Case : No more transactions left. Return 0 profit.
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
        //Base Case : No days left. Return 0 profit.
        if (i == prices.size())
            return 0;

        //Base Case : No more transactions left. Return 0 profit.
        if (transactionsLeft == 0)
            return 0;

        // Check dp cache
        if (dp[i][canIBuyOnIthDay][transactionsLeft] != -1)
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


    int maxProfitBottomUp(vector<int>& prices) {
        int N = prices.size();
        vector<vector<vector<int>>> dp(N + 1, vector<vector<int>>(2, vector<int>(3, 0)));

        //dp[i][j][k] : represents on ith day if we can do jth action(0: buy, 1: sell) with at max 2 transactions
        // i can span from 0 to N-1.                            Total N states
        // j can span from 0 to 1 (buy and not buy).            Total 2 states
        // k can span from 0 to 2 (0 tranx, 1 tranx, 2 tranx).  Total 3 states.
        for (int i = N; i >= 0; i--) {
            for (int canIBuyOnIthDay = 0; canIBuyOnIthDay <= 1; canIBuyOnIthDay++) {
                for (int maxTransaction = 0; maxTransaction <= 2; maxTransaction++) {
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

        // return day 0, can buy, 2 transactions left
        return dp[0][1][2];
    }
public:
    int maxProfit(vector<int>& prices) {
        int transactionsLeft = 2;
        // return maxProfitRecursive(prices, 0, true, transactionsLeft);

        // Top Down Approach 1:
        // unordered_map<string, int> lookup;
        // return maxProfitTopDown(prices, 0, true, transactionsLeft, lookup);

        // Top Down Approach 2:
        // As there are 3 parameters changing, we need a 3D matrix.
        // n days × 
        // 2 buy states × 
        // 3 tx states (0 left,1 left, 2 left)
        vector<vector<vector<int>>> dp(prices.size(), vector<vector<int>>(2, vector<int>(3, -1)));
        return maxProfitTopDown2(prices, 0, true, transactionsLeft, dp);

        return maxProfitBottomUp(prices);
    }
};


int main() {
    Solution obj;
    vector<int> prices = { 3,3,5,0,0,3,1,4 };
    cout << obj.maxProfit(prices) << endl;          //6

    prices = { 1,2,3,4,5 };
    cout << obj.maxProfit(prices) << endl;          //4

    prices = { 7,6,4,3,1 };
    cout << obj.maxProfit(prices) << endl;          //0
}
