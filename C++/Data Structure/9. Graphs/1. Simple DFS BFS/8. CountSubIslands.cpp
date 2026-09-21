#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <queue>
#include <unordered_map>
#include <stack>
using namespace std;

/*
	Problem Statement:
	-----------------
	Count Sub Islands: Given two binary grids grid1 and grid2, count the number of islands in grid2 
	that are also islands in grid1 (sub-islands).
	
	An island is a 4-directionally connected group of 1s.
	A sub-island in grid2 is an island where every cell of that island corresponds to a 1 in grid1.

 	Example:
	-------
	grid1 = [[1,1,1,0,0],    grid2 = [[1,1,1,0,0],
	         [0,1,1,1,1],             [0,0,1,1,1],
	         [0,0,0,0,0],             [0,1,0,0,0],
	         [1,0,0,0,0],             [1,0,1,1,0],
	         [1,1,0,1,1]]             [0,1,0,1,0]]
	
	Output: 3 (three islands in grid2 are completely contained within islands in grid1)

	Approach:
	---------
	1. For each island in grid2, use DFS to traverse all connected cells
	2. During traversal, check if every cell in the island has a corresponding 1 in grid1
	3. If any cell in the island corresponds to 0 in grid1, the entire island is not a sub-island
       But donot stop the DFS in the midway. Continue to expore island in grid2. If we 
       dont explore then this will give us wrong result. Why?

       Lets say we stop when we find two cells not matching.
       At (0,0)
       [0,0,0]      [1,1,0]         [T, F, F]
       [0,1,0]      [0,1,0]         [F, F, F]
        grid1        grid2           visited
       
       Since grid1(0,0) != grid2(0,0), we break the traversal and don't traverse the entire island.

       At (0,1)
       [0,0,0]      [1,1,0]         [T, T, F]
       [0,1,0]      [0,1,0]         [F, F, F]
        grid1        grid2           visited

       Since grid2(0,1) is connected to already visited (0,0), we can't start fresh DFS here.

       At (1,1)
       [0,0,0]      [1,1,0]         [T, T, F]
       [0,1,0]      [0,1,0]         [F, T, F]
        grid1        grid2           visited

       Now we find grid1(1,1) == grid2(1,1) == 1, so we return true as isSubIsland.
       But this is WRONG! Because (1,1) is actually part of the same island as (0,0) and (0,1).
       The entire island should be invalid because it contains cells where grid1 has 0.

       Correct approach: Continue DFS to mark ALL cells of the island as visited, even after
       finding a mismatch. This prevents counting parts of the same island multiple times.

	4. Count only the valid sub-islands

    Reference: https://www.youtube.com/watch?v=eQAEwsct794

    KEY TAKEAWAY : CONTINUE THE TRAVERSAL OF THE ISLAND IN GRID 2 EVEN IF THE CELLS DONOT MATCH
*/

class Solution {
    // Directions for 4-directional movement: right, down, up, left
    static constexpr int dirs[4][2] = { {0,1},{1,0},{-1,0},{0,-1} };
    int rows = 0, cols = 0;
    
    /**
     * Alternative DFS implementation that returns boolean result directly
     * This approach marks visited cells as 0 and uses return value to track validity
     */
    bool dfsAlternate(vector<vector<int>>& grid1, vector<vector<int>>& grid2, int i, int j) {
        // Mark current cell as visited by setting it to 0
        grid2[i][j] = 0;
        
        // Check if current cell makes this a valid sub-island cell
        // If grid1[i][j] == 0, then this island in grid2 is NOT a sub-island
        bool isSubIsland = (grid1[i][j] == 1);

        // Continue DFS to all 4-directionally connected cells
        for (int d = 0; d < 4; d++) {
            int x = i + dirs[d][0];
            int y = j + dirs[d][1];

            // Check bounds and if the neighbor cell is unvisited land in grid2
            if (x >= 0 && x < rows && y >= 0 && y < cols && grid2[x][y] == 1) {
                // Recursively check neighbor and combine results using AND
                // If any part of the island is invalid, the whole island becomes invalid
                if (!dfsAlternate(grid1, grid2, x, y)) {
                    isSubIsland = false;
                }
            }
        }
        return isSubIsland;
    }

