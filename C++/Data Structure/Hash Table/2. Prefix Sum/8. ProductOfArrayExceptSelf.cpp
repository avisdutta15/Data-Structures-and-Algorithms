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

/*
    https://www.youtube.com/watch?v=ku4oITayEmk

    Problem Statement:
    ------------------
    Given an integer array nums, return an array result such that result[i] is equal to the
    product of all the elements of nums except nums[i].
    You must solve it WITHOUT using division and in O(n) time.

    Examples:
    --------
    Input:  nums = [1, 2, 3, 4]
    Output: [24, 12, 8, 6]

    Input:  nums = [-1, 1, 0, -3, 3]
    Output: [0, 0, 9, 0, 0]

    Constraints:
    ------------
    - 2 <= nums.length <= 10^5
    - -30 <= nums[i] <= 30
    - The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
    - Follow up: Can you solve it in O(1) extra space? (output array doesn't count)

    Approach :
    ----------
    1. Brute Force (Solution1)
       - For each i, multiply all elements except nums[i].
       - Time: O(n^2), Space: O(1)

    2. Division (Solution2)
       - Compute total product, divide by nums[i] for each i.
       - Handle zeros separately (use totalProductExceptZero).
       - Time: O(n), Space: O(1)
       - NOTE: Fails if there are 2 or more zeros (all results are 0). Not allowed by problem.

    3. Two arrays - left[i] = product of 0..i, right[i] = product of i..n-1 (Solution3)
       - left[i] includes nums[i], so for result[i] we use left[i-1] * right[i+1].
       - Requires edge case handling for i=0 and i=n-1.
       - Time: O(n), Space: O(n)

    4. Two arrays - left[i] = product of 0..i-1, right[i] = product of i+1..n-1 (Solution4)
       - left[i] stores product of everything BEFORE i (exclusive of nums[i]).
       - right[i] stores product of everything AFTER i (exclusive of nums[i]).
       - result[i] = left[i] * right[i] — no edge case needed.
       - Time: O(n), Space: O(n)

    5. One array (left) + running rightProduct variable (Solution5)
       - Build left[] as in approach 4.
       - Instead of right[], maintain a single running variable rightProduct.
       - Traverse from right, accumulate rightProduct, and compute result[i] = left[i] * rightProduct.
       - Time: O(n), Space: O(n) for left array

    ──────────────────────────────────────────────────────────────────────
    DETAILED WALKTHROUGH: Approach 4 (Two Prefix Arrays, No Edge Cases)
    ──────────────────────────────────────────────────────────────────────

    Key Idea:
      left[i]  = product of all elements BEFORE index i  = nums[0] * nums[1] * ... * nums[i-1]
      right[i] = product of all elements AFTER index i   = nums[i+1] * nums[i+2] * ... * nums[n-1]
      left[0] = 1 and right[n-1] = 1
      result[i] = left[i] * right[i]
      

    Since left[i] excludes nums[i] and right[i] excludes nums[i], their product
    gives the product of everything except nums[i].

    Example: nums = [1, 2, 3, 4]

    Building left[]:
      left[0] = 1              (nothing before index 0)
      left[1] = left[0] * nums[0] = 1 * 1 = 1
      left[2] = left[1] * nums[1] = 1 * 2 = 2
      left[3] = left[2] * nums[2] = 2 * 3 = 6

      left = [1, 1, 2, 6]

    Building right[]:
      right[3] = 1             (nothing after index 3)
      right[2] = right[3] * nums[3] = 1 * 4 = 4
      right[1] = right[2] * nums[2] = 4 * 3 = 12
      right[0] = right[1] * nums[1] = 12 * 2 = 24

      right = [24, 12, 4, 1]

    Final result:
        left = [1, 1, 2, 6]
        right = [24, 12, 4, 1]
      result[0] = left[0] * right[0] = 1 * 24  = 24
      result[1] = left[1] * right[1] = 1 * 12  = 12
      result[2] = left[2] * right[2] = 2 * 4   = 8
      result[3] = left[3] * right[3] = 6 * 1   = 6

      result = [24, 12, 8, 6] ✓

    Why no edge cases? Because left[0]=1 and right[n-1]=1 naturally handle boundaries.

    ──────────────────────────────────────────────────────────────────────
    DETAILED WALKTHROUGH: Approach 5 (One Array + Running Variable)
    ──────────────────────────────────────────────────────────────────────

    Key Idea:
      We still need left[i] and right[i], but we don't need to STORE right[] as a full array.
      - Build left[] exactly as in Approach 4.
      - Then sweep from right to left, maintaining a single variable rightProduct that
        accumulates the product of elements to the right.
      - At each i: , 
            update rightProduct:
                if(i == n-1) 
                    rightProduct = 1
                else
                    rightProduct = rightProduct * nums[i+1]
            then result[i] = left[i] * rightProduct

    Example: nums = [1, 2, 3, 4]

    Step 1 — Build left[]:
      left = [1, 1, 2, 6]    (same as Approach 4)

    Step 2 — Sweep right to left:

      Start: rightProduct = 1

      i=3: (i == n-1) so rightProduct = 1
           result[3] = left[3] * rightProduct = 6 * 1 = 6

      i=2: rightProduct = rightProduct * nums[i+1] = 1 * nums[3] = 1 * 4 = 4
           result[2] = left[2] * rightProduct = 2 * 4 = 8

      i=1: rightProduct = rightProduct * nums[i+1] = 4 * nums[2] = 4 * 3 = 12
           result[1] = left[1] * rightProduct = 1 * 12 = 12

      i=0: rightProduct = rightProduct * nums[i+1] = 12 * nums[1] = 12 * 2 = 24
           result[0] = left[0] * rightProduct = 1 * 24 = 24

      result = [24, 12, 8, 6] ✓

    Why this works:
      At each step, we first accumulate nums[i+1] into rightProduct (the element just to
      the right of i), so that by the time we use it, rightProduct holds the product of
      all elements from i+1 to n-1. Then we multiply it with left[i].

    Further optimization (not coded here):
      You can eliminate left[] too by using the result array to store left products first,
      then multiplying rightProduct into it on the second pass. This gives O(1) extra space.
*/

