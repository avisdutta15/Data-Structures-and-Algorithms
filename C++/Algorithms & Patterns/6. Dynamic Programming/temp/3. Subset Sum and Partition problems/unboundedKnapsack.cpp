#include <bits/stdc++.h>
using namespace std;

/*
    
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
            int include = values[N-1] + knapSackUtil(weights, values, N, weightRemaining-weights[N-1]); 
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
                return lookup[key] = 0; 

            if(lookup.find(key)!=lookup.end())
                return lookup[key];

            //if we cannot include the current item i.e. weight 
            //of current item is greater than the weightRemaining, then exclude 
            if(weights[N-1] > weightRemaining){ 
                return lookup[key] = knapSackUtil(weights, values, N-1, weightRemaining, lookup); 
            }
            
            //else include / exclude the current item 
            //if we include then add the profit value of the current item. 
            int include = values[N-1] + knapSackUtil(weights, values, N, weightRemaining-weights[N-1], lookup); 
            int exclude = knapSackUtil(weights, values, N-1, weightRemaining, lookup); 
            
            return lookup[key] = max(include, exclude); 
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
            int DP[N+1][maxWeight+1];

            for(int n=0; n<=N; n++){
                for(int w=0; w<=maxWeight; w++){
                    if(n==0 || w==0)
                        DP[n][w]=0;
                    else if(weights[n-1] > w){
                        DP[n][w] = DP[n-1][w];
                    }
                    else{
                        int include = values[n-1] + DP[n][w - weights[n-1]];
                        int exclude = DP[n-1][w];
                        DP[n][w] = max(include, exclude);
                    }
                }
            } 
            
            /* to print the values and weights in the knapsack
            
                int x=N, y=maxWeight;
                while(x > 0 && y > 0){
                    if (DP[x][y] == DP[x - 1][y])
                        x--;
                    else {
                        cout<<"including wt "<<weights[x - 1]<<" with value "<<values[x - 1]<<endl;
                        y -= weights[x - 1];
                    }
                }
            */
            return DP[N][maxWeight];
        }
};

int main(){
    vector<int> values ={10, 30, 20}; 
    vector<int> weights = {5, 10, 15}; 
    int maxWeight = 100; 

    Solution1 obj1;
    cout<<obj1.knapSack(weights, values, maxWeight)<<endl;

    Solution2 obj2;
    cout<<obj2.knapSack(weights, values, maxWeight)<<endl;

    Solution3 obj3;
    cout<<obj3.knapSack(weights, values, maxWeight)<<endl;
    
    values = {10, 40, 50, 70}; 
    weights = {1, 3, 4, 5}; 
    maxWeight = 8;
    cout<<obj3.knapSack(weights, values, maxWeight)<<endl;
}