    /**
     * DFS implementation using reference parameter to track validity
     * This approach marks visited cells as 2 and uses reference to update validity
     */
    void dfs(vector<vector<int>>& grid1, vector<vector<int>>& grid2, int i, int j, bool& isSubIsland) {
        // Mark current cell as visited by setting it to 2 (to distinguish from water=0 and land=1)
        grid2[i][j] = 2;
        
        // CRITICAL: Check if current cell is valid for sub-island
        // If grid1[i][j] == 0 but grid2[i][j] was 1, this island is NOT a sub-island
        if (grid1[i][j] == 0) {
            isSubIsland = false;
        }

        // Explore all 4 directions
        for (auto dir : dirs) {
            int x = i + dir[0];
            int y = j + dir[1];
            
            // Check bounds and if neighbor is unvisited land in grid2
            if (x >= 0 && x < rows && y >= 0 && y < cols && grid2[x][y] == 1) {
                // Continue DFS traversal
                // Note: We don't need to check grid1[x][y] here because each cell
                // will be validated when it becomes the current cell in the recursive call
                dfs(grid1, grid2, x, y, isSubIsland);
            }
        }
    }

    void bfs(vector<vector<int>>& grid1, vector<vector<int>>& grid2, int i, int j, bool& isSubIsland) {
        queue<pair<int, int>> Q;

        Q.push({ i, j });
        grid2[i][j] = 2;

        while (!Q.empty()) {
            i = Q.front().first;
            j = Q.front().second;
            Q.pop();

            if (grid1[i][j] == 0)
                isSubIsland = false;

            for (auto dir : dirs) {
                int x = i + dir[0];
                int y = j + dir[1];
                if (x >= 0 && x < rows && y >= 0 && y < cols && grid2[x][y] == 1) {
                    grid2[x][y] = 2;
                    Q.push({ x, y });
                }
            }
        }
    }
public:
    /**
     * Main function to count sub-islands in grid2 that are completely contained in grid1
     * 
     * Algorithm:
     * 1. Iterate through every cell in grid2
     * 2. When we find an unvisited land cell (1), start DFS to explore the entire island
     * 3. During DFS, check if every cell of this island corresponds to land in grid1
     * 4. If all cells are valid, increment the sub-island counter
     * 
     * Time Complexity: O(m*n) where m,n are grid dimensions
     * Space Complexity: O(m*n) for recursion stack in worst case
     */
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        // Handle edge cases
        if (grid2.empty() || grid2[0].empty())
            return 0;

        // Initialize grid dimensions
        rows = grid2.size();
        cols = grid2[0].size();
        int subIslands = 0;
        bool isSubIsland;

        // Iterate through every cell in grid2
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                // If we find an unvisited land cell, start exploring the island
                if (grid2[i][j] == 1) {
                    // Assume this island is valid initially
                    isSubIsland = true;
                    
                    // Use DFS to explore the entire island and validate it
                    dfs(grid1, grid2, i, j, isSubIsland);
                    //bfs(grid1, grid2, i, j, isSubIsland);
                    
                    // If the entire island is valid, count it as a sub-island
                    if (isSubIsland == true)
                        subIslands++;
                }
            }
        }
        return subIslands;
    }
};
int main()
{
	Solution obj;

    // Test case 1: Basic example
    vector<vector<int>> grid1 = {   {1, 1, 1, 0, 0},
                                    {0, 1, 1, 1, 1},
                                    {0, 0, 0, 0, 0},
                                    {1, 0, 0, 0, 0},
                                    {1, 1, 0, 1, 1} };

    vector<vector<int>> grid2 = {   {1, 1, 1, 0, 0},
                                    {0, 0, 1, 1, 1},
                                    {0, 1, 0, 0, 0},
                                    {1, 0, 1, 1, 0},
                                    {0, 1, 0, 1, 0} };

    cout << "Test case 1: " << obj.countSubIslands(grid1, grid2) << endl;

    return 0;
}