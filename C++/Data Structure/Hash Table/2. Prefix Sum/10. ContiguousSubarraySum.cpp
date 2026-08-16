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
    Problem Statement:
    ------------------
    Given an integer array nums and an integer k, return true if nums has a
    good subarray. A good subarray is a subarray where:
      - its length is at least 2, AND
      - the sum of its elements is a multiple of k.

    Examples:
    ---------
    Input:  nums = [23, 2, 4, 6, 7], k = 6
    Output: true
    Explanation: [2, 4] is a subarray of size 2 whose sum is 6, a multiple of 6.

    Input:  nums = [23, 2, 6, 4, 7], k = 6
    Output: true
    Explanation: [23, 2, 6, 4, 7] sums to 42, which is a multiple of 6.

    Input:  nums = [23, 2, 6, 4, 7], k = 13
    Output: false

    Constraints:
    ------------
    - 1 <= nums.length <= 10^5
    - 0 <= nums[i] <= 10^9
    - 0 <= k <= 2^31 - 1

    Derivation:
    -----------
    Same idea as Subarray Sum Divisible by K, but with ONE extra constraint:
    the subarray must have length >= 2.

    sum(i, j) = prefixSum[j] - prefixSum[i-1]

    For sum(i, j) to be divisible by K:
        prefixSum[j] % K == prefixSum[i-1] % K

    For length >= 2:
        j - i + 1 >= 2  →  j - (i-1) >= 2  →  j >= i-1 + 2
        So the stored "i-1" index must be at least 2 positions before j.
        i.e., i-1 <= j - 2

    Key difference from Subarray Sum Divisible by K:
    - In "Divisible by K": we count ALL pairs with same remainder.
    - In "Continuous Subarray Sum": we only care if there EXISTS a pair with
      same remainder where the indices are at least 2 apart.

    Strategy:
    - Store the FIRST (earliest) index where each remainder was seen.
    - At index j, if remainder rem was first seen at index prev, check if j - prev >= 2.
    - We only store the first occurrence because if it doesn't satisfy the distance,
      a later occurrence (closer to j) definitely won't either.

    Worked Example:
    ---------------
    nums = [23, 2, 4, 6, 7], K = 6

    Index:        0    1    2    3    4
    nums:        23    2    4    6    7
    prefixSum:   23   25   29   35   42

    Remainders (% 6):
    prefixSum[-1] = 0   → rem 0, store index -1 in map
    prefixSum[0]  = 23  → rem 5, first time, store index 0
    prefixSum[1]  = 25  → rem 1, first time, store index 1
    prefixSum[2]  = 29  → rem 5, seen before at index 0!
                          Distance: j - prev = 2 - 0 = 2 >= 2 ✓
                          → subarray(1, 2): sum = 2 + 4 = 6, divisible by 6 ✓
                          → return true

    Why distance >= 2?
    If prefixSum[j] % K == prefixSum[prev] % K, the subarray is (prev+1, j).
    Length = j - (prev+1) + 1 = j - prev.
    We need length >= 2, so j - prev >= 2.

    Why ((sum % k) + k) % k?
    ------------------------
    In C++, the % operator can return negative remainders when the left operand is negative.

    -7 % 5 = -2    (in C++)
    But we need remainders in the range [0, K-1] for our hashmap to group them correctly. -2 and 3 should be the same group (both are "equivalent mod 5"), but they'd map to different keys.

    The formula ((sum % k) + k) % k fixes this:

    Step by step for sum = -7, k = 5:

        sum % k         = -7 % 5  = -2
        (sum % k) + k   = -2 + 5  = 3
        ((sum % k) + k) % k = 3 % 5 = 3   ✓ (now in range [0, 4])
    
    Why the final % k again? For when sum is already positive:
    sum = 7, k = 5:

        sum % k         = 7 % 5  = 2
        (sum % k) + k   = 2 + 5  = 7
        ((sum % k) + k) % k = 7 % 5 = 2   ✓ (without the final %k, we'd get 7, which is wrong)
    TL;DR:
        + k handles the negative case (shifts it to positive)
        The outer % k handles the positive case (brings it back into [0, k-1] after adding k)


    Approach:
    ---------
    1. ContiguousSolution1: Return true/false if such a subarray exists
       - Store first occurrence of each remainder.
       - Time: O(n), Space: O(min(n, k))

    2. ContiguousSolution2: Find all such subarrays (length >= 2, sum divisible by K)
       - Store all indices for each remainder, pair those with distance >= 2.
       - Time: O(n + number of valid subarrays), Space: O(n)
*/

// Solution 1: Check if a contiguous subarray of length >= 2 exists with sum divisible by K
class ContiguousSolution1 {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        // Map: remainder → first index where this remainder was seen
        // Store "i-1" index (the prefix sum index)
        unordered_map<int, int> firstOccurrence;

        // prefixSum[-1] = 0, remainder 0, at index -1
        firstOccurrence[0] = -1;

        int sum = 0;

        for (int j = 0; j < (int)nums.size(); j++) {
            sum += nums[j];  // sum = prefixSum[j]

            // Get non-negative remainder
            int rem = (k == 0) ? sum : ((sum % k) + k) % k;

            // Check if this remainder was seen before
            if (firstOccurrence.count(rem)) {
                int prev = firstOccurrence[rem];
                // Subarray is (prev+1, j), length = j - prev
                // Need length >= 2, i.e., j - prev >= 2
                if (j - prev >= 2) {
                    return true;
                }
                // Don't update — keep the earliest index for maximum distance
            } else {
                // First time seeing this remainder, store current index
                firstOccurrence[rem] = j;
            }
        }

        return false;
    }
};

