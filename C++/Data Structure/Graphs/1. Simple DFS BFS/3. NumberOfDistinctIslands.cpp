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

	An island is considered to be the same as another if and only if one island can be 
	translated (and not rotated or reflected) to equal the other.

	Return the number of distinct islands.

	Example:
	-------
	Example 1:
	Input: grid = [[1,1,0,0,0],
				   [1,1,0,0,0],
				   [0,0,0,1,1],
				   [0,0,0,1,1]
				  ]
	Output: 1

	Example 2:
	Input: grid = [[1,1,0,1,1],
				   [1,0,0,0,0],
				   [0,0,0,0,1],
				   [1,1,0,1,1]
				   ]
	Output: 3

	Approach:
	---------
	How will we know if 2 islands are same?
	We could use the position/coordinates of the 1's.
	If we take the first coordinates of any island as a base point and then compute the coordinates 
	of other points from the base point, we can eliminate duplicates to get the distinct count of islands. 
	So, using this approach, the coordinates for the 2 islands in example 1 above can be represented as: 
	[(0, 0), (0, 1), (1, 0), (1, 1)].

	so
		set<vector<pair<int,int>>> uniqueIslands
		traverse the grid
			if land
				var islandsignature
				dfs(grid, i, j, i as basei, j as basej, islandsignature)
				uniqueIslands.insert(islandsignature)
		return uniqueIslands.size()

	dfs(grid, i, j, i as basei, j as basej, islandsignature)
		islandsignature.push_back({basei -i, basej - j})
		normal dfs


	Optimization:
	Instead of using set to get the unique, we can use string encoding + unordered_map


	
*/
class Solution {
private:
	static constexpr int dirs[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
	int rows;
	int cols;

	// Optimized: Use string encoding instead of vector of pairs
	void dfs(vector<vector<int>>& grid, int basei, int basej, int i, int j, string& signature) {
		grid[i][j] = 2; // Mark as visited
		
		// Encode relative position as string (more memory efficient)
		signature += to_string(basei - i) + "," + to_string(basej - j) + ";";

		for (int d = 0; d < 4; d++) {
			int x = dirs[d][0] + i;
			int y = dirs[d][1] + j;
			if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 1) {
				dfs(grid, basei, basej, x, y, signature);
			}
		}
	}

public:
	int numDistinctIslands(vector<vector<int>>& grid) {
		if (grid.empty() || grid[0].empty()) return 0;

		rows = grid.size();
		cols = grid[0].size();

		// Use unordered_set with string keys for O(1) average lookup
		unordered_set<string> uniqueIslands;

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (grid[i][j] == 1) {
					string signature;
					signature.reserve(rows*cols*8); // Optimized for 50x50 grid constraint
					dfs(grid, i, j, i, j, signature);
					uniqueIslands.insert(move(signature));	//move is performance optimization using move semantics
				}
			}
		}
		return uniqueIslands.size();
	}
};

int main()
{
	Solution obj;

	//test case - 1
	vector<vector<int>> grid = {
		{1,1,0,0,0},
		{1,1,0,0,0},
		{0,0,0,1,1},
		{0,0,0,1,1}
	};
	cout << "Number of distinct islands: " << obj.numDistinctIslands(grid) << endl;

	//test case - 2
	grid.clear();
	grid = {
		{1,1,0,1,1},
		{1,0,0,0,0},
		{0,0,0,0,1},
		{1,1,0,1,1}
	};
	cout << "Number of distinct islands: " << obj.numDistinctIslands(grid) << endl;

	return 0;
}

