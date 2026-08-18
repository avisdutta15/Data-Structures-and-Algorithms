#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// ──────────────────────────────────────────────────────────────────────────────
// Problem: Maximum Sum of Distinct Subarrays With Length K (LeetCode 2461)
// ──────────────────────────────────────────────────────────────────────────────

/*
    Problem Statement:
    ------------------
    Given an integer array nums and an integer k, find the maximum subarray sum
    of all subarrays of nums that meet the following conditions:
        - The length of the subarray is k, AND
        - All the elements of the subarray are DISTINCT.

    Return the maximum sum. If no subarray meets the conditions, return 0.

    Examples:
    ---------
    Input:  nums = [1, 5, 4, 2, 9, 9, 9], k = 3
    Output: 15
    Explanation: Subarrays of length 3 with all distinct elements:
                 [1,5,4] sum=10, [5,4,2] sum=11, [4,2,9] sum=15, [2,9,9] has dup,
                 [9,9,9] has dup. Max = 15.

    Input:  nums = [4, 4, 4], k = 3
    Output: 0
    Explanation: [4,4,4] has duplicates. No valid subarray.

    Constraints:
    ------------
    - 1 <= k <= nums.length <= 10^5
    - 1 <= nums[i] <= 10^5

    Approach:
    ---------
    This combines FIXED SIZE window + distinct constraint.

    It's a fixed-size window of size k, but we only consider it valid if all
    elements are distinct. Among all valid windows, find the maximum sum.

    Window state:
    - A running sum (add on expand, subtract on shrink).
    - A frequency map to track duplicates (or count distinct elements).

    How to know if all elements are distinct?
    - freq map: window is valid when freq.size() == k (exactly k distinct elements
      in a window of size k → all must be distinct).

    Template:
        Expand right, add to sum, update freq.
        If window size > k: shrink from left (subtract, update freq).
        If window size == k AND freq.size() == k: update answer.

    Worked Example:
    ---------------
    nums = [1, 5, 4, 2, 9, 9, 9], k = 3

    right=0: sum=1. freq={1:1}. window size=1 < 3.
    right=1: sum=6. freq={1:1, 5:1}. window size=2 < 3.
    right=2: sum=10. freq={1:1, 5:1, 4:1}. window size=3.
             freq.size()=3 == k=3 → all distinct! result=max(0, 10)=10.
    right=3: sum=10+2=12. window size=4 > 3. Shrink:
             sum -= nums[0]=1 → sum=11. freq[1]-- → 0, erase. left=1.
             freq={5:1, 4:1, 2:1}. window size=3.
             freq.size()=3 == 3 → valid! result=max(10, 11)=11.
    right=4: sum=11+9=20. window size=4 > 3. Shrink:
             sum -= nums[1]=5 → sum=15. freq[5]-- → 0, erase. left=2.
             freq={4:1, 2:1, 9:1}. window size=3.
             freq.size()=3 == 3 → valid! result=max(11, 15)=15.
    right=5: sum=15+9=24. window size=4 > 3. Shrink:
             sum -= nums[2]=4 → sum=20. freq[4]-- → 0, erase. left=3.
             freq={2:1, 9:2}. window size=3.
             freq.size()=2 ≠ 3 → has duplicates. Skip.
    right=6: sum=20+9=29. window size=4 > 3. Shrink:
             sum -= nums[3]=2 → sum=27. freq[2]-- → 0, erase. left=4.
             freq={9:3}. window size=3.
             freq.size()=1 ≠ 3 → has duplicates. Skip.

    Result: 15 ✓

    Time Complexity: O(N)
    Space Complexity: O(k) for the frequency map
*/

class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        int left = 0, right = 0;
        long long sum = 0;
        long long result = 0;
        unordered_map<int, int> freq;  // element → count in window

        while (right < n) {
            // 1. EXPAND: add nums[right] to window
            sum += nums[right];
            freq[nums[right]]++;

            // 2. SHRINK: if window exceeds size k, remove from left
            if (right - left + 1 > k) {
                sum -= nums[left];
                freq[nums[left]]--;
                if (freq[nums[left]] == 0)
                    freq.erase(nums[left]);
                left++;
            }

            // 3. UPDATE: if window is exactly size k and all elements are distinct
            if (right - left + 1 == k && (int)freq.size() == k) {
                result = max(result, sum);
            }

            right++;
        }

        return result;
    }
};

int main()
{
    Solution obj;

    vector<int> nums1 = {1, 5, 4, 2, 9, 9, 9};
    cout << "Max sum (k=3): " << obj.maximumSubarraySum(nums1, 3) << endl;  // 15

    vector<int> nums2 = {4, 4, 4};
    cout << "Max sum (k=3): " << obj.maximumSubarraySum(nums2, 3) << endl;  // 0

    return 0;
}
