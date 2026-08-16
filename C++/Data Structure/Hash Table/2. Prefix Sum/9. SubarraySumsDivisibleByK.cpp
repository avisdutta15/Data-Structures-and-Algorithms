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
    https://www.youtube.com/watch?v=7Xeorb721LQ
    Problem Statement:
    ------------------
    Given an integer array nums and an integer k, return the number of non-empty
    subarrays that have a sum divisible by k.

    Examples:
    ---------
    Input:  nums = [4, 5, 0, -2, -3, 1], k = 5
    Output: 7

    Input:  nums = [5], k = 9
    Output: 0

    Constraints:
    ------------
    - 1 <= nums.length <= 3 * 10^4
    - -10^4 <= nums[i] <= 10^4
    - 2 <= k <= 10^4

    Proof / Derivation:
    -------------------
    We want subarrays where sum(i, j) is divisible by K (where j > i),
    i.e., sum(i, j) % K == 0.

    Step 1: Express subarray sum using prefix sums:

        sum(i, j) = prefixSum[j] - prefixSum[i-1]

        (where prefixSum[k] = arr[0] + arr[1] + ... + arr[k],
         and prefixSum[-1] = 0 by convention)

    Step 2: For divisibility by K:

        sum(i, j) % K == 0
        (prefixSum[j] - prefixSum[i-1]) % K == 0

    Step 3: A difference of two numbers is divisible by K if and only if both
             numbers have the same remainder when divided by K:

        (a - b) % K == 0  ⟺  a % K == b % K

        Applying this:

        prefixSum[j] % K == prefixSum[i-1] % K

    Step 4: So subarray (i, j) has sum divisible by K if and only if
             prefixSum[j] and prefixSum[i-1] have the SAME REMAINDER when divided by K.

    Step 5: Therefore, for each index j, count how many previous prefix sums
             (at indices 0 to j-1, including the implicit prefixSum[-1] = 0) have
             the same remainder as prefixSum[j] — each one forms a valid subarray ending at j.

    Handling Negative Numbers:
    --------------------------
        int rem = ((sum % k) + k) % k;

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


    Worked Example:
    ---------------
    arr = [4, 5, 0, -2, -3, 1], K = 5

    Index:        0    1    2    3    4    5
    arr:          4    5    0   -2   -3    1
    prefixSum[i]: 4    9    9    7    4    5

    Also, prefixSum[-1] = 0 (implicit, before the array starts)

    Remainders (% 5):
    prefixSum[-1] = 0  → rem 0
    prefixSum[0]  = 4  → rem 4
    prefixSum[1]  = 9  → rem 4   ← matches prefixSum[0]
                                  → subarray(1,1): prefixSum[1] - prefixSum[0] = 9-4 = 5 ✓
    prefixSum[2]  = 9  → rem 4   ← matches prefixSum[0] and prefixSum[1]
                                  → subarray(1,2): prefixSum[2] - prefixSum[0] = 9-4 = 5 ✓
                                  → subarray(2,2): prefixSum[2] - prefixSum[1] = 9-9 = 0 ✓
    prefixSum[3]  = 7  → rem 2   ← no match
    prefixSum[4]  = 4  → rem 4   ← matches prefixSum[0], [1], [2]
                                  → subarray(1,4): prefixSum[4] - prefixSum[0] = 4-4 = 0 ✓
                                  → subarray(2,4): prefixSum[4] - prefixSum[1] = 4-9 = -5 ✓
                                  → subarray(3,4): prefixSum[4] - prefixSum[2] = 4-9 = -5 ✓
    prefixSum[5]  = 5  → rem 0   ← matches prefixSum[-1]
                                  → subarray(0,5): prefixSum[5] - prefixSum[-1] = 5-0 = 5 ✓

    Total valid subarrays = 7

    Approach:
    ---------
    1. SubarraySolution1: Count subarrays with sum divisible by K
       - Use a hashmap to store count of each remainder seen so far.
       - For each j, add remainderCount[rem] to the answer.
       - Time: O(n), Space: O(k)

    2. SubarraySolution2: Find and print all such subarrays
       - Use a hashmap to store list of indices where each remainder occurred.
       - For each j, every stored index prev with same remainder gives subarray (prev+1, j).
       - Time: O(n + number of valid subarrays), Space: O(n)
*/

// Solution 1: Count subarrays with sum divisible by K
class SubarraySolution1 {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        unordered_map<int, int> remainderCount;

        // prefixSum[-1] = 0 has remainder 0, count it
        remainderCount[0] = 1;

        int sum = 0;   // running prefixSum
        int count = 0;

        for (int j = 0; j < nums.size(); j++) {
            sum += nums[j];  // sum = prefixSum[j]

            // Get non-negative remainder (handles negative numbers)
            int rem = 0;
            if (sum < 0)
                rem = ((sum % k) + k) % k;
            else
                rem = sum % k;

            // How many previous prefixSum[i-1] have the same remainder?
            // Each one gives a valid subarray (i, j) where:
            //   sum(i, j) = prefixSum[j] - prefixSum[i-1], divisible by K
            count += remainderCount[rem];

            // Record this remainder for future indices
            remainderCount[rem]++;
        }

        return count;
    }
};

// Solution 2: Find and print all subarrays with sum divisible by K
class SubarraySolution2 {
public:
    vector<pair<int, int>> findSubarraysDivByK(vector<int>& nums, int k) {
        // Map: remainder → list of indices where prefixSum had this remainder
        // We store the index as "i-1", so when we match at j,
        // the subarray starts at (stored_index + 1) and ends at j
        unordered_map<int, vector<int>> remainderIndices;

        // prefixSum[-1] = 0, remainder 0, store index -1
        remainderIndices[0].push_back(-1);

        vector<pair<int, int>> result;
        int sum = 0;

        for (int j = 0; j < nums.size(); j++) {
            sum += nums[j];  // sum = prefixSum[j]

            // Get non-negative remainder
            int rem = ((sum % k) + k) % k;

            // Every stored index prev where prefixSum[prev] % K == rem
            // gives a valid subarray (prev+1, j) since:
            //   sum(prev+1, j) = prefixSum[j] - prefixSum[prev], divisible by K
            if (remainderIndices.find(rem) != remainderIndices.end()) {
                for (int prev : remainderIndices[rem]) {
                    result.push_back({prev + 1, j});
                }
            }

            // Store current index j as a potential "i-1" for future matches
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

    return 0;
}
