#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>
#include <map>
#include <deque>

using namespace std;

// ──────────────────────────────────────────────────────────────────────────────
// Problem: Continuous Subarrays (LeetCode 2762)
// ──────────────────────────────────────────────────────────────────────────────

/*
    https://www.youtube.com/watch?v=SWyGD8w_85E
    
    Problem Statement:
    ------------------
    You are given a 0-indexed integer array nums. A subarray of nums is called
    continuous if:
        For all pairs (i, j) where left <= i, j <= right:
            |nums[i] - nums[j]| <= 2

    Equivalently: max(subarray) - min(subarray) <= 2.

    Return the total number of continuous subarrays.

    Examples:
    ---------
    Input:  nums = [5, 4, 2, 4]
    Output: 8
    Explanation: All continuous subarrays:
                 Size 1: [5], [4], [2], [4] → 4 subarrays (always valid)
                 Size 2: [5,4] (5-4=1<=2 ✓), [4,2] (4-2=2<=2 ✓), [2,4] (4-2=2<=2 ✓) → 3
                 Size 3: [5,4,2] (5-2=3>2 ✗), [4,2,4] (4-2=2<=2 ✓) → 1
                 Size 4: [5,4,2,4] (5-2=3>2 ✗) → 0
                 Total: 4 + 3 + 1 = 8 ✓

    Input:  nums = [1, 2, 3]
    Output: 6
    Explanation: All 6 subarrays are valid (max-min <= 2 for all).

    Constraints:
    ------------
    - 1 <= nums.length <= 10^5
    - 1 <= nums[i] <= 10^9

    Approach:
    ---------
    Variable Sliding Window — COUNT all valid subarrays.

    Window condition: max - min <= 2 (VALID)
    Invalid when: max - min > 2

    Same counting trick as LC 713 (Subarray Product Less Than K):
    For each right, the number of valid subarrays ENDING at right = (right - left + 1).

    Why (right - left + 1)?
    ────────────────────────
    After shrinking, the window [left..right] is the LONGEST valid window ending at right.
    That means:
    - [left..right] is valid (max - min <= 2)
    - [left-1..right] would be invalid (that's why we shrunk to left)

    Since [left..right] is valid, ALL subarrays that START at left or later and END at right
    are also valid (because a sub-window of a valid window has a smaller or equal range).

    These subarrays ending at right are:
        [right, right]          (length 1)
        [right-1, right]        (length 2)
        [right-2, right]        (length 3)
        ...
        [left, right]           (length right-left+1)

    Total = right - left + 1 subarrays.

    Example: nums = [5, 4, 2, 4], at right=3, left=1
        Window [1..3] = [4, 2, 4]. max-min = 4-2 = 2 <= 2 ✓.
        Valid subarrays ending at index 3:
            [4]       = nums[3..3]   ✓
            [2, 4]    = nums[2..3]   ✓ (max-min = 2)
            [4, 2, 4] = nums[1..3]   ✓ (max-min = 2)
        Count = 3 - 1 + 1 = 3 ✓

    We do NOT include [5, 4, 2, 4] = nums[0..3] because left=1, meaning
    starting from index 0 would be invalid (5-2=3 > 2).

    Challenge: How to efficiently track max and min in the window?
    - Naive: scan window each time → O(n) per step → O(n²) total.
    - Optimal: use an ordered map (like a sorted multiset or TreeMap) → O(log n) per step.
    - Alternative: use two monotonic deques (one for max, one for min) → O(1) amortized.

    Using ordered map (simpler to implement):
    - map<int, int> stores value → count in window.
    - map.begin()->first = current min.
    - map.rbegin()->first = current max.
    - On expand: map[nums[right]]++.
    - On shrink: map[nums[left]]--. If count becomes 0, erase.
    - Check validity: map.rbegin()->first - map.begin()->first <= 2.

    Worked Example:
    ---------------
    nums = [5, 4, 2, 4]

    left=0, right=0: map={5:1}. max-min = 0 <= 2 ✓.
                     count += (0-0+1) = 1. Total=1.
    left=0, right=1: map={4:1, 5:1}. max-min = 5-4 = 1 <= 2 ✓.
                     count += (1-0+1) = 2. Total=3.
    left=0, right=2: map={2:1, 4:1, 5:1}. max-min = 5-2 = 3 > 2 ✗. INVALID!
                     Shrink: map[5]-- → erase 5. left=1. map={2:1, 4:1}. max-min = 4-2 = 2 <= 2 ✓.
                     count += (2-1+1) = 2. Total=5.
    left=1, right=3: map={2:1, 4:2}. max-min = 4-2 = 2 <= 2 ✓.
                     count += (3-1+1) = 3. Total=8.

    Result: 8 ✓

    Time Complexity: O(N log N) with ordered map (each insert/erase is O(log N))
    Space Complexity: O(N) worst case for the map
*/

