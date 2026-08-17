#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>

using namespace std;

/*
    Problem Statement: (LeetCode 131 - Palindrome Partitioning)
    ------------------
    Given a string s, partition s such that every substring of the partition
    is a palindrome. Return ALL possible palindrome partitionings of s.

    Examples:
    --------
    Input: s = "aab"
    Output: [["a","a","b"],["aa","b"]]

    Input: s = "a"
    Output: [["a"]]

    Constraints:
    ------------
    - 1 <= s.length <= 16

    Approach:
    ---------
    Same String Partition pattern:
    - Word Break I:   can we partition? (bool)
    - Word Break II:  return ALL valid partitions (sentences)
    - Palindrome II:  min cuts for palindrome partition
    - Palindrome I:   return ALL palindrome partitions ← THIS

    This is the "print all" variant — like Word Break II but with palindrome check.

    Recurrence:
        solve(start_index, currentPartition):
            if start_index == n:
                result.add(currentPartition)    // found one valid partitioning
                return

            for i = start_index to n-1:
                if isPalindrome(s[start_index..i]):
                    currentPartition.add(s[start_index..i])
                    solve(i + 1, currentPartition)
                    currentPartition.removeLast()    // backtrack

        Answer: solve(0, [])

    No memoization/bottom-up needed for "print all" — we must enumerate
    all valid partitions anyway. Backtracking is the natural approach.

    Time: O(2^n * n) — up to 2^(n-1) ways to partition, each palindrome check O(n).

    For a string of length n, there are n-1 positions where we can place a cut 
    (between each pair of adjacent characters).
      s = "a | a | b"
             ↑   ↑
           cut1  cut2

        Each cut position: either cut or don't cut → 2^(n-1) possible partitions.

    Per partition cost:
        1. Building each partition's strings via substr: O(n) total characters
        2. Palindrome check (Solution 1): O(n) per check, up to n checks per path = O(n²)
        3. With precomputed table (Solution 2): O(1) per check, but still O(n) for substr
    
    Total:
        Number of valid partitions: up to O(2^(n-1)) = O(2^n)
        Work per partition: O(n) for building the strings
    Total: O(n * 2^n)

    Space: O(n) recursion stack + O(2^n) results.
*/

// ============================================================================
// Solution 1: Backtracking
// Time: O(2^n * n), Space: O(n) + results
// ============================================================================
class Solution1 {
private:
    void solve(string& s, int start_index, vector<string>& currentPartition,
               vector<vector<string>>& result) {
        // Reached end — all parts are palindromes, record this partition
        if (start_index == s.size()) {
            result.push_back(currentPartition);
            return;
        }

        // Try every possible palindrome prefix starting at start_index
        for (int i = start_index; i < (int)s.size(); i++) {
            // Check if s[start_index..i] is palindrome
            if (isPalin(s, start_index, i)) {
                // Choose: add this palindrome to current partition
                currentPartition.push_back(s.substr(start_index, i - start_index + 1));

                // Explore: recurse on remaining suffix
                solve(s, i + 1, currentPartition, result);

                // Unchoose: backtrack
                currentPartition.pop_back();
            }
        }
    }

    bool isPalin(string& s, int l, int r) {
        while (l < r) {
            if (s[l] != s[r]) return false;
            l++; r--;
        }
        return true;
    }

public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> result;
        vector<string> currentPartition;
        solve(s, 0, currentPartition, result);
        return result;
    }
};

// ============================================================================
// Solution 2: Backtracking + Precomputed Palindrome Table
// Time: O(2^n * n), Space: O(n²) for palindrome table + results
// ============================================================================
// Same backtracking, but isPalin check is O(1) instead of O(n).
class Solution2 {
private:
    void solve(string& s, int start_index, vector<string>& currentPartition,
               vector<vector<string>>& allPartitions, vector<vector<bool>>& isPalin) {

        // reached end. push the current partition to result
        if (start_index == s.size()) {
            allPartitions.push_back(currentPartition);
            return;
        }

        // try all possible partitions starting at start_index
        for (int i = start_index; i < (int)s.size(); i++) {
            if (isPalin[start_index][i]) {
                currentPartition.push_back(s.substr(start_index, i - start_index + 1));
                solve(s, i + 1, currentPartition, allPartitions, isPalin);
                currentPartition.pop_back();    // backtrack
            }
        }
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
                    if (len == 2)
                        table[i][j] = true;
                    else
                        table[i][j] = table[i + 1][j - 1];
                }
            }
        }

        return table;
    }

public:
    vector<vector<string>> partition(string s) {
        int n = s.size();

        // Precompute palindrome table
        vector<vector<bool>> isPalin = buildPalinTable(s);

        vector<vector<string>> allPartitions;
        vector<string> currentPartition;
        solve(s, 0, currentPartition, allPartitions, isPalin);
        return allPartitions;
    }
};


int main() {
    Solution1 backtrack;
    Solution2 optimized;

    string s1 = "aab";

    cout << "Backtracking:" << endl;
    auto res1 = backtrack.partition(s1);
    for (auto& partition : res1) {
        cout << "  [";
        for (int i = 0; i < partition.size(); i++) {
            cout << "\"" << partition[i] << "\"";
            if (i < partition.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }

    cout << "Optimized:" << endl;
    auto res2 = optimized.partition(s1);
    for (auto& partition : res2) {
        cout << "  [";
        for (int i = 0; i < partition.size(); i++) {
            cout << "\"" << partition[i] << "\"";
            if (i < partition.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }

    return 0;
}
