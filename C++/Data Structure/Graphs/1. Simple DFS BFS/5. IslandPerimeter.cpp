#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <queue>
using namespace std;

/*
	Problem Statement:
	-----------------
	You are given row x col grid representing a map where grid[i][j] = 1 represents 
	land and grid[i][j] = 0 represents water.
	Grid cells are connected horizontally/vertically (not diagonally). The grid is 
	completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells).
	The island doesn't have "lakes", meaning the water inside isn't connected to 
	the water around the island. One cell is a square with side length 1. The grid 
	is rectangular, width and height don't exceed 100. Determine the perimeter of the island.

 	Example:
	-------
	Example 1:
	Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
	Output: 16
	Explanation: The perimeter is the 16 yellow stripes in the image above.

	Example 2:
	Input: grid = [[1]]
	Output: 4

	Example 3:
	Input: grid = [[1,0]]
	Output: 4

	Approach:
	---------
	Simple DFS/BFS. But for a land how to get the sides that have water?
	Contribution of land to the total perimeter = number of sides out of its 4 sides that has lands.
	
	getLandPerimeter(grid, i, j)
		landPerimeter = 4;
		for each of its 4 connected neighbour,
			if(neighbour == 0)
				landPerimeter--;
		return landPerimeter
	
	dfs()
		perimeter+= getLandPerimeter(i, j);
		visit[i][j]
		....rest is normal DFS

*/

class Solution {
	vector<vector<int>> dirs = { {0,1}, {0,-1}, {1,0}, {-1,0} };
	int rows, cols;

	int landPerimeter(vector<vector<int>>& grid, int i, int j) {
		int _landperimeter = 4;
		for (auto dir : dirs) {
			int x = i + dir[0];
			int y = j + dir[1];
			//if the neighbouring cell is a land then it shares a boundary with that land
			//so one side is deducted from its perimeter;
			if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 1) {
				_landperimeter--;
			}
		}
		return _landperimeter;
	}

	void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int i, int j, int& perimeter) {
		//calculate the perimeter contributed by this land cell
		perimeter = perimeter + landPerimeter(grid, i, j);
		visited[i][j] = true;

		//traverse the neighbours
		for (auto dir : dirs) {
			int x = i + dir[0];
			int y = j + dir[1];
			//if the neighbouring cell is a land then it shares a boundary with that land
			//so one side is deducted from its perimeter;
			if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 1 && visited[x][y] == false) {
				dfs(grid, visited, x, y, perimeter);
			}
		}
	}

public:
	int islandPerimeter(vector<vector<int>>& grid) {
		if (grid.size() == 0)
			return 0;

		rows = grid.size();
		cols = grid[0].size();
		vector<vector<bool>> visited(rows, vector<bool>(cols, false));

		int perimeter = 0;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (grid[i][j] == 1 && visited[i][j] == false) {
					dfs(grid, visited, i, j, perimeter);
					break;
				}
			}
		}
		return perimeter;
	}
};

int main()
{
	Solution obj;

	//test case - 1
	vector<vector<int>> image = {
		{0, 1, 0, 0}, 
		{1, 1, 1, 0}, 
		{0, 1, 0, 0}, 
		{1, 1, 0, 0}
	};
	cout << obj.islandPerimeter(image) <<endl;

	return 0;
}

