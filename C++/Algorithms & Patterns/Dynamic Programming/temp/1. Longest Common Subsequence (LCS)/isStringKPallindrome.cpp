#include<bits/stdc++.h>
using namespace std;

/*
    Given a string, find out if the string is K-Palindrome or not. 
    A K-palindrome string transforms into a palindrome on removing 
    at most k characters from it.

    Examples:

    Input : String - abcdecba, k = 1
    Output : Yes
    String can become palindrome by removing
    1 character i.e. either d or e

    Input  : String - abcdeca, K = 2
    Output : Yes
    Can become palindrome by removing
    2 characters b and e (or b and d).

    Input : String - acdcb, K = 1
    Output : No
    String can not become palindrome by
    removing only one character.


    Approach:
    The idea is to find the longest palindromic subsequence of the given string. 
    If the difference between longest palindromic subsequence and the original 
    string is less than equal to k, then the string is k-palindrome else it is 
    not k-palindrome.
*/


class Solution{
    private:
        int LPS(string X, string Y){
            int M = X.length();
            int N = Y.length();
            
            int DP[M+1][N+1];
            for(int i=0; i<=M; i++)
                DP[i][0] = 0;
            for(int i=0; i<=N; i++)
                DP[0][i] = 0;
                
            for(int i=1; i<=M; i++){
                for(int j=1; j<=N; j++){
                    if(X[i-1]==Y[j-1])
                        DP[i][j] = DP[i-1][j-1];
                    else
                        DP[i][j] = max(DP[i-1][j], DP[i][j-1]);
                }
            }
            
            return DP[M][N];
        }
    public:
        bool isKPallindromic(string X, int K){
            reverse(X.begin(), X.end());
            string Y = X;
            reverse(X.begin(), X.end());
            
            int pallindromeLength = LPS(X, Y);
            if(X.length() - pallindromeLength <= K)
                return true;
            return false;
        }
};

int main(){
    Solution obj;
    string X = "acdcb";
    int K = 1;
    obj.isKPallindromic(X, K) == true? cout<<"Possible":cout<<"Not Possible";
}