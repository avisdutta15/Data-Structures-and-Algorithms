#include <bits/stdc++.h>
using namespace std;


class Solution{
    int LCSBottomUp(string X, int N, string Y, int M, vector<vector<int>> &dp){
        for(int n=0; n<=N; n++){
            for(int m=0; m<=M; m++){
                if(n == 0 || m == 0)
                    dp[n][m] = 0;
                else if(X[n-1] == Y[m-1])
                    dp[n][m] = 1 + dp[n-1][m-1];
                else
                    dp[n][m] = max(dp[n-1][m], dp[n][m-1]);
            }
        }
        return dp[N][M];
    }

public:
    string printLCS(string X, string Y){
        int N = X.length(), M = Y.length();
        vector<vector<int>> dp(N+1, vector<int>(M+1, 0));

        //Fill up the matrix
        LCSBottomUp(X, X.length(), Y, Y.length(), dp);

        int i=N, j=M;
        string ans = "";

        while(i>0 && j>0){
            if(X[i-1] == Y[j-1]){
                ans.push_back(X[i-1]);
                i--;
                j--;
            }
            else if(dp[i-1][j] > dp[i][j-1])
                i--;
            else
                j--;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};


int main(){
    Solution obj;
    string X = "AGGTAB"; 
    string Y = "GXTXAYB";
    cout<<obj.printLCS(X, Y);        //GTAB 4.
}