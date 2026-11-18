#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement: Number of Paths with Exactly K Coins
    ------------------
    Given an m x n grid where each cell has some coins, find the number of paths
    from (0,0) to (m-1,n-1) that collect exactly K coins.
    You can only move right or down.

    Examples:
    --------
    Input: grid = [[1, 2, 3],
                   [4, 6, 5],
                   [3, 2, 1]], K = 12
    Output: 2
    Explanation:
        Path 1: 1 → 2 → 3 → 5 → 1 = 12 (right, right, down, down)
        Path 2: 1 → 4 → 6 → 5 → 1 = but that's not 12... let me recompute
        Actually: 1→2→6→2→1=12, 1→4→6→5→1=17 No...
        Path 1: (0,0)→(0,1)→(0,2)→(1,2)→(2,2) = 1+2+3+5+1 = 12 ✓
        Path 2: (0,0)→(1,0)→(1,1)→(1,2)→(2,2) = 1+4+6+5+1 = 17 ✗
        Path 3: (0,0)→(0,1)→(1,1)→(2,1)→(2,2) = 1+2+6+2+1 = 12 ✓

    Constraints:
    ------------
    - 1 <= m, n <= 100
    - 0 <= grid[i][j] <= 100
    - 0 <= K <= 10000

    Approach:
    ---------
    This is a 3D DP problem. State: (row, col, coinsRemaining).
    At each cell, we collect grid[i][j] coins. We need to reach (m-1,n-1) with
    exactly 0 coins remaining (started with K, spent K along the way).

    Recurrence:
        solve(i, j, k):
            if i < 0 or j < 0: return 0                    // out of bounds
            if i == 0 and j == 0:
                return (k == grid[0][0]) ? 1 : 0            // base case: at start, coins must match
            if k < 0: return 0                              // can't have negative coins

            // arrive at (i,j) from above or left, with k-grid[i][j] coins remaining before
            return solve(i-1, j, k - grid[i][j]) + solve(i, j-1, k - grid[i][j])

    Answer: solve(m-1, n-1, K)

    Time: O(m * n * K)
    Space: O(m * n * K)
*/

// ============================================================================
// Solution 1: Recursion (Brute Force)
// Time: O(2^(m+n)), Space: O(m+n)
// ============================================================================
class Solution1 {
private:
    int solve(vector<vector<int>>& grid, int i, int j, int coinsRemaining) {
        // Out of bounds
        if (i < 0 || j < 0) 
            return 0;

        // Base case: at (0,0), coins remaining must equal grid[0][0]
        if (i == 0 && j == 0) {
            return (coinsRemaining == grid[0][0]) ? 1 : 0;
        }

        // can't have negative coins
        if (coinsRemaining < 0)
            return 0;

        // From above + from left (subtract current cell's coins from k)
        return solve(grid, i - 1, j, coinsRemaining - grid[i][j])
             + solve(grid, i, j - 1, coinsRemaining - grid[i][j]);
    }

public:
    int numberOfPaths(vector<vector<int>>& grid, int K) {
        int m = grid.size();
        int n = grid[0].size();
        return solve(grid, m - 1, n - 1, K);
    }
};

// ============================================================================
// Solution 2: Memoization (Top-Down DP)
// Time: O(m * n * K), Space: O(m * n * K)
// ============================================================================
class Solution2 {
private:
    int solve(vector<vector<int>>& grid, int i, int j, int coinsRemaining, vector<vector<vector<int>>>& dp) {
        // Out of bounds
        if (i < 0 || j < 0)
            return 0;

        // Base case: at (0,0), coins remaining must equal grid[0][0]
        if (i == 0 && j == 0) {
            return (coinsRemaining == grid[0][0]) ? 1 : 0;
        }

        // can't have negative coins
        if (coinsRemaining < 0)
            return 0;

        if (dp[i][j][coinsRemaining] != -1) 
            return dp[i][j][coinsRemaining];

        // From above + from left (subtract current cell's coins from k)
        return dp[i][j][coinsRemaining] = solve(grid, i - 1, j, coinsRemaining - grid[i][j], dp)
                                        + solve(grid, i, j - 1, coinsRemaining - grid[i][j], dp);
    }

public:
    int numberOfPaths(vector<vector<int>>& grid, int K) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(K + 1, -1)));
        return solve(grid, m - 1, n - 1, K, dp);
    }
};

// ============================================================================
// Solution 3: Bottom-Up (Tabulation)
// Time: O(m * n * K), Space: O(m * n * K)
// ============================================================================
// Direct translation:
//   solve(i, j, k):
//     if i < 0 or j < 0 or k < 0: return 0
//     if i == 0 and j == 0: return (k == grid[0][0]) ? 1 : 0
//     return solve(i-1, j, k-grid[i][j]) + solve(i, j-1, k-grid[i][j])
class Solution3 {
public:
    int numberOfPaths(vector<vector<int>>& grid, int K) {
        int m = grid.size();
        int n = grid[0].size();

        // dp[i][j][k] = number of paths from (0,0) to (i,j) collecting exactly k coins
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(K + 1, 0)));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k <= K; k++) {
                    // Base case: at (0,0), k must equal grid[0][0]
                    if (i == 0 && j == 0) {
                        dp[i][j][k] = (k == grid[0][0]) ? 1 : 0;
                    }
                    else {
                        // We must have enough coins to cover this cell's value
                        int remaining = k - grid[i][j];
                        if (remaining < 0) {
                            dp[i][j][k] = 0;
                        }
                        else {
                            int fromAbove = (i > 0) ? dp[i - 1][j][remaining] : 0;
                            int fromLeft = (j > 0) ? dp[i][j - 1][remaining] : 0;
                            dp[i][j][k] = fromAbove + fromLeft;
                        }                        
                    }
                }
            }
        }

        // The answer is the number of paths to reach (m-1, n-1) from (0,0) with exactly K coins
        return dp[m - 1][n - 1][K];
    }
};


int main() {
    Solution1 recursion;
    Solution2 memo;
    Solution3 bottomUp;

    vector<vector<int>> grid = {
        {1, 2, 3},
        {4, 6, 5},
        {3, 2, 1}
    };
    int K = 12;

    cout << "Recursion:   " << recursion.numberOfPaths(grid, K) << endl;  // 2
    cout << "Memoization: " << memo.numberOfPaths(grid, K) << endl;       // 2
    cout << "Bottom-Up:   " << bottomUp.numberOfPaths(grid, K) << endl;   // 2

    return 0;
}
