#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
using namespace std;

/*
	Problem Statement:
	-----------------
	You are given an m x n binary matrix grid. An island is a group of 1's (representing land) 
	connected 4-directionally (horizontal or vertical.) You may assume all four edges of the 
	grid are surrounded by water.

	The area of an island is the number of cells with a value 1 in the island.
	Return the maximum area of an island in grid. If there is no island, return 0.

	Example:
	-------
	Example 1:
	Input: grid = [
	[0,0,1,0,0,0,0,1,0,0,0,0,0],
	[0,0,0,0,0,0,0,1,1,1,0,0,0],
	[0,1,1,0,1,0,0,0,0,0,0,0,0],
	[0,1,0,0,1,1,0,0,1,0,1,0,0],
	[0,1,0,0,1,1,0,0,1,1,1,0,0],
	[0,0,0,0,0,0,0,0,0,0,1,0,0],
	[0,0,0,0,0,0,0,1,1,1,0,0,0],
	[0,0,0,0,0,0,0,1,1,0,0,0,0]]

	Output: 6

	Example 2:
	Input: grid = [[0,0,0,0,0,0,0,0]]
	Output: 0

	Approach:
	---------
	Find the largest connected component.

*/
class Solution {
private:
	vector<vector<int>> dirs = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
	int rows;
	int cols;

	void dfs(vector<vector<int>>& grid, int i, int j, int &size) {
		grid[i][j] = 2; // Mark as visited
		size++;

		for (auto dir : dirs) {
			int x = dir[0] + i;
			int y = dir[1] + j;
			if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 1) {
				dfs(grid, x, y, size);
			}
		}
	}

public:
	int maxAreaOfIsland(vector<vector<int>>& grid) {
		if (grid.empty() || grid[0].empty()) return 0;

		rows = grid.size();
		cols = grid[0].size();
		int area = 0;
		int maxArea = 0;

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (grid[i][j] == 1) {
					area = 0;
					dfs(grid, i, j, area);
					maxArea = max(maxArea, area);
				}
			}
		}
		return maxArea;
	}
};

int main()
{
	Solution obj;

	//test case - 1
	vector<vector<int>> grid = {
		{0,0,1,0,0,0,0,1,0,0,0,0,0} ,
		{0,0,0,0,0,0,0,1,1,1,0,0,0},
		{0,1,1,0,1,0,0,0,0,0,0,0,0},
		{0,1,0,0,1,1,0,0,1,0,1,0,0},
		{0,1,0,0,1,1,0,0,1,1,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,1,1,1,0,0,0},
		{0,0,0,0,0,0,0,1,1,0,0,0,0}
	};
	cout << "Max area of island: " << obj.maxAreaOfIsland(grid) << endl;

	//test case - 2
	grid.clear();
	grid = {
		{0,0,0,0,0,0,0,0}
	};
	cout << "Max area of island: " << obj.maxAreaOfIsland(grid) << endl;

	return 0;
}

