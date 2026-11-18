#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Palindromic Substrings (LeetCode 647)
    ────────────────────────────────────────────────

    Problem Statement:
    ------------------
    Given a string s, return the number of SUBSTRINGS (contiguous) that are
    palindromes.

    A string is a palindrome when it reads the same backward as forward.
    A substring is a contiguous sequence of characters within the string.

    Examples:
    ---------
    Input:  s = "abc"
    Output: 3
    Explanation: "a", "b", "c" — three palindromic substrings.

    Input:  s = "aaa"
    Output: 6
    Explanation: "a"(0), "a"(1), "a"(2), "aa"(0,1), "aa"(1,2), "aaa"(0,1,2) → 6.

    Constraints:
    ------------
    - 1 <= s.length <= 1000

    ════════════════════════════════════════════════════════════════════════
    KEY INSIGHT
    ════════════════════════════════════════════════════════════════════════

    This is the same as "Longest Palindromic Substring" (LC 5) but instead
    of finding the LONGEST, we COUNT all palindromic substrings.

    Both approaches from LC 5 work here — just count instead of track max.

    ════════════════════════════════════════════════════════════════════════
    APPROACH 1: Expand From Center — O(n^2) time, O(1) space
    ════════════════════════════════════════════════════════════════════════

    For each center (2n-1 total), expand outward.
    Every successful expansion is one more palindromic substring.

    Example: s = "aaa"
        Center 0 (odd): "a" → expand: "aaa" → 2 expansions = 2 palindromes ("a", "aaa")?
        Wait — each step in expansion is a palindrome:
            "a" (len 1) ✓, then s[-1]==s[1]? Out of bounds. Actually:
            center=0: expand(0,0) → just "a" → count 1.
            center=1: expand(1,1) → "a" → expand s[0]==s[2]? 'a'=='a' → "aaa" → count 2.
            center=2: expand(2,2) → "a" → count 1.
            Even centers: expand(0,1): 'a'=='a' → "aa" → count 1.
                         expand(1,2): 'a'=='a' → "aa" → count 1.
        Total: 1 + 2 + 1 + 1 + 1 = 6 ✓

    ════════════════════════════════════════════════════════════════════════
    APPROACH 2: Interval DP — O(n^2) time, O(n^2) space
    ════════════════════════════════════════════════════════════════════════

    f(i, j) = is s[i..j] a palindrome? (bool)

    Base cases:
        f(i, i) = true
        f(i, i+1) = (s[i] == s[i+1])
        f(i, j) = false if i > j

    Recurrence:
        f(i, j) = (s[i] == s[j]) AND f(i+1, j-1)

    Count all (i, j) where f(i, j) = true.

    ════════════════════════════════════════════════════════════════════════
*/

class Solution{
    // ── Approach 1: Expand From Center — O(n^2) time, O(1) space ──

    // Helper: expand from center, return COUNT of palindromes found
    int countFromCenter(string &s, int left, int right){
        int count = 0;
        while(left >= 0 && right < (int)s.size() && s[left] == s[right]){
            count++;    // each valid expansion is one palindromic substring
            left--;
            right++;
        }
        return count;
    }

    int countPalindromesExpand(string &s){
        int n = s.size();
        int total = 0;

        for(int center = 0; center < n; center++){
            // Odd length palindromes (center = single char)
            total += countFromCenter(s, center, center);
            // Even length palindromes (center = between two chars)
            total += countFromCenter(s, center, center + 1);
        }
        return total;
    }

    // ── Approach 2: Interval DP ──

    // Recursive: check if s[i..j] is a palindrome — O(2^n) without memo
    bool isPalindromeRecursive(string &s, int i, int j){
        if(i >= j) return true;              // empty or single char
        if(s[i] != s[j]) return false;       // outer chars don't match
        return isPalindromeRecursive(s, i+1, j-1);  // check inner
    }

    int countPalindromesRecursive(string &s){
        int n = s.size();
        int count = 0;
        // Check every possible substring s[i..j]
        for(int i = 0; i < n; i++){
            for(int j = i; j < n; j++){
                if(isPalindromeRecursive(s, i, j))
                    count++;
            }
        }
        return count;  // O(n^2 * 2^n) — very slow
    }

    // Top-Down: memoize isPalindrome(i, j) — O(n^2) time
    // memo[i][j]: -1 = not computed, 0 = false, 1 = true
    bool isPalindromeTopDown(string &s, int i, int j, vector<vector<int>> &memo){
        if(i >= j) return true;
        if(s[i] != s[j]) return false;

        if(memo[i][j] != -1)
            return memo[i][j];

        memo[i][j] = isPalindromeTopDown(s, i+1, j-1, memo) ? 1 : 0;
        return memo[i][j];
    }

    int countPalindromesTopDown(string &s){
        int n = s.size();
        vector<vector<int>> memo(n, vector<int>(n, -1));
        int count = 0;

        // Check every possible substring s[i..j]
        for(int i = 0; i < n; i++){
            for(int j = i; j < n; j++){
                if(isPalindromeTopDown(s, i, j, memo))
                    count++;
            }
        }
        return count;  // O(n^2) — each (i,j) computed at most once
    }

    // Bottom-Up: O(n^2) time and space
    int countPalindromesDP(string &s){
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        int count = 0;

        // Fill by increasing distance (1 = single chars, 2 = pairs, 3+)
        for(int distance = 1; distance <= n; distance++){
            for(int i = 0; i < n - distance + 1; i++){
                int j = i + distance - 1;

                if(distance == 1){
                    // Base case: single char is always a palindrome
                    dp[i][j] = true;
                    count++;
                }
                else if(distance == 2 && s[i] == s[j]){
                    // Base case: pair of matching chars
                    dp[i][j] = true;
                    count++;
                }
                else if(s[i] == s[j] && dp[i+1][j-1]){
                    // General case: outer chars match AND inner is palindrome
                    dp[i][j] = true;
                    count++;
                }
            }
        }
        return count;
    }

public:
    int countSubstrings(string s){
        // return countPalindromesExpand(s);      // O(n^2) time, O(1) space
        // return countPalindromesRecursive(s);   // O(n^2 * 2^n) — brute force
        // return countPalindromesTopDown(s);     // O(n^2) time and space
        return countPalindromesDP(s);             // O(n^2) time and space
    }
};


int main(){
    Solution obj;

    cout << "Count (\"abc\"): " << obj.countSubstrings("abc") << endl;      // 3
    cout << "Count (\"aaa\"): " << obj.countSubstrings("aaa") << endl;      // 6
    cout << "Count (\"racecar\"): " << obj.countSubstrings("racecar") << endl;  // 10

    return 0;
}
