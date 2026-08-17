#include <algorithm>
#include <iostream>
#include <climits>
#include <queue>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement: Minimum Steps to Reach Any Boundary Edge
    ------------------
    Given an m x n grid and a starting position (startX, startY),
    find the minimum number of steps to reach any boundary cell.
    You can move in all 4 directions (up, down, left, right).
    Some cells may have obstacles (1 = obstacle, 0 = free).

    Why NOT DP:
    -----------
    - Movement is 4-directional → cycles are possible.
    - No topological order exists → DP cannot be applied.
    - This is a shortest path problem → BFS.

    Without obstacles: Answer = min(startX, startY, m-1-startX, n-1-startY). O(1).
    With obstacles: BFS from start. O(m*n).
*/


// BFS — With obstacles
class Solution {
private:
    vector<vector<int>> dirs = { {0,1},{0,-1},{1,0},{-1,0} };
public:
    int minStepsToBoundary(vector<vector<int>>& grid, int startX, int startY) {
        int rows = grid.size();
        int cols = grid[0].size();

        // Base Case: if start is already at any boundary
        if (startX == 0 || startX == rows-1 || startY == 0 || startY == cols-1)
            return 0;

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        queue<pair<int,int>> Q;
        Q.push({startX, startY});
        visited[startX][startY] = true;
        int steps = 0;

        while (!Q.empty()) {
            int size = Q.size();
            steps++;

            while (size--) {
                auto [i, j] = Q.front(); Q.pop();

                for (auto dir : dirs) {
                    int x = i + dir[0];
                    int y = i + dir[1];
                    
                    // check for valid cell
                    if (x >= 0 && x < rows && y >= 0 && y < cols && !visited[x][y] && grid[x][y] == 0) {

                        // if reached boundary
                        if (x == 0 || x == rows - 1 || y == 0 || y == cols - 1) 
                            return steps;
                        
                        // else visit and push to Q
                        visited[x][y] = true;
                        Q.push({ x, y });
                    }
                    
                }
            }
        }
        return -1;
    }
};

int main() {
    Solution s2;
    vector<vector<int>> grid =
    { 
        { 1, 1, 1, 0, 1 },
        { 1, 0, 1, 0, 1 },
        { 0, 0, 1, 0, 1 },
        { 1, 0, 1, 1, 0 }
    };

    cout << "BFS (5x4, start 2,2): " << s2.minStepsToBoundary(grid, 2, 2) << endl;
    return 0;
}
