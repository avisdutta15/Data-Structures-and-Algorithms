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
	You are given an n x n binary matrix grid where 1 represents land and 0 represents water.
	
	An island is a 4-directionally connected group of 1's not connected to any other 1's. 
	There are exactly two islands in grid.
	
	You may change 0's to 1's to connect the two islands to form one island.
	
	Return the smallest number of 0's you must flip to connect the two islands.
	
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
	For shortest path problem we have 2 approach -
		1. Dijkstra
		2. BFS

	Dijkstra is single source shortest path
	BFS have the multisource shortest path capability.
		We dont just want the shortest path from one specific cell on island A to island B.
		We want the shortest path from any cell on the perimeter of Island A to any cell of Island B.
		By pushing all coordinates of Island A into the BFS queue initially (Multi-Source BFS),
		the distance expands simultaneously from the entire perimeter.

	Our Apporach - DFS to identify islandA + Multi-Source BFS for shortest distance 
	1.  Isolate the first island using DFS.
		iterate the grid.
		if found 1
			DFS -> mark the island as 2. also collect the coordinates of the islandA in a vector.
	2.  BFS
			start from all the coordinates of islandA vector. (multi-source BFS)
			queue them
			distance = 0
			while(!q.empty)
				pop
				for every neighbour
					if(1) then we found island B
						return distance
					if(0) then we found water. We claim it as 2 (add to islandA) and push to queue.
			distance++

	Time Complexity: O(RxC)
	
*/

class Solution {
private:
	vector<vector<int>> dirs = { {0,1},{0,-1}, {1,0}, {-1,0} };
	int rows, cols;

	void DFS(vector<vector<int>>& grid, int i, int j, vector<pair<int, int>>& islandOneCoordinates) {
		grid[i][j] = 2;
		islandOneCoordinates.push_back({ i, j });

		for (auto dir : dirs) {
			int x = i + dir[0];
			int y = j + dir[1];

			if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 1) {
				DFS(grid, x, y, islandOneCoordinates);
			}
		}
	}

	int BFS(vector<vector<int>>& grid, vector<pair<int, int>>& islandOneCoordinates) {
		queue<pair<int, int>> Q;

		// start the BFS from all the coords of the 1st island
		for (auto p : islandOneCoordinates) {
			Q.push(p);
		}

		int queueSize = 0;
		int dist = 0;	// we are currently processing elements in queue at dist 0

		while (!Q.empty()) {
			// Q has elements at distance 'dist' from 1st island
			queueSize = Q.size();
			while (queueSize--) {
				auto front = Q.front();
				Q.pop();

				int i = front.first;
				int j = front.second;

				for (auto dir : dirs) {
					int x = i + dir[0];
					int y = j + dir[1];

					// if valid cell
					if (x >= 0 && x < rows && y >= 0 && y < cols) {

						// we found the 2nd island then return the distance
						if (grid[x][y] == 1) {
							return dist;
						}
						// we found a water cell. So mark it a part of 1st island
						// push it into the queue.
						else if (grid[x][y] == 0) {
							grid[x][y] = 2;
							Q.push({ x, y });
						}
					}
				}
			}
			dist++;
		}

		return dist;
	}

public:
	int shortestBridge(vector<vector<int>>& grid) {
		rows = grid.size();
		cols = grid[0].size();

		vector<pair<int, int>> islandOneCoordinates;

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (grid[i][j] == 1) {
					// traverse the island and mark it as 2
					DFS(grid, i, j, islandOneCoordinates);
					return BFS(grid, islandOneCoordinates);
				}
			}
		}

		return -1;
	}
};

int main() {
	Solution obj;

	vector<vector<int>> grid = {
									{0, 1, 0}, 
									{0, 0, 0}, 
									{0, 0, 1}
								};
	
	cout << obj.shortestBridge(grid) << endl;
		
	return 0;
}