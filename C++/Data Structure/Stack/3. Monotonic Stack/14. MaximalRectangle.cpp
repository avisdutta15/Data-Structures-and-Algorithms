#include <algorithm>
#include <iostream>
#include <climits>
#include <stack>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement: (LeetCode 85 - Maximal Rectangle)
    ------------------
    Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle
    containing only 1's and return its area.

    Examples:
    --------
    Input:
        ["1","0","1","0","0"],
        ["1","0","1","1","1"],
        ["1","1","1","1","1"],
        ["1","0","0","1","0"]
    Output: 6
    Explanation: The maximal rectangle is shown in row 2, cols 0-5... actually
    rows 1-2, cols 2-4: height 2, width 3, area = 6.

    Constraints:
    ------------
    - rows == matrix.length
    - cols == matrix[i].length
    - 1 <= rows, cols <= 200
    - matrix[i][j] is '0' or '1'

    Histogram Construction Example:
    --------------------------------
    Matrix:
        1 0 1 0 0
        1 0 1 1 1
        1 1 1 1 1
        1 0 0 1 0

    Row 0: heights = [1, 0, 1, 0, 0]   (just the first row)
    Row 1: heights = [2, 0, 2, 1, 1]   (col 0: was 1, still '1' → 2. col 1: '0' → reset to 0)
    Row 2: heights = [3, 1, 3, 2, 2]   (all '1' → increment each)
    Row 3: heights = [4, 0, 0, 3, 0]   (col 1,2,4 are '0' → reset to 0)

    At each row, we apply "Largest Rectangle in Histogram" on the current heights[].
    Row 2 gives the max: heights = [3,1,3,2,2] → largest rect area = 6 (height=2, width=3, cols 2-4)

    Time: O(R * C), Space: O(C)

    Approach 1 (Brute Force - O(R² * C)):
    --------------------------------------
    1. Build histogram heights[] row by row:
       - If matrix[i][j] == '1': heights[j]++
       - Else: heights[j] = 0
    2. For each row, for each bar in heights[], expand left/right to find max rectangle

    Time Complexity:
    Outer loop: R rows
    For each row: build histogram O(C) + brute force per bar O(C) × expand left/right O(C) worst case = O(C²)
    Total: R × (C + C²) = O(R × C²)

    Approach 2 (Histogram + PSE/NSE - O(R * C)):
    ---------------------------------------------
    1. Build histogram heights[] row by row:
       - If matrix[i][j] == '1': heights[j]++
       - Else: heights[j] = 0
    2. For each row, apply "Largest Rectangle in Histogram" using PSE + NSE.
    3. Track the global maximum area.
    
    Time Complexity:
    Outer loop: R rows
    For each row: build histogram O(C) + PSE pass O(C) + NSE pass O(C) + area calc O(C) = O(C)
    Total: R × (C + C + C + C) = O(R × C)
*/

// Solution 1: Brute Force O(R * C²)
// Build histogram row by row. For each row, brute force each bar by expanding left/right.
class Solution1 {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int rows = matrix.size(), cols = matrix[0].size();
        vector<int> heights(cols, 0);
        int maxArea = 0;

        for (int i = 0; i < rows; i++) {
            // Build histogram
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == '1')
                    heights[j]++;
                else
                    heights[j] = 0;
            }

            // Brute force largest rectangle in this histogram
            maxArea = max(maxArea, largestRectBrute(heights));
        }

        return maxArea;
    }

private:
    int largestRectBrute(vector<int>& heights) {
        int n = heights.size();
        int maxArea = 0;

        for (int i = 0; i < n; i++) {
            // Expand left: find PSE
            int left = i - 1;
            while (left >= 0 && heights[left] >= heights[i])
                left--;

            // Expand right: find NSE
            int right = i + 1;
            while (right < n && heights[right] >= heights[i])
                right++;

            // left and right are now at first smaller elements
            int width = right - left - 1;
            int area = heights[i] * width;
            maxArea = max(maxArea, area);
        }

        return maxArea;
    }
};

// Solution 2: Histogram + PSE/NSE O(R * C)
// Build histogram row by row. For each row, use monotonic stack to find
// PSE (left boundary) and NSE (right boundary) for each bar in O(C).
class Solution2 {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int rows = matrix.size(), cols = matrix[0].size();
        vector<int> heights(cols, 0);
        int maxArea = 0;

        for (int i = 0; i < rows; i++) {
            // Build histogram
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == '1')
                    heights[j]++;
                else
                    heights[j] = 0;
            }

            // Largest rectangle using PSE + NSE
            maxArea = max(maxArea, largestRectPSENSE(heights));
        }

        return maxArea;
    }

private:
    int largestRectPSENSE(vector<int>& heights) {
        int n = heights.size();
        vector<int> left(n);   // PSE index
        vector<int> right(n);  // NSE index
        stack<int> st;

        // Pass 1: Find PSE (Previous Smaller Element)
        for (int i = 0; i < n; i++) {
            while (!st.empty() && heights[st.top()] >= heights[i])
                st.pop();
            left[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }

        while (!st.empty()) st.pop();

        // Pass 2: Find NSE (Next Smaller Element)
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && heights[st.top()] >= heights[i])
                st.pop();
            right[i] = st.empty() ? n : st.top();
            st.push(i);
        }

        // Calculate max area
        int maxArea = 0;
        for (int i = 0; i < n; i++) {
            int width = right[i] - left[i] - 1;
            int area = heights[i] * width;
            maxArea = max(maxArea, area);
        }

        return maxArea;
    }
};


int main() {
    Solution1 brute;
    Solution2 optimal;

    vector<vector<char>> matrix = {
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    };

    cout << "Brute Force: " << brute.maximalRectangle(matrix) << endl;   // Expected: 6
    cout << "PSE + NSE:   " << optimal.maximalRectangle(matrix) << endl; // Expected: 6

    return 0;
}
