#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <numeric>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given a string s, find the first non-repeating character in it and return its index. If it does not exist, return -1.



	Examples:
	--------
	Example 1:
	Input: s = "leetcode"
	Output: 0

	Explanation:
	The character 'l' at index 0 is the first character that does not occur at any other index.

	Example 2:
	Input: s = "loveleetcode"
	Output: 2

	Example 3:
	Input: s = "aabb"
	Output: -1

 	Constraints:

	1 <= s.length <= 105
	s consists of only lowercase English letters.

	Approach:
	---------	
	Use a int[26] as all the letters are lower case English letters.
	unordere_map should be used when the upper limit of the keys is not known.
*/

class Solution {
public:
	int firstUniqChar(string s) {
		vector<int> freq(26, 0);
		for (char c : s) {
			freq[c - 'a']++;
		}

		for (int i = 0; i < s.length(); i++) {
			char c = s[i];
			if (freq[c - 'a'] == 1)
				return i;
		}
		return -1;
	}
};

int main() {
	Solution obj;
	
	cout << obj.firstUniqChar("leetcode") << endl;
	cout << obj.firstUniqChar("loveleetcode") << endl;
	cout << obj.firstUniqChar("aabb") << endl;

	return 0;
}