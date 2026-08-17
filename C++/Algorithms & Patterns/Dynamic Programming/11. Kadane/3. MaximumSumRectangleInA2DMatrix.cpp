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
	https://www.youtube.com/watch?v=yCQN096CwWM
	Problem Statement:
	------------------
	Given a 2D matrix mat[][] of integers, find the maximum sum among all possible submatrices.

	Examples:
	---------
	Input: mat[][] = [[1,   2, -1, -4, -20],
                      [-8, -3,  4,  2,   1],
                      [3,   8, 10,  1,   3],
                      [-4, -1,  1,  7,  -6]]
	Output: 29
	Explanation: The matrix is as follows and the green rectangle denotes the maximum sum rectangle which is equal to 29.

	Approach:
	--------
											
*/

class Solution {
private: 
	int maximumSubarraySum(vector<int>& A) {
		int maximum_subarray_sum = INT_MIN;
		int current_subarray_sum = 0;

		for (int i = 0; i < A.size(); i++) {
			int subarray_sum_starting_atI = A[i];
			int subarray_sum_ending_atI = current_subarray_sum + A[i];

			current_subarray_sum = max(subarray_sum_starting_atI, subarray_sum_ending_atI);

			maximum_subarray_sum = max(maximum_subarray_sum, current_subarray_sum);
		}

		return maximum_subarray_sum;
	}

public:
	int maxSubMatrixSumInMatrix(vector<vector<int>>& mat) {
		int rows = mat.size();
		int cols = mat[0].size();
		int maxSubmtrixSum = INT_MIN;

		vector<int> accumulate_sum_for_submatrix(rows, 0);

		// fix left
		for (int left = 0; left < cols; left++) {
			
			// reset the submatrix sum array.
			for (int i = 0; i < rows; i++) {
				accumulate_sum_for_submatrix[i] = 0;
			}
			
			// slide right from left to cols
			for (int right = left; right < cols; right++) {

				// add the submatrix sum
				for (int row = 0; row < rows; row++) {
					accumulate_sum_for_submatrix[row] = accumulate_sum_for_submatrix[row] + mat[row][right];
				}

				int subamtrix_sum = maximumSubarraySum(accumulate_sum_for_submatrix);
				maxSubmtrixSum = max(maxSubmtrixSum, subamtrix_sum);
			}
		}

		return maxSubmtrixSum;
	}

};

int main() {
    Solution obj;
	vector<vector<int>> mat = { {1, 2, -1, -4, -20},
							   {-8, -3, 4, 2, 1},
							   {3, 8, 10, 1, 3},
							   {-4, -1, 1, 7, -6} };

	cout << obj.maxSubMatrixSumInMatrix(mat) <<endl;
	return 0;
}