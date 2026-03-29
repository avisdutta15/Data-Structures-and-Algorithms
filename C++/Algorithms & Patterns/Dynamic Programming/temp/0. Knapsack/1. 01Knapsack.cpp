#include<bits/stdc++.h>
using namespace std;

/*
    Given N items where each item has some weight and profit associated with it and 
    also given a bag with capacity W, [i.e., the bag can hold at most W weight in it]. 
    The task is to put the items into the bag such that the sum of profits associated 
    with them is the maximum possible. 

    Note: The constraint here is we can either put an item completely into the bag or 
    cannot put it at all [It is not possible to put a part of an item into the bag].

    Input: N = 3, W = 4, profit[] = {1, 2, 3}, weight[] = {4, 5, 1}
    Output: 3
    Explanation: There are two items which have weight less than or equal to 4. If we 
    select the item with weight 4, the possible profit is 1. And if we select the item 
    with weight 1, the possible profit is 3. So the maximum possible profit is 3. Note 
    that we cannot put both the items with weight 4 and 1 together as the capacity of 
    the bag is 4.

    Input: N = 3, W = 3, profit[] = {1, 2, 3}, weight[] = {4, 5, 6}
    Output: 0

    Recurring Problem:  K(N, W) : K (remaining items, capacity)

                        K(n, W)
                        K(3, 2)  
                    /            \ 
                  /                \               
                K(2, 2)           K(2, 1)
            /       \                /    \ 
           /         \              /        \
        K(1, 2)      K(1, 1)        K(1, 1)     K(1, 0)
        /     \       /     \             /   \
        /      \     /       \           /     \
    K(0, 2)  K(0, 1)  K(0, 1)  K(0, 0)  K(0, 1)  K(0, 0)

    Recursion tree for Knapsack capacity 2 units and 3 items.
    
    Subproblem K(1,1) is repeated.

 */

class Solution{
    //what is the max profit i can get if I have W max weight and N items.
    int knapsackRecursive(vector<int> &profit, vector<int> &weight, int N, int W){
        //base case: if no items left or capacity becomes 0
        //           then we can make 0 profit
        if(N == 0 || W == 0)
            return 0;

        int include = INT_MIN, exclude = INT_MIN;
        // Case 1. Include current item `p[n]` in the knapsack and recur for
        // remaining items `n-1` with decreased capacity `W-w[n]`
        if(weight[N-1]<=W)
            include = profit[N-1] + knapsackRecursive(profit, weight, N-1, W - weight[N-1]);
        
        // Case 2. Excule current item `p[n]` in the knapsack and recur for
        // remaining items `n-1` with same capacity `W`
        exclude = knapsackRecursive(profit, weight, N-1, W);
        return max(include, exclude);
    }

    //what is the max profit i can get if I have W max weight and N items.
    int knapsackMemoized(vector<int> &profit, vector<int> &weight, int N, int W, unordered_map<string, int> &lookup){
        //base case: if no items left or capacity becomes 0
        if(N == 0 || W == 0)
            return 0;

        string key = to_string(N) + " " + to_string(W);
        if(lookup.find(key)!=lookup.end())
            return lookup[key];

        int include = INT_MIN, exclude = INT_MIN;
        // Case 1. Include current item `v[n]` in the knapsack and recur for
        // remaining items `n-1` with decreased capacity `W-w[n]`
        if(weight[N-1]<=W)
            include = profit[N-1] + knapsackMemoized(profit, weight, N-1, W - weight[N-1], lookup);
        exclude = knapsackMemoized(profit, weight, N-1, W, lookup);

        lookup[key] = max(include, exclude);
        return lookup[key];
    }

    //what is the max profit i can get if I have W max weight and N items.
    int knapsackBottomUp(vector<int> &profit, vector<int> &weight, int N, int W){
        
        vector<vector<int>> lookup(N+1, vector<int>(W+1));
        for(int n=0; n<=N; n++){
            for(int w=0; w<=W; w++){
                //base case
                if(n==0 || w==0){
                    lookup[n][w] = 0;
                }
                //include or exclude
                else{
                    int include = INT_MIN;
                    if(weight[n-1]<=w)
                        include = profit[n-1] + lookup[n-1][w-weight[n-1]];
                    int exclude = lookup[n-1][w];
                    lookup[n][w] = max(include, exclude);
                }
            }
        }
        return lookup[N][W];
    }


    int knapsackBottomUp1D(vector<int> &profit, vector<int> &weight, int N, int W){
        vector<int> dp(W+1, 0);

        for(int n=0; n<N; n++){
            for(int w=W; w>=weight[n]; w--){
                if(n == 0 || w == 0)
                    dp[w] = 0;
                else{
                    int include = INT_MIN;
                    if(weight[n]<=w)
                        include = profit[n] + dp[w-weight[n]];
                    int exclude = dp[w];
                    dp[w] = max(include, exclude);
                }
            }
        }        
        return dp[W];
    }

public:
    //O(n x W) Time and Space
    int knapsack(vector<int> &profit, vector<int> &weight, int N, int W){
        unordered_map<string, int> lookup;
        // int i = 0, totalProfit = 0, totalWeight = 0;
        // return knapsackRecursive(profit, weight, i, N, W, totalProfit, totalWeight, lookup);
        // return knapsackMemoizedOptimized(profit, weight, N, W, lookup);
        return knapsackBottomUp1D(profit, weight, N, W);
    }
};

int main(){
    Solution obj;
    vector<int> profit = {1, 2, 3};
    vector<int> weights = {4, 5, 1};
    cout<<obj.knapsack(profit, weights, 3, 4)<<endl;    //3

    profit = {1, 2, 3};
    weights = {4, 5, 6};
    cout<<obj.knapsack(profit, weights, 3, 3)<<endl;    //0 

    return 0;
}