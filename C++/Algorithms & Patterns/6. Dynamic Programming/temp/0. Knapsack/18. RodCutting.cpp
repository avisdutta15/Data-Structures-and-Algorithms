#include <bits/stdc++.h>
using namespace std;

/*
    Given a rod of length n inches and an array price[]. price[i] denotes the 
    value of a piece of length i. The task is to determine the maximum value 
    obtainable by cutting up the rod and selling the pieces.

    Note: price[] is 1-indexed array.

    Input: price[] =  [1, 5, 8, 9, 10, 17, 17, 20]
    Output: 22
    Explanation:  The maximum obtainable value is 22 by cutting in two pieces of 
    lengths 2 and 6, i.e., 5 + 17 = 22.

    Input : price[] =  [3, 5, 8, 9, 10, 17, 17, 20]
    Output : 24
    Explanation : The maximum obtainable value is 24 by cutting the rod into 8 
    pieces of length 1, i.e, 8 * price[1]= 8*3 = 24.

    Input : price[] =  [3]
    Output : 3
    Explanation: There is only 1 way to pick a piece of length 1.

    Approach:
        In 2nd example, we can take rod of length 1, 8 times to maximize the profit.
        This means, for each length of rod, I have the option to take it infinite number 
        of times, or exclude it. 
        This is a variation on unbounded knapsack
*/

class Solution{
        //maximum profit that we can get from n rods of rodlength
        int cutRodRecursive(vector<int> &price, vector<int> &length, int rodLength, int N){
            if(N==0 || rodLength==0)
                return 0;
            int include = INT_MIN, exclude = INT_MIN;
            if(length[N-1]<= rodLength)
                include = price[N-1] + cutRodRecursive(price, length, rodLength-length[N-1], N);
            exclude = cutRodRecursive(price, length, rodLength, N-1);
            return max(include, exclude);
        }

        int cutRodTopDown(vector<int> &price, vector<int> &length, int rodLength, int N, unordered_map<string, int> &lookup){
            if(N==0 || rodLength==0)
                return 0;

            string key = to_string(N) + " " + to_string(rodLength);
            if(lookup.find(key) != lookup.end())
                return lookup[key];

            int include = INT_MIN, exclude = INT_MIN;
            if(length[N-1]<= rodLength)
                include = price[N-1] + cutRodRecursive(price, length, rodLength-length[N-1], N);
            exclude = cutRodRecursive(price, length, rodLength, N-1);
            return lookup[key] = max(include, exclude);
        }

        int cutRodBottomUp(vector<int> &price, vector<int> &length, int rodLength, int N){
            vector<vector<int>> dp(N+1, vector<int> (rodLength + 1, 0));

            for(int n=0; n<=N; n++){
                for(int r=0; r<=rodLength; r++){
                    if(n==0 || r==0)
                        dp[n][r] = 0;
                    else{
                        int include = INT_MIN, exclude = INT_MIN;
                        if(length[n-1]<= r)
                            include = price[n-1] + dp[n][r-length[n-1]];
                        exclude = dp[n-1][r];
                        dp[n][r] = max(include, exclude);
                    }
                }
            }
            return dp[N][rodLength];
        }

    public:
        int cutRod(vector<int> &price){
            int N = price.size();

            //The length array is equivalent to weight array of unbounded knapsack.
            vector<int> length;
            for(int i=1; i<=N; i++)
                length.push_back(i);
            int rodLength = N;

            // return cutRodRecursive(price, length, rodLength, N);

            // unordered_map<string, int> lookup;
            // return cutRodTopDown(price, length, rodLength, N, lookup);

            return cutRodBottomUp(price, length, rodLength, N);
        }
};


int main(){
    Solution obj;
    vector<int> price =  { 1, 5, 8, 9, 10, 17, 17, 20};     //22
    cout << obj.cutRod(price)<<endl;

    price = {3, 5, 8, 9, 10, 17, 17, 20};                   //24
    cout << obj.cutRod(price)<<endl;
}