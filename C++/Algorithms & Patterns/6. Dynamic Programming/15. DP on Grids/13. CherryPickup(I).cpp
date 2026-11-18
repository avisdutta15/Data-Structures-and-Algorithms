#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

/*
    https://www.youtube.com/watch?v=juJ0j-Otgko
    https://www.youtube.com/watch?v=ZV0sUzfA7Eg
    
    Problem Statement: (LeetCode 741 - Cherry Pickup)
    ------------------
    Given an n x n grid where:
      0 = empty cell
      1 = cherry
     -1 = thorn (can't pass)

    Go from (0,0) to (n-1,n-1) collecting cherries (right/down only),
    then return from (n-1,n-1) to (0,0) collecting cherries (left/up only).
    A cherry is collected only once (even if both trips pass through same cell).

    Find the maximum cherries collected in both trips combined.

    Examples:
    --------
    Input: grid = [[0,1,-1],[1,0,-1],[1,1,1]]
    Output: 5

    Input: grid = [[1,1,-1],[1,-1,1],[-1,1,1]]
    Output: 0 (no valid path exists)

    Constraints:
    ------------
    - n == grid.length == grid[i].length
    - 1 <= n <= 50
    - grid[i][j] is -1, 0, or 1

    Why greedy (two separate trips) fails:
    ----------------------------------------
    If we greedily pick max cherries on trip 1, we might block a better
    combined solution. The two trips are interdependent.

    Backtracking
    ------------
    So we should try to do backtracking.
    On trip1 (0,0) to (n-1,n-1) once we reach the end, we start trip2
    to reach the (0,0).

    This is CORRECT because it explores ALL trip1 paths × ALL trip2 paths.
    It's just too slow — O(2^(2n)) for trip1 × O(2^(2n)) for trip2 per path.

    Key Insight:
    ------------
    Instead of "trip 1 forward + trip 2 backward", model it as TWO PERSONS
    moving SIMULTANEOUSLY from (0,0) to (n-1,n-1) (both go right/down).
    This is equivalent because going backward (left/up) from (n-1,n-1) to (0,0)
    is the same as going forward from (0,0) to (n-1,n-1).

    Recurrence without K (4 variables — O(n⁴)):
    ---------------------------------------------
    solve(r1, c1, r2, c2):
        if r1>=n or c1>=n or r2>=n or c2>=n: return -INF        // out of bounds
        if grid[r1][c1]==-1 or grid[r2][c2]==-1: return -INF    // thorns
        if r1==n-1 && c1==n-1 && r2==n-1 && c2==n-1: return grid[r1][c1]    // last cell

        cherries = grid[r1][c1]
        if r1!=r2 && c1!=c2
            cherries += grid[r2][c2]

        // Both move: 4 combinations (right/down for each)
        // Person 1: (r1, c1+1) or (r1+1, c1)
        // Person 2: (r2, c2+1) or (r2+1, c2)
        maxFuture = max(
            solve(r1+1, c1,   r2+1, c2),     // both down
            solve(r1+1, c1,   r2,   c2+1),   // p1 down, p2 right
            solve(r1,   c1+1, r2+1, c2),     // p1 right, p2 down
            solve(r1,   c1+1, r2,   c2+1))   // both right

        return cherries + maxFuture

    Answer: max(0, solve(0, 0, 0, 0))
    Time: O(n⁴) with memoization (n⁴ states)
    Space: O(n⁴)

    Dimension reduction:
    --------------------

    Both persons take the same number of steps. After k steps:
    - Each move (right or down) increases row+col by exactly 1.
    - So after k steps: r1+c1 = k AND r2+c2 = k (always on same diagonal).

    Starting point: Both at (0, 0).

        r1 + c1 = 0 + 0 = 0
        r2 + c2 = 0 + 0 = 0
    
    After 1 step: Each person moves right (col+1) OR down (row+1). Either way, row+col increases by exactly 1.

        Person 1 moves right: (0, 1) → r1+c1 = 1
        Person 1 moves down:  (1, 0) → r1+c1 = 1
        Person 2 moves right: (0, 1) → r2+c2 = 1
        Person 2 moves down:  (1, 0) → r2+c2 = 1

    After k steps:

        r1 + c1 = k    (always, regardless of which path person 1 took)
        r2 + c2 = k    (always, regardless of which path person 2 took)

    Key observation: r1 + c1 == r2 + c2 == k always holds. 
    Since they are taking same number of steps, they will reach the destinatin at same time.

    - Without insight: state = (r1, c1, r2, c2) → O(n⁴)
    - Since c1 = k-r1 and c2 = k-r2, columns are derived for free.
    - Reduced state: (k, r1, r2) → O(n³)

    Recurrence:
        solve(k, r1, r2):
            c1 = k - r1, c2 = k - r2        // derive c1 , c2
            if out of bounds or grid[r1][c1]==-1 or grid[r2][c2]==-1: return -INF       // out of bounds or thorn
            if r1==n-1 && c1==n-1 && r2==n-1 && c2==n-1: return grid[r1][c1]    // reached end

            // Cherries at current positions (count once if same cell)
            cherries = grid[r1][c1]
            if r1 != r2: 
                cherries += grid[r2][c2]

            // Both move: 4 combinations (right/down for each)
            // Person 1: (r1, c1+1) or (r1+1, c1)
            // Person 2: (r2, c2+1) or (r2+1, c2)
            // In terms of rows at step k+1:
            //   right means row stays same, down means row+1
            maxFuture = max({
                solve(k+1, r1,   r2),      // both right
                solve(k+1, r1,   r2+1),    // p1 right, p2 down
                solve(k+1, r1+1, r2),      // p1 down, p2 right
                solve(k+1, r1+1, r2+1)     // both down
            })

            return cherries + maxFuture

        Answer: max(0, solve(0, 0, 0))   // 0 if no valid path

    Time: O(n³) — k goes 0..2(n-1), r1 and r2 go 0..n-1. k is derived from r1+c1.
    Space: O(n³) for memoization.
*/

