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
	Given an n x n binary matrix grid, return the length of the shortest clear 
	path in the matrix. If there is no clear path, return -1.
	
	A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) 
	to the bottom-right cell (i.e., (n - 1, n - 1)) such that:
	- All the visited cells of the path are 0.
	- All the adjacent cells of the path are 8-directionally connected 
	(i.e., they are different and they share an edge or a corner).

	The length of a clear path is the number of visited cells of this path.

	Example:
	--------
	Input: grid = [	[0,1],
					[1,0]]
	Output: 2

	Input: grid = [	[0,0,0],
					[1,1,0],
					[1,1,0]]
	Output: 4

	Input: grid = [	[1,0,0],
					[1,1,0],
					[1,1,0]]
	Output: -1

	Approach 1 - DFS (Brute Force)
	---------------------
	Traverse all possible paths and find the minimum.

	Time Complexity: O(8^(N^2)) where N is the dimension of the grid.
	Why 8^(N^2)) ?
		At each cell, we have atmost 8 choices. In the worst case, we might end up
		visiting all the cells in the grid.

	Space Complexity: O(N^2) for the recursion stack in the worst case.

	Approach 2 - Dijkstra's Algorithm
	---------------------------------
	Since all the edge weights are equal, we can use Dijkstra's algorithm.
	You can treat a binary matrix as a weighted graph where every valid edge has a weight of 1. 
	Dijkstra will successfully find the shortest path.
	However, because it uses a Priority Queue (Min-Heap) to constantly sort the edges 
	by distance, it introduces a logarithmic overhead.
	Using Dijkstra here is like using a sledgehammer to drive in a thumbtack.
	
	Time Complexity: O(N^2 * log(N^2)) = O(N^2 * log(N))
	Why? 
		There are atmost N^2 nodes and each node can be inserted into the priority
		queue at most once. Each insertion takes O(log(N^2)) time.
	Space Complexity: O(N^2) for the priority queue and distance matrix.

	Approach 3 - BFS
	----------------
	BFS expands outwards from the source in uniform rings (or waves) of distance. 
	Because every step costs the same, the very first time one of these rings touches 
	the destination, it is mathematically guaranteed to be the shortest path.

	Time Complexity: O(N^2) where N is the dimension of the grid. 
					 We visit each cell at most once.
	Space Complexity: O(N^2) for the queue in the worst case.

	********
	
	Why DP with Memoization Fails Here
	----------------------------------
	
	You mentioned a problem like Minimum Path Sum. 
	In that problem, Dynamic Programming (DP) is the perfect solution. 
	Why does DP work there, but fail completely for Shortest Path in Binary Matrix?
	
	The Core Requirement of DP: Directed Acyclic Graphs (DAGs)
		Dynamic Programming relies on breaking a problem down into independent subproblems.
	
	In problems like Minimum Path Sum, the rules usually restrict your movement: 
	"You can only move RIGHT or DOWN."
	Because you can only move right or down, it is physically impossible to revisit a cell. 
	The paths form a Directed Acyclic Graph (DAG).
	
	The answer for cell (r, c) depends strictly on (r-1, c) and (r, c-1).
	You can calculate (r, c) once, memoize it, and guarantee it will never change.
	
	The Cyclic Nature of 8-Directional Movement
	In Shortest Path in Binary Matrix, you can move in all 8 directions 
	(Up, Down, Left, Right, and Diagonals).
	
	Because you can move Up and Left, cycles are possible.
		Imagine you are at cell (2, 2).
		To calculate the shortest path from (2, 2), you need to know the shortest 
		path from (2, 3) (its right neighbor).
		
		But to calculate the shortest path from (2, 3), you might need to know 
		the shortest path from (2, 2) (its left neighbor)!
		
		This creates a circular dependency.
		
		You cannot use standard DP/Memoization because you cannot guarantee a 
		topological order to solve the subproblems. The answer for a cell depends 
		on neighbors whose answers depend back on the original cell.

*/

// DFS
class Solution1 {
private:
	vector<vector<int>> dirs = { {0,1}, {0,-1}, {1,0}, {-1,0}, {1,1}, {1,-1}, {-1,1}, {-1,-1} };
	int rows = 0, cols = 0;

	void DFS(vector<vector<int>>& grid, int i, int j, int currentPathLength, int& minimumPathLength) {
		// visit the node
		grid[i][j] = 1;

		if (i == rows - 1 && j == cols - 1) {
			minimumPathLength = min(minimumPathLength, currentPathLength);
			grid[i][j] = 0;
			return;
		}

		for (auto dir : dirs) {
			int x = i + dir[0];
			int y = j + dir[1];

			if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 0) {
				DFS(grid, x, y, currentPathLength + 1, minimumPathLength);
			}
		}

