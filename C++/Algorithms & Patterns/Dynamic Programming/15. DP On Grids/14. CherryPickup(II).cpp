#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement: (LeetCode 1463 - Cherry Pickup II)
    ------------------
    Given a rows x cols grid. Two robots start at:
    - Robot 1: (0, 0) — top-left
    - Robot 2: (0, cols-1) — top-right

    Both move DOWN one row per step. From (i, j) can move to:
    - (i+1, j-1) — down-left
    - (i+1, j)   — down
    - (i+1, j+1) — down-right

    If both robots are at the same cell, only one collects cherries.
    Find the maximum cherries collected by both robots combined.

    Examples:
    --------
    Input: grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
    Output: 24
    Explanation:
        Robot 1: (0,0)→(1,0)→(2,0)→(3,0) collects 3+2+1+2 = 8
        Robot 2: (0,2)→(1,1)→(2,1)→(3,1) collects 1+5+5+1 = 12... total not 24.
        Better paths exist. Optimal = 24.

    Constraints:
    ------------
    - rows == grid.length, cols == grid[i].length
    - 2 <= rows, cols <= 70
    - 0 <= grid[i][j] <= 100

    Key Difference from Cherry Pickup I:
    - Cherry Pickup I: both start at (0,0), move right/down, K dimension trick.
    - Cherry Pickup II: robot1 starts at (0,0), robot2 starts at (0,C-1), both move DOWN.
    - No K trick needed here because both always move to row+1 → row IS the step counter.
    - State: (row, col1, col2) — same as "Two Traversals" problem.
 
    The 9 move combinations (dc1, dc2):
    -----------------------------------------------
    Traversal 1 goes:    Traversal 2 goes:     Combination:
      down-left (-1)       down-left (-1)        (-1, -1)
      down-left (-1)       down (0)              (-1,  0)
      down-left (-1)       down-right (+1)       (-1, +1)
      down (0)             down-left (-1)        ( 0, -1)
      down (0)             down (0)              ( 0,  0)
      down (0)             down-right (+1)       ( 0, +1)
      down-right (+1)      down-left (-1)        (+1, -1)
      down-right (+1)      down (0)              (+1,  0)
      down-right (+1)      down-right (+1)       (+1, +1)

    Recurrence:
        solve(row, col1, col2):
            if row == R: return 0                       // past last row
            if col1 < 0 or col1 >= C: return -INF
            if col2 < 0 or col2 >= C: return -INF

            // Collect cherries (same cell → count once)
            cherries = grid[row][col1]
            if col1 != col2: cherries += grid[row][col2]

            // 9 move combinations: each robot moves down-left, down, or down-right
            maxFuture = -INF
            for dc1 in {-1, 0, 1}:
                for dc2 in {-1, 0, 1}:
                    maxFuture = max(maxFuture, solve(row+1, col1+dc1, col2+dc2))

            return cherries + maxFuture

        Answer: solve(0, 0, C-1)

    Time: O(R * C² * 9) = O(R * C²)
    Space: O(R * C²) for memo, O(C²) for space-optimized.
*/

// ============================================================================
// Solution 1: Recursion
// Time: O(9^R), Space: O(R)
// ============================================================================
class Solution1 {
private:
    int solve(vector<vector<int>>& grid, int row, int col1, int col2, int R, int C) {
        if (col1 < 0 || col1 >= C || col2 < 0 || col2 >= C)
            return 0;
        if (row == R) return 0;

        int cherries = grid[row][col1];
        if (col1 != col2) cherries += grid[row][col2];

        int maxFuture = 0;
        for (int dc1 = -1; dc1 <= 1; dc1++) {
            for (int dc2 = -1; dc2 <= 1; dc2++) {
                maxFuture = max(maxFuture, solve(grid, row + 1, col1 + dc1, col2 + dc2, R, C));
            }
        }

        return cherries + maxFuture;
    }

public:
    int cherryPickup(vector<vector<int>>& grid) {
        int R = grid.size(), C = grid[0].size();
        return solve(grid, 0, 0, C - 1, R, C);
    }
};

// ============================================================================
// Solution 2: Memoization
// Time: O(R * C² * 9) = O(R * C²), Space: O(R * C²)
// ============================================================================
class Solution2 {
private:
    int solve(vector<vector<int>>& grid, int row, int col1, int col2, int R, int C,
              vector<vector<vector<int>>>& dp) {
        if (col1 < 0 || col1 >= C || col2 < 0 || col2 >= C)
            return 0;
        if (row == R) return 0;
        if (dp[row][col1][col2] != -1) return dp[row][col1][col2];

        int cherries = grid[row][col1];
        if (col1 != col2) cherries += grid[row][col2];

        int maxFuture = 0;
        for (int dc1 = -1; dc1 <= 1; dc1++) {
            for (int dc2 = -1; dc2 <= 1; dc2++) {
                maxFuture = max(maxFuture, solve(grid, row + 1, col1 + dc1, col2 + dc2, R, C, dp));
            }
        }

        dp[row][col1][col2] = cherries + maxFuture;
        return dp[row][col1][col2];
    }

public:
    int cherryPickup(vector<vector<int>>& grid) {
        int R = grid.size(), C = grid[0].size();
        vector<vector<vector<int>>> dp(R, vector<vector<int>>(C, vector<int>(C, -1)));
        return solve(grid, 0, 0, C - 1, R, C, dp);
    }
};

// ============================================================================
// Solution 3: Bottom-Up
// Time: O(R * C² * 9) = O(R * C²), Space: O(R * C²)
// ============================================================================
// Direct translation:
//   solve(row, col1, col2):
//     if col1/col2 out of bounds: return -INF
//     if row == R: return 0
//     cherries = grid[row][col1] + (col1 != col2 ? grid[row][col2] : 0)
//     return cherries + max over 9 moves of solve(row+1, col1+dc1, col2+dc2)
//
// Fill from last row to first row (row depends on row+1).
class Solution3 {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int R = grid.size(), C = grid[0].size();
        vector<vector<vector<int>>> dp(R + 1, vector<vector<int>>(C, vector<int>(C, 0)));

        for (int row = R - 1; row >= 0; row--) {
            for (int col1 = 0; col1 < C; col1++) {
                for (int col2 = 0; col2 < C; col2++) {
                    // Collect cherries
                    int cherries = grid[row][col1];
                    if (col1 != col2) cherries += grid[row][col2];

                    // Max of 9 move combinations from row+1
                    int maxFuture = 0;
                    for (int dc1 = -1; dc1 <= 1; dc1++) {
                        for (int dc2 = -1; dc2 <= 1; dc2++) {
                            int nc1 = col1 + dc1, nc2 = col2 + dc2;
                            if (nc1 >= 0 && nc1 < C && nc2 >= 0 && nc2 < C) {
                                maxFuture = max(maxFuture, dp[row + 1][nc1][nc2]);
                            }
                        }
                    }

                    dp[row][col1][col2] = cherries + maxFuture;
                }
            }
        }

        return dp[0][0][C - 1];
    }
};


int main() {
    Solution1 recursion;
    Solution2 memo;
    Solution3 bottomUp;

    vector<vector<int>> grid = {
        {3, 1, 1},
        {2, 5, 1},
        {1, 5, 5},
        {2, 1, 1}
    };

    cout << "Recursion:   " << recursion.cherryPickup(grid) << endl;  // 24
    cout << "Memoization: " << memo.cherryPickup(grid) << endl;       // 24
    cout << "Bottom-Up:   " << bottomUp.cherryPickup(grid) << endl;   // 24

    return 0;
}