// Brute Force: O(n^2)
class Solution1 {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int product = 1;
        vector<int> result;

        for (int i = 0; i < nums.size(); i++) {

            // reset for fresh product except i
            product = 1;

            for (int j = 0; j < nums.size(); j++) {
                // skip self
                if (i != j)
                    product *= nums[j];
            }

            result.push_back(product);
        }

        return result;
    }
};

class Solution2 {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int totalProduct = 1;
        int totalProductExceptZero = 1;

        vector<int> result;

        for (int num : nums) {
            totalProduct = totalProduct * num;
            if(num != 0)
                totalProductExceptZero = totalProductExceptZero * num;
        }

        for (int i = 0; i < nums.size(); i++) {

            // if the current number is not zero, we can simply divide the total product by the current number
            if (nums[i] != 0) {
                result.push_back(totalProduct / nums[i]);
            }
            // if current number if zero, we cannot divide by zero, so use the other product
            else if (nums[i] == 0) {
                result.push_back(totalProductExceptZero);
            }
        }

        return result;
    }
};

class Solution3 {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> result;
        vector<int> left(n, 1);
        vector<int> right(n, 1);

        // Calculate the product till i-th element from the left
        for (int i = 0; i <= n - 2; i++) {
            if(i == 0)
                left[i] = nums[i];
            else
                left[i] = left[i-1] * nums[i];
        }

        // Calculate the product till i-th element from the right
        for(int i = n - 1; i >= 1; i-- ) {
            if(i == n - 1)
                right[i] = nums[i];
            else
                right[i] = right[i+1] * nums[i];
        }

        // Multiply left and right products to get the final result
        for (int i = 0; i < n; i++) {
            int leftProduct = 1;
            int rightProduct = 1;

            // Handle edge cases for first and last elements
            if(i == 0)
                leftProduct = 1;
            else
                leftProduct = left[i-1];

            if(i == n-1)
                rightProduct = 1;
            else
                rightProduct = right[i+1];

            // for ith element, multiply left and right products
            result.push_back(leftProduct * rightProduct);
        }

        return result;
    }
};

// If you dont want to handle the edge case of zero and last index separately
// keep the 0 index = 1 for left 
// keep the last index = 1 for right
// in this way left[i] denotes product of elements from 0 to i-1
// in this way right[i] denotes product of elements from i+1 to n-1
// Time: O(n), Space: O(n)
class Solution4 {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> result;
        vector<int> left(n, 1);
        vector<int> right(n, 1);

        left[0] = 1;
        right[n - 1] = 1;

        // Calculate the product till i-th element from the left
        for (int i = 1; i < n; i++) {
            left[i] = left[i - 1] * nums[i - 1];
        }

        // Calculate the product till i-th element from the right
        for (int i = n - 2; i >= 0; i--) {
            right[i] = right[i + 1] * nums[i + 1];
        }

        // Multiply left and right products to get the final result
        for (int i = 0; i < n; i++) {
            int leftProduct = left[i];
            int rightProduct = right[i];

            // for ith element, multiply left and right products
            result.push_back(leftProduct * rightProduct);
        }

        return result;
    }
};

class Solution5 {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, 1);
        vector<int> left(n, 1);

        // Calculate the product till i-th element from the left
        for (int i = 1; i < n; i++) {
            left[i] = left[i - 1] * nums[i - 1];
        }

        // Multiply left and right products to get the final result
        int rightProduct = 1;
        for (int i = n - 1; i >= 0; i--) {
            int leftProduct = left[i];

            if (i == n - 1)
                rightProduct = 1;
            else
                rightProduct = rightProduct * nums[i + 1];

            // for ith element, multiply left and right products
            result[i] = (leftProduct * rightProduct);
        }
        return result;
    }
};

int main() {
    Solution1 obj;

    return 0;
}
