#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given two strings s and t, return true if t is an anagram of s, and false otherwise.


	Examples:
	--------
	Example 1:
	Input: s = "anagram", t = "nagaram"
	Output: true

	Example 2:
	Input: s = "rat", t = "car"
	Output: false

	Constraints:
	1 <= s.length, t.length <= 5 * 104
	s and t consist of lowercase English letters.

	Follow up: What if the inputs contain Unicode characters? How would you adapt your solution to such a case?


	Approach:
	---------
	1. Using Sorting
		Sort s and t. Check s == t
		T.C. - O(nlogn) + O(mlogm) where n = size of s, m = size of t
		S.C. - O(1)
	2. Using key formed by the freqeuncy of the words.
		getFrequencySignature(s) == getFrequencySignature(t)
		getFrequencySignature(word)
			freq[26] = {0}
			for each character c
				freq[c - 'a']++
			string key
			for i=0 to 26
				if(freq[c-'a'] > 0)
					key = key + char('a'+ i)
					key = key + to_string(freq[c-'a']);
		T.C. - O(n) + O(m)
		S.C. - O(26) + O(26)
	3. Using one frequency array.
		increase the frequency of each character of s in freq
		decrease the frequency of each character of t in freq
		if all the elements of freq is 0 then return true else false

		T.C. - O(n) + O(m)
		S.C. - O(26)

	For followup, we can use approach 3. But use unordered_map instead of freq[26] as the ascii of unicode
	characters starts from 128.
*/


class Solution {
private:
	string getKey(string str) {
		vector<int> freq(26, 0);
		for (char c : str) {
			freq[c - 'a']++;
		}

		string key;
		for (int i = 0; i < 26; i++) {
			if (freq[i] > 0) {
				key += char(i + 'a');
				key += to_string(freq[i]);
			}
		}
		return key;
	}
public:
	bool isAnagram1(string s, string t) {
		if (s.size() != t.size())
			return false;
		sort(s.begin(), s.end());
		sort(t.begin(), t.end());
		return s == t;
	}

	bool isAnagram2(string s, string t) {
		if (s.size() != t.size())
			return false;
		return getKey(s) == getKey(t);
	}

	bool isAnagram3(string s, string t) {
		if (s.size() != t.size())
			return false;
		vector<int>freq(26, 0);
		for (char c : s) {
			freq[c - 'a']++;
		}

		for (char c : t) {
			freq[c - 'a']--;
		}
		for (int i : freq) {
			if (i != 0)
				return false;
		}

		return true;
	}
};

int main() {
	Solution obj;
	obj.isAnagram1("anagram", "nagaram") == true ? cout << "true" << endl : cout << "false" << endl;
	obj.isAnagram1("rat", "car") == true ? cout << "true" << endl : cout << "false" << endl;

	obj.isAnagram2("anagram", "nagaram") == true ? cout << "true" << endl : cout << "false" << endl;
	obj.isAnagram2("rat", "car") == true ? cout << "true" << endl : cout << "false" << endl;

	obj.isAnagram3("anagram", "nagaram") == true ? cout << "true" << endl : cout << "false" << endl;
	obj.isAnagram3("rat", "car") == true ? cout << "true" << endl : cout << "false" << endl;

	return 0;
}