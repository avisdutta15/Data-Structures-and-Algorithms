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
	You are given an m x n matrix board containing letters 'X' and 'O', capture regions that are surrounded:
	- Connect: A cell is connected to adjacent cells horizontally or vertically.
	- Region: To form a region connect every 'O' cell.
	- Surround: A region is surrounded if none of the 'O' cells in that region are on the edge of the board.
	Such regions are completely enclosed by 'X' cells.

	To capture a surrounded region, replace all 'O's with 'X's in-place within the original board.
	You do not need to return anything.

	Example:
	--------
	Input: board = [["X","X","X","X"],
					["X","O","O","X"],
					["X","X","O","X"],
					["X","O","X","X"]]

		   Output: [["X","X","X","X"],
					["X","X","X","X"],
					["X","X","X","X"],
					["X","O","X","X"]]

	In the above diagram, the bottom region is not captured because it is on the edge of the
	board and cannot be surrounded.


	Approach:
	---------
	Boundary DFS traversal to make all 'O' to '1'.
	Traverse the grid again and make '1' to 'O' and any internal 'O' to 'X'.

*/

// DFS solution
class Solution {
private:
	vector<vector<int>> dirs = { {0, 1}, {0,-1}, {1,0}, {-1,0} };
	int rows = 0, cols = 0;

	void DFS(vector<vector<char>>& board, int i, int j) {
		board[i][j] = '1';
		for (auto dir : dirs) {
			int x = i + dir[0];
			int y = j + dir[1];

			if (x >= 0 && x < rows && y >= 0 && y < cols && board[x][y] == 'O') {
				DFS(board, x, y);
			}
		}
	}

public:
	void solve(vector<vector<char>>& board) {
		rows = board.size();
		cols = board[0].size();

		// traverse the board.
		// for evey border 'O' then DFS and set '1' to all connected 'O's
		/*for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if ((i == 0 || i == rows - 1 || j == 0 || j == cols - 1) && board[i][j] == 'O') {
					DFS(board, i, j);
				}
			}
		}*/

		// Optimization : Traverse only the boundary cells
		for (int col = 0; col < cols; col++) {
			if (board[0][col] == 1)
				DFS(board, 0, col);
			if (board[rows-1][col] == 1)
				DFS(board, rows-1, col);
		}

		for (int row = 0; row < rows; row++) {
			if (board[row][0] == 1) 
				DFS(board, row, 0);
			if (board[row][cols - 1] == 1)
				DFS(board, row, cols-1);
		}

		// traverse the board again.
		// if it is an internal 'O' then make it 'X'
		// if it is a '1' then make it 'O'
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (board[i][j] == '1')
					board[i][j] = 'O';	// It was connected to a border, revert to 'O'
				else if (i > 0 && i < rows - 1 && j>0 && j < cols - 1 && board[i][j] == 'O')
					board[i][j] = 'X';	// It was completely surrounded, capture it
			}
		}
	}
};

// Multi-Source BFS solution
class Solution2 {
private:
	vector<vector<int>> dirs = { {0, 1}, {0,-1}, {1,0}, {-1,0} };
	int rows = 0, cols = 0;
public:
	void solve(vector<vector<char>>& board) {
		rows = board.size();
		cols = board[0].size();
		queue<pair<int, int>> Q;

		// Optimization : Traverse only the boundary cells
		// for evey border 'O' set '1' to all connected 'O's
		for (int col = 0; col < cols; col++) {
			if (board[0][col] == 'O') {
				Q.push({ 0, col });
				board[0][col] = '1';
			}
			if (board[rows - 1][col] == 'O') {
				Q.push({ rows - 1, col });
				board[rows - 1][col] = '1';
			}
		}

		for (int row = 0; row < rows; row++) {
			if (board[row][0] == 'O') {
				Q.push({ row, 0 });
				board[row][0] = '1';
			}
			if (board[row][cols - 1] == 'O') {
				Q.push({ row, cols - 1 });
				board[row][cols - 1] = '1';
			}
		}

		while (!Q.empty()) {
			auto front = Q.front(); Q.pop();
			int i = front.first;
			int j = front.second;

			for (auto dir : dirs) {
				int x = i + dir[0];
				int y = j + dir[1];

				if (x >= 0 && x < rows && y >= 0 && y < cols && board[x][y] == 'O') {
					Q.push({ x, y });
					board[x][y] = '1';
				}
			}
		}

		// traverse the board again.
		// if it is an internal 'O' then make it 'X'
		// if it is a '1' then make it 'O'
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (board[i][j] == '1')
					board[i][j] = 'O';	// It was connected to a border, revert to 'O'
				else if (i > 0 && i < rows - 1 && j>0 && j < cols - 1 && board[i][j] == 'O')
					board[i][j] = 'X';	// It was completely surrounded, capture it
			}
		}
	}
};


int main() {
	Solution obj;

	vector<vector<char>> board = {
		{'X', 'X', 'X', 'X'},
		{'X', 'O', 'O', 'X'},
		{'X', 'X', 'O', 'X'},
		{'X', 'O', 'X', 'X'}
	};

	obj.solve(board);

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[0].size(); j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}