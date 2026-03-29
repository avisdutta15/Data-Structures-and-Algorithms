#include <bits/stdc++.h>
using namespace std;


class Solution{
    int LCSRecursive(string X, int N, string Y, int M){
        //if either of the string is empty then there are no 
        //common characters.
        if(N == 0 || M == 0)
            return 0;
        
        if(X[N-1] == Y[M-1])
            return 1 + LCSRecursive(X, N-1, Y, M-1);
        else
            return max(LCSRecursive(X, N-1, Y, M),   LCSRecursive(X, N, Y, M-1));
    }

    int LCSTopDown(string X, int N, string Y, int M, unordered_map<string, int> &lookup){
        //if either of the string is empty then there are no 
        //common characters.
        if(N == 0 || M == 0)
            return 0;
        
        string key = to_string(N) + " " + to_string(M);
        if(lookup.find(key)!=lookup.end())
            return lookup[key];
            
        if(X[N-1] == Y[M-1])
            lookup[key] = 1 + LCSRecursive(X, N-1, Y, M-1);
        else
            lookup[key] = max(LCSRecursive(X, N-1, Y, M),   LCSRecursive(X, N, Y, M-1));

        return lookup[key];
    }

    int LCSBottomUp(string X, int N, string Y, int M){
        vector<vector<int>> dp(N+1, vector<int>(M+1, 0));

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
    int LCS(string X, string Y){
        unordered_map<string, int> lookup;
        // return LCSRecursive(X, X.length(), Y, Y.length());
        // return LCSTopDown(X, X.length(), Y, Y.length(), lookup);
        return LCSBottomUp(X, X.length(), Y, Y.length());
    }
};


int main(){
    Solution obj;
    string X = "AGGTAB"; 
    string Y = "GXTXAYB";
    cout<<obj.LCS(X, Y);        //GTAB 4.
}