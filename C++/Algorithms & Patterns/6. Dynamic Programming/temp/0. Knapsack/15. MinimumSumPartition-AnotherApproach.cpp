#include <bits/stdc++.h>
using namespace std;

/*
    https://www.youtube.com/watch?v=tCoxxtYG2k8
    
    Problem: Minimum Subset Sum Difference
    ───────────────────────────────────────

    Problem Statement:
    ------------------
    Given an array of non-negative integers, partition it into two subsets S1 and S2
    such that the absolute difference of their sums is MINIMIZED.

    Return the minimum possible |sum(S1) - sum(S2)|.

    Examples:
    ---------
    Input:  A = [1, 6, 11, 5]
    Output: 1
    Explanation: S1={1, 5, 6}=12, S2={11}=11. |12-11|=1.

    Input:  A = [1, 2, 3, 4]
    Output: 0
    Explanation: S1={1, 4}=5, S2={2, 3}=5. |5-5|=0.

    Input:  A = [1, 2, 7]
    Output: 4
    Explanation: S1={1, 2}=3, S2={7}=7. |3-7|=4.

    ════════════════════════════════════════════════════════════════════════
    KEY INSIGHT: Reduce to Subset Sum
    ════════════════════════════════════════════════════════════════════════

    Let totalSum = sum of all elements.
    If S1 has sum = s, then S2 has sum = totalSum - s.
    Difference = |s - (totalSum - s)| = |2s - totalSum|.

    To MINIMIZE the difference:
        Minimize |2s - totalSum|
        Which means: find s as CLOSE to totalSum/2 as possible.

    So the problem becomes:
        "What is the largest sum s <= totalSum/2 that can be formed using a subset?"

    This is subset sum where we find the maximum achievable sum up to totalSum/2.

    Answer = totalSum - 2 * s  (where s is the largest achievable sum <= totalSum/2)

    Why totalSum - 2*s?
        If S1 has sum s, S2 has sum (totalSum - s).
        Difference = (totalSum - s) - s = totalSum - 2s.
        (Since s <= totalSum/2, S2 >= S1, so difference is non-negative.)

    ════════════════════════════════════════════════════════════════════════
    APPROACH
    ════════════════════════════════════════════════════════════════════════

    1. Run standard subset sum DP with target = totalSum/2.
       dp[n][w] = can we form sum w using first n elements?

    2. After building the table, scan the last row dp[N][0..totalSum/2]
       to find the LARGEST w where dp[N][w] == true.

    3. Answer = totalSum - 2 * w.

    Alternatively, use the subset sum table to collect all achievable sums
    in the last row and pick the one closest to totalSum/2.

    ════════════════════════════════════════════════════════════════════════
    RECURRENCE (same as Subset Sum)
    ════════════════════════════════════════════════════════════════════════

    f(n, s) = can we form sum s using first n elements?

    Base cases:
        f(0, 0) = true
        f(0, s) = false   for s > 0

    Recurrence:
        if A[n-1] <= s:
            f(n, s) = f(n-1, s - A[n-1]) || f(n-1, s)
        else:
            f(n, s) = f(n-1, s)

    After filling, find max s in [0, totalSum/2] where f(N, s) == true.
    Answer = totalSum - 2 * s.

    Worked Example:
    ───────────────
    A = [1, 6, 11, 5], totalSum = 23, target = totalSum/2 = 11

    Build subset sum DP for target = 11:
    Achievable sums using all 4 elements: {0, 1, 5, 6, 7, 11, 12, 16, 17, 22, 23}
    Largest achievable sum <= 11: s = 11.

    Answer = 23 - 2*11 = 1 ✓ (S1={11}=11, S2={1,6,5}=12, diff=1)

    Time Complexity: O(N * totalSum/2)
    Space Complexity: O(N * totalSum/2) for 2D, O(totalSum/2) for 1D

    ════════════════════════════════════════════════════════════════════════
*/

class Solution{
    // ── Recursive: O(2^N) ──
    // Find all achievable sums, pick the one closest to totalSum/2
    void findAchievableSums(vector<int> &A, int N, int currentSum, int target, int &bestSum){
        // Only consider sums <= target (= totalSum/2)
        if(currentSum <= target)
            bestSum = max(bestSum, currentSum);

        if(N == 0 || currentSum > target)
            return;

        // Include A[N-1]
        findAchievableSums(A, N-1, currentSum + A[N-1], target, bestSum);
        // Exclude A[N-1]
        findAchievableSums(A, N-1, currentSum, target, bestSum);
    }

