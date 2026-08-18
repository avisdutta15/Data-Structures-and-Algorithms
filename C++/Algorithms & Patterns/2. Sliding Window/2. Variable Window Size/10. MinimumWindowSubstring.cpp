#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// ──────────────────────────────────────────────────────────────────────────────
// Problem: Minimum Window Substring (LeetCode 76)
// ──────────────────────────────────────────────────────────────────────────────

/*
    Problem Statement:
    ------------------
    Given two strings s and t of lengths m and n respectively, return the minimum
    window substring of s such that every character in t (including duplicates) is
    included in the window. If there is no such substring, return "".

    The answer is guaranteed to be unique.

    Examples:
    ---------
    Input:  s = "ADOBECODEBANC", t = "ABC"
    Output: "BANC"
    Explanation: The minimum window containing A, B, C is "BANC" (index 9..12).

    Input:  s = "a", t = "a"
    Output: "a"

    Input:  s = "a", t = "aa"
    Output: ""
    Explanation: Both 'a's from t must be in the window. s only has one 'a'.

    Constraints:
    ------------
    - m == s.length, n == t.length
    - 1 <= m, n <= 10^5
    - s and t consist of uppercase and lowercase English letters.

    Approach:
    ---------
    Variable Sliding Window — Find SHORTEST valid window.

    Window is VALID when: it contains ALL characters of t (with correct frequencies).

    Template (Shortest — shrink while VALID):
        Expand right, update window state.
        While window is VALID (contains all chars of t):
            Update answer (minimize length).
            Shrink from left.

    How to efficiently check "window contains all chars of t":
    ──────────────────────────────────────────────────────────
    Naive: compare two frequency maps each time → O(26) or O(52) per step.

    Optimized: maintain a counter `formed` that tracks how many UNIQUE characters
    in t have their required frequency met in the current window.

    - tFreq[c] = how many times c appears in t.
    - windowFreq[c] = how many times c appears in current window.
    - `required` = number of unique chars in t.
    - `formed` = number of unique chars where windowFreq[c] >= tFreq[c].

    Window is valid when: formed == required.

    On expand (add s[right]):
        windowFreq[s[right]]++.
        If windowFreq[s[right]] == tFreq[s[right]]: formed++.

    On shrink (remove s[left]):
        If windowFreq[s[left]] == tFreq[s[left]]: formed--.
        windowFreq[s[left]]--.

    Worked Example:
    ---------------
    s = "ADOBECODEBANC", t = "ABC"
    tFreq = {A:1, B:1, C:1}, required = 3

    Expanding until valid:
    right=0 'A': windowFreq={A:1}. A meets req (1>=1). formed=1.
    right=1 'D': windowFreq={A:1,D:1}. formed=1.
    right=2 'O': formed=1.
    right=3 'B': windowFreq={..,B:1}. B meets req. formed=2.
    right=4 'E': formed=2.
    right=5 'C': windowFreq={..,C:1}. C meets req. formed=3 == required! VALID!
                 Window = "ADOBEC" (length 6). Update result.
                 Shrink: remove 'A'. windowFreq[A]=0 < tFreq[A]=1. formed=2. left=1.
                 formed < required → stop shrinking.

    Continue expanding:
    right=6 'O': formed=2.
    right=7 'D': formed=2.
    right=8 'E': formed=2.
    right=9 'B': windowFreq[B]=2. formed=2 (B was already met).
    right=10 'A': windowFreq[A]=1. A meets req again. formed=3! VALID!
                  Window = "DOBECODEBA" [1..10] (length 10). Not better.
                  Shrink: remove 'D' at left=1. formed still 3. left=2.
                  Window = "OBECODEBA" [2..10] (length 9). Not better.
                  Shrink: remove 'O' at left=2. formed still 3. left=3.
                  Window = "BECODEBA" [3..10] (length 8). Not better.
                  Shrink: remove 'B' at left=3. windowFreq[B]=1 >= tFreq[B]=1. Still formed=3. left=4.
                  Window = "ECODEBA" [4..10] (length 7). Not better.
                  Shrink: remove 'E' at left=4. formed still 3. left=5.
                  Window = "CODEBA" [5..10] (length 6). Same as best. Update (or not, same length).
                  Shrink: remove 'C' at left=5. windowFreq[C]=0 < 1. formed=2. left=6.
                  Stop.

    right=11 'N': formed=2.
    right=12 'C': windowFreq[C]=1. C meets req. formed=3! VALID!
                  Window = "ODEBANC" [6..12] (length 7). Not better.
                  Shrink: remove 'O'. formed=3. left=7.
                  Window = "DEBANC" [7..12] (length 6). Same as best.
                  Shrink: remove 'D'. formed=3. left=8.
                  Window = "EBANC" [8..12] (length 5). Better! Update.
                  Shrink: remove 'E'. formed=3. left=9.
                  Window = "BANC" [9..12] (length 4). Better! Update. result = "BANC".
                  Shrink: remove 'B'. windowFreq[B]=0 < 1. formed=2. left=10.
                  Stop.

    Done. Result = "BANC" ✓

    Time Complexity: O(|s| + |t|) — each char in s is visited at most twice (once by right, once by left)
    Space Complexity: O(|s| + |t|) for the frequency maps (practically O(52) = O(1))
*/

