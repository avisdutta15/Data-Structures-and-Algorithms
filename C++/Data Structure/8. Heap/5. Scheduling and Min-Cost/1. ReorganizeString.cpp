#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
#include <unordered_map>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 767 - Reorganize String

    Given a string `s`, rearrange the characters so that no two adjacent
    characters are the same. Return any valid rearrangement, or "" if
    it's not possible.

    This is the special case of "Rearrange String K Distance Apart"
    (LC 358) with k = 2.

    Examples:
    ---------

    Example 1:
        Input:  s = "aab"
        Output: "aba"

    Example 2:
        Input:  s = "aaab"
        Output: ""
        Explanation: No way to arrange — 'a' appears 3 times, but
                     with 4 chars we can only have 2 non-adjacent slots
                     for the same char (positions 0, 2).

    Example 3:
        Input:  s = "aabbcc"
        Output: "abcabc" (or "abacbc", etc.)

    Constraints:
    ------------
    - 1 <= s.length <= 500
    - s consists of lowercase English letters.

    When is it impossible?
    -----------------------
    If any character's frequency > (n + 1) / 2, it's impossible.
    With n characters, the most frequent char can fill at most every
    other position: positions 0, 2, 4, ... = ceil(n/2) slots.

    Approach: Max-Heap — Pop Two at a Time
    ----------------------------------------
    Greedy: always pick the two most frequent characters and place
    them next to each other. This guarantees they're different.

    Why pop two at a time?
        If we pop one and place it, the next pop might give us the
        SAME character (if it's still the most frequent). Popping
        two guarantees two different characters side by side.

    Algorithm:
        1. Build frequency map. Push all (freq, char) into max-heap.
        2. While heap has >= 2 elements:
            a. Pop top two: (freq1, ch1) and (freq2, ch2).
            b. Append ch1 and ch2 to result.
            c. Decrease both frequencies. Push back if still > 0.
        3. If one character remains:
            - freq == 1 → append it (valid).
            - freq > 1  → impossible, return "".

    Dry Run (s = "aab"):
    ----------------------
    Freq: a:2, b:1.  Heap: [(2,a), (1,b)]

    Round 1: pop (2,a) and (1,b).
        result = "ab". Push (1,a) back.
        Heap: [(1,a)]

    One left: (1,a). freq == 1 → append.
        result = "aba" ✓

    Dry Run (s = "aaab"):
    ----------------------
    Freq: a:3, b:1.  Heap: [(3,a), (1,b)]

    Round 1: pop (3,a) and (1,b).
        result = "ab". Push (2,a) back.
        Heap: [(2,a)]

    One left: (2,a). freq > 1 → return "" ✓

    Complexity Analysis:
    --------------------
    Time:  O(n log A) — n characters, heap has at most A entries
                         (A = alphabet size, at most 26). Effectively O(n).
    Space: O(A) — frequency map + heap (at most 26 entries).

*/

class Solution {
public:
	string reorganizeString(string s) {
        int n = s.length();
		unordered_map<char, int> freq_map;

        for (char c : s) {
            freq_map[c]++;
            if(freq_map[c] > (n + 1) / 2)       // impossible to place
                return "";
        }

		priority_queue<pair<int, char>> pq;     //max-heap of {freq, char}

		for (auto& [ch, freq] : freq_map) {
			pq.push({ freq, ch });
		}

		string result = "";

		// while we can get 2 elements from heap
		while (pq.size() >= 2) {
			auto [freq1, ch1] = pq.top();   pq.pop();
			auto [freq2, ch2] = pq.top();   pq.pop();

			result += ch1;
			result += ch2;

			freq1--;    if (freq1 > 0)   pq.push({ freq1, ch1 });
			freq2--;    if (freq2 > 0)   pq.push({ freq2, ch2 });
		}

		// One character left — valid only if its frequency is 1
		if (!pq.empty()) {
			auto [freq1, ch1] = pq.top();   pq.pop();
			if (freq1 > 1) 
				return "";	// can't place 2+ of same char without adjacency
			else
				result += ch1;
		}
		return result;
	}
};

int main() {
    Solution obj;

    // Example 1: possible
    string s1 = "aab";
    string r1 = obj.reorganizeString(s1);
    cout << "\"aab\" → \"" << r1 << "\"" << endl;
    // Expected: "aba"

    // Example 2: impossible
    string s2 = "aaab";
    string r2 = obj.reorganizeString(s2);
    cout << "\"aaab\" → \"" << (r2.empty() ? "(impossible)" : r2) << "\"" << endl;
    // Expected: (impossible)

    // Example 3: multiple chars, same freq
    string s3 = "aabbcc";
    string r3 = obj.reorganizeString(s3);
    cout << "\"aabbcc\" → \"" << r3 << "\"" << endl;
    // Expected: some valid rearrangement like "abcabc"

    // Example 4: single char
    string s4 = "a";
    string r4 = obj.reorganizeString(s4);
    cout << "\"a\" → \"" << r4 << "\"" << endl;
    // Expected: "a"

    return 0;
}