#include<bits/stdc++.h>
#include <unordered_set>
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

    Bottom Up Matrix:
    profit = {1, 4, 5, 7};
    weight = {1, 3, 4, 5};

    Profit  Weight Indx     0 1 2 3 4 5 6 7     MaxWeight(W)
    0       0       0       0 0 0 0 0 0 0 0 
    1       1       1       0 1 1 1 1 1 1 1
    4       3       2       0 1 1 4 5 5 5 5
    5       4       3       0 1 1 4 5 6 6 9
    7       5       4       0 1 1 4 5 7 8 9

    if(weight[n-1]<w)
        include = profit[n-1] + dp[n-1][w-weight[n-1]];
    exclude = dp[n-1][w];
    dp[n][w] = max(include, exclude);

*/

class Solution{
    void printMatrix(vector<vector<int>> &lookup){
        for(int i=0; i<lookup.size(); i++){
            for(int j=0; j<lookup[0].size(); j++)
                cout<<lookup[i][j]<<" ";
            cout<<endl;
        }
    }

    void printItemsBottomUp(vector<vector<int>> &lookup, vector<int> &profit, vector<int> &weight, int N, int W){
        //For Debugging
        //printMatrix(lookup);
        cout<<"Following Items are included: "<<endl;

        //Why initialize n = N and w = W and the loop ends at n>0 and w>0?
        //Because we are using n-1 to access the elements of weight and profit array.
        int n = N, w = W;
        while(n>0 && w>0){
            int currentValue = lookup[n][w];
            int excludedValue = lookup[n-1][w];

            //if current item is excluded then goto next item.
            if(currentValue == excludedValue)
                n = n - 1;
            else{
                cout<<"Including weight "<<weight[n-1]<<" with profit value "<<profit[n-1]<<endl; 
                //once this item is included, goto the next item with reduced weight.
                w = w - weight[n-1];
                n = n - 1;
            }
        }
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
        
        printItemsBottomUp(lookup, profit, weight, N, W);
        return lookup[N][W];
    }

public:
    //O(n x W) Time and Space
    int knapsack(vector<int> &profit, vector<int> &weight, int N, int W){
        return knapsackBottomUp(profit, weight, N, W);
    }
};

int main(){
    Solution obj;
    vector<int> profit = {1, 4, 5, 7};
    vector<int> weights = {1, 3, 4, 5};
    cout<<obj.knapsack(profit, weights, 4, 7)<<endl;    //9

    return 0;
}