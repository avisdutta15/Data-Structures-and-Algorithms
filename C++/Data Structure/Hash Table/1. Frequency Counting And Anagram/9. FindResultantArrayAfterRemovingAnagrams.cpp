#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <numeric>
using namespace std;

/*
	Problem Statement:
	-----------------
	You are given a 0-indexed string array words, where words[i] consists of lowercase English letters.

	In one operation, select any index i such that 0 < i < words.length and words[i - 1] and words[i] 
	are anagrams, and delete words[i] from words. Keep performing this operation as long as you can 
	select an index that satisfies the conditions.

	Return words after performing all operations. It can be shown that selecting the indices for each 
	operation in any arbitrary order will lead to the same result.

	An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase using 
	all the original letters exactly once. For example, "dacb" is an anagram of "abdc".

 
	Examples
	--------
	Example 1:
	Input: words = ["abba","baba","bbaa","cd","cd"]
	Output: ["abba","cd"]
	Explanation:
		One of the ways we can obtain the resultant array is by using the following operations:
		- Since words[2] = "bbaa" and words[1] = "baba" are anagrams, we choose index 2 and delete words[2].
		  Now words = ["abba","baba","cd","cd"].
		- Since words[1] = "baba" and words[0] = "abba" are anagrams, we choose index 1 and delete words[1].
		  Now words = ["abba","cd","cd"].
		- Since words[2] = "cd" and words[1] = "cd" are anagrams, we choose index 2 and delete words[2].
		  Now words = ["abba","cd"].
		We can no longer perform any operations, so ["abba","cd"] is the final answer.
	
	Example 2:
	Input: words = ["a","b","c","d","e"]
	Output: ["a","b","c","d","e"]
	Explanation:
		No two adjacent strings in words are anagrams of each other, so no operations are performed.
 
	Constraints:
	1 <= words.length <= 100
	1 <= words[i].length <= 10
	words[i] consists of lowercase English letters.

	Approach:
	---------	
	
*/

class Solution {
	bool isAnagram(const string& word1, const string& word2) {
		if (word1.length() != word2.length())
			return false;

		vector<int> freq(26, 0);
		for (auto c : word1) {
			freq[c - 'a']++;
		}
		for (auto c : word2) {
			freq[c - 'a']--;
		}
		for (int i = 0; i < 26; i++) {
			if (freq[i] != 0)
				return false;
		}
		return true;
	}
public:
	vector<string> removeAnagrams(vector<string>& words) {
		vector<string> answer;

		//push the first word into the answer
		answer.push_back(words[0]);

		//start iterating from index 1 
		for (int i = 1; i < words.size(); i++) {
			if (isAnagram(words[i], words[i - 1]) == true) {
				continue;
			}
			else {
				answer.push_back(words[i]);
			}
		}
		return answer;
	}
};

int main() {
	Solution obj;
	vector<string> words = { "abba","baba","bbaa","cd","cd" };
	auto answer = obj.removeAnagrams(words);
	for (auto c : answer) {
		cout << c << " ";
	}
	cout << endl;

	words = { "a","b","c","d","e" };
	answer = obj.removeAnagrams(words);
	for (auto c : answer) {
		cout << c << " ";
	}
	cout << endl;

	return 0;
}