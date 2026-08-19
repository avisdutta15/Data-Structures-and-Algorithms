#include <bits/stdc++.h>
using namespace std;

/*
    Problem Statement:
    -----------------
    Given an unlimited supply of coins of given denominations, find the total 
    number of distinct ways to get a desired change.

    S = {1, 3, 5, 7}
    Change = 8
    O/P: 6

    {1, 7}
    {3, 5} 
    {1, 1, 3, 3}
    {1, 1, 1, 5}
    {1, 1, 1, 1, 1, 3}
    {1, 1, 1, 1, 1, 1, 1, 1}

*/

/*
    Approach:
        Recurrence relation:
            count(coins, N, total) = count(include coin i) + count(exclude coin i)
        =>  count(coins, N, total) = count(coins, N, total-coins[N]) + count(coins, N-1, total)
*/

class Solution
{
    public:
        int naiveUtil(vector<int> coins, int i, int total){
            //if total becomes 0 that means we can make the change, so return 1 i.e. this recursive call makes 1 way
            if(total==0)
                return 1;
            
            //if total is not 0 and we have ran out of coins, that means we cannot make the change
            //So return 0
            if(total!=0 && i<0)
                return 0;

            //if we can include the coin then include it
            int include = 0;
            if(total-coins[i]>=0)
                include = naiveUtil(coins, i, total-coins[i]);    //why i and not i-1? because we have unlimited supply of coin[i]. So if we include it, we can use it again
            
            //exclude the current coin
            int exclude = naiveUtil(coins, i-1, total);
            
            //return the total ways to make change = total by including or excluding the current coin
            return include + exclude;
        }

        int topDownUtil(vector<int> coins, int i, int total, unordered_map<string, int> &lookup){
            if(total==0)
                return 1;
            if(total!=0 && i<0)
                return 0;
            
            string key = to_string(i) + ' ' + to_string(total);

            if(lookup.find(key)==lookup.end()){
                int include = 0;
                if((total - coins[i])>=0)
                    include = topDownUtil(coins, i, total-coins[i], lookup);
                int exclude = topDownUtil(coins, i-1, total, lookup);
                lookup[key] = include + exclude;
            }
            return lookup[key];
        }

        int totalDistinctWaysToGetChangeNaive(vector<int> coins, int total){
            return naiveUtil(coins, coins.size()-1, total);
        }
        
        int totalDistinctWaysToGetChangeTopDown(vector<int> coins, int total){
            unordered_map<string, int> lookup;
            return topDownUtil(coins, coins.size()-1, total, lookup);
        }

        /*       0 1 2 3 4 5 6 7 8
            0    1 0 0 0 0 0 0 0 0 
            2    1 0 1 0 1 0 1 0 1 
            3    1 0 1 0 1 1 1 1 1 
            5    1 0 1 1 1 2 2 2 3 

            Note:
                Why first column is 1? 
                There is only 1 way to make a total of 0 with coins of denomination of 0 i.e. by including it
                There is only 1 way to make a total of 0 with coins of denomination of 0, 2 i.e. by including coin 0
                Hence all the first column is 1 

                Why first row is 0 from change 1 to total?
                Because with coin of denomination of 0, we cannot make the change of amount 1, 2, .... total(i.e. 8)
        */


        int totalDistinctWaysToGetChangeBottomUp(vector<int> coins, int total){
            int n = coins.size();
            int m = total;

            int DP[n+1][m+1]={0};

            for(int i=0; i<=n; i++)
                DP[i][0] = 1;
            
            for(int i=1; i<=m; i++)
                DP[0][i] = 0;
            
            for(int i=1; i<=n; i++){
                for(int j=1; j<=m; j++){
                    int include = 0;
                    if(j-coins[i-1]>=0)
                        include = DP[i][j-coins[i-1]];
                    int exclude = DP[i-1][j];
                    DP[i][j] = include + exclude;
                }
            }
            
            for(int i=0; i<=n; i++){
                for(int j=0; j<=m; j++)
                    cout<<DP[i][j]<<" ";
                cout<<endl;
            }

            return DP[n][m];
        }
};

int main(){
    Solution obj;
    vector<int> denominations = {1, 3, 5, 7};
    int change = 8;

    cout<<obj.totalDistinctWaysToGetChangeBottomUp(denominations, change);

    return 0;
}