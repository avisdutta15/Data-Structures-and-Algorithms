#include <algorithm>
#include <iostream>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string.h>

using namespace std;

/*
    https://www.youtube.com/watch?v=excAOvwF_Wk&t=1s
    
    Problem Statement:
    ------------------
    You are given an array prices where prices[i] is the price of a given stock on the ith day.

    You want to maximize your profit by choosing a single day to buy one stock and choosing a
    different day in the future to sell that stock.

    Return the maximum profit you can achieve from this transaction. If you cannot achieve any
    profit, return 0.

    Examples
    --------

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
    ---------
        To make the max profit, we need to buy it at the lowest price and sell
        it on the day after it with a price higher than it.
        Keep track of the maximum profit made.
        In example1, buy it on day 2 with price = 1 and sell it on day 5 with price = 6.
        Max profit = 6 - 1 = 5.

        Intuition: Track the minimum price seen so far. At each day, either it's a 
        new minimum (potential buy day) or the profit from selling today is better 
        than our best (potential sell day).

    TC : O(N)
        
*/



class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() == 0)
            return 0;

        int minPrice = INT_MAX;
        int maxProfit = 0;

        for (int i = 0; i < prices.size(); i++) {

            if(prices[i] < minPrice) {
                // Found a new minimum — update buy point
                minPrice = prices[i];
            } else {
                // Not a new minimum, calculate profit if we sell today
                int profit = prices[i] - minPrice;

                // Is this profit better than what we've seen?
                if(profit > maxProfit)
                    maxProfit = profit;
            }
        }

        return maxProfit;
    }
};

int main() {
    Solution obj;
    vector<int> prices = { 7,1,5,3,6,4 };
    cout << obj.maxProfit(prices) << endl;

    prices = { 7,6,4,3,1 };
    cout << obj.maxProfit(prices) << endl;

    return 0;
}
