#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

/*

    https://youtu.be/JXU4Akft7yk?list=PLgUwDviBIf0pMFMWuuvDNMAkoQFi-h0ZF

    Problem Statement:
    -----------------
    You are given an m x n integer matrix matrix with the following two properties:

    Each row is sorted in non-decreasing order.
    The first integer of each row is greater than the last integer of the previous row.
    Given an integer target, return true if target is in matrix or false otherwise.

    You must write a solution in O(log(m * n)) time complexity.

    Examples:
    ---------
    Input: matrix = [[1,3,5,7],
                     [10,11,16,20],
                     [23,30,34,60]
                    ], target = 3
    Output: true

    Input: matrix = [[1,3,5,7],
                     [10,11,16,20],
                     [23,30,34,60]], target = 13
    Output: false

    Constraints:
    ------------
    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 100
    -10^4 <= matrix[i][j], target <= 10^4

   
    Approach 1: Binary Search on the "virtual" 1D array formed by flattening the 2D matrix.
    ---------------------------------------------------------------------------------------
    Treat the 2D matrix as a 1D array of size m*n.
    Convert between 1D index and 2D coordinates:
        row = id / cols;
        col = id % cols;

    Why id / cols and id % cols?
    id / cols (Division): Calculates the Row. It finds how many full rows fit into the sequential index, dropping any remainder.
    id % cols (Modulo): Calculates the Column. It uses the remainder of the division to tell you how far into the current row you are
    
    Consider a 3x4 matrix (m=3, n=4). Total elements = 12.

    Indices:[0  1  2  3]
            [4, 5, 6, 7]
            [8, 9, 10,11]

    Time Complexity: O(log(m*n))

    Approach 2: Stair Case Search
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
*/

class Solution1 {
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

class Solution2 {
public:
    /*
    

    */
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


int main() {
    Solution1 obj;
    vector<vector<int>> A = {{1, 3, 5, 7}, 
                             {10, 11, 16, 20}, 
                             {23, 30, 34, 60}}; 
    cout << obj.searchMatrix(A, 16) << endl;

    return 0;
}
