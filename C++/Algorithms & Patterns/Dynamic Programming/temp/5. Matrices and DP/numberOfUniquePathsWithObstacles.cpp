#include <bits/stdc++.h>
using namespace std;

/*
    Given a grid of size m * n, let us assume you are starting at (1, 1) and your 
    goal is to reach (m, n). At any instance, if you are on (x, y), 
    you can either go to (x, y + 1) or (x + 1, y).

    Now consider if some obstacles are added to the grids. How many unique paths would there be?

    An obstacle and empty space are marked as 1 and 0 respectively in the grid.

    Examples:

    Input: [[0, 0, 0],
            [0, 1, 0],
            [0, 0, 0]]
    Output : 2
    There is only one obstacle in the middle.
*/


class Solution{
    public:
        int numberOfUniquePathsWithObstacles(vector<vector<int>> grid){
            int m = grid.size();
            int n = grid[0].size();

            int DP[m][n] = {0};
            
            //For the first column, there is only 1 way to reach it i.e. go down
            for(int i=0; i<m; i++)
                DP[i][0] = 1;
                
            //For the first row, there is only 1 way to reach it i.e. go right    
            for(int i=0; i<n; i++)
                DP[0][i] = 1;

            for(int i=1; i<m; i++){
                for(int j=1; j<n; j++){
                    //if this grid cell is an obstacle then there is no way to reach it
                    if(grid[i][j] == 1)
                        DP[i][j] = 0;
                    else
                        DP[i][j] = DP[i-1][j] + DP[i][j-1];
                }
            }
            return DP[m-1][n-1];
        }

};

int main(){
    vector<vector<int>> grid = {{0, 0, 0},
                                {0, 1, 0},
                                {0, 0, 0}};
    Solution obj;
    cout<<obj.numberOfUniquePathsWithObstacles(grid);
}