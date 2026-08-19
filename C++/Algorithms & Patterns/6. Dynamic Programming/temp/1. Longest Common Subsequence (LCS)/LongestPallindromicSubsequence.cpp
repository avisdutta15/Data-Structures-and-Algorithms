#include <bits/stdc++.h>
using namespace std;

/*
    Given a sequence, find the length of the longest palindromic subsequence in it.
    I/p: GeeksForGeeks
    O/P: eekee or eesee etc. All are for length 5.

    Approach1 : Using LCS
        a. reverse the input string and store it in s2 
        b. return LCS(s1, s2).

    Approach2 : Using Palindrome characteristics
        The idea is to use recursion to solve this problem. compare the last character
        of the string S[i..j] with its first character. Two possiblities:
            a. S[i] == S[j] we got count of 2 characters and recure for the remaining string.
            b. S[i] != S[j] return the max of these two:
                remove the last character and recur for the rest of the string  S[i..j-1]
                remove the first character and recur for the rest of the string S[i+1..j]


*/

class Solution{
    private:
        
        string LCS(string X, string Y){
            int M = X.length();
            int N = Y.length();

            int DP[M+1][N+1];
            for(int i=0; i<=M; i++){
                DP[i][0] = 0;
            }
            for(int i=0; i<=N; i++){
                DP[0][i] = 0;
            }

            for(int i=1; i<=M; i++){
                for(int j=1; j<=N; j++){
                    if(X[i-1]==Y[j-1])
                        DP[i][j] = 1 + DP[i-1][j-1];
                    else
                        DP[i][j] = max(DP[i-1][j], DP[i][j-1]);
                }
            }

            int LCSlength = DP[M][N];
            string ans;
            int i=M, j=N;
            
            while(i>0 && j>0){
                if(X[i-1]==Y[j-1]){
                    ans.push_back(X[i-1]);
                    i--; j--;
                }else if(DP[i-1][j] > DP[i][j-1])
                    i--;
                else
                    j--;
            }
            reverse(ans.begin(),ans.end());
            return ans;
        }
    public:
        string LPSUsingLCS(string X){
            reverse(X.begin(), X.end());
            string Y = X;
            reverse(X.begin(), X.end());
            
            return LCS(X, Y);
        }

        int LPSNaiveUtil(string X, int i, int j){
            // base condition
            if (i > j)
                return 0;

            // if string X has only one character, it is palindrome
            if (i == j)
                return 1;

            // if last character of the string is same as the first character
            if (X[i] == X[j])
            {
                // include first and last characters in palindrome
                // and recur for the remaining substring X[i+1, j-1]
                return LPSNaiveUtil(X, i + 1, j - 1) + 2;
            }

            // if last character of string is different to the first character

            // 1. Remove last character and recur for the remaining
            //	substring X[i, j-1]
            // 2. Remove first character and recur for the remaining
            //	substring X[i+1, j]
            // return maximum of the two values
            return max (LPSNaiveUtil(X, i, j - 1), LPSNaiveUtil(X, i + 1, j));
        }

        int LPSNaive(string x){
            return LPSNaiveUtil(X, 0, X.length-1);
        }

        int LPSBottomUp(string s1){
            int n = s1.length();
            int dp[n][n] = {0};

            //every single character string is palindrome of size 1
            for(int i=0; i<n; i++)
                dp[i][i] = 1;

            for(int distance=2; distance<=n; distance++){

                //for every distance, fix an i and j with width distance apart.    
                for(int i=0; i<n-distance+1; i++){
                    int j = i + distance - 1;
                    if(distance==2 && s1[i] == s1[j])
                        dp[i][j] = 2;
                    else if(s1[i] == s1[j])
                        dp[i][j] = 2 + dp[i+1][j-1];
                    else
                        dp[i][j] = max(dp[i+1][j], dp[i][j-1]);                    
                }
            }

            return dp[0][n-1];
        }
};

int main(){
    string X = "GEEKSFORGEEKS";
    Solution obj;
    cout<<obj.LPSUsingLCS(X);
    return 0;
}