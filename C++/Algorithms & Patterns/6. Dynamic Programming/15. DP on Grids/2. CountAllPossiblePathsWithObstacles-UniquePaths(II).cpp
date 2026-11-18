#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement: (LeetCode 63 - Unique Paths II)
    ------------------
    A robot is located at the top-left corner of an m x n grid.
    It can only move right or down at any point in time.
    Some cells have obstacles (marked as 1). The robot cannot pass through obstacles.
    How many unique paths are there to reach the bottom-right corner?

    Examples:
    --------
    Input: grid = [[0,0,0],[0,1,0],[0,0,0]]
    Output: 2
    Explanation: There is one obstacle in the middle.
        Path 1: Right → Right → Down → Down
        Path 2: Down → Down → Right → Right

    Input: grid = [[0,1],[0,0]]
    Output: 1

    Constraints:
    ------------
    - m == grid.length, n == grid[i].length
    - 1 <= m, n <= 100
    - grid[i][j] is 0 or 1

    Difference from Unique Paths I:
    - If a cell has obstacle (grid[i][j] == 1), no paths go through it → return 0.
    - Everything else stays the same.

    Evolution of approaches:
    ------------------------
    1. Backtracking (0,0) → (m-1,n-1): explore all paths, totalWays++
    2. Backtracking (m-1,n-1) → (0,0): reverse direction, totalWays++
    3. Backtracking (m-1,n-1) → (0,0): each call RETURNS count (no global variable)
    4. Memoization: cache the return values of approach 3
    5. Bottom-Up: iterative tabulation

    Time: O(m*n) for approaches 4,5. O(2^(m+n)) for approaches 1,2,3.
    Space: O(m*n) for approach 4,5. O(m+n) recursion stack for 1,2,3.
*/

// ============================================================================
// Solution 1: Backtracking from (0,0) → (m-1,n-1), totalWays++
// ============================================================================
class Solution1 {
private:
    void solve(vector<vector<int>>& grid, int i, int j, int m, int n, int& totalWays) {
        // Reached destination
        if (i == m - 1 && j == n - 1) {
            totalWays++;
            return;
        }

        // Out of bounds or obstacle
        if (i >= m || j >= n || grid[i][j] == 1) return;

        // Move down
        solve(grid, i + 1, j, m, n, totalWays);
        // Move right
        solve(grid, i, j + 1, m, n, totalWays);
    }

public:
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        if (grid[0][0] == 1 || grid[m - 1][n - 1] == 1) return 0;
        int totalWays = 0;
        solve(grid, 0, 0, m, n, totalWays);
        return totalWays;
    }
};

// ============================================================================
// Solution 2: Backtracking from (m-1,n-1) → (0,0), totalWays++
// ============================================================================
class Solution2 {
private:
    void solve(vector<vector<int>>& grid, int i, int j, int& totalWays) {
        // Reached origin
        if (i == 0 && j == 0) {
            totalWays++;
            return;
        }

        // Out of bounds or obstacle
        if (i < 0 || j < 0 || grid[i][j] == 1) return;

        // Move up
        solve(grid, i - 1, j, totalWays);
        // Move left
        solve(grid, i, j - 1, totalWays);
    }

public:
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        if (grid[0][0] == 1 || grid[m - 1][n - 1] == 1) return 0;
        int totalWays = 0;
        solve(grid, m - 1, n - 1, totalWays);
        return totalWays;
    }
};

// ============================================================================
// Solution 3: Backtracking from (m-1,n-1) → (0,0), RETURN count
// ============================================================================
// Key step before memoization: return value can be cached.
class Solution3 {
private:
    int solve(vector<vector<int>>& grid, int i, int j) {
        // Out of bounds or obstacle
        if (i < 0 || j < 0 || grid[i][j] == 1) return 0;

        // Reached origin — 1 valid path found
        if (i == 0 && j == 0) return 1;

        // Number of ways = ways from above + ways from left
        return solve(grid, i - 1, j) + solve(grid, i, j - 1);
    }

public:
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        if (grid[0][0] == 1 || grid[m - 1][n - 1] == 1) return 0;
        return solve(grid, m - 1, n - 1);
    }
};

// ============================================================================
// Solution 4: Memoization (Top-Down DP)
// ============================================================================
class Solution4 {
private:
    int solve(vector<vector<int>>& grid, int i, int j, vector<vector<int>>& dp) {
        if (i < 0 || j < 0 || grid[i][j] == 1) return 0;
        if (i == 0 && j == 0) return 1;
        if (dp[i][j] != -1) return dp[i][j];

        dp[i][j] = solve(grid, i - 1, j, dp) + solve(grid, i, j - 1, dp);
        return dp[i][j];
    }

public:
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        if (grid[0][0] == 1 || grid[m - 1][n - 1] == 1) return 0;
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return solve(grid, m - 1, n - 1, dp);
    }
};

// ============================================================================
// Solution 5: Bottom-Up (Tabulation)
// ============================================================================
class Solution5 {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        if (grid[0][0] == 1 || grid[m - 1][n - 1] == 1) return 0;

        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // Obstacle — no paths through here
                if (grid[i][j] == 1) {
                    dp[i][j] = 0;
                }
                // 1 way to reach the starting cell
                else if (i == 0 && j == 0) {
                    dp[i][j] = 1;
                }
                // First row: can only come from left
                // If left cell is 0 (blocked by earlier obstacle), this is also 0
                else if (i == 0) {
                    dp[i][j] = dp[i][j - 1];
                }
                // First col: can only come from above
                else if (j == 0) {
                    dp[i][j] = dp[i - 1][j];
                }
                // General case: from above + from left
                else {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};


int main() {
    Solution1 backtrack1;
    Solution2 backtrack2;
    Solution3 backtrack3;
    Solution4 memo;
    Solution5 bottomUp;

    vector<vector<int>> grid = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };

    cout << "Backtrack (0,0)->(m-1,n-1): " << backtrack1.uniquePathsWithObstacles(grid) << endl; // 2
    cout << "Backtrack (m-1,n-1)->(0,0): " << backtrack2.uniquePathsWithObstacles(grid) << endl; // 2
    cout << "Backtrack return count:     " << backtrack3.uniquePathsWithObstacles(grid) << endl; // 2
    cout << "Memoization:                " << memo.uniquePathsWithObstacles(grid) << endl;       // 2
    cout << "Bottom-Up:                  " << bottomUp.uniquePathsWithObstacles(grid) << endl;   // 2

    return 0;
}
