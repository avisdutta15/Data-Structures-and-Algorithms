#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <numeric>
using namespace std;

/*
	Problem Statement:
	-----------------
	Given a string array words, return an array of all characters that show up in all strings within the 
	words (including duplicates). You may return the answer in any order.

	Examples:
	--------
	Example 1:
	Input: words = ["bella","label","roller"]
	Output: ["e","l","l"]
	
	Example 2:
	Input: words = ["cool","lock","cook"]
	Output: ["c","o"]
 
	Constraints:
	1 <= words.length <= 100
	1 <= words[i].length <= 100
	words[i] consists of lowercase English letters.

	Approach:
	---------	
	The problem requires finding common characters that appear in all strings within the array, including duplicates. 
	The approach leverages frequency counting for each character in the alphabet (from 'a' to 'z'). By comparing the 
	character frequencies across all words, we can identify which characters appear in all the words and how many 
	times they appear.
		
		1. Initialize Frequency Array:
		Start by counting the frequency of each character in the first word. This will be our reference frequency array.
		First, count the frequency of each character in the first word "bella".

		Character	Frequency
		a	1
		b	1
		e	1
		l	2
		-	0

	
		2. Update Frequency Array:
		For each subsequent word, count the frequency of each character.
		Update the reference frequency array to keep only the minimum frequency of each character seen so far. This ensures 
		that the reference frequency array will ultimately represent the characters that are common to all words and the 
		minimum number of times they appear in any word.
		Count the frequency of each character in "label":

		Character	Frequency
		a	1
		b	1
		e	1
		l	2
		-	0

		Take the minimum frequency of each character between "bella" and "label":
		Character	Frequency in "bella"	Frequency in "label"	Updated Frequency
		a					1						1						1
		b					1						1						1
		e					1						1						1
		l					2						2						2
		-					0						0						0
	
		3. Build Result:
		Iterate through the reference frequency array.
		For each character that has a non-zero frequency, add it to the result list the number of times it appears in the 
		reference frequency array.

		T.C - 
			Counting characters in each word: O(n * m), where n is the number of words and m is the average length of the words.
			Updating the reference frequency array: O(n * 26), since we compare 26 possible characters for each word.
			Constructing the result list: O(26), iterating through the frequency array to build the result.
			Overall, the time complexity is O(n * m), where n is the number of words and m is the length of the longest word.

		S.C - 
			The space used by the commonCharacterCounts and currentCharacterCounts arrays are constant, as they always 
			have a size of 26 (the number of lowercase English letters).
			Beyond these arrays, the algorithm uses a constant amount of additional space for variables words_size, i, 
			and letter.
			Therefore, the space complexity is O(1).
*/

class Solution {
public:
    vector<string> commonChars(vector<string>& words) {
        vector<int> commonFreq(26, 0);
        vector<string> common;

        for (char c : words[0]) {
            commonFreq[c - 'a']++;
        }

        for (int i = 1; i < words.size(); i++) {
            vector<int> currentWordFreq(26, 0);
            string word = words[i];
            for (char c : word) {
                currentWordFreq[c - 'a']++;
            }
            for (int i = 0; i < 26; i++) {
                commonFreq[i] = min(commonFreq[i], currentWordFreq[i]);
            }
        }

        //build the resultant common character array
        for (int i = 0; i < 26; i++) {
            if (commonFreq[i] != 0) {
                for (int j = 1; j <= commonFreq[i]; j++) {
                    common.push_back(string(1, i + 'a'));
                }
            }
        }

        return common;
    }
};

int main() {
	Solution obj;
	vector<string> words = { "bella", "label", "roller" };
	auto commonCharacterList = obj.commonChars(words);
	for (auto c : commonCharacterList) {
		cout << c << " ";
	}
	cout << endl;

	words = { "cool","lock","cook" };
	commonCharacterList = obj.commonChars(words);
	for (auto c : commonCharacterList) {
		cout << c << " ";
	}
	cout << endl;

	return 0;
}