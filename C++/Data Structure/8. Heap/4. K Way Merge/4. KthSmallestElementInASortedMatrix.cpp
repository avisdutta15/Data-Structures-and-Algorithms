#include <iostream>
#include <queue>
#include <vector>
#include <tuple>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 378 - Kth Smallest Element in a Sorted Matrix

    Given an n x n matrix where each row and each column is sorted
    in ascending order, return the kth smallest element in the matrix.

    Note: it is the kth smallest element in sorted order, not the
    kth distinct element.

    Examples:
    ---------

    Example 1:
        Input:  matrix = [[1,  5,  9],
                          [10, 11, 13],
                          [12, 13, 15]], k = 8
        Output: 13
        Explanation:
            Sorted: [1, 5, 9, 10, 11, 12, 13, 13, 15]
                                              ^
                                          8th smallest

    Example 2:
        Input:  matrix = [[-5]], k = 1
        Output: -5

    Constraints:
    ------------
    - n == matrix.length == matrix[i].length
    - 1 <= n <= 300
    - -10^9 <= matrix[i][j] <= 10^9
    - Each row and column is sorted in ascending order.
    - 1 <= k <= n^2

    Three Approaches:
    -----------------

    Approach 1 — Max-Heap of size K: O(n^2 log k)
        Scan every element, maintain a max-heap of size k.
        Doesn't use the sorted property at all.

    Approach 2 — Min-Heap K-way Merge: O(k log n)
        Each row is a sorted list. Push first element of each row
        into a min-heap. Pop k times — kth pop is the answer.
        After popping (row, col), push (row, col+1) from same row.
        Same pattern as LC 23 (Merge K Sorted Lists) and LC 373
        (K Pairs with Smallest Sums).

    Approach 3 — Binary Search on Value: O(n log(max - min))
        Binary search on the ANSWER value, not on indices.
        For a guess `mid`, count how many elements are <= mid
        using a staircase walk from the bottom-left corner in O(n).
        If count < k, search higher. Otherwise, search lower.

    How the staircase count works:
    -------------------------------
    Start at bottom-left corner (row=n-1, col=0).
        - If matrix[row][col] <= target:
            The entire column above (including this cell) is <= target
            (because columns are sorted). Add (row+1) to count. Move right.
        - If matrix[row][col] > target:
            This cell is too big. Move up.

    Example: matrix = [[1,5,9],[10,11,13],[12,13,15]], target=13

        (2,0): 12 <= 13 → count += 3. Move right.  (col 0: 1,10,12 all <= 13)
        (2,1): 13 <= 13 → count += 3. Move right.  (col 1: 5,11,13)
        (2,2): 15 > 13  → Move up.
        (1,2): 13 <= 13 → count += 2. Move right.  (col 2: 9,13)
        Out of bounds. count = 3+3+2 = 8.

    Complexity Comparison:
    ----------------------
        Approach               Time                Space   Sorted property?
        Max-Heap (size k)      O(n^2 log k)        O(k)    No
        Min-Heap (K-way merge) O(k log n)          O(n)    Rows only
        Binary Search          O(n log(max-min))   O(1)    Rows + Columns

    k small  → K-way merge is fastest.
    k large  → Binary search is fastest.
    Simplest → Max-heap (but slowest).

*/

// =============================================================
// Approach 1: Max-Heap of size K
// Time: O(n^2 log k), Space: O(k)
// =============================================================

class Solution1 {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        // Max-heap: largest of the k smallest is always on top.
        // If a new element < top, it belongs in the top k — swap it in.
        priority_queue<int> maxHeap;

        for (auto& row : matrix) {
            for (int val : row) {
                maxHeap.push(val);
                // Evict the largest — it's not in the top k anymore
                if (maxHeap.size() > k)
                    maxHeap.pop();
            }
        }

        // Top of max-heap = kth smallest
        return maxHeap.top();
    }
};

// =============================================================
// Approach 2: Min-Heap K-way Merge
// Time: O(k log n), Space: O(n)
// =============================================================

class Solution2 {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();

        // Min-heap: {value, row, col}
        // Smallest value is always on top.
        priority_queue<
            tuple<int, int, int>,
            vector<tuple<int, int, int>>,
            greater<tuple<int, int, int>>
        > pq;

        // Push first element (col=0) of each row — the smallest in that row.
        for (int i = 0; i < n; i++) {
            pq.push({matrix[i][0], i, 0});
        }

        int result = 0;

        // Pop k times. The kth popped value is the answer.
        for (int i = 0; i < k; i++) {
            auto [val, row, col] = pq.top();
            pq.pop();
            result = val;

            // Push next element from the same row (col+1).
            // This is the next candidate from that "sorted list."
            if (col + 1 < n) {
                pq.push({matrix[row][col + 1], row, col + 1});
            }
        }

        return result;
    }
};

// =============================================================
// Approach 3: Binary Search on Value
// Time: O(n * log(max - min)), Space: O(1)
// =============================================================

class Solution3 {
private:
    // Count elements <= target using the staircase walk.
    // Start at bottom-left. Move right if <= target, up if > target.
    // Each "move right" adds an entire column's worth of valid elements.
    int countElementsLessOfEqualTo(vector<vector<int>>& matrix, int target, int n) {
        int count = 0;
        int row = n - 1;  // start at bottom-left
        int col = 0;

        while (row >= 0 && col < n) {
            if (matrix[row][col] <= target) {
                // Everything above in this column is also <= target
                // (column is sorted, and this is the biggest in the column)
                count += row + 1;
                col++;       // move right — try next column
            } else {
                row--;       // too big — move up to find smaller values
            }
        }

        return count;
    }

public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int lo = matrix[0][0];          // smallest possible value
        int hi = matrix[n - 1][n - 1];  // largest possible value
        
        int ans;
        
        // Binary search on the VALUE, not on indices.
        // Find the smallest value `mid` such that count(<= mid) >= k.
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            int count = countElementsLessOfEqualTo(matrix, mid, n);

            if (count >= k) {
                ans = mid;
                hi = mid - 1;   // enough elements, mid could be the answer
            }
            else {
                lo = mid + 1;   // too few elements <= mid, need a bigger value
            }   
        }

        return ans;
    }
};

int main() {
    // Example 1
    vector<vector<int>> matrix1 = {
        {1,  5,  9},
        {10, 11, 13},
        {12, 13, 15}
    };
    int k1 = 8;

    Solution1 s1;
    Solution2 s2;
    Solution3 s3;

    cout << "Example 1 (k=" << k1 << "):" << endl;
    cout << "  Max-Heap:     " << s1.kthSmallest(matrix1, k1) << endl;  // 13
    cout << "  K-way Merge:  " << s2.kthSmallest(matrix1, k1) << endl;  // 13
    cout << "  Binary Search:" << s3.kthSmallest(matrix1, k1) << endl;  // 13

    // Example 2: single element
    vector<vector<int>> matrix2 = {{-5}};
    cout << "Example 2 (k=1): " << s3.kthSmallest(matrix2, 1) << endl;  // -5

    // Example 3: k=1 (smallest element)
    cout << "Example 3 (k=1): " << s3.kthSmallest(matrix1, 1) << endl;  // 1

    // Example 4: k=n^2 (largest element)
    cout << "Example 4 (k=9): " << s3.kthSmallest(matrix1, 9) << endl;  // 15

    return 0;
}
