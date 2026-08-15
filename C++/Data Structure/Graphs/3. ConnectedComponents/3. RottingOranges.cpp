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
	You are given an m x n grid where each cell can have one of three values:

	0 representing an empty cell,
	1 representing a fresh orange, or
	2 representing a rotten orange.
	Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

	Return the minimum number of minutes that must elapse until no cell has a fresh orange. 
	If this is impossible, return -1.


	Example:
	--------
	Example 1:
	Input: grid = [[2,1,1],
	               [1,1,0],
				   [0,1,1]]
	Output: 4

	Example 2:
	Input: grid = [[2,1,1],
	               [0,1,1],
				   [1,0,1]]
	Output: -1
	Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, 
	because rotting only happens 4-directionally.
	
	Example 3:
	Input: grid = [[0,2]]
	Output: 0
	Explanation: Since there are already no fresh oranges at minute 0, the answer is just 0.
 

	Approach: BFS
	--------------
	Why the flag (didThisLayerRotAnyFreshOrange) is better than minutes-1 at the end:
	Consider this grid:

		[2, 1]
	
	Without the flag (using minutes - 1):
		Layer 0: Pop (0,0). Rot (0,1). freshCount=0. minutes++ → minutes=1
		Layer 1: Pop (0,1). No fresh neighbors. minutes++ → minutes=2
		Return minutes - 1 = 1 ✓
	
	With your flag:
		Layer 0: Pop (0,0). Rot (0,1). didRot = true. minutes++ → minutes=1
		Layer 1: Pop (0,1). No fresh neighbors. didRot = false. Don't increment.
		Return minutes = 1 ✓
		Both work for this case. But your flag makes it explicit — you only count a layer 
		if it actually did useful work. It avoids the awkward minutes - 1 at the end.
*/

class Solution {
private:
	vector<vector<int>> dirs = { {0,1}, {0,-1}, {1,0}, {-1,0} };
public:
	int orangesRotting(vector<vector<int>>& grid) {
		int rows = grid.size(), cols = grid[0].size();
		queue<pair<int, int>> q;
		int freshCount = 0;

		// Step 1: Push all rotten oranges into queue, count fresh ones
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < cols; c++) {
				if (grid[r][c] == 2) q.push({ r, c });
				else if (grid[r][c] == 1) freshCount++;
			}
		}

		// If no fresh oranges, nothing to rot
		if (freshCount == 0)
			return 0;

		int minutes = 0;
		//this is needed so that we dont increment the timer once we finish the last layer
		//that didnot rot any oranges.
		bool didThisLayerRotAnyFreshOrange = false;

		// Step 2: Multi-source BFS — all rotten oranges spread simultaneously
		while (!q.empty()) {
			int size = q.size();
			didThisLayerRotAnyFreshOrange = false;

			// Process all rotten oranges at current time step
			while (size--) {
				auto [r, c] = q.front();
				q.pop();

				for (auto dir : dirs) {
					int x = r + dir[0];
					int y = c + dir[1];

					// If neighbor is fresh, rot it and add to queue
					if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 1) {
						grid[x][y] = 2;
						freshCount--;
						q.push({ x, y });
						didThisLayerRotAnyFreshOrange = true;
					}
				}
			}
			if (didThisLayerRotAnyFreshOrange)
				minutes++;
		}

		// minutes-1 because the last level processes but doesn't rot anything new
		// OR: if fresh remain, return -1
		return freshCount == 0 ? minutes : -1;
	}
};

int main() {


	return 0;
}