#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement:
    ------------------
    Given a binary array nums, you should delete one element from it.
    Return the size of the longest non-empty subarray containing only 1's
    in the resulting array. Return 0 if there is no such subarray.

    Examples:
    ---------
    Input:  nums = [1, 1, 0, 1, 1, 1, 0, 1, 1]
    Output: 5
    Explanation: Delete the 0 at index 2. Result: [1,1,1,1,1,0,1,1].
                 Longest run of 1's = 5.
                 Or delete index 6: [1,1,0,1,1,1,1,1] → longest = 5.

    Input:  nums = [0, 1, 1, 1, 0, 1, 1, 0, 1]
    Output: 5
    Explanation: Delete the 0 at index 4. [0,1,1,1,1,1,0,1] → longest 1's = 5.

    Input:  nums = [1, 1, 1]
    Output: 2
    Explanation: You MUST delete one element. Delete any 1 → [1,1] → length 2.

    Constraints:
    ------------
    - 1 <= nums.length <= 10^5
    - nums[i] is either 0 or 1.

    Approach:
    ---------
    This is almost identical to Max Consecutive Ones III (LC 1004) with k=1,
    but with one twist: you MUST delete exactly one element.

    Reframe: "Find the longest subarray containing at most 1 zero."
    Then the answer = (window length - 1), because we delete that one zero
    (or one 1 if the array is all 1's).

    Equivalently: answer = longest window with at most 1 zero, minus 1.

    Why minus 1?
    - In LC 1004: we FLIP zeros to 1's. The window IS the answer.
    - Here: we DELETE one element. The resulting subarray has one fewer element
      than the window. So answer = window_size - 1.

    Edge case: all 1's → window = entire array, but we must delete one,
    so answer = n - 1.

    Template (same as 1004 with k=1, then subtract 1):
        Find longest window with at most 1 zero.
        Return (window_length - 1).

    Worked Example:
    ---------------
    nums = [1, 1, 0, 1, 1, 1, 0, 1, 1]

    left=0, right=0: nums[0]=1. zeros=0. window=1.
    left=0, right=1: nums[1]=1. zeros=0. window=2.
    left=0, right=2: nums[2]=0. zeros=1. window=3.
    left=0, right=3: nums[3]=1. zeros=1. window=4.
    left=0, right=4: nums[4]=1. zeros=1. window=5.
    left=0, right=5: nums[5]=1. zeros=1. window=6.
    left=0, right=6: nums[6]=0. zeros=2 > 1! INVALID.
                     shrink: nums[0]=1, left=1. zeros=2 still.
                     shrink: nums[1]=1, left=2. zeros=2 still.
                     shrink: nums[2]=0, left=3. zeros=1. VALID.
                     window = 6-3+1 = 4.
    left=3, right=7: nums[7]=1. zeros=1. window=5.
    left=3, right=8: nums[8]=1. zeros=1. window=6.

    Max window = 6 (indices 0..5 or 3..8).
    Answer = 6 - 1 = 5 ✓

    (Window [3..8] = [1,1,1,0,1,1]. Delete the 0 at index 6 → [1,1,1,1,1] = 5.)

    Time Complexity: O(N)
    Space Complexity: O(1)
*/

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int n = nums.size();
        int left = 0, right = 0;
        int zeroCount = 0;
        int result = 0;

        while (right < n) {
            // 1. EXPAND
            if (nums[right] == 0)
                zeroCount++;

            // 2. SHRINK: while window has more than 1 zero
            while (zeroCount > 1) {
                if (nums[left] == 0)
                    zeroCount--;
                left++;
            }

            // 3. UPDATE: window is valid (at most 1 zero)
            result = max(result, right - left + 1);

            right++;
        }

        // Subtract 1 because we must delete one element
        return result - 1;
    }
};

int main()
{
    Solution obj;

    vector<int> nums1 = {1, 1, 0, 1, 1, 1, 0, 1, 1};
    cout << "Longest after deleting one: " << obj.longestSubarray(nums1) << endl;  // 5

    vector<int> nums2 = {0, 1, 1, 1, 0, 1, 1, 0, 1};
    cout << "Longest after deleting one: " << obj.longestSubarray(nums2) << endl;  // 5

    vector<int> nums3 = {1, 1, 1};
    cout << "Longest after deleting one: " << obj.longestSubarray(nums3) << endl;  // 2

    return 0;
}
