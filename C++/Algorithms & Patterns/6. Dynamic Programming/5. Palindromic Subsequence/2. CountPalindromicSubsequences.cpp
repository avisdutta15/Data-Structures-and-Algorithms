#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Count All Palindromic Subsequences
    ─────────────────────────────────────────────

    Problem Statement:
    ------------------
    Given a string s, count the total number of palindromic subsequences in s.
    (Including single characters and the empty subsequence is typically excluded.)

    Examples:
    ---------
    Input:  s = "abcd"
    Output: 4
    Explanation: "a", "b", "c", "d" (only single chars are palindromes here).

    Input:  s = "aab"
    Output: 4
    Explanation: "a", "a", "b", "aa" → 4 palindromic subsequences.

    Input:  s = "aba"
    Output: 5
    Explanation: "a", "b", "a", "aa", "aba" → 5.

    ════════════════════════════════════════════════════════════════════════
    KEY INSIGHT: Interval DP — Count instead of Length
    ════════════════════════════════════════════════════════════════════════

    Similar to LPS (longest palindromic subsequence) which uses interval DP,
    but instead of tracking the LENGTH of the longest, we COUNT all of them.

    ════════════════════════════════════════════════════════════════════════
    RECURRENCE (Detailed Derivation)
    ════════════════════════════════════════════════════════════════════════

    f(i, j) = number of palindromic subsequences in s[i..j]

    Base cases:
        f(i, i) = 1        (single char is one palindrome)
        f(i, j) = 0 if i > j   (empty range)

    ────────────────────────────────────────────────────────────────────
    CASE 1: s[i] != s[j]
    ────────────────────────────────────────────────────────────────────

    Example: s = "abc", i=0, j=2. s[0]='a', s[2]='c', a≠c.

    Palindromes in "abc" can be:
    - In "bc" (skip 'a') → f(1, 2) = {"b", "c"} = 2
    - In "ab" (skip 'c') → f(0, 1) = {"a", "b"} = 2
    - Overlap: "b" is in BOTH → f(1, 1) = {"b"} = 1

    Standard inclusion-exclusion (no new palindromes created):
        f(i, j) = f(i+1, j) + f(i, j-1) - f(i+1, j-1)
                = 2 + 2 - 1 = 3. Palindromes: {"a", "b", "c"} ✓

    ────────────────────────────────────────────────────────────────────
    CASE 2: s[i] == s[j]
    ────────────────────────────────────────────────────────────────────

    Example: s = "aba", i=0, j=2. s[0]='a', s[2]='a', a==a.

    Step 1: Start with inclusion-exclusion (same as case 1):
        f(i+1, j) + f(i, j-1) - f(i+1, j-1)
        = f("ba") + f("ab") - f("b")
        = 2 + 2 - 1 = 3.  Palindromes so far: {"a"(idx0), "b", "a"(idx2)}

    Step 2: Since s[i] == s[j] == 'a', we get NEW palindromes:

        (a) The pair (s[i], s[j]) = The matching outer characters themselves. 
            The outer "a" and "a" form exactly 1 new palindrome of length 2: "aa"
            "aa" → +1 new palindrome.

        (b) Take every palindrome from inner string f(i+1, j-1) = f("b") = {"b"},
            wrap each with 'a'...'a':
            "b" → "aba" → +1 new palindrome.
            In general: Every single palindrome in the middle can now be wrapped in 'a's.
            (e.g., "b" becomes "aba". This adds another dp[i + 1][j - 1] to our count).
            i.e. +f(i+1, j-1) new wrapped palindromes.

        Total new = 1 + f(i+1, j-1)

    Step 3: Combine:
        f(i, j) = (f(i+1,j) + f(i,j-1) - f(i+1,j-1)) + (1 + f(i+1,j-1))
                = f(i+1,j) + f(i,j-1) - f(i+1,j-1) + 1 + f(i+1,j-1)
                = f(i+1,j) + f(i,j-1) + 1
                                         ↑ the -f and +f cancel out!

        = 2 + 2 + 1 = 5.  Palindromes: {"a"(0), "b", "a"(2), "aa", "aba"} ✓

    ────────────────────────────────────────────────────────────────────
    FINAL FORMULAS:
    ────────────────────────────────────────────────────────────────────

    s[i] != s[j]:  f(i,j) = f(i+1,j) + f(i,j-1) - f(i+1,j-1)
                             (pure inclusion-exclusion, no new palindromes)

    s[i] == s[j]:  f(i,j) = f(i+1,j) + f(i,j-1) + 1
                             (inclusion-exclusion + new pair + wrappings, which
                              simplifies because -f(i+1,j-1) and +f(i+1,j-1) cancel)

    ════════════════════════════════════════════════════════════════════════
    WORKED EXAMPLE: s = "aba"
    ════════════════════════════════════════════════════════════════════════

    Base (distance=1):
        dp[0][0] = 1 ("a")
        dp[1][1] = 1 ("b")
        dp[2][2] = 1 ("a")

    Distance=2:
        dp[0][1]: s[0]='a', s[1]='b'. a≠b → dp[1][1] + dp[0][0] - dp[1][0]
                  = 1 + 1 - 0 = 2.  Palindromes: "a", "b"
        dp[1][2]: s[1]='b', s[2]='a'. b≠a → dp[2][2] + dp[1][1] - dp[2][1]
                  = 1 + 1 - 0 = 2.  Palindromes: "b", "a"

    Distance=3:
        dp[0][2]: s[0]='a', s[2]='a'. a==a → dp[1][2] + dp[0][1] + 1
                  = 2 + 2 + 1 = 5.
                  Palindromes: "a"(idx0), "b", "a"(idx2), "aa", "aba" → 5 ✓

    ════════════════════════════════════════════════════════════════════════
