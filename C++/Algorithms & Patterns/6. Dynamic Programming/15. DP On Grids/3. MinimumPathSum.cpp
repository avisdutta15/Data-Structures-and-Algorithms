#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement: (LeetCode 64 - Minimum Path Sum)
    ------------------
    Given an m x n grid filled with non-negative numbers, find a path from
    top-left to bottom-right which minimizes the sum of all numbers along its path.
    You can only move right or down at any point in time.

    Examples:
    --------
    Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
    Output: 7
    Explanation: Path 1→3→1→1→1 = 7 (right, right, down, down)
                 Path 1→1→4→2→1 = 9
                 Path 1→1→5→1→1 = 9
                 Minimum = 7

    Input: grid = [[1,2,3],[4,5,6]]
    Output: 12

    Constraints:
    ------------
    - m == grid.length, n == grid[i].length
    - 1 <= m, n <= 200
    - 0 <= grid[i][j] <= 200

    Difference from Unique Paths:
    - Instead of counting paths, we find the MINIMUM cost path.
    - Instead of adding counts (dp[i-1][j] + dp[i][j-1]),
      we take minimum (min(dp[i-1][j], dp[i][j-1])) + current cell cost.

    Evolution of approaches:
    ------------------------
    1. Backtracking (0,0) → (m-1,n-1): track path cost, update global min
    2. Backtracking (m-1,n-1) → (0,0): reverse, track path cost, update global min
    3. Backtracking (m-1,n-1) → (0,0): return min cost to reach (0,0)
    4. Memoization: cache the return values
    5. Bottom-Up: iterative tabulation

    Time: O(m*n) for approaches 4,5. O(2^(m+n)) for approaches 1,2,3.
    Space: O(m*n) for approach 4,5. O(m+n) recursion stack for 1,2,3.

    Can we use Dijkstra?
    --------------------
    Yes, but it's overkill. The grid is a weighted graph (edges go right/down,
    weight = destination cell value). Dijkstra works since weights are non-negative.

    But Dijkstra = O(m*n * log(m*n)) vs DP = O(m*n). The log factor is unnecessary.

    Why DP is sufficient here:
    - Movement is restricted to right/down → no cycles → DAG.
    - DAG has natural topological order (top-left to bottom-right).
    - DP exploits this order directly.

    When you NEED Dijkstra on a grid:
    - 4-directional movement (up/down/left/right) → cycles possible → no topological order.
    - Examples: LC 1631 (Path With Minimum Effort), LC 778 (Swim in Rising Water).
*/

// ============================================================================
// Solution 1: Backtracking from (0,0) → (m-1,n-1), update minCost
// ============================================================================
class Solution1 {
private:
    void solve(vector<vector<int>>& grid, int i, int j, int m, int n,
               int currentCost, int& minCost) {
        // Reached destination
        if (i == m - 1 && j == n - 1) {
            minCost = min(minCost, currentCost + grid[i][j]);
            return;
        }

        // Out of bounds
        if (i >= m || j >= n) return;

        // Pruning: if current cost already exceeds min, stop
        if (currentCost + grid[i][j] >= minCost) return;

        // Move down
        solve(grid, i + 1, j, m, n, currentCost + grid[i][j], minCost);
        // Move right
        solve(grid, i, j + 1, m, n, currentCost + grid[i][j], minCost);
    }

public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int minCost = INT_MAX;
        solve(grid, 0, 0, m, n, 0, minCost);
        return minCost;
    }
};

// ============================================================================
// Solution 2: Backtracking from (m-1,n-1) → (0,0), update minCost
// ============================================================================
class Solution2 {
private:
    void solve(vector<vector<int>>& grid, int i, int j,
               int currentCost, int& minCost) {
        // Reached origin
        if (i == 0 && j == 0) {
            minCost = min(minCost, currentCost + grid[i][j]);
            return;
        }

        // Out of bounds
        if (i < 0 || j < 0) return;

        // Pruning
        if (currentCost + grid[i][j] >= minCost) return;

        // Move up
        solve(grid, i - 1, j, currentCost + grid[i][j], minCost);
        // Move left
        solve(grid, i, j - 1, currentCost + grid[i][j], minCost);
    }

public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int minCost = INT_MAX;
        solve(grid, m - 1, n - 1, 0, minCost);
        return minCost;
    }
};

// ============================================================================
// Solution 3: Backtracking from (m-1,n-1) → (0,0), RETURN min cost
// ============================================================================
// Each call returns the minimum cost to reach (0,0) from (i,j).
// Key step before memoization.
class Solution3 {
private:
    int solve(vector<vector<int>>& grid, int i, int j) {
        // Out of bounds
        if (i < 0 || j < 0) 
            return INT_MAX;

        // Reached origin — cost is just this cell
        if (i == 0 && j == 0) 
            return grid[i][j];

        // Min cost = current cell + min(cost from above, cost from left)
        int fromAbove = solve(grid, i - 1, j);
        int fromLeft = solve(grid, i, j - 1);
        return grid[i][j] + min(fromAbove, fromLeft);
    }

public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        return solve(grid, m - 1, n - 1);
    }
};

// ============================================================================
// Solution 4: Memoization (Top-Down DP)
// ============================================================================
class Solution4 {
private:
    int solve(vector<vector<int>>& grid, int i, int j, vector<vector<int>>& dp) {
        if (i < 0 || j < 0) return INT_MAX;
        if (i == 0 && j == 0) return grid[i][j];
        if (dp[i][j] != -1) return dp[i][j];

        int fromAbove = solve(grid, i - 1, j, dp);
        int fromLeft = solve(grid, i, j - 1, dp);
        dp[i][j] = grid[i][j] + min(fromAbove, fromLeft);
        return dp[i][j];
    }

public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return solve(grid, m - 1, n - 1, dp);
    }
};

// ============================================================================
// Solution 5: Bottom-Up (Tabulation)
// ============================================================================
class Solution5 {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // Starting cell — cost is just its value
                if (i == 0 && j == 0) {
                    dp[i][j] = grid[i][j];
                }
                // First row — can only come from left (accumulate)
                else if (i == 0) {
                    dp[i][j] = grid[i][j] + dp[i][j - 1];
                }
                // First col — can only come from above (accumulate)
                else if (j == 0) {
                    dp[i][j] = grid[i][j] + dp[i - 1][j];
                }
                // General case — min of above and left + current cell
                else {
                    dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
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
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };

    cout << "Backtrack (0,0)->(m-1,n-1): " << backtrack1.minPathSum(grid) << endl; // 7
    cout << "Backtrack (m-1,n-1)->(0,0): " << backtrack2.minPathSum(grid) << endl; // 7
    cout << "Backtrack return min cost:  " << backtrack3.minPathSum(grid) << endl; // 7
    cout << "Memoization:                " << memo.minPathSum(grid) << endl;       // 7
    cout << "Bottom-Up:                  " << bottomUp.minPathSum(grid) << endl;   // 7

    return 0;
}
