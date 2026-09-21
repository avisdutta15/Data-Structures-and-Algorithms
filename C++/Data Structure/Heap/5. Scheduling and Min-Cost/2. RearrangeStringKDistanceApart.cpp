#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

/*
    https://www.youtube.com/watch?v=dENDy19_KSM
    Problem Statement:
    ------------------
    LeetCode 358 - Rearrange String k Distance Apart

    Given a string `s` and an integer `k`, rearrange the string such
    that the same characters are at least `k` distance apart.
    Return any valid rearrangement, or "" if not possible.

    This is the generalized version of LC 767 (Reorganize String),
    which is k = 2.

    Examples:
    ---------

    Example 1:
        Input:  s = "aabbcc", k = 3
        Output: "abcabc"

    Example 2:
        Input:  s = "aaabc", k = 3
        Output: ""
        Explanation: 'a' appears 3 times. With 5 chars and k=3,
                     'a' can fill positions 0 and 3 (2 slots).
                     But 'a' needs 3 slots. Impossible.

    Example 3:
        Input:  s = "aaadbbcc", k = 2
        Output: "abacabcd" (or other valid arrangements)

    Constraints:
    ------------
    - 1 <= s.length <= 3 * 10^5
    - s consists of lowercase English letters.
    - 0 <= k <= s.length

    Approach: Max-Heap + Cooldown Queue
    ------------------------------------

    Greedy: at each position, place the character with the highest
    remaining frequency. After placing it, put it in a cooldown queue
    for k rounds before it can be used again.

    Why the cooldown queue holds k entries (including freq 0):
    -----------------------------------------------------------
    The cooldown queue is a TIMER, not a storage for useful characters.
    It acts like a conveyor belt of width k:

        [ placed 1 round ago | placed 2 rounds ago | ... | placed k rounds ago ]

    A character enters at the back and exits at the front after exactly
    k rounds. This guarantees k positions between consecutive uses of
    the same character.

    Why hold entries with freq 0? Because the queue is a SPACER.
    Even a "dead" entry (freq 0) occupies a slot in the queue, keeping
    other characters from exiting too early. If we skipped freq-0
    entries, the queue would shrink below k, and characters would be
    released too soon — breaking the k-distance guarantee.

    Think of it like a waiting room with exactly k chairs. Every round,
    one person sits down (enters) and one person stands up (exits).
    Even if the person standing up has nothing left to do (freq 0),
    they still occupied the chair for k rounds. That's what enforces
    the spacing.

    When cooldown.size() < k (early rounds), nobody exits yet — we're
    still filling up the waiting room. Once it reaches k, one in, one
    out — steady state.

    Algorithm:
    ----------
    1. Build frequency map. Push all (freq, char) into max-heap.
    2. While heap is not empty:
        a. Pop most frequent (freq, ch). Place ch. Decrease freq.
        b. Push (ch, freq-1) into cooldown queue (even if freq-1 == 0).
        c. If cooldown.size() >= k: release the front.
           If released entry has freq > 0, push it back to heap.
    3. If result.size() == s.size() → valid. Otherwise → impossible.

    Detailed Dry Run (s = "aabbccd", k = 3):
    ------------------------------------------

    Frequencies: a:2, b:2, c:2, d:1
    Heap: [(2,c), (2,b), (2,a), (1,d)]
    Cooldown: []   Result: ""

    Pos 0:
        Pop (2,c). result="c". Cooldown.push(c,1).
        Cooldown size(1) < 3 → don't release.
        Heap: [(2,b),(2,a),(1,d)]   Cooldown: [(c,1)]

    Pos 1:
        Pop (2,b). result="cb". Cooldown.push(b,1).
        Cooldown size(2) < 3 → don't release.
        Heap: [(2,a),(1,d)]   Cooldown: [(c,1),(b,1)]

    Pos 2:
        Pop (2,a). result="cba". Cooldown.push(a,1).
        Cooldown size(3) >= 3 → RELEASE (c,1). freq>0 → push to heap.
            Why release 'c' now? Because 'c' was placed at position 0
            and has been in cooldown for 3 rounds (positions 0, 1, 2).
            If 'c' is placed again now, the earliest is position 3 —
            gap from position 0 = 3 = k. Safe to reuse.
        Heap: [(1,d),(1,c)]   Cooldown: [(b,1),(a,1)]

    Pos 3:
        Pop (1,d). result="cbad". Cooldown.push(d,0).  ← freq 0, still enters!
        Cooldown size(3) >= 3 → RELEASE (b,1). freq>0 → push to heap.
            Why release 'b' now? 'b' was placed at position 1, has
            waited 3 rounds (positions 1, 2, 3). Next placement would
            be position 4+ → gap from 1 = 3+ >= k. Safe.
        Heap: [(1,c),(1,b)]   Cooldown: [(a,1),(d,0)]

    Pos 4:
        Pop (1,c). result="cbadc". Cooldown.push(c,0).
        Cooldown size(3) >= 3 → RELEASE (a,1). freq>0 → push to heap.
        Heap: [(1,b),(1,a)]   Cooldown: [(d,0),(c,0)]

    Pos 5:
        Pop (1,b). result="cbadcb". Cooldown.push(b,0).
        Cooldown size(3) >= 3 → RELEASE (d,0). freq 0 → discard.
        Heap: [(1,a)]   Cooldown: [(c,0),(b,0)]

    Pos 6:
        Pop (1,a). result="cbadcba". Cooldown.push(a,0).
        Cooldown size(3) >= 3 → RELEASE (c,0). freq 0 → discard.
        Heap: []   Cooldown: [(b,0),(a,0)]

    Heap empty. result.size(7) == s.size(7) → return "cbadcba" ✓

    Verify k=3 distance:
        c at 0, 4 → gap = 4 >= 3 ✓
        b at 1, 5 → gap = 4 >= 3 ✓
        a at 2, 6 → gap = 4 >= 3 ✓
        d at 3    → once         ✓

    Why the cooldown queue size is k (not k-1):
    ---------------------------------------------
    The character placed at position i enters cooldown at position i.
    It should NOT be available until position i+k. The queue holds k
    entries, so it exits after k rounds — at position i+k. If the
    queue held k-1 entries, it would exit at i+k-1 (one too early).

        Queue size k:   enter at pos 0, exit at pos k   → gap = k ✓
        Queue size k-1: enter at pos 0, exit at pos k-1 → gap = k-1 ✗

    Complexity Analysis:
    --------------------
    Time:  O(n log A) — n characters, heap has at most A entries
                         (A = 26 for lowercase). Effectively O(n).
    Space: O(A + k) — heap (26) + cooldown queue (up to k entries).

*/

