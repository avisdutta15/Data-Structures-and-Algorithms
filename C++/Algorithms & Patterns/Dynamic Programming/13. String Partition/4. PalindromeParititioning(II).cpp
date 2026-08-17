#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement: (LeetCode 132 - Palindrome Partitioning II)
    ------------------
    Given a string s, return the minimum number of cuts needed so that every
    substring of the partition is a palindrome.

    Examples:
    --------
    Input: s = "aab"
    Output: 1
    Explanation: ["aa", "b"] — 1 cut.

    Input: s = "a"
    Output: 0

    Input: s = "ab"
    Output: 1
    Explanation: ["a", "b"] — 1 cut.

    Constraints:
    ------------
    - 1 <= s.length <= 2000

    Approach:
    ---------
    Same String Partition pattern as Word Break:
    - Word Break: "can I partition into valid dictionary words?"
    - This: "partition into palindromes with minimum cuts"

    Intuition:
    ----------
    At index start_index, try every possible end position i.
    If s[start_index..i] is a palindrome, then we make a cut after i and
    solve the remaining s[i+1..n-1].

    The number of cuts = number of partitions - 1.
    Easier to think: solve(start_index) = min cuts to partition s[start_index..n-1].

    Recurrence:
        solve(start_index):
            if start_index == n: return 0        // nothing to partition
            if isPalindrome(s[start_index..n-1]): return 0  // whole thing is palindrome, 0 cuts

            minCuts = INF
            for i = start_index to n-1:
                if isPalindrome(s[start_index..i]):
                    // 1 cut after index i + solve remaining
                    minCuts = min(minCuts, 1 + solve(i + 1))

            return minCuts

        Answer: solve(0)

    Optimization: Precompute isPalindrome[i][j] using DP to avoid O(n) check each time.

    Time: O(n²) with memoization + O(n²) for palindrome precomputation.
    Space: O(n²) for palindrome table + O(n) for dp.
*/

// ============================================================================
// Helper: Check if substring is palindrome (brute force O(n) per call)
// ============================================================================
bool isPalin(string& s, int l, int r) {
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++; r--;
    }
    return true;
}

// ============================================================================
// Solution 1: Recursion
// Time: O(2^n * n), Space: O(n)
// ============================================================================
class Solution1 {
private:
    int solve(string& s, int start_index, int n) {
        // Nothing left to partition
        if (start_index == n) return 0;

        // If remaining string is already a palindrome, 0 cuts needed
        if (isPalin(s, start_index, n - 1)) return 0;

        int minCuts = INT_MAX;
        for (int i = start_index; i < n; i++) {
            // If s[start_index..i] is a palindrome, cut here
            if (isPalin(s, start_index, i)) {
                int cutsForRest = solve(s, i + 1, n);
                minCuts = min(minCuts, 1 + cutsForRest);
            }
        }

        return minCuts;
    }

public:
    int minCut(string s) {
        int n = s.size();
        return solve(s, 0, n);
    }
};

// ============================================================================
// Solution 2: Memoization
// Time: O(n² * n) = O(n³) without palindrome precomputation, Space: O(n)
// ============================================================================
class Solution2 {
private:
    int solve(string& s, int start_index, int n, vector<int>& dp) {
        if (start_index == n) return 0;
        if (isPalin(s, start_index, n - 1)) return 0;
        if (dp[start_index] != -1) return dp[start_index];

        int minCuts = INT_MAX;
        for (int i = start_index; i < n; i++) {
            if (isPalin(s, start_index, i)) {
                int cutsForRest = solve(s, i + 1, n, dp);
                minCuts = min(minCuts, 1 + cutsForRest);
            }
        }

        return dp[start_index] = minCuts;
    }

public:
    int minCut(string s) {
        int n = s.size();
        vector<int> dp(n, -1);
        return solve(s, 0, n, dp);
    }
};

// ============================================================================
// Solution 3: Memoization + Precomputed Palindrome Table
// Time: O(n²), Space: O(n² + n)
// ============================================================================
// Precompute isPalin[i][j] = true if s[i..j] is palindrome.
// This avoids O(n) palindrome check inside the loop → total O(n²).
class Solution3 {
private:
    int solve(string& s, int start_index, int n, vector<int>& dp,
              vector<vector<bool>>& isPalin) {
        // empty string. 0 cuts
        if (start_index == n) 
            return 0;

        // if entire string is palindrome. Then 0 cuts
        if (isPalin[start_index][n - 1]) 
            return 0;

        // check the cache
        if (dp[start_index] != -1) 
            return dp[start_index];

        int minCuts = INT_MAX;
        for (int i = start_index; i < n; i++) {
            if (isPalin[start_index][i]) {
                int cutsForRest = solve(s, i + 1, n, dp, isPalin);
                minCuts = min(minCuts, 1 + cutsForRest);
            }
        }

        return dp[start_index] = minCuts;
    }

