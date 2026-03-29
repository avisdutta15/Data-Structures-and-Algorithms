#include <bits/stdc++.h>
using namespace std;

/*
    In a N x N grid representing a field of cherries, each cell is one of three possible integers.

    0 means the cell is empty, so you can pass through;
    1 means the cell contains a cherry, that you can pick up and pass through;
    -1 means the cell contains a thorn that blocks your way.

    Your task is to collect maximum number of cherries possible by following the rules below:

    Starting at the position (0, 0) and reaching (N-1, N-1) by moving right or down through 
    valid path cells (cells with value 0 or 1);
    After reaching (N-1, N-1), returning to (0, 0) by moving left or up through valid path cells;
    When passing through a path cell containing a cherry, you pick it up and the cell becomes 
    an empty cell (0); If there is no valid path between (0, 0) and (N-1, N-1), then no cherries can be collected.
    
    Example 1:

    Input: grid =
    [[0, 1, -1],
    [1, 0, -1],
    [1, 1,  1]]
    Output: 5
    Explanation: 
    The player started at (0, 0) and went down, down, right right to reach (2, 2).
    4 cherries were picked up during this single trip, and the matrix becomes [[0,1,-1],[0,0,-1],[0,0,0]].
    Then, the player went left, up, up, left to return home, picking up one more cherry.
    The total number of cherries picked up is 5, and this is the maximum possible.
*/

//Approach : 
class Solution1{
    int rows;
    int cols;
    public:
        int cherryPickup(vector<vector<int>> grid){
            rows = grid.size();
            if(rows==0)
                return 0;
            cols = grid[0].size();

            int cherriesCollected = dfs(grid, 0, 0, true);
            return max(0, cherriesCollected);  //why max(0, cherriesCollected)? because if we are not able to reach n-1,n-1
                                               //then cherries cherriesCollected will be -INF.
        }

        int dfs(vector<vector<int>> grid, int i, int j, bool isRound1){
            if(i<0 || i>=rows || j<0 || j>=cols || grid[i][j]==-1)
                return INT_MIN;
            
            int currentCellValue = grid[i][j];
            grid[i][j] = 0; //pick the cherry from the cell if there are any.

            int maxCherriesCollected;

            //when round1, start again.
            //when round2, we would have already made it 0 in round1
            //so return 0.
            if(i==rows-1 && j==cols-1){
                if(isRound1){
                    maxCherriesCollected = dfs(grid, 0, 0, false);
                }
                else{
                    return 0;
                }
            }
            else{
                int right = dfs(grid, i, j+1, isRound1);
                int down  = dfs(grid, i+1, j, isRound1);
                maxCherriesCollected = max(right, down);
            }
            grid[i][j] = currentCellValue;  //put the cherry back in the cell

            return maxCherriesCollected + currentCellValue;  //return the max cherries to its caller
        }
};

//Keep two persons. Both of them start their traversal from (0,0) to reach (n,n).
//how to avoid double counting? when both are standing at same position, count only for one.
class Solution2{
    int rows;
    int cols;
    public:
        int cherryPickup(vector<vector<int>> grid){
            rows = grid.size();
            if(rows==0)
                return 0;
            cols = grid[0].size();

            int cherriesCollected = dfs(grid, 0, 0, 0, 0);
            return max(0, cherriesCollected);
        }