// ============================================================================
// Solution 0: Naive Backtracking — Two Separate Trips (CORRECT but slow)
// Time: O(2^(2n) * 2^(2n)), Space: O(n²)
// ============================================================================
// Trip 1: Backtrack from (0,0) to (n-1,n-1) using right/down.
// When trip 1 reaches (n-1,n-1), call trip 2 from (n-1,n-1) to (0,0) using left/up.
// Trip 2 operates on the modified grid (cherries already collected by trip 1 are gone).
// Track the global max of (trip1 cherries + trip2 cherries).
//
// This is CORRECT because it explores ALL trip1 paths × ALL trip2 paths.
// It's just too slow — O(2^(2n)) for trip1 × O(2^(2n)) for trip2 per path.
// The simultaneous two-person approach (Solution 1) reduces this to O(n³) with memoization.
class Solution0 {
private:
    // Trip 2: from (n-1,n-1) to (0,0) using left/up. Returns max cherries collected.
    int trip2(vector<vector<int>>& grid, int i, int j, int n) {
        if (i < 0 || j < 0 || grid[i][j] == -1) return INT_MIN;
        if (i == 0 && j == 0) return grid[i][j];

        int up   = trip2(grid, i - 1, j, n);
        int left = trip2(grid, i, j - 1, n);

        int best = max(up, left);
        return (best == INT_MIN) ? INT_MIN : grid[i][j] + best;
    }

    // Trip 1: from (0,0) to (n-1,n-1) using right/down. Collects cherries along the way.
    // When destination reached, trigger trip 2 on modified grid.
    void trip1(vector<vector<int>>& grid, int i, int j, int n, int collected, int& maxTotal) {
        if (i >= n || j >= n || grid[i][j] == -1) return;

        int cherry = grid[i][j];
        collected += cherry;

        // Reached destination — now start trip 2 on modified grid
        if (i == n - 1 && j == n - 1) {
            int trip2Cherries = trip2(grid, n - 1, n - 1, n);
            if (trip2Cherries != INT_MIN) {
                // trip2 sees grid[n-1][n-1] as 0 (already collected by trip 1)
                // so trip2Cherries starts from 0 at destination
                maxTotal = max(maxTotal, collected + trip2Cherries - cherry);
                // subtract cherry because trip2 will also count grid[n-1][n-1]
                // but trip1 already collected it
            }
            return;
        }

        // Temporarily remove cherry so trip 2 won't double count
        grid[i][j] = 0;

        trip1(grid, i + 1, j, n, collected, maxTotal); // down
        trip1(grid, i, j + 1, n, collected, maxTotal); // right

        // Restore cherry (backtrack)
        grid[i][j] = cherry;
    }

public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        int maxTotal = 0;
        trip1(grid, 0, 0, n, 0, maxTotal);
        return maxTotal;
    }
};

// ============================================================================
// Solution 1: Recursion (Two Persons Simultaneous — Correct)
// Time: O(4^(2n)), Space: O(n)
// ============================================================================
class Solution1 {
private:
    int solve(vector<vector<int>>& grid, int k, int r1, int r2, int n) {
        int c1 = k - r1, c2 = k - r2;

        // Out of bounds or thorn
        if (r1 >= n || r2 >= n || c1 >= n || c2 >= n)
            return INT_MIN;
        if (grid[r1][c1] == -1 || grid[r2][c2] == -1)
            return INT_MIN;

        // Both reached destination
        if (r1 == n - 1 && c1 == n - 1 && r2 == n - 1 && c2 == n - 1)
            return grid[r1][c1];

        // Cherries at current positions
        int cherries = grid[r1][c1];
        if (r1 != r2) cherries += grid[r2][c2];

        // 4 move combinations
        int best = max({
            solve(grid, k + 1, r1,     r2,     n),  // both right
            solve(grid, k + 1, r1,     r2 + 1, n),  // p1 right, p2 down
            solve(grid, k + 1, r1 + 1, r2,     n),  // p1 down, p2 right
            solve(grid, k + 1, r1 + 1, r2 + 1, n)   // both down
        });

        return cherries + best;
    }

public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        return max(0, solve(grid, 0, 0, 0, n));
    }
};

