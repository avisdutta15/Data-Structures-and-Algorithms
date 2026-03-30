#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given the dimension of a sequence of matrices in an array arr[], where the dimension of the ith matrix is (arr[i-1] * arr[i]), 
	the task is to find the most efficient way to multiply these matrices together such that the total number of element multiplications 
	is minimum. 

	Examples:
	---------
	Input: arr[] = [2, 1, 3, 4]
	Output: 20
	Explanation: There are 3 matrices of dimensions 2x1, 1x3, and 3x4,
	Let the input 3 matrices be M1, M2, and M3. There are two ways to multiply ((M1 x M2) x M3) and (M1 x (M2 x M3)),
	Please note that the result of M1 x M2 is a 2 x 3 matrix and result of (M2 x M3) is a 1 x 4 matrix.
	((M1 x M2) x M3)  requires (2 x 1 x 3)  +  (2 x 3 x 4) = 30
	(M1 x (M2 x M3))  requires (1 x 3 x 4) +  (2 x 1 x 4) = 20
	The minimum of these two is 20.

	Input: arr[] = [1, 2, 3, 4, 3]
	Output: 30
	Explanation: There are 4 matrices of dimensions 1×2, 2×3, 3×4, 4×3. Let the input 4 matrices be M1, M2, M3 and M4. The minimum number of multiplications are obtained by ((M1M2)M3)M4. The minimum number is 1*2*3 + 1*3*4 + 1*4*3 = 30

	Input: arr[] = [3, 4]
	Output: 0
	Explanation: As there is only one matrix so, there is no cost of multiplication.
	
	Approach:
	---------
	Recursive:
		Time Complexity : O(2^n)
		Space Complexity : O(n)

	Top Down:
		Time Complexity : O(n^3)
		Space Complexity : O(n^2)

	Bottom Up:
		Time Complexity : O(n^3)
		Space Complexity : O(n^2)
*/


class Solution1 {
public:
	int mcmRecursive(vector<int> A, int i, int j) {
		//1. BASE CASE
		// if there is no matrix return 0.
		if (i > j)
			return 0;

		// if there is only one Matrix then return 0.
		// It costs 0 operations to multiply a single matrix by nothing.
		if (i == j)
			return 0;

		int ans = INT_MAX;

		//2. TRY EVERY POSSIBLE SPLIT POINT
		// Try placing the parenthesis at every possible split point 'k'
		// This splits the matrices into two groups: (i to k) and (k+1 to j)
		for (int k = i; k <= j - 1; k++) {

			//3. SPLIT INTO LEFT AND RIGHT HALF AND THEN CALCULATE THE MERGE COST
			int left_cost = mcmRecursive(A, i, k);
			int right_cost = mcmRecursive(A, k + 1, j);

			// Calculate cost to multiply the resulting left matrix with the resulting right matrix.
			// The left matrix will end up with dimensions: arr[i-1] x arr[k]
			// The right matrix will end up with dimensions: arr[k] x arr[j]
			// Cost = rows of left * cols of left (which is rows of right) * cols of right
			int merge_cost = A[i - 1] * A[k] * A[j];

			//4. UPDATE THE ANSWER
			int total_cost_at_split_k = left_cost + right_cost + merge_cost;

			// Keep track of the minimum cost found
			ans = min(ans, total_cost_at_split_k);
		}

		return ans;
	}

	int mcm(vector<int> A) {
		int n = A.size();

		// We start i at 1 because matrix 1 has dimensions arr[0] x arr[1].
		// We end j at n-1 because the last matrix has dimensions arr[n-2] x arr[n-1].
		int i = 1;
		int j = n - 1;

		return mcmRecursive(A, i, j);
	}
};

class Solution2 {
public:
	int mcmTopDown(vector<int> A, int i, int j, vector<vector<int>> &dp) {
		//1. BASE CASE
		// if there is no matrix return 0.
		if (i > j)
			return 0;

		// if there is only one Matrix then return 0.
		// It costs 0 operations to multiply a single matrix by nothing.
		if (i == j)
			return 0;

		if (dp[i][j] != -1)
			return dp[i][j];

		int ans = INT_MAX;

		//2. TRY EVERY POSSIBLE SPLIT POINT
		// Try placing the parenthesis at every possible split point 'k'
		// This splits the matrices into two groups: (i to k) and (k+1 to j)
		for (int k = i; k <= j - 1; k++) {

			//3. SPLIT INTO LEFT AND RIGHT HALF AND THEN CALCULATE THE MERGE COST
			int left_cost = mcmTopDown(A, i, k, dp);
			int right_cost = mcmTopDown(A, k + 1, j, dp);

			// Calculate cost to multiply the resulting left matrix with the resulting right matrix.
			// The left matrix will end up with dimensions: arr[i-1] x arr[k]
			// The right matrix will end up with dimensions: arr[k] x arr[j]
			// Cost = rows of left * cols of left (which is rows of right) * cols of right
			int merge_cost = A[i - 1] * A[k] * A[j];

			//4. UPDATE THE ANSWER
			int total_cost_at_split_k = left_cost + right_cost + merge_cost;

			// Keep track of the minimum cost found
			ans = min(ans, total_cost_at_split_k);
		}

		return dp[i][j] = ans;
	}

	int mcm(vector<int> A) {
		int n = A.size();

		// We start i at 1 because matrix 1 has dimensions arr[0] x arr[1].
		// We end j at n-1 because the last matrix has dimensions arr[n-2] x arr[n-1].
		int i = 1;
		int j = n - 1;

		// Dimensions are n x n because 'i' and 'j' can range up to n-1.
		vector<vector<int>> dp(n, vector<int>(n, -1));

		return mcmTopDown(A, i, j, dp);
	}
};

class Solution3 {
public:
	int mcm(vector<int> A) {
		int N = A.size();

		vector<vector<int>> dp(N, vector<int>(N, -1));

		//BASE CASE: i==j -> cost = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i == j)
					dp[i][j] = 0;
			}
		}

		// 1. 'i' goes backwards from the bottom of the table up to the top
		for(int i=N-1; i>=1; i--){

			// 2. 'j' goes forwards from just right of 'i', up to the end. Why not j=i? Coz j=i means single matrix.
			for (int j = i+1; j <= N-1; j++) {
				int ans = INT_MAX;

				//Try all possible splits between i and j exactly like before
				for (int k = i; k <= j - 1; k++) {
					int left_cost = dp[i][k];
					int right_cost = dp[k + 1][j];
					int merge_cost = A[i - 1] * A[k] * A[j];

					int total_cost_at_split_k = left_cost + right_cost + merge_cost;
					ans = min(ans, total_cost_at_split_k);
				}
				dp[i][j] = ans;
			}
		}

		// The answer for the entire chain is still at the top right
		return dp[1][N - 1];
	}
};

int main()
{
	vector<int> A = { 1, 2, 3, 4, 3 };

	Solution1 obj1;
	cout << obj1.mcm(A)<<endl;

	Solution2 obj2;
	cout << obj2.mcm(A) << endl;

	Solution3 obj3;
	cout << obj3.mcm(A) << endl;
	return 0;
}