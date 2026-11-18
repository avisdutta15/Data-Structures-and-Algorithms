#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement: Collect Maximum Coins Before Hitting a Dead End (GFG)
    ------------------
    Given an m x n character matrix where:
      'C' → cell has a coin
      '#' → blocking cell (dead end, can't pass)
      'E' → empty cell (no coin, but can move through)

    Start at (0, 0) facing RIGHT.

    Movement rules:
    - If facing RIGHT:
        1. Move to (i, j+1) — keep facing right
        2. Move to (i+1, j) — now face LEFT
    - If facing LEFT:
        1. Move to (i, j-1) — keep facing left
        2. Move to (i+1, j) — now face RIGHT

    Final position can be anywhere. Collect maximum coins.

    Example:
    --------
    Input:
        E C C C C
        C # C # E
        # C C E C

    Output: 8 (collect 8 coins following the zigzag path)

    Approach:
    ---------
    3D DP: state = (row, col, direction).
    Direction: 0 = RIGHT, 1 = LEFT.

    Recurrence:
        solve(i, j, dir):
            if out of bounds or grid[i][j] == '#': return 0

            coins = (grid[i][j] == 'C') ? 1 : 0

            if dir == RIGHT (0):
                moveForward = solve(i, j+1, RIGHT)    // keep going right
                moveDown    = solve(i+1, j, LEFT)     // turn down and face left
            else: // dir == LEFT (1):
                moveForward = solve(i, j-1, LEFT)     // keep going left
                moveDown    = solve(i+1, j, RIGHT)    // turn down and face right

            return coins + max(moveForward, moveDown)

        Answer: solve(0, 0, RIGHT)

    Time: O(m * n * 2) = O(m * n)
    Space: O(m * n * 2) = O(m * n)
*/

// ============================================================================
// Solution 1: Recursion
// Time: O(2^(m+n)), Space: O(m+n)
// ============================================================================
class Solution1 {
private:
    int solve(vector<string>& grid, int i, int j, int dir, int m, int n) {
        // Base Case: Out of bounds
        if (i < 0 || i >= m || j < 0 || j >= n)
            return 0;

        // Base Case: if dead end
        if (grid[i][j] == '#')
            return 0;

        int coinsAtThisCell = (grid[i][j] == 'C') ? 1 : 0;

        if (dir == 0) { // Facing RIGHT
            int moveForward = solve(grid, i, j + 1, 0, m, n); // right, stay right
            int moveDown    = solve(grid, i + 1, j, 1, m, n); // down, face left
            return coinsAtThisCell + max(moveForward, moveDown);
        } else { // Facing LEFT
            int moveForward = solve(grid, i, j - 1, 1, m, n); // left, stay left
            int moveDown    = solve(grid, i + 1, j, 0, m, n); // down, face right
            return coinsAtThisCell + max(moveForward, moveDown);
        }
    }

public:
    int maxCoins(vector<string>& grid) {
        int m = grid.size(), n = grid[0].size();
        return solve(grid, 0, 0, 0, m, n); // start at (0,0) facing RIGHT
    }
};

// ============================================================================
// Solution 2: Memoization
// Time: O(m * n * 2), Space: O(m * n * 2)
// ============================================================================
class Solution2 {
private:
    int solve(vector<string>& grid, int i, int j, int dir, int m, int n,
              vector<vector<vector<int>>>& dp) {
        // Base Case: Out of bounds
        if (i < 0 || i >= m || j < 0 || j >= n)
            return 0;

        // Base Case: if dead end
        if (grid[i][j] == '#')
            return 0;
        
        // Check cache
        if (dp[i][j][dir] != -1) 
            return dp[i][j][dir];

        int coinsAtThisCell = (grid[i][j] == 'C') ? 1 : 0;

        if (dir == 0) {
            int moveForward = solve(grid, i, j + 1, 0, m, n, dp);
            int moveDown    = solve(grid, i + 1, j, 1, m, n, dp);
            dp[i][j][dir] = coinsAtThisCell + max(moveForward, moveDown);
        } else {
            int moveForward = solve(grid, i, j - 1, 1, m, n, dp);
            int moveDown    = solve(grid, i + 1, j, 0, m, n, dp);
            dp[i][j][dir] = coinsAtThisCell + max(moveForward, moveDown);
        }

        return dp[i][j][dir];
    }

public:
    int maxCoins(vector<string>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(2, -1)));
        return solve(grid, 0, 0, 0, m, n, dp);
    }
};

// ============================================================================
// Solution 3: Bottom-Up
// Time: O(m * n * 2), Space: O(m * n * 2)
// ============================================================================
// Fill from last row to first row (since we move downward).
// For each cell, compute dp[i][j][dir]:
//   dir=0 (RIGHT): depends on dp[i][j+1][0] and dp[i+1][j][1]
//   dir=1 (LEFT):  depends on dp[i][j-1][1] and dp[i+1][j][0]
//
// For dir=0 (RIGHT), j+1 means we need to process columns LEFT to RIGHT.
// For dir=1 (LEFT), j-1 means we need to process columns RIGHT to LEFT.
class Solution3 {
public:
    int maxCoins(vector<string>& grid) {
        int m = grid.size(), n = grid[0].size();
        // dp[i][j][dir]: max coins from (i,j) facing dir
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(2, 0)));

        // Fill from bottom row to top row
        for (int i = m - 1; i >= 0; i--) {

            // dir = 0 (RIGHT): depends on (i, j+1) → process left to right
            for (int j = n - 1; j >= 0; j--) {
                // if blocking cell then no coins can be collected.
                if (grid[i][j] == '#'){ 
                        dp[i][j][0] = 0; 
                        continue; 
                }
                int coinsAtThisCell = (grid[i][j] == 'C') ? 1 : 0;
                int moveForward = (j + 1 < n && grid[i][j+1] != '#') ? dp[i][j + 1][0] : 0;
                int moveDown    = (i + 1 < m && grid[i+1][j] != '#') ? dp[i + 1][j][1] : 0;
                dp[i][j][0] = coinsAtThisCell + max(moveForward, moveDown);
            }

            // dir = 1 (LEFT): depends on (i, j-1) → process right to left
            for (int j = 0; j < n; j++) {
                // if blocking cell then no coins can be collected.
                if (grid[i][j] == '#') {
                    dp[i][j][1] = 0;
                    continue;
                }
                int coinsAtThisCell = (grid[i][j] == 'C') ? 1 : 0;
                int moveForward = (j - 1 >= 0 && grid[i][j-1] != '#') ? dp[i][j - 1][1] : 0;
                int moveDown    = (i + 1 < m && grid[i+1][j] != '#') ? dp[i + 1][j][0] : 0;
                dp[i][j][1] = coinsAtThisCell + max(moveForward, moveDown);
            }
        }

        return dp[0][0][0]; // start at (0,0) facing RIGHT
    }
};


int main() {
    Solution1 recursion;
    Solution2 memo;
    Solution3 bottomUp;

    vector<string> grid = {
        "ECCCC",
        "C#C#E",
        "#CCEC"
    };

    cout << "Recursion:   " << recursion.maxCoins(grid) << endl;  // 8
    cout << "Memoization: " << memo.maxCoins(grid) << endl;       // 8
    cout << "Bottom-Up:   " << bottomUp.maxCoins(grid) << endl;   // 8

    return 0;
}
