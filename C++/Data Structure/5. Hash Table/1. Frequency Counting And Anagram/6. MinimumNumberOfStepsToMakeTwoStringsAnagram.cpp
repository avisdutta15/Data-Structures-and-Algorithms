#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <numeric>
using namespace std;

/*
	Problem Statement:
	-----------------
	You are given two strings of the same length s and t. In one step you can choose any character of t and replace 
	it with another character.

	Return the minimum number of steps to make t an anagram of s.

	An Anagram of a string is a string that contains the same characters with a different (or the same) ordering.

	Examples:
	--------
	Example 1:
	Input: s = "bab", t = "aba"
	Output: 1
	Explanation: Replace the first 'a' in t with b, t = "bba" which is anagram of s.

	Example 2:
	Input: s = "leetcode", t = "practice"
	Output: 5
	Explanation: Replace 'p', 'r', 'a', 'i' and 'c' from t with proper characters to make t anagram of s.

	Example 3:
	Input: s = "anagram", t = "mangaar"
	Output: 0
	Explanation: "anagram" and "mangaar" are anagrams. 

	Constraints:
	1 <= s.length <= 5 * 104
	s.length == t.length
	s and t consist of lowercase English letters only.

	Approach:
	---------	
	The key insight is that we need to count how many characters in string t 
	need to be replaced to match the character frequency of string s.
	
	STEP-BY-STEP PROCESS:
	1. Count frequency of all characters in string s
	2. For each character in string t:
	   - If it exists in s (freq > 0), decrement its count (it's already matching)
	   - If it doesn't exist in s (freq = 0), ignore it (needs replacement)
	3. Sum remaining frequencies = characters that t is missing from s
	
	The remaining frequency represents characters that s has but t doesn't provide.
	These are the minimum replacements needed in t.

	DETAILED EXAMPLE 1: s = "bab", t = "aba"
	-------------------------------------------
	
	Step 1: Build frequency map for s = "bab"
	freq['a'] = 1, freq['b'] = 2, others = 0
	freq array: [1, 2, 0, 0, 0, ..., 0]
	            a  b  c  d  e      z
	
	Step 2: Process each character in t = "aba"
	
	t[0] = 'a': freq['a'] = 1 > 0 → decrement → freq['a'] = 0
	freq array: [0, 2, 0, 0, 0, ..., 0]
	
	t[1] = 'b': freq['b'] = 2 > 0 → decrement → freq['b'] = 1  
	freq array: [0, 1, 0, 0, 0, ..., 0]
	
	t[2] = 'a': freq['a'] = 0 → no change (this 'a' needs replacement)
	freq array: [0, 1, 0, 0, 0, ..., 0]
	
	Step 3: Sum remaining frequencies
	sum = 0 + 1 + 0 + ... + 0 = 1
	
	RESULT: 1 replacement needed (replace extra 'a' in t with 'b')
	
	T.C. - O(N) - Single pass through both strings
	S.C  - O(1) - Fixed size frequency array (26 characters)

*/

class Solution {
public:
	int minSteps(string s, string t) {
		vector<int> freq(26, 0);

		for (char c : s) {
			freq[c - 'a']++;
		}

		for (char c : t) {
			//if the character is present in s
			//then decrease its count
			if (freq[c - 'a'] != 0)
				freq[c - 'a']--;
		}

		return accumulate(freq.begin(), freq.end(), 0);
	}
};

int main() {
	Solution obj;
	
	cout << "=== ALGORITHM WALKTHROUGH EXAMPLES ===" << endl << endl;
	
	// Example 1: Simple case
	cout << "Example 1: s = \"bab\", t = \"aba\"" << endl;
	cout << "Expected: 1 (replace one 'a' with 'b')" << endl;
	cout << "Result: " << obj.minSteps("bab", "aba") << endl;
	cout << "Explanation: t has extra 'a', s has extra 'b'" << endl << endl;
	
	// Example 2: More complex case  
	cout << "Example 2: s = \"leetcode\", t = \"practice\"" << endl;
	cout << "Expected: 5" << endl;
	cout << "Result: " << obj.minSteps("leetcode", "practice") << endl;
	cout << "Explanation: t needs 5 character replacements" << endl << endl;
	
	// Example 3: Already anagrams
	cout << "Example 3: s = \"anagram\", t = \"mangaar\"" << endl;
	cout << "Expected: 0 (already anagrams)" << endl;
	cout << "Result: " << obj.minSteps("anagram", "mangaar") << endl;
	cout << "Explanation: Same character frequencies" << endl << endl;
	
	// Additional test cases
	cout << "Additional Test Cases:" << endl;
	cout << "s = \"abc\", t = \"def\" → " << obj.minSteps("abc", "def") << endl;
	cout << "s = \"aab\", t = \"baa\" → " << obj.minSteps("aab", "baa") << endl;
	cout << "s = \"xxyyzz\", t = \"zzyyxx\" → " << obj.minSteps("xxyyzz", "zzyyxx") << endl;

	return 0;
}