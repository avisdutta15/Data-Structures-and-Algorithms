#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;


/*
    Problem Statement:
    ------------------
    Given an array of positive integers nums and a positive integer target, return
    the MINIMAL LENGTH of a subarray whose sum is greater than or equal to target.
    If there is no such subarray, return 0.

    Examples:
    ---------
    Input:  target = 7, nums = [2, 3, 1, 2, 4, 3]
    Output: 2
    Explanation: The subarray [4, 3] has the minimal length under the condition.

    Input:  target = 4, nums = [1, 4, 4]
    Output: 1

    Input:  target = 11, nums = [1, 1, 1, 1, 1, 1, 1, 1]
    Output: 0

    Constraints:
    ------------
    - 1 <= target <= 10^9
    - 1 <= nums.length <= 10^5
    - 1 <= nums[i] <= 10^4

    Approach:
    ---------
    This is a "find SHORTEST valid window" problem.

    Window condition: sum >= target (VALID when sum is large enough)
    Goal: find the smallest window that is valid.

    Template (Shortest — shrink while VALID):
        while (right < n) {
            // expand: add nums[right]
            // while window is VALID (sum >= target):
            //     update answer (minimize length)
            //     shrink from left
            // right++
        }

    Why it works:
    - All elements are POSITIVE, so expanding (right++) always increases sum,
      and shrinking (left++) always decreases sum.
    - Once sum >= target, we try shrinking to find the minimum window.
    - We keep shrinking until the window becomes invalid (sum < target),
      then expand again.

    Why not use this for arrays with negatives?
    - With negatives, expanding might decrease sum and shrinking might increase it.
    - The monotonic relationship breaks, so sliding window doesn't apply directly.

    Worked Example:
    ---------------
    nums = [2, 3, 1, 2, 4, 3], target = 7

    left=0, right=0: sum=2. sum < 7. right++.
    left=0, right=1: sum=5. sum < 7. right++.
    left=0, right=2: sum=6. sum < 7. right++.
    left=0, right=3: sum=8. sum >= 7 ✓. result=min(INT_MAX, 4)=4. shrink: sum-=2, left=1.
    left=1, right=3: sum=6. sum < 7. right++.
    left=1, right=4: sum=10. sum >= 7 ✓. result=min(4, 4)=4. shrink: sum-=3, left=2.
    left=2, right=4: sum=7. sum >= 7 ✓. result=min(4, 3)=3. shrink: sum-=1, left=3.
    left=3, right=4: sum=6. sum < 7. right++.
    left=3, right=5: sum=9. sum >= 7 ✓. result=min(3, 3)=3. shrink: sum-=2, left=4.
    left=4, right=5: sum=7. sum >= 7 ✓. result=min(3, 2)=2. shrink: sum-=4, left=5.
    left=5, right=5: sum=3. sum < 7. right++.
    right=6: out of bounds, done.

    Result: 2 ✓ (subarray [4, 3])

    Time Complexity: O(N) — left and right each move forward at most N times
    Space Complexity: O(1)
*/

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int left = 0, right = 0;
        int sum = 0;
        int result = INT_MAX;

        while (right < n) {
            // 1. EXPAND: add nums[right] to window
            sum += nums[right];

            // 2. SHRINK: while window is VALID (sum >= target), minimize
            while (sum >= target) {
                result = min(result, right - left + 1);
                sum -= nums[left];
                left++;
            }

            // 3. Move right forward
            right++;
        }

        return (result == INT_MAX) ? 0 : result;
    }
};

int main()
{
    Solution obj;

    vector<int> nums1 = {2, 3, 1, 2, 4, 3};
    cout << "Min length: " << obj.minSubArrayLen(7, nums1) << endl;  // 2

    vector<int> nums2 = {1, 4, 4};
    cout << "Min length: " << obj.minSubArrayLen(4, nums2) << endl;  // 1

    vector<int> nums3 = {1, 1, 1, 1, 1, 1, 1, 1};
    cout << "Min length: " << obj.minSubArrayLen(11, nums3) << endl;  // 0

    return 0;
}
