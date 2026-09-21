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
	https://www.youtube.com/watch?v=HXdCemhtrNA&pp=ygUPU3BpcmFsIE1hdHJpeCAy
	Problem Statement:
	-----------------
	Given a positive integer n, generate an n x n matrix filled with elements from 1 to n2 in spiral order.
	 
	Examples:
	---------
	Input: n = 3
    Output: [[1,2,3],
             [8,9,4],
             [7,6,5]]
    Example 2:

    Input: n = 1
    Output: [[1]]

	Constraints:
	------------
	
	Approach:
	--------
	Traverse in spiral order using direction variable and four pointers.

                left                    right
                 |                        |
        top    -              



        bottom -

        keep counter = 1
        while(counter <= n*n)
        1. populate left to right of top row
                counter++, 
           move top pointer down.
        2. populate top to bottom of right column
                counter++, 
           move right pointer left.
        3. populate right to left of bottom row
                counter++, 
           move bottom pointer up.
        4. populate bottom to top of left column
                counter++, 
           move left pointer right.
*/

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        int counter = 1;

        int rows = n;
        int cols = n;

        vector<vector<int>> matrix(n, vector<int>(n, 0));

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

        while (counter <= n * n) {
            if (dir == 0) {
                // Traverse left to right
                for (int col = left; col <= right; col++) {
                    matrix[top][col] = counter;
                    counter++;
                }

                top++;
            }

            else if (dir == 1) {
                // Traverse from top to bottom
                for (int row = top; row <= bottom; row++) {
                    matrix[row][right] = counter;
                    counter++;
                }

                right--;
            }

            else if (dir == 2) {
                // Traverse from right to left
                for (int col = right; col >= left; col--) {
                    matrix[bottom][col] = counter;
                    counter++;
                }

                bottom--;
            }

            else if (dir == 3) {
                // Traverse from bottom to top
                for (int row = bottom; row >= top; row--) {
                    matrix[row][left] = counter;
                    counter++;
                }
                left++;
            }

            dir = dir + 1;
            dir = dir % 4;
        }

        return matrix;
    }
};
int main() {
	Solution obj;
	
	return 0;
}