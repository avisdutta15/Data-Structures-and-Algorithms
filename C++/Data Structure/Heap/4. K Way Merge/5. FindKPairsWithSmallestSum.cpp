#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;

/*
    https://www.youtube.com/watch?v=nhDri0thuPY

    Problem Statement:
    ------------------
    LeetCode 373 - Find K Pairs with Smallest Sums

    You are given two integer arrays `nums1` and `nums2` sorted in
    ascending order, and an integer `k`. Return the k pairs (u, v)
    with the smallest sums, where u is from nums1 and v is from nums2.

    Examples:
    ---------

    Example 1:
        Input:  nums1 = [1,7,11], nums2 = [2,4,6], k = 3
        Output: [[1,2],[1,4],[1,6]]
        Explanation:
            All possible sums (virtual matrix):
                      2    4    6
                1  [  3    5    7 ]
                7  [  9   11   13 ]
               11  [ 13   15   17 ]
            3 smallest: (1,2)=3, (1,4)=5, (1,6)=7

    Example 2:
        Input:  nums1 = [1,1,2], nums2 = [1,2,3], k = 2
        Output: [[1,1],[1,1]]

    Example 3:
        Input:  nums1 = [1,2], nums2 = [3], k = 3
        Output: [[1,3],[2,3]]
        Explanation: Only 2 pairs exist, return both.

    Constraints:
    ------------
    - 1 <= nums1.length, nums2.length <= 10^5
    - -10^9 <= nums1[i], nums2[i] <= 10^9
    - nums1 and nums2 are sorted in ascending order.
    - 1 <= k <= 10^4
    - k <= nums1.length * nums2.length

    Approach: Min-Heap (K-way Merge on Virtual Matrix)
    ---------------------------------------------------

    Intuition:
    ----------
    Imagine a virtual matrix where matrix[i][j] = nums1[i] + nums2[j]:

              nums2 →  2    4    6
    nums1 ↓
        1           [  3    5    7 ]   ← row 0
        7           [  9   11   13 ]   ← row 1
       11           [ 13   15   17 ]   ← row 2

    Each ROW is sorted (because nums2 is sorted).
    Each COLUMN is sorted (because nums1 is sorted).

    Finding k smallest sums = finding k smallest values in this matrix.
    This is exactly the "Merge K Sorted Lists" pattern:
        - Each row is a sorted list.
        - Start with the first element of each row (col=0) in the heap.
        - Pop smallest, push next element from the same row (col+1).
        - Stop after k pops.

    Why only push col=0 initially?
    -------------------------------
    For each row, the smallest sum is at col=0 (since nums2 is sorted).
    We don't need to consider col=1 until col=0 has been popped.
    This keeps the heap small — at most min(k, rows) elements.

    Optimization: limit initial pushes to k rows.
    ------------------------------------------------
    If k < rows, we only need the first k rows. Rows beyond k can't
    contribute to the k smallest pairs (their first element is already
    larger than the first k rows' first elements, and we only need k
    total results). Hence: pq.size() < k in the init loop.

    Dry Run (nums1=[1,7,11], nums2=[2,4,6], k=3):
    ------------------------------------------------

    Heap init: push col=0 of each row (up to k=3 rows)
        (3, r=0,c=0), (9, r=1,c=0), (13, r=2,c=0)

    Pop (3, r=0,c=0) → result=[(1,2)].   Push (5, r=0,c=1).
    Pop (5, r=0,c=1) → result=[(1,2),(1,4)].  Push (7, r=0,c=2).
    Pop (7, r=0,c=2) → result=[(1,2),(1,4),(1,6)].  k=3, done.

    Result: [[1,2],[1,4],[1,6]] ✓

    Connection to other problems:
    ------------------------------
    LC 23  (Merge K Sorted Lists):  K linked lists → merge
    LC 378 (Kth Smallest in Matrix): same virtual matrix, find kth
    LC 373 (This problem):          same pattern, find k smallest

    Complexity Analysis:
    --------------------
    Time:  O(k log k) — at most k pops, each O(log k). Initial pushes
                         are min(k, N) which is at most k.
    Space: O(k) — heap holds at most k elements.

*/



class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        //          nums2 ->
        // nums1  
        //   |
        //   V

        int rows = nums1.size();
        int cols = nums2.size();

        priority_queue<pair<int, pair<int, int>>
        , vector<pair<int, pair<int, int>>>
        , greater<pair<int, pair<int, int>>>> pq;   //min-heap

        for (int row = 0; row < nums1.size() && pq.size() < k; row++) {
            int sum = nums1[row] + nums2[0];
            pq.push({ sum, {row, 0} });
        }

        vector<vector<int>> result;
        while (!pq.empty() && result.size() < k) {
            auto [sum, cellInfo] = pq.top();
            pq.pop();

            int row = cellInfo.first;
            int col = cellInfo.second;

            result.push_back({ nums1[row], nums2[col] });

            if (col + 1 < cols) {
                pq.push({ nums1[row] + nums2[col + 1], {row, col + 1} });
            }
        }

        return result;
    }
}; 

int main() {
    Solution obj;

    // Example 1
    vector<int> n1 = {1, 7, 11}, n2 = {2, 4, 6};
    auto result1 = obj.kSmallestPairs(n1, n2, 3);
    cout << "Example 1: ";
    for (auto& p : result1) cout << "[" << p[0] << "," << p[1] << "] ";
    cout << endl;
    // Expected: [1,2] [1,4] [1,6]

    // Example 2
    vector<int> n3 = {1, 1, 2}, n4 = {1, 2, 3};
    auto result2 = obj.kSmallestPairs(n3, n4, 2);
    cout << "Example 2: ";
    for (auto& p : result2) cout << "[" << p[0] << "," << p[1] << "] ";
    cout << endl;
    // Expected: [1,1] [1,1]

    // Example 3: k > total pairs
    vector<int> n5 = {1, 2}, n6 = {3};
    auto result3 = obj.kSmallestPairs(n5, n6, 3);
    cout << "Example 3: ";
    for (auto& p : result3) cout << "[" << p[0] << "," << p[1] << "] ";
    cout << endl;
    // Expected: [1,3] [2,3]

    return 0;
}