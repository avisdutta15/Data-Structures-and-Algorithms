#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

/*
	Problem Statement:
	-----------------
	You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.
    Return the size of the largest island in grid after applying this operation.
    An island is a 4-directionally connected group of 1s.

 	Example:
	-------
	Example 1:
    Input: grid = [[1,0],[0,1]]
    Output: 3
    Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.
    
    Example 2:
    Input: grid = [[1,1],[1,0]]
    Output: 4
    Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 4.
    
    Example 3:
    Input: grid = [[1,1],[1,1]]
    Output: 4
    Explanation: Can't change any 0 to 1, only one island with area = 4.

	Approach:
	---------
	1. Traverse the grid, and label the islands starting from id=2 (why from 2 coz 0 is water and 1 is land)
       While labeling, also calculate their size.
       map[islandId][size]
    Edge Cases:
    2. If there is no land then map.size() == 0. So return 1 coz we would flip only one 0 to make it a land
       which will be the largest island.
    3. If the entire grid is an island i.e. full of 1's then return rows*cols
    Next: 
    4. Traverse through the grid again to try converting each 0 to a 1 and calculate the resulting island size:
        For each 0, check its neighboring cells (up, down, left, right) to find which islands are connected to it.
        Use a unordered set to store unique neighboring island IDs. Why set? i/p:
            {1, 1}
            {1, 0} Here 0 will see (0,0) (0,1) (1, 0) all are in same island so we should add the size of that 
                   island only once.
        unordered_set [!!!IMPORTANT]
        Sum the sizes of all unique neighboring islands and add 1 (to account for the flipped 0 turning into a 1).
        Update maxIslandSize with the maximum island size found.
*/

class Solution {
    vector<vector<int>> dirs = { {0, -1}, {-1, 0}, {1, 0}, {0, 1} };
    int rows = 0, cols = 0;
    void getIslandSizeLabelIt(vector<vector<int>>& grid, int i, int j, vector<vector<bool>>& visited, int& islandId, int& size) {
        visited[i][j] = true;
        grid[i][j] = islandId;
        size++;

        for (auto dir : dirs) {
            int x = i + dir[0];
            int y = j + dir[1];
            if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 1 && visited[x][y] == false) {
                getIslandSizeLabelIt(grid, x, y, visited, islandId, size);
            }
        }
    }

    int getIslandSizeLabelItBFS(vector<vector<int>>& grid, int i, int j, vector<vector<bool>>& visited, int& islandId) {
        int size = 0;
        queue<pair<int, int>> Q;
        Q.push({ i, j });
        visited[i][j] = true;
        

        while (!Q.empty()) {
            i = Q.front().first;
            j = Q.front().second;
            Q.pop();

            grid[i][j] = islandId;
            size++;

            for (auto dir : dirs) {
                int x = i + dir[0];
                int y = j + dir[1];
                if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] == 1 && visited[x][y] == false) {
                    Q.push({x, y});
                    visited[x][y] = true;
                }
            }
        }
        return size;
    }

    int areaAfterFlippingThisCell(vector<vector<int>>& grid, int& i, int& j, unordered_map<int, int>& labelSizeMap) {
        int area = 0;
        unordered_set<int> neighboringIslands;

        for (auto dir : dirs) {
            int x = i + dir[0];
            int y = j + dir[1];
            if (x >= 0 && x < rows && y >= 0 && y < cols && grid[x][y] > 1) {
                neighboringIslands.insert(grid[x][y]);
            }
        }

        // Sum the sizes of all unique neighboring islands
        for (int id : neighboringIslands) {
            area += labelSizeMap[id];
        }

        //finally flip this 0 to 1 and add it to the new island area
        area += 1;
        return area;
    }

public:
    int largestIsland(vector<vector<int>>& grid) {
        if (grid.size() == 0)
            return 0;

        rows = grid.size();
        cols = grid[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(cols));
        int islandId = 2;
        unordered_map<int, int> labelSizeMap;

        //traverse, label the island and get their size to store [islandId][size]
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 1 && visited[i][j] == false) {
                    int size = 0; 
                    //size = getIslandSizeLabelItBFS(grid, i, j, visited, islandId);
                    getIslandSizeLabelIt(grid, i, j, visited, islandId, size);
                    labelSizeMap[islandId] = size;
                    islandId++;
                }
            }
        }

        //if there are no lands then the max area possible is 1 i.e. by flipping 1 water
        if (labelSizeMap.size() == 0)
            return 1;

        //if the entire grid is an island i.e. full of 1's then return rows*cols
        if (labelSizeMap.size() == 1 && labelSizeMap[2] == rows * cols)
            return rows * cols;

        int maxAreaOfIsland = 0;

        //Traverse the grid, if encountered a 0, try to flip it and make it a part of the islands.
        //i.e. check all the 4 sides and add the island size if there are any.
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] == 0) {
                    maxAreaOfIsland = max(maxAreaOfIsland, areaAfterFlippingThisCell(grid, i, j, labelSizeMap));
                }
            }
        }
        return maxAreaOfIsland;
    }
}; 

int main()
{
	Solution obj;

    vector<vector<int>> grid = {{1, 0}, 
                                {0, 1}};    
    cout << obj.largestIsland(grid) << endl;

    grid = {{1, 1}, 
            {1, 0}};
    cout << obj.largestIsland(grid) << endl;

    grid = {{0, 0}, 
            {0, 0}};
    cout << obj.largestIsland(grid) << endl;

    grid = {{1, 1}, 
            {1, 1}};
    cout << obj.largestIsland(grid) << endl;

	return 0;
}

