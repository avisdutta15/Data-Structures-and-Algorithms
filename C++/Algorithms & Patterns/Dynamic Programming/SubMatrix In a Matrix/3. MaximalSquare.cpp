#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>
#include <stack>

using namespace std;

/*
    Problem Statement: (LeetCode 221 - Maximal Square)
    ------------------
    Given an m x n binary matrix filled with 0's and 1's, find the largest
    square containing only 1's and return its area.

    Examples:
    --------
    Input: matrix = [["1","0","1","0","0"],
                     ["1","0","1","1","1"],
                     ["1","1","1","1","1"],
                     ["1","0","0","1","0"]]
    Output: 4
    Explanation: Largest square has side 2 (at rows 1-2, cols 2-3).

    Input: matrix = [["0","1"],["1","0"]]
    Output: 1

    Constraints:
    ------------
    - m == matrix.length, n == matrix[i].length
    - 1 <= m, n <= 300
    - matrix[i][j] is '0' or '1'

    Approach:
    ---------
    dp[i][j] = side length of the largest square whose BOTTOM-RIGHT corner is (i,j).

    A square of side k at (i,j) exists only if:
    - dp[i-1][j] >= k-1   (k-1 rows of 1s above)
    - dp[i][j-1] >= k-1   (k-1 cols of 1s to the left)
    - dp[i-1][j-1] >= k-1 (the inner diagonal square)

    The smallest of these three is the bottleneck.

    Recurrence:
        solve(i, j):
            if i < 0 or j < 0: return 0             // out of bounds
            if matrix[i][j] == '0': return 0        // not a 1

            return 1 + min(solve(i-1,j), solve(i,j-1), solve(i-1,j-1))

    Answer: max(solve(i,j))² for all (i,j)

    Time: O(m*n) for memo/bottom-up.
    Space: O(m*n) for memo/bottom-up, O(n) for space-optimized.

    Approach 4 (Histogram + PSE/NSE):
    ----------------------------------
    Same framework as Maximal Rectangle (LC 85):
    1. Build histogram heights[] row by row (if cell='1', heights[j]++, else reset to 0).
    2. For each row, use PSE+NSE to find left/right boundaries of each bar.
    3. Width = right[i] - left[i] - 1.
    4. For RECTANGLE: area = height * width.
       For SQUARE: side = min(height, width), area = side².

    This gives a unified approach for both LC 85 (Maximal Rectangle) and LC 221 (Maximal Square).
    Only difference is the final formula.
*/

// ============================================================================
// Solution 1: Recursion (Brute Force)
// Time: O(3^(m+n)) per cell, overall exponential.
// Space: O(m+n) recursion stack.
// ============================================================================
class Solution1 {
private:
    int solve(vector<vector<char>>& matrix, int i, int j) {
        // Out of bounds or cell is '0'
        if (i < 0 || j < 0) return 0;
        if (matrix[i][j] == '0') return 0;

        int up       = solve(matrix, i - 1, j);
        int left     = solve(matrix, i, j - 1);
        int diagonal = solve(matrix, i - 1, j - 1);

        return 1 + min({up, left, diagonal});
    }

public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        int maxSide = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                maxSide = max(maxSide, solve(matrix, i, j));
            }
        }

        return maxSide * maxSide;
    }
};

// ============================================================================
// Solution 2: Memoization (Top-Down DP)
// Time: O(m*n) — each cell computed once.
// Space: O(m*n) — dp table + recursion stack.
// ============================================================================
class Solution2 {
private:
    int solve(vector<vector<char>>& matrix, int i, int j, vector<vector<int>>& dp) {
        if (i < 0 || j < 0) return 0;
        if (matrix[i][j] == '0') return 0;
        if (dp[i][j] != -1) return dp[i][j];

        int up       = solve(matrix, i - 1, j, dp);
        int left     = solve(matrix, i, j - 1, dp);
        int diagonal = solve(matrix, i - 1, j - 1, dp);

        dp[i][j] = 1 + min({up, left, diagonal});
        return dp[i][j];
    }

public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, -1));
        int maxSide = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                maxSide = max(maxSide, solve(matrix, i, j, dp));
            }
        }

        return maxSide * maxSide;
    }
};

