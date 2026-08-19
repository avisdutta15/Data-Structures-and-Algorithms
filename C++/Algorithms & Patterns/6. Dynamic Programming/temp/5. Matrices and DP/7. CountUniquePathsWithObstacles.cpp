#include <bits/stdc++.h>
using namespace std;

/*
    Problem Statement:
    -----------------
    Given a grid of size m * n, let us assume you are starting at (1, 1) and your 
    goal is to reach (m, n). At any instance, if you are on (x, y), you can either 
    go to (x, y + 1) or (x + 1, y).

    Now consider if some obstacles are added to the grids. How many unique paths would there be?

    An obstacle and empty space are marked as 1 and 0 respectively in the grid.

    Examples:
    Input: [[0, 0, 0],
            [0, 1, 0],
            [0, 0, 0]]
    Output : 2
    There is only one obstacle in the middle.    

*/

/*
    Algorithm:
    ----------
    1. Create a 2D matrix of same size of the given matrix to store the results.
    2. Traverse through the created array row wise and start filling the values in it.
    3. If an obstacle is found, set the value to 0.
    4. For the first row and column, set the value to 1 if obstacle is not found.
    5. Set the sum of the right and the upper values if obstacle is not present at that corresponding position in the given matirx
    6. Return the last value of the created 2d matrix
    
*/

class Solution
{
    int row, col;
    public:
        int countUniquePathsWithObstacles(vector<vector<int>>A){
            row = A.size();
            if(row==0)
                return 0;
            col = A[0].size();

            //if the first cell is an obstacle then we cannot have a solution
            if(A[0][0] == 1)
                return 0;

            //Create a 2D array and 
            int DP[row][col];
            DP[0][0] = 1;

            for(int i=1; i<row; i++){
                if(A[0][i]==0)
                    DP[0][i] = DP[0][i-1];
                else
                    DP[0][i] = 0;
            }

            for(int i=1; i<col; i++){
                if(A[i][0]==0)
                    DP[i][0] = DP[i-1][0];
                else
                    DP[i][0] = 1;
            }

            for(int i=1; i<row; i++){
                for(int j=1; j<col; j++){
                    if(A[i][j]==0)
                        DP[i][j] = DP[i-1][j] + DP[i][j-1];
                    else
                        DP[i][j] = 0;
                }
            }
            return DP[row-1][col-1];
        }
};

int main(){
    Solution obj;    
    vector<vector<int>>A = { 
                             { 0, 0, 0 }, 
                             { 0, 1, 0 },
                             { 0, 0, 0 } 
                           };
    cout<<obj.countUniquePathsWithObstacles(A);
    return 0;
}