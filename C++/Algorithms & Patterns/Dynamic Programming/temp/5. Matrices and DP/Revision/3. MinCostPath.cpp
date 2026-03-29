#include <bits/stdc++.h>
using namespace std;

/*
    Given a 2d matrix cost[][], the task is to calculate the minimum cost path to 
    reach (m, n) from (0, 0). Each cell of the matrix represents a cost to traverse 
    through that cell. The total cost of a path to reach (m, n) is the sum of all 
    the costs on that path (including both source and destination).
    
    We can only traverse down, right and diagonally lower cells from a given cell, 
    i.e., from a given cell (i, j), cells (i+1, j), (i, j+1), and (i+1, j+1) can be traversed.

    Input:  { { 1, 2, 3 },
              { 4, 8, 2 },
              { 1, 5, 3 } };
    O/P: 8
    Explanation : 1->2->2->3
                The cost of the path is 8 (1 + 2 + 2 + 3).    
*/

class Solution{
        int minCostPathRecursive(vector<vector<int>> &grid, int n, int m){
            if(n==1 && m==1)
                return grid[n-1][m-1];

            if(n<1 || m<1)
                return INT_MAX; //denotes not possible

            int costFromLeft =  minCostPathRecursive(grid, n, m-1);
            int costFromUp =    minCostPathRecursive(grid, n-1, m);
            int costFromDiagonalUp = minCostPathRecursive(grid, n-1, m-1);

            return grid[n-1][m-1] + min({costFromLeft, costFromUp, costFromDiagonalUp});
        }

        int minCostPathTopDown(vector<vector<int>> &grid, int n, int m, unordered_map<string, int> &lookup){
            if(n==1 && m==1)
                return grid[n-1][m-1];

            if(n<1 || m<1)
                return INT_MAX; //denotes not possible

            string key = to_string(n) + " " + to_string(m);
            if(lookup.find(key) != lookup.end())
                return lookup[key];

            int costFromLeft =  minCostPathTopDown(grid, n, m-1, lookup);
            int costFromUp =    minCostPathTopDown(grid, n-1, m, lookup);
            int costFromDiagonalUp = minCostPathTopDown(grid, n-1, m-1, lookup);

            return lookup[key] = grid[n-1][m-1] + min({costFromLeft, costFromUp, costFromDiagonalUp});
        }

        int minCostPathBottomUp(vector<vector<int>> &grid, int n, int m){
            vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

            for(int i=0; i<=n; i++){
                for(int j=0; j<=m; j++){
                    if(i==1 && j==1)
                        dp[i][j] = grid[i-1][j-1];

                    else if(i<1 || j<1)
                        dp[i][j] = INT_MAX;
                    
                    else{
                        int totalWaysFromTop = dp[i-1][j];
                        int totalWaysFromLeft= dp[i][j-1];
                        int costFromDiagonalUp = dp[i-1][j-1];
                        dp[i][j] = grid[i-1][j-1] + 
                            min({totalWaysFromTop, totalWaysFromLeft, costFromDiagonalUp});
                    }                    
                }
            }
            return dp[n][m];
        }

    public:
        int minCostPath(vector<vector<int>> &grid){
            int n = grid.size();
            int m = grid[0].size();
            // return minCostPathRecursive(grid, n, m);

            // unordered_map<string, int> lookup;
            // return minCostPathTopDown(grid, n, m, lookup);

            return minCostPathBottomUp(grid, n, m);
        }

        vector<int> printMinCostPath(vector<vector<int>> &grid){
            
        }
};


int main(){
    Solution obj;
    vector<vector<int>> grid = { { 1, 2, 3 },
                                 { 4, 8, 2 },
                                 { 1, 5, 3 } };

    cout<<obj.minCostPath(grid)<<endl;  //8
}