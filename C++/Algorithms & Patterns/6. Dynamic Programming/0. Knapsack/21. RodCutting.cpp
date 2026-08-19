#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Rod Cutting
    ─────────────────────

    Problem Statement:
    ------------------
    Given a rod of length N and a price table where price[i] denotes the price
    of a piece of length (i+1). Determine the maximum revenue obtainable by
    cutting up the rod and selling the pieces.

    Examples:
    ---------
    Input:  N = 8, price = [1, 5, 8, 9, 10, 17, 17, 20]
            (length 1 costs 1, length 2 costs 5, ..., length 8 costs 20)
    Output: 22
    Explanation: Cut into pieces of length 2 and 6: price[1] + price[5] = 5 + 17 = 22.

    Input:  N = 4, price = [2, 5, 7, 8]
    Output: 10
    Explanation: Cut into two pieces of length 2: 5 + 5 = 10.

    ════════════════════════════════════════════════════════════════════════
    KEY INSIGHT: This IS Unbounded Knapsack
    ════════════════════════════════════════════════════════════════════════

    Mapping to unbounded knapsack:
        - Rod length N = Knapsack capacity W
        - Piece lengths [1, 2, 3, ..., N] = Item weights
        - price[i] = Item profits
        - Each piece length can be cut multiple times = Items are REUSABLE

    So:
        weight[] = [1, 2, 3, ..., N]     (all possible cut lengths)
        profit[] = price[]                (revenue for each cut length)
        Capacity = N                      (total rod length)

    Find max profit with unlimited usage of items = unbounded knapsack.

    ════════════════════════════════════════════════════════════════════════
    RECURRENCE
    ════════════════════════════════════════════════════════════════════════

    f(n, length) = max revenue using first n piece-sizes with remaining rod length

    Base cases:
        f(0, length) = 0     (no piece sizes to use → 0 revenue)
        f(n, 0) = 0          (no rod remaining → 0 revenue)

    Recurrence:
        cut = INT_MIN
        skip = INT_MIN

        if pieceLength[n-1] <= length:
            cut = price[n-1] + f(n, length - pieceLength[n-1])   // cut this size (STAY — can reuse)

        skip = f(n-1, length)                                     // skip this size

        f(n, length) = max(cut, skip)

    Since pieceLength[i] = i+1, we can simplify:
        cut = INT_MIN
        skip = INT_MIN

        if (n <= length):
            cut = price[n-1] + f(n, length - n)     // cut piece of length n (reuse allowed)

        skip = f(n-1, length)                        // don't cut this length

        f(n, length) = max(cut, skip)

    Answer: f(N, N)

    ════════════════════════════════════════════════════════════════════════
    1D OPTIMIZATION (Left to Right — Unbounded)
    ════════════════════════════════════════════════════════════════════════

    Since this is unbounded knapsack:
        dp[length] = max revenue for rod of given length
        Iterate left to right so each piece size can be reused.

    for each piece size n (1 to N):
        pieceLen = n
        for length = pieceLen to N:     ← LEFT to RIGHT (unbounded)
            dp[length] = max(dp[length], price[n-1] + dp[length - pieceLen])

    ════════════════════════════════════════════════════════════════════════
*/

class Solution{
    // ── Recursive ──
    // Time: O(2^rodLength) — at each step we either cut (stay) or skip, and cutting
    //       can repeat up to rodLength/1 times for the smallest piece.
    // Space: O(rodLength) recursion stack depth
    int rodCutRecursive(vector<int> &price, vector<int> &pieceLength, int N, int rodLength){
        // Base case: no piece sizes or no rod remaining
        if(N == 0 || rodLength == 0)
            return 0;

        int cut = INT_MIN, skip = INT_MIN;

        // Cut piece of pieceLength[N-1] (stay at N — can cut same length again)
        if(pieceLength[N-1] <= rodLength)
            cut = price[N-1] + rodCutRecursive(price, pieceLength, N, rodLength - pieceLength[N-1]);

        // Skip this piece length (move to N-1)
        skip = rodCutRecursive(price, pieceLength, N-1, rodLength);

        return max(cut, skip);
    }

