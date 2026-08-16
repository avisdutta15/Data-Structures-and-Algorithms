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
    https://www.youtube.com/watch?v=nGJmxkUJQGs
    https://www.youtube.com/watch?v=3SJ3pUkPQMc

    Problem Statement : 
    -----------------
    You are given an integer array prices where prices[i] is the price of a given stock on the ith day.

    On each day, you may decide to buy and/or sell the stock. You can only
    hold at most one share of the stock at any time. However, you can buy
    it then immediately sell it on the same day.

    Find and return the maximum profit you can achieve.

    Example:
    --------

    Example 1:
    Input: prices = [7,1,5,3,6,4]
    Output: 7
    Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
    Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
    Total profit is 4 + 3 = 7.

    Example 2:
    Input: prices = [1,2,3,4,5]
    Output: 4
    Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
    Total profit is 4.

    Example 3:
    Input: prices = [7,6,4,3,1]
    Output: 0
    Explanation: There is no way to make a positive profit, so we never buy the
    stock to achieve the maximum profit of 0.

    Constraints:
    ------------
    1 <= prices.length <= 3 * 10^4
    0 <= prices[i] <= 10^4

    Approach 1 : Recurrence -> Memoization -> Bottomup
    --------------------------------------------------
    In this question, we can buy and sell multiple times i.e. Can have multiple transactions
    (buy-sell together is called a transaction). But if we buy on ith day, the next following days,
    we can only sell it. When we buy we do a -price[i] because that depletes our profit. But when
    we sell the stock we do a + price[i] as that price is added to our profit.
    This problem has knapsack like decision making process.
        If we can buy on ith day, we have 2 options:
            1. either buy and goto next day.
            2. or dont buy and goto next day (why dont buy? because the price might be too high!)
        If we can sell on ith day, we have 2 options:
            1. either sell it on ith day and book profit and goto next day
            2. or dont sell and goto next day (why dont sell? because the price might be too low than what we bought)
    the max profit that we can make on that ith day will be the max of all these 4.


    Approach 2: Valley-Peak Approach
    --------------------------------
    Since we can make unlimited transactions, the optimal strategy is: buy at every valley (local minimum) 
    and sell at the next peak (local maximum).


    Price
      |
      |       *peak
      |      / \
      |     /   \       *peak
      |    /     \     / \
      |   /       \   /   \
      |  *valley   \ /     \
      |              *valley \
      |                       *
      +------------------------→ Days

      Buy here↑    Sell↑  Buy↑  Sell↑
    
    Why this works:

        1. If tomorrow's price is lower than today → don't buy today (wait for a better entry)
        2. If tomorrow's price is higher → today is a potential valley (buy point)
        3. Once we buy, keep riding the uptrend until prices stop increasing → that's the peak (sell point)
        4. After selling at the peak, start looking for the next valley
    
    Why skip everything between peak and next valley?
    Between a peak and the next valley, prices are falling.
    Any transaction started in this region would result in a loss.
    So we jump to i = j + 1 (day after the peak) and start looking for the next upward move.
    
*/


class Solution1 {
private:
    // Time: O(2^N) — each day branches into 2 choices. 
    // Space: O(N) — recursion stack.
    // returns the max profit that we can make on ith day.
    int maxProfitRecursive(vector<int>& prices, int i, bool canIBuyOnIthDay) {
        // Base Case: No more days
        if (i == prices.size())
            return 0;

        int profitOnIthDay = 0;

        //If I can buy on ith day
        if (canIBuyOnIthDay == true) {
            //if we choose to buy and goto next day
            int profitOnIthDayIfIBuy = -prices[i] + maxProfitRecursive(prices, i + 1, false);
            //if we choose not to buy and goto next day
            int profitOnIthDayIfIDontBuy = 0 + maxProfitRecursive(prices, i + 1, true);
            profitOnIthDay = max(profitOnIthDayIfIBuy, profitOnIthDayIfIDontBuy);
        }
        else {
            //if we choose to sell and goto next day
            int profitOnIthDayIfISell = prices[i] + maxProfitRecursive(prices, i + 1, true);
            //if we choose not to sell and goto next day
            int profitOnIthDayIfIDontSell = 0 + maxProfitRecursive(prices, i + 1, false);
            profitOnIthDay = max(profitOnIthDayIfISell, profitOnIthDayIfIDontSell);
        }
        return profitOnIthDay;
    }

    int maxProfitTopDown(vector<int>& prices, int i, bool canIBuyOnIthDay, unordered_map<string, int>& lookup) {
        // Base Case: No more days
        if (i == prices.size())
            return 0;

        string key = to_string(i) + " " + to_string(canIBuyOnIthDay);
        if (lookup.find(key) != lookup.end()) {
            return lookup[key];
        }

        int profitOnIthDay = 0;
        if (canIBuyOnIthDay == true) {
            int profitOnIthDayIfIBuy = -prices[i] + maxProfitTopDown(prices, i + 1, false, lookup);
            int profitOnIthDayIfIDontBuy = 0 + maxProfitTopDown(prices, i + 1, true, lookup);
            profitOnIthDay = max(profitOnIthDayIfIBuy, profitOnIthDayIfIDontBuy);
        }
        else {
            int profitOnIthDayIfISell = prices[i] + maxProfitTopDown(prices, i + 1, true, lookup);
            int profitOnIthDayIfIDontSell = 0 + maxProfitTopDown(prices, i + 1, false, lookup);
            profitOnIthDay = max(profitOnIthDayIfISell, profitOnIthDayIfIDontSell);
        }
        return lookup[key] = profitOnIthDay;
    }
    
