#include <bits/stdc++.h>
using namespace std;

/*
    Given a matrix of size n * m. Find the maximum path sum in the matrix. 
    The maximum path is the sum of all elements from the first row to the 
    last row where you are allowed to move only down or diagonally to left 
    or right. You can start from any element in the first row.

    Examples: 
    Input: mat[][] = 10 10  2  0   20  4
                     1  0   0  30  2   5
                     0  10  4  0   2   0
                     1  0   2  20  0   4
    Output: 74
    Explanation: The maximum sum path is 20-30-4-20.

    Input: mat[][] = 1 2 3
                     9 8 7
                     4 5 6
    Output: 17
    Explanation: The maximum sum path is 3-8-6.
*/

class Solution{
        int maxPathSumFromFirstRowToLastRowRecursive(vector<vector<int>> &grid, int i, int j, int &lastRow){
            if(i<0 || j<0 || i>=lastRow || j>=grid[i].size())
                return INT_MIN;         //denotes out of bound
            
            if(i==lastRow-1)
                return grid[i][j];
            
            int maxPathFromDown = maxPathSumFromFirstRowToLastRowRecursive(grid, i+1, j, lastRow);
            int maxPathFromDiagonallyDownRight = maxPathSumFromFirstRowToLastRowRecursive(grid, i+1, j+1, lastRow);
            int maxPathFromDiagonallyDownLeft  = maxPathSumFromFirstRowToLastRowRecursive(grid, i+1, j-1, lastRow);

            return grid[i][j] + max({maxPathFromDown, maxPathFromDiagonallyDownRight, maxPathFromDiagonallyDownLeft});
        }
    public:
        int maxPathSumFromFirstRowToLastRow(vector<vector<int>> &grid){
            vector<int> lastRowCost(grid[0].size(), 0);
            int lastRow = grid.size();

            for(int j=0; j<grid[0].size(); j++){
                lastRowCost[j] = maxPathSumFromFirstRowToLastRowRecursive(grid, 0, j, lastRow);
            }

            return *max_element(lastRowCost.begin(), lastRowCost.end());
        }
};


int main(){
    Solution obj;
    vector<vector<int>> grid = {{10, 10, 2, 0, 20, 4},
                                {1, 0, 0, 30, 2, 5},
                                {0, 10, 4, 0, 2, 0},
                                {1, 0, 2, 20, 0, 4}};

    cout<<obj.maxPathSumFromFirstRowToLastRow(grid)<<endl;

    grid =  {{1, 2, 3},
             {9, 8, 7},
             {4, 5, 6}};
    cout<<obj.maxPathSumFromFirstRowToLastRow(grid)<<endl;
    return 0;
}