*/

class Solution{
    // ── Recursive: O(2^n) ──
    int countPalSubseqRecursive(string &s, int i, int j){
        if(i > j) return 0;       // empty range
        if(i == j) return 1;       // single char = 1 palindrome

        if(s[i] == s[j])
            return countPalSubseqRecursive(s, i+1, j)
                 + countPalSubseqRecursive(s, i, j-1)
                 + 1;   // existing + wrapping all inner palindromes + new pair
        else
            return countPalSubseqRecursive(s, i+1, j)
                 + countPalSubseqRecursive(s, i, j-1)
                 - countPalSubseqRecursive(s, i+1, j-1);  // inclusion-exclusion
    }

    // ── Top-Down: O(n^2) ──
    int countPalSubseqTopDown(string &s, int i, int j, vector<vector<int>> &memo){
        if(i > j) return 0;
        if(i == j) return 1;

        if(memo[i][j] != -1)
            return memo[i][j];

        if(s[i] == s[j])
            memo[i][j] = countPalSubseqTopDown(s, i+1, j, memo)
                       + countPalSubseqTopDown(s, i, j-1, memo)
                       + 1;
        else
            memo[i][j] = countPalSubseqTopDown(s, i+1, j, memo)
                       + countPalSubseqTopDown(s, i, j-1, memo)
                       - countPalSubseqTopDown(s, i+1, j-1, memo);

        return memo[i][j];
    }

    // ── Bottom-Up (Interval DP): O(n^2) ──
    int countPalSubseqBottomUp(string &s){
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Base case: single characters
        for(int i = 0; i < n; i++)
            dp[i][i] = 1;

        // Fill by increasing distance
        for(int distance = 2; distance <= n; distance++){
            for(int i = 0; i < n - distance + 1; i++){
                int j = i + distance - 1;

                if(s[i] == s[j])
                    // All from (i+1,j) + all from (i,j-1) + 1 new pair
                    // The overlap f(i+1,j-1) cancels with new wrappings
                    dp[i][j] = dp[i+1][j] + dp[i][j-1] + 1;
                else
                    // Inclusion-exclusion: union without new palindromes
                    dp[i][j] = dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1];
            }
        }
        return dp[0][n-1];
    }

public:
    int countPalindromicSubsequences(string s){
        int n = s.size();

        // return countPalSubseqRecursive(s, 0, n-1);

        // vector<vector<int>> memo(n, vector<int>(n, -1));
        // return countPalSubseqTopDown(s, 0, n-1, memo);

        return countPalSubseqBottomUp(s);
    }
};


int main(){
    Solution obj;

    cout << "Count (\"abcd\"): " << obj.countPalindromicSubsequences("abcd") << endl;  // 4
    cout << "Count (\"aab\"): " << obj.countPalindromicSubsequences("aab") << endl;    // 4
    cout << "Count (\"aba\"): " << obj.countPalindromicSubsequences("aba") << endl;    // 5
    cout << "Count (\"aaa\"): " << obj.countPalindromicSubsequences("aaa") << endl;    // 7 (a,a,a,aa,aa,aa,aaa)

    return 0;
}