    // Build palindrome lookup table in O(n²)
    vector<vector<bool>> buildPalinTable(string& s) {
        int n = s.size();
        vector<vector<bool>> table(n, vector<bool>(n, false));

        // Every single char is palindrome
        // the left diagonal will be set to true
        for (int i = 0; i < n; i++) 
            table[i][i] = true;

        // Check substrings of increasing length (2, 3, 4, ..., n)
        for (int len = 2; len <= n; len++) {
            // Try all starting positions for this length
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;  // ending index of substring s[i..j]

                // A substring s[i..j] is palindrome if:
                //   1. Outer chars match: s[i] == s[j]
                //   2. Inner part is palindrome: table[i+1][j-1]
                //      (or length is 2, in which case matching outer chars is enough)
                if (s[i] == s[j]) {
                    if (len ==2)
                        table[i][j] = true;
                    else
                        table[i][j] = table[i + 1][j - 1];
                }
            }
        }

        return table;
    }

public:
    int minCut(string s) {
        int n = s.size();
        vector<vector<bool>> isPalin = buildPalinTable(s);

        // state : start_index. Since the recursion is changing only 1
        // variable, hence 1D DP array
        vector<int> dp(n, -1);
        return solve(s, 0, n, dp, isPalin);
    }
};

// ============================================================================
// Solution 4: Bottom-Up
// Time: O(n²), Space: O(n² + n)
// ============================================================================
// Direct translation:
//   solve(start_index):
//     if start_index == n: return 0
//     if isPalin[start_index][n-1]: return 0
//     minCuts = INF
//     for i = start_index to n-1:
//       if isPalin[start_index][i]:
//         minCuts = min(minCuts, 1 + solve(i+1))
//     return minCuts
//
// dp[start_index] depends on dp[i+1] where i >= start_index → fill right to left.
class Solution4 {
public:
    int minCut(string s) {
        int n = s.size();

        // Precompute palindrome table
        vector<vector<bool>> isPalin(n, vector<bool>(n, false));
        for (int i = 0; i < n; i++) isPalin[i][i] = true;
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                if (s[i] == s[j])
                    isPalin[i][j] = (len == 2) || isPalin[i + 1][j - 1];
            }
        }

        // state : start_index. Since the recursion is changing only 1
        // variable, hence 1D DP array
        // dp[start_index] = min cuts for s[start_index..n-1]
        vector<int> dp(n + 1, 0);
        // dp[n] = 0 (base case: nothing to partition)

        // Fill DP from right to left
        // Because dp[start_index] depends on dp[i + 1] where i >= start_index.
        // dp[start_index] needs dp[start_index + 1], dp[start_index + 2], ..., dp[n]
        for (int start_index = n - 1; start_index >= 0; start_index--) {
            // If entire remaining string is palindrome, 0 cuts
            if (isPalin[start_index][n - 1]) {
                dp[start_index] = 0;
                continue;
            }

            int minCuts = INT_MAX;
            for (int i = start_index; i < n; i++) {
                // If s[start_index..i] is palindrome, cut here
                // Mirrors: if (isPalin[start_index][i]) minCuts = min(minCuts, 1 + solve(i+1))
                if (isPalin[start_index][i]) {
                    minCuts = min(minCuts, 1 + dp[i + 1]);
                }
            }

            dp[start_index] = minCuts;
        }

        return dp[0];
    }
};


int main() {
    Solution1 recursion;
    Solution2 memo;
    Solution3 memoOptimized;
    Solution4 bottomUp;

    string s1 = "aab";
    cout << "Recursion:      " << recursion.minCut(s1) << endl;      // 1
    cout << "Memo:           " << memo.minCut(s1) << endl;           // 1
    cout << "Memo+PalinTable:" << memoOptimized.minCut(s1) << endl;  // 1
    cout << "Bottom-Up:      " << bottomUp.minCut(s1) << endl;       // 1

    cout << endl;
    string s2 = "aabaa";
    cout << "Recursion:      " << recursion.minCut(s2) << endl;      // 0 (already palindrome)
    cout << "Bottom-Up:      " << bottomUp.minCut(s2) << endl;       // 0

    return 0;
}
