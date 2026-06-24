#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

/*
    https://www.youtube.com/watch?v=9ZbB397jU4k&list=PLgUwDviBIf0pMFMWuuvDNMAkoQFi-h0ZF&index=27&pp=iAQB

    Problem Statement:
    -----------------
    Write an efficient algorithm that searches for a value target in an m x n integer matrix matrix. 
    This matrix has the following properties:

    Integers in each row are sorted in ascending from left to right.
    Integers in each column are sorted in ascending from top to bottom.

    Examples:
    --------- 
    Input: matrix = [[1,  4, 7,11,15],
                     [2,  5, 8,12,19],
                     [3,  6, 9,16,22],
                     [10,13,14,17,24],
                     [18,21,23,26,30]], 
    target = 5
    Output: true
   

    Input: matrix = [[1,  4, 7,11,15],
                     [2,  5, 8,12,19],
                     [3,  6, 9,16,22],
                     [10,13,14,17,24],
                     [18,21,23,26,30]],   
    target = 20
    Output: false

    Constraints:
    ------------
    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 300
    -10^4 <= matrix[i][j], target <= 10^4
    All the integers in each row are sorted in ascending order.
    All the integers in each column are sorted in ascending order.


    Approach 1: Stair Case Search
    ------------------------------
    Start from the Top Right Corner:
    Begin at the top-right corner of the matrix (row = 0, col = n-1).

    Compare with Target:
    If the current element equals the target, return true.
    If the target is smaller, move left (col--).
    If the target is larger, move down (row++).

    Why this works:
    The key insight is that the matrix has a sorted property:
    - Rows are sorted left to right.
    - Columns are sorted top to bottom.
    Starting from the top-right corner allows us to make a binary decision at each step:
    - If we're smaller than target, we know all elements to the left in the same row are also smaller, so we go down.
    - If we're larger than target, we know all elements below in the same column are also larger, so we go left.

    Time Complexity: O(m + n)

    ---------------------------------

    WHY BINARY SEARCH IS NOT POSSIBLE?
    Binary search requires a single sorted array.
    Here, we have a 2D matrix where elements are sorted in two directions (rows and columns).
    We cannot treat the entire matrix as one sorted array because the elements aren't in a single sequence.
    For example, in the matrix:
    [
      [1,  4,  7, 11],
      [2,  5,  8, 12],
      [3,  6,  9, 16]
    ]
    The sequence 1 -> 4 -> 7 -> 11 -> 12 -> 16 is not sorted.
    Therefore, standard binary search on the flattened matrix won't work correctly.
*/

class Solution1 {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        int row = 0, col = cols - 1; // start from top right corner

        while (row < rows && col >= 0) {
            if (matrix[row][col] == target)
                return true;
            else if (target < matrix[row][col]) {
                col = col - 1;
            }
            else if (target > matrix[row][col]) {
                row = row + 1;
            }
        }
        return false;
    }
};

class Solution2 {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();

        int totalElements = m * n;

        int lo = 0, hi = totalElements - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;

            int row = mid / n;
            int col = mid % n;

            if (matrix[row][col] == target)
                return true;
            else if (matrix[row][col] < target)
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        return false;
    }
};

int main() {
    Solution1 obj;
    vector<vector<int>> A = {{1, 3, 5, 7}, 
                             {10, 11, 16, 20}, 
                             {23, 30, 34, 60}}; 
    cout << obj.searchMatrix(A, 16) << endl;

    return 0;
}
