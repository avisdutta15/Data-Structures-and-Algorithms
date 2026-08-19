#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Target Sum (LeetCode 494)
    ────────────────────────────────────

    Problem Statement:
    ------------------
    You are given an integer array nums and an integer target.
    You want to build an expression out of nums by adding one of the symbols
    '+' or '-' before each integer in nums and then concatenate all the integers.

    Return the number of different expressions that evaluate to target.

    Examples:
    ---------
    Input:  nums = [1, 1, 1, 1, 1], target = 3
    Output: 5
    Explanation: 
        -1 +1 +1 +1 +1 = 3
        +1 -1 +1 +1 +1 = 3
        +1 +1 -1 +1 +1 = 3
        +1 +1 +1 -1 +1 = 3
        +1 +1 +1 +1 -1 = 3

    Input:  nums = [1], target = 1
    Output: 1

    Constraints:
    ------------
    - 1 <= nums.length <= 20
    - 0 <= nums[i] <= 1000
    - 0 <= sum(nums[i]) <= 1000
    - -1000 <= target <= 1000

    ════════════════════════════════════════════════════════════════════════
    KEY INSIGHT: This IS "Count Subsets with Given Difference"
    ════════════════════════════════════════════════════════════════════════

    Assigning '+' or '-' to each element partitions the array into:
        S1 = elements with '+' (positive set)
        S2 = elements with '-' (negative set)

    Expression value = sum(S1) - sum(S2) = target

    This is EXACTLY "Count Subsets with Given Difference" where d = target!

    Reduction:
        s1 - s2 = target        ... (1)
        s1 + s2 = totalSum      ... (2)

    Adding (1) and (2):
        2*s1 = target + totalSum
        s1 = (target + totalSum) / 2

    Problem reduces to:
        "Count subsets with sum = (target + totalSum) / 2"

    Pre-checks:
    - (target + totalSum) must be even
    - (target + totalSum) / 2 must be >= 0
    - |target| must be <= totalSum

    ════════════════════════════════════════════════════════════════════════
    APPROACH 1: Direct +/- (current_sum approach)
    ════════════════════════════════════════════════════════════════════════

    f(A, current_sum, N, targetSum) = In how many ways can we reach targetSum
    by assigning + and - signs to N elements, given we've accumulated current_sum so far.

    Keep a running variable current_sum that builds up as we assign signs.

    Base cases:
        if N == 0 && current_sum == targetSum: return 1   (reached target!)
        if N == 0 && current_sum != targetSum: return 0   (failed to reach)

    Recurrence:
        plus  = f(A, current_sum + A[N-1], N-1, targetSum)   ← assign '+' to A[N-1]
        minus = f(A, current_sum - A[N-1], N-1, targetSum)   ← assign '-' to A[N-1]
        return plus + minus

    States for memoization: (N, current_sum)
    Note: current_sum can go negative! Range: [-totalSum, +totalSum].
    For 2D vector memo, use offset: memo[N][current_sum + totalSum].
    Memo dimensions: (N+1) × (2*totalSum + 1).

    Recursion → Memo → Bottom Up

    ════════════════════════════════════════════════════════════════════════
    APPROACH 2: Algebraic Reduction to Count Subset Sum
    ════════════════════════════════════════════════════════════════════════

    Assigning '+' or '-' partitions into S1 (positive) and S2 (negative):
        sum(S1) - sum(S2) = target
        sum(S1) + sum(S2) = totalSum
        → s1 = (target + totalSum) / 2

    Reduces to: "Count subsets with sum = (target + totalSum) / 2"

    f(n, s) = number of subsets using first n elements that sum to s

    Base cases:
        f(0, 0) = 1    (empty subset → one way)
        f(0, s) = 0    (no elements → zero ways for s > 0)

    Recurrence:
        if A[n-1] <= s:
            f(n, s) = f(n-1, s - A[n-1])  +  f(n-1, s)
                      (include: assign '+')    (exclude: assign '-')
        else:
            f(n, s) = f(n-1, s)

    Answer: f(N, (target + totalSum) / 2)

    Pre-checks:
    - (target + totalSum) must be even
    - |target| must be <= totalSum

    ════════════════════════════════════════════════════════════════════════
*/

class Solution{

    // ══════════════════════════════════════════════════════════════════════
    // APPROACH 1: Direct +/- with current_sum
    // ══════════════════════════════════════════════════════════════════════

    // ── Recursive: O(2^N) ──
    // f(A, current_sum, N, targetSum): count ways to reach targetSum
    int approach1Recursive(vector<int> &A, int currentSum, int N, int targetSum){
        // Base case: all elements processed
        if(N == 0 && currentSum == targetSum)
            return 1;   // reached target!
        if(N == 0 && currentSum != targetSum)
            return 0;   // failed

        // Assign '+' to A[N-1]
        int plus = approach1Recursive(A, currentSum + A[N-1], N-1, targetSum);
        // Assign '-' to A[N-1]
        int minus = approach1Recursive(A, currentSum - A[N-1], N-1, targetSum);

        return plus + minus;
    }

    // ── Top-Down with 2D Memoization: O(N * 2*totalSum) ──
    // States: (N, currentSum). currentSum ranges from -totalSum to +totalSum.
    // Use offset: memo[N][currentSum + totalSum] to handle negatives.
    int approach1TopDown(vector<int> &A, int currentSum, int N, int targetSum,
                         int totalSum, vector<vector<int>> &memo){
        if(N == 0 && currentSum == targetSum)
            return 1;
        if(N == 0)
            return 0;

        // Offset to make index non-negative
        int offset = currentSum + totalSum;
        if(memo[N][offset] != -1)
            return memo[N][offset];

        int plus = approach1TopDown(A, currentSum + A[N-1], N-1, targetSum, totalSum, memo);
        int minus = approach1TopDown(A, currentSum - A[N-1], N-1, targetSum, totalSum, memo);

        memo[N][offset] = plus + minus;
        return memo[N][offset];
    }

