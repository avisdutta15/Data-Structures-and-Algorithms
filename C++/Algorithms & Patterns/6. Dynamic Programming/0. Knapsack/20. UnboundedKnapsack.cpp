#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Unbounded Knapsack
    ────────────────────────────

    Problem Statement:
    ------------------
    Given N items where each item has a weight and profit, and a bag with capacity W.
    Each item can be used UNLIMITED times (unlike 0/1 knapsack where each item is used at most once).
    Find the maximum profit achievable.

    Examples:
    ---------
    Input:  N = 3, W = 4, profit = [1, 4, 5], weight = [2, 3, 4]
    Output: 5
    Explanation: Take item with weight 3 (profit 4) + item with weight 2... no, 3+2=5 > 4.
                 Take item with weight 4 (profit 5). Or take item weight 2 twice (profit 1+1=2).
                 Best: item 3 (weight 4, profit 5). Answer = 5? 
                 Actually: weight 2 item once = profit 1. weight 3 item once = profit 4. 
                 Weight 2 twice = profit 2. Best single item = weight 4, profit 5. ✓

    Input:  N = 2, W = 3, profit = [2, 3], weight = [1, 2]
    Output: 6
    Explanation: Take item with weight 1 three times → profit = 2*3 = 6.

    ════════════════════════════════════════════════════════════════════════
    KEY DIFFERENCE FROM 0/1 KNAPSACK
    ════════════════════════════════════════════════════════════════════════

    0/1 Knapsack:
        - Each item used at most ONCE.
        - After including item n, move to item n-1: f(n-1, w - weight[n-1])
        - In 1D: iterate w from RIGHT to LEFT.

    Unbounded Knapsack:
        - Each item can be used UNLIMITED times.
        - After including item n, STAY at item n: f(n, w - weight[n-1])
          (we can pick it again!)
        - In 1D: iterate w from LEFT to RIGHT.

    The ONLY change in the recurrence:
        0/1:        include = profit[n-1] + f(n-1, w - weight[n-1])   ← move to n-1
        Unbounded:  include = profit[n-1] + f(n, w - weight[n-1])     ← stay at n

    ════════════════════════════════════════════════════════════════════════
    RECURRENCE
    ════════════════════════════════════════════════════════════════════════

    f(n, w) = maximum profit using first n items (each reusable) with capacity w

    Base cases:
        f(0, w) = 0    (no items → 0 profit)
        f(n, 0) = 0    (no capacity → 0 profit)

    Recurrence:
        if weight[n-1] <= w:
            f(n, w) = max(
                profit[n-1] + f(n, w - weight[n-1]),    // include (STAY at n, can reuse)
                f(n-1, w)                                // exclude (move to n-1)
            )
        else:
            f(n, w) = f(n-1, w)    (can't include, too heavy)

    Answer: f(N, W)

    ════════════════════════════════════════════════════════════════════════
    2D → 1D SPACE OPTIMIZATION
    ════════════════════════════════════════════════════════════════════════

    In 0/1 knapsack:
        dp[n][w] uses dp[n-1][w-weight[n-1]] → previous row, smaller index
        1D: iterate w RIGHT to LEFT (so we don't reuse current row's updated values)

    In unbounded knapsack:
        dp[n][w] uses dp[n][w-weight[n-1]] → SAME row, smaller index
        1D: iterate w LEFT to RIGHT (we WANT to use current row's updated values,
            because using the updated value means we're reusing the same item!)

    0/1 (right to left):
        for(int n = 0; n < N; n++)
            for(int w = W; w >= weight[n]; w--)       ← right to left
                dp[w] = max(profit[n] + dp[w-weight[n]], dp[w]);

    Unbounded (left to right):
        for(int n = 0; n < N; n++)
            for(int w = weight[n]; w <= W; w++)       ← left to right
                dp[w] = max(profit[n] + dp[w-weight[n]], dp[w]);

    Why left to right gives unlimited usage:
        When computing dp[w], dp[w-weight[n]] has ALREADY been updated for item n
        in this iteration. So it might already include item n → item n gets used again.

    ════════════════════════════════════════════════════════════════════════
*/

class Solution{
    // ── Recursive: O(exponential) ──
    int unboundedKnapsackRecursive(vector<int> &profit, vector<int> &weight, int N, int W){
        // Base case: no items or no capacity
        if(N == 0 || W == 0)
            return 0;

        int include = INT_MIN, exclude = INT_MIN;

        // Include item N (STAY at N — can reuse it)
        if(weight[N-1] <= W)
            include = profit[N-1] + unboundedKnapsackRecursive(profit, weight, N, W - weight[N-1]);

        // Exclude item N (move to N-1 — done with this item)
        exclude = unboundedKnapsackRecursive(profit, weight, N-1, W);

        return max(include, exclude);
    }

    // ── Top-Down with 2D Memoization: O(N * W) ──
    int unboundedKnapsackTopDown(vector<int> &profit, vector<int> &weight, int N, int W,
                                  vector<vector<int>> &memo){
        if(N == 0 || W == 0)
            return 0;

        if(memo[N][W] != -1)
            return memo[N][W];

        int include = INT_MIN, exclude = INT_MIN;

        if(weight[N-1] <= W)
            include = profit[N-1] + unboundedKnapsackTopDown(profit, weight, N, W - weight[N-1], memo);
        exclude = unboundedKnapsackTopDown(profit, weight, N-1, W, memo);

        memo[N][W] = max(include, exclude);
        return memo[N][W];
    }

    // ── Bottom-Up 2D: O(N * W) ──
    int unboundedKnapsackBottomUp(vector<int> &profit, vector<int> &weight, int N, int W){
        vector<vector<int>> dp(N+1, vector<int>(W+1, 0));

        for(int n = 0; n <= N; n++){
            for(int w = 0; w <= W; w++){
                // Base case
                if(n == 0 || w == 0){
                    dp[n][w] = 0;
                }
                else{
                    int include = INT_MIN, exclude = INT_MIN;
                    if(weight[n-1] <= w)
                        // STAY at n (dp[n][...]) — can reuse item
                        include = profit[n-1] + dp[n][w - weight[n-1]];
                    // Move to n-1 (dp[n-1][...]) — exclude item
                    exclude = dp[n-1][w];
                    dp[n][w] = max(include, exclude);
                }
            }
        }
        return dp[N][W];
    }

    // ── Bottom-Up 1D: O(W) space ──
    // LEFT to RIGHT iteration — allows reusing same item multiple times
    int unboundedKnapsackBottomUp1D(vector<int> &profit, vector<int> &weight, int N, int W){
        vector<int> dp(W+1, 0);

        for(int n = 0; n < N; n++){
            // LEFT to RIGHT: dp[w-weight[n]] already updated for item n
            // → item n can be included again → unlimited usage
            for(int w = weight[n]; w <= W; w++){
                dp[w] = max(dp[w], profit[n] + dp[w - weight[n]]);
            }
        }
        return dp[W];
    }

public:
    int unboundedKnapsack(vector<int> &profit, vector<int> &weight, int W){
        int N = profit.size();

        // return unboundedKnapsackRecursive(profit, weight, N, W);

        // vector<vector<int>> memo(N+1, vector<int>(W+1, -1));
        // return unboundedKnapsackTopDown(profit, weight, N, W, memo);

        // return unboundedKnapsackBottomUp(profit, weight, N, W);

        return unboundedKnapsackBottomUp1D(profit, weight, N, W);
    }
};


int main(){
    Solution obj;

    vector<int> profit1 = {1, 4, 5};
    vector<int> weight1 = {2, 3, 4};
    cout << "Max profit (W=4): " << obj.unboundedKnapsack(profit1, weight1, 4) << endl;  // 5

    vector<int> profit2 = {2, 3};
    vector<int> weight2 = {1, 2};
    cout << "Max profit (W=3): " << obj.unboundedKnapsack(profit2, weight2, 3) << endl;  // 6

    vector<int> profit3 = {10, 30, 20};
    vector<int> weight3 = {5, 10, 15};
    cout << "Max profit (W=100): " << obj.unboundedKnapsack(profit3, weight3, 100) << endl;  // 300

    return 0;
}
