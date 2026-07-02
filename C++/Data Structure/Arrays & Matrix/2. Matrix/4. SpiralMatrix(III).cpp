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
	https://www.youtube.com/watch?v=dt0UzAz7SPg&t=1246s
	Problem Statement:
	-----------------
	You start at the cell (rStart, cStart) of an rows x cols grid facing east. 
    The northwest corner is at the first row and column in the grid, and the southeast 
    corner is at the last row and column.
    
    You will walk in a clockwise spiral shape to visit every position in this grid. 
    Whenever you move outside the grid's boundary, we continue our walk outside the grid 
    (but may return to the grid boundary later.). 
    Eventually, we reach all rows * cols spaces of the grid.
    
    Return an array of coordinates representing the positions of the grid in the order you visited them.
	 
	Examples:
	---------
	Input: rows = 1, cols = 4, rStart = 0, cStart = 0
    Output: [[0,0],
             [0,1],
             [0,2],
             [0,3]]

    Input: rows = 5, cols = 6, rStart = 1, cStart = 4
    Output: [[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],
             [3,5],[3,4],[3,3],[3,2],[2,2],[1,2],[0,2],[4,5],[4,4],
             [4,3],[4,2],[4,1],[3,1],[2,1],[1,1],[0,1],[4,0],[3,0],
             [2,0],[1,0],[0,0]]

	Constraints:
	------------
	
	Approach:
	--------
	Traverse in spiral order using direction.

        When we traverse EAST or WEST, we need to increase our steps by 1.
        We start with 0 steps, and go in EAST direction.
        We take 'steps' number of moves in that direction.
        Then we turn clockwise to next direction.
         dir = (dir + 1) % 4;

    Time Complexity : O(max(m,n)^2)
*/

class Solution {
public:
    vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart) {

        vector<vector<int>> dirs =
        {
            {0, 1},     //EAST (same row, incr col)
            {1, 0},     //SOUTH (same col, incr row)
            {0, -1},    //WEST (same row, decr col)
            {-1, 0}     //NORTH (same col, decr row)
        };

        int steps = 0;  // how much steps to move
        int dir = 0;  // direction array index
        vector<vector<int>> result;

        result.push_back({ rStart, cStart });

        while (result.size() < rows * cols)
        {
            // When we move EAST or WEST, we need to increase our steps by 1
            if (dir == 0 || dir == 2)
                steps++;

            // Take the steps.
            for (int step = 1; step <= steps; step++) {
                rStart = rStart + dirs[dir][0];
                cStart = cStart + dirs[dir][1];

                // if the new coordinate is within the matrix then push to ans
                if (rStart >= 0 && rStart < rows && cStart >= 0 && cStart < cols) {
                    result.push_back({ rStart, cStart });
                }
            }

            // turn to next direction
            dir = (dir + 1) % 4;
        }

        return result;
    }
}; 

int main() {
	Solution obj;
	
	return 0;
}