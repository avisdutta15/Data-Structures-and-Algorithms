#include <bits/stdc++.h>
using namespace std;

/*
    https://www.youtube.com/watch?v=qpgqhp_9d1s&t=402s&pp=ygUPayBzdW0gcGFydGl0aW9u
    
    Problem: K Sum Partition / Partition to K Equal Sum Subsets (LeetCode 698)
    ──────────────────────────────────────────────────────────────────────────

    Problem Statement:
    ------------------
    Given an integer array nums and an integer k, return true if it is possible
    to divide this array into k non-empty subsets whose sums are all equal.

    Examples:
    ---------
    Input:  nums = [4, 3, 2, 3, 5, 2, 1], k = 4
    Output: true
    Explanation: [5], [1,4], [2,3], [2,3] all sum to 5.

    Input:  nums = [1, 2, 3, 4], k = 3
    Output: false

    Constraints:
    ------------
    - 1 <= k <= nums.length <= 16
    - 1 <= nums[i] <= 10^4

    ════════════════════════════════════════════════════════════════════════
    GENERALIZATION FROM 2-PARTITION AND 3-PARTITION
    ════════════════════════════════════════════════════════════════════════

    2-Partition: f(n, s1) — 2D — each element goes to S1 or S2(leftover)
    3-Partition: f(n, s1, s2) — 3D — each element goes to S1, S2, or S3(leftover)
    K-Partition: f(n, s1, s2, ..., s_{k-1}) — K dimensions!

    For K-Partition with the DP approach, we'd need a K-dimensional table which
    is impractical for large K. Instead, we use BACKTRACKING.

    ════════════════════════════════════════════════════════════════════════
    APPROACH: Backtracking
    ════════════════════════════════════════════════════════════════════════

    Maintain K buckets, each must reach target = totalSum / k.
    For each element, try placing it in each of the K buckets.
    If a bucket's sum would exceed target, skip it.
    If all elements are placed and all buckets hit target → return true.

    Optimizations:
    1. Sort descending — larger elements first, prunes earlier.
    2. If a bucket has the same sum as another bucket we already tried and
       failed, skip it (avoid duplicate work).
    3. If the largest element > target, impossible.

    Pre-checks:
    - totalSum % k != 0 → impossible
    - max(nums) > target → impossible

    Time Complexity: O(K^N) worst case, but pruning makes it much faster.
    Space Complexity: O(N) for recursion stack + O(K) for bucket sums.

    ════════════════════════════════════════════════════════════════════════
    RECURRENCE (Backtracking)
    ════════════════════════════════════════════════════════════════════════

    f(index, buckets[]) = can we place elements A[index..N-1] into K buckets
                          such that each bucket sums to target?

    Base case:
        f(N, buckets) = true   (all elements placed, buckets are valid)
                        — we only reach here if no bucket exceeded target

    Recurrence (for element at 'index'):
        For each bucket b from 0 to K-1:
            if buckets[b] + A[index] <= target:
                buckets[b] += A[index]
                if f(index + 1, buckets) == true: return true
                buckets[b] -= A[index]    // backtrack

            // Pruning: skip duplicate bucket sums
            if buckets[b] == 0: break
                // If an empty bucket didn't work, no other empty bucket will either

        return false  (tried all buckets, none worked)

    ════════════════════════════════════════════════════════════════════════
    WHY BACKTRACKING INSTEAD OF DP?
    ════════════════════════════════════════════════════════════════════════

    - For K=2: states = (n, s1) → O(N × sum) — manageable
    - For K=3: states = (n, s1, s2) → O(N × sum²) — still OK
    - For K=4+: states = (n, s1, s2, s3, ...) → exponential dimensions

    Backtracking with pruning is more practical for general K.
    For small N (≤ 16), bitmask DP is also an option (discussed below).

    ════════════════════════════════════════════════════════════════════════
    ALTERNATIVE: Bitmask DP (for N ≤ 16)
    ════════════════════════════════════════════════════════════════════════

    State: dp[mask] = sum of elements selected by mask, modulo target.
    If we can fill buckets one by one (each time accumulating to exactly target),
    then a valid partition exists.

    dp[mask] = the sum of selected elements mod target, tracking whether
    all "completed" buckets hit exactly target.

    Time: O(N × 2^N), Space: O(2^N). Works for N ≤ 16.

    ════════════════════════════════════════════════════════════════════════
*/

