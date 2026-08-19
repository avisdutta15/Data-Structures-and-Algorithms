#include <bits/stdc++.h>
using namespace std;

/*
    Given a string s, return the longest palindromic substring in s.

    Example 1:
    Input: s = "babad"
    Output: "bab"
    Note: "aba" is also a valid answer.

    Example 2:
    Input: s = "cbbd"
    Output: "bb"

    Example 3:
    Input: s = "a"
    Output: "a"

    Example 4:
    Input: s = "ac"
    Output: "a"

    Recurrence:
        Whether S[i...j] is a palindromic substring is stored in dp[i][j]
                   |
        dp[i][j] = |  S[i]==S[j]    then dp[i+1][j-1]+2
                   |  S[i]!=S[j]    then 0
                   |  i+1 = j i.e. 2 letter subtring then => 2.

        dp[i][j] can have boolen or int values
        dp[i][j] = true means substring s[i..j] is palindromic substring of length i-j+1.
        dp[i][j] = number means substring s[i..j] is palindromic substring of length number.
        
        Atlast the dp table contains all the substrings of S[i..j] which are palindromic i.e. dp[i][j] = true.
*/




class Solution {
public:
    string longestPalindrome(string S) {
        int N = S.length();
        vector<vector<int>> dp(N, vector<int>(N, 0));
        int lengthOfLongestPalindrome =  INT_MIN;
        int startIndex = 0;
        
        for(int i=0; i<N; i++){
            dp[i][i] = 1; 
            if(lengthOfLongestPalindrome<1){
                lengthOfLongestPalindrome = 1;
                startIndex = i;
            }
        }
        
        for(int distance = 2; distance<=N; distance++){
            for(int i=0; i<=N-distance; i++){
                int j = i + distance - 1;
                if(distance == 2 && S[i]==S[j]){
                    dp[i][j] = 2;
                }
                else if(S[i]==S[j] && dp[i+1][j-1]>0)
                    dp[i][j] = 2 + dp[i+1][j-1];
                
                //if the current substring S[i..j] is palindrome then check if it is
                //greater than any other previously seen palindrome. If yes then save
                //the start index as i and the length as distance.
                if(dp[i][j]>0 && lengthOfLongestPalindrome<distance){
                    lengthOfLongestPalindrome = distance;
                    startIndex = i;
                }
            }
        }
        return S.substr(startIndex, lengthOfLongestPalindrome);
    }
};