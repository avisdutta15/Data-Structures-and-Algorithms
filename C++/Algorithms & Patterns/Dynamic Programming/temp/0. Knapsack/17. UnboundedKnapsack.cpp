#include <bits/stdc++.h>
using namespace std;

/*
    Given a knapsack weight, say capacity and a set of n items with certain 
    value vali and weight wti, The task is to fill the knapsack in such a way 
    that we can get the maximum profit. 
    This is different from the classical Knapsack problem, here we are allowed 
    to use an unlimited number of instances of an item.

    Examples: 
    Input: capacity = 100, val[]  = [1, 30], wt[] = [1, 50]
    Output: 100 
    Explanation: There are many ways to fill knapsack. 
    1) 2 instances of 50 unit weight item. 
    2) 100 instances of 1 unit weight item. 
    3) 1 instance of 50 unit weight item and 50 instances of 1 unit weight items. 
    We get maximum value with option 2.  

    Input: capacity = 8, val[] = [10, 40, 50, 70], wt[]  = [1, 3, 4, 5]        
    Output : 110
    Explanation: We get maximum value with one unit of weight 5 and one unit of weight 3.
*/

class Solution{

    //what is the max profit i can get if I have W max weight and N items.
    int knapsackRecursive(vector<int> &profit, vector<int> &weight, int N, int W){
        //base case: if no items left or capacity becomes 0
        //           then we can make 0 profit
        if(N == 0 || W == 0)
            return 0;

        int include = INT_MIN, exclude = INT_MIN;
        if(weight[N-1]<=W)
            include = profit[N-1] + knapsackRecursive(profit, weight, N, W-weight[N-1]);
        exclude = knapsackRecursive(profit, weight, N-1, W);
        return max(include, exclude);
    }

    //what is the max profit i can get if I have W max weight and N items.
    int knapsackTopDown(vector<int> &profit, vector<int> &weight, int N, int W, unordered_map<string, int> &lookup){
        //base case: if no items left or capacity becomes 0
        //           then we can make 0 profit
        if(N==0 || W==0)
            return 0;
        
        string key = to_string(N) + " " + to_string(W);
        if(lookup.find(key)!=lookup.end())
            return lookup[key];
        
        int include = INT_MIN, exclude = INT_MIN;
        if(weight[N-1]<=W)
            include = profit[N-1] + knapsackTopDown(profit, weight, N, W-weight[N-1], lookup);
        exclude = knapsackTopDown(profit, weight, N-1, W, lookup);
        return lookup[key] = max(include, exclude);
    }

    //what is the max profit i can get if I have W max weight and N items.
    int knapsackBottomUp(vector<int> &profit, vector<int> &weight, int N, int W){
        vector<vector<int>> dp(N+1, vector<int>(W+1, 0));

        for(int n=0; n<=N; n++){
            for(int w=0; w<=W; w++){
                //base case: if no items left or capacity becomes 0
                //           then we can make 0 profit
                if(n==0 || w == 0)
                    dp[n][w] = 0;
                else{
                    int include = INT_MIN, exclude = INT_MIN;
                    if(weight[n-1] <= w)
                        include = profit[n-1] + dp[n][w-weight[n-1]];
                    exclude = dp[n-1][w];
                    dp[n][w] = max(include, exclude);
                }
            }
        }
        return dp[N][W];
    }
    public:
        int knapsack(vector<int> &profit, vector<int> &weight, int N, int W){
            // return knapsackRecursive(profit, weight, N, W);

            // unordered_map<string, int> lookup;
            // return knapsackTopDown(profit, weight, N, W, lookup);

            return knapsackBottomUp(profit, weight, N, W);
        }
};


int main(){
    Solution obj;
    vector<int> weight = {2, 4, 6};     // Weight of items
    vector<int> profit = {5, 11, 13};   // Value of items
    int W = 10;                         // Weight capacity of the knapsack
    int N = weight.size();              // Total items
    cout<<obj.knapsack(profit, weight, N, W)<<endl;
}