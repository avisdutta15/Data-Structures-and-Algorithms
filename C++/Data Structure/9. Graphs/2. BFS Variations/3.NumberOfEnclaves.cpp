#include <algorithm>
#include <iostream>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string.h>

using namespace std;

/*
	Problem Statement:
	------------------
	You are given an m x n binary matrix grid, where 0 represents a sea cell and 1 represents a land cell.
	
	A move consists of walking from one land cell to another adjacent (4-directionally) land cell or 
	walking off the boundary of the grid.
	
	Return the number of land cells in grid for which we cannot walk off the boundary of the grid in 
	any number of moves.
	
	Example:
	--------
	Input: grid = [[0,1],
				   [1,0]]
	Output: 1

	Input: grid = [[0,1,0],
				   [0,0,0],
				   [0,0,1]]
	Output: 2

	Input: grid = [[1,1,1,1,1],
				   [1,0,0,0,1],
				   [1,0,1,0,1],
				   [1,0,0,0,1],
				   [1,1,1,1,1]]
	Output: 1

	Constraints:
	------------
		n == grid.length == grid[i].length
		2 <= n <= 100
		grid[i][j] is either 0 or 1.
		There are exactly two islands in grid.

	Approach:
	---------
	1. Traverse the boundary cells and if the cell is 1 then do a DFS traversal and mark all the
	connected land cells as visited (mark them as 2).
	2. Now traverse the entire matrix and count the number of 1s.

	The above approach works because once we mark all the land cells connected to the boundary as visited,
	all the 1s that are left are the ones which are completely enclosed by 0s.

	Multi-Source BFS can also be used instead of DFS.
	

	Complexity Analysis:
	-------------------
	Time: O(m*n), we are traversing the matrix constant number of times.
	Space: O(m*n), recursion stack space in worst case when the whole matrix is 1.
	
*/

// DFS Approach on the boundary cells
class Solution {
private:
	int rows = 0, cols = 0;
	vector<vector<int>> dirs = { {0,1},{1,0},{-1,0},{0,-1} };

	// 1 DFS function to visit the island attached to the boundary cell
	// and count the enclaves 
	void DFS(vector<vector<int>>& grid, int i, int j) {
		grid[i][j] = 0;	// mark it visited by making it an island

		for (auto dir : dirs) {
			int x = i + dir[0];
			int y = j + dir[1];

			if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 1) {
				DFS(grid, x, y);
			}
		}
	}

public:
	int numEnclaves(vector<vector<int>>& grid) {
		rows = grid.size();
		cols = grid[0].size();

		// Traverse the entire matrix.
		// if the cell is a 1 and is a boundary cell then identify all the lands reachable from here.
		//for (int i = 0; i < rows; i++) {
		//	for (int j = 0; j < cols; j++) {
		//		//if it is a boundary cell then do DFS
		//		if ((i == 0 || i == rows - 1 || j == 0 || j == cols - 1) && grid[i][j] == 1)
		//			DFS(grid, i, j);
		//	}
		//}

		// Optimization: traverse only the boundary cells
		// If the cell is a 1 and is a boundary cell then identify all the lands reachable from here.
		for (int col = 0; col < cols; col++) {
			if(grid[0][col] == 1)
				DFS(grid, 0, col);
			if (grid[rows - 1][col] == 1)
				DFS(grid, rows - 1, col);
		}

		for (int row = 0; row < rows; row++) {
			if (grid[row][0] == 1)
				DFS(grid, row, 0);
			if (grid[row][cols-1] == 1)
				DFS(grid, row, cols-1);
		}

		// count the actual enclaves.
		// After DFS finishes, every land cell connected to the boundary has been converted to 0.
		// so just count the number of 1s left.
		int enclaveCount = 0;

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (grid[i][j] == 1)
					enclaveCount++;
			}
		}

		return enclaveCount;
	}
};

// Multi-Source BFS Approach on the boundary cells
class Solution2 {
private:
	int rows = 0, cols = 0;
	vector<vector<int>> dirs = { {0,1},{1,0},{-1,0},{0,-1} };

public:
	int numEnclaves(vector<vector<int>>& grid) {
		rows = grid.size();
		cols = grid[0].size();

		queue<pair<int, int>> Q;

		// Optimization: traverse only the boundary cells
		// If the cell is a 1 and is a boundary cell then identify all the lands reachable from here.
		for (int col = 0; col < cols; col++) {
			if (grid[0][col] == 1) {
				Q.push({ 0, col });
				grid[0][col] = 0;
			}				
			if (grid[rows - 1][col] == 1) {
				Q.push({ rows - 1, col });
				grid[rows - 1][col] = 0;
			}				
		}

		for (int row = 0; row < rows; row++) {
			if (grid[row][0] == 1)
				Q.push({ row, 0 });			grid[row][0] = 0;
			if (grid[row][cols - 1] == 1)
				Q.push({ row, cols - 1 });	grid[row][cols - 1] = 0;
		}

		// Multi-Source BFS
		while (!Q.empty()) {
			auto front = Q.front();
			Q.pop();

			int i = front.first;
			int j = front.second;
			for (auto dir : dirs) {
				int x = i + dir[0];
				int y = j + dir[1];
				if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 1) {
					Q.push({ x, y });
					grid[x][y] = 0;		// mark it visited by making it an island
				}
			}
		}

		// count the actual enclaves.
		// After DFS finishes, every land cell connected to the boundary has been converted to 0.
		// so just count the number of 1s left.
		int enclaveCount = 0;

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (grid[i][j] == 1) {
					enclaveCount++;
				}
			}
		}

		return enclaveCount;
	}
};

int main() {
	Solution obj;

	vector<vector<int>> grid =	{
									{0, 0, 0, 0}, 
									{1, 0, 1, 0}, 
									{0, 1, 1, 0}, 
									{0, 0, 0, 0}
								};
	
	cout << obj.numEnclaves(grid) << endl;

	Solution2 obj2;
	cout << obj2.numEnclaves(grid) << endl;
		
	return 0;
}