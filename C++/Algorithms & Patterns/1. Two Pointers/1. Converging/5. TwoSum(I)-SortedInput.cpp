#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement:
    ------------------
    Given a 1-indexed array of integers `numbers` that is already sorted in
    non-decreasing order, find two numbers such that they add up to a specific
    target number.

    Return the indices of the two numbers (1-indexed) as [index1, index2]
    where 1 <= index1 < index2 <= numbers.length.

    There is exactly one solution. You may not use the same element twice.
    Your solution must use only constant extra space.

    Examples:
    ---------
    Input:  numbers = [2, 7, 11, 15], target = 9
    Output: [1, 2]
    Explanation: 2 + 7 = 9. indices are 1 and 2.

    Input:  numbers = [2, 3, 4], target = 6
    Output: [1, 3]
    Explanation: 2 + 4 = 6.

    Input:  numbers = [-1, 0], target = -1
    Output: [1, 2]

    Constraints:
    ------------
    - 2 <= numbers.length <= 3 * 10^4
    - -1000 <= numbers[i] <= 1000
    - numbers is sorted in non-decreasing order
    - -1000 <= target <= 1000
    - There is exactly one solution.

    Approach:
    ---------
    This is the simplest converging two-pointer problem.

    Since the array is SORTED:
    - left = 0, right = n-1
    - sum = numbers[left] + numbers[right]
    - If sum == target → found it.
    - If sum < target → need a bigger sum → move left++ (next bigger element).
    - If sum > target → need a smaller sum → move right-- (next smaller element).

    Why this works:
    - Array is sorted, so moving left++ increases the sum, moving right-- decreases it.
    - We are guaranteed exactly one solution, so we will always find it before left >= right.

    This is the FOUNDATION of all converging pointer problems:
    - 3Sum = fix one + this
    - 3Sum Closest = fix one + variation of this
    - 4Sum = fix two + this

    Worked Example:
    ---------------
    numbers = [2, 7, 11, 15], target = 9

    left=0, right=3: sum = 2+15 = 17 > 9, right--
    left=0, right=2: sum = 2+11 = 13 > 9, right--
    left=0, right=1: sum = 2+7  = 9 == 9 ✓ → return [1, 2]

    Time Complexity: O(N)
    Space Complexity: O(1)
*/

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0, right = numbers.size() - 1;

        while (left < right) {
            int sum = numbers[left] + numbers[right];

            if (sum == target) {
                // 1-indexed result
                return {left + 1, right + 1};
            }
            else if (sum < target) {
                left++;
            }
            else {
                right--;
            }
        }

        // Should never reach here (problem guarantees exactly one solution)
        return {-1, -1};
    }
};

int main()
{
    Solution obj;
    vector<int> numbers = {2, 7, 11, 15};
    int target = 9;

    auto result = obj.twoSum(numbers, target);
    cout << "Two Sum II: [" << result[0] << ", " << result[1] << "]" << endl;  // [1, 2]

    return 0;
}
