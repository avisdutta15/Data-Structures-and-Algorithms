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
	Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.
    The distance between two cells sharing a common edge is 1.

    Examples:
    --------
    Example 1:

    Input: 
    [0, 0, 0]
    [0, 1, 0]
    [0, 0, 0]

    Output:
    [0, 0, 0]
    [0, 1, 0]
    [0, 0, 0]

    Example 2:

    Input: 
    [0, 0, 0]
    [0, 1, 0]
    [1, 1, 1]

    Output: 
    [0, 0, 0]
    [0, 1, 0]
    [1, 2, 1]

	Approach:
	---------
    We need to find the smallest distance. We can use BFS.
    Why BFS and not Dijkstra? - Because this does not have any edge cost.

    Okay so start the BFS for evey 1 in the grid. As soon as you get a cell with 0 return the level.
    Time Complexity - O(m*n) * O(m*n)
    
    The key insight is to think of this problem in reverse. Instead of finding the distance from each 1 
    to the nearest 0, we start from all 0s and expand outward simultaneously.

    Imagine dropping stones into water at multiple points - each 0 is like a stone creating ripples. These 
    ripples expand outward at the same speed, and when a ripple reaches a cell for the first time, that's 
    the shortest distance from that cell to any 0.

    Why does this work better than starting from each 1? If we started from each 1 and searched for the 
    nearest 0, we'd potentially repeat a lot of work. For a matrix with many 1s and few 0s, we'd be running BFS many times.

    By using multi-source BFS starting from all 0s simultaneously, we:
        Visit each cell exactly once
        Guarantee that the first time we reach a cell, we've found the shortest path to it
        Achieve optimal time complexity of O(m × n)
        The BFS naturally processes cells in layers:

    Layer 0: All cells containing 0 (distance = 0)
    Layer 1: All cells adjacent to any 0 (distance = 1)
    Layer 2: All cells at distance 2 from the nearest 0
    And so on...
    This layer-by-layer expansion ensures that when we first visit a cell, we've found its minimum distance 
    to any 0. We mark visited cells (using ans[x][y] = -1 as "unvisited") to avoid processing them again, which 
    prevents infinite loops and ensures correctness.

	Time Complexity: O(m*n)
*/

class SolutionNaive{
private:
    int rows = 0, cols = 0;
    vector<vector<int>> dirs = { {0,1},{1,0},{0,-1},{-1,0} };

    //returns the distance of the nearest 0 for the 1 in cell (i,j)
    int distanceFromOne(vector<vector<int>>& mat, int i, int j) {
        queue<pair<int, int>> Q;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        Q.push({ i, j });
        visited[i][j] = true;

        int level = 0;

        //start BFS
        while (!Q.empty()) {
            level++;
            int levelSize = Q.size();
            while (levelSize--) {
                int _i = Q.front().first;
                int _j = Q.front().second;
                Q.pop();

                for (auto dir : dirs) {
                    int x = _i + dir[0];
                    int y = _j + dir[1];
                    if (x >= 0 && x < rows && y >= 0 && y < cols && visited[x][y] == false) {
                        //if this is a 0 then return the current level/distance
                        if (mat[x][y] == 0)
                            return level;
                        else
                        {
                            Q.push({ x, y });
                            visited[x][y] = true;
                        }
                    }
                }
            }            
        }
        return level;
    }

public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        if (mat.size() == 0)
            return vector<vector<int>>();

        rows = mat.size();
        cols = mat[0].size();

        vector<vector<int>> distance(rows, vector<int>(cols, 0));

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                // if the cell has 0 then its distance of nearest 0 is 0
                if (mat[i][j] == 0)
                    distance[i][j] = 0;
                // if the cell has 1 then its distance of nearest 0 is the BFS
                else
                    distance[i][j] = distanceFromOne(mat, i, j);
            }
        }
        return distance;
    }
};

class Solution {
    int rows = 0, cols = 0;
    vector<vector<int>> dirs = { {0,1},{1,0},{0,-1},{-1,0} };
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        if (mat.size() == 0)
            return vector<vector<int>>();

        rows = mat.size();
        cols = mat[0].size();

        vector<vector<int>>distance(rows, vector<int>(cols, -1));
        queue<pair<int, int>> Q;
        int level = 0;

        //Multi Source BFS
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (mat[i][j] == 0) {
                    distance[i][j] = level;
                    Q.push({ i, j });
                }
            }
        }

        while (!Q.empty()) {
            int levelSize = Q.size();
            level++;
            while (levelSize--) {
                int _i = Q.front().first;
                int _j = Q.front().second;
                Q.pop();

                for (auto dir : dirs) {
                    int x = _i + dir[0];
                    int y = _j + dir[1];

                    if (x >= 0 && x < rows && y >= 0 && y < cols && distance[x][y] == -1) {
                        distance[x][y] = level;
                        Q.push({ x, y });
                    }
                }
            }
        }
        return distance;
    }
};

void printMatrix(vector<vector<int>>& mat) {
    int rows = mat.size();
    int cols = mat[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    SolutionNaive obj1;
    vector<vector<int>> mat = {
                                { 0, 0, 0 },
                                { 0, 1, 0 },
                                { 0, 0, 0 }
                              };
    cout << "Naive:" << endl;
    cout << "Input:" << endl;
    printMatrix(mat);
    cout << endl;
    auto distance = obj1.updateMatrix(mat);
    cout << "Output:" << endl;
    printMatrix(distance);
    cout << endl;

    mat = {
        { 0, 0, 0 },
        { 0, 1, 0 },
        { 1, 1, 1 }
    };
    cout << "Input:" << endl;
    printMatrix(mat);
    cout << endl;
    distance = obj1.updateMatrix(mat);
    cout << "Output:" << endl;
    printMatrix(distance);
    cout << endl;


    mat = {
        { 0, 1, 1 },
        { 1, 1, 1 },
        { 1, 1, 1 }
    };
    cout << "Input:" << endl;
    printMatrix(mat);
    cout << endl;
    distance = obj1.updateMatrix(mat);    
    cout << "Output:" << endl;
    printMatrix(distance);

    cout << endl;
    cout << "BFS:" << endl;
    Solution obj2;
    mat = {
                                { 0, 0, 0 },
                                { 0, 1, 0 },
                                { 0, 0, 0 }
    };
    cout << "Input:" << endl;
    printMatrix(mat);
    cout << endl;
    distance = obj2.updateMatrix(mat);
    cout << "Output:" << endl;
    printMatrix(distance);
    cout << endl;

    mat = {
        { 0, 0, 0 },
        { 0, 1, 0 },
        { 1, 1, 1 }
    };
    cout << "Input:" << endl;
    printMatrix(mat);
    cout << endl;
    distance = obj2.updateMatrix(mat);
    cout << "Output:" << endl;
    printMatrix(distance);
    cout << endl;


    mat = {
        { 0, 1, 1 },
        { 1, 1, 1 },
        { 1, 1, 1 }
    };
    cout << "Input:" << endl;
    printMatrix(mat);
    cout << endl;
    distance = obj2.updateMatrix(mat);
    cout << "Output:" << endl;
    printMatrix(distance);

    return 0;

}