// ============================================================================
// Solution 3: Bottom-Up (Tabulation)
// Time: O(m*n), Space: O(m*n)
// ============================================================================
// Direct translation:
//   solve(i, j):
//     if i < 0 or j < 0: return 0
//     if matrix[i][j] == '0': return 0
//     return 1 + min(solve(i-1,j), solve(i,j-1), solve(i-1,j-1))
class Solution3 {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int maxSide = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // Base case: matrix[i][j] == '0' → dp[i][j] = 0
                if (matrix[i][j] == '0') {
                    dp[i][j] = 0;
                }
                // First row or first column: can only form 1x1 at most
                // (out of bounds returns 0, so min(0,...)+1 = 1)
                else if (i == 0 || j == 0) {
                    dp[i][j] = 1;
                }
                // General case: 1 + min(above, left, diagonal)
                else {
                    dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
                }

                maxSide = max(maxSide, dp[i][j]);
            }
        }

        return maxSide * maxSide;
    }
};

// ============================================================================
// Solution 4: Histogram + PSE/NSE
// Time: O(m*n), Space: O(n)
// ============================================================================
// Build histogram row by row. For each row, use PSE+NSE to find the width each
// bar can span. For a square: side = min(height, width). Same as Maximal Rectangle
// but replace area = height*width with side = min(height, width).
class Solution4 {
private:
    int largestSquareInHistogram(vector<int>& heights) {
        int n = heights.size();
        vector<int> left(n), right(n);
        stack<int> st;

        // PSE: Previous Smaller Element
        for (int i = 0; i < n; i++) {
            while (!st.empty() && heights[st.top()] >= heights[i])
                st.pop();
            left[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }

        while (!st.empty()) st.pop();

        // NSE: Next Smaller Element
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && heights[st.top()] >= heights[i])
                st.pop();
            right[i] = st.empty() ? n : st.top();
            st.push(i);
        }

        // For square: side = min(height, width)
        // Each bar i can span a rectangle of height=heights[i] and width=right[i]-left[i]-1.
        // The largest SQUARE that fits inside this rectangle has:
        //   side = min(height, width)
        // Because a square needs equal height and width, so the smaller dimension limits it.
        //
        // Example: heights = [1, 3, 3, 3, 1]
        //   Bar at index 2: height=3, PSE=0 (height 1), NSE=4 (height 1)
        //   width = 4 - 0 - 1 = 3
        //   For rectangle: area = 3 * 3 = 9
        //   For square: side = min(3, 3) = 3, area = 9
        //
        //   Bar at index 1: height=3, PSE=0, NSE=4
        //   width = 4 - 0 - 1 = 3
        //   side = min(3, 3) = 3
        //
        //   If heights = [1, 5, 5, 5, 1]:
        //   Bar at index 2: height=5, width=3
        //   For rectangle: area = 5 * 3 = 15
        //   For square: side = min(5, 3) = 3, area = 9
        //   (can't make a 5x5 square with only width 3)
        int maxArea = 0;
        for (int i = 0; i < n; i++) {
            int width = right[i] - left[i] - 1;
            int side = min(heights[i], width);
            maxArea = max(maxArea, side * side);
        }

        return maxArea;
    }

public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> heights(n, 0);
        int maxArea = 0;

        for (int i = 0; i < m; i++) {
            // Build histogram
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '1')
                    heights[j]++;
                else
                    heights[j] = 0;
            }

            maxArea = max(maxArea, largestSquareInHistogram(heights));
        }

        return maxArea;
    }

};


int main() {
    Solution1 recursion;
    Solution2 memo;
    Solution3 bottomUp;
    Solution4 histogram;

    vector<vector<char>> matrix = {
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    };

    cout << "Recursion:   " << recursion.maximalSquare(matrix) << endl;  // 4
    cout << "Memoization: " << memo.maximalSquare(matrix) << endl;       // 4
    cout << "Bottom-Up:   " << bottomUp.maximalSquare(matrix) << endl;   // 4
    cout << "Histogram:   " << histogram.maximalSquare(matrix) << endl;  // 4

    return 0;
}
