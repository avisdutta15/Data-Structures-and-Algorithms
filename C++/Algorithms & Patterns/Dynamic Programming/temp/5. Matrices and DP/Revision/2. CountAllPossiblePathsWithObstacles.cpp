#include <bits/stdc++.h>
using namespace std;

/*
    Given a maze[][] of dimension N X M, such that maze[i][j] = -1 represents a 
    blocked cell and maze[i][j] = 0 represents an unblocked cell. The task is to 
    count the number of ways to reach bottom-right cell starting from top-left 
    cell by moving right (i, j+1) and down (i+1, j) in the maze.
    Note: You can only pass through the unblocked cells.

    Examples: 
    Input: maze = 
                {     
                    {0, 0, 0, 0},
                    {0, -1, 0, 0},
                    {-1, 0, 0, 0},
                    {0,  0, 0, 0}
                };
    Output: 4
*/

class Solution{
        int countAllPossiblePathsRecursive(vector<vector<int>> &grid, int n, int m){
            if(n==1 && m==1)
                return 1;
            if(n<1 || m<1)
                return 0;
            
            if(grid[n-1][m-1] == -1)
                return 0;
            
            int totalWaysFromTop = countAllPossiblePathsRecursive(grid, n-1, m);
            int totalWaysFromLeft= countAllPossiblePathsRecursive(grid, n, m-1);

            return totalWaysFromTop + totalWaysFromLeft;
        }

        int countAllPossiblePathsTopDown(vector<vector<int>> &grid, int n, int m, unordered_map<string, int> &lookup){
            if(n==1 && m==1)
                return 1;
            if(n<1 || m<1)
                return 0;
            
            string key = to_string(n) + " " + to_string(m);
            if(lookup.find(key) != lookup.end())
                return lookup[key];

            if(grid[n-1][m-1] == -1)
                return 0;
            
            int totalWaysFromTop = countAllPossiblePathsTopDown(grid, n-1, m, lookup);
            int totalWaysFromLeft= countAllPossiblePathsTopDown(grid, n, m-1, lookup);

            return lookup[key] = totalWaysFromTop + totalWaysFromLeft;            
        }

        int countAllPossiblePathsBottomUp(vector<vector<int>> &grid, int n, int m){
            vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

            for(int i=0; i<=n; i++){
                for(int j=0; j<=m; j++){
                    if(i==1 && j==1)
                        dp[i][j] = 1;

                    else if(i<1 || j<1)
                        dp[i][j] = 0;
                    
                    else if(grid[i-1][j-1] == -1)
                        dp[i][j] = 0;
                    else{
                        int totalWaysFromTop = dp[i-1][j];
                        int totalWaysFromLeft= dp[i][j-1];
                        dp[i][j] = totalWaysFromTop + totalWaysFromLeft;
                    }                    
                }
            }
            return dp[n][m];
        }

    public:
        int countAllPossiblePaths(vector<vector<int>> &grid){
            int n = grid.size();
            int m = grid[0].size();

            // return countAllPossiblePathsRecursive(grid, n, m);

            // unordered_map<string, int> lookup;
            // return countAllPossiblePathsTopDown(grid, n, m, lookup);

            return countAllPossiblePathsBottomUp(grid, n, m);
        }
};

int main(){
    Solution obj;
    vector<vector<int>> maze = {{0, 0, 0, 0},
                                {0, -1, 0, 0},
                                {-1, 0, 0, 0},
                                {0,  0, 0, 0}};

    cout<<obj.countAllPossiblePaths(maze)<<endl;    //4
    return 0;
}