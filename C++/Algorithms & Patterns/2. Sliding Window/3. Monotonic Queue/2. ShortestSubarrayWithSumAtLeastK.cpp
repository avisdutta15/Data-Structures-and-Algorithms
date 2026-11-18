#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

/*
    Problem (LC 862. Shortest Subarray with Sum at Least K)
    -------
    Given an integer array nums (which CAN contain negatives) and an
    integer k, find the length of the shortest non-empty subarray with
    sum >= k. Return -1 if no such subarray exists.

    =========================================================================
    Approach — Min-Heap with Prefix Sums (Convention 1: P[0] = A[0])
    =========================================================================
    Convention 1 prefix sum:
        P[0] = nums[0]
        P[i] = nums[0] + nums[1] + ... + nums[i]

    Subarray sum:
        sum(nums[i..j]) = P[j] - P[i-1]    (when i > 0)
        sum(nums[0..j]) = P[j]              (edge case, no P[-1])

    Pair-search: for each j, find idx < j such that P[j] - P[idx] >= k.
        Subarray = nums[idx+1..j], length = j - idx.
    Edge case:  if P[j] >= k, subarray = nums[0..j], length = j + 1.

    Min-heap gives us the smallest P[idx] first. Once an idx forms a
    valid pair with j, any future j' > j would give a longer subarray
    with the same idx, so we pop it (consumed).

    Time:  O(n log n) — each index pushed/popped at most once, O(log n) each.
    Space: O(n) — prefix array + heap.
*/

class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int N = static_cast<int>(nums.size());
        vector<long long> PS(N, 0);

        // Build prefix sum array (Convention 1: P[0] = nums[0])
        PS[0] = nums[0];
        for (int i = 1; i < N; i++) {
            PS[i] = PS[i - 1] + nums[i];
        }

        // min-heap of {prefix_sum, index}
        priority_queue<pair<long long, int>,
                       vector<pair<long long, int>>,
                       greater<pair<long long, int>>> PQ;

        int ans = INT_MAX;

        for (int j = 0; j < N; j++) {
            //Edge case : PS[j] >= k -> subarray nums[0..j] — no P index to subtract
            if (PS[j] >= k) {
                ans = min(ans, j + 1);
            }

            // Try to form valid subarrays with the smallest prefix sums
            // Now try to cut a slice from the start of the array
            // to get a subarray whose sum >=K. Find the longest subarray from such subarrays
            // so that the resultant subarray that is left has sum >= k
            while (!PQ.empty() && PS[j] - PQ.top().first >= k) {
                auto [prefixSum, idx] = PQ.top();
                PQ.pop();  // consumed — future j' would only give longer subarrays
                ans = min(ans, j - idx);  // subarray nums[idx+1..j], length = j - idx [j-(idx+1)+1 = j - idx - 1 + 1 = j-i]
            }

            PQ.push({PS[j], j});
        }

        // if no such subarray exists then ans == INT_MAX, return -1
        return ans == INT_MAX ? -1 : ans;
    }
};

int main() {
    // Test case from the writeup
    // nums = [84, -37, 32, 40, 95], k = 167
    // Expected: 3  (subarray [32, 40, 95] sums to 167)
    vector<int> nums1 = {84, -37, 32, 40, 95};
    int k1 = 167;

    Solution s;
    int r1 = s.shortestSubarray(nums1, k1);
    cout << "Test 1: " << r1 << " (expected 3)" << endl;

    // Test case: all positive
    // nums = [1, 2, 3, 4, 5], k = 11
    // Expected: 3  (subarray [3, 4, 5] sums to 12)
    vector<int> nums2 = {1, 2, 3, 4, 5};
    int k2 = 11;
    int r2 = s.shortestSubarray(nums2, k2);
    cout << "Test 2: " << r2 << " (expected 3)" << endl;

    // Test case: no valid subarray
    // nums = [1, -1, 1, -1], k = 5
    // Expected: -1
    vector<int> nums3 = {1, -1, 1, -1};
    int k3 = 5;
    int r3 = s.shortestSubarray(nums3, k3);
    cout << "Test 3: " << r3 << " (expected -1)" << endl;

    // Test case: single element
    // nums = [5], k = 5
    // Expected: 1
    vector<int> nums4 = {5};
    int k4 = 5;
    int r4 = s.shortestSubarray(nums4, k4);
    cout << "Test 4: " << r4 << " (expected 1)" << endl;

    return 0;
}
