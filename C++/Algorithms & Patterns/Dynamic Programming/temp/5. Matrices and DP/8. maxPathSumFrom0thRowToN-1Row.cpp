#include <bits/stdc++.h>
using namespace std;

/*
    Problem Statement:
    -----------------
    Given a N X N matrix Mat[N][N] of positive integers. There are only three possible moves from a cell (i, j)
        (i+1, j)
        (i+1, j-1)
        (i+1, j+1)
    Starting from any column in row 0, return the largest sum of any of the paths up to row N-1.

    Examples:

    Input : mat[4][4] = { {4, 2, 3, 4},
                          {2, 9, 1, 10},
                          {15, 1, 3, 0},
                          {16, 92, 41, 44} };
    Output :120
    path : 4 + 9 + 15 + 92 = 120 
*/

/*
    We can do a bottom up approach. At any cell of any row except the first row, ask yourself
    how you can reach there with the moves - [ i-1, j ]  ,  [ i-1, j+1 ]  ,  [ i-1, j-1 ]  
*/

class Solution
{
    int row, col;
    int maximum(int a, int b, int c){
        if(a>b && a>c)
            return a;
        if(b>a && b>c)
            return b;
        return c;
    }
    public:
        int util(vector<vector<int>> A, int i, int j){
            if(i==0 && j==0)
                return A[i][j];
            if(i<0 || j<0 || j>=col)
                return 0;
            
            return A[i][j] + maximum( util(A, i-1, j),
                                      util(A, i-1, j+1),
                                      util(A, i-1, j-1)
                                    );
        }

        int maximumPathSum(vector<vector<int>> A){
            row = A.size();
            col = A[0].size();

            int i = row-1;
            int maxCost = INT_MIN;
            for(int j=0; j<col; j++){
                maxCost = max(maxCost, util(A, i, j));
            }
            return maxCost;
        }

        int maximumPathSumBottomUp(vector<vector<int>> A){
            row = A.size();
            col = A[0].size();

            //initialize a DP table where 1st row is same as 1st row of input matrix
            int DP[row][col];
            for(int i=0; i<col; i++)
                DP[0][i] = A[0][i];
          
            //fill the rest of the table
            for(int i=1; i<row; i++){
                for(int j=0; j<col; j++){
                    
                    //Allowed moves - [ i-1, j ]  ,  [ i-1, j+1 ]  ,  [ i-1, j-1 ]  
                    
                    if(j==0) //first column can take value from top or diag top right
                        DP[i][j] = A[i][j] + max(DP[i-1][j], DP[i-1][j+1]);
                        
                    else if(j<col-1)
                        DP[i][j] = A[i][j] + maximum(DP[i-1][j], DP[i-1][j+1], DP[i-1][j-1]);
                        
                    else if(j==col-1) //last column can take value from top or diag top left
                        DP[i][j] = A[i][j] + max(DP[i-1][j], DP[i-1][j-1]);
                }
            }

            int N = row-1;
            int maxCost = INT_MIN;
            for(int i=0; i<col; i++)
                maxCost = max(maxCost, DP[N][i]);
            return maxCost;
        }

};

int main(){
    Solution obj;
    vector<vector<int>> A = { {4, 2, 3, 4},
                              {2, 9, 1, 10},
                              {15, 1, 3, 0},
                              {16, 92, 41, 44} 
                            };
    cout<<obj.maximumPathSumBottomUp(A);
    return 0;
}