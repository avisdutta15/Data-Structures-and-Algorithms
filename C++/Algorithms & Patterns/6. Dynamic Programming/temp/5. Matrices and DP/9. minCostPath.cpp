#include <bits/stdc++.h>
using namespace std;

/*
    Problem Statement:
    -----------------
    Given a cost matrix cost[][] and a position (m, n) in cost[][], write a function that 
    returns cost of minimum cost path to reach (m, n) from (0, 0). Each cell of the matrix 
    represents a cost to traverse through that cell. Total cost of a path to reach (m, n) 
    is sum of all the costs on that path (including both source and destination). You can 
    only traverse down, right and diagonally lower cells from a given cell, i.e., from a 
    given cell (i, j), cells (i+1, j), (i, j+1) and (i+1, j+1) can be traversed. You may 
    assume that all costs are positive integers.
*/

/*
    Recurrence :
        if(m<0 || n<0)
            return INT_MAX
        if(m==0 || n==0)
            return cost[m][n]
        cost to reach(m, n) = cost[m][n] + minimum ( cost to reach (m - 1, n - 1),
                                                     cost to reach (m - 1, n),
                                                     cost to reach (m, n - 1)
                                                   )
*/

class Solution
{
    int row, col;
    int minimum(int a, int b, int c){
        if(a<b && a<c)
            return a;
        if(b<a && b<c)
            return b;
        return c;
    }
    public:
        int util(vector<vector<int>>mat, int row, int col){
            if(row<0 || col<0)
                return INT_MAX;
            if(row==0 && col==0)
                return mat[row][col];
            
            return mat[row][col] + minimum(util(mat, row-1, col-1),
                                           util(mat, row, col-1),
                                           util(mat, row-1, col));
        }

        int utilTopDown(vector<vector<int>>mat, int row, int col, unordered_map<string, int> &lookup){
            if(row<0 || col<0)
                return INT_MAX;
                
            if(row==0 && col==0)
                return mat[row][col];
            
            string key = to_string(row) + ' ' + to_string(col);
            
            if(lookup.find(key)==lookup.end()){
                int cost = mat[row][col] + minimum(utilTopDown(mat, row-1, col-1, lookup),
                                                   utilTopDown(mat, row, col-1, lookup),
                                                   utilTopDown(mat, row-1, col, lookup));
                lookup[key] = cost;
            }
            
            return lookup[key];
        }

        int minCostPath(vector<vector<int>>mat){
            row = mat.size();
            if(row==0)
                return 0;
            if(row!=0)
                col = mat[0].size();

            return util(mat, row-1, col-1);
        }
        
        int minCostPathTopDown(vector<vector<int>>mat){
            row = mat.size();
            if(row==0)
                return 0;
            if(row!=0)
                col = mat[0].size();

            unordered_map<string, int> lookup;
            
            return utilTopDown(mat, row-1, col-1, lookup);
        }

        /*
            1 3 6 
            5 9 5 
            6 10 8
        */
        
        int minCostPathBottomUp(vector<vector<int>> mat){
            row = mat.size();
            if(row==0)
                return 0;
            if(row!=0)
                col = mat[0].size();

            int DP[row][col];
            
            DP[0][0] = mat[0][0];
            
            for(int i=1; i<col; i++){
                DP[0][i] = DP[0][i-1] + mat[0][i];
            }
            
            for(int i=1; i<row; i++){
                DP[i][0] = DP[i-1][0] + mat[i][0];
            }

            for(int i=1; i<row; i++){
                for(int j=1; j<col; j++){
                    DP[i][j] = mat[i][j] + minimum(DP[i-1][j], DP[i-1][j-1], DP[i][j-1]);
                }
            }

            return DP[row-1][col-1];
        }

        void printMinCostPath(vector<vector<int>> mat){
            row = mat.size();
            if(row==0){
                cout<<"Input Matrix is empty";
                return;
            }
            if(row!=0)
                col = mat[0].size();

            int DP[row][col];
            
            DP[0][0] = mat[0][0];
            
            for(int i=1; i<col; i++){
                DP[0][i] = DP[0][i-1] + mat[0][i];
            }
            
            for(int i=1; i<row; i++){
                DP[i][0] = DP[i-1][0] + mat[i][0];
            }

            for(int i=1; i<row; i++){
                for(int j=1; j<col; j++){
                    DP[i][j] = mat[i][j] + minimum(DP[i-1][j], DP[i-1][j-1], DP[i][j-1]);
                }
            }

            /*
            DP:
                1 3 6 
                5 9 5
                6 10 8

            Mat:
                {1, 2, 3},
                {4, 8, 2},
                {1, 5, 3}   3,3         3 -> 2 -> 2
            */


            int i=row-1, j=col-1;
            while(i>=0 && j>=0){
                cout<<mat[i][j]<<"<-";
                int top = DP[i-1][j];
                int left= DP[i][j-1];
                int diag= DP[i-1][j-1];

                if(top<left && top<diag)
                    i--;
                else if(left<top && left<diag)
                    j--;
                else{
                    i--;
                    j--;
                }
            }
        }
};

int main(){
    Solution obj;
    vector<vector<int>> mat = {{1, 2, 3},
                               {4, 8, 2},
                               {1, 5, 3}};

    //cout<<obj.minCostPath(mat)<<endl;
    //cout<<obj.minCostPathTopDown(mat)<<endl;
    //cout<<obj.minCostPathBottomUp(mat)<<endl;
    obj.printMinCostPath(mat);

    return 0;
}