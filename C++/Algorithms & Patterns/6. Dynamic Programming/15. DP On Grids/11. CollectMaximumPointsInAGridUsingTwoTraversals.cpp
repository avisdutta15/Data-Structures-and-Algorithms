#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement: Collect Maximum Points in a Grid Using Two Traversals
    ------------------
    Given an R x C grid with points in each cell. Two traversals happen simultaneously:
    - Traversal 1: starts at (0, 0) — top-left corner
    - Traversal 2: starts at (0, C-1) — top-right corner

    Both move downward. From cell (i, j), can move to:
    - (i+1, j-1) — down-left
    - (i+1, j)   — down
    - (i+1, j+1) — down-right

    If both traversals are at the same cell, points are collected only once.
    Find the maximum total points collected by both traversals combined.

    Example:
    --------
    Input:
        3 6 8 2
        5 2 4 3
        1 1 20 10
        1 1 20 10
        1 1 20 10
    Output: 73

    Constraints:
    ------------
    - 1 <= R, C <= 100

    Approach:
    ---------
    Key insight: Both traversals move together row by row (they're always on the same row).
    So we track BOTH positions simultaneously.

    State: (row, col1, col2) where col1 = column of traversal 1, col2 = column of traversal 2.

    At each step, both make one of 3 moves (down-left, down, down-right).
    Total combinations per step = 3 * 3 = 9.

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

    Both traversals are always on the same row (they move down together),
    so row is shared — we only track (row, col1, col2).

    Recurrence:
        solve(row, col1, col2):
            if row == R: return 0               // past last row
            if col1 < 0 or col1 >= C: return -INF   // out of bounds
            if col2 < 0 or col2 >= C: return -INF

            // Collect points (if same cell, count once)
            points = grid[row][col1]
            if col1 != col2:
                points += grid[row][col2]

            // Try all 9 combinations of moves for both traversals
            maxFuture = -INF
            for dc1 in {-1, 0, 1}:
                for dc2 in {-1, 0, 1}:
                    maxFuture = max(maxFuture, solve(row+1, col1+dc1, col2+dc2))

            return points + maxFuture

        Answer: solve(0, 0, C-1)

    This is essentially the same as Cherry Pickup II (LeetCode 1463).

    Time: O(R * C * C * 9) = O(R * C²)
    Space: O(R * C²) for memoization, O(C²) for space-optimized bottom-up.
*/

// ============================================================================
// Solution 1: Recursion
// Time: O(9^R), Space: O(R) recursion stack
// ============================================================================
class Solution1 {
private:
    int solve(vector<vector<int>>& grid, int row, int col1, int col2, int R, int C) {
        // Base Case: Out of bounds
        if (col1 < 0 || col1 >= C || col2 < 0 || col2 >= C)
            return INT_MIN;

        // Base Case: Past last row
        if (row == R) 
            return 0;

        // Collect points (if same cell → count once)
        int points = grid[row][col1];
        if (col1 != col2)
            points += grid[row][col2];

        // Try all 9 move combinations
        // {-1, 0, 1} * {-1, 0, 1}
        int maxFuture = INT_MIN;
        for (int dirC1 = -1; dirC1 <= 1; dirC1++) {
            for (int dirC2 = -1; dirC2 <= 1; dirC2++) {
                int future = solve(grid, row + 1, col1 + dirC1, col2 + dirC2, R, C);
                maxFuture = max(maxFuture, future);
            }
        }

        // return the maximum points collected at this cell
        return points + maxFuture;
    }

public:
    int maxPoints(vector<vector<int>>& grid) {
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
        // Base Case: Out of bounds
        if (col1 < 0 || col1 >= C || col2 < 0 || col2 >= C)
            return INT_MIN;

        // Base Case: Past last row
        if (row == R)
            return 0;

        // Check cache
        if (dp[row][col1][col2] != -1) 
            return dp[row][col1][col2];

        // Collect points (if same cell → count once)
        int points = grid[row][col1];
        if (col1 != col2)
            points += grid[row][col2];

        // Try all 9 move combinations
        // {-1, 0, 1} * {-1, 0, 1}
        int maxFuture = INT_MIN;
        for (int dirC1 = -1; dirC1 <= 1; dirC1++) {
            for (int dirC2 = -1; dirC2 <= 1; dirC2++) {
                int future = solve(grid, row + 1, col1 + dirC1, col2 + dirC2, R, C, dp);
                maxFuture = max(maxFuture, future);
            }
        }

        // return the maximum points collected at this cell
        return dp[row][col1][col2] = points + maxFuture;
    }

public:
    int maxPoints(vector<vector<int>>& grid) {
        int R = grid.size(), C = grid[0].size();
        // dp[row][col1][col2] : where col1 = column of traversal 1, col2 = column of traversal 2 at the same row
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
//     points = grid[row][col1] + (col1 != col2 ? grid[row][col2] : 0)
//     return points + max over 9 moves of solve(row+1, col1+dc1, col2+dc2)
//
// Fill from last row to first row.
class Solution3 {
public:
    int maxPoints(vector<vector<int>>& grid) {
        int R = grid.size(), C = grid[0].size();
        // dp[row][col1][col2]
        vector<vector<vector<int>>> dp(R + 1, vector<vector<int>>(C, vector<int>(C, 0)));

        // start from last row
        for (int row = R - 1; row >= 0; row--) {
            for (int col1 = 0; col1 < C; col1++) {
                for (int col2 = 0; col2 < C; col2++) {

                    // Base case: if out of bounds, skip (or treat as -INF)
                    if (col1 < 0 || col1 >= C || col2 < 0 || col2 >= C)
                        continue;

                    // Collect points (if same cell → count once)
                    int points = grid[row][col1];
                    if (col1 != col2)
                        points += grid[row][col2];

                    // Try all 9 move combinations
                    int maxFuture = INT_MIN;
                    for (int dirC1 = -1; dirC1 <= 1; dirC1++) {
                        for (int dirC2 = -1; dirC2 <= 1; dirC2++) {
                            int nc1 = col1 + dirC1;
                            int nc2 = col2 + dirC2;
                            // Out of bounds → skip (same as returning -INF)
                            if (nc1 < 0 || nc1 >= C || nc2 < 0 || nc2 >= C)
                                continue;
                            maxFuture = max(maxFuture, dp[row + 1][nc1][nc2]);
                        }
                    }

                    // If no valid future move exists (all out of bounds), maxFuture stays -INF
                    // For the last row, dp[row+1] is all 0s, so maxFuture = 0.
                    dp[row][col1][col2] = points + (maxFuture == INT_MIN ? 0 : maxFuture);
                }
            }
        }

        // Answer is at starting positions: (0, 0) and (0, C-1)
        return dp[0][0][C - 1];
    }
};


int main() {
    Solution1 recursion;
    Solution2 memo;
    Solution3 bottomUp;

    vector<vector<int>> grid = {
        {3, 6, 8, 2},
        {5, 2, 4, 3},
        {1, 1, 20, 10},
        {1, 1, 20, 10},
        {1, 1, 20, 10}
    };

    cout << "Recursion:   " << recursion.maxPoints(grid) << endl;  // 73
    cout << "Memoization: " << memo.maxPoints(grid) << endl;       // 73
    cout << "Bottom-Up:   " << bottomUp.maxPoints(grid) << endl;   // 73

    return 0;
}