class Solution{
    // ── Backtracking: try placing each element into one of K buckets ──
    bool canPartitionBacktrack(vector<int> &A, int index, vector<int> &buckets, int target){
        // Base case: all elements placed successfully
        if(index == (int)A.size())
            return true;

        for(int b = 0; b < (int)buckets.size(); b++){
            // Try placing A[index] in bucket b
            if(buckets[b] + A[index] <= target){
                buckets[b] += A[index];

                if(canPartitionBacktrack(A, index + 1, buckets, target))
                    return true;

                buckets[b] -= A[index];  // backtrack
            }

            // Pruning: if this bucket is empty and we couldn't place here,
            // then no other empty bucket will work either (they're identical)
            if(buckets[b] == 0)
                break;
        }

        return false;  // tried all buckets, none worked for this element
    }

    // ── Bitmask DP: O(N * 2^N) — for N ≤ 16 ──
    // dp[mask] = total sum of elements in mask, mod target
    // If at any point adding an element would exceed target within a bucket,
    // mark that mask as invalid (-1).
    bool canPartitionBitmask(vector<int> &A, int N, int target){
        int totalMasks = 1 << N;  // 2^N possible subsets
        vector<int> dp(totalMasks, -1);  // -1 means invalid

        dp[0] = 0;  // empty set has sum 0

        for(int mask = 0; mask < totalMasks; mask++){
            if(dp[mask] == -1) continue;  // invalid state, skip

            for(int i = 0; i < N; i++){
                // If element i is NOT already in this mask
                if((mask & (1 << i)) == 0){
                    int newMask = mask | (1 << i);

                    // dp[mask] is the current "bucket sum mod target"
                    // Adding A[i] shouldn't exceed target within current bucket
                    if(dp[mask] + A[i] <= target){
                        dp[newMask] = (dp[mask] + A[i]) % target;
                        // When sum hits target exactly, mod resets to 0
                        // meaning a new bucket starts filling
                    }
                }
            }
        }

        // If all elements can be used (full mask) and sum is valid
        return dp[totalMasks - 1] == 0;
    }

public:
    bool canPartitionKSubsets(vector<int> A, int k){
        int N = A.size();
        int sum = accumulate(A.begin(), A.end(), 0);

        // Pre-check: total sum must be divisible by k
        if(sum % k != 0)
            return false;

        int target = sum / k;

        // Pre-check: no single element can exceed the target
        if(*max_element(A.begin(), A.end()) > target)
            return false;

        // Sort descending — place larger elements first for better pruning
        sort(A.begin(), A.end(), greater<int>());

        // Approach 1: Backtracking
        vector<int> buckets(k, 0);
        return canPartitionBacktrack(A, 0, buckets, target);

        // Approach 2: Bitmask DP (uncomment for N ≤ 16)
        // return canPartitionBitmask(A, N, target);
    }
};


int main(){
    Solution obj;

    vector<int> A1 = {4, 3, 2, 3, 5, 2, 1};
    cout << (obj.canPartitionKSubsets(A1, 4) ? "Possible" : "Not Possible") << endl;  // Possible

    vector<int> A2 = {1, 2, 3, 4};
    cout << (obj.canPartitionKSubsets(A2, 3) ? "Possible" : "Not Possible") << endl;  // Not Possible

    vector<int> A3 = {3, 3, 3, 3, 3, 3};
    cout << (obj.canPartitionKSubsets(A3, 3) ? "Possible" : "Not Possible") << endl;  // Possible

    vector<int> A4 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    cout << (obj.canPartitionKSubsets(A4, 5) ? "Possible" : "Not Possible") << endl;  // Possible

    return 0;
}
