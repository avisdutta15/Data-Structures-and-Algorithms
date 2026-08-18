#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>
#include <map>
#include <deque>

using namespace std;

// ──────────────────────────────────────────────────────────────────────────────
// Problem: Longest Continuous Subarray With Absolute Diff <= Limit (LeetCode 1438)
// ──────────────────────────────────────────────────────────────────────────────

/*
    Problem Statement:
    ------------------
    Given an array of integers nums and an integer limit, return the size of the
    longest non-empty subarray such that the absolute difference between any two
    elements of this subarray is less than or equal to limit.

    Examples:
    ---------
    Input:  nums = [8, 2, 4, 7], limit = 4
    Output: 2
    Explanation: [2, 4] → max-min = 2 <= 4. Length 2.
                 [4, 7] → max-min = 3 <= 4. Length 2.
                 [8, 2, 4] → max-min = 6 > 4. Invalid.
                 Longest = 2.

    Input:  nums = [10, 1, 2, 4, 7, 2], limit = 5
    Output: 4
    Explanation: [2, 4, 7, 2] → max=7, min=2, diff=5 <= 5. Length 4.

    Input:  nums = [4, 2, 2, 2, 4, 4, 2, 2], limit = 0
    Output: 3
    Explanation: [2, 2, 2] → max-min = 0 <= 0. Length 3.

    Constraints:
    ------------
    - 1 <= nums.length <= 10^5
    - 1 <= nums[i] <= 10^9
    - 0 <= limit <= 10^9

    This is the same as LC 2762 (Continuous Subarrays) but with a variable `limit`
    instead of fixed 2, and we find the LONGEST window instead of counting.

    Equivalently: max(subarray) - min(subarray) <= limit.

    Why max - min is equivalent to "absolute diff between ANY two elements <= limit":
    ─────────────────────────────────────────────────────────────────────────────────
    The problem says: |nums[i] - nums[j]| <= limit for ALL pairs (i, j) in the subarray.

    The largest possible |nums[i] - nums[j]| in any subarray is always
    max(subarray) - min(subarray). This is because:
    - |a - b| is maximized when one is the largest and the other is the smallest.
    - All other pairs have a difference <= max - min.

    So if max - min <= limit, then EVERY pair satisfies |nums[i] - nums[j]| <= limit.
    And if max - min > limit, then at least one pair (the max and min) violates it.

    Therefore: "all pairs differ by at most limit" ⟺ "max - min <= limit".


    ═══════════════════════════════════════════════════════════════════════
    Approach 1: Ordered Map — O(N log N)
    ═══════════════════════════════════════════════════════════════════════
    Same as LC 2762: use std::map to track values in window.
    - map.begin()->first = min
    - map.rbegin()->first = max
    - Shrink while max - min > limit.

    ═══════════════════════════════════════════════════════════════════════
    Approach 2: Two Monotonic Deques — O(N)
    ═══════════════════════════════════════════════════════════════════════
    Use two deques:
    - maxDeque: decreasing order → front is the current window max.
    - minDeque: increasing order → front is the current window min.

    On expand (add nums[right]):
    - maxDeque: pop from back while back < nums[right]. Push nums[right].
    - minDeque: pop from back while back > nums[right]. Push nums[right].

    On shrink (remove nums[left]):
    - If maxDeque.front() == nums[left]: pop front.
    - If minDeque.front() == nums[left]: pop front.

    Validity check: maxDeque.front() - minDeque.front() <= limit.

    Why monotonic deques are O(1) amortized:
    - Each element is pushed and popped from each deque at most once.
    - Total operations across all steps = O(N).

    Why use deques instead of ordered map?
    - Ordered map: O(log N) per insert/erase → O(N log N) total.
    - Monotonic deques: O(1) amortized per step → O(N) total.

    How monotonic deques maintain max/min:
    ──────────────────────────────────────
    maxDeque (decreasing):
        Stores potential maximum candidates. Front is always the current max.
        When we add a new element, we remove all smaller elements from the back
        because they can never be the max while the new (larger) element is in the window.

    minDeque (increasing):
        Stores potential minimum candidates. Front is always the current min.
        When we add a new element, we remove all larger elements from the back
        because they can never be the min while the new (smaller) element is in the window.

    Worked Example (Deques):
    ------------------------
    nums = [10, 1, 2, 4, 7, 2], limit = 5

    right=0 (10): maxDq=[10], minDq=[10]. max-min=0<=5. result=1.
    right=1 (1):  maxDq=[10,1], minDq=[1]. max-min=9>5! Shrink.
                  left=0: 10==maxDq.front() → pop. maxDq=[1]. left=1.
                  max-min=0<=5. result=1.
    right=2 (2):  maxDq: pop 1 (1<2), push 2. maxDq=[2]. minDq=[1,2]. max-min=1<=5. result=2.
    right=3 (4):  maxDq: pop 2 (2<4), push 4. maxDq=[4]. minDq=[1,2,4]. max-min=3<=5. result=3.
    right=4 (7):  maxDq: pop 4 (4<7), push 7. maxDq=[7]. minDq=[1,2,4,7]. max-min=6>5! Shrink.
                  left=1: 1==minDq.front() → pop. minDq=[2,4,7]. left=2.
                  max-min=7-2=5<=5. result=max(3,3)=3.
    
    Wait, window is [2..4] = [2,4,7]. length=3. result stays 3.

    right=5 (2):  maxDq: 7>2, just push. maxDq=[7,2]. minDq: pop 7,4 (>2), push 2. minDq=[2,2].
                  Wait — minDq was [2,4,7]. Adding 2: pop while back > 2: pop 7, pop 4. minDq=[2,2].
                  max-min=7-2=5<=5. window=[2..5]=[2,4,7,2]. length=4. result=4.

    Result: 4 ✓

    Time Complexity: O(N) — each element pushed/popped from deques at most once
    Space Complexity: O(N) worst case for the deques
*/

