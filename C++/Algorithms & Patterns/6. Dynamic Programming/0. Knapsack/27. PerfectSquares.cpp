#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Perfect Squares (LeetCode 279)
    ─────────────────────────────────────────

    Problem Statement:
    ------------------
    Given an integer n, return the least number of perfect square numbers that
    sum to n.

    A perfect square is an integer that is the square of an integer (1, 4, 9, 16, ...).

    Examples:
    ---------
    Input:  n = 12
    Output: 3
    Explanation: 12 = 4 + 4 + 4.

    Input:  n = 13
    Output: 2
    Explanation: 13 = 4 + 9.

    Constraints:
    ------------
    - 1 <= n <= 10^4

    ════════════════════════════════════════════════════════════════════════
    KEY INSIGHT: This IS Coin Change (min coins) with coins = perfect squares
    ════════════════════════════════════════════════════════════════════════

    Mapping to Coin Change (LC 322):
        - coins[] = [1, 4, 9, 16, 25, ...] (all perfect squares <= n)
        - amount = n
        - Minimize the number of "coins" (squares) used
        - Each "coin" can be reused → unbounded knapsack

    So it's the exact same problem as Coin Change with:
        coins = [1, 4, 9, 16, ..., floor(√n)²]

    ════════════════════════════════════════════════════════════════════════
    RECURRENCE (same as Coin Change — minimize)
    ════════════════════════════════════════════════════════════════════════

    Let squares[] = [1, 4, 9, 16, ...] (all perfect squares <= n)
    K = the number of perfect squares that are ≤ n, and the largest 
    perfect square ≤ n is floor(√n)².
    The squares are: 1², 2², 3², ..., floor(√n)²

    That's floor(√n) items total.
    Let K = number of perfect squares <= n (= floor(√n))

    f(k, amount) = min squares needed using first k square numbers to make amount

    Base cases:
        f(k, 0) = 0            (amount 0 needs 0 squares)
        f(0, amount) = INT_MAX (no squares available, impossible)

    Recurrence:
        include = INT_MAX
        exclude = INT_MAX

        if squares[k-1] <= amount AND f(k, amount - squares[k-1]) != INT_MAX:
            include = 1 + f(k, amount - squares[k-1])   // use square (STAY — can reuse)

        exclude = f(k-1, amount)                         // skip this square

        f(k, amount) = min(include, exclude)

    Answer: f(K, n)

    ════════════════════════════════════════════════════════════════════════
    1D OPTIMIZATION (Left to Right — Unbounded)
    ════════════════════════════════════════════════════════════════════════

    for each square s in [1, 4, 9, 16, ...]:
        for amt = s to n:        ← LEFT to RIGHT (can reuse same square)
            if dp[amt - s] != INT_MAX:
                dp[amt] = min(dp[amt], 1 + dp[amt - s])

    ════════════════════════════════════════════════════════════════════════
*/

class Solution{
    // ── Recursive ──
    // Time: O(K^n) worst case where K = √n
    // Space: O(n) recursion stack
    int perfectSquaresRecursive(vector<int> &squares, int K, int amount){
        if(amount == 0)
            return 0;
        if(K == 0)
            return INT_MAX;

        int include = INT_MAX, exclude = INT_MAX;

        // Use squares[K-1] (stay at K — can reuse)
        if(squares[K-1] <= amount){
            int subResult = perfectSquaresRecursive(squares, K, amount - squares[K-1]);
            if(subResult != INT_MAX)
                include = 1 + subResult;
        }

        // Skip this square (move to K-1)
        exclude = perfectSquaresRecursive(squares, K-1, amount);

        return min(include, exclude);
    }

    // ── Top-Down with 2D Memoization ──
    // Time: O(K * n) where K = √n
    // Space: O(K * n) for memo + O(n) recursion stack
    int perfectSquaresTopDown(vector<int> &squares, int K, int amount, vector<vector<int>> &memo){
        if(amount == 0)
            return 0;
        if(K == 0)
            return INT_MAX;

        if(memo[K][amount] != -1)
            return memo[K][amount];

        int include = INT_MAX, exclude = INT_MAX;

        if(squares[K-1] <= amount){
            int subResult = perfectSquaresTopDown(squares, K, amount - squares[K-1], memo);
            if(subResult != INT_MAX)
                include = 1 + subResult;
        }

        exclude = perfectSquaresTopDown(squares, K-1, amount, memo);

        memo[K][amount] = min(include, exclude);
        return memo[K][amount];
    }

    // ── Bottom-Up 2D ──
    // Time: O(K * n) where K = √n
    // Space: O(K * n)
    int perfectSquaresBottomUp(vector<int> &squares, int K, int n){
        vector<vector<int>> dp(K+1, vector<int>(n+1, 0));

        for(int k = 0; k <= K; k++){
            for(int amt = 0; amt <= n; amt++){
                if(amt == 0){
                    dp[k][amt] = 0;
                }
                else if(k == 0){
                    dp[k][amt] = INT_MAX;
                }
                else{
                    int include = INT_MAX, exclude = INT_MAX;

                    if(squares[k-1] <= amt && dp[k][amt - squares[k-1]] != INT_MAX)
                        include = 1 + dp[k][amt - squares[k-1]];

                    exclude = dp[k-1][amt];

                    dp[k][amt] = min(include, exclude);
                }
            }
        }
        return dp[K][n];
    }

    // ── Bottom-Up 1D ──
    // Time: O(√n * n)
    // Space: O(n)
    // Left to right (unbounded — same square reusable)
    int perfectSquaresBottomUp1D(vector<int> &squares, int K, int n){
        vector<int> dp(n+1, INT_MAX);
        dp[0] = 0;

        for(int k = 0; k < K; k++){
            // LEFT to RIGHT: allows reusing squares[k]
            for(int amt = squares[k]; amt <= n; amt++){
                if(dp[amt - squares[k]] != INT_MAX)
                    dp[amt] = min(dp[amt], 1 + dp[amt - squares[k]]);
            }
        }
        return dp[n];
    }

public:
    int numSquares(int n){
        // Build the "coins" array: all perfect squares <= n
        vector<int> squares;
        for(int i = 1; i * i <= n; i++)
            squares.push_back(i * i);

        int K = squares.size();  // number of available squares

        // return perfectSquaresRecursive(squares, K, n);

        // vector<vector<int>> memo(K+1, vector<int>(n+1, -1));
        // return perfectSquaresTopDown(squares, K, n, memo);

        // return perfectSquaresBottomUp(squares, K, n);

        return perfectSquaresBottomUp1D(squares, K, n);
    }
};


int main(){
    Solution obj;

    cout << "Perfect squares (12): " << obj.numSquares(12) << endl;  // 3 (4+4+4)
    cout << "Perfect squares (13): " << obj.numSquares(13) << endl;  // 2 (4+9)
    cout << "Perfect squares (1): " << obj.numSquares(1) << endl;    // 1
    cout << "Perfect squares (7): " << obj.numSquares(7) << endl;    // 4 (4+1+1+1)

    return 0;
}
