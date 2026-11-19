#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <numeric>
#include <algorithm>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
    In other words, return true if one of s1's permutations is the substring of s2.

	Examples:
	--------
	Example 1:
    Input: s1 = "ab", s2 = "eidbaooo"
    Output: true
    Explanation: s2 contains one permutation of s1 ("ba").

    Example 2:
    Input: s1 = "ab", s2 = "eidboaoo"
    Output: false


	Approach:
	---------
    Sliding Window

	Optimization : Sliding Window + matchCount Optimization (Similar to Find All Anagrams)
	IDEA:
        Instead of comparing all 26 entries every window, track how many of the 26 characters
        currently have equal frequency in sFreq and pFreq. When all 26 match, it's an anagram.
        This replaces the O(26) comparison with an O(1) check: matchCount == 26.

    TIME COMPLEXITY:  O(|s|) — Strictly O(1) work per window slide.
    SPACE COMPLEXITY: O(1) — Two fixed-size arrays of 26 elements + one integer.

    HOW matchCount WORKS:
        - matchCount = number of characters (out of 26) where sFreq[c] == pFreq[c].
        - Initialization: Before processing s, sFreq is all zeros. Any character with
          pFreq[c] == 0 already matches (0 == 0), so matchCount starts at the count of
          characters NOT in p. For example, if p = "ab", then 24 characters have pFreq = 0,
          so matchCount starts at 24. We need 2 more matches (a and b) to reach 26.

        - When a character ENTERS the window (sFreq[c]++ already done):
            sFreq[c] == pFreq[c]       →  This character just became a match.  matchCount++
            sFreq[c] == pFreq[c] + 1   →  This character just broke a match.   matchCount--
            Otherwise                   →  Was not matching before, still isn't. No change.

        - When a character LEAVES the window (sFreq[c]-- already done):
            sFreq[c] == pFreq[c]       →  This character just became a match.  matchCount++
            sFreq[c] == pFreq[c] - 1   →  This character just broke a match.   matchCount--
            Otherwise                   →  Was not matching before, still isn't. No change.

        - When matchCount == 26, every character has the same frequency in both vectors,
          meaning the current window is an anagram of p.

    EXAMPLE TRACE:
        s = "cbaebabacd",  p = "abc",  K = 3
        pFreq: a=1, b=1, c=1, rest=0
        matchCount starts at 23  (23 chars have pFreq=0, already matching sFreq=0)

        +------+--------+-----+--------+-----------+----+-----------------------+
        | Step | Window | Add | Remove | sFreq     | MC | Result                |
        |      |        |     |        | (a, b, c) |    |                       |
        +------+--------+-----+--------+-----------+----+-----------------------+
        |  1   | c      |  c  |   —    | (0, 0, 1) | 24 | window < K            |
        |  2   | cb     |  b  |   —    | (0, 1, 1) | 25 | window < K            |
        |  3   | cba    |  a  |   c    | (1, 1, 0) | 25 | ✅ MC=26 → idx 0      |
        |  4   | bae    |  e  |   b    | (1, 0, 0) | 23 | ❌ MC=23              |
        |  5   | aeb    |  b  |   a    | (0, 1, 0) | 23 | ❌ MC=23              |
        |  6   | eba    |  a  |   e    | (1, 1, 0) | 25 | ❌ MC=25              |
        |  7   | bab    |  b  |   b    | (1, 1, 0) | 24 | ❌ MC=24              |
        |  8   | aba    |  a  |   a    | (1, 1, 0) | 25 | ❌ MC=25              |
        |  9   | bac    |  c  |   b    | (1, 0, 1) | 25 | ✅ MC=26 → idx 6      |
        | 10   | acd    |  d  |   a    | (0, 0, 1) | 23 | ❌ MC=23              |
        +------+--------+-----+--------+-----------+----+-----------------------+

        Step 1: start=0, end=0, (c) add 'c'
            sFreq[c]: 0→1,  pFreq[c]=1  →  new match (1==1)      →  matchCount = 24
            Window size = 1 < 3, expand.

        Step 2: start=0, end=1, (cb) add 'b'
            sFreq[b]: 0→1,  pFreq[b]=1  →  new match (1==1)      →  matchCount = 25
            Window size = 2 < 3, expand.

        Step 3: start=0, end=2, (cba) add 'a'
            sFreq[a]: 0→1,  pFreq[a]=1  →  new match (1==1)      →  matchCount = 26
            Window size = 3 == K
            matchCount == 26  →  ✅ anagram found at start=0       →  result = [0]
            Remove s[0]='c':  sFreq[c]: 1→0,  pFreq[c]=1  →  broke match (0==1-1)
                                                                      matchCount = 25

        Step 4: start=1, end=3, (bae) add 'e'
            sFreq[e]: 0→1,  pFreq[e]=0  →  broke match (1==0+1)  →  matchCount = 24
            Window size = 3 == K
            matchCount = 24 ≠ 26  →  ❌ not an anagram
            Remove s[1]='b':  sFreq[b]: 1→0,  pFreq[b]=1  →  broke match (0==1-1)
                                                                      matchCount = 23

        Step 5: start=2, end=4, (aeb) add 'b'
            sFreq[b]: 0→1,  pFreq[b]=1  →  new match (1==1)      →  matchCount = 24
            Window size = 3 == K
            matchCount = 24 ≠ 26  →  ❌ not an anagram
            Remove s[2]='a':  sFreq[a]: 1→0,  pFreq[a]=1  →  broke match (0==1-1)
                                                                      matchCount = 23

        Step 6: start=3, end=5, add 'a'
            sFreq[a]: 0→1,  pFreq[a]=1  →  new match (1==1)      →  matchCount = 24
            Window size = 3 == K
            matchCount = 24 ≠ 26  →  ❌ not an anagram
            Remove s[3]='e':  sFreq[e]: 1→0,  pFreq[e]=0  →  new match (0==0)
                                                                      matchCount = 25

        Step 7: start=4, end=6, add 'b'
            sFreq[b]: 1→2,  pFreq[b]=1  →  broke match (2==1+1)  →  matchCount = 24
            Window size = 3 == K
            matchCount = 24 ≠ 26  →  ❌ not an anagram
            Remove s[4]='b':  sFreq[b]: 2→1,  pFreq[b]=1  →  new match (1==1)
                                                                      matchCount = 25

        Step 8: start=5, end=7, add 'a'
            sFreq[a]: 1→2,  pFreq[a]=1  →  broke match (2==1+1)  →  matchCount = 24
            Window size = 3 == K
            matchCount = 24 ≠ 26  →  ❌ not an anagram
            Remove s[5]='a':  sFreq[a]: 2→1,  pFreq[a]=1  →  new match (1==1)
                                                                      matchCount = 25

        Step 9: start=6, end=8, add 'c'
            sFreq[c]: 0→1,  pFreq[c]=1  →  new match (1==1)      →  matchCount = 26
            Window size = 3 == K
            matchCount == 26  →  ✅ anagram found at start=6       →  result = [0, 6]
            Remove s[6]='b':  sFreq[b]: 1→0,  pFreq[b]=1  →  broke match (0==1-1)
                                                                      matchCount = 25

        Step 10: start=7, end=9, add 'd'
            sFreq[d]: 0→1,  pFreq[d]=0  →  broke match (1==0+1)  →  matchCount = 24
            Window size = 3 == K
            matchCount = 24 ≠ 26  →  ❌ not an anagram
            Remove s[7]='a':  sFreq[a]: 1→0,  pFreq[a]=1  →  broke match (0==1-1)
                                                                      matchCount = 23

        end=10 >= s.length()=10, loop ends.

        Final result: [0, 6]  ✓
