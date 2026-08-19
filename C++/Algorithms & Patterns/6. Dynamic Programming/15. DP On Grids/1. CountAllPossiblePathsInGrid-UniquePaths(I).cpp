#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement: (LeetCode 62 - Unique Paths)
    ------------------
    A robot is located at the top-left corner of an m x n grid.
    It can only move right or down at any point in time.
    How many unique paths are there to reach the bottom-right corner?

    Examples:
    --------
    Input: m = 3, n = 7
    Output: 28

    Input: m = 3, n = 2
    Output: 3

    Constraints:
    ------------
    - 1 <= m, n <= 100

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
// Start at (0,0). Move right or down. When we reach (m-1,n-1), increment count.
class Solution1 {
private:
    void solve(int i, int j, int m, int n, int& totalWays) {
        // Reached destination
        if (i == m - 1 && j == n - 1) {
            totalWays++;
            return;
        }

        // Out of bounds
        if (i >= m || j >= n) 
            return;

        // Move down
        solve(i + 1, j, m, n, totalWays);
        // Move right
        solve(i, j + 1, m, n, totalWays);
    }

public:
    int uniquePaths(int m, int n) {
        int totalWays = 0;
        solve(0, 0, m, n, totalWays);
        return totalWays;
    }
};

// ============================================================================
// Solution 2: Backtracking from (m-1,n-1) → (0,0), totalWays++
// ============================================================================
// Start at (m-1,n-1). Move up or left. When we reach (0,0), increment count.
// Same logic as Solution 1 but reversed direction.
class Solution2 {
private:
    void solve(int i, int j, int& totalWays) {
        // Reached origin
        if (i == 0 && j == 0) {
            totalWays++;
            return;
        }

        // Out of bounds
        if (i < 0 || j < 0) 
            return;

        // Move up
        solve(i - 1, j, totalWays);
        // Move left
        solve(i, j - 1, totalWays);
    }

public:
    int uniquePaths(int m, int n) {
        int totalWays = 0;
        solve(m - 1, n - 1, totalWays);
        return totalWays;
    }
};

// ============================================================================
// Solution 3: Backtracking from (m-1,n-1) → (0,0), RETURN count
// ============================================================================
// Instead of a global variable, each call returns the number of ways to reach (0,0).
// This is the KEY step before memoization — the return value can be cached.
class Solution3 {
private:
    int solve(int i, int j) {
        // Reached origin — 1 valid path found
        if (i == 0 && j == 0) 
            return 1;

        // Out of bounds — no valid path
        if (i < 0 || j < 0) 
            return 0;

        // Number of ways = ways from above + ways from left
        int totalWaysFromIJToOrigin = 0;
        int totalWaysFromAbove = solve(i - 1, j);
        int totalWaysFromLeft  = solve(i, j - 1);

        return totalWaysFromIJToOrigin = totalWaysFromAbove + totalWaysFromLeft;
    }

public:
    int uniquePaths(int m, int n) {
        return solve(m - 1, n - 1);
    }
};

// ============================================================================
// Solution 4: Memoization (Top-Down DP)
// ============================================================================
// Same as Solution 3, but cache results to avoid recomputation.
// dp[i][j] = number of unique paths from (i,j) to (0,0).
class Solution4 {
private:
    int solve(int i, int j, vector<vector<int>>& dp) {
        // Reached origin — 1 valid path found
        if (i == 0 && j == 0) 
            return 1;
        if (i < 0 || j < 0) 
            return 0;

        // Out of bounds — no valid path
        if (dp[i][j] != -1) 
            return dp[i][j];

        dp[i][j] = solve(i - 1, j, dp) + solve(i, j - 1, dp);
        // Number of ways = ways from above + ways from left
        int totalWaysFromIJToOrigin = 0;
        int totalWaysFromAbove = solve(i - 1, j, dp);
        int totalWaysFromLeft = solve(i, j - 1, dp);

        totalWaysFromIJToOrigin = totalWaysFromAbove + totalWaysFromLeft;
        return dp[i][j] = totalWaysFromIJToOrigin;
    }

public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return solve(m - 1, n - 1, dp);
    }
};

// ============================================================================
// Solution 5: Bottom-Up (Tabulation)
// ============================================================================
// Fill dp table iteratively. dp[i][j] = dp[i-1][j] + dp[i][j-1].
// Base case: first row and first column = 1 (only one way to reach them).
class Solution5 {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));

        dp[0][0] = 1;  // base case: same as "if i==0 && j==0 return 1"

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                //1 way to reach the starting cell
                if (i == 0 && j == 0) {
                    dp[i][j] = 1;
                }
                //1 way to reach this cell in first row. Take right
                else if (i == 0) {
                    dp[i][j] = 1;
                }
                //1 way to reach this cell in first column. Take down
                else if (j == 0) {
                    dp[i][j] = 1;
                }
                else {
                    // dp[i][j] = number of ways to reach (i,j) from (0,0)
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
                }
            }
        }

        // dp[m - 1][n - 1] = number of ways to reach (m-1, n-1) from (0, 0)
        return dp[m - 1][n - 1];
    }
};



int main() {
    Solution1 backtrack1;
    Solution2 backtrack2;
    Solution3 backtrack3;
    Solution4 memo;
    Solution5 bottomUp;

    int m = 3, n = 7;

    cout << "Backtrack (0,0)→(m-1,n-1): " << backtrack1.uniquePaths(m, n) << endl; // 28
    cout << "Backtrack (m-1,n-1)→(0,0): " << backtrack2.uniquePaths(m, n) << endl; // 28
    cout << "Backtrack return count:     " << backtrack3.uniquePaths(m, n) << endl; // 28
    cout << "Memoization:                " << memo.uniquePaths(m, n) << endl;       // 28
    cout << "Bottom-Up:                  " << bottomUp.uniquePaths(m, n) << endl;   // 28

    return 0;
}