    // ── Top-Down with 2D Memoization: O(N * totalSum/2) ──
    // States: (N, currentSum) — N items remaining, currentSum accumulated so far
    // memo[n][s] = can we achieve a subset sum of exactly s using first n elements?
    // We fill the memo, then scan for the largest achievable sum <= target.
    bool subsetSumMemo(vector<int> &A, int N, int sum, vector<vector<int>> &memo){
        if(N == 0 && sum == 0)
            return true;
        if(N == 0 && sum != 0)
            return false;

        if(memo[N][sum] != -1)
            return memo[N][sum];

        bool include = false, exclude = false;
        if(A[N-1] <= sum)
            include = subsetSumMemo(A, N-1, sum - A[N-1], memo);
        exclude = subsetSumMemo(A, N-1, sum, memo);

        memo[N][sum] = (include || exclude) ? 1 : 0;
        return memo[N][sum];
    }

    int minDiffTopDown(vector<int> &A, int N, int totalSum){
        int target = totalSum / 2;
        // memo[n][s]: -1 = not computed, 0 = false, 1 = true
        vector<vector<int>> memo(N+1, vector<int>(target+1, -1));

        // Check all possible sums from target down to 0
        // The first one that returns true is the largest achievable sum
        for(int s = target; s >= 0; s--){
            if(subsetSumMemo(A, N, s, memo))
                return totalSum - 2 * s;
        }
        return totalSum;  // worst case: one subset is empty
    }

    // ── Bottom-Up: O(N * totalSum/2) ──
    // Standard subset sum DP, then scan last row for largest achievable sum
    int minDiffBottomUp(vector<int> &A, int N, int totalSum){
        int target = totalSum / 2;
        vector<vector<bool>> dp(N+1, vector<bool>(target+1, false));

        // Fill DP table (standard subset sum with base cases inside)
        for(int n = 0; n <= N; n++){
            for(int s = 0; s <= target; s++){
                // Base case: empty subset has sum 0
                if(n == 0 && s == 0)
                    dp[n][s] = true;
                else if(n == 0 && s != 0)
                    dp[n][s] = false;
                else{
                    bool include = false, exclude = false;
                    if(A[n-1] <= s)
                        include = dp[n-1][s - A[n-1]];  // include item n
                    exclude = dp[n-1][s];                // exclude item n
                    dp[n][s] = include || exclude;
                }
            }
        }

        // Find the largest achievable sum <= totalSum/2
        int bestSum = 0;
        for(int s = target; s >= 0; s--){
            if(dp[N][s]){
                bestSum = s;
                break;
            }
        }

        // S1 = bestSum, S2 = totalSum - bestSum
        // Difference = (totalSum - bestSum) - bestSum = totalSum - 2*bestSum
        return totalSum - 2 * bestSum;
    }

    // ── Bottom-Up 1D: O(totalSum/2) space ──
    int minDiffBottomUp1D(vector<int> &A, int N, int totalSum){
        int target = totalSum / 2;
        vector<bool> dp(target+1, false);
        dp[0] = true;  // empty subset has sum 0

        // 0/1 knapsack style — iterate right to left
        for(int n = 0; n < N; n++){
            for(int s = target; s >= A[n]; s--){
                dp[s] = dp[s] || dp[s - A[n]];
            }
        }

        // Find largest achievable sum <= totalSum/2
        int bestSum = 0;
        for(int s = target; s >= 0; s--){
            if(dp[s]){
                bestSum = s;
                break;
            }
        }

        return totalSum - 2 * bestSum;
    }

public:
    int minimumSubsetSumDifference(vector<int> A){
        int N = A.size();
        int totalSum = accumulate(A.begin(), A.end(), 0);

        // Approach 1: Recursive (for understanding)
        // int bestSum = 0;
        // findAchievableSums(A, N, 0, totalSum/2, bestSum);
        // return totalSum - 2 * bestSum;

        // Approach 2: Top-Down 2D Memoization
        // return minDiffTopDown(A, N, totalSum);

        // Approach 3: Bottom-Up 2D
        // return minDiffBottomUp(A, N, totalSum);

        // Approach 4: Bottom-Up 1D (space optimized)
        return minDiffBottomUp1D(A, N, totalSum);
    }
};


int main(){
    Solution obj;

    vector<int> A1 = {1, 6, 11, 5};
    cout << "Min diff: " << obj.minimumSubsetSumDifference(A1) << endl;  // 1

    vector<int> A2 = {1, 2, 3, 4};
    cout << "Min diff: " << obj.minimumSubsetSumDifference(A2) << endl;  // 0

    vector<int> A3 = {1, 2, 7};
    cout << "Min diff: " << obj.minimumSubsetSumDifference(A3) << endl;  // 4

    return 0;
}
