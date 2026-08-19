#include <bits/stdc++.h>
using namespace std;

/*
    Problem: 3 Sum Partition (Partition into 3 equal sum subsets)
    ─────────────────────────────────────────────────────────────

    Problem Statement:
    ------------------
    Given an array of non-negative integers, determine if the array can be
    partitioned into THREE subsets such that the sum of elements in all three
    subsets is equal.

    Examples:
    ---------
    Input:  A = [1, 2, 3, 0, 3]
    Output: true
    Explanation: [1, 2], [3, 0], [3] all sum to 3.

    Input:  A = [0, 2, 1, 6, 3]
    Output: true
    Explanation: [0, 2, 1], [6], [3]... wait, 0+2+1=3, 6≠3.
                 Actually: [0, 6], [2, 1, 3], ... hmm. totalSum=12, target=4.
                 [2, 1, 0], [6]... doesn't work either. Let me recheck.
                 totalSum = 0+2+1+6+3 = 12, target = 4.
                 [0, 1, 3], [2, 6]... 2+6=8≠4. 
                 Actually this might be false. Let me use a simpler example.

    Input:  A = [3, 3, 3, 3, 3, 3]
    Output: true
    Explanation: totalSum=18, target=6. [3,3], [3,3], [3,3].

    Input:  A = [1, 2, 3, 4, 5, 6, 7]
    Output: false
    Explanation: totalSum=28, 28 % 3 != 0, impossible.

    ════════════════════════════════════════════════════════════════════════
    KEY INSIGHT: Reduction to 2-Subset Sum
    ════════════════════════════════════════════════════════════════════════

    For 2 Partition:
        Find subset with sum = totalSum / 2.
        The remaining elements automatically form the other subset.

    For 3 Partition:
        Each subset must have sum = totalSum / 3.
        If we can find:
            - Subset S1 with sum = totalSum/3
            - Subset S2 (from remaining elements) with sum = totalSum/3
        Then the leftover elements S3 will automatically sum to totalSum/3.

    So: Find TWO disjoint subsets each summing to totalSum/3.
    This is a 2D subset sum problem!

    Pre-check: If totalSum % 3 != 0, partition is impossible.

    ════════════════════════════════════════════════════════════════════════
    RECURRENCE
    ════════════════════════════════════════════════════════════════════════

    f(n, s1, s2) = can we form sum s1 for subset1 AND sum s2 for subset2
                   using first n elements?

    Each element has 3 choices:
        - Put in subset 1 (reduces s1)
        - Put in subset 2 (reduces s2)
        - Put in subset 3 (don't reduce either — leftovers go to S3)

    Base cases:
        f(0, 0, 0) = true      (both targets met, remaining = S3)
        f(0, s1, s2) = false   if s1 != 0 or s2 != 0

    Recurrence:
        f(n, s1, s2) =
            (put in S1): if A[n-1] <= s1, f(n-1, s1 - A[n-1], s2)
            OR
            (put in S2): if A[n-1] <= s2, f(n-1, s1, s2 - A[n-1])
            OR
            (put in S3): f(n-1, s1, s2)   ← leave it for the third subset

    Answer: f(N, totalSum/3, totalSum/3)

    Note: This has 3 changing parameters (n, s1, s2) so memoization needs
    a 3D table or a map with 3-key. Time: O(N * target * target).

    ════════════════════════════════════════════════════════════════════════
    COMPARISON WITH 2-PARTITION
    ════════════════════════════════════════════════════════════════════════

    2-Partition:
        Each element: include in S1 or exclude (goes to S2).
        States: f(n, s) — 2D
        Time: O(N * totalSum/2)

    3-Partition:
        Each element: put in S1, S2, or S3.
        States: f(n, s1, s2) — 3D
        Time: O(N * (totalSum/3)^2)

    ════════════════════════════════════════════════════════════════════════
*/

class Solution{
    // ── Recursive: O(3^N) time ──
    // Each element has 3 choices: go to S1, S2, or S3
    bool threeSumPartitionRecursive(vector<int> &A, int N, int s1, int s2){
        // Both subsets reached their target — remaining elements form S3
        if(N == 0 && s1 == 0 && s2 == 0)
            return true;
        // No more elements but targets not met
        if(N == 0)
            return false;

        bool putInS1 = false, putInS2 = false, putInS3 = false;

        // Choice 1: Put A[N-1] in subset 1
        if(A[N-1] <= s1)
            putInS1 = threeSumPartitionRecursive(A, N-1, s1 - A[N-1], s2);

        // Choice 2: Put A[N-1] in subset 2
        if(A[N-1] <= s2)
            putInS2 = threeSumPartitionRecursive(A, N-1, s1, s2 - A[N-1]);

        // Choice 3: Put A[N-1] in subset 3 (leave for leftovers)
        putInS3 = threeSumPartitionRecursive(A, N-1, s1, s2);

        return putInS1 || putInS2 || putInS3;
    }

    // ── Top-Down Memoization: O(N * target * target) time ──
    // 3 changing parameters: N, s1, s2
    bool threeSumPartitionTopDown(vector<int> &A, int N, int s1, int s2, 
                                  unordered_map<string, bool> &lookup){
        if(N == 0 && s1 == 0 && s2 == 0)
            return true;
        if(N == 0)
            return false;

        string key = to_string(N) + " " + to_string(s1) + " " + to_string(s2);
        if(lookup.find(key) != lookup.end())
            return lookup[key];

        bool putInS1 = false, putInS2 = false, putInS3 = false;

        if(A[N-1] <= s1)
            putInS1 = threeSumPartitionTopDown(A, N-1, s1 - A[N-1], s2, lookup);
        if(A[N-1] <= s2)
            putInS2 = threeSumPartitionTopDown(A, N-1, s1, s2 - A[N-1], lookup);
        putInS3 = threeSumPartitionTopDown(A, N-1, s1, s2, lookup);

        lookup[key] = putInS1 || putInS2 || putInS3;
        return lookup[key];
    }

