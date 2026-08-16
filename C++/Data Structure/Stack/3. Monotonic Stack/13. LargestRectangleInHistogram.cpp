#include <algorithm>
#include <iostream>
#include <climits>
#include <stack>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement:
    ------------------
    Given an array of integers heights representing the histogram's bar height where
    the width of each bar is 1, return the area of the largest rectangle in the histogram.

    Examples:
    --------
    Input: heights = [2, 1, 5, 6, 2, 3]
    Output: 10
    Explanation: The largest rectangle has area = 5 * 2 = 10 (bars at index 2 and 3).

    Input: heights = [2, 4]
    Output: 4

    Constraints:
    ------------
    - 1 <= heights.length <= 10^5
    - 0 <= heights[i] <= 10^4

    Approach 1 (Brute Force - O(N²)):
    ----------------------------------
    For each bar i, expand left and right while neighboring bars are >= heights[i].
    Width = right - left + 1. Area = heights[i] * width.

    Problem: For each bar we scan left and right → O(N) per bar → O(N²) total.

    Approach 2 (PSE + NSE using stacks - O(N)):
    --------------------------------------------
    For each bar i, we need:
    - left[i] = index of Previous Smaller Element (PSE) → left boundary
    - right[i] = index of Next Smaller Element (NSE) → right boundary

    Width that bar i can span = right[i] - left[i] - 1
    Area = heights[i] * width

    If no PSE exists, left[i] = -1 (can extend to the start).
    If no NSE exists, right[i] = n (can extend to the end).

    Two passes with a monotonic stack:
    - Pass 1 (left to right): find PSE for each bar
    - Pass 2 (right to left): find NSE for each bar

    Time: O(N), Space: O(N)
*/

// Solution 1: Brute Force O(N²)
// For each bar, expand left and right to find how far it can extend.
class Solution1 {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        int maxArea = 0;

        for (int i = 0; i < n; i++) {
            // Expand left
            int left = i - 1;
            while (left >= 0 && heights[left] >= heights[i])
                left--;

            // Expand right
            int right = i + 1;
            while (right < n && heights[i] <= heights[right])
                right++;

            // left and right now point to first smaller elements (or boundaries)
            // Width = right - left - 1
            int width = right - left - 1;
            int area = heights[i] * width;
            maxArea = max(maxArea, area);
        }

        return maxArea;
    }
};

// Solution 2: PSE + NSE with Monotonic Stack O(N)
// Pass 1: Find Previous Smaller Element (left boundary) for each bar.
// Pass 2: Find Next Smaller Element (right boundary) for each bar.
// Width = right[i] - left[i] - 1. Area = heights[i] * width.
class Solution2 {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> left(n);   // PSE index for each bar
        vector<int> right(n);  // NSE index for each bar

        stack<int> st;

        // Pass 1: Find PSE (Previous Smaller Element)
        // Scan left to right. Maintain increasing monotonic stack.
        for (int i = 0; i < n; i++) {
            while (!st.empty() && heights[st.top()] >= heights[i])
                st.pop();
            if (st.empty())
                left[i] = -1;
            else
                left[i] = st.top();
            st.push(i);
        }

        // Clear stack for second pass
        while (!st.empty()) 
            st.pop();

        // Pass 2: Find NSE (Next Smaller Element)
        // Scan right to left. Maintain increasing monotonic stack.
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && heights[st.top()] >= heights[i])
                st.pop();
            if (st.empty())
                right[i] = n;
            else
                right[i] = st.top();
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

    vector<int> heights = {2, 1, 5, 6, 2, 3};

    cout << "Brute Force: " << brute.largestRectangleArea(heights) << endl;   // Expected: 10
    cout << "PSE + NSE:   " << optimal.largestRectangleArea(heights) << endl; // Expected: 10

    vector<int> heights2 = {2, 4};
    cout << "Brute Force: " << brute.largestRectangleArea(heights2) << endl;  // Expected: 4
    cout << "PSE + NSE:   " << optimal.largestRectangleArea(heights2) << endl; // Expected: 4

    return 0;
}
