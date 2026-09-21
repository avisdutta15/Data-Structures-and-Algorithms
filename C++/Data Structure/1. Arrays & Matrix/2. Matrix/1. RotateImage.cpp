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
	https://www.youtube.com/watch?v=Z0R2u6gd3GU&t=893s&pp=ygUMcm90YXRlIGltYWdl
	Problem Statement:
	-----------------
	You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).
	You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. 
	
	DO NOT allocate another 2D matrix and do the rotation.
	
	Examples:
	---------
	Input: matrix = [[1,2,3],
					 [4,5,6],
					 [7,8,9]]

	Output:			
					[[7,4,1],
					 [8,5,2],
					 [9,6,3]]
	
	Input: matrix = [[5,1,9,11],
					 [2,4,8,10],
					 [13,3,6,7],
					 [15,14,12,16]]
	
	Output:			[[15,13,2,5],
					 [14,3,4,1],
					 [12,6,8,9],
					 [16,7,10,11]]

	Constraints:
	------------
	
	Approach:
	--------
	1. Transpose the matrix
	2. Reverse each row
*/

class Solution {
public:
	void rotate(vector<vector<int>>& matrix) {
		int rows = matrix.size();
		int cols = matrix[0].size();

		// 1. Transpose
		for (int i = 0; i < rows; i++) {
			for (int j = i+1; j < cols; j++) {
				swap(matrix[i][j], matrix[j][i]);
			}
		}

		// 2. Reverse each row
		for (int row = 0; row < rows; row++) {
			reverse(matrix[row].begin(), matrix[row].end());
		}
	}
};

int main() {
	Solution obj;
	
	return 0;
}