// ============================================================================
// Solution 2: Memoization
// Time: O(n³), Space: O(n³)
// ============================================================================
class Solution2 {
private:
    int solve(vector<vector<int>>& grid, int k, int r1, int r2, int n,
              vector<vector<vector<int>>>& dp) {
        int c1 = k - r1, c2 = k - r2;

        if (r1 >= n || r2 >= n || c1 >= n || c2 >= n)
            return INT_MIN;
        if (grid[r1][c1] == -1 || grid[r2][c2] == -1)
            return INT_MIN;
        if (r1 == n - 1 && c1 == n - 1 && r2 == n - 1 && c2 == n - 1)
            return grid[r1][c1];
        if (dp[k][r1][r2] != INT_MIN)
            return dp[k][r1][r2];

        int cherries = grid[r1][c1];
        if (r1 != r2) cherries += grid[r2][c2];

        int best = max({
            solve(grid, k + 1, r1,     r2,     n, dp),
            solve(grid, k + 1, r1,     r2 + 1, n, dp),
            solve(grid, k + 1, r1 + 1, r2,     n, dp),
            solve(grid, k + 1, r1 + 1, r2 + 1, n, dp)
        });

        dp[k][r1][r2] = cherries + best;
        return dp[k][r1][r2];
    }

public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        int maxK = 2 * (n - 1);
        // Using INT_MIN as "unvisited" marker — but need a different sentinel
        // since INT_MIN is also used for invalid paths. Use INT_MIN + 1.
        vector<vector<vector<int>>> dp(maxK + 1, vector<vector<int>>(n, vector<int>(n, INT_MIN)));
        int result = solve(grid, 0, 0, 0, n, dp);
        return max(0, result);
    }
};

// ============================================================================
// Solution 3: Bottom-Up
// Time: O(n³), Space: O(n³)
// ============================================================================
// Direct translation:
//   solve(k, r1, r2):
//     c1 = k-r1, c2 = k-r2
//     if out of bounds or thorn: return -INF
//     if k == 2*(n-1): return grid[r1][c1]
//     cherries = grid[r1][c1] + (r1 != r2 ? grid[r2][c2] : 0)
//     return cherries + max of 4 moves at (k+1, ...)
//
// Fill from k = 2*(n-1) back to k = 0.
class Solution3 {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();

        // 1 person can take (n-1) steps to reach (n-1, n-1)
        // so maxSteps = total steps taken by 2 persons
        int maxSteps = 2 * (n - 1);

        // dp[k][r1][r2] = max cherries from step k onwards
        vector<vector<vector<int>>> dp(maxSteps + 1,
            vector<vector<int>>(n, vector<int>(n, INT_MIN)));

        for (int k = maxSteps; k >= 0; k--) {
            for (int r1 = 0; r1 < n; r1++) {
                for (int r2 = 0; r2 < n; r2++) {

                    // derive c1 and c2
                    int c1 = k - r1, c2 = k - r2;

                    // Out of bounds or thorn
                    if (c1 < 0 || c1 >= n || c2 < 0 || c2 >= n) continue;
                    if (grid[r1][c1] == -1 || grid[r2][c2] == -1) continue;

                    // Base case: both at destination
                    if (r1 == n - 1 && c1 == n - 1 && r2 == n - 1 && c2 == n - 1) {
                        dp[k][r1][r2] = grid[r1][c1];
                        continue;
                    }

                    // Cherries at current positions
                    int cherries = grid[r1][c1];
                    if (r1 != r2) 
                        cherries += grid[r2][c2];

                    // Max of 4 move combinations from step k+1
                    int best = INT_MIN;
                    for (int dr1 = 0; dr1 <= 1; dr1++) {
                        for (int dr2 = 0; dr2 <= 1; dr2++) {

                            int nr1 = r1 + dr1, 
                            int nr2 = r2 + dr2;
                            
                            if (nr1 < n && nr2 < n && dp[k + 1][nr1][nr2] != INT_MIN) {
                                best = max(best, dp[k + 1][nr1][nr2]);
                            }
                        }
                    }

                    if (best != INT_MIN)
                        dp[k][r1][r2] = cherries + best;
                }
            }
        }

        // If dp[0][0][0] is still INT_MIN, there's no valid path
        return max(0, dp[0][0][0]);
    }
};


int main() {
    // Solution1 is too slow for large inputs
    Solution1 recursion;
    Solution2 memo;
    Solution3 bottomUp;

    vector<vector<int>> grid = {
        {0, 1, -1},
        {1, 0, -1},
        {1, 1,  1}
    };

    cout << "Recursion:   " << recursion.cherryPickup(grid) << endl;  // 5
    cout << "Memoization: " << memo.cherryPickup(grid) << endl;       // 5
    cout << "Bottom-Up:   " << bottomUp.cherryPickup(grid) << endl;   // 5

    return 0;
}
