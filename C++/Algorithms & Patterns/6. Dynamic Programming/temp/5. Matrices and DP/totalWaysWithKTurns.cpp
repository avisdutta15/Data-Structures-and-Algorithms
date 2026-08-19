#include <bits/stdc++.h>
using namespace std;

class Solution{
    int m, n;
    public:
        Solution(){
            m=0, n=0;
        }

        int totalWaysWithKTurnsUtil(int i, int j, int K, bool isCol){
            
            //if the current cell is not valid then return 0
            if(i<0 || j<0 || i>m || j>n)
                return 0;
            
            //if we have reached the bottom right and there are 0 turns left then
            //return 1 as a waycount
            if(K==0 && i==m-1 && j==n-1)
                return 1;
            
            
            //if the current direction is column 
            if(isCol == true){
                //1. continue moving along the column 
                //2. turn right and decrement the K.
                return totalWaysWithKTurnsUtil(i+1, j, K, isCol) + totalWaysWithKTurnsUtil(i, j+1, K-1, !isCol);
            }
            
            //if the current direction is row
            //1. continue moving along the row
            //2. turn down and decrement the K
            return totalWaysWithKTurnsUtil(i, j+1, K, isCol) + totalWaysWithKTurnsUtil(i+1, j, K-1, !isCol);
        }

        int totalWaysWithKTurns(int m, int n, int K){
            this->m = m;
            this->n = n;
            
            // Recur for two cases: moving along row and along column 
            return totalWaysWithKTurnsUtil(0, 0, K, false) +    // Moving along row 
                   totalWaysWithKTurnsUtil(0, 0, K, true);      // Moving along column
        }
};

class Solution2{
    int m, n;
    int dp[4][4][4][2];
    public:
        Solution2(){
            m=0, n=0;
            memset(dp, -1, sizeof dp); 
        }
        
        int totalWaysWithKTurnsUtil(int i, int j, int K, int isCol){
            
            //if the current cell is not valid then return 0
            if(i<0 || j<0 || i>m || j>n)
                return 0;
            
            //if we have reached the bottom right and there are 0 turns left then
            //return 1 as a waycount
            if(K==0 && i==m-1 && j==n-1){
                return 1;
            }
            
            if(dp[m][n][K][isCol] != -1)
                return dp[m][n][K][isCol];
            
            //if the current direction is column 
            if(isCol == 1){
                //1. continue moving along the column 
                //2. turn right and decrement the K.
                return dp[m][n][K][isCol] = totalWaysWithKTurnsUtil(i+1, j, K, isCol) + totalWaysWithKTurnsUtil(i, j+1, K-1, !isCol);
            }
            
            //if the current direction is row
            //1. continue moving along the row
            //2. turn down and decrement the K
            return dp[m][n][K][isCol] = totalWaysWithKTurnsUtil(i, j+1, K, isCol) + totalWaysWithKTurnsUtil(i+1, j, K-1, !isCol);
            
        }

        int totalWaysWithKTurns(int m, int n, int K){
            this->m = m;
            this->n = n;
            return totalWaysWithKTurnsUtil(0, 0, K, 1) + totalWaysWithKTurnsUtil(0, 0, K, 0);
        }
};


int main(){
    Solution2 obj;
    cout<<obj.totalWaysWithKTurns(3, 3, 2);
}





