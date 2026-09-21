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
	Instead of using set to get the unique, we can use string encoding + unordered_set

		unordered_set<string> uniqueIslands;
		traverse the grid
			if land
				string islandSignature;
				islandSignature.reserve(50 * 50 * 8);
				DFS(...., &islandSignature)
				uniqueIslands.insert(islandsignature)
		return uniqueIslands.size();

		In C++, strings automatically allocate memory as they grow. If you append characters one by one, 
		the string will run out of space, create a bigger block of memory, copy everything over, and 
		delete the old block. This is called reallocation, and doing it thousands of times inside a 
		DFS is very slow.

		By using reserve(), the developer tells C++:
		"I am about to build a string. Please reserve enough contiguous memory upfront to hold 
		[Max Island Size] * [8 characters per block]. This way, you will never have to pause and 
		reallocate memory while my DFS is running."

		why 50 * 50 * 8?
		The * 8 represents the maximum number of characters generated per cell visited. 
		Let's break down the worst-case scenario for a single cell's coordinate string:
		- Row Coordinate: Can be a negative number, up to 2 digits (e.g., -50) -> 3 chars
		- Delimiter: A comma separating row and col (,) -> 1 char
		- Col Coordinate: Can be a negative number, up to 2 digits (e.g., -50) -> 3 chars
		- Separator: A delimiter separating this cell from the next (|) -> 1 char
		- Total characters for a worst-case cell: 3 + 1 + 3 + 1 = 8 characters.

		why row and col can grow to -50?
		Since we are doing baseI-i and baseJ-j, 
		for a 50*50 grid, if the entire grid is a big island, then starting the DFS at 0,0
		and at 49*49 cell, we will have {0-49, 0-49} which is {-49, -49}

	Time Complexity: R x C
		The secret to this strict O(R x C) limit is that as soon as the DFS visits a land cell (1), 
		it immediately marks it as visited (usually by turning it into a 0 or updating a boolean array).
		Because of this, a cell can never be processed by the DFS loop more than once.
		
		Let's look at the extreme grid layouts to prove this:
		
		Extreme Case 1: The grid is 100% water (All 0s)
		- The double for loop checks every single cell.
		- The if (grid[i][j] == 1) condition is never met.
		- The DFS is never called.
		- Total Operations: R x C checks.
		
		Extreme Case 2: The grid is 100% land (All 1s)
		- The double for loop checks the very first cell at (0,0).
		- The if condition is met! The DFS triggers.
		- The DFS runs wildly through the entire grid, visiting every single cell, processing them, 
		and turning them all into 0s.
		- The DFS finishes and returns to the double for loop.
		- The for loop continues from (0,1) to the end of the board. 
		- But because the DFS already turned everything into 0s, the if condition is never met again.
		- Total Operations: R x C cells visited by DFS + R x C cells skipped by the loop = O(2 x R x C), 
		  which simplifies exactly to O(R x C).
		  
		Extreme Case 3: The Checkerboard (Alternating 1s and 0s)
		- The double for loop checks every cell.
		- It finds a 1, triggers the DFS. 
		- The DFS visits exactly one cell (because it is surrounded by 0s), flips it, and returns.
		- This happens R x C / 2 times.
		- Total Operations: Half the cells processed by DFS + all cells checked by the loop = O(R x C).

	Space Complexity : O(R x C)
	
*/
class Solution {
private:
	vector<vector<int>> dirs = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
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

