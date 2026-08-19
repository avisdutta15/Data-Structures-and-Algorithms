#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

// ──────────────────────────────────────────────────────────────────────────────
// Problem: Maximum Beauty of an Array After Applying Operation (LeetCode 2779)
// ──────────────────────────────────────────────────────────────────────────────

/*
    https://www.youtube.com/watch?v=VrFolxiw_yQ  (Queue based approach)

    Problem Statement:
    ------------------
    You are given a 0-indexed array nums and a non-negative integer k. In one
    operation, you can:
        - Choose an index i that hasn't been chosen before.
        - Replace nums[i] with any integer in the range [nums[i] - k, nums[i] + k].

    The beauty of the array is the length of the longest subsequence consisting
    of equal elements. (After operations, how many elements can be made equal?)

    Return the maximum possible beauty after applying the operation to each
    element at most once.

    Note: you can apply the operation to EACH element independently.

    Examples:
    ---------
    Input:  nums = [4, 6, 1, 2], k = 2
    Output: 3
    Explanation:
        - nums[0]=4 can become [2, 6]
        - nums[1]=6 can become [4, 8]
        - nums[2]=1 can become [-1, 3]
        - nums[3]=2 can become [0, 4]
        Target value 4: nums[0]→4 ✓, nums[1]→4 ✓, nums[3]→4 ✓. Beauty = 3.

    Input:  nums = [1, 1, 1, 1], k = 10
    Output: 4
    Explanation: All already equal.

    Constraints:
    ------------
    - 1 <= nums.length <= 10^5
    - 1 <= nums[i] <= 10^5
    - 0 <= k <= 10^5

    
    Approach 1: Naive: O(N^2)
    -------------------------
    - For each element, treat its value as the target.
    - Count how many elements can reach that target: 
        if (nums[j] - k <= target && target <= nums[j] + k) {
            count++;
        }
    - The maximum count across all targets is the answer.
    
    
    Approach 2: Range-Based + Sort + Queue (Overlapping Intervals) — O(N log N)
    ────────────────────────────────────────────────────────────────────────────

    Intuition:
    Each nums[i] can become anything in [nums[i]-k, nums[i]+k]. Think of each
    element as an INTERVAL on a number line. The question becomes:
    "What is the maximum number of intervals that all share a common point?"

    If 3 intervals overlap at some point T, it means all 3 elements can become T.
    So max overlapping intervals = max beauty.

     Why this works:
    - Sorted by start: as we process interval i, all previous intervals in the queue
    started before or at the same time.
    - If a previous interval's end < current start → no overlap → remove it.
    - Remaining intervals in the queue all overlap with current → queue size = overlap count.

    Example: nums = [1, 2, 4, 6], k = 2
    Intervals (sorted by start = sorted by value since all have same width):
     1: [-1, 3]
     2: [ 0, 4]
     4: [ 2, 6]
     6: [ 4, 8]

   Number line:
     -1  0  1  2  3  4  5  6  7  8
      [──────────1──────────]
         [──────────2──────────]
               [──────────4──────────]
                     [──────────6──────────]

    Elements can be made equal if ranges OVERLAP
    If two ranges overlap, there exists some target value T that both can reach.

    From the drawing:
    - 1 and 4 overlap at [2, 3]. Both can become 2 or 3. ✓
    - 4 and 6 overlap at [4, 6]. Both can become 4, 5, or 6. ✓
    - 1 and 6: [-1,3] and [4,8] DON'T overlap. Gap = 6-1=5 > 2k=4. ✗

   Processing (queue stores full intervals):
     i=0: interval [-1, 3]. Queue = {[-1,3]}. Size=1.
     i=1: interval [0, 4]. Front end=3 >= 0? keep. Queue={[-1,3],[0,4]}. Size=2.
     i=2: interval [2, 6]. Front end=3 >= 2? keep. Queue={[-1,3],[0,4],[2,6]}. Size=3.
     i=3: interval [4, 8]. Front end=3 < 4? remove! Queue={[0,4],[2,6]}.
                           Front end=4 >= 4? keep. Queue={[0,4],[2,6],[4,8]}. Size=3.

   Max size = 3 ✓ (intervals for 1,2,4 all overlap at point 2 or 3)

    Algorithm:
    1. PREPARE: Create interval [nums[i]-k, nums[i]+k] for each element.
    2. SORT: Sort intervals by start time.
    3. ITERATE with QUEUE:
       - For each interval, push its END into the queue.
       - Remove from the front of the queue any interval whose END < current START
         (those intervals don't overlap with the current one).
       - Queue size = number of intervals overlapping at the current point.
       - Track maximum queue size.

    Why a queue works:
    - Intervals are sorted by start. So ends in the queue are in non-decreasing order
      (since all intervals have the same width 2k, sorted by start = sorted by end).
    - The oldest interval (front of queue) has the smallest end.
    - If the front's end < current start → it doesn't overlap → pop it.
    - Everything remaining in the queue overlaps with the current interval.
*/

