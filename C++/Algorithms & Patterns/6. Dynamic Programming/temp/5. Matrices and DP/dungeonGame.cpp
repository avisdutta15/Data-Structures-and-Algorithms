#include<bits/stdc++.h>
using namespace std;

/*
    The demons had captured the princess (P) and imprisoned her in the bottom-right corner of 
    a dungeon. The dungeon consists of M x N rooms laid out in a 2D grid. Our valiant knight (K) 
    was initially positioned in the top-left room and must fight his way through the dungeon to 
    rescue the princess.

    The knight has an initial health point represented by a positive integer. If at any point his 
    health point drops to 0 or below, he dies immediately.

    Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon 
    entering these rooms; other rooms are either empty (0's) or contain magic orbs that increase 
    the knight's health (positive integers).

    In order to reach the princess as quickly as possible, the knight decides to move only rightward 
    or downward in each step.

    Write a function to determine the knight's minimum initial health so that he is able to rescue 
    the princess.

    For example, given the dungeon below, the initial health of the knight must be at least 7 if 
    he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.

    -2 (K)	-3	3
    -5	-10	1
    10	30	-5 (P)
 

    Note:

    The knight's health has no upper bound.
    Any room can contain threats or power-ups, even the first room the knight enters and the 
    bottom-right room where the princess is imprisoned.


    Approach:
    We start recursion. At each cell we have 2 options: go right / go down.
    At each cell we want to know how much of minimum energy is needed to enter this cell,
    fight the deamon if present, be alive after fighting the deamon and move forward to 
    another cell.
    Now suppose in recursion we reached the queen [the last cell]. So at this cell we 
    have 2 things to observe in order to know the minimum amount of energy needed to 
    enter this cell.
    If any deamon is present in this cell then we will loose this enegy in fighting,
    and need 1 amount of energy left to survive and get the queen.
    Therefore,      energyNeededToEnterThisCell + (-energyToFightTheDaemon) = 1   [why energyToFightTheDaemon is -ve? given in question]
                =>  energyNeededToEnterThisCell = 1 - (-energyToFightTheDaemon)
    If no deamon, then there is food. So we can enter this cell with the minimum amount of 
    energy i.e. 1.

    So when we reach the queen / last cell,
        if(dungeon[i][j]<0) //then there is deamon
            return 1-dungeon[i][j];
        else
            return 1;
    
    Now we are standing on any other cell.
        minimumEnergyNeededToEnterRightCell = dfs(i, j+1);
        minimumEnergyNeededToEnterDownCell  = dfs(i+1, j);
    
        So I will choose the minimum of this 2 for my path.
        minHealthRequiredToExitTheCell = min(minimumEnergyNeededToEnterRightCell, minimumEnergyNeededToEnterDownCell)

        Now i need to calculate the healthRequiredToEnterThisCell.
        if(dungeon[i][j] < minHealthRequiredToExitTheCell)
            healthRequiredToEnterThisCell = dungeon[i][j] - minHealthRequiredToExitTheCell
        else 
            healthRequiredToEnterThisCell = 1
    return healthRequiredToEnterThisCell;
*/

//Recursion
class Solution{
    int rows;
    int cols;
    public:
        int calculateMinimumHP(vector<vector<int>> &dungeon){
            rows = dungeon.size();
            cols = dungeon[0].size();
            return solve(dungeon, 0, 0);
        }

        //returns the minimum health required to enter a cell (i,j)
        int solve(vector<vector<int>> &dungeon, int i, int j){
            //if you go out of the grid then you cannot reach queen, so return +INF
            if(i<0 || i>=rows || j<0 || j>=cols)
                return INT_MAX;
            
            //if you reached the queen
            //then check if there is a deamon in that cell. If yes then you need some 
            //health to enter and survive in order to get the queen. Minimum health to
            //survive after fighting the deamon = 1. So min health required to enter the
            //cell, fight the deamon and get the queen will be 1-dungeon[i][j].
            //If there is no deamon in the last cell, then you donot need any energy to
            //fight, so the minimum health required = 1 
            if(i==rows-1 && j==cols-1){
                if(dungeon[i][j]<0)
                    return 1-dungeon[i][j];
                return 1;
            }

            int goDown = solve(dungeon, i+1, j);
            int goRight= solve(dungeon, i, j+1);

            int minHealthRequiredToExitTheCell = min(goDown, goRight);

            //if minHealthRequired is < the current enegy (can be negative due to a deamon,
            //or a less positive number), then the knight more energy while he entered the cell
            //i.e. minHealthRequiredToExitTheCell = healthRequiredToEnterThisCell + theEnergyGainedOrLostInThisCell
            //  => healthRequiredToEnterThisCell  = minHealthRequiredToExitTheCell - theEnergyGainedOrLostInThisCell
            //if 

            int healthRequiredToEnterThisCell;
            if(dungeon[i][j] < minHealthRequiredToExitTheCell){
                healthRequiredToEnterThisCell = minHealthRequiredToExitTheCell - dungeon[i][j];
            }else{
                healthRequiredToEnterThisCell = 1;
            }
            return healthRequiredToEnterThisCell;
        }
};

