#include <bits/stdc++.h>
using namespace std;

/*
    Given a character matrix where every cell has one of the following values.

    'C' -->  This cell has coin

    '#' -->  This cell is a blocking cell. 
            We can not go anywhere from this.

    'E' -->  This cell is empty. We don't get
            a coin, but we can move from here.  
    Initial position is cell (0, 0) and initial direction is right.

    Following are rules for movements across cells.

    If face is Right, then we can move to below cells

    Move one step ahead, i.e., cell (i, j+1) and direction remains right.
    Move one step down and face left, i.e., cell (i+1, j) and direction becomes left.
    If face is Left, then we can move to below cells

    Move one step ahead, i.e., cell (i, j-1) and direction remains left.
    Move one step down and face right, i.e., cell (i+1, j) and direction becomes right.
    Final position can be anywhere and final direction can also be anything. The target 
    is to collect maximum coins.
*/

class Solution{
    int rows, cols;
    public:
        int maximumCoinsBeforeHitingDeadEndUtil(vector<vector<char>> &grid, int i, int j, string direction){
            if(i<0 || i>=rows || j<0 || j>=cols || grid[i][j]=='#')
                return 0;
            if(i==rows-1 && j==cols-1)
                return 1;

            int numCoins = 0;
            if(grid[i][j]=='C')
                numCoins = 1;
            
            if(direction=="right"){
                int right = maximumCoinsBeforeHitingDeadEndUtil(grid, i, j+1, direction);
                int downLeft = maximumCoinsBeforeHitingDeadEndUtil(grid, i+1, j, "left");
                numCoins = numCoins + max(right, downLeft);
            }

            if(direction=="left"){
                int left = maximumCoinsBeforeHitingDeadEndUtil(grid, i, j-1, direction);
                int downRight = maximumCoinsBeforeHitingDeadEndUtil(grid, i+1, j, "right");
                numCoins = numCoins + max(left, downRight);
            }

            return numCoins;
        }

        int maximumCoinsBeforeHitingDeadEnd(vector<vector<char>> grid){
            rows = grid.size();
            if(rows==0) return 0;
            cols = grid[0].size();
            string initialDirection = "right";
            return maximumCoinsBeforeHitingDeadEndUtil(grid, 0, 0, initialDirection);
        }
};

class Solution2{
    int rows, cols;
    unordered_map<string, int> lookup;
    public:
        int maximumCoinsBeforeHitingDeadEndUtil(vector<vector<char>> &grid, int i, int j, string direction){
            if(i<0 || i>=rows || j<0 || j>=cols || grid[i][j]=='#')
                return 0;
            if(i==rows-1 && j==cols-1)
                return 1;

            int numCoins = 0;
            if(grid[i][j]=='C')
                numCoins = 1;
            
            string key = to_string(i)+" "+to_string(j)+" "+direction;
            if(lookup.count(key)>0)
                return lookup[key];

            if(direction=="right"){
                int right = maximumCoinsBeforeHitingDeadEndUtil(grid, i, j+1, direction);
                int downLeft = maximumCoinsBeforeHitingDeadEndUtil(grid, i+1, j, "left");
                numCoins = numCoins + max(right, downLeft);
            }

            if(direction=="left"){
                int left = maximumCoinsBeforeHitingDeadEndUtil(grid, i, j-1, direction);
                int downRight = maximumCoinsBeforeHitingDeadEndUtil(grid, i+1, j, "right");
                numCoins = numCoins + max(left, downRight);
            }
            
            return (lookup[key] = numCoins);
        }

        int maximumCoinsBeforeHitingDeadEnd(vector<vector<char>> grid){
            rows = grid.size();
            if(rows==0) return 0;
            cols = grid[0].size();
            lookup.clear();
            
            string initialDirection = "right";
            return maximumCoinsBeforeHitingDeadEndUtil(grid, 0, 0, initialDirection);
        }
};

int main(){
    Solution2 obj;
    vector<vector<char>> grid = { {'E', 'C', 'C', 'C', 'C'}, 
                                  {'C', '#', 'C', '#', 'E'}, 
                                  {'#', 'C', 'C', '#', 'C'}, 
                                  {'C', 'E', 'E', 'C', 'E'}, 
                                  {'C', 'E', '#', 'C', 'E'} 
                                }; 
    cout<<obj.maximumCoinsBeforeHitingDeadEnd(grid);
}