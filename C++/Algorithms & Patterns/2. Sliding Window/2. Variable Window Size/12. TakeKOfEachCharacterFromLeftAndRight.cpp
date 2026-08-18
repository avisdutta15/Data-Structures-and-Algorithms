#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// ──────────────────────────────────────────────────────────────────────────────
// Problem: Take K of Each Character From Left and Right (LeetCode 2516)
// ──────────────────────────────────────────────────────────────────────────────

/*
    https://www.youtube.com/watch?v=s4nRUC1SDDA (Recursion Logic)
    Problem Statement:
    ------------------
    You are given a string s consisting of characters 'a', 'b', and 'c' and a
    non-negative integer k. Each minute, you may take either the leftmost or the
    rightmost character of s.

    Return the MINIMUM number of minutes to take at least k of each character,
    or return -1 if it is not possible.

    Examples:
    ---------
    Input:  s = "aabaaaacaabc", k = 2
    Output: 8

    Input:  s = "a", k = 1
    Output: -1
    Explanation: Not enough 'b' and 'c'.

    Constraints:
    ------------
    - 1 <= s.length <= 10^5
    - s consists of only 'a', 'b', 'c'
    - 0 <= k <= s.length

    ═══════════════════════════════════════════════════════════════════════
    Approach 1: Naive Recursive (Take left or Take right) — O(2^n) time
    ═══════════════════════════════════════════════════════════════════════

    Same pattern as LC 1658. At each step:
    - Take from left (i++)
    - Take from right (j--)

    Track how many a's, b's, c's we've taken so far.

    Base cases:
    - If countA >= k && countB >= k && countC >= k: satisfied! Update minCount.
    - If i > j or count >= minCount: prune, return.

    Recurrence:
        solve(s, i, j, count, countA, countB, countC):
            if all counts >= k → update minCount
            if i > j or count >= minCount → prune
            else:
                // Take left character s[i]
                solve(s, i+1, j, count+1, updated counts)
                // Take right character s[j]
                solve(s, i, j-1, count+1, updated counts)

    ═══════════════════════════════════════════════════════════════════════
    Approach 2: Reverse Thinking + Sliding Window — O(N) time
    ═══════════════════════════════════════════════════════════════════════

    Instead of minimizing what we take from left and right, MAXIMIZE what
    we KEEP in the middle.

    If we take some characters from left + right, the remaining characters
    form a contiguous middle subarray.

    Constraint on the middle window:
    - If middle contains midA copies of 'a', then left+right has (totalA - midA).
    - We need: totalA - midA >= k → midA <= totalA - k.
    - Same for 'b' and 'c'.

    So: find the LONGEST subarray (middle) where:
        count('a') <= totalA - k
        count('b') <= totalB - k
        count('c') <= totalC - k

    Answer = n - (longest valid middle length)

    Edge case: if totalA < k or totalB < k or totalC < k → return -1.

    Worked Example:
    ---------------
    s = "aabaaaacaabc", k = 2
    n = 12, totalA=8, totalB=2, totalC=2

    Allowed in middle: a <= 8-2=6, b <= 2-2=0, c <= 2-2=0
    Middle can have at most 6 a's, 0 b's, 0 c's.

    Longest subarray of only a's: "aaaa" (indices 3..6), length 4.
    Answer = 12 - 4 = 8 ✓

    Time Complexity: O(N)
    Space Complexity: O(1)
*/

// ── Approach 1: Naive Recursive ──
class SolutionNaive {
private:
    int minCount;

public:
    void solve(string& s, int i, int j, int count, int countA, int countB, int countC, int k) {
        // Base case: all requirements met
        if (countA >= k && countB >= k && countC >= k) {
            minCount = min(minCount, count);
            return;
        }

        // Prune: no more characters to take, or already worse than best
        if (i > j || count >= minCount)
            return;

        // Choice 1: Take from left
        int newA = countA + (s[i] == 'a');
        int newB = countB + (s[i] == 'b');
        int newC = countC + (s[i] == 'c');
        solve(s, i + 1, j, count + 1, newA, newB, newC, k);

        // Choice 2: Take from right
        newA = countA + (s[j] == 'a');
        newB = countB + (s[j] == 'b');
        newC = countC + (s[j] == 'c');
        solve(s, i, j - 1, count + 1, newA, newB, newC, k);
    }

    int takeCharacters(string s, int k) {
        if (k == 0) return 0;

        int n = s.size();
        minCount = INT_MAX;

        solve(s, 0, n - 1, 0, 0, 0, 0, k);

        return (minCount == INT_MAX) ? -1 : minCount;
    }
};

// ── Approach 2: Reverse Thinking + Sliding Window ──
class Solution {
public:
    int takeCharacters(string s, int k) {
        if (k == 0) return 0;

        int n = s.size();

        // Count total occurrences of each character
        int total[3] = {0, 0, 0};
        for (char c : s)
            total[c - 'a']++;

        // Check if it's even possible
        if (total[0] < k || total[1] < k || total[2] < k)
            return -1;

        // Maximum allowed count of each char in the middle window
        int maxAllowed[3] = {total[0] - k, total[1] - k, total[2] - k};

        // Find the LONGEST window where count of each char <= maxAllowed
        int left = 0, right = 0;
        int windowCount[3] = {0, 0, 0};
        int maxWindowLen = 0;

        while (right < n) {
            // 1. EXPAND: add s[right] to window
            windowCount[s[right] - 'a']++;

            // 2. SHRINK: while window is INVALID (any char exceeds allowed)
            while (windowCount[0] > maxAllowed[0] ||
                   windowCount[1] > maxAllowed[1] ||
                   windowCount[2] > maxAllowed[2]) {
                windowCount[s[left] - 'a']--;
                left++;
            }

            // 3. UPDATE: window is valid, maximize length
            maxWindowLen = max(maxWindowLen, right - left + 1);

            right++;
        }

        // Answer = total characters - longest valid middle
        return n - maxWindowLen;
    }
};

int main()
{
    Solution sol;
    SolutionNaive naive;

    string s1 = "aabaaaacaabc";
    cout << "Sliding Window: " << sol.takeCharacters(s1, 2) << endl;    // 8
    cout << "Naive:          " << naive.takeCharacters(s1, 2) << endl;  // 8

    string s2 = "a";
    cout << "Sliding Window: " << sol.takeCharacters(s2, 1) << endl;    // -1
    cout << "Naive:          " << naive.takeCharacters(s2, 1) << endl;  // -1

    string s3 = "abc";
    cout << "Sliding Window: " << sol.takeCharacters(s3, 1) << endl;    // 3
    cout << "Naive:          " << naive.takeCharacters(s3, 1) << endl;  // 3

    return 0;
}
