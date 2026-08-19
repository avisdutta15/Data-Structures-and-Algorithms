#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Maximum Number of Segments of Lengths a, b, and c
    ────────────────────────────────────────────────────────────

    Problem Statement:
    ------------------
    Given a positive integer N, and three positive integers a, b, and c.
    Cut the rod of length N into the maximum number of segments of lengths
    a, b, or c. Each segment must be of length a, b, or c (no leftover allowed).

    Examples:
    ---------
    Input:  N = 7, a = 5, b = 2, c = 5
    Output: 2
    Explanation: Cut into 5 + 2 = 7. Two segments.

    Input:  N = 17, a = 2, b = 1, c = 3
    Output: 17
    Explanation: Cut into 17 segments of length 1.

    Input:  N = 4, a = 3, b = 5, c = 7
    Output: 0
    Explanation: Can't cut 4 into pieces of 3, 5, or 7 with no leftover.

    ════════════════════════════════════════════════════════════════════════
    KEY INSIGHT: This IS Coin Change (min coins) but MAXIMIZE instead
    ════════════════════════════════════════════════════════════════════════

    Mapping to Coin Change:
        - coins = [a, b, c]    (segment lengths = coin denominations)
        - amount = N            (rod length = target amount)
        - Each coin reusable   (can cut same length multiple times)
        - MAXIMIZE number of coins used (opposite of LC 322 which minimizes)

    Coin Change (LC 322): minimize coins → min + base impossible = INT_MAX
    Max Segments:         maximize segments → max + base impossible = INT_MIN (or -1)

    ════════════════════════════════════════════════════════════════════════
    RECURRENCE
    ════════════════════════════════════════════════════════════════════════

    coins = [a, b, c], N = number of coin types (3)

    f(n, length) = max segments using first n segment types for rod of given length

    Base cases:
        f(n, 0) = 0         (rod fully cut, 0 more segments needed — valid!)
        f(0, length) = -1   (no segment types left, can't cut — impossible)

    Recurrence:
        include = -1
        exclude = -1

        if coins[n-1] <= length AND f(n, length - coins[n-1]) != -1:
            include = 1 + f(n, length - coins[n-1])    // cut this segment (STAY — can reuse)

        exclude = f(n-1, length)                        // skip this segment type

        f(n, length) = max(include, exclude)

    Answer: f(N, rodLength). If == -1, return 0.

    ════════════════════════════════════════════════════════════════════════
    COMPARISON
    ════════════════════════════════════════════════════════════════════════

    Coin Change (min coins, LC 322):
        include = 1 + f(n, amt - coins[n-1])
        f(n, amt) = min(include, exclude)
        Base impossible = INT_MAX

    Max Segments (max cuts):
        include = 1 + f(n, len - coins[n-1])
        f(n, len) = max(include, exclude)
        Base impossible = -1

    Same structure, just min → max and INT_MAX → -1.

    ════════════════════════════════════════════════════════════════════════
    1D OPTIMIZATION (Left to Right — Unbounded)
    ════════════════════════════════════════════════════════════════════════

    for each segment length s in coins:
        for len = s to N:       ← LEFT to RIGHT (can reuse same segment)
            if dp[len - s] != -1:
                dp[len] = max(dp[len], 1 + dp[len - s])

    ════════════════════════════════════════════════════════════════════════
*/

class Solution{
    // ── Recursive ──
    // Time: O(3^N) worst case
    // Space: O(N) recursion stack
    int maxSegmentsRecursive(vector<int> &coins, int N, int length){
        if(length == 0)
            return 0;       // rod fully used — valid
        if(N == 0)
            return -1;      // no segment types, can't cut — impossible

        int include = -1, exclude = -1;

        // Cut segment of coins[N-1] (stay at N — can reuse)
        if(coins[N-1] <= length){
            int subResult = maxSegmentsRecursive(coins, N, length - coins[N-1]);
            if(subResult != -1)
                include = 1 + subResult;
        }

        // Skip this segment type (move to N-1)
        exclude = maxSegmentsRecursive(coins, N-1, length);

        return max(include, exclude);
    }

    // ── Top-Down with 2D Memoization ──
    // Time: O(N * rodLength) where N = number of segment types (3)
    // Space: O(N * rodLength) for memo
    int maxSegmentsTopDown(vector<int> &coins, int N, int length, vector<vector<int>> &memo){
        if(length == 0)
            return 0;
        if(N == 0)
            return -1;

        if(memo[N][length] != -2)   // using -2 as "not computed" since -1 means impossible
            return memo[N][length];

        int include = -1, exclude = -1;

        if(coins[N-1] <= length){
            int subResult = maxSegmentsTopDown(coins, N, length - coins[N-1], memo);
            if(subResult != -1)
                include = 1 + subResult;
        }

        exclude = maxSegmentsTopDown(coins, N-1, length, memo);

        memo[N][length] = max(include, exclude);
        return memo[N][length];
    }

    // ── Bottom-Up 2D ──
    // Time: O(N * rodLength)
    // Space: O(N * rodLength)
    int maxSegmentsBottomUp(vector<int> &coins, int N, int rodLength){
        vector<vector<int>> dp(N+1, vector<int>(rodLength+1, -1));

        // Base case: length 0 is achievable with 0 segments
        for(int n = 0; n <= N; n++)
            dp[n][0] = 0;

        for(int n = 1; n <= N; n++){
            for(int l = 1; l <= rodLength; l++){
                int include = -1, exclude = -1;

                // Cut segment of coins[n-1] (stay at n — unbounded)
                if(coins[n-1] <= l && dp[n][l - coins[n-1]] != -1)
                    include = 1 + dp[n][l - coins[n-1]];

                // Skip this segment type
                exclude = dp[n-1][l];

                dp[n][l] = max(include, exclude);
            }
        }
        return dp[N][rodLength];
    }

    // ── Bottom-Up 1D ──
    // Time: O(N * rodLength) where N = 3
    // Space: O(rodLength)
    // Left to right (unbounded — same segment reusable)
    int maxSegmentsBottomUp1D(vector<int> &coins, int N, int rodLength){
        vector<int> dp(rodLength+1, -1);
        dp[0] = 0;  // 0 segments needed for length 0

        for(int n = 0; n < N; n++){
            // LEFT to RIGHT: allows reusing coins[n]
            for(int l = coins[n]; l <= rodLength; l++){
                if(dp[l - coins[n]] != -1)
                    dp[l] = max(dp[l], 1 + dp[l - coins[n]]);
            }
        }
        return dp[rodLength];
    }

public:
    int maxSegments(int rodLength, int a, int b, int c){
        vector<int> coins = {a, b, c};
        int N = coins.size();  // always 3

        // return maxSegmentsRecursive(coins, N, rodLength);

        // vector<vector<int>> memo(N+1, vector<int>(rodLength+1, -2));
        // int result = maxSegmentsTopDown(coins, N, rodLength, memo);

        // int result = maxSegmentsBottomUp(coins, N, rodLength);

        int result = maxSegmentsBottomUp1D(coins, N, rodLength);

        return (result == -1) ? 0 : result;
    }
};


int main(){
    Solution obj;

    cout << "Max segments (7, a=5, b=2, c=5): " << obj.maxSegments(7, 5, 2, 5) << endl;   // 2
    cout << "Max segments (17, a=2, b=1, c=3): " << obj.maxSegments(17, 2, 1, 3) << endl;  // 17
    cout << "Max segments (4, a=3, b=5, c=7): " << obj.maxSegments(4, 3, 5, 7) << endl;    // 0
    cout << "Max segments (11, a=2, b=3, c=5): " << obj.maxSegments(11, 2, 3, 5) << endl;  // 5 (2+2+2+2+3)

    return 0;
}
