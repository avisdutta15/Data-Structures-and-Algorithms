#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

/*
    https://www.youtube.com/watch?v=nGGp5XBzC4g&t=95s

    Problem Statement:
    -----------------
    A peak element in a 2D grid is an element that is strictly greater than all of its adjacent neighbors 
    to the left, right, top, and bottom.
    Given a 0-indexed m x n matrix mat where no two adjacent cells are equal, find any peak element mat[i][j] 
    and return the length 2 array [i,j].
    You may assume that the entire matrix is surrounded by an outer perimeter with the value -1 in each cell.
    You must write an algorithm that runs in O(m log(n)) or O(n log(m)) time.

    Examples:
    --------- 
    Input: mat = [[1,4],
                  [3,2]]
    Output: [0,1]
    Explanation: Both 3 and 4 are peak elements so [1,0] and [0,1] are both acceptable answers.

    Input: mat = [[10,20,15],
                  [21,30,14],
                  [7,16,32]]
    Output: [1,1]
    Explanation: Both 30 and 32 are peak elements so [1,1] and [2,2] are both acceptable answers.

    Constraints:
    ------------
    m == mat.length
    n == mat[i].length
    1 <= m, n <= 500
    1 <= mat[i][j] <= 10^5
    No two adjacent cells are equal.


    Approach 1: 
    ------------
    Traverse all the elements and find the element which is greater than all of its adjacent neighbors.
    Time Complexity: O(N*M)

    Approach 2:
    -----------
    Use Binary Search
    1. Apply binary search on cols (start = 0, end = last_col)
    2. Get the mid col
    3. Find the row index of the max element in the mid col
    4. Get the left and right element of the max row index. If mid is in boundary cols left or right will be +INF
    5. If left < maxElement > right, then we found the peak element
    6. If left > maxElement, search in left half        (peak element might be on left)
    7. If right > maxElement, search in right half      (peak element might be on right)
    8. Return the peak element

    Time Complexity: O(N*LogM)
    
*/

class Solution {
private:
    int getRowIdxOfMaxElement(vector<vector<int>>& A, int midCol) {
        int rows = A.size();
        int maxElement = INT_MIN;
        int rowIdxOfMaxElement = -1;

        for (int row = 0; row < rows; row++) {
            if (A[row][midCol] > maxElement) {
                maxElement = A[row][midCol];
                rowIdxOfMaxElement = row;
            }
        }
        return rowIdxOfMaxElement;
    }
public:
    vector<int> findPeakGrid(vector<vector<int>>& A) {
        int rows = A.size();
        int cols = A[0].size();

        // Apply Binary Search on cols
        int lo = 0;
        int hi = cols - 1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;

            // Find the row index of the max element in the mid col
            int rowIdxOfMaxElement = getRowIdxOfMaxElement(A, mid);

            // Get the left and right element of the max row index
            int left = mid == 0 ? INT_MIN : A[rowIdxOfMaxElement][mid - 1];
            int right = mid == cols - 1 ? INT_MIN : A[rowIdxOfMaxElement][mid + 1];

            // If left < maxElement > right, then we found the peak element
            if (left < A[rowIdxOfMaxElement][mid] && A[rowIdxOfMaxElement][mid] > right)
                return { rowIdxOfMaxElement, mid };
            else if (left > A[rowIdxOfMaxElement][mid])
                hi = mid - 1;
            else
                lo = mid + 1;
        }
        return { -1, -1 };
    }
};

int main() {
    Solution obj;
    vector<vector<int>> A = { 
                              {10,20,15}, 
                              {21,30,14}, 
                              {7,16,32} 
                            };

    auto coords = obj.findPeakGrid(A);
    cout<<A[coords[0]][coords[1]]<<" ";

    return 0;
}
