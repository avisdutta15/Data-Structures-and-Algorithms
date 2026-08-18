#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/*
    Problem Statement:
    ------------------
    Given an integer array nums of length n and an integer target, find three
    integers in nums such that the sum is CLOSEST to target.
    Return the sum of the three integers.

    You may assume that each input would have exactly one solution.

    Examples:
    ---------
    Input:  nums = [-1, 2, 1, -4], target = 1
    Output: 2
    Explanation: The sum that is closest to target is 2. (-1 + 2 + 1 = 2)

    Input:  nums = [0, 0, 0], target = 1
    Output: 0

    Constraints:
    ------------
    - 3 <= nums.length <= 500
    - -1000 <= nums[i] <= 1000
    - -10^4 <= target <= 10^4

    Approach:
    ---------
    Exactly the same structure as 3Sum:
    - Sort the array.
    - Fix nums[i], use two pointers (j = i+1, k = n-1).
    - Instead of checking sum == 0, we track which sum is closest to target.

    Difference from 3Sum:
    - 3Sum: we check if sum == 0. If less, move j++. If more, move k--.
    - 3Sum Closest: we compute sum, update closest if |sum - target| < |closest - target|.
      Then if sum < target, move j++. If sum > target, move k--.
    - No need to handle duplicates (we just want the closest, not unique triplets).
      But skipping duplicates can speed it up.

    Worked Example:
    ---------------
    nums = [-1, 2, 1, -4], target = 1
    After sort: [-4, -1, 1, 2]

    closestSum = INT_MAX (or nums[0]+nums[1]+nums[2] = -4+-1+1 = -4)

    i=0, nums[i]=-4, j=1, k=3:
      sum = -4 + (-1) + 2 = -3.  |(-3)-1| = 4.  closestSum = -3
      sum < target → j++
      sum = -4 + 1 + 2 = -1.     |(-1)-1| = 2.  closestSum = -1
      sum < target → j++
      j >= k, done.

    i=1, nums[i]=-1, j=2, k=3:
      sum = -1 + 1 + 2 = 2.      |2-1| = 1.     closestSum = 2
      sum > target → k--
      j >= k, done.

    i=2: only 1 element left after i, can't form triplet, stop.

    Result: 2 ✓

    Time Complexity: O(NlogN) + O(N^2) = O(N^2)
    Space Complexity: O(1)
*/

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());

        // Initialize with first possible triplet sum
        int closestSum = nums[0] + nums[1] + nums[2];

        for (int i = 0; i <= (int)nums.size() - 3; i++) {
            // Skip duplicates for i (optional optimization)
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            int j = i + 1, k = nums.size() - 1;

            while (j < k) {
                //skip duplicates for j
                if (j != i + 1 && nums[j] == nums[j - 1]) {
                    j++;
                }

                //skip duplicates for k
                else if (k != nums.size() - 1 && nums[k] == nums[k + 1]) {
                    k--;
                }
                else {
                    int sum = nums[i] + nums[j] + nums[k];

                    // Update closest if this sum is nearer to target
                    if (abs(sum - target) < abs(closestSum - target)) {
                        closestSum = sum;
                    }

                    // Exact match — can't do better
                    if (sum == target) {
                        return sum;
                    }
                    else if (sum < target) {
                        j++;
                    }
                    else {
                        k--;
                    }
                }                
            }
        }

        return closestSum;
    }
};

int main()
{
    // 3Sum Closest
    Solution obj2;
    vector<int> B = { -1, 2, 1, -4 };
    cout << "3Sum Closest: " << obj2.threeSumClosest(B, 1) << endl;  // 2
}
