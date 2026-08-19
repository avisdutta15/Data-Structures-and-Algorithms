#include <bits/stdc++.h>
using namespace std;

/*
    Given a string s, return the number of palindromic substrings in it.
    A string is a palindrome when it reads the same backward as forward.
    A substring is a contiguous sequence of characters within the string.

    Example 1:
    Input: s = "abc"
    Output: 3
    Explanation: Three palindromic strings: "a", "b", "c".

    Example 2:
    Input: s = "aaa"
    Output: 6
    Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
    
    Constraints:
    1 <= s.length <= 1000
    s consists of lowercase English letters.

    Approach:
    Same as longest palindromic substring. Just check if current substring dp[i][j]
    is palindrome? then do count++;
*/


class Solution {
public:
    int countSubstrings(string S) {
        int N = S.length();
        vector<vector<bool>> dp(N, vector<bool>(N, false));
        int count = 0;

        for(int i=0; i<N; i++){
            dp[i][i] = true; 
            count++;
        }

        for(int distance = 2; distance<=N; distance++){
            for(int i=0; i<=N-distance; i++){
                int j = i + distance - 1;
                if(distance == 2 && S[i]==S[j]){
                    dp[i][j] = true;
                }
                else if(S[i]==S[j] && dp[i+1][j-1] == true)
                    dp[i][j] = true;

                if(dp[i][j] == true)
                    count++;
            }
        }
        return count;
    }
};