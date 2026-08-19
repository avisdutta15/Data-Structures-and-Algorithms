#include <bits/stdc++.h>
using namespace std;

/*
    Given a matrix where every cell represents points. How to collect 
    maximum points using two traversals under following conditions?
    Let the dimensions of given grid be R x C.

    1. The first traversal starts from top left corner, i.e., (0, 0) and 
    should reach left bottom corner, i.e., (R-1, 0). 
    2. The second traversal starts from top right corner, i.e., (0, C-1) 
    and should reach bottom right corner, i.e., (R-1, C-1).
    3. From a point (i, j), we can move to (i+1, j+1) or (i+1, j-1) or (i+1, j)
    
    A traversal gets all points of a particular cell through which it passes. 
    If one traversal has already collected points of a cell, then the other 
    traversal gets no points if goes through that cell again.
    
    Input :
        int arr[R][C] = {{3, 6, 8, 2},
                        {5, 2, 4, 3},
                        {1, 1, 20, 10},
                        {1, 1, 20, 10},
                        {1, 1, 20, 10},
                        };

        Output: 73

    Explanation :
    First traversal collects total points of value 3 + 2 + 20 + 1 + 1 = 27
    Second traversal collects total points of value 2 + 4 + 10 + 20 + 10 = 46.
    Total Points collected = 27 + 46 = 73.

    Approach:
    The idea is to do both traversals concurrently. We start first from (0, 0) 
    and second traversal from (0, C-1) simultaneously. The important thing to 
    note is, at any particular step both traversals will be in same row as in 
    all possible three moves, row number is increased. Let (x1, y1) and (x2, y2) 
    denote current positions of first and second traversals respectively. Thus at 
    any time x1 will be equal to x2 as both of them move forward but variation is 
    possible along y. Since variation in y could occur in 3 ways no change (y), 
    go left (y – 1), go right (y + 1). So in total 9 combinations among y1, y2 are 
    possible. The 9 cases as mentioned below after base cases.
*/

class Solution{
        int rows;
        int cols;
        int maxPointsWithTwoTraversalRecursive(vector<vector<int>> &grid, int row, int col1, int col2){
            // if out of bounds then return not possible.
            if(row>=rows || col1<0 || col2<0 || col1>=cols || col2>=cols)
                return INT_MIN;
            
            if(row == rows-1){
                // if at the last row, the target cells are reached.
                if(col1==0 && col2==cols-1)
                    return grid[row][col1] + grid[row][col2];
                // this means the control reached the last row but not the target cells, then its not possible.
                else
                    return INT_MIN;         
            } 
            
            int maxPointAtThisRow = 0;
            //if the robots are at the same cell, count it only once.
            if(col1 == col2)
                maxPointAtThisRow = grid[row][col1];
            else
                maxPointAtThisRow = grid[row][col1] + grid[row][col2];
            
            maxPointAtThisRow = maxPointAtThisRow + max({
                maxPointsWithTwoTraversalRecursive(grid, row + 1, col1-1, col2-1),
                maxPointsWithTwoTraversalRecursive(grid, row + 1, col1-1, col2),
                maxPointsWithTwoTraversalRecursive(grid, row + 1, col1-1, col2+1),

                maxPointsWithTwoTraversalRecursive(grid, row + 1, col1, col2-1),
                maxPointsWithTwoTraversalRecursive(grid, row + 1, col1, col2),
                maxPointsWithTwoTraversalRecursive(grid, row + 1, col1, col2+1),

                maxPointsWithTwoTraversalRecursive(grid, row + 1, col1+1, col2-1),
                maxPointsWithTwoTraversalRecursive(grid, row + 1, col1+1, col2),
                maxPointsWithTwoTraversalRecursive(grid, row + 1, col1+1, col2+1)
            });

            return maxPointAtThisRow;
        }

