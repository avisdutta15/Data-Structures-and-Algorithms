#include <bits/stdc++.h>
using namespace std;

/*
    if the characters match, then
        case 1: if the control is in first row or column then
                the LCS[i][j] = 1
        case 2: if the control is not in the first row or column then
                LCS[i][j] = LCS[i-1][j-1] + 1;
    else
                LCS[i][j] = 0
        
    Approach for printing all LCS:
        create a new vector each time LCS[i][j] > maxLCStillNow
        if LCS[i][j] == maxLCStillNow then insert into the same vector
*/

class Solution{
    public:
        vector<string> LCSubstring(string X, string Y){
            
            int M = X.length();
            int N = Y.length();
            
            int DP[M+1][N+1];
            
            vector<string> ans;
            int maxLCS = -1;
            
            for(int i=0; i<=M; i++){
                for(int j=0; j<=N; j++){
                    
                    if(X[i]==Y[j]){
                        if(i==0 || j==0)    DP[i][j] = 1;
                        else
                            DP[i][j] = DP[i-1][j-1] + 1;
                        
                        //check for max condition
                        if(DP[i][j]>maxLCS){
                            //create a new vector
                            maxLCS = DP[i][j];
                            vector<string>temp;
                            ans = temp;
                            ans.push_back(X.substr(i-maxLCS+1,maxLCS));
                        }
                        else if(DP[i][j]==maxLCS)
                        {
                            ans.push_back(X.substr(i-maxLCS+1,maxLCS));
                        }
                    }
                    else{
                        DP[i][j] = 0;
                    }
                }
            }
            return ans;
        }
};

int main() {
	Solution obj;
	string X = "ABAB";
	string Y = "BABA";
	
	vector<string>LCS = obj.LCSubstring(X, Y);
	for(string i: LCS)
	    cout<<i<<endl;
	return 0;
}