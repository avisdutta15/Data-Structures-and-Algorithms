#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given a string containing digits from 2-9 inclusive, return all possible letter 
	combinations that the number could represent. Return the answer in any order.

	A mapping of digits to letters (just like on the telephone buttons) is given below. 
	Note that 1 does not map to any letters.


	Example 1:
	Input: digits = "23"
	Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

	Example 2:
	Input: digits = "2"
	Output: ["a","b","c"]

	Constraints:
	------------
	1 <= digits.length <= 4
	digits[i] is a digit in the range ['2', '9'].

	Approach - https://www.youtube.com/watch?v=vgnhZzw-kfU
	---------

	For the input digits = "23", the algorithm explores combinations by mapping '2' to "abc" and '3' to "def".

	In this pattern, the depth of the tree (the Levels) represents which digit in the input string we are 
	currently looking at (digit_index). The branches at each node represent the for loop iterating through 
	the mapped letters (word[i]).

	ASCII Recursion Tree

	Level 0:                                     ""
	(idx = 0)                       [Processing digit '2' -> "abc"]
								   /              |               \
								  /               |                \
						 Add 'a' /        Add 'b' |                 \ Add 'c'
								/                 |                  \
	Level 1:                  "a"                "b"                 "c"
	(idx = 1)        [Processing '3'->"def"] [Processing '3'->"def"] [Processing '3'->"def"]
						   /   |   \           /   |   \            /   |   \
						 /     |     \       /     |     \        /     |     \
					  'd'     'e'    'f'   'd'    'e'    'f'    'd'    'e'    'f'
					  /        |       \   /       |       \    /       |       \
	Level 2:       "ad"      "ae"     "af""bd"   "be"     "bf""cd"    "ce"     "cf"
	(idx = 2)        |         |        |   |      |        |   |       |        |
	Base Case:     (Add)     (Add)    (Add)(Add) (Add)    (Add)(Add)  (Add)    (Add)



*/

class Solution{
private:
	unordered_map<int, string> mapping;
	void solve(const string &digits, int digit_index, string current_combination, vector<string> &allCombinations) {
		if (digit_index == digits.length()) {
			allCombinations.push_back(current_combination);
			return;
		}

		int current_digit = digits[digit_index] - '0';
		string word = mapping[current_digit];

		for (int i = 0; i < word.length(); i++) {
			current_combination += word[i];
			solve(digits, digit_index + 1, current_combination, allCombinations);
			current_combination.pop_back();
		}
	}
public:
	vector<string> letterCombinations(string digits) {

		mapping[2] = "abc";
		mapping[3] = "def";
		mapping[4] = "ghi";
		mapping[5] = "jkl";
		mapping[6] = "mno";
		mapping[7] = "pqrs";
		mapping[8] = "tuv";
		mapping[9] = "wxyz";

		string current_combination = "";
		int digit_index = 0;
		vector<string> allCombinations;

		solve(digits, digit_index, current_combination, allCombinations);
		return allCombinations;
	}
};


int main() {
	Solution obj;
	vector<string> result = obj.letterCombinations("23");
	for (string s : result) {
		cout << s << endl;
	}
	cout << endl;
}
