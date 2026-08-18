#include <algorithm>
#include <iostream>
#include <climits>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// ════════════════════════════════════════════════════════════════════════════════
// TWO POINTER PATTERN 1: CONVERGING POINTERS
// ════════════════════════════════════════════════════════════════════════════════
//
// Core Idea:
// - Two pointers start at opposite ends (left=0, right=n-1) and move toward each other.
// - At each step, decide which pointer to move based on some condition.
// - Terminates when left >= right (or left > right depending on problem).
//
// When to use:
// - Sorted array + find pair with some property
// - Maximize/minimize something by choosing from two ends
// - Comparing elements from both ends (palindrome check, container width, etc.)
//
// ════════════════════════════════════════════════════════════════════════════════

// ──────────────────────────────────────────────────────────────────────────────
// Problem 1: Container With Most Water (LeetCode 11)
// ──────────────────────────────────────────────────────────────────────────────

/*
    Problem Statement:
    ------------------
    Given n non-negative integers height[0..n-1] where each represents a vertical
    line at position i with height height[i], find two lines that together with
    the x-axis form a container that holds the most water.

    Examples:
    ---------
    Input:  height = [1,8,6,2,5,4,8,3,7]
    Output: 49
    Explanation: Lines at index 1 (height=8) and index 8 (height=7).
                 Area = min(8,7) * (8-1) = 7 * 7 = 49

    Input:  height = [1,1]
    Output: 1

    Constraints:
    ------------
    - 2 <= n <= 10^5
    - 0 <= height[i] <= 10^4

    Approach:
    ---------
    Brute Force: Try all pairs (i, j) → O(n^2)

    Two Pointer (Converging):
    - left = 0, right = n-1
    - Area = height * width
             height = min(height[left], height[right])
             width = (right - left)
    - Move the pointer with the SHORTER height inward.

    Why move the shorter one?
    - Width is decreasing as pointers converge (right - left shrinks).
    - The only way to potentially find a LARGER area is to find a taller line.
    - The area is limited by the shorter line (min of the two).
    - If we move the taller pointer, the height can only stay the same or decrease
      (still limited by the shorter one), AND width decreases → area can only shrink.
    - If we move the shorter pointer, we MIGHT find a taller line that increases
      the min height enough to overcome the width loss.

    Worked Example:
    ---------------
    height = [1, 8, 6, 2, 5, 4, 8, 3, 7]
              L                          R

    L=0, R=8: area = min(1,7) * 8 = 8.   height[L] < height[R], move L
    L=1, R=8: area = min(8,7) * 7 = 49.  height[R] < height[L], move R
    L=1, R=7: area = min(8,3) * 6 = 18.  height[R] < height[L], move R
    L=1, R=6: area = min(8,8) * 5 = 40.  equal, move either (say L)
    L=2, R=6: area = min(6,8) * 4 = 24.  height[L] < height[R], move L
    L=3, R=6: area = min(2,8) * 3 = 6.   height[L] < height[R], move L
    L=4, R=6: area = min(5,8) * 2 = 10.  height[L] < height[R], move L
    L=5, R=6: area = min(4,8) * 1 = 4.   height[L] < height[R], move L
    L=6, R=6: L >= R, stop.

    Maximum area = 49 ✓

    Time: O(n), Space: O(1)
*/

class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int maxWater = 0;

        while (left < right) {
            // Calculate area with current pair
            int width = right - left;
            int levelOfWaterStored = min(height[left], height[right]);
            maxWater = max(maxWater, width * levelOfWaterStored);

            // Move the shorter pointer inward
            // As we shrink the width, the only way to increase area is 
            // to find a taller line.
            // So discard the shorter line.
            if (height[left] < height[right])
                left++;
            else
                right--;
        }

        return maxWater;
    }
};

int main() {
    Solution obj;

    vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << "Max area: " << obj.maxArea(height) << endl;  // 49

    return 0;
}
