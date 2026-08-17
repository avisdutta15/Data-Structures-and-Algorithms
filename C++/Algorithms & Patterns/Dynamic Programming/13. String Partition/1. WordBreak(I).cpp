#include <algorithm>
#include <iostream>
#include <climits>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement: (LeetCode 139 - Word Break)
    ------------------
    Given a string s and a dictionary of strings wordDict, return true if s can
    be segmented into a space-separated sequence of one or more dictionary words.
    The same word in the dictionary may be reused multiple times.

    Examples:
    --------
    Input: s = "leetcode", wordDict = ["leet","code"]
    Output: true
    Explanation: "leetcode" = "leet" + "code"

    Input: s = "applepenapple", wordDict = ["apple","pen"]
    Output: true
    Explanation: "apple" + "pen" + "apple"

    Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
    Output: false

    Constraints:
    ------------
    - 1 <= s.length <= 300
    - 1 <= wordDict.length <= 1000
    - 1 <= wordDict[i].length <= 20

    Approach:
    ---------
    This is a string partition problem: can we partition s into parts where each
    part is a valid dictionary word?

    Intuition:
    ----------
    At index i, try every possible word that starts at i.
    If s[i..i+len-1] is a valid word, then recursively check if s[i+len..end] can also be broken.
    If we reach the end of the string, return true.

    Recurrence:
        solve(i):
            if i == n: return true       // reached end, all parts are valid words
            for each word in dictionary:
                if s starts with word at index i:
                    if solve(i + word.length()) == true:
                        return true
            return false                 // no word matches at this position

        Answer: solve(0)

    Walkthrough: s = "leetcode", dict = {"leet", "code"}
    -------------------------------------------------------
    solve(0): try all words at index 0
      "leet" matches s[0..3] → solve(4)
        solve(4): try all words at index 4
          "leet" doesn't match s[4..7] ("code" != "leet")
          "code" matches s[4..7] → solve(8)
            solve(8): i == n → return true ✓

    Time: O(n * m * n) for memo where n=len(s), m=dict size, n for substring comparison.
    Space: O(n) for memo.
*/


// Recursion. But we are creating 3 strings in each call.
// We are not reusing the given string by adjusting i. 
class Solution0 {
private:
    bool solve(string s, unordered_set<string>& dict) {
        // Reached end — all parts were valid words
        if (s.empty()) return true;

        // If the entire string is a word
        if (dict.count(s)) return true;

        // Try every prefix
        for (int end = 1; end <= (int)s.size(); end++) {
            string prefix = s.substr(0, end);       // first 'end' characters
            string suffix = s.substr(end);          // remaining after prefix
            if (dict.count(prefix) && solve(suffix, dict)) {
                return true;
            }
        }

        return false;
    }

public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        return solve(s, dict);
    }
};


// ============================================================================
// Solution 1: Recursion
// Time: O(2^n) worst case (try all partition points), Space: O(n)
// ============================================================================
class Solution1 {
private:
    bool solve(string& s, int start_index, unordered_set<string>& dict) {
        // Reached end — all parts were valid words
        if (start_index == s.size())
            return true;

        // Try every possible word starting at index i
        for (int i = start_index; i <= (int)s.size(); i++) {
            // Extract the current prefix [startIndex...i]
            string word = s.substr(start_index, i - start_index + 1);

            //if prefix exists in the dictionary, then look for the remaining
            //string i.e. suffix
            if (dict.count(word) && solve(s, i + 1, dict)) {
                return true;
            }
        }

        return false;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        return solve(s, 0, dict);
    }
};

// ============================================================================
// Solution 2: Memoization
// Time: O(n² * m) where m = max word length, Space: O(n)
// ============================================================================
class Solution2 {
private:

    bool solve(string& s, int start_index, unordered_set<string>& dict, vector<int>& dp) {
        // Reached end — all parts were valid words
        if (start_index == s.size())
            return dp[start_index] = true;

        // Check memoization cache
        if (dp[start_index] != -1)
            return dp[start_index];

        // Try every possible word starting at index i
        for (int i = start_index; i <= (int)s.size(); i++) {
            // Extract the current prefix [startIndex...i]
            string word = s.substr(start_index, i - start_index + 1);

            //if prefix exists in the dictionary, then look for the remaining
            //string i.e. suffix
            if (dict.count(word) && solve(s, i + 1, dict, dp)) {
                return dp[start_index] = true;
            }
        }

        return dp[start_index] = false;
    }


public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        vector<int> dp(s.size(), -1);
        return solve(s, 0, dict, dp);
    }
};

// ============================================================================
// Solution 3: Bottom-Up
// Time: O(n² * m), Space: O(n)
// ============================================================================
// Direct translation:
//   solve(i):
//     if i == n: return true
//     for end = i+1 to n:
//       if s[i..end-1] in dict AND solve(end) == true: return true
//     return false
//
// dp[start_index] = can s[start_index..n-1] be segmented?
// Fill from start_index = n-1 down to 0 (since dp[start_index] depends on dp[i+1] where i > start_index).
class Solution3 {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        unordered_set<string> dict(wordDict.begin(), wordDict.end());

        // dp[start_index] = true if s[start_index..n-1] can be segmented
        vector<bool> dp(n + 1, false);

        // Base case: if start_index == n, return true (empty string)
        dp[n] = true;

        for (int start_index = n - 1; start_index >= 0; start_index--) {

            // Try every possible word starting at start_index
            // Mirrors: for (int i = start_index; i < n; i++)
            for (int i = start_index; i < n; i++) {

                // Extract the current prefix [start_index...i]
                // Mirrors: string word = s.substr(start_index, i - start_index + 1)
                string word = s.substr(start_index, i - start_index + 1);

                // If prefix exists in the dictionary, then look for the remaining
                // string i.e. suffix. Mirrors: if (dict.count(word) && solve(s, i+1, dict))
                if (dict.count(word) && dp[i + 1]) {
                    dp[start_index] = true;
                    break;
                }
            }
        }

        // Answer: solve(0) → dp[0]
        return dp[0];
    }
};


int main() {
    Solution1 recursion;
    Solution2 memo;
    Solution3 bottomUp;

    string s1 = "leetcode";
    vector<string> dict1 = {"leet", "code"};

    cout << "Recursion:   " << recursion.wordBreak(s1, dict1) << endl;  // 1 (true)
    cout << "Memoization: " << memo.wordBreak(s1, dict1) << endl;       // 1 (true)
    cout << "Bottom-Up:   " << bottomUp.wordBreak(s1, dict1) << endl;   // 1 (true)

    cout << endl;
    string s2 = "catsandog";
    vector<string> dict2 = {"cats", "dog", "sand", "and", "cat"};

    cout << "Recursion:   " << recursion.wordBreak(s2, dict2) << endl;  // 0 (false)
    cout << "Memoization: " << memo.wordBreak(s2, dict2) << endl;       // 0 (false)
    cout << "Bottom-Up:   " << bottomUp.wordBreak(s2, dict2) << endl;   // 0 (false)

    return 0;
}
