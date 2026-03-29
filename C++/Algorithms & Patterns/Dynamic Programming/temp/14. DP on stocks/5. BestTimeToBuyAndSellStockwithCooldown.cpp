#include <bits/stdc++.h>
using namespace std;

/*
    You are given an array prices where prices[i] is the price of a given stock on the ith day.

    Find the maximum profit you can achieve. You may complete as many transactions as you like (i.e., 
    buy one and sell one share of the stock multiple times) with the following restrictions:

    After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).
    Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock 
    before you buy again).

    Example 1:
    Input: prices = [1,2,3,0,2]
    Output: 3
    Explanation: transactions = [buy, sell, cooldown, buy, sell]
    
    Example 2:
    Input: prices = [1]
    Output: 0
    
    Constraints:
    1 <= prices.length <= 5000
    0 <= prices[i] <= 1000

    Approach:
        Same like BTOBASS(II) with a twist.
        if we choose to sell, goto i+2th day as i+1th day is cooldown
*/

class Solution {
        //returns the max profit that we can make on ith day.
        int maxProfitRecursive(vector<int>& prices, int i, bool canIBuyOnIthDay){
            if(i >= prices.size())
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
                //if we choose to sell, goto i+2th day as i+1th day is cooldown
                int profitOnIthDayIfISell     =  prices[i] + maxProfitRecursive(prices, i+2, true);
                //if we choose not to sell
                int profitOnIthDayIfIDontSell =          0 + maxProfitRecursive(prices, i+1, false);
                profitOnIthDay = max(profitOnIthDayIfISell, profitOnIthDayIfIDontSell);
            }
            return profitOnIthDay;
        }
        
        int maxProfitTopDown(vector<int>& prices, int i, bool canIBuyOnIthDay, unordered_map<string, int> &lookup){
            if(i >= prices.size())
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
                int profitOnIthDayIfISell     =  prices[i] + maxProfitTopDown(prices, i+2, true, lookup);
                int profitOnIthDayIfIDontSell =          0 + maxProfitTopDown(prices, i+1, false, lookup);
                profitOnIthDay = max(profitOnIthDayIfISell, profitOnIthDayIfIDontSell);
            }
            return lookup[key] = profitOnIthDay;
        }
    
        int maxProfitBottomUp(vector<int>& prices){
            int N = prices.size();
            //Why N+2? because we would goto i+2. when i=N then we would goto N+2
            vector<vector<int>> dp(N+2, vector<int>(2, 0));
            
            for(int i=N; i>=0; i--){
                for(int canIBuyOnIthDay = 0; canIBuyOnIthDay<=1; canIBuyOnIthDay++){
                    if(i >= N)
                        dp[i][canIBuyOnIthDay] = 0;
                    else{
                        int profitOnIthDay = 0;
                        if(canIBuyOnIthDay == 1){
                            int profitOnIthDayIfIBuy     =  -prices[i] + dp[i+1][0];
                            int profitOnIthDayIfIDontBuy =           0 + dp[i+1][1];
                            profitOnIthDay = max(profitOnIthDayIfIBuy, profitOnIthDayIfIDontBuy);
                        }
                        else{
                            int profitOnIthDayIfISell     =  prices[i] + dp[i+2][1];
                            int profitOnIthDayIfIDontSell =          0 + dp[i+1][0];
                            profitOnIthDay = max(profitOnIthDayIfISell, profitOnIthDayIfIDontSell);
                        }
                        dp[i][canIBuyOnIthDay] = profitOnIthDay;
                    }
                }
            }
    
            return dp[0][1];
        }
        
    public:
        int maxProfit(vector<int>& prices) {
            // return maxProfitRecursive(prices, 0, true);

            // unordered_map<string, int> lookup;
            // return maxProfitTopDown(prices, 0, true, lookup);

            return maxProfitBottomUp(prices);
        }
};


int main(){
    Solution obj;
    vector<int> prices = {1,2,3,0,2};
    cout<<obj.maxProfit(prices)<<endl;  //3

    prices = {1};
    cout<<obj.maxProfit(prices)<<endl;  //0

    return 0;
}