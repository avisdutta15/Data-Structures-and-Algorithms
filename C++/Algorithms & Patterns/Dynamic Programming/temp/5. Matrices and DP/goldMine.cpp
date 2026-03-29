#include <bits/stdc++.h>
using namespace std;

/*
    Given a gold mine of n*m dimensions. Each field in this mine 
    contains a positive integer which is the amount of gold in tons. 
    Initially the miner is at first column but can be at any row. 
    He can move only (right->,right up /,right down\) that is from 
    a given cell, the miner can move to the cell diagonally up 
    towards the right or right or diagonally down towards the right. 
    
    Find out maximum amount of gold he can collect.

    Examples:
    
    Input : mat[][] = {{1, 3, 3},
                       {2, 1, 4},
                       {0, 6, 4}};
    Output : 12 
    {(1,0)->(2,1)->(2,2)}
*/

class Solution{
    int rows, cols;
    public:
        int goldMineUtil(vector<vector<int>> A, int x, int y){
            if(x<0 || x>=rows || y<0 || y>=cols)
                return 0;

            if(x==rows-1 || y==cols-1)
                return A[x][y];

            int goldCollectedFromRight = goldMineUtil(A, x, y+1);
            int goldCollectedFromRightDown = goldMineUtil(A, x+1, y+1);
            int goldCollectedFromRightUp = goldMineUtil(A, x-1, y+1);

            int maxGoldCollectedFromThisCell = A[x][y] + max(goldCollectedFromRight, 
                                                         max(goldCollectedFromRightDown, goldCollectedFromRightUp));
            return maxGoldCollectedFromThisCell;
        }

        int goldMine(vector<vector<int>> A){
            rows = A.size(), cols = A[0].size();
            int maxGoldCollected = INT_MIN;

            for(int i=0; i<rows; i++){
                maxGoldCollected = max(maxGoldCollected, goldMineUtil(A, i, 0));
            }            
            return maxGoldCollected;
        }
};

class Solution2{
    int rows, cols;
    public:
        int goldMine(vector<vector<int>> A){
            rows = A.size(), cols = A[0].size();

            int maxGoldCollected = INT_MIN;
            vector<vector<int>> DP(rows, vector<int>(cols, 0));

            for(int i=0; i<rows; i++)
                DP[i][cols-1] = A[i][cols-1];

            for(int i=0; i<rows; i++){
                for(int j=cols-2; j>=0; j--){
                    int goldCollectedFromRight = (j+1<0 || j+1>=cols)?0: DP[i][j+1];
                    int goldCollectedFromUpperRight = (i-1<0 || i-1>=rows || j+1<0 || j+1>=cols)?0: DP[i-1][j+1];
                    int goldCollectedFromBottomRight = (i+1<0 || i+1>=rows || j+1<0 || j+1>=cols)?0: DP[i+1][j+1];
                    DP[i][j] = A[i][j] + max(goldCollectedFromRight, max(goldCollectedFromUpperRight, goldCollectedFromBottomRight));
                }
            }

            for(int i=0; i<rows; i++)
                maxGoldCollected = max(maxGoldCollected, DP[i][0]);
            return maxGoldCollected;
        }
};

int main(){
    Solution obj;
    vector<vector<int>> A = { {1, 3, 1, 5},
                            {2, 2, 4, 1},
                            {5, 0, 2, 3},
                            {0, 6, 1, 2}};
    cout<<obj.goldMine(A);
    cout<<endl;

    Solution2 obj2;
    cout<<obj2.goldMine(A);
}