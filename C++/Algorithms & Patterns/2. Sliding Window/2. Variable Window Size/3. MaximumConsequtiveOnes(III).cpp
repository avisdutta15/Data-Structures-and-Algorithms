#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement:
    ------------------
    Given a binary array nums and an integer k, return the maximum number of
    consecutive 1's in the array if you can flip at most k 0's.

    Examples:
    ---------
    Input:  nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
    Output: 6
    Explanation: Flip the 0's at index 5 and 10.
                 [1,1,1,0,0,1,1,1,1,1,1] → longest run of 1's = 6.
                 Actually: flip index 5 and 10 → window from index 5 to 10.
                 Better: [1,1,1,0,0,0,1,1,1,1,1] flip index 10 → 6 ones from idx 5..10? 
                 Let me recheck: flip indices 5,10 → array has 1's at 0-3, 5-10.
                 Longest consecutive = indices 5 to 10 = 6 ✓

    Input:  nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
    Output: 10
    Explanation: Flip 0's at indices 4, 5, 9.
                 Window [2..11] has 10 elements with at most 3 zeros.

    Constraints:
    ------------
    - 1 <= nums.length <= 10^5
    - nums[i] is either 0 or 1
    - 0 <= k <= nums.length

    Approach:
    ---------
    Variable Sliding Window — Find LONGEST valid window.

    Reframe the problem:
    "Find the longest subarray that contains at most k zeros."

    If a window has at most k zeros, we can flip them all to 1, making the entire
    window all-1's. So the longest such window = the answer.

    Window condition: count of 0's in window <= k (VALID)
    Invalid when: count of 0's > k

    Template (Longest — shrink while INVALID):
        while (right < n) {
            // expand: if nums[right] == 0, increment zero count
            // while window is INVALID (zeroCount > k):
            //     shrink: if nums[left] == 0, decrement zero count. left++.
            // update answer: result = max(result, right - left + 1)
            // right++
        }

    Worked Example:
    ---------------
    index=  0  1  2  3  4  5  6  7  8  9  10
    nums = [1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0], k = 2

    left=0, right=0: nums[0]=1. zeros=0. result=1.
    left=0, right=1: nums[1]=1. zeros=0. result=2.
    left=0, right=2: nums[2]=1. zeros=0. result=3.
    left=0, right=3: nums[3]=0. zeros=1. result=4.
    left=0, right=4: nums[4]=0. zeros=2. result=5.
    left=0, right=5: nums[5]=0. zeros=3 > k=2! INVALID.
                     shrink: nums[0]=1, left=1. zeros still 3.
                     shrink: nums[1]=1, left=2. zeros still 3.
                     shrink: nums[2]=1, left=3. zeros still 3.
                     shrink: nums[3]=0, left=4. zeros=2. VALID now.
                     result=max(5, 5-4+1)=max(5,2)=5.
    left=4, right=6: nums[6]=1. zeros=2. result=max(5,3)=5.
    left=4, right=7: nums[7]=1. zeros=2. result=max(5,4)=5.
    left=4, right=8: nums[8]=1. zeros=2. result=max(5,5)=5.
    left=4, right=9: nums[9]=1. zeros=2. result=max(5,6)=6.
    left=4, right=10: nums[10]=0. zeros=3 > k=2! INVALID.
                      shrink: nums[4]=0, left=5. zeros=2. VALID.
                      result=max(6, 10-5+1)=max(6,6)=6.

    Result: 6 ✓

    Time Complexity: O(N)
    Space Complexity: O(1)
*/

class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size();
        int left = 0, right = 0;
        int zeroCount = 0;
        int result = 0;

        while (right < n) {
            // 1. EXPAND: add nums[right] to window
            if (nums[right] == 0)
                zeroCount++;

            // 2. SHRINK: while window is INVALID (too many zeros)
            while (zeroCount > k) {
                if (nums[left] == 0)
                    zeroCount--;
                left++;
            }

            // 3. UPDATE: window is valid, maximize length
            result = max(result, right - left + 1);

            right++;
        }

        return result;
    }
};

int main()
{
    Solution obj;

    vector<int> nums1 = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
    cout << "Max consecutive ones (k=2): " << obj.longestOnes(nums1, 2) << endl;  // 6

    vector<int> nums2 = {0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1};
    cout << "Max consecutive ones (k=3): " << obj.longestOnes(nums2, 3) << endl;  // 10

    return 0;
}
