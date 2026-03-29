#include <bits/stdc++.h>
using namespace std;

/*
    Given a matrix where every cell has some number of coins. Count number 
    of ways to reach bottom right from top left with exactly k coins. 
    We can move to (i+1, j) and (i, j+1) from a cell (i, j).

    Example: 

    Input:  k = 12
            mat[][] = { {1, 2, 3},
                        {4, 6, 5},
                        {3, 2, 1}
                    };
    Output:  2
    There are two paths with 12 coins
    1 -> 2 -> 6 -> 2 -> 1
    1 -> 2 -> 3 -> 5 -> 1

    Approach:
        This is like grid traversal + bounded knapsack where the max weight = K
*/

class Solution{
        int numOfPathsWithExactlyKPathsRecursive(vector<vector<int>> &grid, int i, int j, int K){
            //if all coins are exhausted then return 1;
            if(i==1 && j==1){
                if(K == grid[i-1][j-1])
                    return 1;
                else 
                    return 0;
            } 

            if(i<1 || j<1 || K==0)
                return 0;
            
            int numOfPathsToUp     = numOfPathsWithExactlyKPathsRecursive(grid, i-1, j, K-grid[i-1][j-1]);
            int numOfPathsFromLeft = numOfPathsWithExactlyKPathsRecursive(grid, i, j-1, K-grid[i-1][j-1]);
            return numOfPathsToUp + numOfPathsFromLeft;
        }

        int numOfPathsWithExactlyKPathsTopDown(vector<vector<int>> &grid, int i, int j, int K, unordered_map<string, int> &lookup){
            //if all coins are exhausted then return 1;
            if(i==1 && j==1){
                if(K == grid[i-1][j-1])
                    return 1;
                else 
                    return 0;
            } 

            if(i<1 || j<1 || K==0)
                return 0;
            
            string key = to_string(i) + " " + to_string(j) + " " + to_string(K);
            if(lookup.find(key)!=lookup.end())
                return lookup[key];
            
            int numOfPathsToUp     = numOfPathsWithExactlyKPathsTopDown(grid, i-1, j, K-grid[i-1][j-1], lookup);
            int numOfPathsFromLeft = numOfPathsWithExactlyKPathsTopDown(grid, i, j-1, K-grid[i-1][j-1], lookup);
            return lookup[key] = numOfPathsToUp + numOfPathsFromLeft;
        }

        int numOfPathsWithExactlyKPathsBottomUp(vector<vector<int>> &grid, int N, int M, int K){
            // DP Table: dp[i][j][k] represents the number of paths to (i, j) with sum exactly k
            vector<vector<vector<int>>> dp(N + 1, vector<vector<int>>(M + 1, vector<int>(K + 1, 0)));

            // Base Case
            // if (grid[0][0] <= K)
            //     dp[1][1][grid[0][0]] = 1;

            // Fill DP table
            for (int i = 0; i <= N; i++) {
                for (int j = 0; j <= M; j++) {
                    for (int k = 0; k <= K; k++) {
                        //if (i == 1 && j == 1) continue; // Base case handled already
                        if(i==0 || j==0 || k==0)
                            dp[i][j][k] = 0;
                        else if(i==1 && j==1){
                            if(k== grid[i-1][j-1])
                                dp[i][j][k] = 1;
                            else
                                dp[i][j][k] = 0;
                        }
                        else{
                            // why this if was added?? because if k = 1 and grid[i-1][j-1] = 3
                            // then 1 - 3 = -2 is an invalid index in matrix. This is like include
                            // condition in knapsack
                            if(k>=grid[i-1][j-1]){          
                                int numOfPathsToUp     = dp[i-1][j][k-grid[i-1][j-1]];
                                int numOfPathsFromLeft = dp[i][j-1][k - grid[i-1][j-1]];
                                dp[i][j][k] = numOfPathsToUp + numOfPathsFromLeft;
                            }
                            
                            // int cellValue = grid[i-1][j-1]; 
                            // if (k - cellValue >= 0) {
                            //     // Paths from above
                            //     dp[i][j][k] += dp[i-1][j][k - cellValue];

                            //     // Paths from left
                            //     dp[i][j][k] += dp[i][j-1][k - cellValue];
                            // }
                        }
                        
                    }
                }
            }

            return dp[N][M][K]; // Answer: Number of paths to (M, N) with sum K
        } 

    public:
        int numOfPathsWithExactlyKPaths(vector<vector<int>> &grid, int K){
            int N = grid.size();
            int M = grid[0].size();

            // return numOfPathsWithExactlyKPathsRecursive(grid, N, M, K);

            // unordered_map<string, int> lookup;
            // return numOfPathsWithExactlyKPathsTopDown(grid, N, M, K, lookup);

            return numOfPathsWithExactlyKPathsBottomUp(grid, N, M, K);
        }
};


int main(){
    Solution obj;
    vector<vector<int>> grid = { {1, 2, 3},
                                 {4, 6, 5},
                                 {3, 2, 1}
                                };

    cout<<obj.numOfPathsWithExactlyKPaths(grid, 12)<<endl;
}