*/

class Solution1 {
public:
    bool checkInclusion(string pattern, string text) {

        int pLen = pattern.length();
        int tLen = text.length();
        if (pLen > tLen)
            return false;

        vector<int> pFreq(26, 0), tFreq(26, 0);

        //find the hash of the pattern
        for (int i = 0; i < pLen; i++) {
            pFreq[pattern[i] - 'a']++;
        }

        int start = 0, end = 0;

        while (end < tLen) {
            // Expand: add current character to window
            tFreq[text[end] - 'a']++;

            int windowSize = end - start + 1;

            if (windowSize < pLen) {
                // Window not big enough yet
                end++;
            }
            else {
                // Window is exactly pLen — check if it's a permutation
                if (tFreq == pFreq)
                    return true;

                // Shrink: remove leftmost character and slide forward
                tFreq[text[start] - 'a']--;
                start++;
                end++;
            }
        }
        return false;
    }
};

class Solution2 {
public:
    bool checkInclusion(string p, string t) {
        vector<int> pHash(26, 0);
        vector<int> tHash(26, 0);

        for (int i = 0; i < p.length(); i++) {
            pHash[p[i] - 'a']++;
        }

        int matchCount = 0;
        for (int i = 0; i < p.length(); i++) {
            if(pHash[p[i]-'a'] == 0) matchCount++;
        }

        int start = 0, end = 0, K = p.length();
        bool containsAnagram = false;
        while (end < t.length()) {
            // 1. Add the current element to window
            char c = t[end] - 'a';
            tHash[c]++;
            if(tHash[c] == pHash[c])  matchCount++;
            else if(tHash[c] == pHash[c] + 1) matchCount--;

            // 2.1. Check if windowSize == K. If not then expand the pointer to
            // add more elements to this window
            if (end - start + 1 < K) {
                end++;
            }
            // 2.2. If the windowSize == K.
            else if (end - start + 1 == K) {
                if (pHash == tHash)                 // 1. Process the current window
                    return true;

                char charToDelete = t[start] - 'a'; // 2. Delete the starting element from window
                tHash[charToDelete]--; 
                if(tHash[charToDelete] == pHash[charToDelete])  matchCount++;
                else if(tHash[charToDelete] == pHash[charToDelete] - 1) matchCount--;

                start++;                            // 3. Adjust pointers
                end++;
            }
        }

        return containsAnagram;
    }
};

int main() {
	Solution obj;
	cout << obj.checkInclusion("ab", "eidbaooo") << endl;
	cout << obj.checkInclusion("ab", "eidboaoo") << endl;

	return 0;
}
