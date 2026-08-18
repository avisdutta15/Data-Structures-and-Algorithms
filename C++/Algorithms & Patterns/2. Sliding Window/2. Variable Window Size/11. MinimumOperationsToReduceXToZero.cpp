#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// ──────────────────────────────────────────────────────────────────────────────
// Problem: Minimum Operations to Reduce X to Zero (LeetCode 1658)
// ──────────────────────────────────────────────────────────────────────────────

/*
    https://www.youtube.com/watch?v=w7u9sMlx7zc  [Recursion Logic]
    Problem Statement:
    ------------------
    You are given an integer array nums and an integer x. In one operation, you
    can either remove the leftmost or the rightmost element from the array and
    subtract its value from x.

    Return the MINIMUM number of operations to reduce x to exactly 0.
    If it's not possible, return -1.

    Examples:
    ---------
    Input:  nums = [1, 1, 4, 2, 3], x = 5
    Output: 2
    Explanation: Remove rightmost 3, then rightmost 2: 5 - 3 - 2 = 0. (2 ops)

    Input:  nums = [5, 6, 7, 8, 9], x = 4
    Output: -1

    Input:  nums = [3, 2, 20, 1, 1, 3], x = 10
    Output: 5
    Explanation: Remove 3,2 from left and 1,1,3 from right: 3+2+1+1+3 = 10.

    Constraints:
    ------------
    - 1 <= nums.length <= 10^5
    - 1 <= nums[i] <= 10^4
    - 1 <= x <= 10^9

    ═══════════════════════════════════════════════════════════════════════
    Approach 1: Naive Recursive (Take i or Take j) — O(2^n) time
    ═══════════════════════════════════════════════════════════════════════

    At each step, we have two choices:
    - Take from the left (i++)
    - Take from the right (j--)

    We use a void function with a global minCount tracker instead of returning values.

    Base cases:
    - If remain == 0: found a valid answer, update minCount = min(minCount, count).
    - If remain < 0 or i > j or count >= minCount: prune this path, return.

    Recurrence:
        solve(nums, remain, count, i, j):
            if remain == 0 → update minCount
            if remain < 0 or i > j or count >= minCount → prune
            else:
                solve(nums, remain - nums[i], count + 1, i + 1, j)   // take left
                solve(nums, remain - nums[j], count + 1, i, j - 1)   // take right

    The `count >= minCount` check is a pruning optimization: if we've already
    used as many or more operations than the best answer, no point continuing.

    This explores all 2^n combinations — way too slow, but shows the logic.

    ═══════════════════════════════════════════════════════════════════════
    Approach 2: Reverse Thinking + Sliding Window — O(N) time
    ═══════════════════════════════════════════════════════════════════════

    Same insight as LC 2516:
    - Taking from left + right = removing a prefix + suffix.
    - What's left in the middle is a contiguous subarray.
    - If prefix + suffix sum = x, then middle sum = totalSum - x.

    Reversed problem:
        Find the LONGEST subarray with sum == (totalSum - x).
        Answer = n - length of that subarray.

    If totalSum - x < 0: impossible.
    If no such subarray exists: impossible.

    This is "find longest subarray with exact sum = target" where all elements
    are positive → sliding window works (expand increases sum, shrink decreases).

    Worked Example:
    ---------------
    nums = [1, 1, 4, 2, 3], x = 5
    totalSum = 11. target = 11 - 5 = 6.

    Find longest subarray with sum == 6:

    left=0, right=0: sum=1. sum < 6.
    left=0, right=1: sum=2. sum < 6.
    left=0, right=2: sum=6. sum == 6! window length = 3. maxLen = 3.
    left=0, right=3: sum=8. sum > 6. Shrink: sum-=1, left=1. sum=7. Still > 6.
                     Shrink: sum-=1, left=2. sum=6. sum == 6! window length = 2.
                     maxLen stays 3.
    left=2, right=4: sum=9. sum > 6. Shrink: sum-=4, left=3. sum=5. sum < 6.

    Longest subarray with sum 6 has length 3 (indices 0..2 = [1,1,4]).
    Answer = 5 - 3 = 2 ✓ (remove 2 elements from the right: [2, 3])

    Time Complexity: O(N)
    Space Complexity: O(1)
*/

// ── Approach 1: Naive Recursive ──
class SolutionNaive {
private:
    int minCount;
public:
    void solve(vector<int>& nums, int x, int count, int i, int j) {
        if (x == 0) {
            minCount = min(minCount, count);
            return;
        }

        // Base Case: Out of Bounds
        if (i > j)
            return;
        
        // if remaining x is < 0
        if (x < 0)
            return;

        // pruning
        if (count >= minCount)
            return;
        
        solve(nums, x - nums[i], count + 1, i + 1, j);
        solve(nums, x - nums[j], count + 1, i, j - 1);
    }
    
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();
        minCount = INT_MAX;

        solve(nums, x, 0, 0, n-1);
        
        if (minCount == INT_MAX) 
            return -1;
        
        return minCount;
    }
};

// ── Approach 2: Reverse Thinking + Sliding Window ──
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();

        // Calculate target sum for the middle subarray
        int totalSum = 0;
        for (int num : nums)
            totalSum += num;

        int target = totalSum - x;

        // Edge case: need to take all elements
        if (target == 0) 
            return n;

        // Impossible: target is negative (x > totalSum)
        if (target < 0) 
            return -1;

        // Find the LONGEST subarray with sum == target
        int left = 0, right = 0;
        int sum = 0;
        int maxLen = -1;  // -1 means no valid subarray found

        while (right < n) {
            // 1. EXPAND: add nums[right]
            sum += nums[right];

            // 2. SHRINK: while sum exceeds target (all positive, so shrink works)
            while (sum > target) {
                sum -= nums[left];
                left++;
            }

            // 3. CHECK: if sum exactly matches target, update max length
            if (sum == target) {
                maxLen = max(maxLen, right - left + 1);
            }

            right++;
        }

        // If no valid middle subarray found, it's impossible
        return (maxLen == -1) ? -1 : n - maxLen;
    }
};

int main()
{
    Solution sol;
    SolutionNaive naive;

    vector<int> nums1 = {1, 1, 4, 2, 3};
    cout << "Sliding Window: " << sol.minOperations(nums1, 5) << endl;  // 2
    cout << "Naive:          " << naive.minOperations(nums1, 5) << endl;  // 2

    vector<int> nums2 = {5, 6, 7, 8, 9};
    cout << "Sliding Window: " << sol.minOperations(nums2, 4) << endl;  // -1
    cout << "Naive:          " << naive.minOperations(nums2, 4) << endl;  // -1

    vector<int> nums3 = {3, 2, 20, 1, 1, 3};
    cout << "Sliding Window: " << sol.minOperations(nums3, 10) << endl;  // 5
    cout << "Naive:          " << naive.minOperations(nums3, 10) << endl;  // 5

    return 0;
}