// ── Naive Approach: Frequency map comparison at every window ──
// Instead of the 'formed' counter, we compare the full frequency maps to check validity.
// Time: O(|s| * 52) — 52 for comparing freq maps (uppercase + lowercase)
// Still O(|s|) asymptotically but with a larger constant factor.
class SolutionNaive {
private:
    // Check if window contains all characters of t with sufficient frequency
    // For every char in tFreq, windowFreq must have at least that many
    bool isValid(unordered_map<char, int>& windowFreq, unordered_map<char, int>& tFreq) {
        for (auto& [c, count] : tFreq) {
            if (windowFreq[c] < count)
                return false;
        }
        return true;
    }
public:
    string minWindow(string s, string t) {
        if (t.size() > s.size()) return "";

        // Build frequency map for t
        unordered_map<char, int> tFreq;
        for (char c : t)
            tFreq[c]++;

        unordered_map<char, int> windowFreq;  // frequency of chars in current window

        int left = 0, right = 0;
        int minLen = INT_MAX;
        int minStart = 0;

        while (right < (int)s.size()) {
            // 1. EXPAND: add s[right] to window
            windowFreq[s[right]]++;

            // 2. SHRINK: while window is VALID (check by comparing freq maps)
            while (isValid(windowFreq, tFreq)) {
                // Update answer
                int windowLen = right - left + 1;
                if (windowLen < minLen) {
                    minLen = windowLen;
                    minStart = left;
                }

                // Remove s[left] from window
                windowFreq[s[left]]--;
                if (windowFreq[s[left]] == 0)
                    windowFreq.erase(s[left]);
                left++;
            }

            right++;
        }

        return (minLen == INT_MAX) ? "" : s.substr(minStart, minLen);
    }
};

// Time Complexity: O(|s| + |t|) — each char in s is visited at most twice (once by right, once by left)
// Space Complexity: O(|s| + |t|) for the frequency maps (practically O(52) = O(1))
class Solution {
public:
    string minWindow(string s, string t) {
        if (t.size() > s.size()) return "";

        // Build frequency map for t
        unordered_map<char, int> tFreq;
        for (char c : t)
            tFreq[c]++;

        int required = tFreq.size();  // number of unique chars in t that must be satisfied
        int formed = 0;               // how many unique chars currently meet the requirement

        unordered_map<char, int> windowFreq;  // frequency of chars in current window

        int left = 0, right = 0;
        int minLen = INT_MAX;
        int minStart = 0;  // start index of the best window

        while (right < (int)s.size()) {
            // 1. EXPAND: add s[right] to window
            char c = s[right];
            windowFreq[c]++;

            // If this char is in t and we've just met the required count
            if (tFreq.count(c) && windowFreq[c] == tFreq[c]) {
                formed++;
            }

            // 2. SHRINK: while window is VALID (all chars of t are covered)
            while (formed == required) {
                // Update answer (minimize window length)
                int windowLen = right - left + 1;
                if (windowLen < minLen) {
                    minLen = windowLen;
                    minStart = left;
                }

                // Remove s[left] from window
                char leftChar = s[left];
                windowFreq[leftChar]--;

                // If removing this char breaks the requirement
                if (tFreq.count(leftChar) && windowFreq[leftChar] < tFreq[leftChar]) {
                    formed--;
                }

                left++;
            }

            right++;
        }

        return (minLen == INT_MAX) ? "" : s.substr(minStart, minLen);
    }
};


int main()
{
    Solution sol;
    SolutionNaive naive;

    cout << "Optimized (formed counter):" << endl;
    cout << "  \"ADOBECODEBANC\", \"ABC\" → \"" << sol.minWindow("ADOBECODEBANC", "ABC") << "\"" << endl;
    cout << "  \"a\", \"a\" → \"" << sol.minWindow("a", "a") << "\"" << endl;
    cout << "  \"a\", \"aa\" → \"" << sol.minWindow("a", "aa") << "\"" << endl;

    cout << "\nNaive (freq map comparison):" << endl;
    cout << "  \"ADOBECODEBANC\", \"ABC\" → \"" << naive.minWindow("ADOBECODEBANC", "ABC") << "\"" << endl;
    cout << "  \"a\", \"a\" → \"" << naive.minWindow("a", "a") << "\"" << endl;
    cout << "  \"a\", \"aa\" → \"" << naive.minWindow("a", "aa") << "\"" << endl;

    return 0;
}
