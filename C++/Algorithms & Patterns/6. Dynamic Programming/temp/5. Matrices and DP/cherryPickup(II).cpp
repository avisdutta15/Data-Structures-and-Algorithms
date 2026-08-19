#include <bits/stdc++.h>
using namespace std;

/*
    Given a rows x cols matrix grid representing a field of cherries. Each cell in grid 
    represents the number of cherries that you can collect.

    You have two robots that can collect cherries for you, Robot #1 is located at the 
    top-left corner (0,0) , and Robot #2 is located at the top-right corner (0, cols-1) 
    of the grid.

    Return the maximum number of cherries collection using both robots  by following the rules below:

        From a cell (i,j), robots can move to cell (i+1, j-1) , (i+1, j) or (i+1, j+1).
        When any robot is passing through a cell, It picks it up all cherries, and the cell 
        becomes an empty cell (0).
        When both robots stay on the same cell, only one of them takes the cherries.
        Both robots cannot move outside of the grid at any moment.
        Both robots should reach the bottom row in the grid.
    
    Input: grid = [ [3,1,1],
                    [2,5,1],
                    [1,5,5],
                    [2,1,1]]
    Output: 24
    Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
    Cherries taken by Robot #1, (3 + 2 + 5 + 2) = 12.
    Cherries taken by Robot #2, (1 + 5 + 5 + 1) = 12.
    Total of cherries: 12 + 12 = 24.


Approach:
    The idea is to do both traversals concurrently. We start first from (0, 0) 
    and second traversal from (0, C-1) simultaneously. The important thing to 
    note is, at any particular step both traversals will be in same row as in 
    all possible three moves, row number is increased. Let (x1, y1) and (x2, y2) 
    denote current positions of first and second traversals respectively. Thus 
    at any time x1 will be equal to x2 as both of them move forward but variation 
    is possible along y. Since variation in y could occur in 3 ways no change (y), 
    go left (y – 1), go right (y + 1). So in total 9 combinations among y1, y2 are 
    possible.
*/

class Solution {
    int rows, cols;
    unordered_map<string, int> dp;
public:
    int cherryPickup(vector<vector<int>>& grid) {
        rows = grid.size();
        cols = grid[0].size();
        
        
        return dfs(grid, 0, 0, cols-1);        
    }
    
    int dfs(vector<vector<int>>& grid, int r1, int c1, int c2){
        if(c1<0 || c1>=cols || c2<0 || c2>=cols )
            return INT_MIN;
        
        string key = to_string(r1)+" "+to_string(c1)+" "+to_string(c2);
        if(dp.count(key)>0)
            return dp[key];

        if(r1==rows) //Reach to bottom row
            return 0;
        
        int currentCellValue = (c1==c2) ? grid[r1][c1] : grid[r1][c1] + grid[r1][c2];

        int cherriesCollected = 0;
        cherriesCollected = max(cherriesCollected, dfs(grid, r1+1, c1, c2-1));
        cherriesCollected = max(cherriesCollected, dfs(grid, r1+1, c1, c2));
        cherriesCollected = max(cherriesCollected, dfs(grid, r1+1, c1, c2+1));
        cherriesCollected = max(cherriesCollected, dfs(grid, r1+1, c1-1, c2-1));
        cherriesCollected = max(cherriesCollected, dfs(grid, r1+1, c1-1, c2));
        cherriesCollected = max(cherriesCollected, dfs(grid, r1+1, c1-1, c2+1));
        cherriesCollected = max(cherriesCollected, dfs(grid, r1+1, c1+1, c2));
        cherriesCollected = max(cherriesCollected, dfs(grid, r1+1, c1+1, c2-1));
        cherriesCollected = max(cherriesCollected, dfs(grid, r1+1, c1+1, c2+1));

        cherriesCollected = cherriesCollected + currentCellValue;

        return dp[key] = cherriesCollected;
    }
};