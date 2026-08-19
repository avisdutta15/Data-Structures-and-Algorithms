#include<bits/stdc++.h>
using namespace std;

/*
    Given a string S and a string T, count the number of distinct subsequences of S which equals T.

    A subsequence of a string is a new string which is formed from the original string by deleting 
    some (can be none) of the characters without disturbing the relative positions of the remaining
    characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

    Example 1:

    Input: S = "rabbbit", T = "rabbit"
    Output: 3
    Explanation:

    As shown below, there are 3 ways you can generate "rabbit" from S.
    (The caret symbol ^ means the chosen letters)

    rabbbit
    ^^^^ ^^
    rabbbit
    ^^ ^^^^
    rabbbit
    ^^^ ^^^
    
    
    Example 2:

    Input: S = "babgbag", T = "bag"
    Output: 5
    Explanation:

    As shown below, there are 5 ways you can generate "bag" from S.
    (The caret symbol ^ means the chosen letters)

    babgbag
    ^^ ^
    babgbag
    ^^    ^
    babgbag
    ^    ^^
    babgbag
    ^  ^^
    babgbag
        ^^^

    Approach:
        i points to T and j points to S
        if(T[i]==S[j])
            then fix i in T and traverse rest of S => count(T, S, i, j-1)
            +
            move both i and j and traverse rest of T and S => count(T, S, i-1, j-1)
        else
            stay at i in T and move in S. => count(T, S, i, j-1)

                        |   count[0][j] = 1                      iff T is empty then S has "" set so count = 1
                        |   count[0][0] = 1
        count[i][j] =   |   count[i-1][j-1] + count[i][j-1]      iff T[i] == S[j]
                        |   
                        |   count[i][j-1]                        iff T[i] != S[j]

*/


class Solution{
    public:
        int count(string S, int m, string T, int n){
            //if both the strings are empty then return 1
            if(m==0 && n==0)
                return 1;

            //If Target string is empty then return 1.
            //An empty string is subsequence of all
            if(n==0)
                return 1;
            
            //If the source string is null then return 0
            if(m==0)
                return 0;

            // If last characters are different, ignore 
            // last char of first string and recur for 
            // remaining string 
            if(S[m-1]!=T[n-1])
                return count(S, m-1, T, n);
            
            // If last characters are same 
            // Recur for remaining strings by 
            // 1. considering last characters of both strings 
            // 2. ignoring last character of first string
            //Take the sum of both the counts
            return count(S, m-1, T, n) + count(S, m-1, T, n-1);
        }

        int countDistinctOccurenceAsSubsequenceNaive(string S, string T){
            int m = S.length();
            int n = T.length();

            return count(S, m, T, n);
        }

        int countDistinctOccurenceAsSubsequenceBottomUp(string s, string t) {
            int n = t.length();
            int m = s.length();
            
            int dp[n+1][m+1] = {0};
            for(int i=0; i<=m; i++)
                dp[0][i] = 1;
            
            for(int i=1; i<=n; i++){
                for(int j=1; j<=m; j++){
                    if(t[i-1]==s[j-1])
                        dp[i][j] = dp[i-1][j-1] + dp[i][j-1];
                    else
                        dp[i][j] = dp[i][j-1];
                }
            }
            return dp[n][m];
        }
};

int main(){
    Solution obj;
    string S = "banana";
    string T = ""ban;
    cout<<obj.countDistinctOccurenceAsSubsequence(S, T);

    return 0;
}