    // ── Bottom-Up: O(N * 2*totalSum) ──
    // dp[n][s] = number of ways to reach sum s using first n elements
    // s is offset by totalSum: actual sum = s - totalSum
    // Range of s: [0, 2*totalSum] representing actual sums [-totalSum, +totalSum]
    int approach1BottomUp(vector<int> &A, int N, int targetSum, int totalSum){
        int offset = totalSum;  // shift all sums by totalSum to make non-negative
        int range = 2 * totalSum + 1;  // total possible sum values

        vector<vector<int>> dp(N+1, vector<int>(range, 0));

        // Base case: with 0 elements, currentSum = 0 (index = 0 + offset = totalSum)
        dp[0][0 + offset] = 1;

        for(int n = 1; n <= N; n++){
            for(int s = 0; s < range; s++){
                // s represents actual sum = s - offset
                // If we assigned '+' to A[n-1], previous sum was s - A[n-1]
                if(s - A[n-1] >= 0 && dp[n-1][s - A[n-1]] > 0)
                    dp[n][s] += dp[n-1][s - A[n-1]];
                // If we assigned '-' to A[n-1], previous sum was s + A[n-1]
                if(s + A[n-1] < range && dp[n-1][s + A[n-1]] > 0)
                    dp[n][s] += dp[n-1][s + A[n-1]];
            }
        }

        // Answer: number of ways to reach targetSum (at index targetSum + offset)
        return dp[N][targetSum + offset];
    }

    // ══════════════════════════════════════════════════════════════════════
    // APPROACH 2: Algebraic reduction to Count Subset Sum
    // ══════════════════════════════════════════════════════════════════════

    // ── Recursive (direct +/- approach): O(2^N) ──
    int findTargetSumWaysRecursive(vector<int> &A, int N, int target){
        // All elements assigned, check if target reached
        if(N == 0 && target == 0)
            return 1;
        if(N == 0)
            return 0;

        // Assign '+' to A[N-1]: reduce target
        int positive = findTargetSumWaysRecursive(A, N-1, target - A[N-1]);
        // Assign '-' to A[N-1]: increase target
        int negative = findTargetSumWaysRecursive(A, N-1, target + A[N-1]);

        return positive + negative;
    }

    // ── Top-Down with 2D Memoization (subset sum reduction): O(N * target) ──
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
                        include = dp[n-1][s - A[n-1]];
                    exclude = dp[n-1][s];
                    dp[n][s] = include + exclude;
                }
            }
        }
        return dp[N][target];
    }

    // ── Bottom-Up 1D: O(target) space ──
    int countSubsetsBottomUp1D(vector<int> &A, int N, int target){
        vector<int> dp(target+1, 0);
        dp[0] = 1;

        for(int n = 0; n < N; n++){
            for(int s = target; s >= A[n]; s--){
                dp[s] = dp[s] + dp[s - A[n]];
            }
        }
        return dp[target];
    }

public:
    int findTargetSumWays(vector<int> A, int target){
        int N = A.size();
        int totalSum = accumulate(A.begin(), A.end(), 0);

        // ── Approach 1: Direct +/- with current_sum ──
        // return approach1Recursive(A, 0, N, target);

        // vector<vector<int>> memo(N+1, vector<int>(2*totalSum+1, -1));
        // return approach1TopDown(A, 0, N, target, totalSum, memo);

        // return approach1BottomUp(A, N, target, totalSum);

        // ── Approach 2: Algebraic reduction to count subset sum ──
        // Assigning '+' or '-' partitions into S1 (positive) and S2 (negative):
        // sum(S1) - sum(S2) = target
        // sum(S1) + sum(S2) = totalSum
        // → s1 = (target + totalSum) / 2
        // Pre-checks
        if(abs(target) > totalSum)
            return 0;
        if((target + totalSum) % 2 != 0)
            return 0;

        int s1 = (target + totalSum) / 2;

        // return countSubsetsRecursive(A, N, s1);  // direct approach

        // vector<vector<int>> memo(N+1, vector<int>(s1+1, -1));
        // return countSubsetsTopDown(A, N, s1, memo);

        // return countSubsetsBottomUp(A, N, s1);

        return countSubsetsBottomUp1D(A, N, s1);
    }
};


int main(){
    Solution obj;

    vector<int> A1 = {1, 1, 1, 1, 1};
    cout << "Ways (target=3): " << obj.findTargetSumWays(A1, 3) << endl;  // 5

    vector<int> A2 = {1};
    cout << "Ways (target=1): " << obj.findTargetSumWays(A2, 1) << endl;  // 1

    vector<int> A3 = {1, 2, 3};
    cout << "Ways (target=0): " << obj.findTargetSumWays(A3, 0) << endl;  // 1 ({+1,+2,-3} or {-1,-2,+3})... 
    // Actually: +1-2+3=2≠0, -1+2+3=4≠0, +1+2-3=0 ✓, -1-2+3=0 ✓ → 2

    vector<int> A4 = {0, 0, 0, 0, 0};
    cout << "Ways (target=0): " << obj.findTargetSumWays(A4, 0) << endl;  // 32 (2^5, every +/- combo works)

    return 0;
}
