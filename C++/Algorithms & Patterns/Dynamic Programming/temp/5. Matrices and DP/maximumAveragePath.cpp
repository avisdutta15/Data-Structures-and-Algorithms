#include <bits/stdc++.h>
using namespace std;

/*
    Input : Matrix = [1, 2, 3
                  4, 5, 6
                  7, 8, 9]
    Output : 5.8
    Path with maximum average is, 1 -> 4 -> 7 -> 8 -> 9
    Sum of the path is 29 and average is 29/5 = 5.8
*/

class Solution{
    public:
        double maxAverageOfPath(vector<vector<int>> A){
            int rows = A.size();
            if(rows==0) return 0;
            int cols = A[0].size();

            int steps = (rows-1)+(cols-1)+1;
            
            vector<vector<int>> DP(rows, vector<int>(cols, 0));
            DP[0][0] = A[0][0];
            
            for(int i=1; i<cols; i++){
                DP[0][i] = DP[0][i-1] + A[0][i];
            }
            for(int i=1; i<rows; i++){
                DP[i][0] = DP[i-1][0] + A[i][0];
            }

            for(int i=1; i<rows; i++){
                for(int j=1; j<cols; j++){
                    DP[i][j] = A[i][j] + max(DP[i-1][j], DP[i][j-1]);
                }
            }

            return (double)DP[rows-1][cols-1]/(steps);
        }
};

int main(){
    vector<vector<int>> A = {{1,2,3},{4,5,6},{7,8,9}};
    Solution obj;
    cout<<obj.maxAverageOfPath(A);
}