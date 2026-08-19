/*
    Given two strings s and t, return the number of distinct 
    subsequences of s which equals t.

    A string's subsequence is a new string formed from the original 
    string by deleting some (can be none) of the characters without 
    disturbing the remaining characters' relative positions. (i.e., "ACE" 
    is a subsequence of "ABCDE" while "AEC" is not).

    It is guaranteed the answer fits on a 32-bit signed integer.

    Example 1:
    Input: s = "rabbbit", t = "rabbit"
    Output: 3
    Explanation:
    As shown below, there are 3 ways you can generate "rabbit" from S.
    rabbbit
    rabbbit
    rabbbit

    Example 2:
    Input: s = "babgbag", t = "bag"
    Output: 5
    Explanation:
    As shown below, there are 5 ways you can generate "bag" from S.
    babgbag
    babgbag
    babgbag
    babgbag
    babgbag

    Approach: 
    recur(S, i, T, j):
        if(i<0 && j<0)      //if both S and T are empty then return 1. Because "" is a subsequence of "".
            return 1;

        if(i<0 && j>=0)     //if S is empty but T is not then return 0.
            return 0;

        if(j<0 && i>=0)     //if T is empty but S is not then we found a subsequence equals T. return 1.
            return 1;

        count = 0; // this stores the count of distinct subsequences of S ending at i that are equal to T ending at j
        If (S[i] == T[j])
            //skip current character of S and T and check others
            count = count + recur(S, i-1, T, j-1);     

        //Do not skip the current character of T but skip the current character of S.
        count = count + recur(S, i-1, T, j);
*/

class Solution1 {
public:
    int dp(string S, int i, string T, int j){
        if(i<0 && j<0)
            return 1;
        if(i<0 && j>=0)
            return 0;
        if(j<0 && i>=0)
            return 1;
        
        int count = 0;
        if(S[i] == T[j])
           count+=dp(S, i-1, T, j-1);
        
        count+=dp(S, i-1, T, j); 
        
        return count;
    }   
    
    int numDistinct(string s, string t) {
        return dp(s, s.length()-1, t, t.length()-1);
    }
};


class Solution2 {
    unordered_map<string, long long int> hash;
public:
    int numDistinct(string S, string T) {
        int N = S.length(), M = T.length();

        vector<vector<long long int>> DP(N+1, vector<long long int>(M+1, 0));

        //empty string in S is the subsequence of any string T
        for(int i=0; i<=N; i++)
            DP[i][0] = 1;

        for(long long int  i=1; i<=N; i++){
            for(long long int j=1; j<=M; j++){
                if(S[i-1] == T[j-1])
                    DP[i][j] += DP[i-1][j-1];
                DP[i][j] += DP[i-1][j];
            }
        }

        return DP[N][M];
    }
};

