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

    Approach: SLIDING WINDOW WITH FREQUENCY MATCHING
    -----------------------------------------------

    TIME COMPLEXITY: O(|s|) - Single pass through string s
    SPACE COMPLEXITY: O(1) - Fixed size frequency arrays (26 characters)

    ALGORITHM:
    1. Create frequency map for pattern p
    2. Use sliding window of size |p| over string s
    3. Maintain frequency of current window
    4. Compare frequencies to detect anagrams
    5. Slide window: remove left char, add right char

*/

class Solution {
public:
	vector<int> findAnagrams(string s, string p) {
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

	auto allAnagrams = obj.findAnagrams(s, p);
	for (int i : allAnagrams) {
		cout << i << " ";
	}
	cout << endl;

	s = "abacabad";
	p = "aaab";
	allAnagrams = obj.findAnagrams(s, p);
	for (int i : allAnagrams) {
		cout << i << " ";
	}
	cout << endl;

	s = "cbaebabacd";
	p = "abc";
	allAnagrams = obj.findAnagrams(s, p);
	for (int i : allAnagrams) {
		cout << i << " ";
	}
	cout << endl;

	return 0;
}