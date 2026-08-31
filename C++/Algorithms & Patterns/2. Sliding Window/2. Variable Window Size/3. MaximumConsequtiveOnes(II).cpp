#include <iostream>
#include <vector>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 487 - Max Consecutive Ones II
    Given a binary array nums, return the maximum number of consecutive 1's
    if you can flip at most one 0.

    Examples:
    ---------
    Input:  nums = [1, 0, 1, 1, 0, 1]
    Output: 4
    Explanation: Flip the 0 at index 1 → [1,1,1,1,0,1], longest run = 4.

    Input:  nums = [1, 0, 1, 1, 0]
    Output: 4
    Explanation: Flip the 0 at index 4 → [1,0,1,1,1], longest run = 4.
                 Or flip index 1 → [1,1,1,1,0], longest run = 4.

    Constraints:
    ------------
    - 1 <= nums.length <= 10^5
    - nums[i] is either 0 or 1

    Approach:
    ---------
    Variable Sliding Window — Find LONGEST valid window.

    Reframe the problem:
    "Find the longest subarray containing at most one 0."
    Flipping that one 0 makes the entire window all-1's.

    Window condition: zeroCount <= 1  (VALID)
    Invalid when:     zeroCount > 1

    Steps:
      1. Expand right: if nums[end] == 0, increment zeroCount.
      2. Shrink left while INVALID (zeroCount > 1):
             if nums[start] == 0, decrement zeroCount. start++.
      3. Update answer: maxLength = max(maxLength, end - start + 1).
      4. end++.

    Worked Example:
    ---------------
    index= 0  1  2  3  4  5
    nums = [1, 0, 1, 1, 0, 1]

    start=0, end=0: nums[0]=1. zeros=0. maxLen=1.
    start=0, end=1: nums[1]=0. zeros=1. maxLen=2.
    start=0, end=2: nums[2]=1. zeros=1. maxLen=3.
    start=0, end=3: nums[3]=1. zeros=1. maxLen=4.
    start=0, end=4: nums[4]=0. zeros=2 > 1! INVALID.
                    shrink: nums[0]=1, start=1. zeros still 2.
                    shrink: nums[1]=0, start=2. zeros=1. VALID.
                    maxLen=max(4, 4-2+1)=max(4,3)=4.
    start=2, end=5: nums[5]=1. zeros=1. maxLen=max(4,4)=4.

    Result: 4 ✓

    Time Complexity:  O(N)
    Space Complexity: O(1)
*/

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int n = nums.size();
        int start = 0, end = 0;
        int zeroCount = 0;

        int maxLength = 0;
        while (end < n) {
            // ADD TO WINDOW
            if (nums[end] == 0) zeroCount++;

            // SHRINK
            while (zeroCount > 1) {
                if (nums[start] == 0) zeroCount--;
                start++;
            }

            // CALCULATE WINDOW SIZE AND SLIDE
            maxLength = max(maxLength, end - start + 1);
            end++;
        }
        return maxLength;
    }
};

int main() {
    Solution obj;
    vector<int> nums = {1, 0, 1, 1, 0, 1};
    cout << obj.findMaxConsecutiveOnes(nums) << endl; // Expected: 4
}