#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Last Stone Weight II (LeetCode 1049)
    ──────────────────────────────────────────────

    Problem Statement:
    ------------------
    You are given an array of integers stones where stones[i] is the weight of
    the ith stone. We are playing a game with the stones. On each turn, we choose
    any two stones and smash them. Suppose the stones have weights x and y with
    x <= y. The result of this smash is:
        - If x == y, both stones are destroyed.
        - If x != y, the stone of weight x is destroyed, and the stone of weight y
          has new weight y - x.

    At the end of the game, there is at most one stone left.
    Return the smallest possible weight of the left stone. If no stones are left, return 0.

    Examples:
    ---------
    Example 1:
    
    Input: stones = [2,7,4,1,8,1]
    Output: 1
    Explanation:
    We can combine 2 and 4 to get 2, so the array converts to [2,7,1,8,1] then,
    we can combine 7 and 8 to get 1, so the array converts to [2,1,1,1] then,
    we can combine 2 and 1 to get 1, so the array converts to [1,1,1] then,
    we can combine 1 and 1 to get 0, so the array converts to [1], then that's the optimal value.
    
    Example 2:

    Input: stones = [31,26,33,21,40]
    Output: 5

    Constraints:
    ------------
    - 1 <= stones.length <= 30
    - 1 <= stones[i] <= 100

    ════════════════════════════════════════════════════════════════════════
    KEY INSIGHT: This IS Minimum Subset Sum Difference
    ════════════════════════════════════════════════════════════════════════

    When we smash two stones (x, y), we get |y - x|.
    If we think about the entire sequence of smashes, the final result is:
        Assign '+' or '-' to each stone, and minimize |total|.

    Why? Every smash operation subtracts one stone from another. The final
    result is some combination of stones with + and - signs:
        ±stones[0] ± stones[1] ± ... ± stones[n-1]

    We want to minimize the absolute value of this expression.

    This is EXACTLY partitioning into two groups S1 (+) and S2 (-) and
    minimizing |sum(S1) - sum(S2)| = Minimum Subset Sum Difference!

    Example: stones = [2, 7, 4, 1, 8, 1], totalSum = 23
        Optimal partition: S1={7, 4, 1} = 12, S2={2, 8, 1} = 11
        Difference = |12 - 11| = 1 ✓

    ════════════════════════════════════════════════════════════════════════
    APPROACH (same as Minimum Subset Sum Difference)
    ════════════════════════════════════════════════════════════════════════

    Derivation of totalSum - 2*s:
    ─────────────────────────────

    Partition array into S1 and S2.
    Let sum(S1) = s, then sum(S2) = totalSum - s.

    We want S1 to be the smaller subset (s <= totalSum/2).
    Difference = sum(S2) - sum(S1)
               = (totalSum - s) - s
               = totalSum - 2*s

    To minimize the difference:
        Minimize (totalSum - 2*s)
        Since totalSum is fixed, we need to MAXIMIZE s.
        But s must be achievable by some subset AND s <= totalSum/2.

    So: find the LARGEST s <= totalSum/2 that is achievable.
    Answer = totalSum - 2*s.

    Example: stones = [2, 7, 4, 1, 8, 1], totalSum = 23, target = 11
        Achievable sums <= 11: {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}
        Largest achievable: s = 11 (subset {7, 4} or {2, 8, 1} etc.)
        Answer = 23 - 2*11 = 1 ✓

    1. Find the largest achievable subset sum s <= totalSum/2.
    2. Answer = totalSum - 2*s.

    Use subset sum DP with target = totalSum/2.
    Scan for largest s where dp[N][s] == true.

    Recurrence (standard subset sum):
        f(n, s) = f(n-1, s - A[n-1]) || f(n-1, s)

    Answer: totalSum - 2 * (largest achievable sum <= totalSum/2)

    Time: O(N * totalSum/2)
    Space: O(totalSum/2) with 1D optimization

    ════════════════════════════════════════════════════════════════════════
*/