		// backtrack
		grid[i][j] = 0;
	}
public:
	int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
		rows = grid.size();
		cols = grid[0].size();

		// Base Case:
		if (grid[0][0] == 1 || grid[rows - 1][cols - 1] == 1)
			return -1;

		int minimumPathLength = INT_MAX;
		int i = 0, j = 0;
		int currentPathLength = 1;
		DFS(grid, i, j, currentPathLength, minimumPathLength);

		// If there is not path from source to destination
		return minimumPathLength == INT_MAX ? -1 : minimumPathLength;
	}
};

// Dijkstra's Algorithm
class Solution2 {
private:
	vector<vector<int>> dirs = { {0,1}, {0,-1}, {1,0}, {-1,0}, {1,1}, {1,-1}, {-1,1}, {-1,-1} };
	int rows = 0, cols = 0;

	int dijkstra(vector<vector<int>>& grid, pair<int, int> source) {

		vector<vector<int>> distance(rows, vector<int>(cols, INT_MAX));
		priority_queue<pair<int, pair<int, int>>,
		vector<pair<int, pair<int, int>>>,
		greater<pair<int, pair<int, int>>>> Q;		// Q(distance, {i, j})
		

		// INITIALIZE THE SINGLE SOURCE
		distance[source.first][source.second] = 1;
		Q.push({1, {0, 0}});

		while (!Q.empty()) {
			// nodeWeight is the total distance accumulated from
			// start to node 'node'
			auto [nodeWeight, node] = Q.top();	
			int i = node.first;
			int j = node.second;
			Q.pop();

			// Destination reached
			if (i == rows - 1 && j == cols - 1)
				return nodeWeight;

			// visit the edges
			for (auto dir : dirs) {
				int x = i + dir[0];
				int y = j + dir[1];
				
				if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 0) {
					if (distance[x][y] > 1 + nodeWeight) {
						distance[x][y] = 1 + nodeWeight;
						Q.push({ distance[x][y], {x, y} });
					}
				}
			}
		}

		return distance[rows-1][cols-1];
	}

public:
	int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
		rows = grid.size();
		cols = grid[0].size();
		// Base Case:
		if (grid[0][0] == 1 || grid[rows - 1][cols - 1] == 1)
			return -1;

		int minimumPathLength = dijkstra(grid, {0, 0});
		return minimumPathLength == INT_MAX	? -1 : minimumPathLength;
	}
};

// BFS
class Solution3 {
private:
	vector<vector<int>> dirs = { {0,1}, {0,-1}, {1,0}, {-1,0}, {1,1}, {1,-1}, {-1,1}, {-1,-1} };
	int rows = 0, cols = 0;

	int BFS(vector<vector<int>>& grid, pair<int, int> source) {
		queue<pair<int, int>> Q;
		Q.push({source.first, source.second});
		grid[source.first][source.second] = 1; // mark visited

		int pathLength = 1;

		while (!Q.empty()) {
			int qSize = Q.size();
			while (qSize--) {
				auto [i, j] = Q.front();
				Q.pop();

				if (i == rows - 1 && j == cols - 1) {
					return pathLength;
				}

				for (auto dir : dirs) {
					int x = i + dir[0];
					int y = j + dir[1];

					// If neighbor is valid and unvisited
					if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 0) {
						Q.push({x, y});
						grid[x][y] = 1; // mark visited
					}
				}
			}
			pathLength++;
		}

		return INT_MAX;	//denotes no path exists
	}

public:
	int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
		rows = grid.size();
		cols = grid[0].size();
		// Base Case:
		if (grid[0][0] == 1 || grid[rows - 1][cols - 1] == 1)
			return -1;

		int minimumPathLength = BFS(grid, { 0, 0 });
		return minimumPathLength == INT_MAX ? -1 : minimumPathLength;
	}
};

int main() {
	Solution1 obj;
	vector<vector<int>> grid = {{0, 0, 0}, 
								{1, 1, 0}, 
								{1, 1, 0}};
	
	cout << obj.shortestPathBinaryMatrix(grid) << endl;
	
	grid = {{0, 0, 0},
			{1, 1, 1},
			{1, 1, 0}};

	cout << obj.shortestPathBinaryMatrix(grid) << endl;

	return 0;
}