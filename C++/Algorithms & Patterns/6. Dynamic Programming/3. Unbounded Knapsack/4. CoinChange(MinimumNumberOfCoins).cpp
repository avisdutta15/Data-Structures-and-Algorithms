#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Coin Change — Minimum Coins (LeetCode 322)
    ────────────────────────────────────────────────────

    Problem Statement:
    ------------------
    You are given an integer array coins representing coins of different
    denominations and an integer amount representing a total amount of money.
    Return the fewest number of coins that you need to make up that amount.
    If that amount of money cannot be made up, return -1.

    You may assume that you have an infinite number of each kind of coin.

    Examples:
    ---------
    Input:  coins = [1, 5, 6, 9], amount = 11
    Output: 2
    Explanation: 5 + 6 = 11. Two coins.

    Input:  coins = [2], amount = 3
    Output: -1

    Input:  coins = [1], amount = 0
    Output: 0

    Constraints:
    ------------
    - 1 <= coins.length <= 12
    - 1 <= coins[i] <= 2^31 - 1
    - 0 <= amount <= 10^4

    ════════════════════════════════════════════════════════════════════════
    KEY INSIGHT: Unbounded Knapsack — MINIMIZE instead of MAXIMIZE
    ════════════════════════════════════════════════════════════════════════

    Mapping to unbounded knapsack:
        - coins[] = item weights (each coin can be used unlimited times)
        - amount = knapsack capacity
        - We want to MINIMIZE the number of coins (items) used

    Differences from standard unbounded knapsack:
        - Standard: maximize profit
        - Coin change: minimize count (every coin has "cost" = 1)
        - max → min
        - Base case: f(n, 0) = 0 (need 0 coins for amount 0)
        - Impossible: return INT_MAX (or -1)

    ════════════════════════════════════════════════════════════════════════
    RECURRENCE
    ════════════════════════════════════════════════════════════════════════

    f(n, amount) = minimum coins needed using first n coin types to make amount

    Base cases:
        f(n, 0) = 0        (amount 0 needs 0 coins — valid)
        f(0, amount) = ∞   (no coin types, can't make positive amount — impossible)

    Recurrence:
        include = INT_MAX
        exclude = INT_MAX

        if coins[n-1] <= amount AND f(n, amount - coins[n-1]) != INT_MAX:
            include = 1 + f(n, amount - coins[n-1])     // use coin (STAY — can reuse)

        exclude = f(n-1, amount)                         // skip this coin type

        f(n, amount) = min(include, exclude)

    Answer: f(N, amount). If == INT_MAX, return -1.

    ════════════════════════════════════════════════════════════════════════
    COMPARISON WITH UNBOUNDED KNAPSACK
    ════════════════════════════════════════════════════════════════════════

    Unbounded Knapsack (maximize profit):
        include = profit[n-1] + f(n, W - weight[n-1])
        exclude = f(n-1, W)
        f(n, W) = max(include, exclude)

    Coin Change (minimize coins):
        include = 1 + f(n, amount - coins[n-1])      // "profit" = 1 (one coin used)
        exclude = f(n-1, amount)
        f(n, amount) = min(include, exclude)          // min instead of max

    Changes:
        profit[n-1] → 1 (each coin costs 1 unit)
        max → min
        0 (base for no items) → INT_MAX (impossible)
        0 (base for no capacity) → 0 (0 coins for amount 0)

    ════════════════════════════════════════════════════════════════════════
    1D OPTIMIZATION (Left to Right — Unbounded)
    ════════════════════════════════════════════════════════════════════════

    for each coin n (0 to N-1):
        for amt = coins[n] to amount:    ← LEFT to RIGHT (can reuse coin)
            if dp[amt - coins[n]] != INT_MAX:
                dp[amt] = min(dp[amt], 1 + dp[amt - coins[n]])

    ════════════════════════════════════════════════════════════════════════
*/

class Solution{
    // ── Recursive ──
    // Time: O(N^amount) worst case — exponential branching
    // Space: O(amount) recursion stack
    int coinChangeRecursive(vector<int> &coins, int N, int amount){
        // Base case: amount 0 needs 0 coins
        if(amount == 0)
            return 0;
        // Base case: no coins left, can't make positive amount
        if(N == 0)
            return INT_MAX;

        int include = INT_MAX, exclude = INT_MAX;

        // Use coin N (stay at N — can reuse same coin)
        if(coins[N-1] <= amount){
            int subResult = coinChangeRecursive(coins, N, amount - coins[N-1]);
            if(subResult != INT_MAX)
                include = 1 + subResult;
        }

        // Skip coin N (move to N-1)
        exclude = coinChangeRecursive(coins, N-1, amount);

        return min(include, exclude);
    }

    // ── Top-Down with 2D Memoization ──
    // Time: O(N * amount) — N×amount unique states
    // Space: O(N * amount) for memo + O(amount) recursion stack
    int coinChangeTopDown(vector<int> &coins, int N, int amount, vector<vector<int>> &memo){
        if(amount == 0)
            return 0;
        if(N == 0)
            return INT_MAX;

        if(memo[N][amount] != -1)
            return memo[N][amount];

        int include = INT_MAX, exclude = INT_MAX;

        if(coins[N-1] <= amount){
            int subResult = coinChangeTopDown(coins, N, amount - coins[N-1], memo);
            if(subResult != INT_MAX)
                include = 1 + subResult;
        }

        exclude = coinChangeTopDown(coins, N-1, amount, memo);

        memo[N][amount] = min(include, exclude);
        return memo[N][amount];
    }

    // ── Bottom-Up 2D ──
    // Time: O(N * amount)
    // Space: O(N * amount)
    int coinChangeBottomUp(vector<int> &coins, int N, int amount){
        vector<vector<int>> dp(N+1, vector<int>(amount+1, 0));

        for(int n = 0; n <= N; n++){
            for(int amt = 0; amt <= amount; amt++){
                if(amt == 0){
                    dp[n][amt] = 0;          // 0 coins needed for amount 0
                }
                else if(n == 0){
                    dp[n][amt] = INT_MAX;    // impossible: no coins, positive amount
                }
                else{
                    int include = INT_MAX, exclude = INT_MAX;

                    // Use coin n (stay at n — unbounded)
                    if(coins[n-1] <= amt && dp[n][amt - coins[n-1]] != INT_MAX)
                        include = 1 + dp[n][amt - coins[n-1]];

                    // Skip coin n
                    exclude = dp[n-1][amt];

                    dp[n][amt] = min(include, exclude);
                }
            }
        }
        return dp[N][amount];
    }

    // ── Bottom-Up 1D ──
    // Time: O(N * amount)
    // Space: O(amount)
    // Left to right (unbounded — same coin reusable)
    int coinChangeBottomUp1D(vector<int> &coins, int N, int amount){
        vector<int> dp(amount+1, INT_MAX);
        dp[0] = 0;  // 0 coins needed for amount 0

        for(int n = 0; n < N; n++){
            // LEFT to RIGHT: allows reusing coin[n]
            for(int amt = coins[n]; amt <= amount; amt++){
                if(dp[amt - coins[n]] != INT_MAX)
                    dp[amt] = min(dp[amt], 1 + dp[amt - coins[n]]);
            }
        }
        return dp[amount];
    }

public:
    int coinChange(vector<int> coins, int amount){
        int N = coins.size();

        // return coinChangeRecursive(coins, N, amount);

        // vector<vector<int>> memo(N+1, vector<int>(amount+1, -1));
        // return coinChangeTopDown(coins, N, amount, memo);

        // int result = coinChangeBottomUp(coins, N, amount);

        int result = coinChangeBottomUp1D(coins, N, amount);

        return (result == INT_MAX) ? -1 : result;
    }
};


int main(){
    Solution obj;

    vector<int> coins1 = {1, 5, 6, 9};
    cout << "Min coins (11): " << obj.coinChange(coins1, 11) << endl;  // 2 (5+6)

    vector<int> coins2 = {2};
    cout << "Min coins (3): " << obj.coinChange(coins2, 3) << endl;    // -1

    vector<int> coins3 = {1};
    cout << "Min coins (0): " << obj.coinChange(coins3, 0) << endl;    // 0

    vector<int> coins4 = {1, 2, 5};
    cout << "Min coins (11): " << obj.coinChange(coins4, 11) << endl;  // 3 (5+5+1)

    return 0;
}