class Solution{
    // ── Recursive: O(2^N) ──
    // Directly try assigning + or - to each stone, track minimum result
    void findMinResult(vector<int> &A, int N, int currentSum, int &minResult){
        if(N == 0){
            minResult = min(minResult, abs(currentSum));
            return;
        }
        // Assign '+' to A[N-1]
        findMinResult(A, N-1, currentSum + A[N-1], minResult);
        // Assign '-' to A[N-1]
        findMinResult(A, N-1, currentSum - A[N-1], minResult);
    }

    // ── Top-Down 2D Memoization: O(N * totalSum/2) ──
    // Subset sum memo to check if sum s is achievable
    bool subsetSumMemo(vector<int> &A, int N, int sum, vector<vector<int>> &memo){
        if(N == 0 && sum == 0) return true;
        if(N == 0) return false;

        if(memo[N][sum] != -1) return memo[N][sum];

        bool include = false, exclude = false;
        if(A[N-1] <= sum)
            include = subsetSumMemo(A, N-1, sum - A[N-1], memo);
        exclude = subsetSumMemo(A, N-1, sum, memo);

        memo[N][sum] = (include || exclude) ? 1 : 0;
        return memo[N][sum];
    }

    int minDiffTopDown(vector<int> &A, int N, int totalSum){
        int target = totalSum / 2;
        vector<vector<int>> memo(N+1, vector<int>(target+1, -1));

        // Find largest achievable sum <= totalSum/2
        for(int s = target; s >= 0; s--){
            if(subsetSumMemo(A, N, s, memo))
                return totalSum - 2 * s;
        }
        return totalSum;
    }

    // ── Bottom-Up 2D: O(N * totalSum/2) ──
    int minDiffBottomUp(vector<int> &A, int N, int totalSum){
        int target = totalSum / 2;
        vector<vector<bool>> dp(N+1, vector<bool>(target+1, false));

        for(int n = 0; n <= N; n++){
            for(int s = 0; s <= target; s++){
                if(n == 0 && s == 0)
                    dp[n][s] = true;
                else if(n == 0 && s != 0)
                    dp[n][s] = false;
                else{
                    bool include = false, exclude = false;
                    if(A[n-1] <= s)
                        include = dp[n-1][s - A[n-1]];
                    exclude = dp[n-1][s];
                    dp[n][s] = include || exclude;
                }
            }
        }

        // Find largest achievable sum <= totalSum/2
        for(int s = target; s >= 0; s--){
            if(dp[N][s])
                return totalSum - 2 * s;
        }
        return totalSum;
    }

    // ── Bottom-Up 1D: O(totalSum/2) space ──
    int minDiffBottomUp1D(vector<int> &A, int N, int totalSum){
        int target = totalSum / 2;
        vector<bool> dp(target+1, false);
        dp[0] = true;

        // 0/1 knapsack — right to left
        for(int n = 0; n < N; n++){
            for(int s = target; s >= A[n]; s--){
                dp[s] = dp[s] || dp[s - A[n]];
            }
        }

        // Find largest achievable sum <= totalSum/2
        for(int s = target; s >= 0; s--){
            if(dp[s])
                return totalSum - 2 * s;
        }
        return totalSum;
    }

public:
    int lastStoneWeightII(vector<int> A){
        int N = A.size();
        int totalSum = accumulate(A.begin(), A.end(), 0);

        // Approach 1: Recursive (for understanding)
        // int minResult = INT_MAX;
        // findMinResult(A, N, 0, minResult);
        // return minResult;

        // Approach 2: Top-Down 2D
        // return minDiffTopDown(A, N, totalSum);

        // Approach 3: Bottom-Up 2D
        // return minDiffBottomUp(A, N, totalSum);

        // Approach 4: Bottom-Up 1D
        return minDiffBottomUp1D(A, N, totalSum);
    }
};


int main(){
    Solution obj;

    vector<int> A1 = {2, 7, 4, 1, 8, 1};
    cout << "Last stone weight: " << obj.lastStoneWeightII(A1) << endl;  // 1

    vector<int> A2 = {31, 26, 33, 21, 40};
    cout << "Last stone weight: " << obj.lastStoneWeightII(A2) << endl;  // 5

    vector<int> A3 = {1, 2};
    cout << "Last stone weight: " << obj.lastStoneWeightII(A3) << endl;  // 1

    return 0;
}
