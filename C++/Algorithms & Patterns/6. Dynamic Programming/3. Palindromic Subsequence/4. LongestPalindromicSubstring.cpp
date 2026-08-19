#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Longest Palindromic Substring (LeetCode 5)
    ────────────────────────────────────────────────────

    Problem Statement:
    ------------------
    Given a string s, return the longest SUBSTRING (contiguous) that is a palindrome.

    Note: SUBSTRING (contiguous) not SUBSEQUENCE (can skip chars).

    Examples:
    ---------
    Input:  s = "babad"
    Output: "bab" (or "aba")

    Input:  s = "cbbd"
    Output: "bb"

    Constraints:
    ------------
    - 1 <= s.length <= 1000

    ════════════════════════════════════════════════════════════════════════
    DIFFERENCE FROM LPS (Longest Palindromic Subsequence)
    ════════════════════════════════════════════════════════════════════════

    LPS: subsequence (can skip chars). Uses interval DP on "length".
    This: substring (must be contiguous). Uses "is palindrome" check.

    Key: we don't need to find the longest palindromic sequence of chars —
    we need the longest contiguous window that reads the same both ways.

    ════════════════════════════════════════════════════════════════════════
    APPROACH 1: Expand From Center — O(n^2) time, O(1) space
    ════════════════════════════════════════════════════════════════════════

    A palindrome expands from its center. For each possible center:
    - Odd length: center is one char (n possible centers)
    - Even length: center is between two chars (n-1 possible centers)

    For each center, expand outward while s[left] == s[right].
    Track the longest palindrome found.

        for(int center = 0; center < n; center++){
            // Odd length palindrome (center = single char)
            int len1 = expandFromCenter(s, center, center);
            // Even length palindrome (center = between two chars)
            int len2 = expandFromCenter(s, center, center + 1);

            int len = max(len1, len2);
            if(len > maxLen){
                maxLen = len;
                start = center - (len - 1) / 2;  // calculate start index
            }
        }

    The palindrome is centered at center and has total length len. 
    We need to find where it starts (the leftmost index).

    Example: s = "xbabad", palindrome "bab" centered at index 2 ('b'), len = 3

        x  b  a  b  a  d
        0  1  2  3  4  5
            ↑     ↑
        start center

    start = center - (left half length)
        = center - (len - 1) / 2
        = 2 - (3 - 1) / 2
        = 2 - 1
        = 1 ✓ ("bab" starts at index 1)
    Why (len - 1) / 2?

    A palindrome of length len extends (len - 1) / 2 characters to the LEFT of center.
    For odd length 5: extends 2 to the left. (5-1)/2 = 2 ✓
    For even length 4 (center is the left-middle char): extends 1 to the left. (4-1)/2 = 1 ✓
    Odd (len=5):   [s][s][C][s][s]     ← center is C, 2 chars to the left
                        ↑
                start = center - 2

    Even (len=4):  [s][C][s][s]        ← center is left-middle, 1 char to the left
                    ↑
                start = center - 1
    The (len-1)/2 formula handles both odd and even cases with integer division.

    Total centers = 2n - 1. Each expansion is O(n) worst case.
    Time: O(n^2), Space: O(1).

    ════════════════════════════════════════════════════════════════════════
    APPROACH 2: Interval DP — O(n^2) time, O(n^2) space
    ════════════════════════════════════════════════════════════════════════

    f(i, j) = is s[i..j] a palindrome? (bool)

    Base cases:
        f(i, i) = true                  (single char)
        f(i, i+1) = (s[i] == s[i+1])   (pair of chars)
        f(i, j) = false if i > j        (empty/invalid)

    Recurrence:
        f(i, j) = (s[i] == s[j]) AND f(i+1, j-1)
                  (outer chars match AND inner substring is palindrome)

    Fill by increasing distance. Track longest (i,j) where f(i,j) = true.

    ════════════════════════════════════════════════════════════════════════
    WORKED EXAMPLE (Expand from Center): s = "babad"
    ════════════════════════════════════════════════════════════════════════

    Center at index 0 ('b'): expand → "b" (length 1)
    Center at index 1 ('a'): expand → 'b'=='b'? No. left='b', right='b'? 
        Wait: left=0,right=2: s[0]='b', s[2]='b' → match! "bab" (length 3)
        left=-1: stop.
    Center at index 2 ('b'): expand → s[1]='a', s[3]='a' → match! "aba" (length 3)
        s[0]='b', s[4]='d' → no match. Stop.
    Center at index 3 ('a'): expand → s[2]='b', s[4]='d' → no. "a" (length 1)
    Center at index 4 ('d'): expand → "d" (length 1)
    Even centers: (0,1) 'b'≠'a', (1,2) 'a'≠'b', (2,3) 'b'≠'a', (3,4) 'a'≠'d'

    Longest = "bab" or "aba" (length 3) ✓

    ════════════════════════════════════════════════════════════════════════
*/

class Solution{
    // ── Approach 1: Expand From Center — O(n^2) time, O(1) space ──

    // Helper: expand from center, return length of palindrome
    int expandFromCenter(string &s, int left, int right){
        while(left >= 0 && right < (int)s.size() && s[left] == s[right]){
            left--;
            right++;
        }
        // After loop: left and right are one past the palindrome bounds
        return right - left - 1;  // length of palindrome
    }

    string longestPalindromeExpand(string &s){
        int n = s.size();
        int start = 0, maxLen = 0;

        for(int center = 0; center < n; center++){
            // Odd length palindrome (center = single char)
            int len1 = expandFromCenter(s, center, center);
            // Even length palindrome (center = between two chars)
            int len2 = expandFromCenter(s, center, center + 1);

            int len = max(len1, len2);
            if(len > maxLen){
                maxLen = len;
                start = center - (len - 1) / 2;  // calculate start index
            }
        }
        return s.substr(start, maxLen);
    }

    // ── Approach 2: Interval DP — O(n^2) time and space ──
    // dp[i][j] = is s[i..j] a palindrome?
    string longestPalindromeDP(string &s){
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n, false));

        int start = 0, maxLen = 1;

        // Base case: single chars are palindromes
        for(int i = 0; i < n; i++)
            dp[i][i] = true;

        // Base case: check pairs
        for(int i = 0; i < n - 1; i++){
            if(s[i] == s[i+1]){
                dp[i][i+1] = true;
                start = i;
                maxLen = 2;
            }
        }

        // Fill for distance >= 3
        for(int distance = 3; distance <= n; distance++){
            for(int i = 0; i < n - distance + 1; i++){
                int j = i + distance - 1;

                // s[i..j] is palindrome if outer chars match AND inner is palindrome
                if(s[i] == s[j] && dp[i+1][j-1]){
                    dp[i][j] = true;
                    if(distance > maxLen){
                        start = i;
                        maxLen = distance;
                    }
                }
            }
        }
        return s.substr(start, maxLen);
    }

public:
    string longestPalindrome(string s){
        // return longestPalindromeExpand(s);
        return longestPalindromeDP(s);
    }
};


int main(){
    Solution obj;

    cout << "Longest palindromic substring (\"babad\"): " << obj.longestPalindrome("babad") << endl;  // "bab" or "aba"
    cout << "Longest palindromic substring (\"cbbd\"): " << obj.longestPalindrome("cbbd") << endl;    // "bb"
    cout << "Longest palindromic substring (\"a\"): " << obj.longestPalindrome("a") << endl;          // "a"
    cout << "Longest palindromic substring (\"racecar\"): " << obj.longestPalindrome("racecar") << endl;  // "racecar"

    return 0;
}