// Solution 2: Find all contiguous subarrays of length >= 2 with sum divisible by K
class ContiguousSolution2 {
public:
    vector<pair<int, int>> findContiguousSubarrays(vector<int>& nums, int k) {
        // Map: remainder → list of indices where prefixSum had this remainder
        unordered_map<int, vector<int>> remainderIndices;

        // prefixSum[-1] = 0, remainder 0, at index -1
        remainderIndices[0].push_back(-1);

        vector<pair<int, int>> result;
        int sum = 0;

        for (int j = 0; j < (int)nums.size(); j++) {
            sum += nums[j];  // sum = prefixSum[j]

            // Get non-negative remainder
            int rem = (k == 0) ? sum : ((sum % k) + k) % k;

            // Every stored index prev with same remainder where j - prev >= 2
            // gives a valid subarray (prev+1, j) of length >= 2
            if (remainderIndices.count(rem)) {
                for (int prev : remainderIndices[rem]) {
                    if (j - prev >= 2) {
                        result.push_back({prev + 1, j});
                    }
                }
            }

            // Store current index
            remainderIndices[rem].push_back(j);
        }

        return result;
    }
};

int main() {
    vector<int> nums = {4, 5, 0, -2, -3, 1};
    int k = 5;

    SubarraySolution1 s1;
    cout << "Count of subarrays divisible by " << k << ": " << s1.subarraysDivByK(nums, k) << endl;

    SubarraySolution2 s2;
    vector<pair<int, int>> subarrays = s2.findSubarraysDivByK(nums, k);
    cout << "\nAll subarrays with sum divisible by " << k << ":" << endl;
    for (auto& [start, end] : subarrays) {
        cout << "  [" << start << ", " << end << "] -> sum = ";
        int s = 0;
        for (int i = start; i <= end; i++) s += nums[i];
        cout << s << endl;
    }

    // --- Continuous Subarray Sum ---
    vector<int> nums2 = {23, 2, 4, 6, 7};
    int k2 = 6;
    ContiguousSolution1 cs1;
    cout << "\nContiguous subarray sum (exists?): " << (cs1.checkSubarraySum(nums2, k2) ? "true" : "false") << endl;

    ContiguousSolution2 cs2;
    vector<pair<int, int>> contSubarrays = cs2.findContiguousSubarrays(nums2, k2);
    cout << "All contiguous subarrays (length >= 2) with sum divisible by " << k2 << ":" << endl;
    for (auto& [start, end] : contSubarrays) {
        cout << "  [" << start << ", " << end << "] -> sum = ";
        int s = 0;
        for (int i = start; i <= end; i++) s += nums2[i];
        cout << s << endl;
    }

    return 0;
}
