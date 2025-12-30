#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <numeric>
#include <algorithm>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given a 2D matrix matrix, handle multiple queries of the following type:

    Calculate the sum of the elements of matrix inside the rectangle defined by its upper left 
    corner (row1, col1) and lower right corner (row2, col2).

    Implement the NumMatrix class:

        1. NumMatrix(int[][] matrix) Initializes the object with the integer matrix matrix.
        2. int sumRegion(int row1, int col1, int row2, int col2) Returns the sum of the elements of matrix 
           inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

    You must design an algorithm where sumRegion works on O(1) time complexity.

	Examples:
	---------
	Input
    ["NumMatrix", "sumRegion", "sumRegion", "sumRegion"]
    [[[[3, 0, 1, 4, 2], 
       [5, 6, 3, 2, 1], 
       [1, 2, 0, 1, 5], 
       [4, 1, 0, 1, 7], 
       [1, 0, 3, 0, 5]]], 
       
       [2, 1, 4, 3], 
       
       [1, 1, 2, 2], 
       
       [1, 2, 2, 4]]
    Output
    [null, 8, 11, 12]

    Explanation
    NumMatrix numMatrix = new NumMatrix([
                    [3, 0, 1, 4, 2], 
                    [5, 6, 3, 2, 1], 
                    [1, 2, 0, 1, 5], 
                    [4, 1, 0, 1, 7], 
                    [1, 0, 3, 0, 5]]);

    numMatrix.sumRegion(2, 1, 4, 3); // return 8 (i.e sum of the red rectangle)
    numMatrix.sumRegion(1, 1, 2, 2); // return 11 (i.e sum of the green rectangle)
    numMatrix.sumRegion(1, 2, 2, 4); // return 12 (i.e sum of the blue rectangle)

	Approach:
	---------
    prefixSum[][] = 
                    [3  ,3  , 4  ,8  ,10]
                    [8  ,14 , 18 ,24 ,27]
                    [9  ,17 , 21 ,28 ,36]
                    [13 ,22 , 26 ,34 ,49]
                    [14 ,23 , 30 ,38 ,58]

	prefixSum[i][j] represents the sum of area from matrix[0][0] to matrix[i][j]
    +-----+-+-------+     +--------+-----+     +-----+---------+     +-----+--------+
    |     | |       |     |        |     |     |     |         |     |     |        |
    |     | |       |     |        |     |     |     |         |     |     |        |
    +-----+-+       |     +--------+     |     |     |         |     +-----+        |
    |     | |       |  =  |              |  +  |     |         |  -  |              |
    +-----+-+       |     |              |     +-----+         |     |              |
    |               |     |              |     |               |     |              |
    |               |     |              |     |               |     |              |
    +---------------+     +--------------+     +---------------+     +--------------+

     sums[i][j]      =      sums[i-1][j]    +     sums[i][j-1]    -   sums[i-1][j-1]   +  matrix[i-1][j-1] 

    So, we use the same idea to find the specific area's sum.

    +---------------+   +---------+----+   +---+-----------+   +---------+----+   +---+----------+
    |               |   |         |    |   |   |           |   |         |    |   |   |          |
    |   (r1,c1)     |   |         |    |   |   |           |   |         |    |   |   |          |
    |   +------+    |   |         |    |   |   |           |   +---------+    |   +---+          |
    |   |      |    | = |         |    | - |   |           | - |      (r1,c2) | + |   (r1,c1)    |
    |   |      |    |   |         |    |   |   |           |   |              |   |              |
    |   +------+    |   +---------+    |   +---+           |   |              |   |              |
    |        (r2,c2)|   |       (r2,c2)|   |   (r2,c1)     |   |              |   |              |
    +---------------+   +--------------+   +---------------+   +--------------+   +--------------+

     submatrixsum =           total      -        left      -        top        +      topLeft (since it is removed 2wice from left and top)
*/

class NumMatrix {
    vector<vector<int>> prefixSum;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        prefixSum = vector<vector<int>>(rows, vector<int>(cols));
        prefixSum[0][0] = matrix[0][0];

        //process first row -> It will be similar to 1D prefix sum
        for (int j = 1; j < cols; j++) {
            prefixSum[0][j] = prefixSum[0][j - 1] + matrix[0][j];
        }

        //process first column -> It will be similar to 1D prefix sum
        for (int i = 1; i < rows; i++) {
            prefixSum[i][0] = prefixSum[i - 1][0] + matrix[i][0];
        }

        //A[i][j] + top + left - topLeft
        for (int i = 1; i < rows; i++) {
            for (int j = 1; j < cols; j++) {
                prefixSum[i][j] = matrix[i][j] + prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        int total = prefixSum[row2][col2];

        // If row1 > 0, we subtract the area above. If row1 == 0, there is nothing above to subtract.
        int top = (row1 == 0) ? 0 : prefixSum[row1 - 1][col2];

        // If col1 > 0, we subtract the area to the left. If col1 == 0, there is nothing to left.
        int left = (col1 == 0) ? 0 : prefixSum[row2][col1 - 1];

        // If both > 0, we added the top-left intersection back twice, so we subtract it once? 
        // Actually, in the formula Total - Top - Left + TopLeft, if we subtract Top and Left, 
        // we subtract the TopLeft intersection twice. We must add it back.
        // If either boundary is 0, the intersection doesn't exist. 
        int topLeft = (row1 == 0 || col1 == 0) ? 0 : prefixSum[row1 - 1][col1 - 1];

        return total - top - left + topLeft;
    }
};

int main() {

	return 0;
}