        int maxPointsWithTwoTraversalTopDown(vector<vector<int>> &grid, int row, int col1, int col2, unordered_map<string, int> &lookup){
            // if out of bounds then return not possible.
            if(row>=rows || col1<0 || col2<0 || col1>=cols || col2>=cols)
                return INT_MIN;
            
            if(row == rows-1){
                // if at the last row, the target cells are reached.
                if(col1==0 && col2==cols-1)
                    return grid[row][col1] + grid[row][col2];
                // this means the control reached the last row but not the target cells, then its not possible.
                else
                    return INT_MIN;         
            } 
            
            string key = to_string(row) + " " + to_string(col1) + " " + to_string(col2);
            if(lookup.find(key) != lookup.end())
                return lookup[key];

            int maxPointAtThisRow = 0;
            //if the robots are at the same cell, count it only once.
            if(col1 == col2)
                maxPointAtThisRow = grid[row][col1];
            else
                maxPointAtThisRow = grid[row][col1] + grid[row][col2];
            
            maxPointAtThisRow = maxPointAtThisRow + max({
                maxPointsWithTwoTraversalTopDown(grid, row + 1, col1-1, col2-1, lookup),
                maxPointsWithTwoTraversalTopDown(grid, row + 1, col1-1, col2, lookup),
                maxPointsWithTwoTraversalTopDown(grid, row + 1, col1-1, col2+1, lookup),

                maxPointsWithTwoTraversalTopDown(grid, row + 1, col1, col2-1, lookup),
                maxPointsWithTwoTraversalTopDown(grid, row + 1, col1, col2, lookup),
                maxPointsWithTwoTraversalTopDown(grid, row + 1, col1, col2+1, lookup),

                maxPointsWithTwoTraversalTopDown(grid, row + 1, col1+1, col2-1, lookup),
                maxPointsWithTwoTraversalTopDown(grid, row + 1, col1+1, col2, lookup),
                maxPointsWithTwoTraversalTopDown(grid, row + 1, col1+1, col2+1, lookup)
            });

            return lookup[key] = maxPointAtThisRow;
        }

        int maxPointsWithTwoTraversalBottomUp(vector<vector<int>> &grid){
            vector<vector<vector<int>>> dp(rows+1, vector<vector<int>>(cols+1, vector<int>(cols+1, 0)));

            for(int row = rows; row>=0; row--){
                for(int col1 = 0; col1 <= cols; col1++){
                    for(int col2 = 0; col2<=cols; col2++){
                        if(row>=rows || col1<0 || col2<0 || col1>=cols || col2>=cols)
                            dp[row][col1][col2] = INT_MIN;
                        
                        else if(row == rows-1){
                            // if at the last row, the target cells are reached.
                            if(col1==0 && col2==cols-1)
                                dp[row][col1][col2] = grid[row][col1] + grid[row][col2];
                            // this means the control reached the last row but not the target cells, then its not possible.
                            else
                                dp[row][col1][col2] = INT_MIN;         
                        }
                        else{
                            int maxPointAtThisRow = 0;
                            //if the robots are at the same cell, count it only once.
                            if(col1 == col2)
                                maxPointAtThisRow = grid[row][col1];
                            else
                                maxPointAtThisRow = grid[row][col1] + grid[row][col2];
                            
                            // Try all 9 possible moves
                            for (int move1 = -1; move1 <= 1; move1++) {
                                for (int move2 = -1; move2 <= 1; move2++) {
                                    int nc1 = col1 + move1, nc2 = col2 + move2;

                                    if (nc1 >= 0 && nc1 < cols && nc2 >= 0 && nc2 < cols)
                                        maxPointAtThisRow = max(maxPointAtThisRow, dp[row + 1][nc1][nc2]);
                                }
                            }
                
                            dp[row][col1][col2] = maxPointAtThisRow;
                        }
                            
                    }
                }
            }

            return dp[0][0][cols-1];
        }
        
    public:
        int maxPointsWithTwoTraversal(vector<vector<int>> &grid){
            rows = grid.size();
            cols = grid[0].size();
            //return maxPointsWithTwoTraversalRecursive(grid, 0, 0, cols-1);

            // unordered_map<string, int> lookup;
            // return maxPointsWithTwoTraversalTopDown(grid, 0, 0, cols-1, lookup);
            
            return maxPointsWithTwoTraversalBottomUp(grid);     //doesnot work. Need to revisit. Above all works.
        }
};


int main(){
    Solution obj;
    vector<vector<int>> grid = 
                            {   {3, 6, 8, 2},
                                {5, 2, 4, 3},
                                {1, 1, 20, 10},
                                {1, 1, 20, 10},
                                {1, 1, 20, 10},
                            };

    cout<<obj.maxPointsWithTwoTraversal(grid)<<endl; //73
}