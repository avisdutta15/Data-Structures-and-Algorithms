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
    Find All Anagrams in a String

    Given two strings s and p, return an array of all the start indices of p's anagrams in s.
    You may return the answer in any order.

    An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
    typically using all the original letters exactly once.

    Examples:
    --------
    Example 1:
        Input: s = "abab", p = "ab"
        Output: [0,2]
        Explanation:
        The substring with start index = 0 is "ab", which is an anagram of "ab".
        The substring with start index = 2 is "ab", which is an anagram of "ab".

    Example 2:
        Input: s = "abacabad", p = "aaab"
        Output: [0,1]
        Explanation:
        The substring with start index = 0 is "abac", which is an anagram of "aaab".
        The substring with start index = 1 is "baca", which is an anagram of "aaab".

    Constraints:
        1 <= s.length, p.length <= 3 * 10^4
        s and p consist of lowercase English letters only.

    ========================================================================================
    APPROACH 1 — findAnagramsType1 (Solution1)
    Sliding Window + Full Frequency Vector Comparison
    ========================================================================================

    IDEA:
        Maintain a frequency vector for the current window of size |p|.
        At each valid window, compare the entire sFreq vector against pFreq.

    TIME COMPLEXITY:  O(|s| * 26) — Each window comparison scans all 26 characters.
    SPACE COMPLEXITY: O(1) — Two fixed-size arrays of 26 elements.

    ALGORITHM:
        1. Build frequency vector pFreq for pattern p.
        2. Slide a window of size |p| over s, maintaining sFreq for the current window.
        3. When window size == |p|, compare pFreq == sFreq (O(26) per comparison).
        4. Slide: remove the leftmost character, add the next right character.

    ========================================================================================
    APPROACH 2 — findAnagrams (Solution2)
    Sliding Window + matchCount Optimization
    ========================================================================================

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

    ========================================================================================
    APPROACH 3 — findAnagramsType2 (Solution3)
    Classic Two-Loop Sliding Window + Full Frequency Comparison
    ========================================================================================

    IDEA:
        Same as Approach 1 but uses a separate loop to initialize the first window,
        then a second loop to slide through the rest. Structurally simpler but still
        uses full vector comparison.

    TIME COMPLEXITY:  O(|s| * 26)
    SPACE COMPLEXITY: O(1)

    ========================================================================================
*/


class Solution1 {
private:
    void getFrequencyOfP(string &s, vector<int> &pFreq){
        for(char c: s)
            pFreq[c-'a']++;
    }
public:
    vector<int> findAnagramsType(string s, string p) {
        vector<int> pFreq(26, 0);
        vector<int> sFreq(26, 0);
        vector<int> startIndices;
        int K = p.length();

        getFrequencyOfP(p, pFreq);

        int start = 0, end = 0;

        while(end < s.length()){
			// 1. Add the current element to window
            sFreq[s[end] - 'a']++;					

			// 2.1. Check if the window size == K (here p.length). If not then expand the pointer to right to add more element
            if (windowSize < K) {
                end++;
            }
			// 2.2. If the window size == K.
            else if (windowSize == K){
                if(pFreq == sFreq)						// 1. Process this window — check if it's an anagram
                    startIndices.push_back(start);
				
                sFreq[s[start] - 'a']--;				// 2. Delete the starting element from window

                start++;								// 3. Adjust pointers to slide the window
                end++;
            }
        }

        return startIndices;
    }
};

class Solution2{
private:
    void getFrequencyOfP(string &s, vector<int> &pFreq){
        for(char c: s)
            pFreq[c-'a']++;
    }
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> pFreq(26, 0);
        vector<int> sFreq(26, 0);
        vector<int> startIndices;
        int K = p.length();
        getFrequencyOfP(p, pFreq);

        int start = 0, end = 0;
        int matchCount = 0;

        // Initialize matchCount: characters with freq 0 in both vectors already match
        for (int i = 0; i < 26; i++) {
            if (pFreq[i] == 0)
                matchCount++;       // since all the elements whose freq = 0 in both p and s match, we increase matchCount.
        }

        while (end < s.length()) {
            // 1. Add the current element to window
            int endChar = s[end] - 'a';
            sFreq[endChar]++;

            // if adding char to s makes the freq equal with p then matchCount++
            // if adding char to s broke the freq match (i.e. sFreq[a]=1 and pFreq[a]=0 or sFreq[a]=2 and pFreq[a]=1). 
            // Then decrease matchCount (matchCount--) stating they are not matching.
            if (sFreq[endChar] == pFreq[endChar])           matchCount++;
            else if (sFreq[endChar] == pFreq[endChar] + 1)  matchCount--;   

            // 2.1. Window too small — expand
            if (end - start + 1 < K) {
                end++;
            }
            // 2.2. Window size == K
            else {
                if (matchCount == 26)                // 1. Process this window. O(1) check instead of O(26)
                    startIndices.push_back(start);

                int startChar = s[start] - 'a';      // 2. Delete the starting element from window
                sFreq[startChar]--;

                // if adding char to s makes the freq equal with p then matchCount++
                // if adding char to s broke the freq match (i.e. sFreq[a]=1 and pFreq[a]=0 or sFreq[a]=2 and pFreq[a]=1). 
                // Then decrease matchCount (matchCount--) stating they are not matching.
                if (sFreq[startChar] == pFreq[startChar])             matchCount++;
                else if (sFreq[startChar] == pFreq[startChar] - 1)    matchCount--;

                start++;                             // 3. Adjust pointers to slide the window
                end++;
            }
        }
        return startIndices;
    }
};

class Solution3{
public:
	vector<int> findAnagramsType2(string s, string p) {
		vector<int> allanagrams;

		vector<int> pHash(26, 0);
		vector<int> sHash(26, 0);

		//process the pattern and the first window
		for (int i = 0; i < p.length(); i++) {
			pHash[p[i] - 'a']++;
			sHash[s[i] - 'a']++;
		}
		if (pHash == sHash)
			allanagrams.push_back(0);

		//process rest of the string
		for (int i = p.length(); i < s.length(); i++) {
			//delete the element which is out of the window
			sHash[s[i - p.length()] - 'a']--;

			//insert new element into the window
			sHash[s[i] - 'a']++;

			//process the window ending at index i
			if (pHash == sHash)
				allanagrams.push_back(i - p.length() + 1);
		}
			
		return allanagrams;
	}
};

int main() {
	Solution obj;
	string s = "abab";
	string p = "ab";

	auto allAnagrams = obj.findAnagramsType1(s, p);
	for (int i : allAnagrams) {
		cout << i << " ";
	}
	cout << endl;

	s = "abacabad";
	p = "aaab";
	allAnagrams = obj.findAnagramsType1(s, p);
	for (int i : allAnagrams) {
		cout << i << " ";
	}
	cout << endl;

	s = "cbaebabacd";
	p = "abc";
	allAnagrams = obj.findAnagramsType1(s, p);
	for (int i : allAnagrams) {
		cout << i << " ";
	}
	cout << endl;

	return 0;
}
