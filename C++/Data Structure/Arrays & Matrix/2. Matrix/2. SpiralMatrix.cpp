#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <stack>
#include <string>

using namespace std;

/*
	https://www.youtube.com/watch?v=73j2ipxR958&t=1358s
	Problem Statement:
	-----------------
	Given an m x n matrix, return all elements of the matrix in spiral order.
	
	Examples:
	---------
	Input: matrix = [[1,2,3],
                     [4,5,6],
                     [7,8,9]]

    Output: [1,2,3,6,9,8,7,4,5]
	
	Input: matrix = [[1,2,3,4],
                     [5,6,7,8],
                     [9,10,11,12]]

    Output: [1,2,3,4,8,12,11,10,9,5,6,7]

	Constraints:
	------------
	
	Approach:
	--------
	Traverse in spiral order using direction variable and four pointers.

                left                    right
                 |                        |
        top    -              



        bottom -

        1. print left to right of top row, move top pointer down.
        2. print top to bottom of right column, move right pointer left.
        3. print right to left of bottom row, move bottom pointer up.
        4. print bottom to top of left column, move left pointer right.
*/

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        int dir = 0;

        /*
            dir = 0 : left to right
            dir = 1 : top to bottom
            dir = 2 : right to left
            dir = 3 : bottom to top
        */

        int top = 0;
        int bottom = rows - 1;
        int left = 0;
        int right = cols - 1;

        vector<int> result;

        while (top <= bottom && left <= right) {
            if (dir == 0) {
                // Traverse left to right
                for (int col = left; col <= right; col++) {
                    result.push_back(matrix[top][col]);
                }

                top++;
            }

            else if (dir == 1) {
                // Traverse from top to bottom
                for (int row = top; row <= bottom; row++) {
                    result.push_back(matrix[row][right]);
                }

                right--;
            }

            else if (dir == 2) {
                // Traverse from right to left
                for (int col = right; col >= left; col--) {
                    result.push_back(matrix[bottom][col]);
                }

                bottom--;
            }

            else if (dir == 3) {
                // Traverse from bottom to top
                for (int row = bottom; row >= top; row--) {
                    result.push_back(matrix[row][left]);
                }
                left++;
            }

            dir = dir + 1;
            dir = dir % 4;
        }

        return result;
    }
};

int main() {
	Solution obj;
	
	return 0;
}