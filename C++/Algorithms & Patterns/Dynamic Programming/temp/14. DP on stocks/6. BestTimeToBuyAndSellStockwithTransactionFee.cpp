#include <bits/stdc++.h>
using namespace std;

/*
    You are given an array prices where prices[i] is the price of a given stock on 
    the ith day, and an integer fee representing a transaction fee.

    Find the maximum profit you can achieve. You may complete as many transactions as 
    you like, but you need to pay the transaction fee for each transaction.

    Note:

    You may not engage in multiple transactions simultaneously (i.e., you must sell the 
    stock before you buy again).
    The transaction fee is only charged once for each stock purchase and sale.
    

    Example 1:
    Input: prices = [1,3,2,8,4,9], fee = 2
    Output: 8
    Explanation: The maximum profit can be achieved by:
    - Buying at prices[0] = 1
    - Selling at prices[3] = 8
    - Buying at prices[4] = 4
    - Selling at prices[5] = 9
    The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.

    Example 2:
    Input: prices = [1,3,7,5,10,3], fee = 3
    Output: 6

    Constraints:
    1 <= prices.length <= 5 * 10^4
    1 <= prices[i] < 5 * 10^4
    0 <= fee < 5 * 10^4
*/

class Solution{
    //returns the max profit that we can make on ith day.
    int maxProfitRecursive(vector<int>& prices, int i, bool canIBuyOnIthDay, int transactionFee){
        if(i == prices.size())
            return 0;

        int profitOnIthDay = 0;

        //If I can buy on ith day
        if(canIBuyOnIthDay == true){
            //if we choose to buy
            int profitOnIthDayIfIBuy     =  -prices[i] + maxProfitRecursive(prices, i+1, false, transactionFee);
            //if we choose not to buy
            int profitOnIthDayIfIDontBuy =           0 + maxProfitRecursive(prices, i+1, true, transactionFee);
            profitOnIthDay = max(profitOnIthDayIfIBuy, profitOnIthDayIfIDontBuy);
        }
        else{
            //if we choose to sell. Transaction fee is levied once we complete a transaction. i.e. make a sell.
            int profitOnIthDayIfISell     =  (prices[i] - transactionFee) + maxProfitRecursive(prices, i+1, true, transactionFee);
            //if we choose not to sell
            int profitOnIthDayIfIDontSell =          0 + maxProfitRecursive(prices, i+1, false, transactionFee);
            profitOnIthDay = max(profitOnIthDayIfISell, profitOnIthDayIfIDontSell);
        }
        return profitOnIthDay;
    }

    int maxProfitTopDown(vector<int>& prices, int i, bool canIBuyOnIthDay, int transactionFee, unordered_map<string, int> &lookup){
        if(i == prices.size())
            return 0;
        
        string key = to_string(i) + " " + to_string(canIBuyOnIthDay);
        if(lookup.find(key)!=lookup.end()){
            return lookup[key];
        }

        int profitOnIthDay = 0;
        if(canIBuyOnIthDay == true){
            int profitOnIthDayIfIBuy     =  -prices[i] + maxProfitTopDown(prices, i+1, false, transactionFee, lookup);
            int profitOnIthDayIfIDontBuy =           0 + maxProfitTopDown(prices, i+1, true, transactionFee,  lookup);
            profitOnIthDay = max(profitOnIthDayIfIBuy, profitOnIthDayIfIDontBuy);
        }
        else{
            int profitOnIthDayIfISell     =  (prices[i]-transactionFee) + maxProfitTopDown(prices, i+1, true, transactionFee,  lookup);
            int profitOnIthDayIfIDontSell =          0 + maxProfitTopDown(prices, i+1, false, transactionFee,  lookup);
            profitOnIthDay = max(profitOnIthDayIfISell, profitOnIthDayIfIDontSell);
        }
        return lookup[key] = profitOnIthDay;
    }
    
    int maxProfitBottomUp(vector<int>& prices, int transactionFee){
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
                        int profitOnIthDayIfISell     =  prices[i] - transactionFee + dp[i+1][1];
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
        int maxProfit(vector<int>& prices, int transactionFee) {
            bool canIBuyOnIthDay = true;
            // return maxProfitRecursive(prices, 0, canIBuyOnIthDay, transactionFee);        
            
            // unordered_map<string, int> lookup;
            // return maxProfitTopDown(prices, 0, canIBuyOnIthDay, transactionFee, lookup);

            return maxProfitBottomUp(prices, transactionFee);
        }
};

int main(){
    Solution obj;
    vector<int> prices = {1,3,2,8,4,9};
    cout<<obj.maxProfit(prices, 2)<<endl;  //8

    prices = {1,3,7,5,10,3};
    cout<<obj.maxProfit(prices, 3)<<endl;  //6

    return 0;
}