// ── Naive: O(N^2) — for each element as target, count how many can reach it ──
class SolutionNaive {
public:
    int maximumBeauty(vector<int>& nums, int k) {
        int result = 0;

        // Try each element's value as the target
        for (int i = 0; i < (int)nums.size(); i++) {
            int target = nums[i];
            int count = 0;

            // Count how many elements can reach this target
            for (int j = 0; j < (int)nums.size(); j++) {
                // nums[j] can become target if target is within [nums[j]-k, nums[j]+k]
                if (nums[j] - k <= target && target <= nums[j] + k) {
                    count++;
                }
            }

            result = max(result, count);
        }

        return result;
    }
};

// ── Queue Approach: Overlapping Intervals — O(N log N) ──
// 
// Idea: Treat each element nums[i] as an interval [nums[i]-k, nums[i]+k].
// The answer = maximum number of intervals that all overlap at some point.
//
// If we sort intervals by start time, we use a queue to track active intervals.
// An interval leaves the queue when its END is before the current interval's START
// (no overlap possible). The queue size at any point = number of overlapping intervals.
//
// The queue stores ENTIRE intervals (pair<int,int>) so we can inspect both
// the start and end of each active interval. We check the front's END against
// the current interval's START to decide if it still overlaps.
//
// Why this works:
// - Sorted by start: as we process interval i, all previous intervals in the queue
//   started before or at the same time.
// - If a previous interval's end < current start → no overlap → remove it.
// - Remaining intervals in the queue all overlap with current → queue size = overlap count.
//
// Example: nums = [1, 2, 4, 6], k = 2
//   Intervals (sorted by start = sorted by value since all have same width):
//     1: [-1, 3]
//     2: [ 0, 4]
//     4: [ 2, 6]
//     6: [ 4, 8]
//
//   Number line:
//     -1  0  1  2  3  4  5  6  7  8
//      [──────────1──────────]
//         [──────────2──────────]
//               [──────────4──────────]
//                     [──────────6──────────]
//
//   Processing (queue stores full intervals):
//     i=0: interval [-1, 3]. Queue = {[-1,3]}. Size=1.
//     i=1: interval [0, 4]. Front end=3 >= 0? keep. Queue={[-1,3],[0,4]}. Size=2.
//     i=2: interval [2, 6]. Front end=3 >= 2? keep. Queue={[-1,3],[0,4],[2,6]}. Size=3.
//     i=3: interval [4, 8]. Front end=3 < 4? remove! Queue={[0,4],[2,6]}.
//                           Front end=4 >= 4? keep. Queue={[0,4],[2,6],[4,8]}. Size=3.
//
//   Max size = 3 ✓ (intervals for 1,2,4 all overlap at point 2 or 3)
//
// This is equivalent to the sliding window approach — just framed differently.
// Both sort and find the longest "compatible" group. The queue approach makes
// the interval overlap intuition explicit.
//
#include <queue>

class SolutionQueue {
public:
    int maximumBeauty(vector<int>& nums, int k) {
        int n = nums.size();

        // Step 1: Prepare intervals [nums[i]-k, nums[i]+k] for each element
        vector<pair<int, int>> intervals(n);
        for (int i = 0; i < n; i++) {
            intervals[i] = {nums[i] - k, nums[i] + k};
        }

        // Step 2: Sort intervals by start time
        sort(intervals.begin(), intervals.end());

        // Step 3: Iterate and use queue to track overlapping intervals
        int result = 0;
        queue<pair<int, int>> q;  // stores entire intervals {start, end}

        for (int i = 0; i < n; i++) {
            int start = intervals[i].first;
            int end = intervals[i].second;

            // Remove intervals from front whose END < current START (no overlap)
            while (!q.empty() && q.front().second < start) {
                q.pop();
            }

            // Add current interval to queue
            q.push({start, end});

            // Queue size = number of currently overlapping intervals
            result = max(result, (int)q.size());
        }

        return result;
    }
};

class Solution {
public:
    int maximumBeauty(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());

        int n = nums.size();
        int left = 0, right = 0;
        int result = 0;

        while (right < n) {
            // SHRINK: while window is INVALID (range exceeds 2k)
            while (nums[right] - nums[left] > 2 * k) {
                left++;
            }

            // UPDATE: window is valid, maximize length
            result = max(result, right - left + 1);

            right++;
        }

        return result;
    }
};

int main()
{
    Solution sol;
    SolutionNaive naive;
    SolutionQueue solQ;

    vector<int> nums1 = {4, 6, 1, 2};
    cout << "Sliding Window (k=2): " << sol.maximumBeauty(nums1, 2) << endl;    // 3
    cout << "Queue (k=2):          " << solQ.maximumBeauty(nums1, 2) << endl;   // 3
    cout << "Naive (k=2):          " << naive.maximumBeauty(nums1, 2) << endl;  // 3

    vector<int> nums2 = {1, 1, 1, 1};
    cout << "Sliding Window (k=10): " << sol.maximumBeauty(nums2, 10) << endl;    // 4
    cout << "Queue (k=10):          " << solQ.maximumBeauty(nums2, 10) << endl;   // 4
    cout << "Naive (k=10):          " << naive.maximumBeauty(nums2, 10) << endl;  // 4

    return 0;
}
