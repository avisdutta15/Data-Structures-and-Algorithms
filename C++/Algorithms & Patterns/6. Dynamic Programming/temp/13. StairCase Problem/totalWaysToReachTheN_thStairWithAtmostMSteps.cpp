#include <bits/stdc++.h>
using namespace std;

/*
    Given a staircase, find the total number of ways to reach the nth stair from the bottom of
    the stair when you are allowed to take at-most m steps at a time.

    Input: n = 3, m = 2
    Output: Total ways to reach the 3’rd stair with at-most 2 steps are:  3
        1 step + 1 step + 1 step
        1 step + 2 steps
        2 steps + 1 step

    Input: n = 4, m = 3
    Output: Total ways to reach the 4’th stair with at-most 3 steps are:  7
        1 step + 1 step + 1 step + 1 steps
        1 step + 1 step + 2 steps
        1 step + 2 steps + 1 step
        1 step + 3 steps
        2 steps + 1 step + 1 step
        2 steps + 2 steps
        3 steps + 1 step
    
    For a maximum of 3 steps at a time, we have came up with the recurrence relation T(n):
        T(n) = T(n-1) + T(n-2) + T(n-3) where n >= 0 and
        T(0) = 1, T(1) = 1, and T(2) = 2
    For at-most m steps, the recurrence relation T(n) can be written as following:
        T(n) = T(n-1) + T(n-2) + ... T(n-m)
*/


class Solution{
    public:
        int totalWays(int n, int m){
            if(n<0)
                return 0;
            if(n==0)
                return 1;
            int count = 0;
            for(int i=1; i<=m; i++){
                count+= totalWays(n-i, m);
            }
            return count;
        }
};

class Solution1{
    public:
        int totalWaysUtil(int n, int m, vector<int> &dp){
            if(n<0)
                return 0;
            if(n==0)
                return 1;
            if(dp[n]==0){
                for(int i=1; i<=m; i++)
                    dp[n] = dp[n] + totalWaysUtil(n-i, m, dp);
            }
            return dp[n];
        }

        int totalWays(int n, int m){
            vector<int> dp(n+1, 0);

            totalWaysUtil(n, m, dp);
            return dp[n];
        }
};

int main(){
    Solution obj;
    cout<<obj.totalWays(4,3)<<endl;

    Solution1 obj1;
    cout<<obj1.totalWays(4,3)<<endl;
}