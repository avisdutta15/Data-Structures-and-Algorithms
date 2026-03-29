#include <bits/stdc++.h>
using namespace std;

/*
    Problem Statement:
    -----------------
    The problem is to count all the possible paths from top left to bottom right of a mXn matrix 
    with the constraints that from each cell you can either move only to right or down.

    Input :  m = 2, n = 3;
    Output : 3
    There are three paths
    (0, 0) -> (0, 1) -> (0, 2) -> (1, 2)
    (0, 0) -> (0, 1) -> (1, 1) -> (1, 2)
    (0, 0) -> (1, 0) -> (1, 1) -> (1, 2)

    Given a matrix, print all the possible paths from top left to bottom right of a mXn matrix 
    with the constraints that from each cell you can either move only to right or down.

*/

class Solution
{
    int row, col;
    
    public:
        int countPaths(int n, int m){
            //if this is the topmost left cell n=0 m=0 then there is no way to reach this cell
            if(n==0 && m==0)
                return 0;
            
            //if we hit a cell in the first row then there is only one way to reach this cell i.e. from left
            //if we hit a cell in the first column then there is only one way to reach this cell i.e. from top
            if(n==0 || m==0)
                return 1;
            
            //if there exists X ways to reach cell n,m from top and Y ways to reach from left, then total ways is X + Y
            return countPaths(n-1, m) + countPaths(n, m-1);
        }

        int countPathsBottomUp(int rows, int columns){
            int DP[n][m];

            for(int i=0; i<rows; i++)
                DP[i][0] = 1;
            
            for(int i=0; i<columns; i++)
                DP[0][i] = 1;

            for(int i=1; i<rows; i++){
                for(int j=1; j<columns; j++)
                    DP[i][j] = DP[i-1][j] + DP[i][j-1];
            }
            return DP[n-1][m-1];
        }

        void util1(vector<vector<int>> A, int currentRow, int currentColumn, string path){
            
            //if control reaches at the last row then append all the remaining elements in the remaining columns of last row
            if(currentRow==row-1){
                for(int i=currentColumn; i<col; i++)
                    path = path + " " + to_string(A[currentRow][i]);
                cout<<path<<endl;
                return;
            }

            //if control reaches at the last column then append all the remaining elements in the remaining rows of the last column
            if(currentColumn==col-1){
                for(int i=currentRow; i<row; i++)   
                    path = path + " " + to_string(A[i][currentColumn]);
                cout<<path<<endl;
                return;
            }
            
            //Add the current cell to path
            path = path + " " + to_string(A[currentRow][currentColumn]);

            //Now recurse for down and right
            util1(A, currentRow+1, currentColumn, path);
            util1(A, currentRow, currentColumn+1, path);
        }

        void printAllPossiblePaths1(vector<vector<int>> A){
            
            //Refer: https://algorithms.tutorialhorizon.com//print-all-paths-from-top-left-to-bottom-right-in-two-dimensional-array/
            row = A.size();
            if(row==0)
                return;
            col = A[0].size();

            int currentRow = 0;
            int currentColumn = 0;
            string path = "";
            util1(A, currentRow, currentColumn, path);
        }

        void util2(vector<vector<int>> A, int i, int j, string path){
            if(i>=row || j>=col)
                return;

            if(i==row-1 && j==col-1){
                path = path + " " + to_string(A[i][j]);
                cout<<path<<endl;
                return;
            }

            path = path + " " + to_string(A[i][j]);
            util2(A, i+1, j, path);
            util2(A, i, j+1, path);
        }

        void printAllPossiblePaths2(vector<vector<int>> A){
            row = A.size();
            if(row==0)
                return;
            col = A[0].size();

            string path = "";
            util2(A, 0, 0, path);
        }       
};

int main(){
    Solution obj;
    int row = 3, col = 3;
    cout<<obj.countPaths(row-1, col-1)<<endl; //counts the number of ways to reach from top left to bottom right in a 3 X 3 matrix
    cout<<obj.countPathsBottomUp(row, col)<<endl;  //counts the number of ways to reach from top left to bottom right in a 3 X 3 matrix

    vector<vector<int>>A = { { 1, 2, 3 }, 
                             { 4, 5, 6 },
                             { 7, 8, 9 } 
                           };
    obj.printAllPossiblePaths1(A);
    cout<<endl<<endl;
    obj.printAllPossiblePaths2(A);  //easy approach
    return 0;
}