    // ── Top-Down with 2D Memoization ──
    // Time: O(N * rodLength) — N×rodLength unique states, each computed once
    // Space: O(N * rodLength) for memo table + O(rodLength) recursion stack
    int rodCutTopDown(vector<int> &price, vector<int> &pieceLength, int N, int rodLength, vector<vector<int>> &memo){
        if(N == 0 || rodLength == 0)
            return 0;

        if(memo[N][rodLength] != -1)
            return memo[N][rodLength];

        int cut = INT_MIN, skip = INT_MIN;

        if(pieceLength[N-1] <= rodLength)
            cut = price[N-1] + rodCutTopDown(price, pieceLength, N, rodLength - pieceLength[N-1], memo);
        skip = rodCutTopDown(price, pieceLength, N-1, rodLength, memo);

        memo[N][rodLength] = max(cut, skip);
        return memo[N][rodLength];
    }

    // ── Bottom-Up 2D ──
    // Time: O(N * rodLength) — two nested loops
    // Space: O(N * rodLength) for the dp table
    int rodCutBottomUp(vector<int> &price, vector<int> &pieceLength, int N, int rodLength){
        vector<vector<int>> dp(N+1, vector<int>(rodLength+1, 0));

        for(int n = 0; n <= N; n++){
            for(int l = 0; l <= rodLength; l++){
                if(n == 0 || l == 0){
                    dp[n][l] = 0;
                }
                else{
                    int cut = INT_MIN, skip = INT_MIN;
                    // Cut piece of pieceLength[n-1] (stay at n — unbounded)
                    if(pieceLength[n-1] <= l)
                        cut = price[n-1] + dp[n][l - pieceLength[n-1]];
                    // Skip piece of this length
                    skip = dp[n-1][l];
                    dp[n][l] = max(cut, skip);
                }
            }
        }
        return dp[N][rodLength];
    }

    // ── Bottom-Up 1D ──
    // Time: O(N * rodLength) — two nested loops
    // Space: O(rodLength) — single 1D array
    // Left to right (unbounded — can reuse each piece length)
    int rodCutBottomUp1D(vector<int> &price, vector<int> &pieceLength, int N, int rodLength){
        vector<int> dp(rodLength+1, 0);

        // For each piece size
        for(int n = 0; n < N; n++){
            // LEFT to RIGHT: allows reusing piece of pieceLength[n]
            for(int l = pieceLength[n]; l <= rodLength; l++){
                dp[l] = max(dp[l], price[n] + dp[l - pieceLength[n]]);
            }
        }
        return dp[rodLength];
    }

public:
    int rodCut(vector<int> &price){
        int N = price.size();

        // Create explicit pieceLength array: [1, 2, 3, ..., N]
        vector<int> pieceLength;
        for(int i = 1; i <= N; i++)
            pieceLength.push_back(i);

        int rodLength = N;

        // return rodCutRecursive(price, pieceLength, N, rodLength);

        // vector<vector<int>> memo(N+1, vector<int>(rodLength+1, -1));
        // return rodCutTopDown(price, pieceLength, N, rodLength, memo);

        // return rodCutBottomUp(price, pieceLength, N, rodLength);

        return rodCutBottomUp1D(price, pieceLength, N, rodLength);
    }
};


int main(){
    Solution obj;

    vector<int> price1 = {1, 5, 8, 9, 10, 17, 17, 20};
    cout << "Max revenue (N=8): " << obj.rodCut(price1) << endl;  // 22

    vector<int> price2 = {2, 5, 7, 8};
    cout << "Max revenue (N=4): " << obj.rodCut(price2) << endl;  // 10

    vector<int> price3 = {3, 5, 8, 9, 10, 17, 17, 20};
    cout << "Max revenue (N=8): " << obj.rodCut(price3) << endl;  // 24 (eight pieces of length 1)

    return 0;
}
