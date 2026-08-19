#include <bits/stdc++.h>
using namespace std;

class Solution{
    public:
        int calculateSum(vector<vector<int>>A, int p, int q, int r, int s){
            int rows = A.size();
            int cols = A[0].size();

            //create an aux matrix
            int sum[rows][cols];
            sum[0][0] = A[0][0];

            //preprocess the first row
            for(int i=1; i<rows; i++)
                sum[0][i] = A[0][i] + sum[0][i-1];
            
            //preprocess the first column
            for(int i=1; i<cols; i++)
                sum[i][0] = A[i][0] + sum[i-1][0];
            
            //process the rest of the matrix
            for(int i=1; i<rows; i++){
                for(int j=1; j<cols; j++){
                    sum[i][j] = (sum[i][j-1] + sum[i-1][j] + A[i][j]) - sum[i-1][j-1];
                }
            }

            int total = sum[r][s];
            if(p-1 >= 0)
                total = total - sum[p-1][s];
            if(q-1 >= 0)
                total = total - sum[r][q-1];
            if(p-1>=0 && q-1>=0)
                total = total + sum[p-1][q-1];
            return total;
        }
};

int main(){
    vector<vector<int>> A = {
        {0, 2, 5, 4, 1},
        {4, 8, 2, 3, 7},
        {6, 3, 4, 6, 2},
        {7, 3, 1, 8, 3},
        {1, 5, 7, 9, 4}
    };

    Solution obj;
    cout<<obj.calculateSum(A, 1, 1, 3, 3);
}