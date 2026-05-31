#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

/*
    Problem Statement:
    -----------------
    You are given an m x n integer array grid where grid[i][j] could be:

    1 representing the starting square. There is exactly one starting square.
    2 representing the ending square. There is exactly one ending square.
    0 representing empty squares we can walk over.
    -1 representing obstacles that we cannot walk over.
    
    Return the number of 4-directional walks from the starting square to the ending square, 
    that walk over every non-obstacle square exactly once.
    

    Examples:
    ---------
    Input: grid = [[1,0,0,0],
                   [0,0,0,0],
                   [0,0,2,-1]
                  ]
    Output: 2
    Explanation: We have the following two paths: 
    1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
    2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)
    

    Input: grid = [[1,0,0,0],
                   [0,0,0,0],
                   [0,0,0,2]
                  ]
    Output: 4
    Explanation: We have the following four paths:
    1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
    2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
    3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
    4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)

    Input: grid = [
                    [0,1],
                    [2,0]
                  ]
    Output: 0
    Explanation: There is no path that walks over every empty square exactly once.
    Note that the starting and ending square can be anywhere in the grid.

    Constraints:
        m == grid.length
        n == grid[i].length
        1 <= m, n <= 20
        1 <= m * n <= 20
        -1 <= grid[i][j] <= 2


    Approach:
    ----------
    1. Grid Backtracking template
*/

//Recursion 
class Solution {
private:
    int solve(vector<vector<int>>& grid, int r, int c, int& m, int& n, int count, int& countOfNonObstacleCell) {
        //if cell is out of bounds or is obstacle or is visited then 0 ways.
        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == -1 || grid[r][c] == -2)
            return 0;

        //if the cell is the dest cell and we have visited all the non-obstacle cells
        if (grid[r][c] == 2) {
            if (count == countOfNonObstacleCell)
                return 1;
            return 0;
        }

        //visit this cell
        grid[r][c] = -2;
        count++;

        //visit all 4 directions
        int totalWays = solve(grid, r + 1, c, m, n, count, countOfNonObstacleCell) +
            solve(grid, r - 1, c, m, n, count, countOfNonObstacleCell) +
            solve(grid, r, c + 1, m, n, count, countOfNonObstacleCell) +
            solve(grid, r, c - 1, m, n, count, countOfNonObstacleCell);

        //unvisit this cell
        grid[r][c] = 0;
        count--;
        return totalWays;
    }

public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int startR = -1, startC = -1;
        int countOfNonObstacleCell = 0;

        //find the starting cell
        //count the number of non - obstacle cells.
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0)
                    countOfNonObstacleCell++;
                if (grid[i][j] == 1) {
                    //The start cell is also a non obstacle cell.
                    //In the backtracking we do count++ at the start cell also.
                    //so when we do count == countOfNonObstacleCell, count includes
                    //start cell. Hence countOfNonObstacleCell should include start cell.
                    countOfNonObstacleCell++;
                    startR = i;
                    startC = j;
                }
            }
        }

        return solve(grid, startR, startC, m, n, 0, countOfNonObstacleCell);
    }
};


int main() {
    Solution obj;
    vector<vector<int>> grid = { 
                                 {1,0,0,0},
                                 {0,0,0,0},
                                 {0,0,2,-1}
                               };
    auto ans = obj.uniquePathsIII(grid);
    cout << ans;
    cout << endl;

    return 0;
}