//DP Top Down
class Solution{
    int rows;
    int cols;
    public:
        int calculateMinimumHP(vector<vector<int>> &dungeon){
            rows = dungeon.size();
            cols = dungeon[0].size();
            vector<vector<int>> dp(row,vector<int>(cols, 0));
            return solve(dungeon, 0, 0, dp);
        }

        //returns the minimum health required to enter a cell (i,j)
        int solve(vector<vector<int>> &dungeon, int i, int j, vector<vector<int>> &dp){
            //if you go out of the grid then you cannot reach queen, so return +INF
            if(i<0 || i>=rows || j<0 || j>=cols)
                return INT_MAX;
            
            //if you reached the queen
            //then check if there is a deamon in that cell. If yes then you need some 
            //health to enter and survive in order to get the queen. Minimum health to
            //survive after fighting the deamon = 1. So min health required to enter the
            //cell, fight the deamon and get the queen will be 1-dungeon[i][j].
            //If there is no deamon in the last cell, then you donot need any energy to
            //fight, so the minimum health required = 1 
            if(i==rows-1 && j==cols-1){
                if(dungeon[i][j]<0)
                    return dp[i][j] = 1-dungeon[i][j];
                return dp[i][j]=1;
            }

            if(dp[i][j]>0)
                return dp[i][j];

            int goDown = solve(dungeon, i+1, j, dp);
            int goRight= solve(dungeon, i, j+1, dp);

            int minHealthRequiredToExitTheCell = min(goDown, goRight);

            //if minHealthRequired is < the current enegy (can be negative due to a deamon,
            //or a less positive number), then the knight more energy while he entered the cell
            //i.e. minHealthRequiredToExitTheCell = healthRequiredToEnterThisCell + theEnergyGainedOrLostInThisCell
            //  => healthRequiredToEnterThisCell  = minHealthRequiredToExitTheCell - theEnergyGainedOrLostInThisCell

            int healthRequiredToEnterThisCell;
            if(dungeon[i][j] < minHealthRequiredToExitTheCell){
                healthRequiredToEnterThisCell = minHealthRequiredToExitTheCell - dungeon[i][j];
            }else{
                healthRequiredToEnterThisCell = 1;
            }
            return dp[i][j] = healthRequiredToEnterThisCell;
        }
};

//Bottom - Up
class Solution{
    int rows;
    int cols;
    public:
        int calculateMinimumHP(vector<vector<int>> &dungeon){
            rows = dungeon.size();
            cols = dungeon[0].size();
            vector<vector<int>> dp(rows,vector<int>(cols, 0));

            for(int i=rows-1; i>=0; i--){
                for(int j=cols-1; j>=0; j--){
                    if(i==rows-1 && j==cols-1){
                        if(dungeon[i][j] < 0)
                            dp[i][j] = 1-dungeon[i][j];
                        else
                            dp[i][j] = 1;
                    }
                    else if(i==rows-1){
                        if(dungeon[i][j] < dp[i][j+1])
                            dp[i][j] = dp[i][j+1] - dungeon[i][j];
                        else
                            dp[i][j] = 1;
                    }
                    else if(j==cols-1){
                        if(dungeon[i][j] < dp[i+1][j])
                            dp[i][j] = dp[i+1][j] - dungeon[i][j];
                        else
                            dp[i][j] = 1;
                    }else{
                        int minHealthRequiredToExitTheCell = min(dp[i][j+1], dp[i+1][j]);

                        int healthRequiredToEnterThisCell;
                        if(dungeon[i][j] < minHealthRequiredToExitTheCell){
                            healthRequiredToEnterThisCell = minHealthRequiredToExitTheCell - dungeon[i][j];
                        }else{
                            healthRequiredToEnterThisCell = 1;
                        }

                        dp[i][j] = healthRequiredToEnterThisCell;
                    }
                }
            }
            return dp[0][0];
        }
};
