#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement: Maximum Path Sum in a Triangle + Print Path
    ------------------
    Given a triangular matrix, find the maximum path sum from the first row
    to the last row. At every cell (i, j) you can move to (i+1, j) or (i+1, j+1).
    Also print the path that gives the maximum sum.

    Examples:
    --------
    Input: triangle = [[2],
                       [3, 7],
                       [8, 5, 6],
                       [6, 1, 9, 3]]
    Output: 24
    Path: 2 → 7 → 6 → 9

    Constraints:
    ------------
    - 1 <= triangle.length <= 200
    - -10^4 <= triangle[i][j] <= 10^4

    Approach:
    ---------
    Exactly same as Minimum Path Sum in Triangle (LC 120) but use max instead of min.
    To print the path, backtrack from dp[0][0] choosing the direction that was picked.

    Recurrence:
        solve(i, j):
            if i == n-1: return triangle[n-1][j]
            return triangle[i][j] + max(solve(i+1, j), solve(i+1, j+1))

        Answer: solve(0, 0)
*/

// ============================================================================
// Solution 1: Recursion (Brute Force)
// Time: O(2^N), Space: O(N)
// ============================================================================
class Solution1 {
private:
    int solve(vector<vector<int>>& triangle, int i, int j, int n) {
        if (i == n - 1) return triangle[i][j];

        int down      = solve(triangle, i + 1, j, n);
        int downRight = solve(triangle, i + 1, j + 1, n);

        return triangle[i][j] + max(down, downRight);
    }

public:
    int maximumTotal(vector<vector<int>>& triangle) {
        return solve(triangle, 0, 0, triangle.size());
    }
};

// ============================================================================
// Solution 2: Memoization (Top-Down DP)
// Time: O(N²), Space: O(N²)
// ============================================================================
class Solution2 {
private:
    int solve(vector<vector<int>>& triangle, int i, int j, int n,
              vector<vector<int>>& dp) {
        if (i == n - 1) return triangle[i][j];
        if (dp[i][j] != INT_MIN) return dp[i][j];

        int down      = solve(triangle, i + 1, j, n, dp);
        int downRight = solve(triangle, i + 1, j + 1, n, dp);

        dp[i][j] = triangle[i][j] + max(down, downRight);
        return dp[i][j];
    }

public:
    int maximumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<vector<int>> dp(n, vector<int>(n, INT_MIN));
        return solve(triangle, 0, 0, n, dp);
    }
};

// ============================================================================
// Solution 3: Bottom-Up (Tabulation) + Print Path
// Time: O(N²), Space: O(N²)
// ============================================================================
// Direct translation:
//   solve(i, j):
//     if i == n-1: return triangle[n-1][j]
//     return triangle[i][j] + max(solve(i+1, j), solve(i+1, j+1))
//
// Fill from last row to first row.
// To print path: from dp[0][0], greedily follow the direction that gives max.
class Solution3 {
public:
    int maximumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j <= i; j++) {
                // Base case: last row
                if (i == n - 1) {
                    dp[i][j] = triangle[i][j];
                }
                // Recursive case: triangle[i][j] + max(dp[i+1][j], dp[i+1][j+1])
                else {
                    dp[i][j] = triangle[i][j] + max(dp[i + 1][j], dp[i + 1][j + 1]);
                }
            }
        }

        // Print path: backtrack from dp[0][0]
        printPath(triangle, dp, n);

        return dp[0][0];
    }

private:
    void printPath(vector<vector<int>>& triangle, vector<vector<int>>& dp, int n) {
        cout << "Path: ";
        int j = 0;
        for (int i = 0; i < n; i++) {
            cout << triangle[i][j];

            // if not the last row
            if (i < n - 1) {
                cout << " -> ";
                // Choose direction: go where dp is larger
                if (dp[i + 1][j + 1] > dp[i + 1][j]) {
                    j = j + 1; // go down-right
                }
                // else j stays same (go down)
            }
        }
        cout << endl;
    }
};


int main() {
    Solution1 recursion;
    Solution2 memo;
    Solution3 bottomUp;

    vector<vector<int>> triangle = {
        {2},
        {3, 7},
        {8, 5, 6},
        {6, 1, 9, 3}
    };

    cout << "Recursion:   " << recursion.maximumTotal(triangle) << endl;  // 24
    cout << "Memoization: " << memo.maximumTotal(triangle) << endl;       // 24
    cout << "Bottom-Up:   " << bottomUp.maximumTotal(triangle) << endl;   // 24 + prints path

    return 0;
}