    // ── Top-Down with 3D Vector Memoization ──
    // 3 changing parameters → 3D vector memo[N+1][target+1][target+1]
    //   - Dimension 1 (n): items considered (0 to N)
    //   - Dimension 2 (s1): remaining sum for subset 1 (0 to target)
    //   - Dimension 3 (s2): remaining sum for subset 2 (0 to target)
    // Values: -1 = not computed, 0 = false, 1 = true
    // Advantage over hashmap: direct O(1) indexing, no string allocation overhead.
    bool threeSumPartitionTopDown2(vector<int> &A, int N, int s1, int s2,
                                   vector<vector<vector<int>>> &memo){
        if(N == 0 && s1 == 0 && s2 == 0)
            return true;
        if(N == 0)
            return false;

        // Check memo: -1 means not computed yet
        if(memo[N][s1][s2] != -1)
            return memo[N][s1][s2];

        bool putInS1 = false, putInS2 = false, putInS3 = false;

        if(A[N-1] <= s1)
            putInS1 = threeSumPartitionTopDown2(A, N-1, s1 - A[N-1], s2, memo);
        if(A[N-1] <= s2)
            putInS2 = threeSumPartitionTopDown2(A, N-1, s1, s2 - A[N-1], memo);
        putInS3 = threeSumPartitionTopDown2(A, N-1, s1, s2, memo);

        memo[N][s1][s2] = (putInS1 || putInS2 || putInS3) ? 1 : 0;
        return memo[N][s1][s2];
    }

    // ── Bottom-Up: O(N * target * target) time and space ──
    // dp[n][s1][s2] = can we form sum s1 for S1 and sum s2 for S2 using first n elements?
    bool threeSumPartitionBottomUp(vector<int> &A, int N, int target){
        // 3D DP table: dp[n][s1][s2]
        vector<vector<vector<bool>>> dp(N+1, 
            vector<vector<bool>>(target+1, vector<bool>(target+1, false)));

        // Base case (equivalent to recursive base):
        // ─────────────────────────────────────────
        // In recursion:
        //   f(0, 0, 0) = true   → no items, both targets met
        //   f(0, s1, s2) = false if s1 != 0 or s2 != 0
        //
        // In bottom-up: we initialized everything to false,
        // so we only need to set dp[0][0][0] = true.
        // The n=0 row serves as the base case.
        dp[0][0][0] = true;

        // Fill from n=1 to N
        // ──────────────────
        // Why start from n=1?
        // n=0 is the base case (already filled above).
        // n=1 means "considering the first 1 item" — it looks up dp[n-1] = dp[0] (the base case).
        // n=2 means "considering first 2 items" — it looks up dp[1] (which we just computed).
        // ...and so on. Each row n depends only on row n-1.
        //
        // This exactly mirrors the recursion:
        //   f(n, s1, s2) calls f(n-1, ...) → dp[n] depends on dp[n-1]
        for(int n = 1; n <= N; n++){
            for(int s1 = 0; s1 <= target; s1++){
                for(int s2 = 0; s2 <= target; s2++){
                    // Choice 3: put A[n-1] in S3 (don't reduce s1 or s2)
                    bool putInS3 = dp[n-1][s1][s2];

                    // Choice 1: put A[n-1] in S1
                    bool putInS1 = false;
                    if(A[n-1] <= s1)
                        putInS1 = dp[n-1][s1 - A[n-1]][s2];

                    // Choice 2: put A[n-1] in S2
                    bool putInS2 = false;
                    if(A[n-1] <= s2)
                        putInS2 = dp[n-1][s1][s2 - A[n-1]];

                    dp[n][s1][s2] = putInS1 || putInS2 || putInS3;
                }
            }
        }
        return dp[N][target][target];
    }

public:
    bool threeSumPartition(vector<int> A){
        int N = A.size();
        int sum = accumulate(A.begin(), A.end(), 0);

        // If total sum is not divisible by 3, can't split into 3 equal parts
        if(sum % 3 != 0)
            return false;

        int target = sum / 3;

        // Reduce to: can we find two disjoint subsets each summing to target?
        // return threeSumPartitionRecursive(A, N, target, target);

        // unordered_map<string, bool> lookup;
        // return threeSumPartitionTopDown(A, N, target, target, lookup);

        // vector<vector<vector<int>>> memo(N+1, vector<vector<int>>(target+1, vector<int>(target+1, -1)));
        // return threeSumPartitionTopDown2(A, N, target, target, memo);

        return threeSumPartitionBottomUp(A, N, target);
    }
};


int main(){
    Solution obj;

    vector<int> A1 = {3, 3, 3, 3, 3, 3};
    cout << (obj.threeSumPartition(A1) ? "Possible" : "Not Possible") << endl;  // Possible

    vector<int> A2 = {1, 2, 3, 0, 3};
    cout << (obj.threeSumPartition(A2) ? "Possible" : "Not Possible") << endl;  // Possible

    vector<int> A3 = {1, 2, 3, 4, 5, 6, 7};
    cout << (obj.threeSumPartition(A3) ? "Possible" : "Not Possible") << endl;  // Not Possible (28%3!=0)

    vector<int> A4 = {1, 1, 1, 1, 1, 1};
    cout << (obj.threeSumPartition(A4) ? "Possible" : "Not Possible") << endl;  // Possible (sum=6, target=2)

    return 0;
}
