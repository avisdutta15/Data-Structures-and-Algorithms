#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Coin Change 2 — Number of Ways (LeetCode 518)
    ───────────────────────────────────────────────────────

    Problem Statement:
    ------------------
    You are given an integer array coins representing coins of different
    denominations and an integer amount representing a total amount of money.
    Return the number of COMBINATIONS that make up that amount.
    If that amount cannot be made up, return 0.

    You may assume that you have an infinite number of each kind of coin.
    The answer is guaranteed to fit into a signed 32-bit integer.

    Note: COMBINATIONS, not permutations. [1,2] and [2,1] count as ONE way.

    Examples:
    ---------
    Input:  coins = [1, 2, 5], amount = 5
    Output: 4
    Explanation: 
        5 = 5
        5 = 2 + 2 + 1
        5 = 2 + 1 + 1 + 1
        5 = 1 + 1 + 1 + 1 + 1
        Four combinations.

    Input:  coins = [2], amount = 3
    Output: 0

    Input:  coins = [10], amount = 10
    Output: 1

    Constraints:
    ------------
    - 1 <= coins.length <= 300
    - 1 <= coins[i] <= 5000
    - 0 <= amount <= 5000

    ════════════════════════════════════════════════════════════════════════
    KEY INSIGHT: Unbounded Knapsack — COUNT ways
    ════════════════════════════════════════════════════════════════════════

    Mapping to unbounded knapsack:
        - coins[] = item weights (each reusable)
        - amount = knapsack capacity
        - We want to COUNT combinations (not maximize/minimize)

    ════════════════════════════════════════════════════════════════════════
    COMPARISON: Coin Change (min) vs Coin Change 2 (count)
    ════════════════════════════════════════════════════════════════════════

    Coin Change (LC 322 — minimize coins):
        include = 1 + f(n, amount - coins[n-1])
        exclude = f(n-1, amount)
        f(n, amount) = min(include, exclude)
        Base: f(n,0)=0, f(0,amt)=INT_MAX

    Coin Change 2 (LC 518 — count ways):
        include = f(n, amount - coins[n-1])
        exclude = f(n-1, amount)
        f(n, amount) = include + exclude         ← ADD (count ways)
        Base: f(n,0)=1, f(0,amt)=0

    Changes:
        min → + (sum up all ways)
        1 + f(...) → f(...) (not counting items, counting paths)
        Base f(n,0) = 1 (one way to make amount 0: use no coins)
        Base f(0,amt) = 0 (no coins, zero ways for positive amount)

    ════════════════════════════════════════════════════════════════════════
    RECURRENCE
    ════════════════════════════════════════════════════════════════════════

    f(n, amount) = number of ways to make amount using first n coin types

    Base cases:
        f(n, 0) = 1        (one way to make 0: use nothing)
        f(0, amount) = 0   (no coins, can't make positive amount)

    Recurrence:
        include = 0
        exclude = 0

        if coins[n-1] <= amount:
            include = f(n, amount - coins[n-1])     // use coin (STAY — can reuse)

        exclude = f(n-1, amount)                     // skip this coin type

        f(n, amount) = include + exclude

    Answer: f(N, amount)

    ════════════════════════════════════════════════════════════════════════
    1D OPTIMIZATION (Left to Right — Unbounded)
    ════════════════════════════════════════════════════════════════════════

    for each coin n (0 to N-1):
        for amt = coins[n] to amount:    ← LEFT to RIGHT (can reuse coin)
            dp[amt] = dp[amt] + dp[amt - coins[n]]

    Why this gives COMBINATIONS (not permutations):
    - Outer loop is over COINS. We process coin 1 fully, then coin 2, etc.
    - This ensures we never count [1,2] and [2,1] as different.
    - If outer loop were over AMOUNT and inner over COINS, we'd get permutations
      (that would be Combination Sum IV, LC 377).

    ════════════════════════════════════════════════════════════════════════
*/

class Solution{
    // ── Recursive ──
    // Time: O(N^amount) worst case
    // Space: O(amount) recursion stack
    int coinChange2Recursive(vector<int> &coins, int N, int amount){
        // One way to make amount 0: use nothing
        if(amount == 0)
            return 1;
        // No coins, can't make positive amount
        if(N == 0)
            return 0;

        int include = 0, exclude = 0;

        // Use coin N (stay at N — can reuse)
        if(coins[N-1] <= amount)
            include = coinChange2Recursive(coins, N, amount - coins[N-1]);

        // Skip coin N (move to N-1)
        exclude = coinChange2Recursive(coins, N-1, amount);

        return include + exclude;
    }

    // ── Top-Down with 2D Memoization ──
    // Time: O(N * amount)
    // Space: O(N * amount) for memo + O(amount) recursion stack
    int coinChange2TopDown(vector<int> &coins, int N, int amount, vector<vector<int>> &memo){
        if(amount == 0)
            return 1;
        if(N == 0)
            return 0;

        if(memo[N][amount] != -1)
            return memo[N][amount];

        int include = 0, exclude = 0;

        if(coins[N-1] <= amount)
            include = coinChange2TopDown(coins, N, amount - coins[N-1], memo);
        exclude = coinChange2TopDown(coins, N-1, amount, memo);

        memo[N][amount] = include + exclude;
        return memo[N][amount];
    }

    // ── Bottom-Up 2D ──
    // Time: O(N * amount)
    // Space: O(N * amount)
    int coinChange2BottomUp(vector<int> &coins, int N, int amount){
        vector<vector<int>> dp(N+1, vector<int>(amount+1, 0));

        for(int n = 0; n <= N; n++){
            for(int amt = 0; amt <= amount; amt++){
                if(amt == 0){
                    dp[n][amt] = 1;      // one way to make 0: use nothing
                }
                else if(n == 0){
                    dp[n][amt] = 0;      // no coins, can't make positive amount
                }
                else{
                    int include = 0, exclude = 0;

                    // Use coin n (stay at n — unbounded)
                    if(coins[n-1] <= amt)
                        include = dp[n][amt - coins[n-1]];

                    // Skip coin n
                    exclude = dp[n-1][amt];

                    dp[n][amt] = include + exclude;
                }
            }
        }
        return dp[N][amount];
    }

    // ── Bottom-Up 1D ──
    // Time: O(N * amount)
    // Space: O(amount)
    // Left to right (unbounded — same coin reusable)
    // Outer loop = coins → gives COMBINATIONS (not permutations)
    int coinChange2BottomUp1D(vector<int> &coins, int N, int amount){
        vector<int> dp(amount+1, 0);
        dp[0] = 1;  // one way to make 0

        // Outer loop over coins → combinations
        for(int n = 0; n < N; n++){
            // LEFT to RIGHT: allows reusing coins[n]
            for(int amt = coins[n]; amt <= amount; amt++){
                dp[amt] = dp[amt] + dp[amt - coins[n]];
            }
        }
        return dp[amount];
    }

public:
    int change(vector<int> coins, int amount){
        int N = coins.size();

        // return coinChange2Recursive(coins, N, amount);

        // vector<vector<int>> memo(N+1, vector<int>(amount+1, -1));
        // return coinChange2TopDown(coins, N, amount, memo);

        // return coinChange2BottomUp(coins, N, amount);

        return coinChange2BottomUp1D(coins, N, amount);
    }
};


int main(){
    Solution obj;

    vector<int> coins1 = {1, 2, 5};
    cout << "Ways to make 5: " << obj.change(coins1, 5) << endl;    // 4

    vector<int> coins2 = {2};
    cout << "Ways to make 3: " << obj.change(coins2, 3) << endl;    // 0

    vector<int> coins3 = {10};
    cout << "Ways to make 10: " << obj.change(coins3, 10) << endl;  // 1

    vector<int> coins4 = {1, 2, 5};
    cout << "Ways to make 0: " << obj.change(coins4, 0) << endl;    // 1

    return 0;
}
