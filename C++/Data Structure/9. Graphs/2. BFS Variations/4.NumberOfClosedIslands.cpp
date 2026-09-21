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
	Given a 2D grid consists of 0s (land) and 1s (water).  
	An island is a maximal 4-directionally connected group of 0s and a closed island is an 
	island totally (all left, top, right, bottom) surrounded by 1s.
	
	Return the number of closed islands.

	Example:
	--------
	Input: grid = [[1,1,1,1,1,1,1,0],
				   [1,0,0,0,0,1,1,0],
				   [1,0,1,0,1,1,1,0],
				   [1,0,0,0,0,1,0,1],
				   [1,1,1,1,1,1,1,0]]
	Output: 2
	Explanation: 
	Islands in gray are closed because they are completely surrounded by water (group of 1s).


	Approach:
	---------
	This is similar to 1020. Number of Enclaves.
	First, we need to remove all land connected to the edges using flood fill.
	Then, we can count the remaining islands.

	Approach 1 : All DFS
	Approach 2 : Multi-Source BFS for boundary cells + DFS for island count

*/

// All DFS
class Solution {
private:
	int rows = 0, cols = 0;
	vector<vector<int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

	void DFS(vector<vector<int>>& grid, int i, int j) {
		grid[i][j] = 1;	//mark it visited

		for (auto dir : dirs) {
			int x = i + dir[0];
			int y = j + dir[1];
			if (x >= 0 && x<rows && y>=0 && y<cols && grid[x][y] == 0)
				DFS(grid, x, y);
		}
	}

public:
	int closedIsland(vector<vector<int>>& grid) {
		
		rows = grid.size();
		cols = grid[0].size();

		// Traverse first and last row
		for (int col = 0; col < cols; col++) {
			if (grid[0][col] == 0) DFS(grid, 0, col);
			if (grid[rows - 1][col] == 0) DFS(grid, rows - 1, col);
		}

		// Traverse first and last col
		for (int row = 0; row < rows; row++) {
			if (grid[row][0] == 0) DFS(grid, row, 0);
			if (grid[row][cols - 1] == 0) DFS(grid, row, cols - 1);
		}

		// Traverse the grid again and count the number of islands
		int closedIslands = 0;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (grid[i][j] == 0){
					//found an island, do a dfs and mark all the connected components as visited
					DFS(grid, i, j);
					closedIslands++;
				}
			}
		}
		return closedIslands;
	}
};

// Multi-Source BFS for boundary cells + DFS for island count
class Solution2 {
private:
	int rows = 0, cols = 0;
	vector<vector<int>> dirs = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

	void DFS(vector<vector<int>>& grid, int i, int j) {
		grid[i][j] = 1;	//mark it visited

		for (auto dir : dirs) {
			int x = i + dir[0];
			int y = j + dir[1];
			if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 0)
				DFS(grid, x, y);
		}
	}

public:
	int closedIsland(vector<vector<int>>& grid) {

		rows = grid.size();
		cols = grid[0].size();

		queue<pair<int, int>> Q;

		// Traverse first and last row
		for (int col = 0; col < cols; col++) {
			if (grid[0][col] == 0) {
				Q.push({ 0, col });
				grid[0][col] = 1;
			}
			if (grid[rows - 1][col] == 0) { 
				Q.push({ rows - 1, col });
				grid[rows - 1][col] = 1;
			}
		}

		// Traverse first and last col
		for (int row = 0; row < rows; row++) {
			if (grid[row][0] == 0) {
				Q.push({ row, 0 });
				grid[row][0] = 1;
			}
			if (grid[row][cols - 1] == 0) {
				Q.push({ row, cols - 1 });
				grid[row][cols - 1] = 1;
			}
		}


		while (!Q.empty()) {
			auto front = Q.front();
			Q.pop();

			int i = front.first;
			int j = front.second;

			for (auto dir : dirs) {
				int x = i + dir[0];
				int y = j + dir[1];
				if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 0) {
					Q.push({ x, y });
					grid[x][y] = 1;		// mark it visited
				}
			}
		}

		// Traverse the grid again and count the number of islands
		int closedIslands = 0;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (grid[i][j] == 0) {
					//found an island, do a dfs and mark all the connected components as visited
					DFS(grid, i, j);
					closedIslands++;
				}
			}
		}
		return closedIslands;
	}
};


int main() {
	Solution obj;

	vector<vector<int>> grid =
	{ 
		{1, 1, 1, 1, 1, 1, 1, 0},
		{1, 0, 0, 0, 0, 1, 1, 0},
		{1, 0, 1, 0, 1, 1, 1, 0},
		{1, 0, 0, 0, 0, 1, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 0} 
	};

	cout<< obj.closedIsland(grid) << endl;
		
	return 0;
}