#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
    Problem Statement:
    ------------------
    Given a string s, find the length of the LONGEST substring without
    repeating characters.

    Examples:
    ---------
    Input:  s = "abcabcbb"
    Output: 3
    Explanation: "abc" is the longest substring without repeating chars.

    Input:  s = "bbbbb"
    Output: 1

    Input:  s = "pwwkew"
    Output: 3
    Explanation: "wke" is the answer.

    Constraints:
    ------------
    - 0 <= s.length <= 5 * 10^4
    - s consists of English letters, digits, symbols, and spaces.

    Approach:
    ---------
    Variable Sliding Window — Find LONGEST valid window.

    Window condition: no repeating characters (all unique).
    Invalid when: a character appears more than once in the window.

    Template (Longest — shrink while INVALID):
        while (right < n) {
            // expand: add s[right] to window
            // while window is INVALID (has duplicate):
            //     shrink from left
            // update answer (maximize length)
            // right++
        }

    How to track duplicates:
    - Option A: HashSet — add char on expand, remove on shrink. Invalid if char already in set.
    - Option B: HashMap (char → count) — invalid if any count > 1.
    - Option C: HashMap (char → last index) — jump left directly to skip over the duplicate.

    Option A (HashSet — clearest for understanding):
    ─────────────────────────────────────────────────
    - Expand: try to insert s[right].
    - If s[right] already in set → window is invalid → shrink (remove s[left], left++).
    - Keep shrinking until s[right] is no longer in set.
    - Then insert s[right], update answer.

    Option C (HashMap with last index — most efficient):
    ────────────────────────────────────────────────────
    - Store the last seen index of each character.
    - When s[right] was seen at index `lastIdx`, and lastIdx >= left:
      → jump left to lastIdx + 1 (skip all chars up to and including the duplicate).
    - No inner while loop needed — O(1) shrink per step.

    Worked Example (Option A):
    --------------------------
    s = "abcabcbb"

    left=0, right=0: 'a' not in set. set={a}. result=max(0,1)=1. right++.
    left=0, right=1: 'b' not in set. set={a,b}. result=max(1,2)=2. right++.
    left=0, right=2: 'c' not in set. set={a,b,c}. result=max(2,3)=3. right++.
    left=0, right=3: 'a' IN set! shrink: remove 'a', left=1. set={b,c}.
                     'a' not in set now. set={b,c,a}. result=max(3,3)=3. right++.
    left=1, right=4: 'b' IN set! shrink: remove 'b', left=2. set={c,a}.
                     'b' not in set now. set={c,a,b}. result=max(3,3)=3. right++.
    left=2, right=5: 'c' IN set! shrink: remove 'c', left=3. set={a,b}.
                     'c' not in set now. set={a,b,c}. result=max(3,3)=3. right++.
    left=3, right=6: 'b' IN set! shrink: remove 'a', left=4. set={b,c}.
                     'b' still IN set! shrink: remove 'b', left=5. set={c}.
                     'b' not in set now. set={c,b}. result=max(3,2)=3. right++.
    left=5, right=7: 'b' IN set! shrink: remove 'c', left=6. set={b}.
                     'b' still IN set! shrink: remove 'b', left=7. set={}.
                     'b' not in set now. set={b}. result=max(3,1)=3. right++.
    right=8: out of bounds, done.

    Result: 3 ✓

    Time Complexity: O(N) — left and right each move forward at most N times
    Space Complexity: O(min(N, alphabet_size)) for the set/map
*/

// ── Solution 1: HashSet approach ──
class Solution1 {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int left = 0, right = 0;
        int maxWindowLength = 0;
        unordered_set<char> window;

        while (right < n) {
            char currentChar = s[right];

            // Shrink while window is INVALID (s[right] i.e. current char is a duplicate in the window)
            while (window.count(currentChar)) {
                window.erase(s[left]);
                left++;
            }

            // Expand: add s[right] to window
            window.insert(currentChar);

            // Update answer (window is valid now)
            maxWindowLength = max(maxWindowLength, right - left + 1);

            right++;
        }

        return maxWindowLength;
    }
};

// ── Solution 2: HashMap (char → last index) — no inner loop ──
class Solution2 {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int left = 0;
        int result = 0;
        unordered_map<char, int> lastSeen;  // char → last index where it appeared

        for (int right = 0; right < n; right++) {

            char currentChar = s[right];

            // If s[right] was seen before AND its last position is within current window
            if (lastSeen.count(currentChar) > 0  && lastSeen[currentChar] >= left) {
                // Jump left past the previous occurrence
                left = lastSeen[currentChar] + 1;
            }

            // Update last seen index
            lastSeen[currentChar] = right;

            // Update answer
            result = max(result, right - left + 1);
        }

        return result;
    }
};

int main()
{
    Solution1 sol1;
    Solution2 sol2;

    cout << "HashSet approach:" << endl;
    cout << "  \"abcabcbb\" → " << sol1.lengthOfLongestSubstring("abcabcbb") << endl;  // 3
    cout << "  \"bbbbb\" → " << sol1.lengthOfLongestSubstring("bbbbb") << endl;        // 1
    cout << "  \"pwwkew\" → " << sol1.lengthOfLongestSubstring("pwwkew") << endl;      // 3

    cout << "\nHashMap (last index) approach:" << endl;
    cout << "  \"abcabcbb\" → " << sol2.lengthOfLongestSubstring("abcabcbb") << endl;  // 3
    cout << "  \"bbbbb\" → " << sol2.lengthOfLongestSubstring("bbbbb") << endl;        // 1
    cout << "  \"pwwkew\" → " << sol2.lengthOfLongestSubstring("pwwkew") << endl;      // 3

    return 0;
}