// ── Approach 1: Naive O(N^2) — scan for max/min each expansion ──
class SolutionNaive {
public:
    long long continuousSubarrays(vector<int>& nums) {
        int n = nums.size();
        long long count = 0;

        for (int i = 0; i < n; i++) {
            int maxVal = nums[i], minVal = nums[i];

            for (int j = i; j < n; j++) {
                maxVal = max(maxVal, nums[j]);
                minVal = min(minVal, nums[j]);

                // If window is valid, count it
                if (maxVal - minVal <= 2) {
                    count++;
                } else {
                    // Once invalid, extending further only makes it worse
                    break;
                }
            }
        }

        return count;
    }
};

// ── Approach 2: Sliding Window + Ordered Map — O(N log N) ──
class Solution {
public:
    long long continuousSubarrays(vector<int>& nums) {
        int n = nums.size();
        int left = 0, right = 0;
        long long count = 0;
        map<int, int> window;  // ordered map: value → frequency in window

        while (right < n) {
            // 1. EXPAND: add nums[right] to window
            window[nums[right]]++;

            // 2. SHRINK: while window is INVALID (max - min > 2)
            while (window.rbegin()->first - window.begin()->first > 2) {
                // Remove nums[left] from window
                window[nums[left]]--;
                if (window[nums[left]] == 0)
                    window.erase(nums[left]);
                left++;
            }

            // 3. COUNT: all subarrays ending at right within [left..right] are valid
            count += (long long)(right - left + 1);

            right++;
        }

        return count;
    }
};

// ── Approach 3: Sliding Window + Two Monotonic Deques — O(N) ──
// maxDeque (decreasing): front = current window max
// minDeque (increasing): front = current window min
// Each element enters and leaves each deque at most once → O(1) amortized per step.
class SolutionDeque {
public:
    long long continuousSubarrays(vector<int>& nums) {
        int n = nums.size();
        int left = 0, right = 0;
        long long count = 0;

        deque<int> maxDq;  // stores indices, decreasing by value
        deque<int> minDq;  // stores indices, increasing by value

        while (right < n) {
            // 1. EXPAND: maintain monotonic deques

            // maxDq: remove indices from back whose values are smaller than nums[right]
            // (they can never be the max while nums[right] is in the window)
            while (!maxDq.empty() && nums[maxDq.back()] <= nums[right])
                maxDq.pop_back();
            maxDq.push_back(right);

            // minDq: remove indices from back whose values are larger than nums[right]
            // (they can never be the min while nums[right] is in the window)
            while (!minDq.empty() && nums[minDq.back()] >= nums[right])
                minDq.pop_back();
            minDq.push_back(right);

            // 2. SHRINK: while max - min > 2
            while (nums[maxDq.front()] - nums[minDq.front()] > 2) {
                // Move left past whichever deque front is at left
                if (maxDq.front() == left)
                    maxDq.pop_front();
                if (minDq.front() == left)
                    minDq.pop_front();
                left++;
            }

            // 3. COUNT: all subarrays ending at right within [left..right] are valid
            count += (long long)(right - left + 1);

            right++;
        }

        return count;
    }
};

int main()
{
    Solution sol;
    SolutionNaive naive;
    SolutionDeque solDq;

    vector<int> nums1 = {5, 4, 2, 4};
    cout << "Ordered Map:  " << sol.continuousSubarrays(nums1) << endl;      // 8
    cout << "Mono Deque:   " << solDq.continuousSubarrays(nums1) << endl;    // 8
    cout << "Naive:        " << naive.continuousSubarrays(nums1) << endl;    // 8

    vector<int> nums2 = {1, 2, 3};
    cout << "Ordered Map:  " << sol.continuousSubarrays(nums2) << endl;      // 6
    cout << "Mono Deque:   " << solDq.continuousSubarrays(nums2) << endl;    // 6
    cout << "Naive:        " << naive.continuousSubarrays(nums2) << endl;    // 6

    return 0;
}
