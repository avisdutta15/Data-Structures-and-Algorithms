#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement: (LeetCode 931 - Minimum Falling Path Sum)
    ------------------
    Given an n x n array of integers, return the minimum sum of any falling path through matrix.
    A falling path starts at any element in the first row and chooses the element in the next
    row that is either directly below, below-left, or below-right.

    Examples:
    --------
    Input: matrix = [[2,1,3],
                     [6,5,4],
                     [7,8,9]]
    Output: 13
    Explanation: Paths: 1 → 5 → 7 = 13, or 1 → 4 → 8 = 13

    Input: matrix = [[-19,57],
                     [-40,-5]]
    Output: -59
    Explanation: -19 + (-40) = -59

    Constraints:
    ------------
    - n == matrix.length == matrix[i].length
    - 1 <= n <= 100
    - -100 <= matrix[i][j] <= 100

    Key Difference from Minimum Path Sum:
    - Start at ANY cell in first row (not just (0,0))
    - End at ANY cell in last row (not just (m-1,n-1))
    - Can move to 3 directions: down-left, down, down-right (not just right/down)

    Evolution of approaches:
    ------------------------
    1. Backtracking: start from each cell in last row, go UP to any cell in first row
    2. Return min cost: each call returns min cost to reach first row
    3. Memoization: cache the return values
    4. Bottom-Up: iterative tabulation

    Time: O(N²) for approaches 3,4. O(3^N) for approaches 1,2.
    Space: O(N²) for approach 3,4. O(N) recursion stack for 1,2.
*/

// ============================================================================
// Solution 1: Backtracking from last row → first row, update global min
// ============================================================================
class Solution1 {
private:
    void solve(vector<vector<int>>& matrix, int i, int j, int n,
               int currentCost, int& minCost) {
        // Out of bounds
        if (j < 0 || j >= n) 
            return;

        // Reached first row — record total cost
        if (i == 0) {
            minCost = min(minCost, currentCost + matrix[i][j]);
            return;
        }

        // Pruning
        if (currentCost + matrix[i][j] >= minCost) return;

        // Move up-left, up, up-right
        solve(matrix, i - 1, j - 1, n, currentCost + matrix[i][j], minCost);
        solve(matrix, i - 1, j, n, currentCost + matrix[i][j], minCost);
        solve(matrix, i - 1, j + 1, n, currentCost + matrix[i][j], minCost);
    }

public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int minCost = INT_MAX;

        // Try starting from each cell in the last row
        for (int j = 0; j < n; j++) {
            solve(matrix, n - 1, j, n, 0, minCost);
        }

        return minCost;
    }
};

// ============================================================================
// Solution 2: Backtracking from last row → first row, RETURN min cost
// ============================================================================
// Each call returns the minimum falling path sum from (i,j) up to any cell in row 0.
class Solution2 {
private:
    int solve(vector<vector<int>>& matrix, int i, int j, int n) {
        // Out of bounds
        if (j < 0 || j >= n) 
            return INT_MAX;

        // Reached first row — cost is just this cell
        if (i == 0) 
            return matrix[i][j];

        // Min of three directions going up + current cell
        int upLeft  = solve(matrix, i - 1, j - 1, n);
        int up      = solve(matrix, i - 1, j, n);
        int upRight = solve(matrix, i - 1, j + 1, n);

        return matrix[i][j] + min({upLeft, up, upRight});
    }

public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int minCost = INT_MAX;

        // Try starting from each cell in the last row
        for (int j = 0; j < n; j++) {
            minCost = min(minCost, solve(matrix, n - 1, j, n));
        }

        return minCost;
    }
};

// ============================================================================
// Solution 3: Memoization (Top-Down DP)
// ============================================================================
class Solution3 {
private:
    int solve(vector<vector<int>>& matrix, int i, int j, int n,
              vector<vector<int>>& dp) {
        if (j < 0 || j >= n) return INT_MAX;
        if (i == 0) return matrix[i][j];
        if (dp[i][j] != INT_MIN) return dp[i][j];

        int upLeft  = solve(matrix, i - 1, j - 1, n, dp);
        int up      = solve(matrix, i - 1, j, n, dp);
        int upRight = solve(matrix, i - 1, j + 1, n, dp);

        dp[i][j] = matrix[i][j] + min({upLeft, up, upRight});
        return dp[i][j];
    }

public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<vector<int>> dp(n, vector<int>(n, INT_MIN));
        int minCost = INT_MAX;

        for (int j = 0; j < n; j++) {
            minCost = min(minCost, solve(matrix, n - 1, j, n, dp));
        }

        return minCost;
    }
};

// ============================================================================
// Solution 4: Bottom-Up (Tabulation)
// ============================================================================
// Direct translation of the recursive structure:
//   solve(i, j):
//     if j < 0 or j >= n: return INT_MAX
//     if i == 0: return matrix[i][j]
//     return matrix[i][j] + min(solve(i-1,j-1), solve(i-1,j), solve(i-1,j+1))
//
// Bottom-up: fill dp[i][j] from i=0 to i=n-1 (since each row depends on previous row)
class Solution4 {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Base case: if i == 0, return matrix[0][j]
                if (i == 0) {
                    dp[i][j] = matrix[i][j];
                }
                else {
                    // Recursive case: matrix[i][j] + min(solve(i-1,j-1), solve(i-1,j), solve(i-1,j+1))
                    // Out of bounds (j<0 or j>=n) returns INT_MAX
                    int upLeft  = (j - 1 >= 0) ? dp[i - 1][j - 1] : INT_MAX;
                    int up      = dp[i - 1][j];
                    int upRight = (j + 1 < n)  ? dp[i - 1][j + 1] : INT_MAX;

                    dp[i][j] = matrix[i][j] + min({upLeft, up, upRight});
                }
            }
        }

        // Answer: min(solve(n-1, j)) for all j
        int minCost = INT_MAX;
        for (int j = 0; j < n; j++) {
            minCost = min(minCost, dp[n - 1][j]);
        }

        return minCost;
    }
};


int main() {
    Solution1 backtrack1;
    Solution2 backtrack2;
    Solution3 memo;
    Solution4 bottomUp;

    vector<vector<int>> matrix = {
        {2, 1, 3},
        {6, 5, 4},
        {7, 8, 9}
    };

    cout << "Backtrack (update min):   " << backtrack1.minFallingPathSum(matrix) << endl; // 13
    cout << "Backtrack (return min):   " << backtrack2.minFallingPathSum(matrix) << endl; // 13
    cout << "Memoization:              " << memo.minFallingPathSum(matrix) << endl;       // 13
    cout << "Bottom-Up:                " << bottomUp.minFallingPathSum(matrix) << endl;   // 13

    return 0;
}
