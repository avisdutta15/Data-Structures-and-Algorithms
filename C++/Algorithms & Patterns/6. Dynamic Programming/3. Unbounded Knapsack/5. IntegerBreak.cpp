#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Integer Break (LeetCode 343)
    ───────────────────────────────────────

    Problem Statement:
    ------------------
    Given an integer n, break it into the sum of k positive integers, where
    k >= 2, and maximize the product of those integers.
    Return the maximum product you can get.

    Examples:
    ---------
    Input:  n = 2
    Output: 1
    Explanation: 2 = 1 + 1, product = 1*1 = 1.

    Input:  n = 10
    Output: 36
    Explanation: 10 = 3 + 3 + 4, product = 3*3*4 = 36.

    Constraints:
    ------------
    - 2 <= n <= 58

    ════════════════════════════════════════════════════════════════════════
    KEY INSIGHT: This is Rod Cutting / Unbounded Knapsack
    ════════════════════════════════════════════════════════════════════════

    Mapping to Rod Cutting:
        - Rod length = n
        - Piece lengths = [1, 2, 3, ..., n-1] (must break into at least 2 pieces)
        - "Price" of a piece of length i = i itself (since we multiply the pieces)
        - Maximize the PRODUCT (not sum) of pieces

    Difference from standard Rod Cutting:
        - Rod cutting: maximize SUM of prices → dp[l] = max(dp[l], price[i] + dp[l-piece])
        - Integer break: maximize PRODUCT of pieces → dp[l] = max(dp[l], i * dp[l-i])
        - Addition becomes multiplication in the recurrence

    ════════════════════════════════════════════════════════════════════════
    RECURRENCE
    ════════════════════════════════════════════════════════════════════════

    f(n) = maximum product achievable by breaking n into 2+ parts

    Base case:
        f(1) = 1    (can't break further, piece value = 1)

    Recurrence: for each possible first cut i (1 to n-1):
        f(n) = max over all i from 1 to n-1 of:
            max(i * (n-i),       // cut into exactly 2 pieces: i and (n-i), don't break further
                i * f(n-i))      // cut piece i, and break the remaining (n-i) further

    Why max(i * (n-i), i * f(n-i))?
        - i * (n-i): stop breaking here. Use (n-i) as a whole piece.
        - i * f(n-i): break (n-i) further for a potentially better product.
        - We need the first option because f(n-i) might be worse than (n-i) itself.
          For example: f(3) = 2 (1*2), but using 3 directly gives 3 which is better.
          The "break" requirement only applies to the original n, not sub-pieces.

    Alternative (cleaner): define f(n) as the max product OR n itself (no forced break):
        dp[i] = max value achievable from number i (either i itself or broken)
        dp[1] = 1, dp[2] = 2, dp[3] = 3  (as pieces, they're worth their face value)
        For the final answer, we MUST break, so try all first cuts.

    ════════════════════════════════════════════════════════════════════════
    APPROACH AS UNBOUNDED KNAPSACK (1D)
    ════════════════════════════════════════════════════════════════════════

    Think of it as: pieces = [1, 2, 3, ..., n-1], each can be used multiple times.
    dp[length] = maximum product for breaking `length` (where pieces keep their value).

    But since product is multiplicative (not additive), we can't directly use
    the standard knapsack "add profit" approach. Instead:

    dp[i] = max product obtainable from integer i
    dp[1] = 1

    for i = 2 to n:
        for j = 1 to i-1:
            dp[i] = max(dp[i], max(j, dp[j]) * max(i-j, dp[i-j]))

    Or simpler: only cut one piece j at a time, let the rest be handled by dp:
    for i = 2 to n:
        for j = 1 to i-1:
            dp[i] = max(dp[i], j * (i-j), j * dp[i-j])

    ════════════════════════════════════════════════════════════════════════
*/

class Solution{
    // ── Recursive ──
    // Time: O(2^n) — for each cut point, we branch
    // Space: O(n) recursion stack
    int integerBreakRecursive(int n){
        // Base: can't break 1 further
        if(n == 1)
            return 1;

        int maxProduct = 0;

        // Try every first cut: split into i and (n-i)
        for(int i = 1; i < n; i++){
            // Option 1: don't break (n-i) further → product = i * (n-i)
            // Option 2: break (n-i) further → product = i * f(n-i)
            int withoutFurtherBreak = i * (n - i);
            int withFurtherBreak = i * integerBreakRecursive(n - i);
            maxProduct = max(maxProduct, max(withoutFurtherBreak, withFurtherBreak));
        }

        return maxProduct;
    }

    // ── Top-Down with Memoization ──
    // Time: O(n^2) — n states, each tries n cuts
    // Space: O(n) for memo + recursion stack
    int integerBreakTopDown(int n, vector<int> &memo){
        if(n == 1)
            return 1;

        if(memo[n] != -1)
            return memo[n];

        int maxProduct = 0;

        for(int i = 1; i < n; i++){
            int withoutFurtherBreak = i * (n - i);
            int withFurtherBreak = i * integerBreakTopDown(n - i, memo);
            maxProduct = max(maxProduct, max(withoutFurtherBreak, withFurtherBreak));
        }

        memo[n] = maxProduct;
        return memo[n];
    }

    // ── Bottom-Up ──
    // Time: O(n^2)
    // Space: O(n)
    int integerBreakBottomUp(int n){
        // dp[n] stores the maximum product obtainable by breaking integer n into 2 or more parts.
        vector<int> dp(n+1, 0);
        dp[1] = 1;

        for(int i = 2; i <= n; i++){
            // Try every first cut: split i into j and (i-j)
            for(int j = 1; j < i; j++){
                // j * (i-j): use both pieces as-is (no further break of i-j)
                // j * dp[i-j]: use j as-is, break (i-j) further
                dp[i] = max(dp[i], max(j * (i - j), j * dp[i - j]));
            }
        }
        return dp[n];
    }

public:
    int integerBreak(int n){
        // return integerBreakRecursive(n);

        // vector<int> memo(n+1, -1);
        // memo[n] stores the maximum product obtainable by breaking integer n into 2 or more parts.
        // return integerBreakTopDown(n, memo);

        return integerBreakBottomUp(n);
    }
};


int main(){
    Solution obj;

    cout << "Integer break (2): " << obj.integerBreak(2) << endl;   // 1 (1*1)
    cout << "Integer break (10): " << obj.integerBreak(10) << endl; // 36 (3*3*4)
    cout << "Integer break (8): " << obj.integerBreak(8) << endl;   // 18 (2*3*3)
    cout << "Integer break (4): " << obj.integerBreak(4) << endl;   // 4 (2*2)

    return 0;
}
