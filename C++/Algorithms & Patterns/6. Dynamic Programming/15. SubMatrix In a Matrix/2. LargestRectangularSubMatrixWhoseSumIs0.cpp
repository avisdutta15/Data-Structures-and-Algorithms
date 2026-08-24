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
    Problem Statement:
    ------------------
    Given a 2D matrix of integers, find the largest area rectangular sub-matrix
    whose sum is equal to 0.

    Examples:
    --------
    Input:
         1,  2, -1, -4
        -8,  3,  4,  2
         3,  8, 10, -8
         
    Output: Area = 4 (e.g., a 2x2 or 4x1 submatrix with sum 0)

    Input:
         9,  7, 16, 5
         1, -6, -7, 3
         1,  8,  7, 9
         7, -2,  0, 10

    Output: Area = 6 (submatrix rows 0-2, cols 1-2: 7+16+(-6)+(-7)+8+7 = 25? Need to verify)

    Constraints:
    ------------
    - 1 <= rows, cols <= 100
    - -10^4 <= matrix[i][j] <= 10^4

    Approach :
    ----------
    Same framework as Maximum Sum Rectangle:
    1. Fix left column boundary.
    2. Expand right column boundary.
    3. Maintain temp[] where temp[i] = sum of row i from left to right.
    4. Instead of Kadane's, find the LONGEST SUBARRAY WITH SUM 0 in temp[].

    Finding longest subarray with sum 0:
    - Compute prefix sums of temp[].
    - If prefix[j] == prefix[i], then temp[i..j-1] has sum 0.
    - Use hash map to store first occurrence of each prefix sum.
    - Track the longest such subarray (gives max height for this left/right).

    Area = width (right - left + 1) × height (longest subarray with sum 0).

    Time: O(C² * R), Space: O(R)
*/

class Solution {
private:
    // Returns length of longest subarray with sum 0
    int longestSubarrayWithSumZero(vector<int>& arr, int& startRow, int& endRow) {
        unordered_map<int, int> prefixMap; // prefix_sum → first index
        prefixMap[0] = -1; // empty prefix at index -1

        int prefixSum = 0;
        int maxLen = 0;

        for (int i = 0; i < (int)arr.size(); i++) {
            prefixSum += arr[i];

            if (prefixMap.find(prefixSum) != prefixMap.end()) {
                int len = i - prefixMap[prefixSum];
                if (len > maxLen) {
                    maxLen = len;
                    startRow = prefixMap[prefixSum] + 1;
                    endRow = i;
                }
            } else {
                prefixMap[prefixSum] = i;
            }
        }

        return maxLen;
    }

public:
    int maxAreaSubmatrixSumZero(vector<vector<int>>& matrix) {
        int rows = matrix.size(), cols = matrix[0].size();
        int maxArea = 0;

        // Fix left column
        for (int left = 0; left < cols; left++) {
            vector<int> temp(rows, 0);

            // Expand right column
            for (int right = left; right < cols; right++) {
                // Add current right column to temp
                for (int i = 0; i < rows; i++) {
                    temp[i] += matrix[i][right];
                }

                // Find longest subarray with sum 0 in temp
                int startRow = 0, endRow = 0;
                int height = longestSubarrayWithSumZero(temp, startRow, endRow);

                int width = right - left + 1;
                int area = height * width;
                maxArea = max(maxArea, area);
            }
        }

        return maxArea;
    }
};


int main() {
    Solution obj;

    vector<vector<int>> matrix = {
        { 1,  2,  3},
        {-3, -2, -1},
        { 1,  7,  5}
    };

    // Rows 0-1, cols 0-2: (1+2+3) + (-3-2-1) = 6 + (-6) = 0, area = 2*3 = 6
    cout << "Max Area (sum=0): " << obj.maxAreaSubmatrixSumZero(matrix) << endl; // Expected: 6

    return 0;
}
