#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Minimum Number of Deletions to Make a String Palindrome
    ─────────────────────────────────────────────────────────────────

    Problem Statement:
    ------------------
    Given a string s, find the minimum number of characters to be deleted
    from s to make it a palindrome.

    Examples:
    ---------
    Input:  s = "aebcbda"
    Output: 2
    Explanation: Remove 'e' and 'd' → "abcba" (palindrome).

    Input:  s = "geeksforgeeks"
    Output: 8
    Explanation: Remove 8 chars → "eee" or similar palindrome (LPS length = 5).

    ════════════════════════════════════════════════════════════════════════
    KEY INSIGHT: Deletions = n - LPS_length
    ════════════════════════════════════════════════════════════════════════

    The Longest Palindromic Subsequence (LPS) is the longest part of the string
    that is already a palindrome (as a subsequence).

    To make the whole string a palindrome, we keep the LPS and delete everything else.

    Minimum deletions = n - LPS_length

    Example: s = "aebcbda" (n=7)
        LPS = "abcba" (length 5)
        Deletions = 7 - 5 = 2 ✓ (delete 'e' and 'd')

    ════════════════════════════════════════════════════════════════════════
    APPROACH 1: Using LCS(s, reverse(s))
    ════════════════════════════════════════════════════════════════════════

    LPS_length = LCS(s, reverse(s))
    Deletions = n - LCS(s, reverse(s))

    ════════════════════════════════════════════════════════════════════════
    APPROACH 2: Using Direct LPS (Interval DP)
    ════════════════════════════════════════════════════════════════════════

    LPS_length = LPS(s)
    Deletions = n - LPS(s)

    Both reduce to: compute LPS, subtract from n. One line on top of LPS.

    ════════════════════════════════════════════════════════════════════════

    Similarly:
    Minimum Number of INSERTIONS to make a string palindrome = n - LPS_length
    (Same answer! Inserting a char is equivalent to deleting its "pair" from the other side.)

    ════════════════════════════════════════════════════════════════════════
    K-Palindrome: Is a string K-Palindrome?
    ════════════════════════════════════════════════════════════════════════

    A string is K-palindrome if it can be made a palindrome by removing at most K chars.
    Answer: (min_deletions <= K) → (n - LPS_length <= K)

    ════════════════════════════════════════════════════════════════════════
*/

class Solution{
    // ── Recursive: O(2^n) time, O(n) stack ──
    // f(i, j) = LPS length of s[i..j]
    int lpsRecursive(string &s, int i, int j){
        if(i > j) return 0;       // empty range — no palindrome
        if(i == j) return 1;       // single char — palindrome of length 1

        if(s[i] == s[j])
            return 2 + lpsRecursive(s, i+1, j-1);   // both ends match, include both
        else
            return max(lpsRecursive(s, i+1, j),      // skip left char
                       lpsRecursive(s, i, j-1));     // skip right char
    }

    // ── Top-Down: O(n^2) time and space ──
    // States: (i, j) — range [i..j] of string
    int lpsTopDown(string &s, int i, int j, vector<vector<int>> &memo){
        if(i > j) return 0;
        if(i == j) return 1;

        if(memo[i][j] != -1)       // already computed
            return memo[i][j];

        if(s[i] == s[j])
            memo[i][j] = 2 + lpsTopDown(s, i+1, j-1, memo);
        else
            memo[i][j] = max(lpsTopDown(s, i+1, j, memo),
                             lpsTopDown(s, i, j-1, memo));

        return memo[i][j];
    }

    // ── Bottom-Up (Interval DP): O(n^2) time and space ──
    // Fill table by increasing distance (subproblem size)
    int lpsBottomUp(string &s){
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Base case: every single character is a palindrome of length 1
        for(int i = 0; i < n; i++)
            dp[i][i] = 1;

        // Fill for increasing distances (2 = pairs, 3 = triples, ..., n = full string)
        for(int distance = 2; distance <= n; distance++){
            for(int i = 0; i < n - distance + 1; i++){
                int j = i + distance - 1;   // j = right end of interval

                if(distance == 2 && s[i] == s[j])
                    dp[i][j] = 2;                          // pair of matching chars
                else if(s[i] == s[j])
                    dp[i][j] = 2 + dp[i+1][j-1];          // ends match, add 2 to inner LPS
                else
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1]); // skip left or right
            }
        }
        return dp[0][n-1];   // LPS of full string s[0..n-1]
    }

public:
    // Minimum deletions = characters NOT in the LPS
    int minDeletions(string s){
        int n = s.size();

        // int lpsLength = lpsRecursive(s, 0, n-1);

        // vector<vector<int>> memo(n, vector<int>(n, -1));
        // int lpsLength = lpsTopDown(s, 0, n-1, memo);

        int lpsLength = lpsBottomUp(s);

        return n - lpsLength;   // delete everything outside the LPS
    }

    // Minimum insertions = same as deletions (inserting = mirroring deleted chars)
    int minInsertions(string s){
        return minDeletions(s);
    }

    // K-palindrome: can we make it palindrome with at most k deletions?
    bool isKPalindrome(string s, int k){
        return minDeletions(s) <= k;
    }
};


int main(){
    Solution obj;

    // Min Deletions
    cout << "Min deletions (\"aebcbda\"): " << obj.minDeletions("aebcbda") << endl;  // 2
    cout << "Min deletions (\"geeksforgeeks\"): " << obj.minDeletions("geeksforgeeks") << endl;  // 8

    // Min Insertions (same answer)
    cout << "Min insertions (\"aebcbda\"): " << obj.minInsertions("aebcbda") << endl;  // 2

    // K-Palindrome
    cout << "Is \"aebcbda\" 2-palindrome? " << (obj.isKPalindrome("aebcbda", 2) ? "Yes" : "No") << endl;  // Yes
    cout << "Is \"aebcbda\" 1-palindrome? " << (obj.isKPalindrome("aebcbda", 1) ? "Yes" : "No") << endl;  // No

    return 0;
}
