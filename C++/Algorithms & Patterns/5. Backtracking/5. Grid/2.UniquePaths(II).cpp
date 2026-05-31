#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

/*
    Problem Statement:
    -----------------
    You are given an m x n integer array grid. There is a robot initially located at the top-left corner 
    (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). 
    The robot can only move either down or right at any point in time.

    An obstacle and space are marked as 1 or 0 respectively in grid. A path that the robot takes cannot 
    include any square that is an obstacle.

    Return the number of possible unique paths that the robot can take to reach the bottom-right corner.

    The testcases are generated so that the answer will be less than or equal to 2 * 10^9.
    

    Examples:
    ---------
    Input: obstacleGrid = [ [0,0,0],
                            [0,1,0],
                            [0,0,0]]
    Output: 2
    Explanation: There is one obstacle in the middle of the 3x3 grid above.
    There are two ways to reach the bottom-right corner:
    1. Right -> Right -> Down -> Down
    2. Down -> Down -> Right -> Right

    Input: obstacleGrid = [[0,1],
                           [0,0]]
    Output: 1

    Constraints:
        1 <= m, n <= 100


    Approach:
    ----------
    1. Recursion - 
    2. Memoization - Why possible? Because in recursion we were hitting a cell
    multiple times. The answer of how many ways to reach the bottom right from that
    cell is constant. So we can memoize them.
    3. Bottom Up DP
*/

//Recursion 
class Solution {
private:
    int solve(int r, int c, vector<vector<int>>& grid, int m, int n) {
        //1. BASE CASE
        //if out of bounds then return 0
        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == 1)
            return 0;

        //if reached last cell
        if (r == m - 1 && c == n - 1)
            return 1;

        int right = solve(r, c + 1, grid, m, n);
        int down = solve(r + 1, c, grid, m, n);

        return right + down;
    }
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();

        return solve(0, 0, obstacleGrid, m, n);
    }
};

//Memoization
class Solution {
private:
    int solve(int r, int c, vector<vector<int>>& grid, vector<vector<int>>& dp, int m, int n) {
        //1. BASE CASE
        //if out of bounds then return 0
        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == 1)
            return 0;

        //if reached last cell
        if (r == m - 1 && c == n - 1)
            return dp[r][c] = 1;

        if (dp[r][c] != -1)
            return dp[r][c];

        int right = solve(r, c + 1, grid, dp, m, n);
        int down = solve(r + 1, c, grid, dp, m, n);

        return dp[r][c] = (right + down);
    }
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));

        return solve(0, 0, obstacleGrid, dp, m, n);
    }
};

//Bottom up DP
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        if (obstacleGrid[0][0] == 1)
            return 0;

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));

        for (int r = 0; r <= m - 1; r++) {
            for (int c = 0; c <= n - 1; c++) {
                if (r == 0 && c == 0 && obstacleGrid[r][c] == 1) {
                    dp[r][c] = 0;
                }
                else if (r == 0 && c == 0 && obstacleGrid[r][c] == 0)
                    dp[r][c] = 1;
                else if (obstacleGrid[r][c] == 1)
                    dp[r][c] = 0;
                else if (r == 0)
                    dp[r][c] = dp[r][c - 1];
                else if (c == 0)
                    dp[r][c] = dp[r - 1][c];
                else {
                    dp[r][c] = dp[r - 1][c] + dp[r][c - 1];
                }
            }
        }
        return dp[m - 1][n - 1];
    }
};


int main() {
    Solution obj;
    vector<vector<int>> grid = {{0, 0, 0}, 
                                {0, 1, 0}, 
                                {0, 0, 0}
                               };
    auto ans = obj.uniquePathsWithObstacles(grid);
    cout << ans;
    cout << endl;

    return 0;
}