#include <bits/stdc++.h>
using namespace std;

/*
    You are given an integer array prices where prices[i] is the price of a given stock on the ith day.

    On each day, you may decide to buy and/or sell the stock. You can only 
    hold at most one share of the stock at any time. However, you can buy 
    it then immediately sell it on the same day.

    Find and return the maximum profit you can achieve.
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
    1 <= prices.length <= 3 * 10^4
    0 <= prices[i] <= 10^4

    Approach:
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

    https://www.youtube.com/watch?v=nGJmxkUJQGs
*/

class Solution{
    //returns the max profit that we can make on ith day.
    int maxProfitRecursive(vector<int>& prices, int i, bool canIBuyOnIthDay){
        if(i == prices.size())
            return 0;

        int profitOnIthDay = 0;

        //If I can buy on ith day
        if(canIBuyOnIthDay == true){
            //if we choose to buy
            int profitOnIthDayIfIBuy     =  -prices[i] + maxProfitRecursive(prices, i+1, false);
            //if we choose not to buy
            int profitOnIthDayIfIDontBuy =           0 + maxProfitRecursive(prices, i+1, true);
            profitOnIthDay = max(profitOnIthDayIfIBuy, profitOnIthDayIfIDontBuy);
        }
        else{
            //if we choose to sell
            int profitOnIthDayIfISell     =  prices[i] + maxProfitRecursive(prices, i+1, true);
            //if we choose not to sell
            int profitOnIthDayIfIDontSell =          0 + maxProfitRecursive(prices, i+1, false);
            profitOnIthDay = max(profitOnIthDayIfISell, profitOnIthDayIfIDontSell);
        }
        return profitOnIthDay;
    }

    int maxProfitTopDown(vector<int>& prices, int i, bool canIBuyOnIthDay, unordered_map<string, int> &lookup){
        if(i == prices.size())
            return 0;
        
        string key = to_string(i) + " " + to_string(canIBuyOnIthDay);
        if(lookup.find(key)!=lookup.end()){
            return lookup[key];
        }

        int profitOnIthDay = 0;
        if(canIBuyOnIthDay == true){
            int profitOnIthDayIfIBuy     =  -prices[i] + maxProfitTopDown(prices, i+1, false, lookup);
            int profitOnIthDayIfIDontBuy =           0 + maxProfitTopDown(prices, i+1, true, lookup);
            profitOnIthDay = max(profitOnIthDayIfIBuy, profitOnIthDayIfIDontBuy);
        }
        else{
            int profitOnIthDayIfISell     =  prices[i] + maxProfitTopDown(prices, i+1, true, lookup);
            int profitOnIthDayIfIDontSell =          0 + maxProfitTopDown(prices, i+1, false, lookup);
            profitOnIthDay = max(profitOnIthDayIfISell, profitOnIthDayIfIDontSell);
        }
        return lookup[key] = profitOnIthDay;
    }
    void printDp(vector<vector<int>> &dp){
        for(int i=0; i<dp.size();i++){
            for(int j=0; j<dp[0].size(); j++){
                cout<<dp[i][j]<<"\t";
            }
            cout<<endl;
        }
    }
    int maxProfitBottomUp(vector<int>& prices){
        int N = prices.size();
        vector<vector<int>> dp(N+1, vector<int>(2, 0));
        
        for(int i=N; i>=0; i--){
            for(int canIBuyOnIthDay = 0; canIBuyOnIthDay<=1; canIBuyOnIthDay++){
                if(i == N)
                    dp[i][canIBuyOnIthDay] = 0;
                else{
                    int profitOnIthDay = 0;
                    if(canIBuyOnIthDay == 1){
                        int profitOnIthDayIfIBuy     =  -prices[i] + dp[i+1][0];
                        int profitOnIthDayIfIDontBuy =           0 + dp[i+1][1];
                        profitOnIthDay = max(profitOnIthDayIfIBuy, profitOnIthDayIfIDontBuy);
                    }
                    else{
                        int profitOnIthDayIfISell     =  prices[i] + dp[i+1][1];
                        int profitOnIthDayIfIDontSell =          0 + dp[i+1][0];
                        profitOnIthDay = max(profitOnIthDayIfISell, profitOnIthDayIfIDontSell);
                    }
                    dp[i][canIBuyOnIthDay] = profitOnIthDay;
                }
            }
        }

        //printDp(dp);
        return dp[0][1];
    }

    public:
        int maxProfit(vector<int>& prices) {
            bool canIBuyOnIthDay = true;
            // return maxProfitRecursive(prices, 0, canIBuyOnIthDay);        
            
            // unordered_map<string, int> lookup;
            // return maxProfitTopDown(prices, 0, canIBuyOnIthDay, lookup);

            return maxProfitBottomUp(prices);
        }
};


//Approach2: https://www.youtube.com/watch?v=3SJ3pUkPQMc
//Find the total profit where we buy at dip and sell at high.
//i.e. profit = prices[j] - prices[i]       Where prices[j]>prices[i] and j>i.
//sum up all these profits.
class Solution2{
    public:
        int maxProfit(vector<int>& prices) {
            int N = prices.size();
            int profit=0;
            // i for buy day index
            // j for sell index
            for (int i=0; i<N-1; i++) {
                if(prices[i] < prices[i+1]) {
                    int j=i+1;
                    while(j < N-1 && prices[j] < prices[j+1]) {
                        j++;
                    }
                    profit+= prices[j]-prices[i];
                    i=j;    //because we cannot buy anything in between
                }
            }
            return profit;
        }
};

int main(){
    Solution obj;
    vector<int> prices = {7,1,5,3,6,4};
    cout<<obj.maxProfit(prices)<<endl;  //7

    prices = {1,2,3,4,5};
    cout<<obj.maxProfit(prices)<<endl;  //4

    prices = {7,6,4,3,1};
    cout<<obj.maxProfit(prices)<<endl;  //0
}