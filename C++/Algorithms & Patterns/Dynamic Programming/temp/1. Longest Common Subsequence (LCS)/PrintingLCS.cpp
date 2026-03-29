#include <bits/stdc++.h>
using namespace std;

class Solution{
    int LCSBottomUp(string X, string Y, vector<vector<int>> &DP){
        int M = X.length();
        int N = Y.length();
        if(M==0 || N==0)
            return 0;

        for(int i=1; i<=M; i++){
            for(int j=1; j<=N; j++){
                if(X[i-1]==Y[j-1]){
                    DP[i][j] = 1 + DP[i-1][j-1];
                }
                else{
                    DP[i][j] = max(DP[i-1][j], DP[i][j-1]);
                }
            }
        }
        return DP[M][N];
    }
    public:
        string printLCSIterative(string X, string Y){
            string lcs;
            if(X.length()==0|| Y.length()==0)
                return lcs;
            
            int M = X.length();
            int N = Y.length();
            
            vector<vector<int>>DP(M+1, vector<int>(N+1));   
            int lcsLength = LCSBottomUp(X, Y, DP);
            
            if(lcsLength==0)
                return lcs;
            
            int i=M+1, j=N+1;
            while(i>0 && j>0){
                if(X[i-1] == Y[j-1]){
                    lcs.push_back(X[i-1]);
                    i--;
                    j--;
                }else if(DP[i-1][j] > DP[i][j-1])
                    i--;
                else
                    j--;
            }
            reverse(lcs.begin(), lcs.end());
            return lcs;
        }

        string printLCSRecursiveUtil(string X, string Y, int i, int j, vector<vector<int>> &DP){
            if(i==0 || j==0)
                return "";
            if(X[i-1]==Y[j-1])
                return printLCSRecursiveUtil(X, Y, i-1, j-1, DP) + X[i-1];
            
            if(DP[i-1][j]>=DP[i][j-1])
                return printLCSRecursiveUtil(X, Y, i-1, j, DP);
            else
                return printLCSRecursiveUtil(X, Y, i, j-1, DP);
        }
        
        string printLCSRecursive(string X, string Y){
            string lcs;
            if(X.length()==0|| Y.length()==0)
                return lcs;
            
            int M = X.length();
            int N = Y.length();
            
            vector<vector<int>>DP(M+1, vector<int>(N+1));   
            int lcsLength = LCSBottomUp(X, Y, DP);
            
            if(lcsLength==0)
                return lcs;
                
            return printLCSRecursiveUtil(X, Y, M+1, N+1, DP);
        }

};

int main(){
    string X = "ABCBDAB";
    string Y = "BDCABA";
    
    Solution obj;
    
    cout<<"Print Once LCS Iterative: "<<endl;
    string lcs = obj.printLCSIterative(X, Y);
    lcs.size()==0?cout<<"No LCS\n":cout<<lcs<<endl;
    
    cout<<"Print Once LCS Recursive: "<<endl;
    lcs = obj.printLCSRecursive(X, Y);
    lcs.size()==0?cout<<"No LCS\n":cout<<lcs<<endl;

    
    return 0;
}