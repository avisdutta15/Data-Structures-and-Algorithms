#include <bits/stdc++.h>
using namespace std;

/*
    Problem Statement:
    -----------------
    The problem is to count all the possible paths from top left to bottom right of a mXn matrix 
    with the constraints that from each cell you can either move only to right or down.

    Input :  m = 2, n = 3;
    Output : 3
    There are three paths
    (0, 0) -> (0, 1) -> (0, 2) -> (1, 2)
    (0, 0) -> (0, 1) -> (1, 1) -> (1, 2)
    (0, 0) -> (1, 0) -> (1, 1) -> (1, 2)

    Given a matrix, print all the possible paths from top left to bottom right of a mXn matrix 
    with the constraints that from each cell you can either move only to right or down.

*/

class Solution{
        //we start from i=0, j=0 and see if we are able to reach n, m. If yes then totalPath++
        void countAllPossiblePathsBacktracking(int i, int j, int n, int m, int &totalPaths){
            if(i==n-1 && j==m-1){
                totalPaths++;
                return;
            }

            //if out of bounds then return
            if(i>=n || j>=m)
                return;

            //goto right
            countAllPossiblePathsBacktracking(i, j+1, n, m, totalPaths);       
            //goto down
            countAllPossiblePathsBacktracking(i+1, j, n, m, totalPaths);
        }

        //we start from n and m and try to goto 0,0. If we are able to reach 0,0 then totalPath++
        void countAllPossiblePathsBacktrackingLessVar(int n, int m, int &totalPaths){
            if(n==1 && m==1){
                totalPaths++;
                return;
            }

            //if out of bounds then return
            if(n<1 || m<1)
                return;

            //goto left
            countAllPossiblePathsBacktrackingLessVar(n, m-1, totalPaths);       
            //goto up
            countAllPossiblePathsBacktrackingLessVar(n-1, m, totalPaths);
        }

        //we start from i=0, j=0. We donot keep a totalPath variable.
        //At i,j we ask ourself, in how many ways I can goto n,m by going right and down.
        //Ans = totalWaysRight + totalWaysDown
        int countAllPossiblePathsRecursive(int i, int j, int n, int m){
            if(i==n-1 && j==m-1){
                return 1;
            }

            //if out of bounds then return
            if(i>=n || j>=m)
                return 0;

            //goto right
            int right = countAllPossiblePathsRecursive(i, j+1, n, m);       
            //goto down
            int down = countAllPossiblePathsRecursive(i+1, j, n, m);

            //so total ways that I can reach from i,j to n,m by going right and down is right + down
            return right + down;
        }

        //we start from n and m and try to goto 0,0. We donot keep a totalPath variable.
        //At any cell we ask ourself, in how many ways I reach n,m from 0,0 by coming from left and up.
        //Ans = totalWaysLeft + totalWaysUp
        int countAllPossiblePathsRecursiveLessVar(int n, int m){
            if(n==1 && m==1)
                return 1;
            
            if(n<1 || m<1)
                return 0;
            
            //goto left
            int left = countAllPossiblePathsRecursiveLessVar(n, m-1);       
            //goto up
            int up = countAllPossiblePathsRecursiveLessVar(n-1, m);

            //so total ways to reach n,m from 0,0 is total ways from left + total ways from up
            return left + up;
        }

        int countAllPossiblePathsTopDown(int n, int m, unordered_map<string, int> &lookup){
            if(n==1 && m==1)
                return 1;

            if(n<1 || m<1)
                return 0;
            
            string key = to_string(n) + " " + to_string(m);
            if(lookup.find(key) != lookup.end())
                return lookup[key];

            int totalWaysFromLeft = countAllPossiblePathsTopDown(n, m-1, lookup);
            int totalWaysFromUp = countAllPossiblePathsTopDown(n-1, m, lookup);
            return lookup[key] = totalWaysFromLeft + totalWaysFromUp;
        }

        int countAllPossiblePathsBottomUp(int n, int m){
            vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

            for(int i=0; i<=n; i++){
                for(int j=0; j<=m; j++){
                    if(i==1 && j==1)
                        dp[i][j] = 1;
                    else if (i<1 || j<1)
                        dp[i][j] = 0;
                    else{
                        int totalWaysFromLeft = dp[i][j-1];
                        int totalWaysFromUp   = dp[i-1][j];
                        dp[i][j] = totalWaysFromLeft + totalWaysFromUp; 
                    }
                }
            }
            return dp[n][m];
        }

    public:
        int countAllPossiblePaths(int n, int m){
            // Backtracking
            // int totalPaths = 0;
            // countAllPossiblePathsBacktracking(0, 0, n, m, totalPaths);
            // countAllPossiblePathsBacktrackingLessVar(n, m, totalPaths);
            // return totalPaths;

            //Recursion + DP
            // return countAllPossiblePathsRecursive(0, 0, n, m);
            // return countAllPossiblePathsRecursiveLessVar(n, m);
            // unordered_map<string, int> lookup;
            // return countAllPossiblePathsTopDown(n, m, lookup);
            return countAllPossiblePathsBottomUp(n, m);
        }
};


int main(){
    Solution obj;
    cout<<obj.countAllPossiblePaths(2, 2)<<endl;
    cout<<obj.countAllPossiblePaths(2, 3)<<endl;

    return 0;
}