#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement:
    ------------------
    Given an array of n integers nums and an integer target, find the number of
    index triplets (i, j, k) with 0 <= i < j < k < n that satisfy the condition:
        nums[i] + nums[j] + nums[k] < target

    Examples:
    ---------
    Input:  nums = [-2, 0, 1, 3], target = 2
    Output: 2
    Explanation: Because there are two triplets which sums are less than 2:
                 [-2, 0, 1] → sum = -1
                 [-2, 0, 3] → sum = 1

    Input:  nums = [], target = 0
    Output: 0

    Input:  nums = [0], target = 0
    Output: 0

    Constraints:
    ------------
    - n == nums.length
    - 0 <= n <= 3500
    - -100 <= nums[i] <= 100
    - -100 <= target <= 100

    Approach:
    ---------
    Same structure as 3Sum: Sort + fix one element + two pointers.

    Key Difference from 3Sum:
    - 3Sum: find triplets where sum == 0. Count unique triplets.
    - 3Sum Smaller: COUNT triplets where sum < target. Duplicates are OK (we count indices, not values).

    Steps:
    1. Sort the array.
    2. Fix nums[i] (outer loop).
    3. Two pointers: left = i+1, right = n-1.
    4. If nums[i] + nums[left] + nums[right] < target:
       → ALL pairs (left, left+1), (left, left+2), ..., (left, right) are valid!
         Because moving right to the left only makes the sum smaller.
         So we add (right - left) to the count, then move left++.
    5. Else:
       → Sum is too big, move right--.

    The Critical Insight (why count += right - left):
    ─────────────────────────────────────────────────
    When nums[i] + nums[left] + nums[right] < target, since the array is sorted:
      nums[left] <= nums[left+1] <= ... <= nums[right]

    If pairing left with right (the LARGEST remaining) still gives sum < target,
    then pairing left with anything between left+1 and right will ALSO give sum < target.

    How many such pairs? right - left pairs: (left, left+1), (left, left+2), ..., (left, right).

    Worked Example:
    ---------------
    nums = [-2, 0, 1, 3], target = 2
    After sort: [-2, 0, 1, 3]

    i=0, nums[i]=-2, left=1, right=3:
      sum = -2 + 0 + 3 = 1 < 2 ✓
      count += right - left = 3 - 1 = 2.  (triplets: [-2,0,3] and [-2,0,1])
      left++.

      left=2, right=3:
      sum = -2 + 1 + 3 = 2 == 2, NOT less. right--.
      left=2, right=2: left >= right, done.

    i=1, nums[i]=0, left=2, right=3:
      sum = 0 + 1 + 3 = 4 >= 2. right--.
      left=2, right=2: left >= right, done.

    Total count = 2 ✓

    Another Example:
    nums = [1, 2, 3, 4, 5], target = 10
    After sort: [1, 2, 3, 4, 5]

    i=0, nums[i]=1:
      left=1, right=4: 1+2+5=8 < 10 → count += 4-1 = 3. left++.
        (triplets: [1,2,5], [1,2,4], [1,2,3])
      left=2, right=4: 1+3+5=9 < 10 → count += 4-2 = 2. left++.
        (triplets: [1,3,5], [1,3,4])
      left=3, right=4: 1+4+5=10 >= 10. right--.
      left >= right, done.

    i=1, nums[i]=2:
      left=2, right=4: 2+3+5=10 >= 10. right--.
      left=2, right=3: 2+3+4=9 < 10 → count += 3-2 = 1. left++.
        (triplet: [2,3,4])
      left >= right, done.

    i=2, nums[i]=3:
      left=3, right=4: 3+4+5=12 >= 10. right--.
      left >= right, done.

    Total count = 3 + 2 + 1 = 6

    Time Complexity: O(N^2)
        Sorting: O(NlogN)
        Outer loop O(N) × Two pointers O(N) = O(N^2)

    Space Complexity: O(1)
*/

class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        int n = nums.size();
        if (n < 3) return 0;

        sort(nums.begin(), nums.end());
        int count = 0;

        for (int i = 0; i < n - 2; i++) {
            int left = i + 1, right = n - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum < target) {
                    // All pairs (left, left+1), ..., (left, right) are valid
                    count += (right - left);
                    left++;
                } else {
                    // Sum too big, need smaller → move right
                    right--;
                }
            }
        }

        return count;
    }
};

int main()
{
    Solution obj;

    vector<int> nums1 = {-2, 0, 1, 3};
    cout << "3Sum Smaller: " << obj.threeSumSmaller(nums1, 2) << endl;  // 2

    vector<int> nums2 = {1, 2, 3, 4, 5};
    cout << "3Sum Smaller: " << obj.threeSumSmaller(nums2, 10) << endl;  // 6

    return 0;
}
