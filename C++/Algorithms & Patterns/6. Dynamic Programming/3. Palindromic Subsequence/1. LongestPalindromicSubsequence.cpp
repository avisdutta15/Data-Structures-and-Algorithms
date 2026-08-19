#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Longest Palindromic Subsequence (LeetCode 516)
    ────────────────────────────────────────────────────────

    https://www.youtube.com/watch?v=M4pfB3G-YQc
    https://www.youtube.com/watch?v=_nCsPn7_OgI
    https://algo.monster/problems/dp_interval_intro
    https://algo.monster/liteproblems/516

    Problem Statement:
    ------------------
    Given a string s, find the longest palindromic subsequence's length in s.
    A subsequence is a sequence derived from the string by deleting some or no
    characters without changing the order of the remaining characters.

    Examples:
    ---------
    Input:  s = "bbbab"
    Output: 4
    Explanation: "bbbb" is the longest palindromic subsequence.

    Input:  s = "cbbd"
    Output: 2
    Explanation: "bb" is the longest palindromic subsequence.

    Input:  s = "agbcba"
    Output: 5
    Explanation: "abcba" is the longest palindromic subsequence.

    ════════════════════════════════════════════════════════════════════════
    KEY INSIGHT: LPS = LCS(s, reverse(s))
    ════════════════════════════════════════════════════════════════════════

    The longest palindromic subsequence of s is the same as the longest
    common subsequence of s and reverse(s).

    Why? A palindrome reads the same forwards and backwards. So the longest
    subsequence that appears in both s and reverse(s) must be a palindrome.

    Example: s = "agbcba", rev = "abcbga"
        LCS("agbcba", "abcbga") = "abcba" (length 5) → palindrome ✓

    ════════════════════════════════════════════════════════════════════════
    APPROACH 1: LCS of s and reverse(s)
    ════════════════════════════════════════════════════════════════════════

    Standard LCS recurrence:

    f(i, j) = length of LCS of s[0..i-1] and t[0..j-1]
              where t = reverse(s)

    Base cases:
        f(0, j) = 0    (empty first string)
        f(i, 0) = 0    (empty second string)

    Recurrence:
        if s[i-1] == t[j-1]:
            f(i, j) = 1 + f(i-1, j-1)         // match: include this char
        else:
            f(i, j) = max(f(i-1, j), f(i, j-1))  // skip one or the other

    Answer: f(len, len)

    ════════════════════════════════════════════════════════════════════════
    APPROACH 2: Direct LPS (Interval DP)
    ════════════════════════════════════════════════════════════════════════

    f(i, j) = length of longest palindromic subsequence of s[i..j]

    Base cases:
        f(i, i) = 1        (single character is a palindrome of length 1)
        f(i, j) = 0 if i > j   (empty range)

    Recurrence:
        if s[i] == s[j]:
            f(i, j) = 2 + f(i+1, j-1)         // both ends match, include both
        else:
            f(i, j) = max(f(i+1, j), f(i, j-1))  // skip left or skip right

    Answer: f(0, n-1)

    Note: This is "interval DP" — the subproblem is defined by a range [i, j].
    The table must be filled diagonally or by gap length.

    Example Matrix Transition: s = "abcba" (n=5)
    ─────────────────────────────────────────────

    dp[i][j] = LPS length of s[i..j]

    Initial (gap=0, single chars — all 1):

           a  b  c  b  a
        j: 0  1  2  3  4
    i=0:   1  .  .  .  .
    i=1:   .  1  .  .  .
    i=2:   .  .  1  .  .
    i=3:   .  .  .  1  .
    i=4:   .  .  .  .  1

    Gap=1 (pairs):
      dp[0][1]: s[0]='a', s[1]='b'. a≠b → max(dp[1][1], dp[0][0]) = max(1,1) = 1
      dp[1][2]: s[1]='b', s[2]='c'. b≠c → max(dp[2][2], dp[1][1]) = max(1,1) = 1
      dp[2][3]: s[2]='c', s[3]='b'. c≠b → max(dp[3][3], dp[2][2]) = max(1,1) = 1
      dp[3][4]: s[3]='b', s[4]='a'. b≠a → max(dp[4][4], dp[3][3]) = max(1,1) = 1

           a  b  c  b  a
        j: 0  1  2  3  4
    i=0:   1  1  .  .  .
    i=1:   .  1  1  .  .
    i=2:   .  .  1  1  .
    i=3:   .  .  .  1  1
    i=4:   .  .  .  .  1

    Gap=2 (triples):
      dp[0][2]: s[0]='a', s[2]='c'. a≠c → max(dp[1][2], dp[0][1]) = max(1,1) = 1
      dp[1][3]: s[1]='b', s[3]='b'. b==b → 2 + dp[2][2] = 2 + 1 = 3
      dp[2][4]: s[2]='c', s[4]='a'. c≠a → max(dp[3][4], dp[2][3]) = max(1,1) = 1

           a  b  c  b  a
        j: 0  1  2  3  4
    i=0:   1  1  1  .  .
    i=1:   .  1  1  3  .
    i=2:   .  .  1  1  1
    i=3:   .  .  .  1  1
    i=4:   .  .  .  .  1

    Gap=3:
      dp[0][3]: s[0]='a', s[3]='b'. a≠b → max(dp[1][3], dp[0][2]) = max(3,1) = 3
      dp[1][4]: s[1]='b', s[4]='a'. b≠a → max(dp[2][4], dp[1][3]) = max(1,3) = 3

           a  b  c  b  a
        j: 0  1  2  3  4
    i=0:   1  1  1  3  .
    i=1:   .  1  1  3  3
    i=2:   .  .  1  1  1
    i=3:   .  .  .  1  1
    i=4:   .  .  .  .  1

    Gap=4 (full string):
      dp[0][4]: s[0]='a', s[4]='a'. a==a → 2 + dp[1][3] = 2 + 3 = 5

           a  b  c  b  a
        j: 0  1  2  3  4
    i=0:   1  1  1  3  5  ← ANSWER
    i=1:   .  1  1  3  3
    i=2:   .  .  1  1  1
    i=3:   .  .  .  1  1
    i=4:   .  .  .  .  1

    Answer: dp[0][4] = 5 ✓ (LPS = "abcba")

    Fill order: diagonal by diagonal (gap 0 → gap 1 → gap 2 → ... → gap n-1).
    Each cell dp[i][j] only depends on dp[i+1][j-1], dp[i+1][j], dp[i][j-1] —
    all of which are computed in earlier gaps (smaller intervals).

    ════════════════════════════════════════════════════════════════════════
    PRINTING THE LPS (Backtrack through LCS table)
    ════════════════════════════════════════════════════════════════════════

    After building the LCS table for s and reverse(s):
    Start at dp[m][n]. At each step:
    - If s[i-1] == t[j-1]: this char is in the LPS → add it, move diagonally (i-1, j-1)
    - Else: move in direction of larger value (dp[i-1][j] or dp[i][j-1])

    ════════════════════════════════════════════════════════════════════════
