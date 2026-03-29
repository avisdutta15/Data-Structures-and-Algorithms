#include <bits/stdc++.h>
using namespace std;

//Print all the LCS in lexicographical order


/*
    Approach:
    We construct L[m+1][n+1] table as discussed in the previous post and traverse the 2D array 
    starting from L[m][n]. For current cell L[i][j] in the matrix,

    a) If the last characters of X and Y are same (i.e. X[i-1] == Y[j-1]), then the 
       charcater must be present in all LCS of substring X[0…i-1] and Y[0..j-1]. 
       We simply recurse for L[i-1][j-1] in the matrix and append current character 
       to all LCS possible of substring X[0…i-2] and Y[0..j-2].

    b) If the last characters of X and Y are not same (i.e. X[i-1] != Y[j-1]), then 
       LCS can be constructed from either top side of the matrix (i.e. L[i-1][j]) or 
       from left side of matrix (i.e. L[i][j-1]) depending upon which value is greater. 
       If both the values are equal(i.e. L[i-1][j] == L[i][j-1]), then it will be 
       constructed from both sides of matrix. So based on values at L[i-1][j] and 
       L[i][j-1], we go in direction of greater value or go in both directions if the 
       values are equal.

*/

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
        vector<string> printAllLCSUtil(string X, string Y, int i, int j, vector<vector<int>> &DP){
            
            if(i==0 || j==0){
                vector<string> lcs(1);
                return lcs;
            }            
            if(X[i-1] == Y[j-1]){
                //donot insert the matched character to the LCS now.
                //because this will be a common character to all the LCS above it       
                vector<string> lcs = printAllLCSUtil(X, Y, i-1, j-1, DP);
                
                //append the current character to all the LCS above it 
                for(string &s: lcs)
                    s= s+(X[i-1]);
                
                return lcs;
            }            
            if(DP[i-1][j] > DP[i][j-1])
                return printAllLCSUtil(X, Y, i-1, j, DP);
            else if(DP[i][j-1] > DP[i-1][j])
                return printAllLCSUtil(X, Y, i, j-1, DP);
                       
            //both are of same value
            //then recurse top and left
            vector<string> top = printAllLCSUtil(X, Y, i-1, j, DP);
            vector<string> left= printAllLCSUtil(X, Y, i, j-1, DP);
            
            //merge both top and left into 1 vector and return
            top.insert(top.end(),left.begin(), left.end());
            
            return top;
        }
        
        vector<string> printAllLCS(string X, string Y){
            vector<string> allLCS;
            if(X.length()==0|| Y.length()==0)
                return allLCS;
            
            int M = X.length();
            int N = Y.length();
            
            vector<vector<int>>DP(M+1, vector<int>(N+1));   
            int lcsLength = LCSBottomUp(X, Y, DP);
            
            if(lcsLength==0)
                return allLCS;
            
            allLCS = printAllLCSUtil(X, Y, M+1, N+1, DP);
            
            set<string> setOfAllLCS;
            for(string s: allLCS)
                setOfAllLCS.insert(s);
            
            //allLCS.clear();
            //allLCS.insert(setOfAllLCS.begin(), setOfAllLCS.end());
            return allLCS;
        }
    
};

//Note: to print in lexographical order use set instead of vector

int main(){
    string X = "ABCBDAB";
    string Y = "BDCABA";
    
    Solution obj;
    
    cout<<"Print All LCS:"<<endl;
    vector<string> allLCS = obj.printAllLCS(X, Y);
    for(auto i: allLCS)
       cout<<i<<"\n";
}
