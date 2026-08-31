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
*/

class Solution {
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

int main() {
	Solution obj;
	cout << obj.checkInclusion("ab", "eidbaooo") << endl;
	cout << obj.checkInclusion("ab", "eidboaoo") << endl;

	return 0;
}