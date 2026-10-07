#include <bits/stdc++.h>
using namespace std;

/*
    https://www.youtube.com/watch?v=9biz4kxyVh8
    
    Problem: 2106. Maximum Fruits Harvested After at Most K Steps (LeetCode Hard)
    ─────────────────────────────────────────────────────────────────────────────

    Fruits are planted along an infinite x-axis. You are given a 2D array fruits[]
    where fruits[i] = [position_i, amount_i] denotes amount_i fruits at position_i.
    fruits is sorted by position_i in ascending order.

    You start at position startPos. You can move left or right, and you can harvest
    all fruits at any position you visit. Return the maximum total fruits you can
    harvest within at most k steps.

    Examples:
    ---------
    Input:  fruits = [[2,8],[6,3],[8,6]], startPos = 5, k = 4
    Output: 9

    Input:  fruits = [[0,9],[4,1],[5,7],[6,2],[7,4],[10,9]], startPos = 5, k = 4
    Output: 14

    ════════════════════════════════════════════════════════════════════════
    APPROACH: Enumerate distance d, Binary Search + Prefix Sum
    ════════════════════════════════════════════════════════════════════════

    We enumerate how far we go in one direction (distance d), then use
    the remaining steps to go the other way.

    For each d from 0 to k/2:
        Case 1: Move LEFT by d steps first, then RIGHT
            - Go left d steps to (startPos - d), come back d steps, then go right
            - Total left+right steps used = 2*d, remaining = k - 2*d
            - Harvesting range: [startPos - d, startPos + (k - 2*d)]
            - i.e. i = startPos - d,  j = startPos + remain

        Case 2: Move RIGHT by d steps first, then LEFT
            - Go right d steps to (startPos + d), come back d steps, then go left
            - Total right+left steps used = 2*d, remaining = k - 2*d
            - Harvesting range: [startPos - (k - 2*d), startPos + d]
            - i.e. i = startPos - remain,  j = startPos + d

    For each case, use binary search to find which fruit indices fall in [i, j]:
        - left  = lower_bound(positions, i)   → first fruit at position >= i
        - right = upper_bound(positions, j)-1 → last fruit at position <= j

    Then use prefix sum to get total fruits in [left, right] in O(1).

    Time:  O(K/2 * log N) — enumerate d, binary search for each
    Space: O(N) — prefix sum and positions arrays

    ════════════════════════════════════════════════════════════════════════
*/

class Solution{
    public:
        int maxTotalFruits(vector<vector<int>> &fruits, int startPos, int k){
            int N = fruits.size();

            // Extract positions for binary search
            vector<int> positions(N);
            for(int i = 0; i < N; i++)
                positions[i] = fruits[i][0];

            // Build prefix sum over fruit amounts
            // prefixSum[i] = sum of fruits[0..i] (inclusive)
            // Total fruits in index range [l, r] = prefixSum[r] - (l > 0 ? prefixSum[l-1] : 0)
            vector<int> prefixSum(N, 0);
            prefixSum[0] = fruits[0][1];
            for(int i = 1; i < N; i++)
                prefixSum[i] = prefixSum[i-1] + fruits[i][1];

            int maxFruits = 0;

            // Enumerate d: the distance we travel in one direction before turning around.
            //
            // Why d ranges from 0 to k/2:
            //   When we go distance d in one direction and turn around, we walk d steps
            //   out and d steps back to startPos. That round trip costs 2*d steps.
            //   The remaining (k - 2*d) steps are spent going the other direction.
            //
            //   If d > k/2, then 2*d > k — the round trip alone exceeds our budget,
            //   leaving no steps for the other direction. So d can be at most k/2.
            //
            //   d = 0:   no turning, go entirely in one direction (all k steps one way)
            //   d = k/2: spend almost all steps on the round trip, barely any left for the other side
            for(int d = 0; d <= k/2; d++){
                int remain = k - 2 * d;  // remaining steps for the other direction

                // ──────────────────────────────────────────────────────
                // Case 1: Move LEFT by d, then RIGHT by remain
                // Harvest range: [startPos - d, startPos + remain]
                // ──────────────────────────────────────────────────────
                {
                    int i = startPos - d;           // leftmost position reachable
                    int j = startPos + remain;      // rightmost position reachable

                    // Find first fruit index with position >= i
                    int left = lower_bound(positions.begin(), positions.end(), i) - positions.begin();
                    // Find last fruit index with position <= j
                    int right = upper_bound(positions.begin(), positions.end(), j) - positions.begin() - 1;

                    if(left <= right){
                        int total = prefixSum[right] - (left > 0 ? prefixSum[left - 1] : 0);
                        maxFruits = max(maxFruits, total);
                    }
                }

                // ──────────────────────────────────────────────────────
                // Case 2: Move RIGHT by d, then LEFT by remain
                // Harvest range: [startPos - remain, startPos + d]
                // ──────────────────────────────────────────────────────
                {
                    int i = startPos - remain;      // leftmost position reachable
                    int j = startPos + d;            // rightmost position reachable

                    // Find first fruit index with position >= i
                    int left = lower_bound(positions.begin(), positions.end(), i) - positions.begin();
                    // Find last fruit index with position <= j
                    int right = upper_bound(positions.begin(), positions.end(), j) - positions.begin() - 1;

                    if(left <= right){
                        int total = prefixSum[right] - (left > 0 ? prefixSum[left - 1] : 0);
                        maxFruits = max(maxFruits, total);
                    }
                }
            }

            return maxFruits;
        }
};

int main(){
    Solution obj;

    vector<vector<int>> fruits1 = {{2, 8}, {6, 3}, {8, 6}};
    cout << "Max fruits: " << obj.maxTotalFruits(fruits1, 5, 4) << endl;  // 9

    vector<vector<int>> fruits2 = {{0, 9}, {4, 1}, {5, 7}, {6, 2}, {7, 4}, {10, 9}};
    cout << "Max fruits: " << obj.maxTotalFruits(fruits2, 5, 4) << endl;  // 14

    vector<vector<int>> fruits3 = {{0, 3}, {6, 4}, {8, 5}};
    cout << "Max fruits: " << obj.maxTotalFruits(fruits3, 3, 2) << endl;  // 0

    vector<vector<int>> fruits4 = {{0, 10}};
    cout << "Max fruits: " << obj.maxTotalFruits(fruits4, 0, 0) << endl;  // 10

    return 0;
}