class Solution {
public:
    string rearrangeString(string s, int k) {
        // Edge case: k <= 1 means no spacing needed
        if (k <= 1) return s;

        // Step 1: Build frequency map
        unordered_map<char, int> freqMap;
        for (char c : s) freqMap[c]++;

        // Step 2: Max-heap of {freq, char} — most frequent first
        priority_queue<pair<int, char>> pq;
        for (auto& [ch, freq] : freqMap) {
            pq.push({ freq, ch });
        }

        // Cooldown queue: {char, remaining freq}
        // Acts as a timer — entries stay for exactly k rounds.
        // Even freq-0 entries stay to maintain the k-width spacing.
        queue<pair<char, int>> cooldownQueue;

        string result = "";

        while (!pq.empty()) {
            // Pop the most frequent available character
            auto [freq, ch] = pq.top();
            pq.pop();

            // Place it in the result
            result += ch;

            // Enter cooldown with decreased frequency
            // (even if freq-1 == 0, it must occupy a slot)
            cooldownQueue.push({ ch, freq - 1 });

            // If cooldown queue has k entries, release the oldest one.
            // This character has waited k rounds — safe to reuse.
            if (cooldownQueue.size() >= k) {
                auto [releasedCh, releasedFreq] = cooldownQueue.front();
                cooldownQueue.pop();
                // Only push back to heap if it still has remaining uses
                if (releasedFreq > 0)
                    pq.push({ releasedFreq, releasedCh });
            }
        }

        // If we placed all characters, it's valid.
        // If heap ran out early (cooldown blocked all chars), it's impossible.
        return result.length() == s.length() ? result : "";
    }
};

int main() {
    Solution obj;

    // Example 1: k = 3
    string r1 = obj.rearrangeString("aabbcc", 3);
    cout << "\"aabbcc\", k=3 → \"" << r1 << "\"" << endl;
    // Expected: valid arrangement like "abcabc"

    // Example 2: impossible
    string r2 = obj.rearrangeString("aaabc", 3);
    cout << "\"aaabc\", k=3 → \"" << (r2.empty() ? "(impossible)" : r2) << "\"" << endl;
    // Expected: impossible

    // Example 3: with odd char out
    string r3 = obj.rearrangeString("aabbccd", 3);
    cout << "\"aabbccd\", k=3 → \"" << r3 << "\"" << endl;
    // Expected: valid like "cbadcba"

    // Example 4: k = 1 (no spacing needed)
    string r4 = obj.rearrangeString("aabbcc", 1);
    cout << "\"aabbcc\", k=1 → \"" << r4 << "\"" << endl;
    // Expected: "aabbcc" (unchanged)

    // Example 5: k = 2 (same as Reorganize String)
    string r5 = obj.rearrangeString("aab", 2);
    cout << "\"aab\", k=2 → \"" << r5 << "\"" << endl;
    // Expected: "aba"

    return 0;
}
