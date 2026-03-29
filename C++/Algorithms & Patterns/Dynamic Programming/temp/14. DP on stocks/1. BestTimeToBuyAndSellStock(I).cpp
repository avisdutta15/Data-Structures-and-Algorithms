#include <bits/stdc++.h>
using namespace std;

/*
    You are given an array prices where prices[i] is the price of a given stock on the ith day.

    You want to maximize your profit by choosing a single day to buy one stock and choosing a 
    different day in the future to sell that stock.

    Return the maximum profit you can achieve from this transaction. If you cannot achieve any 
    profit, return 0.


    Example 1:
    Input: prices = [7,1,5,3,6,4]
    Output: 5
    Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
    Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.
    
    Example 2:
    Input: prices = [7,6,4,3,1]
    Output: 0
    Explanation: In this case, no transactions are done and the max profit = 0.
    
    Constraints:
    1 <= prices.length <= 105
    0 <= prices[i] <= 104


    Approach:
        The make the max profit, we need to buy it at the lowest price and sell
        it on the day after it with the maximum price.
        In example1, buy it on day 2 with price = 1 and sell it on day 5 with price = 6.
        Max profit = 6 - 1 = 5.

        So if we think in other way, we can make the max profit on day i by selling it 
        on day i and purchasing it on any day before i with the minimum cost.
        i.e. to make the max profit, sell it on day 5 with price = 6 and buy it on day 2
        with price = 1. 

        https://www.youtube.com/watch?v=excAOvwF_Wk&t=1s
*/



class Solution{
    public:
        int maxProfit(vector<int>& prices) {
            if(prices.size() == 0)
                return 0;
            
            int minimumPriceTillNow = prices[0];
            int maxProfit = 0;
            vector<int> profitOnIthDay(prices.size());
            profitOnIthDay[0] = 0;

            for(int i=1; i<prices.size(); i++){
                int profitBySellingItOnIthDay = prices[i] - minimumPriceTillNow;
                // maxProfit = max(maxProfit, profitBySellingItOnIthDay);
                profitOnIthDay[i] = profitBySellingItOnIthDay;
                minimumPriceTillNow = min(minimumPriceTillNow, prices[i]);
            }
            return *max_element(profitOnIthDay.begin(), profitOnIthDay.end());
        }
};

//We can eliminate the profitOnIthDay array as all we are doing is taking the
//max value at the end from the end. We can achieve this by having a running maxProfit variable.
class Solution2{
    public:
        int maxProfit(vector<int>& prices) {
            if(prices.size() == 0)
                return 0;
            
            int minimumPriceTillNow = prices[0];
            int maxProfit = 0;

            for(int i=1; i<prices.size(); i++){
                int profitBySellingItOnIthDay = prices[i] - minimumPriceTillNow;
                maxProfit = max(maxProfit, profitBySellingItOnIthDay);
                minimumPriceTillNow = min(minimumPriceTillNow, prices[i]);
            }
            return maxProfit;
        }
};

int main(){
    Solution obj;
    vector<int> prices = {7,1,5,3,6,4};
    cout<<obj.maxProfit(prices)<<endl;

    prices = {7,6,4,3,1};
    cout<<obj.maxProfit(prices)<<endl;

    return 0;
}
