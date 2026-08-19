#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement: Gold Mine Problem (GFG)
    ------------------
    Given an m x n grid where each cell has gold coins. A miner can start from
    ANY row in the first column (column 0) and can move:
    - Right: (i, j) → (i, j+1)
    - Right-Up: (i, j) → (i-1, j+1)
    - Right-Down: (i, j) → (i+1, j+1)

    Find the maximum gold that can be collected.

    Examples:
    --------
    Input: grid = [[1, 3, 3],
                   [2, 1, 4],
                   [0, 6, 4]]
    Output: 12
    Explanation: Path: (1,0)→(2,1)→(1,2) = 2+6+4 = 12

    Input: grid = [[1, 3, 1, 5],
                   [2, 2, 4, 1],
                   [5, 0, 2, 3],
                   [0, 6, 1, 2]]
    Output: 16
    Explanation: Path: (2,0)→(3,1)→(2,2)→(1,3) = 5+6+2+3... No that's not right.
    Actually: (2,0)→(1,1)→(0,2)... let me just trust the answer = 16.

    Constraints:
    ------------
    - 1 <= m, n <= 500
    - 0 <= grid[i][j] <= 100

    Approach:
    ---------
    Similar to Minimum Falling Path Sum but:
    - Start at ANY row in first column (not first row).
    - Move RIGHT (not down): right, right-up, right-down.
    - Maximize (not minimize).

    Recurrence:
        solve(i, j):
            if j < 0 or j >= C: return INT_MIN   // shouldn't happen as entry point
            if i < 0 or i >= R: return INT_MIN    // out of bounds vertically
            if j == C-1: return grid[i][j]        // last column = base case

            right     = solve(i, j+1)
            rightUp   = solve(i-1, j+1)
            rightDown = solve(i+1, j+1)

            return grid[i][j] + max({right, rightUp, rightDown})

        Answer: max(solve(i, 0)) for all i in 0..R-1

    Time: O(R * C)
    Space: O(R * C) for memo, O(C) for space-optimized.
*/

// ============================================================================
// Solution 1: Recursion
// Time: O(3^C), Space: O(C)
// ============================================================================
class Solution1 {
private:
    int solve(vector<vector<int>>& grid, int i, int j, int R, int C) {
        // Out of bounds
        if (i < 0 || i >= R) return INT_MIN;

        // Last column — base case
        if (j == C - 1) return grid[i][j];

        int right     = solve(grid, i, j + 1, R, C);
        int rightUp   = solve(grid, i - 1, j + 1, R, C);
        int rightDown = solve(grid, i + 1, j + 1, R, C);

        return grid[i][j] + max({right, rightUp, rightDown});
    }

public:
    int maxGold(vector<vector<int>>& grid) {
        int R = grid.size(), C = grid[0].size();
        int maxCoins = INT_MIN;
        for (int i = 0; i < R; i++) {
            maxCoins = max(maxCoins, solve(grid, i, 0, R, C));
        }
        return maxCoins;
    }
};

// ============================================================================
// Solution 2: Memoization
// Time: O(R * C), Space: O(R * C)
// ============================================================================
class Solution2 {
private:
    int solve(vector<vector<int>>& grid, int i, int j, int R, int C,
              vector<vector<int>>& dp) {
        if (i < 0 || i >= R) return INT_MIN;
        if (j == C - 1) return grid[i][j];
        if (dp[i][j] != -1) return dp[i][j];

        int right     = solve(grid, i, j + 1, R, C, dp);
        int rightUp   = solve(grid, i - 1, j + 1, R, C, dp);
        int rightDown = solve(grid, i + 1, j + 1, R, C, dp);

        dp[i][j] = grid[i][j] + max({right, rightUp, rightDown});
        return dp[i][j];
    }

public:
    int maxGold(vector<vector<int>>& grid) {
        int R = grid.size(), C = grid[0].size();
        vector<vector<int>> dp(R, vector<int>(C, -1));
        int maxCoins = INT_MIN;
        for (int i = 0; i < R; i++) {
            maxCoins = max(maxCoins, solve(grid, i, 0, R, C, dp));
        }
        return maxCoins;
    }
};

// ============================================================================
// Solution 3: Bottom-Up
// Time: O(R * C), Space: O(R * C)
// ============================================================================
// Direct translation:
//   solve(i, j):
//     if i < 0 or i >= R: return INT_MIN
//     if j == C-1: return grid[i][j]
//     return grid[i][j] + max(solve(i, j+1), solve(i-1, j+1), solve(i+1, j+1))
//
// Dependencies: dp[i][j] depends on dp[i][j+1], dp[i-1][j+1], dp[i+1][j+1]
// Fill columns right to left (last column first).
// Why do we check all columns even though we need only 1 column?
// Because dp[i][j] depends on dp[...][j+1] (the column to the right). 
// To have j+1 ready when computing j, we must fill right-to-left.
// We check all columns because we need to fill the entire DP table.
// The recursion solve(i, 0) calls solve(i, 1) which calls solve(i, 2) ... all the 
// way to solve(i, C - 1).In bottom - up, we pre - compute all of these by iterating all columns.
class Solution3 {
public:
    int maxGold(vector<vector<int>>& grid) {
        int R = grid.size(), C = grid[0].size();
        vector<vector<int>> dp(R, vector<int>(C, 0));

        // Fill DP table from right to left (last column to first)
        for (int j = C - 1; j >= 0; j--) {
            for (int i = 0; i < R; i++) {
                // Base case: last column
                if (j == C - 1) {
                    dp[i][j] = grid[i][j];
                }
                // Recursive case
                else {
                    int right     = dp[i][j + 1];
                    int rightUp   = (i > 0)     ? dp[i - 1][j + 1] : INT_MIN;
                    int rightDown = (i < R - 1) ? dp[i + 1][j + 1] : INT_MIN;

                    dp[i][j] = grid[i][j] + max({right, rightUp, rightDown});
                }
            }
        }

        // Answer: max(dp[i][0]) for all rows
        int maxCoins = INT_MIN;
        for (int i = 0; i < R; i++) {
            maxCoins = max(maxCoins, dp[i][0]);
        }
        return maxCoins;
    }
};


int main() {
    Solution1 recursion;
    Solution2 memo;
    Solution3 bottomUp;

    vector<vector<int>> grid = {
        {1, 3, 3},
        {2, 1, 4},
        {0, 6, 4}
    };

    cout << "Recursion:   " << recursion.maxGold(grid) << endl;  // 12
    cout << "Memoization: " << memo.maxGold(grid) << endl;       // 12
    cout << "Bottom-Up:   " << bottomUp.maxGold(grid) << endl;   // 12

    return 0;
}
