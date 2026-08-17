#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement: (LeetCode 120 - Triangle)
    ------------------
    We are given a Triangular matrix. We need to find the minimum path sum 
    from the first row to the last row.

    At every cell we can move in only two directions: either to the 
    bottom cell (↓) or to the bottom-right cell(↘).

    Example
    --------
    Examples: 
    Input: triangle[][] =  [[2],
                            [3, 7],
                            [8, 5, 6],
                            [6, 1, 9, 3]]
    Output: 11 
    Explanation : The path is 2 → 3 → 5 → 1, which results in a minimum sum of 2 + 3 + 5 + 1 = 11.

    Input: triangle[][] =  [[3],
                            [6, 9],
                            [8, 7, 1],
                            [9, 6, 8, 2]]
    Output: 15
    Explanation: The path is 3 → 9 → 1 → 2, which results in a minimum sum of 3 + 9 + 1 + 2 = 15.


    Constraints:
    ------------
    - 1 <= triangle.length <= 200
    - triangle[0].length == 1
    - triangle[i].length == triangle[i-1].length + 1
    - -10^4 <= triangle[i][j] <= 10^4

    Approach:
    ---------
    Key Observations:
    - Start at (0,0), end at any cell in last row.
    - From (i, j) can move to (i+1, j) or (i+1, j+1).
    - Alternatively (going backwards): to reach (i, j), came from (i-1, j-1) or (i-1, j).

    Recurrence (going from last row backwards to top):
        solve(i, j):
            if i == n-1: return triangle[n-1][j]    // last row = base case
            if j < 0 or j > i: return INT_MAX       // out of bounds

            down     = solve(i+1, j)
            downRight = solve(i+1, j+1)
            return triangle[i][j] + min(down, downRight)

        Answer: solve(0, 0)

    Time: O(N²) for memo/bottom-up where N = number of rows.
    Space: O(N²) for memo, O(N) for space-optimized bottom-up.
*/

// ============================================================================
// Solution 1: Recursion (Brute Force)
// Time: O(2^N) — each cell branches into 2 calls, N rows deep.
// Space: O(N) — recursion stack depth.
// ============================================================================
// Start at (0,0), move down or down-right. Return min cost to reach last row.
class Solution1 {
private:
    int solve(vector<vector<int>>& triangle, int i, int j, int n) {
        // Reached last row — base case
        if (i == n - 1) return triangle[i][j];

        // Move down or down-right, pick minimum
        int down      = solve(triangle, i + 1, j, n);
        int downRight = solve(triangle, i + 1, j + 1, n);

        return triangle[i][j] + min(down, downRight);
    }

public:
    int minimumTotal(vector<vector<int>>& triangle) {
        return solve(triangle, 0, 0, triangle.size());
    }
};

// ============================================================================
// Solution 2: Memoization (Top-Down DP)
// Time: O(N²) — each cell computed once, total cells = 1+2+...+N = N²/2.
// Space: O(N²) — dp table + O(N) recursion stack.
// ============================================================================
class Solution2 {
private:
    int solve(vector<vector<int>>& triangle, int i, int j, int n,
              vector<vector<int>>& dp) {
        if (i == n - 1) return triangle[i][j];
        if (dp[i][j] != INT_MIN) return dp[i][j];

        int down      = solve(triangle, i + 1, j, n, dp);
        int downRight = solve(triangle, i + 1, j + 1, n, dp);

        dp[i][j] = triangle[i][j] + min(down, downRight);
        return dp[i][j];
    }

public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<vector<int>> dp(n, vector<int>(n, INT_MIN));
        return solve(triangle, 0, 0, n, dp);
    }
};

// ============================================================================
// Solution 3: Bottom-Up (Tabulation)
// Time: O(N²) — fill all cells iteratively.
// Space: O(N²) — dp table.
// ============================================================================
// Direct translation of recursive structure:
//   solve(i, j):
//     if i == n-1: return triangle[n-1][j]
//     return triangle[i][j] + min(solve(i+1, j), solve(i+1, j+1))
//
// Fill from last row to first row (since each row depends on the row below).
class Solution3 {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int rows = triangle.size();
        vector<vector<int>> dp(rows, vector<int>(rows, 0));

        for (int i = rows - 1; i >= 0; i--) {
            for (int j = 0; j <= i; j++) {
                // Base case: if last row i.e. i == rows-1, return triangle[i][j]
                if (i == rows - 1) {
                    dp[i][j] = triangle[i][j];
                }
                // Recursive case: triangle[i][j] + min(solve(i+1,j), solve(i+1,j+1))
                else {
                    dp[i][j] = triangle[i][j] + min(dp[i + 1][j], dp[i + 1][j + 1]);
                }
            }
        }

        // Answer: solve(0, 0)
        return dp[0][0];
    }
};

// ============================================================================
// Solution 4: Space Optimized Bottom-Up O(N) space
// Time: O(N²) — same traversal as bottom-up.
// Space: O(N) — single 1D array of last row size.
// ============================================================================
// Since dp[i] only depends on dp[i+1], use a single 1D array.
// Start with last row, overwrite in place going up.
class Solution4 {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        // Start with last row values
        vector<int> dp(triangle[n - 1].begin(), triangle[n - 1].end());

        // Fill from second-last row to top
        for (int i = n - 2; i >= 0; i--) {
            for (int j = 0; j <= i; j++) {
                dp[j] = triangle[i][j] + min(dp[j], dp[j + 1]);
            }
        }

        return dp[0];
    }
};


int main() {
    Solution1 recursion;
    Solution2 memo;
    Solution3 bottomUp;
    Solution4 optimized;

    vector<vector<int>> triangle = {
        {2},
        {3, 4},
        {6, 5, 7},
        {4, 1, 8, 3}
    };

    cout << "Recursion:       " << recursion.minimumTotal(triangle) << endl;  // 11
    cout << "Memoization:     " << memo.minimumTotal(triangle) << endl;       // 11
    cout << "Bottom-Up:       " << bottomUp.minimumTotal(triangle) << endl;   // 11
    cout << "Space Optimized: " << optimized.minimumTotal(triangle) << endl;  // 11

    return 0;
}
