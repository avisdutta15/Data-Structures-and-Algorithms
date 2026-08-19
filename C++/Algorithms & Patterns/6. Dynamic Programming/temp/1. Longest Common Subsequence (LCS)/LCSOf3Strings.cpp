#include <bits/stdc++.h>
using namespace std;

int LCSof3(string s1, string s2, string s3){
    int n = s1.length();
    int m = s2.length();
    int o = s3.length();
            
    int lookup[n+1][m+1][o+1];
            
    for(int i=0; i<=n; i++){
        for(int j=0; j<=m; j++){
            for(int k=0; k<=o; k++){
                if(i==0 || j==0 || k==0)
                    lookup[i][j][k] = 0;
                else if(s1[i-1] == s2[j-1] && s2[j-1]==s3[k-1])
                    lookup[i][j][k] = 1 + lookup[i-1][j-1][k-1];
                else
                    lookup[i][j][k] = max(lookup[i-1][j][k], max(lookup[i][j-1][k], lookup[i][j][k-1]));
            }
        }
    }
            
    return lookup[n][m][o];
}

int main(){
    string X = "AGGT12";  
    string Y = "12TXAYB";  
    string Z = "12XBA";
	cout<<LCSof3(X, Y, Z);  //2
}