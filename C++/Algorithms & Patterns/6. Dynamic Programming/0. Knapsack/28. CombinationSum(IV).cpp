#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Combination Sum IV (LeetCode 377)
    ────────────────────────────────────────────

    Problem Statement:
    ------------------
    Given an array of distinct integers nums and a target integer target, return
    the number of possible combinations that add up to target.

    Note: Different ORDERINGS of the same set of numbers count as different
    combinations (so this is actually counting PERMUTATIONS, not combinations).

    Examples:
    ---------
    Input:  nums = [1, 2, 3], target = 4
    Output: 7
    Explanation:
        (1,1,1,1)
        (1,1,2)
        (1,2,1)
        (1,3)
        (2,1,1)
        (2,2)
        (3,1)
        Note: (1,2,1) and (2,1,1) and (1,1,2) are ALL counted separately!

    Input:  nums = [9], target = 3
    Output: 0

    Constraints:
    ------------
    - 1 <= nums.length <= 200
    - 1 <= nums[i] <= 1000
    - All elements of nums are unique.
    - 1 <= target <= 1000

    ════════════════════════════════════════════════════════════════════════
    KEY DIFFERENCE: PERMUTATIONS vs COMBINATIONS
    ════════════════════════════════════════════════════════════════════════

    Coin Change 2 (LC 518): ORDER DOESN'T MATTER (combinations)
        [1,2] and [2,1] are the SAME → count once.
        1D: outer loop = coins, inner loop = amount

    Combination Sum IV (LC 377): ORDER MATTERS (permutations)
        [1,2] and [2,1] are DIFFERENT → count both.
        1D: outer loop = amount, inner loop = coins

    Why the loop order matters:
    ───────────────────────────
    Combinations (LC 518):
        for each coin:           ← process coin 1 fully, then coin 2, then coin 3...
            for amt = coin to target:
                dp[amt] += dp[amt - coin]
        → Once we're past coin 1, we never "go back" to using coin 1 before coin 2.
        → Guarantees [1,2] is counted but [2,1] is not (coin 1 is always before coin 2).

        Code:
            vector<int> dp(target+1, 0);
            dp[0] = 1;
            for(int n = 0; n < N; n++)                  // outer: coins
                for(int amt = coins[n]; amt <= target; amt++)  // inner: amount
                    dp[amt] += dp[amt - coins[n]];

    Permutations (LC 377):
        for amt = 1 to target:   ← for each amount, try ALL coins
            for each coin:
                dp[amt] += dp[amt - coin]
        → At each amount, we consider all coins as the "last coin added".
        → dp[3] includes: {..., 1} and {..., 2} and {..., 3} — all orderings.
        → [1,2] counted at dp[3] via coin=2 (dp[1] already has path using coin 1).
        → [2,1] counted at dp[3] via coin=1 (dp[2] already has path using coin 2).

        Code:
            vector<int> dp(target+1, 0);
            dp[0] = 1;
            for(int amt = 1; amt <= target; amt++)      // outer: amount
                for(int n = 0; n < N; n++)              // inner: coins
                    if(coins[n] <= amt)
                        dp[amt] += dp[amt - coins[n]];

    ════════════════════════════════════════════════════════════════════════
    APPROACH 1: "What was the last coin?" (1D recurrence)
    ════════════════════════════════════════════════════════════════════════

    This is the CORRECT approach for permutations.
    Instead of deciding per-coin (take/skip), we ask:
    "What could the LAST coin in the sequence be?"

    f(target) = number of ordered sequences from nums that sum to target

    Base case:
        f(0) = 1    (one way to reach 0: empty sequence)

    Recurrence:
        f(target) = Σ f(target - nums[i])   for all nums[i] <= target
                    i=0 to N-1

    At each step, the LAST element in the sequence can be ANY coin.
    This naturally counts all orderings.

    This is similar to take / not-take just that not-take is done by for loop.

    Answer: f(target)

    Note: This is 1D — only one changing parameter (remaining target).
    Unlike knapsack which has 2 parameters (items, capacity).

    ════════════════════════════════════════════════════════════════════════
    WHY NO 'n' PARAMETER?
    ════════════════════════════════════════════════════════════════════════

    In combinations (LC 518):
        f(n, amount) — we track which coins are "available" to avoid reordering.
        Once we move past coin n, we can't go back → prevents [2,1] after counting [1,2].

    In permutations (LC 377):
        f(target) — ALL coins are always available at every step.
        No need to track "which coins we've processed" because order matters.
        Every position in the sequence independently chooses from all coins.

    ════════════════════════════════════════════════════════════════════════
