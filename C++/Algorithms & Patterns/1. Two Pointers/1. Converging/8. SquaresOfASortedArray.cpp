#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement:
    ------------------
    Given an integer array nums sorted in non-decreasing order, return an array
    of the squares of each number sorted in non-decreasing order.

    Examples:
    ---------
    Input:  nums = [-4, -1, 0, 3, 10]
    Output: [0, 1, 9, 16, 100]

    Input:  nums = [-7, -3, 2, 3, 11]
    Output: [4, 9, 9, 49, 121]

    Constraints:
    ------------
    - 1 <= nums.length <= 10^4
    - -10^4 <= nums[i] <= 10^4
    - nums is sorted in non-decreasing order.

    Follow up: Can you do it in O(n) time?

    Approach:
    ---------
    Naive: Square each element, then sort → O(nlogn)

    Two Pointers (Converging) → O(n):

    Key Insight:
    - The array is sorted but has negatives. After squaring, the LARGEST values
      are at the two ends (far left has large negative → large square,
      far right has large positive → large square).
    - The smallest squares are somewhere in the middle (near zero).

    So: compare absolute values from both ends, fill the result array from the BACK.

    Steps:
    1. left = 0, right = n-1
    2. Create result array of size n.
    3. Fill result from position n-1 down to 0:
       - Compare |nums[left]| vs |nums[right]|.
       - Whichever is bigger, its square goes into the current position.
       - Move that pointer inward.

    Why fill from the back?
    - The largest square is at one of the two ends.
    - By picking the larger of the two ends each time and placing it at the back
      of result, we build the sorted array in reverse.

    Worked Example:
    ---------------
    nums = [-4, -1, 0, 3, 10]
            L                R

    pos=4: |nums[0]|=4 vs |nums[4]|=10. 10 > 4. result[4]=100. right--.
    pos=3: |nums[0]|=4 vs |nums[3]|=3.  4 > 3.  result[3]=16.  left++.
    pos=2: |nums[1]|=1 vs |nums[3]|=3.  3 > 1.  result[2]=9.   right--.
    pos=1: |nums[1]|=1 vs |nums[2]|=0.  1 > 0.  result[1]=1.   left++.
    pos=0: |nums[2]|=0 vs |nums[2]|=0.  equal.   result[0]=0.   done.

    result = [0, 1, 9, 16, 100] ✓

    Time Complexity: O(N)
    Space Complexity: O(N) for result (O(1) extra if output doesn't count)
*/

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);

        int left = 0, right = n - 1;
        int pos = n - 1;  // fill from the back. Why? Because largest should go at last.

        while (left <= right) {
            int leftSq = nums[left] * nums[left];
            int rightSq = nums[right] * nums[right];
            
            if (leftSq >= rightSq) {
                result[pos] = leftSq;
                left++;
            } else {
                result[pos] = rightSq;
                right--;
            }
            pos--;
        }

        return result;
    }
};

int main()
{
    Solution obj;

    vector<int> nums = {-4, -1, 0, 3, 10};
    auto result = obj.sortedSquares(nums);

    cout << "Sorted squares: [";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;  // [0, 1, 9, 16, 100]

    return 0;
}
