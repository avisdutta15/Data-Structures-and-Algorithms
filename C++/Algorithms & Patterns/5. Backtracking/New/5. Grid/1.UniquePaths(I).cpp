#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

/*
    Problem Statement:
    -----------------
    There is a robot on an m x n grid. The robot is initially located at the top-left corner 
    (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). 
    The robot can only move either down or right at any point in time.

    Given the two integers m and n, return the number of possible unique paths that the 
    robot can take to reach the bottom-right corner.

    The test cases are generated so that the answer will be less than or equal to 2 * 10^9.
    

    Examples:
    ---------
    Input: m = 3, n = 7
    Output: 28

    Input: m = 3, n = 2
    Output: 3
    Explanation: From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
    1. Right -> Down -> Down
    2. Down -> Down -> Right
    3. Down -> Right -> Down

    Constraints:
        1 <= m, n <= 100


    Approach:
    ----------
    1. Recursion - Why we dont need a visited[][] or mark the cell visited? Because only two moves -
                   left, right are allowed. These moves doesnot create a cycle. If there were 4 moves
                   allowed - left, right, top, bottom then we would need a visited concept as it would
                   create cycle.
    2. Memoization - Why possible? Because in recursion we were hitting a cell
    multiple times. The answer of how many ways to reach the bottom right from that
    cell is constant. So we can memoize them.
    3. Bottom Up DP
*/

//Recursion 
class Solution {
private:
    int solve(int r, int c, int m, int n) {
        //1. BASE CASE
        //if reached last cell
        if (r == m - 1 && c == n - 1)
            return 1;

        //if out of bounds then return 0
        if (r<0 || r>=m || c<0 || c>=n)
            return 0;

        int right = solve(r, c + 1, m, n);
        int down = solve(r + 1, c, m, n);

        return right + down;
    }
public:
    int uniquePaths(int m, int n) {
        return solve(0, 0, m, n);
    }
}; 

//Memoization
class Solution {
private:
    int solve(int r, int c, int m, int n, vector<vector<int>>& dp) {
        //1. BASE CASE
        //if reached last cell
        if (r == m - 1 && c == n - 1)
            return dp[r][c] = 1;

        //if out of bounds then return 0
        if (r<0 || r>=m || c<0 || c>=n)
            return 0;

        if (dp[r][c] != -1)
            return dp[r][c];

        int right = solve(r, c + 1, m, n, dp);
        int down = solve(r + 1, c, m, n, dp);

        return dp[r][c] = (right + down);
    }
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));
        solve(0, 0, m, n, dp);
        return dp[0][0];
    }
};

//Bottom up DP
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));

        for (int r = 0; r <= m - 1; r++) {
            for (int c = 0; c <= n - 1; c++) {

                //1 way to reach the starting cell
                if (r == 0 && c == 0)
                    dp[r][c] = 1;
                //1 way to reach this cell in first row. Take right
                else if (r == 0)
                    dp[r][c] = 1;
                //1 way to reach this cell in first col. Take down.
                else if (c == 0)
                    dp[r][c] = 1;
                else {
                    //can reach this cell either from top or left.
                    //total ways = ways from top + ways from left
                    dp[r][c] = dp[r - 1][c] + dp[r][c - 1];
                }
            }
        }

        //return the total ways to reach the last cell.
        return dp[m - 1][n - 1];
    }
};

int main() {
    Solution obj;
    auto ans = obj.uniquePaths(3, 7);
    cout << ans;
    cout << endl;

    return 0;
}