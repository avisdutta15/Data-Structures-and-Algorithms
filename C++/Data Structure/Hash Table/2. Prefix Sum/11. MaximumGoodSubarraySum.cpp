#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

/*
    https://www.youtube.com/watch?v=qN551m06ngs&t=12s
    Problem Statement:
    ------------------
    LeetCode 3026 - Maximum Good Subarray Sum

    You are given an array `nums` of length n and a positive integer `k`.
    A subarray nums[i..j] is called "good" if the absolute difference
    between its first and last element equals exactly k:
        |nums[i] - nums[j]| == k

    Find the maximum sum among all good subarrays. Return 0 if no good
    subarray exists.

    Examples:
    ---------

    Example 1:
        Input:  nums = [1, 2, 3, 4, 5, 6], k = 1
        Output: 11
        Explanation:
            The good subarray [5, 6] has |5 - 6| = 1 == k, and sum = 11.

    Example 2:
        Input:  nums = [-1, 3, 2, 4, 5], k = 3
        Output: 11
        Explanation:
            The good subarray [3, 2, 4, 5] has |3 - 5| = 2 ... not this one.
            The good subarray [-1, 3, 2, 4] has |-1 - 4| = 5 ... not this one.
            The good subarray [3, 2, 4, 5] ... |3 - 5| = 2, nope.
            The good subarray [-1, 3, 2] has |-1 - 2| = 3 == k, sum = 4.
            The good subarray [2, 4, 5] has |2 - 5| = 3 == k, sum = 11. ← max

    Example 3:
        Input:  nums = [-1, -2, -3, -4], k = 2
        Output: -6
        Explanation:
            The good subarray [-1, -2, -3] has |-1 - (-3)| = 2 == k, sum = -6.
            The good subarray [-2, -3, -4] has |-2 - (-4)| = 2 == k, sum = -9.
            -6 > -9, so answer is -6.

    Constraints:
    ------------
    - 2 <= nums.length <= 10^5
    - -10^9 <= nums[i] <= 10^9
    - 1 <= k <= 10^9

    Approach: Prefix Sum + HashMap
    ------------------------------

    Intuition — step by step:
    -------------------------

    Step 1: What are we looking for?

        For every pair (i, j) where i <= j, check if |nums[i] - nums[j]| == k.
        If yes, compute the sum nums[i] + nums[i+1] + ... + nums[j].
        We want the maximum such sum.

        Brute force: try all pairs (i, j), compute the sum. O(n^2). Too slow.

    Step 2: Use prefix sums to compute subarray sums fast.

        Let prefixSum up to index i = nums[0] + nums[1] + ... + nums[i].
        Then sum of nums[i..j] = prefixSum[j] - prefixSum[i-1].
        (where prefixSum[-1] = 0, i.e., the sum before the array starts.)

        So: subarraySum = currentPrefixSum - prefixSumBeforeStart.

        To MAXIMIZE this, we want prefixSumBeforeStart to be as SMALL
        as possible.

    Step 3: What does the "good" condition mean?

        |nums[i] - nums[j]| == k means:
            nums[i] = nums[j] - k    OR    nums[i] = nums[j] + k

        So when we're at position j with value x = nums[j], we need to
        find a previous position i where nums[i] was either (x - k)
        or (x + k).

    Step 4: Combining Steps 2 and 3.

        When we're at index j:
            - We know x = nums[j].
            - We want a previous index i where nums[i] = x-k or x+k.
            - Among all such i's, we want the one with the SMALLEST
              prefix sum before i (to maximize subarraySum).

        So we maintain a HashMap:
            key   = a value that appeared in nums
            value = the MINIMUM prefix sum seen just BEFORE that value

        When we encounter nums[j] = x:
            1. Check if (x - k) is in the map → if yes, we can form a
               good subarray. The sum = currentPrefixSum - map[x - k].
            2. Check if (x + k) is in the map → same logic.
            3. Update the map for x: store the minimum prefix sum
               seen before x (so future elements can pair with x).

    Step 5: Why store the MINIMUM prefix sum?

        subarraySum = currentPrefixSum - prefixSumBeforeStart

        currentPrefixSum is fixed (it's where we are now). To maximize
        the result, we subtract the smallest possible value. That's why
        we store the minimum.

        If the same value appeared at index 2 (prefixSum before it = 10)
        and index 7 (prefixSum before it = 3), we keep 3 because:
            currentPrefixSum - 3 > currentPrefixSum - 10

    Step 6: When do we update the map?

        BEFORE we add nums[j] to the running sum. Because the map
        stores "prefix sum before index i" — that means the sum of
        everything BEFORE nums[i], not including nums[i].

        So the order for each element x = nums[j] is:
            a) Record prefixSum[x] = min(prefixSum[x], currentSum)
               (currentSum has NOT yet included x)
            b) Add x to currentSum: currentSum += x
            c) Now check if (x-k) or (x+k) exist in the map.
               Use currentSum (which now INCLUDES x, i.e., includes
               the end of our subarray) minus the stored prefix sum
               to get the full subarray sum.

        Wait — looking at the code below, it does (a) then (b) then (c).
        Let's verify: after step (b), currentSum = sum from 0 to j.
        The map stores prefixSum before some earlier index i, so:
            currentSum - map[x±k] = sum from i to j. Correct ✓

    Dry Run (nums = [1, 5, 3, 4, 2], k = 3):
    ------------------------------------------

    Initially: map = {}, currentSum = 0

    j=0, x=1:
        map[1] doesn't exist → map[1] = 0  (currentSum before adding 1)
        currentSum = 0 + 1 = 1
        Check x-k = -2: not in map
        Check x+k = 4:  not in map
        map = {1: 0}

    j=1, x=5:
        map[5] doesn't exist → map[5] = 1
        currentSum = 1 + 5 = 6
        Check x-k = 2: not in map
        Check x+k = 8: not in map
        map = {1: 0, 5: 1}

    j=2, x=3:
        map[3] doesn't exist → map[3] = 6
        currentSum = 6 + 3 = 9
        Check x-k = 0: not in map
        Check x+k = 6: not in map
        map = {1: 0, 5: 1, 3: 6}

    j=3, x=4:
        map[4] doesn't exist → map[4] = 9
        currentSum = 9 + 4 = 13
        Check x-k = 1: FOUND! map[1] = 0
            subarraySum = 13 - 0 = 13 → subarray is [1,5,3,4], |1-4|=3 ✓
            maxSum = 13
        Check x+k = 7: not in map
        map = {1: 0, 5: 1, 3: 6, 4: 9}

    j=4, x=2:
        map[2] doesn't exist → map[2] = 13
        currentSum = 13 + 2 = 15
        Check x-k = -1: not in map
        Check x+k = 5: FOUND! map[5] = 1
            subarraySum = 15 - 1 = 14 → subarray is [5,3,4,2], |5-2|=3 ✓
            maxSum = max(13, 14) = 14
        map = {1: 0, 5: 1, 3: 6, 4: 9, 2: 13}

    Answer: 14  ✓

    Complexity Analysis:
    --------------------
    Time  : O(n) — single pass, each step is O(1) hashmap operations.
    Space : O(n) — hashmap stores at most n entries.

*/

class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        unordered_map<int, long long> prefixSum;
        long long currentSum = 0;
        long long maxSum = LLONG_MIN;

        for(int i=0; i<nums.size(); i++){

            int x = nums[i];
            int y1 = nums[i] - k;
            int y2 = nums[i] + k;
            
            // first update the prefix sum of x
            // prefix sum of x is prefix sum upto the previous element of x
            // hence prefixsum[x] = currentSum. See we have not yet done currentSum + x;
            if(prefixSum.find(x) == prefixSum.end())
                prefixSum[x] = currentSum;
            else
                prefixSum[x] = min(prefixSum[x], currentSum);
            
            // now update the current sum
            currentSum = currentSum + x;

            // now get the subarray sum between y and x
            if(prefixSum.find(y1) != prefixSum.end()){
                maxSum = max(maxSum, currentSum - prefixSum[y1]);
            }
            if(prefixSum.find(y2) != prefixSum.end()){
                maxSum = max(maxSum, currentSum - prefixSum[y2]);
            }
        }

        return maxSum == LLONG_MIN ? 0 : maxSum;
    }
};

int main() {
    Solution obj;
}
