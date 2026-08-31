#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    Problem Statement:
    ------------------
    https://www.youtube.com/watch?v=iOqH_JnXIOQ
    LeetCode 1838 - Frequency of the Most Frequent Element

    The frequency of an element is the number of times it occurs in an array.
    You are given an integer array `nums` and an integer `k`. In one operation,
    you can choose an index of `nums` and increment the element at that index by 1.
    Return the maximum possible frequency of an element after performing at most
    `k` operations.

    Examples:
    ---------

    Example 1:
        Input:  nums = [1, 2, 4], k = 5
        Output: 3
        Explanation:
            Increment nums[0] five times  -> nums[0] becomes 1+3 = 4  (cost 3)
            Increment nums[1] two times   -> nums[1] becomes 2+2 = 4  (cost 2)
            Total cost = 3 + 2 = 5 <= k
            Now nums = [4, 4, 4]. The element 4 has frequency 3.

    Example 2:
        Input:  nums = [1, 4, 8, 13], k = 5
        Output: 2
        Explanation:
            Increment nums[0] three times -> nums[0] becomes 1+7 = 8  (cost 7 > k, too expensive alone with 8)
            But we can increment nums[1] four times -> nums[1] becomes 4+4 = 8 (cost 4)
            Or increment nums[0] to 4 (cost 3), making two 4s. Total cost = 3 <= k.
            Best we can do is a frequency of 2 (e.g., make nums[0]=4 with cost 3, freq of 4 is 2).

    Example 3:
        Input:  nums = [3, 9, 6], k = 2
        Output: 1
        Explanation:
            Sorted: [3, 6, 9]. The gap between any two elements is too large
            for k=2 to bridge more than one element to match another.
            Maximum frequency achievable is 1.

    Constraints:
    ------------
    - 1 <= nums.length <= 10^5
    - 1 <= nums[i]   <= 10^5
    - 1 <= k          <= 10^5

    Approach: Sorting + Sliding Window
    ==========================================

    Intuition:
    ----------
    Why must the target value be an element already in the array?
    Why not pick some arbitrary value outside the array?

    Suppose we pick a target T that is NOT in the array. Since we can only
    increment (never decrement), T must be >= every element we want to
    convert. Now consider two cases:

        Case 1: T > max(nums)
            Every element, including the largest one, must be incremented
            up to T. That means we are spending extra operations even on
            the element that was already the closest to T. If we had just
            chosen T = max(nums) instead, we save those wasted operations
            on the largest element and can use them to bring MORE elements
            up. So picking T above the array maximum is strictly worse
            (or at best equal, never better).

        Case 2: T is between two array elements, say nums[i] < T < nums[i+1]
            We are raising elements up to T. But nums[i+1] already exists
            in the array and nums[i+1] > T, so we can't include nums[i+1]
            (it would need decrementing, which isn't allowed). The group
            we'd convert is the same set of elements <= T. Now compare
            this to choosing T = nums[i] (the nearest array element below T):
            - Same group of convertible elements (everything <= nums[i]
              is also <= T).
            - But each element costs (T - nums[j]) instead of
              (nums[i] - nums[j]), which is MORE expensive since T > nums[i].
            So picking T between array values is strictly worse — we pay
            more for the exact same group.

    Conclusion: The optimal target is always some element already present
    in the array. Any value outside the array either wastes operations
    (Case 1) or costs more for the same group (Case 2). This is the key
    observation that lets us iterate over array elements as targets.

    With that settled, since we can only INCREMENT elements (never decrement), if we want to make
    multiple elements equal, we should raise smaller elements UP to match a
    larger element. This immediately suggests sorting the array first, because:

        1. After sorting, elements that are close in value are adjacent.
        2. The cheapest group of elements to make equal will always be a
           contiguous subarray in the sorted order (picking non-adjacent
           elements would skip over closer values, wasting operations).
        3. The TARGET value we raise everything to should be the largest
           element in the chosen group (the rightmost in the window),
           because raising it further would cost extra for every element.

    So the problem reduces to:
        "Find the longest contiguous window [start..end] in the sorted array
         such that the cost of raising every element in the window to
         nums[end] is at most k."

    Cost Calculation:
    -----------------
    For a window [start..end] with target = nums[end]:

        cost = (nums[end] - nums[start])
             + (nums[end] - nums[start+1])
             + ...
             + (nums[end] - nums[end])

             = nums[end] * windowLength  -  sum(nums[start..end])

             = targetSum - windowSum

    where:
        windowLength = end - start + 1
        targetSum    = nums[end] * windowLength   (ideal sum if all equal target)
        windowSum    = actual sum of elements in the window

    Sliding Window Mechanics:
    -------------------------
    We maintain two pointers, `start` and `end`, both initially at 0.

        - EXPAND: Move `end` to the right, adding nums[end] to windowSum.
          Recalculate opsNeeded = targetSum - windowSum.

        - SHRINK: If opsNeeded > k, the window is too expensive. Remove
          nums[start] from windowSum and move `start` right. Repeat until
          opsNeeded <= k.

        - RECORD: After shrinking, the window [start..end] is valid.
          Update maxFreq = max(maxFreq, end - start + 1).

    Why This Works:
    ---------------
    - Sorting ensures the cheapest candidates to raise are always adjacent.
    - The sliding window never revisits elements, giving O(n) window work.
    - Each element enters and leaves the window at most once.

    Dry Run (Example 1: nums = [1,2,4], k = 5):
    ---------------------------------------------
    Sorted: [1, 2, 4]

    end=0: window=[1],   windowSum=1, target=1, cost=1*1-1=0  <= 5  -> maxFreq=1
    end=1: window=[1,2], windowSum=3, target=2, cost=2*2-3=1  <= 5  -> maxFreq=2
    end=2: window=[1,2,4], windowSum=7, target=4, cost=4*3-7=5 <= 5 -> maxFreq=3

    Answer: 3  ✓

    ==========================================
    Complexity Analysis:
    ==========================================
    Time  : O(n log n)  — sorting dominates; the sliding window is O(n).
    Space : O(1)        — only a few integer variables (ignoring sort's internal space).

*/

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int start = 0, end = 0;

        int windowSum = 0;
        int windowLength = 0;
        int targetSum = 0;
        int opsNeeded = 0;
        int maxFreq = 0;
        int targetNum = 0;

        while (end < n) {
            // We want to make all elements in current window equal to nums[end]
            // so the desiredWindowSum = windowLength * nums[end]
            // This is the key insight: we want to convert the entire window into the same value
            // as the rightmost element (nums[end]) with minimum operations
            // The cost to do this is: (windowLength * nums[end]) - windowSum
            // while this cost > k, we need to shrink the window from left

            targetNum = nums[end];          // we want to make all the numbers from start to end equal to nums[end]
            windowSum = windowSum + targetNum;  // current window sum after including nums[end]
            targetSum = targetNum * (end - start + 1);  //what will be the windowsum if all elements become nums[end]? its. numOfElements we would replace * nums[end]
            opsNeeded = targetSum - windowSum;  // operations needed will be targetSum - windowSum.

            while (opsNeeded > k) {
                windowSum = windowSum - nums[start];
                start++;
                targetSum = nums[end] * (end - start + 1);
                opsNeeded = targetSum - windowSum;
            }

            maxFreq = max(maxFreq, end - start + 1);
            end++;
        }
        return maxFreq;
    }
};

int main() {
    Solution obj;
}