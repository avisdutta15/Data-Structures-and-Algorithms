#include <algorithm>
#include <iostream>
#include <climits>
#include <stack>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement: (LeetCode 42 - Trapping Rain Water)
    ------------------
    Given n non-negative integers representing an elevation map where the width of
    each bar is 1, compute how much water it can trap after raining.

    Examples:
    --------
    Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
    Output: 6

    Input: height = [4,2,0,3,2,5]
    Output: 9

    Constraints:
    ------------
    - n == height.length
    - 1 <= n <= 2 * 10^4
    - 0 <= height[i] <= 10^5

    Core Formula:
    -----------------------------------
    Water above bar i = min(maxLeft, maxRight) - height[i]
    where maxLeft  = tallest bar to the left (including i)
          maxRight = tallest bar to the right (including i)

    ==========================================================================
    Approach 1: Brute Force - O(N²) time, O(1) space
    ==========================================================================
    For each bar i, scan left to find maxLeft, scan right to find maxRight.
    Water at i = min(maxLeft, maxRight) - height[i].

    ==========================================================================
    Approach 2: Prefix Max Arrays - O(N) time, O(N) space
    ==========================================================================
    Precompute leftMax[] (running max from left) and rightMax[] (running max from right).
    Then water at i = min(leftMax[i], rightMax[i]) - height[i].

    Example:
        height   = [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
        leftMax  = [0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3]
        rightMax = [3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 1]
        water    = [0, 0, 1, 0, 1, 2, 1, 0, 0, 1, 0, 0] = 6

    ==========================================================================
    Approach 3: Two Pointers - O(N) time, O(1) space (OPTIMAL)
    ==========================================================================

    Intuition:
    ----------
    From Approach 2, water at bar i = min(leftMax[i], rightMax[i]) - height[i].
    We need min(leftMax, rightMax). The key insight is:
    - We don't need to know BOTH leftMax and rightMax exactly.
    - We only need whichever is SMALLER (the bottleneck).

    How two pointers achieve this:
    - left pointer starts at 0, right pointer starts at n-1.
    - leftMax tracks max height seen from the left side so far.
    - rightMax tracks max height seen from the right side so far.
    - Update BOTH maxes at the start of each iteration.
    - Move the pointer whose max is SMALLER (that side is the bottleneck).

    Why does this work?
    - If lmax < rmax:
        The left side is the bottleneck. Water at left = lmax - height[l].
        Even though we don't know the true rightMax for position l,
        we know it's at least rmax which is > lmax. So lmax determines the water.
        Move l++ (this bar is done).

    - If lmax >= rmax:
        The right side is the bottleneck. Water at right = rmax - height[r].
        Same logic: the true leftMax for position r is at least lmax >= rmax.
        Move r-- (this bar is done).

    Why process l (not r) when lmax < rmax?
    ----------------------------------------
    At position l:
      - True leftMax = lmax (we've seen everything to the left ✓)
      - True rightMax = unknown, BUT >= rmax > lmax
      - So min(leftMax, rightMax) = lmax — GUARANTEED correct.
      - Water at l = lmax - height[l] ✓

    At position r:
      - True rightMax = rmax (we've seen everything to the right ✓)
      - True leftMax = UNKNOWN — could be lmax, or something BIGGER between l and r.
      - So min(leftMax, rightMax) = can't determine yet!
      - Water at r = NOT safe to compute.

    Example:  height = [2, 0, 0, 0, 9, 0, 3]
                        l                 r
              lmax=2, rmax=3. lmax < rmax.
              Position l: rightMax >= 3 > 2 → water = lmax - height[l] = 0 ✓ (safe)
              Position r: leftMax could be 9 (hidden between l and r)! Can't determine yet.

    Rule: We process the side whose max is SMALLER because that side's answer is
    fully determined. The other side might have unseen taller bars that we'll
    discover as we move inward.

    Trace Example:
    --------------
    height = [4, 2, 0, 3, 2, 5]
    l=0, r=5, lmax=0, rmax=0, ans=0

    Step 1: lmax=max(0,4)=4, rmax=max(0,5)=5. lmax<rmax → ans+=4-4=0. l=1.
    Step 2: lmax=max(4,2)=4, rmax=max(5,5)=5. lmax<rmax → ans+=4-2=2. l=2.
    Step 3: lmax=max(4,0)=4, rmax=max(5,5)=5. lmax<rmax → ans+=4-0=4. l=3.
    Step 4: lmax=max(4,3)=4, rmax=max(5,5)=5. lmax<rmax → ans+=4-3=1. l=4.
    Step 5: lmax=max(4,2)=4, rmax=max(5,5)=5. lmax<rmax → ans+=4-2=2. l=5.

    l == r → stop. Total = 0+2+4+1+2 = 9 ✓
*/

// ============================================================================
// Solution 1: Brute Force O(N²)
// ============================================================================
class Solution1 {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int totalWater = 0;

        for (int i = 0; i < n; i++) {
            int maxLeft = 0;
            for (int j = 0; j <= i; j++)
                maxLeft = max(maxLeft, height[j]);

            int maxRight = 0;
            for (int j = i; j < n; j++)
                maxRight = max(maxRight, height[j]);

            totalWater += min(maxLeft, maxRight) - height[i];
        }

        return totalWater;
    }
};

// ============================================================================
// Solution 2: Prefix Max Arrays O(N) time, O(N) space
// ============================================================================
class Solution2 {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n == 0) return 0;

        vector<int> leftMax(n), rightMax(n);

        leftMax[0] = height[0];
        for (int i = 1; i < n; i++)
            leftMax[i] = max(leftMax[i - 1], height[i]);

        rightMax[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; i--)
            rightMax[i] = max(rightMax[i + 1], height[i]);

        int totalWater = 0;
        for (int i = 0; i < n; i++)
            totalWater += min(leftMax[i], rightMax[i]) - height[i];

        return totalWater;
    }
};

// ============================================================================
// Solution 3: Two Pointers O(N) time, O(1) space (OPTIMAL)
// ============================================================================
class Solution3 {
public:
    int trap(vector<int>& height) {
        int l = 0, r = height.size() - 1;
        int leftMax = 0, rightMax = 0;
        int totalWater = 0;

        while (l < r) {
            leftMax = max(leftMax, height[l]);
            rightMax = max(rightMax, height[r]);

            if (leftMax < rightMax) {
                totalWater += leftMax - height[l];
                l++;
            } else {
                totalWater += rightMax - height[r];
                r--;
            }
        }

        return totalWater;
    }
};


int main() {
    Solution1 brute;
    Solution2 prefix;
    Solution3 twoPtr;

    vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

    cout << "Brute Force:    " << brute.trap(height) << endl;   // Expected: 6
    cout << "Prefix Max:     " << prefix.trap(height) << endl;  // Expected: 6
    cout << "Two Pointers:   " << twoPtr.trap(height) << endl;  // Expected: 6

    cout << endl;
    vector<int> height2 = {4, 2, 0, 3, 2, 5};
    cout << "Brute Force:    " << brute.trap(height2) << endl;   // Expected: 9
    cout << "Prefix Max:     " << prefix.trap(height2) << endl;  // Expected: 9
    cout << "Two Pointers:   " << twoPtr.trap(height2) << endl;  // Expected: 9

    return 0;
}
