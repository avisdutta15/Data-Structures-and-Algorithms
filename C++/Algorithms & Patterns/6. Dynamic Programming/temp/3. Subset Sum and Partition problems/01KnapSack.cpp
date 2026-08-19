#include <bits/stdc++.h>
using namespace std;

/*
    In the following recursion tree, K() refers 
    to knapSack(). The two parameters indicated in the
    following recursion tree are n and W.
    The recursion tree is for following sample inputs.
    wt[] = {1, 1, 1}, W = 2, val[] = {10, 20, 30}
                        K(n, W)
                        K(3, 2)  
                    /            \ 
                    /                \               
                K(2, 2)                  K(2, 1)
            /       \                  /    \ 
            /           \              /        \
        K(1, 2)      K(1, 1)        K(1, 1)     K(1, 0)
        /  \         /   \          /   \
        /      \     /       \      /       \
    K(0, 2)  K(0, 1)  K(0, 1)  K(0, 0)  K(0, 1)   K(0, 0)
    Recursion tree for Knapsack capacity 2 
    units and 3 items of 1 unit weight.

*/

class Solution1{
    public:
        int knapSackUtil(vector<int> weights, vector<int> values, int N, int weightRemaining){
            if(N==0 || weightRemaining==0)
                return 0;
            
            //if we cannot include the current item i.e. weight
            //of current item is greater than the weightRemaining, then exclude
            if(weights[N-1] > weightRemaining){
                return knapSackUtil(weights, values, N-1, weightRemaining);
            }

            //else include / exclude the current item
            //if we include then add the profit value of the current item.
            int include = values[N-1] + knapSackUtil(weights, values, N-1, weightRemaining-weights[N-1]);
            int exclude = knapSackUtil(weights, values, N-1, weightRemaining);
            
            return max(include, exclude);
        }
        int knapSack(vector<int> weights, vector<int> values, int maxWeight){
            int weightRemaining = maxWeight;
            int N = values.size();
            return knapSackUtil(weights, values, N, weightRemaining);
        }
};

class Solution2{
    public:
        int knapSackUtil(vector<int> weights, vector<int> values, int N, int weightRemaining, unordered_map<string, int> &lookup){
            string key = to_string(N) + " " + to_string(weightRemaining);
            if(N==0 || weightRemaining==0)
                return lookup[key]=0;
            
            if(lookup.count(key) > 0)
                return lookup[key];

            //if we cannot include the current item i.e. weight
            //of current item is greater than the weightRemaining, then exclude
            if(weights[N-1] > weightRemaining){
                return lookup[key]=knapSackUtil(weights, values, N-1, weightRemaining, lookup);
            }

            //else include / exclude the current item
            //if we include then add the profit value of the current item.
            int include = values[N-1] + knapSackUtil(weights, values, N-1, weightRemaining-weights[N-1], lookup);
            int exclude = knapSackUtil(weights, values, N-1, weightRemaining, lookup);
            
            return lookup[key]=max(include, exclude);
        }
        int knapSack(vector<int> weights, vector<int> values, int maxWeight){
            int weightRemaining = maxWeight;
            int N = values.size();
            unordered_map<string, int> lookup;
            return knapSackUtil(weights, values, N, weightRemaining, lookup);
        }
};

class Solution3{
    public:
        int knapSack(vector<int> weights, vector<int> values, int maxWeight){
            int N = values.size();
            int dp[N+1][maxWeight+1];

            for(int n=0; n<=N; n++){
                for(int w=0; w<=maxWeight; w++){
                    if(n==0 || w==0)
                        dp[n][w] = 0;
                    else if(weights[n-1]>w){
                        dp[n][w] = dp[n-1][w];
                    }else{
                        dp[n][w] = max(values[n-1]+dp[n-1][w-weights[n-1]], dp[n-1][w]);
                    }
                }
            }

            return dp[N][maxWeight];
        }

        void printKnapSack(vector<int> weights, vector<int> values, int maxWeight){
            int N = values.size();
            int dp[N+1][maxWeight+1];

            for(int n=0; n<=N; n++){
                for(int w=0; w<=maxWeight; w++){
                    if(n==0 || w==0)
                        dp[n][w] = 0;
                    else if(weights[n-1]>w){
                        dp[n][w] = dp[n-1][w];
                    }else{
                        dp[n][w] = max(values[n-1]+dp[n-1][w-weights[n-1]], dp[n-1][w]);
                    }
                }
            }

            int maxProfit = dp[N][maxWeight];
            int i = N;
            int j = maxWeight;

            while(i>0 && j>0){
                if(dp[i][j] == dp[i-1][j])
                    i--;
                else{
                    cout<<"Including weight "<<weights[i - 1]<<" with value "<<values[i - 1]<<endl;
                    j = j - weights[i-1];
                    i = i-1;
                }
            }
        }
};

int main(){
    Solution1 obj1;
    Solution2 obj2;
    Solution3 obj3;

    vector<int> weights = {10, 20, 30};
    vector<int> values  = {60, 100, 120};
    int maxWeight = 50;

    cout<<obj1.knapSack(weights, values, maxWeight)<<endl;
    cout<<obj2.knapSack(weights, values, maxWeight)<<endl;
    cout<<obj3.knapSack(weights, values, maxWeight)<<endl;
    obj3.printKnapSack(weights, values, maxWeight);
}
