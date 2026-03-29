#include <bits/stdc++.h>
using namespace std;

/*
    Problem Statement:
    -----------------
    Given unlimited supply of coins of given denominations, find the minimum number of coins
    to get a desired change.

    S = {1, 3, 5, 7}
    Change = 15

    Ways:
    {7 + 7 + 1}, {5 + 5 + 5}, {3 + 7 + 5}
    i.e. Op: 3

*/

/*
    Approach:
        Recursion. For each coin of given denomination, we recurse to see if total can be reached by including 
        the coin or not. If choosing the current coin resulted in solution, then we update the minimum coins 
        needed. 
        Finally we return minimum value that we get after exhausting all the combintions.
*/


class Solution{
    public:
    int coinChange(vector<int> coins, int change){
        //if total is 0 then no coins required
        if(change == 0)
            return 0;

        //return INFINITY(meaning not possible) if total become -ve
        if(change<0)
            return INT_MAX;
        
        //initialize the minimum number of coins required to INFINITY
        int minCoins = INT_MAX;

        for(int i=0; i<coins.size(); i++){

            //recurse to see if total can be rached by including this coin.
            int res = coinChange(coins, change - coins[i]);
            
            //if it is possible to make a change using this coin then include it.
            if(res!=INT_MAX)
                res = res + 1;

            //update minCoins
            minCoins = min(minCoins, res);
        }

        return minCoins;
    }

    int coinChangeTopDownUtil(vector<int> coins, int change, unordered_map<int, int> &Hash){
        //if total is 0 then no coins required
        if(change == 0)
            return 0;

        //return INFINITY(meaning not possible) if total become -ve
        if(change<0)
            return INT_MAX;
        
        if(Hash.find(change)!=Hash.end())
            return Hash[change];

        //initialize the minimum number of coins required to INFINITY
        int minCoins = INT_MAX;

        for(int i=0; i<coins.size(); i++){

            //recurse to see if total can be rached by including this coin.
            int res = coinChangeTopDownUtil(coins, change - coins[i], Hash);
            
            //if it is possible to make a change using this coin then include it.
            if(res!=INT_MAX)
                res = res + 1;

            //update minCoins
            minCoins = min(minCoins, res);
        }

        Hash[change] = minCoins;

        return minCoins;
    }

    
    int coinChangeTopDown(vector<int>coins, int change){
        unordered_map<int, int> Hash;
        return coinChangeTopDownUtil(coins, change, Hash);
    }

    int coinChangeBottomUp(vector<int> coins, int change){
        int n = coins.size();
        int DP[n+1][change+1];

        for(int i=1; i<=change; i++)
            DP[0][i] = INT_MAX;
        for(int i=0; i<=coins.size();i++)
            DP[i][0] = 0;

        for(int i=1; i<=coins.size(); i++){
            for(int j=1; j<=change; j++){
                if(j<coins[i-1]){
                    DP[i][j] = DP[i-1][j];
                }else{
                    
                    int include = DP[i][j-coins[i-1]];
                    if(include != INT_MAX)
                        include = include + 1;
                    int exclude = DP[i-1][j];
                    DP[i][j] = min(include, exclude);
                }
            }
        }

        cout<<"The coins are: "<<endl;
        int i=coins.size(), j=change;
        while(i!=0 && j!=0){
            if(DP[i-1][j]==DP[i][j])
                i=i-1;
            else{
                cout<<coins[i-1]<<" ";
                j = j - coins[i-1];
            }
        }
        cout<<endl;
        return DP[n][change];
    }

    int coinChangeBottomUpOpt(vector<int> coins, int change){
        vector<int>DP(change+1, INT_MAX);
        DP[0] = 0;

        for(int i=1; i<=coins.size();i++){
            for(int j=0; j<=change; j++){
                if(j>=coins[i-1]){
                    int include = DP[j-coins[i-1]];
                    if(include != INT_MAX)
                        include = include + 1;
                    int exclude = DP[j];
                    DP[j] = min(include, exclude);
                }
            }
        }
        return DP[change];
    }
};


int main(){
    Solution obj;
    
    vector<int> coins = {5, 6, 8};
    int change = 20;
    
    cout<<obj.coinChange(coins, change)<<endl;
    cout<<obj.coinChangeTopDown(coins, change)<<endl;
    cout<<obj.coinChangeBottomUp(coins, change)<<endl;
    cout<<obj.coinChangeBottomUpOpt(coins, change)<<endl;
}