    // TC: O(N × 2)
    int maxProfitTopDown2(vector<int>& prices, int i, bool canIBuyOnIthDay, vector<vector<int>>& dp) {
        // Base Case: No more days
        if (i == prices.size())
            return 0;

        if(dp[i][canIBuyOnIthDay] != -1)
            return dp[i][canIBuyOnIthDay];

        int profitOnIthDay = 0;
        if (canIBuyOnIthDay == true) {
            int profitOnIthDayIfIBuy = -prices[i] + maxProfitTopDown2(prices, i + 1, false, dp);
            int profitOnIthDayIfIDontBuy = 0 + maxProfitTopDown2(prices, i + 1, true, dp);
            profitOnIthDay = max(profitOnIthDayIfIBuy, profitOnIthDayIfIDontBuy);
        }
        else {
            int profitOnIthDayIfISell = prices[i] + maxProfitTopDown2(prices, i + 1, true, dp);
            int profitOnIthDayIfIDontSell = 0 + maxProfitTopDown2(prices, i + 1, false, dp);
            profitOnIthDay = max(profitOnIthDayIfISell, profitOnIthDayIfIDontSell);
        }
        return dp[i][canIBuyOnIthDay] = profitOnIthDay;
    }

    // Time: O(N), Space: O(N)
    int maxProfitBottomUp(vector<int>& prices) {

        int N = prices.size();
        // We are tracking 2 states : Day and the canIBuyOnIthDay.
        // n rows -> n days
        // 2 cols -> 2 states -> buy(1) or sell(0)
        // dp[i][0] = max profit from day i onwards when HOLDING (can sell)
        // dp[i][1] = max profit from day i onwards when NOT HOLDING (can buy)
        vector<vector<int>> dp(N + 1, vector<int>(2, 0));

        // Fill from last day backwards
        for (int i = N; i >= 0; i--) {
            for (int canIBuyOnIthDay = 0; canIBuyOnIthDay <= 1; canIBuyOnIthDay++) {
                if (i == N)
                    dp[i][canIBuyOnIthDay] = 0;
                else {
                    int profitOnIthDay = 0;
                    if (canIBuyOnIthDay == 1) {
                        int profitOnIthDayIfIBuy = -prices[i] + dp[i + 1][0];
                        int profitOnIthDayIfIDontBuy = 0 + dp[i + 1][1];
                        profitOnIthDay = max(profitOnIthDayIfIBuy, profitOnIthDayIfIDontBuy);
                    }
                    else {
                        int profitOnIthDayIfISell = prices[i] + dp[i + 1][1];
                        int profitOnIthDayIfIDontSell = 0 + dp[i + 1][0];
                        profitOnIthDay = max(profitOnIthDayIfISell, profitOnIthDayIfIDontSell);
                    }
                    dp[i][canIBuyOnIthDay] = profitOnIthDay;
                }
            }
        }

        // start on day 0, and buy. We cannot sell on day 0 without buying.
        return dp[0][1];
    }

public:
    int maxProfit(vector<int>& prices) {
        bool canIBuyOnIthDay = true;
        // return maxProfitRecursive(prices, 0, canIBuyOnIthDay);        

        // Top Down Approach 1
        // unordered_map<string, int> lookup;
        // return maxProfitTopDown(prices, 0, canIBuyOnIthDay, lookup);

        // Top Down Approach 2. We are tracking 2 states : Day and the canIBuyOnIthDay.
        // n rows -> n days.
        // 2 cols -> 2 states -> buy(1) or sell(0)
        // int n = prices.size();
        // vector<vector<int>> dp(n, vector<int>(2, -1));
        // return maxProfitTopDown2(prices, 0, true, dp);

        return maxProfitBottomUp(prices);
    }
};


//Approach2: https://www.youtube.com/watch?v=3SJ3pUkPQMc
//Find the total profit where we buy at dip and sell at high.
//i.e. profit = prices[j] - prices[i]       Where prices[j]>prices[i] and j>i.
//sum up all these profits.
class Solution2 {
public:
    int maxProfit(vector<int>& prices) {
        int N = prices.size();
        int profit = 0;

        // i for buy day index
        // j for sell index
        
        int i = 0;
        while (i <= N - 2) {
            // if the next day price is higher then buy today
            if (prices[i] < prices[i + 1]) {

                // start trying to sell from next day and find the peak
                int j = i + 1;
                while (j < N - 1 && prices[j] < prices[j + 1]) {
                    j++;
                }

                // found the peak, book the profit
                profit += prices[j] - prices[i];

                // start the next transaction from the peak day
                // because we cannot buy anything in between
                i = j+1;
            }
            // if the next day price is lower or equal, we don't buy today.
            else {
                i++;
            }
        }

        return profit;
    }
};

int main() {
    Solution1 obj;
    vector<int> prices = { 7,1,5,3,6,4 };
    cout << obj.maxProfit(prices) << endl;  //7

    prices = { 1,2,3,4,5 };
    cout << obj.maxProfit(prices) << endl;  //4

    prices = { 7,6,4,3,1 };
    cout << obj.maxProfit(prices) << endl;  //0
}