// ── Approach 1: Ordered Map — O(N log N) ──
class Solution1 {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int n = nums.size();
        int left = 0, right = 0;
        int result = 0;
        map<int, int> window;  // value → count

        while (right < n) {
            // 1. EXPAND
            window[nums[right]]++;

            // 2. SHRINK: while max - min > limit
            while (window.rbegin()->first - window.begin()->first > limit) {
                window[nums[left]]--;
                if (window[nums[left]] == 0)
                    window.erase(nums[left]);
                left++;
            }

            // 3. UPDATE
            result = max(result, right - left + 1);
            right++;
        }

        return result;
    }
};

// ── Approach 2: Two Monotonic Deques — O(N) ──
class Solution2 {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int n = nums.size();
        int left = 0, right = 0;
        int result = 0;

        deque<int> maxDq;  // decreasing: front = current max
        deque<int> minDq;  // increasing: front = current min

        while (right < n) {
            // 1. EXPAND: maintain monotonic deques
            // maxDq: remove smaller elements from back (they'll never be max)
            while (!maxDq.empty() && maxDq.back() < nums[right])
                maxDq.pop_back();
            maxDq.push_back(nums[right]);

            // minDq: remove larger elements from back (they'll never be min)
            while (!minDq.empty() && minDq.back() > nums[right])
                minDq.pop_back();
            minDq.push_back(nums[right]);

            // 2. SHRINK: while max - min > limit
            while (maxDq.front() - minDq.front() > limit) {
                // Remove nums[left] from deques if it's at the front
                if (maxDq.front() == nums[left])
                    maxDq.pop_front();
                if (minDq.front() == nums[left])
                    minDq.pop_front();
                left++;
            }

            // 3. UPDATE: window is valid
            result = max(result, right - left + 1);
            right++;
        }

        return result;
    }
};

int main()
{
    Solution1 sol1;
    Solution2 sol2;

    vector<int> nums1 = {8, 2, 4, 7};
    cout << "Ordered Map: " << sol1.longestSubarray(nums1, 4) << endl;  // 2
    cout << "Mono Deque:  " << sol2.longestSubarray(nums1, 4) << endl;  // 2

    vector<int> nums2 = {10, 1, 2, 4, 7, 2};
    cout << "Ordered Map: " << sol1.longestSubarray(nums2, 5) << endl;  // 4
    cout << "Mono Deque:  " << sol2.longestSubarray(nums2, 5) << endl;  // 4

    vector<int> nums3 = {4, 2, 2, 2, 4, 4, 2, 2};
    cout << "Ordered Map: " << sol1.longestSubarray(nums3, 0) << endl;  // 3
    cout << "Mono Deque:  " << sol2.longestSubarray(nums3, 0) << endl;  // 3

    return 0;
}
