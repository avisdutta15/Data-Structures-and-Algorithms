#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water),
	return the number of islands.

	An island is surrounded by water and is formed by connecting adjacent lands horizontally
	or vertically. You may assume all four edges of the grid are all surrounded by water.

	Example:
	-------
	Example 1:

	Input: grid = [
	  ["1","1","1","1","0"],
	  ["1","1","0","1","0"],
	  ["1","1","0","0","0"],
	  ["0","0","0","0","0"]
	]
	Output: 1

	Example 2:

	Input: grid = [
	  ["1","1","0","0","0"],
	  ["1","1","0","0","0"],
	  ["0","0","1","0","0"],
	  ["0","0","0","1","1"]
	]
	Output: 3

	Approach:
	---------
	Traverse the grid.
		If we encounter a land, do a DFS/BFS and find all the lands in that connected component.
		do island++
	T.C. - O(n x m)
	The outer loops iterate through every cell in the grid, which takes O(m * n) time.
	For each cell that contains '1', we perform a DFS traversal. In the worst case, if the entire 
	grid is filled with '1's forming one large island, the DFS will visit every cell once.
	Each cell is visited at most twice: once by the outer loop iteration and potentially once 
	during a DFS traversal from a neighboring cell.
	The pairwise function with dirs = (-1, 0, 1, 0, -1) generates 4 direction pairs: [(-1, 0), (0, 1), (1, 0), (0, -1)], 
	representing up, right, down, and left movements. This operation is O(1) for each cell.
	Overall, every cell is processed a constant number of times, resulting in O(m * n) time complexity.

	S.C - O(1) if used the input grid to track visited cells
		  O(n x m) if a separate grid is used to track visited cells
*/
class Solution {
	vector<vector<int>> dirs = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
	int rows;
	int cols;

	void dfs(vector<vector<char>>& grid, int i, int j) {
		grid[i][j] = '2';
		for (auto dir : dirs) {
			int x = dir[0] + i;
			int y = dir[1] + j;
			if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == '1')
				dfs(grid, x, y);
		}
	}
	
	void bfs(vector<vector<char>>& grid, int i, int j) {
		queue<pair<int, int>> Q;
		
		//process starting node
		Q.push({ i,j });
		grid[i][j] = '2';

		//process other nodes
		while (!Q.empty()) {
			auto u = Q.front();
			Q.pop();

			i = u.first;
			j = u.second;

			for (auto dir : dirs) {
				int x = dir[0] + i;
				int y = dir[1] + j;
				if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == '1') {
					grid[x][y] = '2';
					Q.push({ x, y });
				}
			}			
		}
	}

public:
	int numIslands(vector<vector<char>>& grid) {
		if (grid.size() == 0)
			return 0;
		rows = grid.size();
		cols = grid[0].size();
		int islandCount = 0;

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (grid[i][j] == '1') {
					//dfs(grid, i, j);
					bfs(grid, i, j);
					islandCount++;
				}
			}
		}
		return islandCount;
	}
};

int main()
{
	Solution obj;

	//test case - 1
	vector<vector<char>> grid = {
		{'1','1','1','1','0'},
		{'1','1','0','1','0'},
		{'1','1','0','0','0'},
		{'0','0','0','0','0'}
	};
	cout << "Number of islands: " << obj.numIslands(grid) << endl;

	//test case - 2
	grid.clear();
	grid = {
		{'1','1','0','0','0'} ,
		{'1','1','0','0','0'},
		{'0','0','1','0','0'},
		{'0','0','0','1','1'}
	};
	cout << "Number of islands: " << obj.numIslands(grid) << endl;

	return 0;
}