#include <bits/stdc++.h>
using namespace std;

class Solution{
    int rows;
    int cols;
    public:
        int maxSizeSquareWithAll1sUtil(vector<vector<int>> &A, int x, int y, int &maxArea){
            if(x<0 || x>=rows || y<0 || y>=cols)
                return 0;
            
            if(x==0 || y==0)
                return A[x][y];

            int up = maxSizeSquareWithAll1sUtil(A, x-1, y, maxArea);
            int left = maxSizeSquareWithAll1sUtil(A, x, y-1, maxArea);
            int diagonal = maxSizeSquareWithAll1sUtil(A, x-1, y-1, maxArea);

            int maxAreaForThisCell = 0 ;
            if(A[x][y]!=0)
                maxAreaForThisCell = A[x][y]+min(left,min(up, diagonal));

            maxArea = max(maxArea, maxAreaForThisCell);
            return maxAreaForThisCell;
        }

        int maxSizeSquareWithAll1s(vector<vector<int>> A){
            rows = A.size();
            cols = A[0].size();

            int maxArea = INT_MIN;
            maxSizeSquareWithAll1sUtil(A, rows-1, cols-1, maxArea);  
            return maxArea;          
        }
};

class Solution2{
    int minimum(int a, int b, int c){
        if(a<b && a<c)
            return a;
        if(b<a && b<c)
            return b;
        return c;
    }
    public:
        int maxSizeSquareWithAll1s(vector<vector<int>> A){
            if(A.size()==0)
                return 0;
            int rows = A.size();
            int columns = A[0].size();

            int DP[rows][columns];
            int maxSize = INT_MIN;
            int max_i = 0;
            int max_j = 0;

            for(int i=0; i<rows; i++){
                for(int j=0; j<columns; j++){
                    
                    //if first row then copy as it is
                    if(i==0)
                        DP[i][j] = A[i][j];

                    //if first column then copy as it is
                    else if(j==0)
                        DP[i][j] = A[i][j];

                    //else if the current cell is 1 then it can make a square sub-matrix
                    //in this case take the minimum of the above 3 cells (top, diag, left) and add 1 to it
                    //if the current cell is 0 then it cannot make a square sub-matrix hence make it 0
                    else if(A[i][j]==0)
                        DP[i][j] = 0;
                    else
                        DP[i][j] = 1 + minimum(DP[i-1][j], DP[i][j-1], DP[i-1][j-1]);

                    if(maxSize < DP[i][j]){
                        maxSize = DP[i][j];
                        max_i = i;
                        max_j = j;
                    }
                }
            }
            
            /*
            for(int i=max_i; i>=(max_i-maxSize+1); i--){
                for(int j=max_j; j>=(max_j-maxSize+1); j--)
                    cout<<1<<" ";
                cout<<endl;
            }
            */
            
            return maxSize;
        }
};

int main(){
    
    
    vector<vector<int>> A = {
                             {0, 1, 1, 0, 1},  
                             {1, 1, 0, 1, 0},  
                             {0, 1, 1, 1, 0}, 
                             {1, 1, 1, 1, 0}, 
                             {1, 1, 1, 1, 1}, 
                             {0, 0, 0, 0, 0}
                            }; 

    Solution obj;
    cout<<obj.maxSizeSquareWithAll1s(A);
    cout<<endl;
    Solution2 obj2;
    cout<<obj2.maxSizeSquareWithAll1s(A);

    return 0;
}