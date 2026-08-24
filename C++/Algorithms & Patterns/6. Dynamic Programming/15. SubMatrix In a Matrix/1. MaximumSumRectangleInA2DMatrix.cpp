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
    https://www.youtube.com/watch?v=yCQN096CwWM
    Problem Statement:
    ------------------
    Given a 2D matrix of integers, find the submatrix (contiguous rectangular region)
    with the maximum sum.

    Examples:
    --------
    Input:
         1   2  -1  -4
        -8   3   4   2
         3   8  10  -8

    Output: 29
    Explanation: Submatrix from row 0-2, col 1-2:
         2  -1
         3   4
         8  10
    Sum = 2 + (-1) + 3 + 4 + 8 + 10 = 26? Let me recompute...
    Actually col 1-2, rows 1-2: 3+4+8+10 = 25. With row 0: 2+(-1)+3+4+8+10 = 26.
    Checking all: the max is actually col 1-2, all rows = 2-1+3+4+8+10 = 26.

    Constraints:
    ------------
    - 1 <= rows, cols <= 100
    - -10^4 <= matrix[i][j] <= 10^4

    Approach :
    ----------
    Reduce 2D problem to 1D:
    1. Fix left column boundary.
    2. Expand right column boundary one at a time.
    3. Maintain a temp[] array where temp[i] = sum of row i from left to right column.
    4. Apply Kadane's algorithm on temp[] to find the best top-bottom boundary.

    This works because:
    - Fixing left/right gives us C² combinations.
    - For each, we compress the 2D sub-problem into a 1D array.
    - Kadane's finds the optimal contiguous subarray in O(R).

    All "find submatrix with property X" problems use this same framework:
    - Max sum → Kadane's
    - Sum = 0 → prefix sum hash map (prefix[j] == prefix[i])
    - Sum = k → prefix sum hash map (prefix[j] - prefix[i] == k)
    - Sum divisible by k → prefix sum mod k hash map
    - Equal 0s and 1s → convert 0→-1, then sum = 0

    Time: O(C² * R)
        outer for loop (0 -> cols)  -> C
            inner for loop (left -> cols) -> C
                for loop on rows -> R
                Kadene  -> R
        Total -> C.C.(R + R) = C².R
    Space: O(R)
*/

class Solution {
private:
    int kadane(vector<int>& arr) {
        int maxEndingHere = arr[0];
        int maxSoFar = arr[0];

        for (int i = 1; i < (int)arr.size(); i++) {
            maxEndingHere = max(arr[i], maxEndingHere + arr[i]);
            maxSoFar = max(maxSoFar, maxEndingHere);
        }

        return maxSoFar;
    }

public:
    int maxSumRectangle(vector<vector<int>>& matrix) {
        int rows = matrix.size(), cols = matrix[0].size();
        int maxSum = INT_MIN;

        // Fix left column
        for (int left = 0; left < cols; left++) {
            // temp[i] = sum of matrix[i][left..right]
            vector<int> temp(rows, 0);

            // Expand right column
            for (int right = left; right < cols; right++) {
                // Add current right column to temp
                for (int i = 0; i < rows; i++) {
                    temp[i] += matrix[i][right];
                }

                // Apply Kadane's on temp to find best top-bottom
                int kadaneMax = kadane(temp);
                maxSum = max(maxSum, kadaneMax);
            }
        }

        return maxSum;
    }
};


int main() {
    Solution obj;

    vector<vector<int>> matrix = {
        { 1,  2, -1, -4},
        {-8,  3,  4,  2},
        { 3,  8, 10, -8}
    };

    cout << "Max Sum Rectangle: " << obj.maxSumRectangle(matrix) << endl; // Expected: 26

    return 0;
}