        int dfs(vector<vector<int>> &grid, int r1, int c1, int r2, int c2){
            // if we went out of the grid or hit a thorn, discourage this path by returning Integer.MIN_VALUE
            if(r1<0 || r1>=rows || c1<0|| c1>=cols || r2<0 || r2>=rows || c2<0|| c2>=cols || grid[r1][c1]==-1 || grid[r2][c2]==-1)
                return INT_MIN;
            
            // if person 1 reached the bottom right, return what's in there (could be 1 or 0)
            if(r1==rows-1 && c1==cols-1)
                return grid[r1][c1];
            
            if(r2==rows-1 && c2==cols-1)
                return grid[r2][c2];
            
            int cherriesCollected;

            // if both persons standing on the same cell, don't double count and return what's in this cell (could be 1 or 0)
            if(r1==r2 && c1==c2){
                cherriesCollected = grid[r1][c1];
            }else{
                // otherwise, number of cherries collected by both of them equals the sum of what's on their cells
                cherriesCollected = grid[r1][c1] + grid[r2][c2];
            }

            // since each person of the 2 person can move only to the bottom or to the right, then the total number of cherries
            // equals the max of the following possibilities:
            //    P1     |      P2
            //   DOWN    |     DOWN
            //   DOWN    |     RIGHT
            //   RIGHT   |     DOWN
            //   RIGHT   |     RIGHT
            int p1Downp2Down = dfs(grid, r1+1, c1, r2+1, c2);
            int p1Downp2Right= dfs(grid, r1+1, c1, r2, c2+1);
            int p1Rightp2Down= dfs(grid, r1, c1+1, r2+1, c2);
            int p1Rightp2Right= dfs(grid, r1, c1+1, r2, c2+1);

            cherriesCollected += max(max(p1Downp2Down, p1Downp2Right),
                                     max(p1Rightp2Down, p1Rightp2Right)
                                    );
            return cherriesCollected;
        }
};


//Top Down:
/*
Let that above solution sink in. Now think about memoization. 
To make this solution use memoization, we have to think what states we have to preserve. 
Here we want to track r1,c1 and r2,c2 positions. We keep a cache with "r1c1r2c2" as key.
*/
class Solution3{
    int rows;
    int cols;
    public:
        int cherryPickup(vector<vector<int>> grid){
            rows = grid.size();
            if(rows==0)
                return 0;
            cols = grid[0].size();
            
            unordered_map<string, int> cache;
            int cherriesCollected = dfs(grid, 0, 0, 0, 0, cache);
            return max(0, cherriesCollected);
        }

        int dfs(vector<vector<int>> &grid, int r1, int c1, int r2, int c2, unordered_map<string, int> &cache){
            if(r1<0 || r1>=rows || c1<0|| c1>=cols || r2<0 || r2>=rows || c2<0|| c2>=cols || grid[r1][c1]==-1 || grid[r2][c2]==-1)
                return INT_MIN;

            string key = to_string(r1)+" "+to_string(c1)+" "+to_string(r2)+" "+to_string(c2);
            if(cache.count(key)>0)
                return cache[key];

            // if person 1 reached the bottom right, return what's in there (could be 1 or 0)
            if(r1==rows-1 && c1==cols-1)
                return cache[key] = grid[r1][c1];
            
            if(r2==rows-1 && c2==cols-1)
                return cache[key] = grid[r2][c2];
            
            int cherriesCollected;

            // if both persons standing on the same cell, don't double count and return what's in this cell (could be 1 or 0)
            if(r1==r2 && c1==c2){
                cherriesCollected = grid[r1][c1];
            }else{
                // otherwise, number of cherries collected by both of them equals the sum of what's on their cells
                cherriesCollected = grid[r1][c1] + grid[r2][c2];
            }

            // since each person of the 2 person can move only to the bottom or to the right, then the total number of cherries
            // equals the max of the following possibilities:
            //    P1     |      P2
            //   DOWN    |     DOWN
            //   DOWN    |     RIGHT
            //   RIGHT   |     DOWN
            //   RIGHT   |     RIGHT
            int p1Downp2Down = dfs(grid, r1+1, c1, r2+1, c2, cache);
            int p1Downp2Right= dfs(grid, r1+1, c1, r2, c2+1, cache);
            int p1Rightp2Down= dfs(grid, r1, c1+1, r2+1, c2, cache);
            int p1Rightp2Right= dfs(grid, r1, c1+1, r2, c2+1,cache);

            cherriesCollected += max(max(p1Downp2Down, p1Downp2Right),
                                     max(p1Rightp2Down, p1Rightp2Right)
                                    );
            return cache[key] = cherriesCollected;
        }
};

int main(){
    Solution obj;
    vector<vector<int>> grid = {{0, 1, -1},
                                {1, 0, -1},
                                {1, 1,  1}};

    cout<<obj.cherryPickup(grid)<<endl;

    grid = {{1, 1, -1},
            {1, -1, -1},
            {-1, 1,  1}};

}