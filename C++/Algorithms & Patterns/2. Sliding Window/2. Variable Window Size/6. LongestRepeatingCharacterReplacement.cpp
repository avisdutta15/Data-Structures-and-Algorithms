#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// ──────────────────────────────────────────────────────────────────────────────
// Problem: Longest Repeating Character Replacement (LeetCode 424)
// ──────────────────────────────────────────────────────────────────────────────

/*
    Problem Statement:
    ------------------
    You are given a string s and an integer k. You can choose any character of
    the string and change it to any other uppercase English character. You can
    perform this operation at most k times.

    Return the length of the longest substring containing the same letter after
    performing the above operations.

    Examples:
    ---------
    Input:  s = "ABAB", k = 2
    Output: 4
    Explanation: Replace the two 'A's with 'B's (or vice versa) → "BBBB" or "AAAA".

    Input:  s = "AABABBA", k = 1
    Output: 4
    Explanation: Replace the 'B' at index 3 → "AAAAABA". Longest = 4 ("AAAA").
                 Or: "AABBBBA" → longest = 4 ("BBBB"). Either way, answer = 4.

    Constraints:
    ------------
    - 1 <= s.length <= 10^5
    - s consists of only uppercase English letters.
    - 0 <= k <= s.length

    Approach:
    ---------
    Variable Sliding Window — Find LONGEST valid window.

    Key Insight:
    For a window to become all one character, we need to REPLACE all characters
    that are NOT the most frequent character in that window.

    Number of replacements needed = window_size - count_of_most_frequent_char

    Window is VALID when:
        (right - left + 1) - maxFreq <= k

    Where maxFreq = frequency of the most common character in the current window.

    Window is INVALID when:
        (right - left + 1) - maxFreq > k
        (we need more than k replacements)

    Template:
        Expand right, update freq and maxFreq.
        While invalid: shrink from left.
        Update answer.

    Important subtlety about maxFreq:
    ─────────────────────────────────
    When we shrink the window, do we need to DECREASE maxFreq?

    NO! Here's why:
    - maxFreq only needs to increase to find a LONGER valid window.
    - If maxFreq stays the same (or is stale/too high), the window just won't
      grow — the condition (windowSize - maxFreq > k) will force more shrinking.
    - We only care about the MAXIMUM window ever seen. A stale maxFreq that's
      too high might keep the window the same size, but it can never produce a
      WRONG answer — it just means the window doesn't grow until a genuinely
      higher maxFreq is found.
    - This is why we never decrease maxFreq, making it O(1) per step.

    Worked Example:
    ---------------
    s = "AABABBA", k = 1

    freq = {}, maxFreq = 0

    left=0, right=0: 'A'. freq={A:1}. maxFreq=1. windowSize=1.
                     replacements = 1-1 = 0 <= 1 ✓. result=1.
    left=0, right=1: 'A'. freq={A:2}. maxFreq=2. windowSize=2.
                     replacements = 2-2 = 0 <= 1 ✓. result=2.
    left=0, right=2: 'B'. freq={A:2, B:1}. maxFreq=2. windowSize=3.
                     replacements = 3-2 = 1 <= 1 ✓. result=3.
    left=0, right=3: 'A'. freq={A:3, B:1}. maxFreq=3. windowSize=4.
                     replacements = 4-3 = 1 <= 1 ✓. result=4.
    left=0, right=4: 'B'. freq={A:3, B:2}. maxFreq=3. windowSize=5.
                     replacements = 5-3 = 2 > 1 ✗. INVALID!
                     shrink: freq[A]--, freq={A:2, B:2}. left=1. windowSize=4.
                     replacements = 4-3 = 1 <= 1 ✓. (maxFreq stays 3 — stale but fine)
                     result=max(4, 4)=4.
    left=1, right=5: 'B'. freq={A:2, B:3}. maxFreq=3. windowSize=5.
                     replacements = 5-3 = 2 > 1 ✗. INVALID!
                     shrink: freq[A]--, freq={A:1, B:3}. left=2. windowSize=4.
                     replacements = 4-3 = 1 <= 1 ✓.
                     result=max(4, 4)=4.
    left=2, right=6: 'A'. freq={A:2, B:3}. maxFreq=3. windowSize=5.
                     replacements = 5-3 = 2 > 1 ✗. INVALID!
                     shrink: freq[B]--, freq={A:2, B:2}. left=3. windowSize=4.
                     replacements = 4-3 = 1 <= 1 ✓.
                     result=max(4, 4)=4.

    Result: 4 ✓

    Time Complexity: O(N) — single pass, no inner loop over alphabet
    Space Complexity: O(26) = O(1) — frequency array of 26 chars
*/

// ── Naive Approach: O(N^2) ──
// For each starting index i, expand right as far as possible while
// (windowSize - maxFreqInWindow) <= k. Track maxFreq by scanning freq array.
class SolutionNaive {
public:
    int characterReplacement(string s, int k) {
        int n = s.size();
        int result = 0;

        // Try every possible starting position
        for (int start = 0; start < n; start++) {
            vector<int> freq(26, 0);  // frequency of each char in window [i..j]
            int maxFreq = 0;          // most frequent char count in window [i..j]

            // Expand window from i to j
            for (int end = start; end < n; end++) {
                freq[s[end] - 'A']++;   // include s[j] in the window
                maxFreq = max(maxFreq, freq[s[end] - 'A']);  // update max frequency

                int windowSize = end - start + 1;
                int replacementsNeeded = windowSize - maxFreq;  // chars that need to change

                if (replacementsNeeded <= k) {
                    // Window is valid: we can make all chars the same with <= k replacements
                    result = max(result, windowSize);
                } else {
                    // Can't extend further from this start — adding more chars won't help
                    // because replacementsNeeded only increases as window grows
                    break;
                }
            }
        }

        return result;
    }
};

// ── Optimized: Sliding Window O(N) ──
class Solution {
public:
    int characterReplacement(string s, int k) {
        int n = s.size();
        int left = 0, right = 0;
        int result = 0;
        int maxFreq = 0;  // max frequency of any single char in current window
        vector<int> freq(26, 0);

        while (right < n) {
            // 1. EXPAND: add s[right] to window
            freq[s[right] - 'A']++;
            maxFreq = max(maxFreq, freq[s[right] - 'A']);

            // 2. SHRINK: while window is INVALID (need more than k replacements)
            // replacements needed = windowSize - maxFreq
            while ((right - left + 1) - maxFreq > k) {
                freq[s[left] - 'A']--;
                left++;
                // Note: we do NOT decrease maxFreq here (see explanation above)
            }

            // 3. UPDATE: window is valid
            result = max(result, right - left + 1);

            right++;
        }

        return result;
    }
};

int main()
{
    Solution obj;

    cout << "ABAB, k=2: " << obj.characterReplacement("ABAB", 2) << endl;       // 4
    cout << "AABABBA, k=1: " << obj.characterReplacement("AABABBA", 1) << endl;  // 4

    return 0;
}
