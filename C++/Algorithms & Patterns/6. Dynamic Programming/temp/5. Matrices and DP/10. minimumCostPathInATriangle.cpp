#include <bits/stdc++.h>
using namespace std;

/*
    Given a triangular structure of numbers, find the minimum path sum from top to bottom. 
    Each step you may move to adjacent numbers on the row below.
    
    Input:
            2 
           3, 9 
          1, 6, 7
    
    Output:
        2 + 3 + 1 = 6        
*/

/*
    Steps:
    Take a aux 1D array to store prev row of intermediate calculations
    Initialize it with the last row of Mat[]
    DP = [1, 6, 7]

    start from 2nd row of Mat
    Processing the 2nd last row of Mat: DP = [4, 15]   ==> {4 = 1+3,  15 = 9+6}
    Processing the 1st row of Mat:      DP = [6]       ==> {6 = 2+4}

    If you want to print the path, convert the triange into a 2d array and append 0's at the end.
    Then the problem reduces to min cost path

        2 0 0               =>     6 0  0
        3 9 0                      4 15 0
        1 6 7                      1 6  7

        To print the path, start from Mat[0][0]. print it.
        Now see which one(bottom or diag bottom) is smaller. Then go to it.
        Continue the process till you reach the last row.        
*/

class Solution
{
    int row, col;
    public:
        int minimumSumPath(vector<vector<int>> mat){
            row = mat.size();
            if(row==0)
                return 0;
            col = mat[0].size();
            
            //1D array to store the intermediate results of previous row
            int DP[col];
            
            //initialize the 1D array with the last row of the matrix
            for(int i=0; i<mat[row-1].size(); i++)
                DP[i] = mat[row-1][i]; 


            //start from 2nd last row
            //each cell will be sum of current cell + min(bottom cell, diag bottom cell)
            for(int i=row-2; i>=0; i--){
                for(int j=0; j<mat[i+1].size(); j++){
                    DP[j] = mat[i][j] + min(DP[j], DP[j+1]);
                }
            }
            return DP[0];
        }    
};

int main(){
    Solution obj;
    vector<vector<int>> mat = {
                                { 2 }, 
                                { 3, 9 }, 
                                { 1, 6, 7 }
                              }; 
    
    cout<<obj.minimumSumPath(mat);

    return 0;
}