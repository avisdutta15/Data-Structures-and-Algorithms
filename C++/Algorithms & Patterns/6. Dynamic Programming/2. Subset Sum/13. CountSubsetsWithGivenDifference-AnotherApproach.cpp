#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Count Subsets with Given Difference
    ─────────────────────────────────────────────

    Problem Statement:
    ------------------
    Given an array of non-negative integers and a difference d, count the number
    of ways to partition the array into two subsets S1 and S2 such that:
        sum(S1) - sum(S2) = d    (where sum(S1) >= sum(S2))

    Examples:
    ---------
    Input:  A = [1, 1, 2, 3], d = 1
    Output: 3
    Explanation:
        S1={1,3}, S2={1,2}: 4-3=1 ✓
        S1={1,3}, S2={1,2}: 4-3=1 ✓ (different 1 chosen)
        S1={2,3}, S2={1,1}: 5-2=3 ✗... let me recompute.
        totalSum=7, target=(7+1)/2=4.
        Count subsets with sum 4: {1,3}, {1,3}, {2,1,1}? 
        {1,3} using first 1 = ✓
        {1,3} using second 1 = ✓
        {1,1,2} = sum 4 ✓
        Count = 3 ✓

    Input:  A = [1, 2, 3, 1, 2], d = 1
    Output: ?

    ════════════════════════════════════════════════════════════════════════
    KEY INSIGHT: Algebraic Reduction to Count Subset Sum
    ════════════════════════════════════════════════════════════════════════

    Let sum(S1) = s1, sum(S2) = s2.
    Given:
        s1 - s2 = d          ... (1)
        s1 + s2 = totalSum   ... (2)  (every element is in one subset)

    Adding (1) and (2):
        2*s1 = d + totalSum
        s1 = (d + totalSum) / 2

    So the problem reduces to:
        "Count the number of subsets with sum = (d + totalSum) / 2"

    This is exactly "Count Number of Subsets with Given Sum" where
    target = (d + totalSum) / 2.

    Pre-checks:
    - (d + totalSum) must be even (otherwise no integer solution for s1)
    - (d + totalSum) / 2 must be >= 0
    - d must be <= totalSum

    ════════════════════════════════════════════════════════════════════════
    RECURRENCE (Count Subset Sum)
    ════════════════════════════════════════════════════════════════════════

    f(n, s) = number of subsets using first n elements that sum to s

    Base cases:
        f(0, 0) = 1    (empty subset has sum 0 — one way)
        f(0, s) = 0    (no elements, can't form positive sum — zero ways)

    Recurrence:
        if A[n-1] <= s:
            f(n, s) = f(n-1, s - A[n-1])  +  f(n-1, s)
                      (include item n)        (exclude item n)
        else:
            f(n, s) = f(n-1, s)

    Answer: f(N, target) where target = (d + totalSum) / 2

    ════════════════════════════════════════════════════════════════════════
    COMPARISON WITH SUBSET SUM VARIANTS
    ════════════════════════════════════════════════════════════════════════

    Subset Sum (exists?):    || (OR)         → bool
    Count Subset Sum:        + (ADD)         → int
    Max Size Subset Sum:     max() + check   → int

    The structure is identical — just change the combine operator:
        bool, ||    →   int, +

    ════════════════════════════════════════════════════════════════════════
    CONNECTION TO OTHER PROBLEMS
    ════════════════════════════════════════════════════════════════════════

    This same reduction (s1 = (diff + totalSum) / 2) directly solves:
    - LC 494 (Target Sum): assign + or - to each element, count ways to reach target.
      → same as partitioning into S1 (positive) and S2 (negative) with diff = target.
    
    ════════════════════════════════════════════════════════════════════════
*/

class Solution{
    // ── Recursive: O(2^N) ──
    int countSubsetsRecursive(vector<int> &A, int N, int sum){
        if(N == 0 && sum == 0)
            return 1;   // found one valid subset
        if(N == 0 && sum != 0)
            return 0;   // no elements left, can't reach sum

        int include = 0, exclude = 0;
        if(A[N-1] <= sum)
            include = countSubsetsRecursive(A, N-1, sum - A[N-1]);
        exclude = countSubsetsRecursive(A, N-1, sum);

        return include + exclude;
    }

    // ── Top-Down with 2D Memoization: O(N * target) ──
    int countSubsetsTopDown(vector<int> &A, int N, int sum, vector<vector<int>> &memo){
        if(N == 0 && sum == 0)
            return 1;
        if(N == 0 && sum != 0)
            return 0;

        if(memo[N][sum] != -1)
            return memo[N][sum];

        int include = 0, exclude = 0;
        if(A[N-1] <= sum)
            include = countSubsetsTopDown(A, N-1, sum - A[N-1], memo);
        exclude = countSubsetsTopDown(A, N-1, sum, memo);

        memo[N][sum] = include + exclude;
        return memo[N][sum];
    }

    // ── Bottom-Up: O(N * target) ──
    int countSubsetsBottomUp(vector<int> &A, int N, int target){
        vector<vector<int>> dp(N+1, vector<int>(target+1, 0));

        for(int n = 0; n <= N; n++){
            for(int s = 0; s <= target; s++){
                if(n == 0 && s == 0)
                    dp[n][s] = 1;       // one way: empty subset
                else if(n == 0 && s != 0)
                    dp[n][s] = 0;       // zero ways
                else{
                    int include = 0, exclude = 0;
                    if(A[n-1] <= s)
                        include = dp[n-1][s - A[n-1]];  // include item n
                    exclude = dp[n-1][s];                // exclude item n
                    dp[n][s] = include + exclude;
                }
            }
        }
        return dp[N][target];
    }

    // ── Bottom-Up 1D: O(target) space ──
    int countSubsetsBottomUp1D(vector<int> &A, int N, int target){
        vector<int> dp(target+1, 0);
        dp[0] = 1;  // one way to form sum 0: empty subset

        for(int n = 0; n < N; n++){
            // Right to left for 0/1 knapsack (each item used once)
            for(int s = target; s >= A[n]; s--){
                dp[s] = dp[s] + dp[s - A[n]];
            }
        }
        return dp[target];
    }

public:
    int countSubsetsWithGivenDifference(vector<int> A, int d){
        int N = A.size();
        int totalSum = accumulate(A.begin(), A.end(), 0);

        // Pre-check: (d + totalSum) must be even and non-negative
        if((d + totalSum) % 2 != 0)
            return 0;
        if(d > totalSum)
            return 0;

        int target = (d + totalSum) / 2;

        // Reduce to: count subsets with sum = target
        // return countSubsetsRecursive(A, N, target);

        // vector<vector<int>> memo(N+1, vector<int>(target+1, -1));
        // return countSubsetsTopDown(A, N, target, memo);

        // return countSubsetsBottomUp(A, N, target);

        return countSubsetsBottomUp1D(A, N, target);
    }
};


int main(){
    Solution obj;

    vector<int> A1 = {1, 1, 2, 3};
    cout << "Count (d=1): " << obj.countSubsetsWithGivenDifference(A1, 1) << endl;  // 3

    vector<int> A2 = {1, 2, 3};
    cout << "Count (d=0): " << obj.countSubsetsWithGivenDifference(A2, 0) << endl;  // 1 ({1,2} and {3})

    vector<int> A3 = {1, 1, 1, 1};
    cout << "Count (d=0): " << obj.countSubsetsWithGivenDifference(A3, 0) << endl;  // 6 (C(4,2)=6 ways to split into two pairs)

    return 0;
}