*/

class Solution{
    
    // ══════════════════════════════════════════════════════════════════════
    // APPROACH 2: "What was the last coin?" (gives PERMUTATIONS — correct)
    // ══════════════════════════════════════════════════════════════════════

    // ── Recursive ──
    // Time: O(N^target) worst case — at each level, N branches
    // Space: O(target) recursion stack
    //
    // Example: nums = [1, 2], target = 3
    //
    //                    f(3)
    //                 /        \
    //         f(3-1)=f(2)     f(3-2)=f(1)
    //          /     \            /     \
    //     f(2-1)  f(2-2)    f(1-1)   f(1-2)
    //      =f(1)   =f(0)    =f(0)     ✗ (2>1)
    //     /    \     =1       =1
    //   f(0)  f(1-2)
    //    =1     ✗
    //
    // f(0) = 1 (base case)
    // f(1) = f(1-1) + f(1-2) = f(0) + ✗ = 1
    //        (only coin 1 fits: sequence [1])
    // f(2) = f(2-1) + f(2-2) = f(1) + f(0) = 1 + 1 = 2
    //        (last coin=1: [?,1] → f(1)=1 way: [1,1])
    //        (last coin=2: [?,2] → f(0)=1 way: [2])
    //        sequences: [1,1], [2]
    // f(3) = f(3-1) + f(3-2) = f(2) + f(1) = 2 + 1 = 3
    //        (last coin=1: [?,1] → f(2)=2 ways: [1,1,1], [2,1])
    //        (last coin=2: [?,2] → f(1)=1 way:  [1,2])
    //        sequences: [1,1,1], [2,1], [1,2]  → 3 ✓
    //
    int combinationSum4Recursive(vector<int> &nums, int target){
        // One way to reach 0: empty sequence
        if(target == 0)
            return 1;

        int totalWays = 0;

        // Try every number as the LAST element added
        for(int i = 0; i < (int)nums.size(); i++){
            if(nums[i] <= target)
                totalWays += combinationSum4Recursive(nums, target - nums[i]);
        }

        return totalWays;
    }

    // ── Top-Down with 1D Memoization ──
    // Time: O(N * target) — target unique states, each tries N coins
    // Space: O(target) for memo + recursion stack
    int combinationSum4TopDown(vector<int> &nums, int target, vector<int> &memo){
        if(target == 0)
            return 1;

        if(memo[target] != -1)
            return memo[target];

        int totalWays = 0;

        for(int i = 0; i < (int)nums.size(); i++){
            if(nums[i] <= target)
                totalWays += combinationSum4TopDown(nums, target - nums[i], memo);
        }

        memo[target] = totalWays;
        return memo[target];
    }

    // ── Bottom-Up 1D ──
    // Time: O(N * target)
    // Space: O(target)
    // Outer loop = amount, inner loop = coins → PERMUTATIONS
    int combinationSum4BottomUp(vector<int> &nums, int target){
        vector<unsigned int> dp(target+1, 0);
        dp[0] = 1;  // one way to make 0

        // Outer loop: amount (1 to target)
        for(int amt = 1; amt <= target; amt++){
            // Inner loop: try ALL coins at each amount
            for(int i = 0; i < (int)nums.size(); i++){
                if(nums[i] <= amt)
                    dp[amt] += dp[amt - nums[i]];
            }
        }
        return dp[target];
    }

public:
    int combinationSum4(vector<int> nums, int target){
        int N = nums.size();

        // return combinationSum4Recursive(nums, target);

        // vector<int> memo(target+1, -1);
        // return combinationSum4TopDown(nums, target, memo);

        return combinationSum4BottomUp(nums, target);
    }
};


int main(){
    Solution obj;

    vector<int> nums1 = {1, 2, 3};
    cout << "Permutations (target=4): " << obj.combinationSum4(nums1, 4) << endl;  // 7

    vector<int> nums2 = {9};
    cout << "Permutations (target=3): " << obj.combinationSum4(nums2, 3) << endl;  // 0

    vector<int> nums3 = {1, 2};
    cout << "Permutations (target=3): " << obj.combinationSum4(nums3, 3) << endl;  // 3 (1+1+1, 1+2, 2+1)

    return 0;
}
