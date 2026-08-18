#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

// ──────────────────────────────────────────────────────────────────────────────
// Problem: Subarray Product Less Than K (LeetCode 713)
// ──────────────────────────────────────────────────────────────────────────────

/*
    Problem Statement:
    ------------------
    Given an array of positive integers nums and an integer k, return the number
    of contiguous subarrays where the product of all the elements is strictly
    less than k.

    Examples:
    ---------
    Input:  nums = [10, 5, 2, 6], k = 100
    Output: 8
    Explanation: The 8 subarrays with product < 100 are:
                 [10], [5], [2], [6], [10,5], [5,2], [2,6], [5,2,6]

    Input:  nums = [1, 2, 3], k = 0
    Output: 0
    Explanation: No subarray has product < 0.

    Constraints:
    ------------
    - 1 <= nums.length <= 3 * 10^4
    - 1 <= nums[i] <= 1000
    - 0 <= k <= 10^6

    Approach:
    ---------
    Variable Sliding Window — COUNT all valid subarrays.

    This is different from previous problems:
    - Before: find the LONGEST/SHORTEST valid window.
    - Here: COUNT the total number of valid subarrays.

    Key Insight:
    For each position of right, how many valid subarrays END at right?
    Answer: (right - left + 1)

    Why? If window [left..right] is valid (product < k), then ALL subarrays
    ending at right within this window are also valid:
        [right], [right-1, right], [right-2, right-1, right], ..., [left..right]
    That's (right - left + 1) subarrays.

    Why all of them are valid?
    - All elements are POSITIVE (≥ 1).
    - Shrinking a subarray (removing elements from left) can only DECREASE
      or maintain the product.
    - If [left..right] has product < k, then [left+1..right], [left+2..right], etc.
      all have product ≤ product([left..right]) < k.

    Template:
        Expand right, multiply product.
        While product >= k: shrink (divide by nums[left], left++).
        count += (right - left + 1).   ← all subarrays ending at right.

    Worked Example:
    ---------------
    nums = [10, 5, 2, 6], k = 100

    left=0, right=0: product = 10. 10 < 100 ✓.
                     count += (0-0+1) = 1.  → subarrays: [10]
                     Total = 1.

    left=0, right=1: product = 50. 50 < 100 ✓.
                     count += (1-0+1) = 2.  → subarrays: [5], [10,5]
                     Total = 3.

    left=0, right=2: product = 100. 100 >= 100 ✗! Shrink.
                     product /= 10. left=1. product = 10.
                     10 < 100 ✓.
                     count += (2-1+1) = 2.  → subarrays: [2], [5,2]
                     Total = 5.

    left=1, right=3: product = 60. 60 < 100 ✓.
                     count += (3-1+1) = 3.  → subarrays: [6], [2,6], [5,2,6]
                     Total = 8.

    Result: 8 ✓

    All 8 subarrays:
    right=0: [10]
    right=1: [5], [10,5]
    right=2: [2], [5,2]
    right=3: [6], [2,6], [5,2,6]

    Why not [10,5,2]? product = 100, NOT less than 100.
    Why not [10,5,2,6]? product = 600, not less than 100.

    Time Complexity: O(N) — left and right each move forward at most N times
    Space Complexity: O(1)
*/

class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        // Edge case: if k <= 1, no positive product can be less than k
        // (since all nums[i] >= 1, smallest product is 1)
        if (k <= 1) return 0;

        int n = nums.size();
        int left = 0, right = 0;
        int product = 1;
        int count = 0;

        while (right < n) {
            // 1. EXPAND: multiply nums[right] into product
            product *= nums[right];

            // 2. SHRINK: while product is too big (>= k)
            while (product >= k) {
                product /= nums[left];  // safe because all elements >= 1
                left++;
            }

            // 3. COUNT: all subarrays ending at right within [left..right] are valid
            // They are: [right], [right-1,right], ..., [left..right]
            count += (right - left + 1);

            right++;
        }

        return count;
    }
};

int main()
{
    Solution obj;

    vector<int> nums1 = {10, 5, 2, 6};
    cout << "Subarrays with product < 100: " << obj.numSubarrayProductLessThanK(nums1, 100) << endl;  // 8

    vector<int> nums2 = {1, 2, 3};
    cout << "Subarrays with product < 0: " << obj.numSubarrayProductLessThanK(nums2, 0) << endl;  // 0

    return 0;
}