*/

class SolutionLCS{

    // ══════════════════════════════════════════════════════════════════════
    // APPROACH 1: LCS(s, reverse(s))
    // ══════════════════════════════════════════════════════════════════════

    // ── Recursive: O(2^n) ──
    int lcsRecursive(string &s, string &t, int i, int j){
        if(i == 0 || j == 0)
            return 0;

        if(s[i-1] == t[j-1])
            return 1 + lcsRecursive(s, t, i-1, j-1);
        else
            return max(lcsRecursive(s, t, i-1, j), lcsRecursive(s, t, i, j-1));
    }

    // ── Top-Down: O(m * n) ──
    int lcsTopDown(string &s, string &t, int i, int j, vector<vector<int>> &memo){
        if(i == 0 || j == 0)
            return 0;

        if(memo[i][j] != -1)
            return memo[i][j];

        if(s[i-1] == t[j-1])
            memo[i][j] = 1 + lcsTopDown(s, t, i-1, j-1, memo);
        else
            memo[i][j] = max(lcsTopDown(s, t, i-1, j, memo), lcsTopDown(s, t, i, j-1, memo));

        return memo[i][j];
    }

    // ── Bottom-Up: O(m * n) time and space ──
    int lcsBottomUp(string &s, string &t){
        int m = s.size(), n = t.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

        for(int i = 0; i <= m; i++){
            for(int j = 0; j <= n; j++){
                if(i == 0 || j == 0)
                    dp[i][j] = 0;
                else if(s[i-1] == t[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        return dp[m][n];
    }

    // ── Print LPS using LCS backtracking ──
    string printLPS_LCS(string &s, string &t){
        int m = s.size(), n = t.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

        // Build LCS table
        for(int i = 0; i <= m; i++){
            for(int j = 0; j <= n; j++){
                if(i == 0 || j == 0)
                    dp[i][j] = 0;
                else if(s[i-1] == t[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }

        // Backtrack to find the LCS string (= LPS)
        string lps = "";
        int i = m, j = n;
        while(i > 0 && j > 0){
            if(s[i-1] == t[j-1]){
                lps += s[i-1];     // this char is in the LPS
                i--; j--;          // move diagonally
            }
            else if(dp[i-1][j] > dp[i][j-1])
                i--;               // move up (skip char from s)
            else
                j--;               // move left (skip char from t)
        }

        reverse(lps.begin(), lps.end());  // we built it backwards
        return lps;
    }

public:
    int longestPalindromeSubseq(string s){
        string t = s;
        reverse(t.begin(), t.end());

        // return lcsRecursive(s, t, s.size(), t.size());

        // int m = s.size(), n = t.size();
        // vector<vector<int>> memo(m+1, vector<int>(n+1, -1));
        // return lcsTopDown(s, t, m, n, memo);

        return lcsBottomUp(s, t);
    }

    string printLPS(string s){
        string t = s;
        reverse(t.begin(), t.end());
        return printLPS_LCS(s, t);
    }
};


class SolutionLPS{

    // ══════════════════════════════════════════════════════════════════════
    // APPROACH 2: Direct LPS (Interval DP)
    // ══════════════════════════════════════════════════════════════════════

    // ── Recursive: O(2^n) ──
    int lpsRecursive(string &s, int i, int j){
        if(i > j)
            return 0;       // empty range
        if(i == j)
            return 1;       // single char

        if(s[i] == s[j])
            return 2 + lpsRecursive(s, i+1, j-1);
        else
            return max(lpsRecursive(s, i+1, j), lpsRecursive(s, i, j-1));
    }

    // ── Top-Down: O(n^2) ──
    int lpsTopDown(string &s, int i, int j, vector<vector<int>> &memo){
        if(i > j)
            return 0;
        if(i == j)
            return 1;

        if(memo[i][j] != -1)
            return memo[i][j];

        if(s[i] == s[j])
            memo[i][j] = 2 + lpsTopDown(s, i+1, j-1, memo);
        else
            memo[i][j] = max(lpsTopDown(s, i+1, j, memo), lpsTopDown(s, i, j-1, memo));

        return memo[i][j];
    }

    // ── Bottom-Up (Interval DP): O(n^2) ──
    // Fill by distance: distance=1 (single chars), distance=2 (pairs), ..., distance=n (full string)
    int lpsBottomUp(string &s){
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Base case: single characters (distance = 1)
        for(int i = 0; i < n; i++)
            dp[i][i] = 1;

        // Fill for increasing distances (2 to n)
        for(int distance = 2; distance <= n; distance++){
            // For every distance, fix i and j with width `distance` apart
            for(int i = 0; i < n - distance + 1; i++){
                int j = i + distance - 1;

                if(distance == 2 && s[i] == s[j])
                    dp[i][j] = 2;
                else if(s[i] == s[j])
                    dp[i][j] = 2 + dp[i+1][j-1];
                else
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
            }
        }
        return dp[0][n-1];
    }

    // ── Print LPS using Interval DP backtracking ──
    string printLPS_Interval(string &s){
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for(int i = 0; i < n; i++)
            dp[i][i] = 1;

        for(int gap = 1; gap < n; gap++){
            for(int i = 0; i + gap < n; i++){
                int j = i + gap;
                if(s[i] == s[j])
                    dp[i][j] = 2 + dp[i+1][j-1];
                else
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
            }
        }

        // Backtrack to build the palindrome
        string left = "", right = "";
        int i = 0, j = n - 1;
        while(i < j){
            if(s[i] == s[j]){
                left += s[i];      // add to left half
                right += s[j];     // add to right half
                i++; j--;
            }
            else if(dp[i+1][j] > dp[i][j-1])
                i++;               // skip left char
            else
                j--;               // skip right char
        }
        // If i == j, there's a middle character
        string mid = (i == j) ? string(1, s[i]) : "";
        reverse(right.begin(), right.end());
        return left + mid + right;
    }

public:
    int longestPalindromeSubseq(string s){
        int n = s.size();

        // return lpsRecursive(s, 0, n-1);

        // vector<vector<int>> memo(n, vector<int>(n, -1));
        // return lpsTopDown(s, 0, n-1, memo);

        return lpsBottomUp(s);
    }

    string printLPS(string s){
        return printLPS_Interval(s);
    }
};


int main(){
    SolutionLCS sol1;
    SolutionLPS sol2;

    string s1 = "bbbab";
    cout << "=== Approach 1: LCS ===" << endl;
    cout << "LPS length: " << sol1.longestPalindromeSubseq(s1) << endl;  // 4
    cout << "LPS string: " << sol1.printLPS(s1) << endl;                  // "bbbb"

    cout << "\n=== Approach 2: Interval DP ===" << endl;
    cout << "LPS length: " << sol2.longestPalindromeSubseq(s1) << endl;  // 4
    cout << "LPS string: " << sol2.printLPS(s1) << endl;                  // "bbbb"

    string s2 = "agbcba";
    cout << "\n=== s = \"agbcba\" ===" << endl;
    cout << "LCS approach: " << sol1.longestPalindromeSubseq(s2) << " → " << sol1.printLPS(s2) << endl;
    cout << "LPS approach: " << sol2.longestPalindromeSubseq(s2) << " → " << sol2.printLPS(s2) << endl;

    return 0;
}
