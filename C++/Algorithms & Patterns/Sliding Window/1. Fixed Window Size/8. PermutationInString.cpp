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

        vector<int> pHash(26, 0), tHash(26, 0);

        //find the hash of the pattern and text(first window)
        for (int i = 0; i < pLen; i++) {
            pHash[pattern[i] - 'a']++;
            tHash[text[i] - 'a']++;
        }

        if (pHash == tHash)
            return true;

        //iterate over the text
        for (int i = pLen; i < tLen; i++) {
            //remove from window
            tHash[text[i - pLen] - 'a']--;

            //add to the window
            tHash[text[i] - 'a']++;

            //process the window
            if (tHash == pHash)
                return true;
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