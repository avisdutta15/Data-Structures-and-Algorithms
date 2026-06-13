#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

/*
	https://www.youtube.com/watch?v=tGAMyZxlwuA&t=2710s
	Problem Statement:
	-----------------
	Given a string s, find the longest substring which is a palindrome. 
	If there are multiple answers, then find the first appearing substring.

	Examples:
	---------
	Input: s = "forgeeksskeegfor"
	Output: "geeksskeeg"
	Explanation: The longest substring that reads the same forward and backward 
	is "geeksskeeg". Other palindromes like "kssk" or "eeksskee" are shorter.

	Input: s = "Geeks"
	Output: "ee"
	Explanation: The substring "ee" is the longest palindromic part in "Geeks". 
	All others are shorter single characters.

	Input: s = "abc"
	Output: "a"
	Explanation: No multi-letter palindromes exist. So the first character "a" 
	is returned as the longest palindromic substring.


	Approach 1 : Generating all sub-strings - O(n^3) time and O(1) space
	-------------------------------------------------------------------
	Generate all possible substrings of the given string. 
	For each substring, check if it is a palindrome.
		If it is, update the result if its length is greater 
		than the longest palindrome found so far.


	This has overlapping subproblems.
	Add memo cache in the isPalindrome function.

	...

	For bottom up, we will approach it in a different way.
	
	The main idea behind the approach is that if we know the status (i.e., palindrome or not) 
	of the substring ranging [i, j], we can find the status of the substring ranging [i-1, j+1] 
	by only matching the character str[i-1] and str[j+1].

	If the substring from i to j is not a palindrome, then the substring from i-1 to j+1 will 
	also not be a palindrome. Otherwise, it will be a palindrome only if str[i-1] and str[j+1] 
	are the same.
	Base on this fact, we can create a 2D table (say table[][] which stores status of 
	substring str[i . . . j] ), and check for substrings with LENGTH from 1 to n. 

	For each length find all the substrings starting from each character i and find 
	if it is a palindrome or not using the above idea. The longest length for which a 
	palindrome formed will be the required answer.


	Approach 2: Expand around center for every index i
	-----------
		for every index i
			expand and check is palindrome(i, i)		// odd length
			expand and check is palindrome(i, i+1)		// even length
	
*/

class Solution1 {
private:
	// Recursively check if a string is palindrome
	bool isPalindrome(int i, int j, string& s) {
		// this means we have exhausted traversing the string
		if (i > j)
			return true;

		// if the characters are not same then it is not a palindrome
		if (s[i] != s[j])
			return false;

		// check if the rest of the string is palindrome or not
		return isPalindrome(i + 1, j - 1, s);
	}
public:
	string longestPalindrome(string s) {
		int N = s.length();
		int start_index = -1;
		int maxLen = 0;

		// for every substring
		for (int i = 0; i < N; i++) {
			for (int j = i; j < N; j++) {

				// check if this is a palindrome or not
				if (isPalindrome(i, j, s)) {
					if (maxLen < j - i + 1) {
						maxLen = j - i + 1;
						start_index = i;
					}
				}
			}
		}

		// if the string was empty then start_index will be -1
		// else return the max length
		return start_index == -1 ? "" : s.substr(start_index, maxLen);
	}
};

class Solution2 {
private:
	// Recursively check if a string is palindrome
	bool isPalindrome(int i, int j, string& s, vector<vector<int>> &memo) {
		// this means we have exhausted traversing the string
		if (i > j)
			return true;

		// check the cache
		if (memo[i][j] != -1)
			return memo[i][j];

		// if the characters are not same then it is not a palindrome
		if (s[i] != s[j])
			return memo[i][j] = false;

		// check if the rest of the string is palindrome or not
		return memo[i][j] = isPalindrome(i + 1, j - 1, s, memo);
	}

public:
	string longestPalindrome(string s) {
		int N = s.length();
		int start_index = -1;
		int maxLen = 0;
		vector<vector<int>> memo(N+1, vector<int>(N+1, -1));

		// for every substring
		for (int i = 0; i < N; i++) {
			for (int j = i; j < N; j++) {

				// check if this is a palindrome or not
				if (isPalindrome(i, j, s, memo)) {
					if (maxLen < j - i + 1) {
						maxLen = j - i + 1;
						start_index = i;
					}
				}
			}
		}

		// if the string was empty then start_index will be -1
		// else return the max length
		return start_index == -1 ? "" : s.substr(start_index, maxLen);
	}
};

class Solution3 {
public:
	string longestPalindrome(string s) {
		int N = s.length();
		int start_index = -1;
		int maxLen = 0;
		vector<vector<bool>> dp(N + 1, vector<bool>(N + 1, -1));

		// For every substring of length L
		// check if it is palindrome.
		// keep a index (i, j) : i=start j=end
		// check if S(i, j) is palindrome or not. 
		// s[i] == s[j] && s(i + 1, j - 1) is palindrome(i.e.dp[i + 1][j - 1] == true)
		for (int L = 1; L <= N; L++) {

			//i is the start index of substring of length L
			for (int i = 0; i + L - 1 < N; i++) {

				// j is the end index of substring of length L
				int j = i + L - 1;

				// substring of length 1
				if (i == j) {
					dp[i][j] = true;
				}

				// substring of length 2
				else if (i + 1 == j) {
					if (s[i] == s[j])
						dp[i][j] = true;
					else
						dp[i][j] = false;
				}

				// substring of length >=3
				else {
					if (s[i] == s[j] && dp[i + 1][j - 1] == true)
						dp[i][j] = true;
					else
						dp[i][j] = false;
				}

				//Calculate the max length
				if (dp[i][j] == true && maxLen < L) {
					start_index = i;
					maxLen = L;
				}
			}
		}

		// if the string was empty then start_index will be -1
		// else return the max length
		return start_index == -1 ? "" : s.substr(start_index, maxLen);
	}
};

class Solution4 {
private:
	int getPalindromeLength(int& i, int& j, const string& s) {
		int length = 0;
		while (i >= 0 && j < s.length() && s[i] == s[j]) {
			length = (j - i + 1);
			i--; j++;
		}
		// readjust the indices since you came out of loop.
		// this is needed for the correct start and end
		i++;
		j--;
		return length;
	}
public:
	string longestPalindrome(string s) {
		int start_index = -1;
		int maxLen = 0;

		// for every index i, expand from center
		for (int i = 0; i < s.length(); i++) {

			// expand around (i)
			int start = i;
			int end = i;
			int oddLength = getPalindromeLength(start, end, s);
			if (oddLength != 0 && maxLen < oddLength) {
				maxLen = oddLength;
				start_index = start;
			}

			// expand around (i, i+1)
			start = i;
			end = i + 1;
			int evenLength = getPalindromeLength(start, end, s);
			if (evenLength != 0 && maxLen < evenLength) {
				maxLen = evenLength;
				start_index = start;
			}
		}

		return start_index == -1 ? "" : s.substr(start_index, maxLen);
	}
};

int main() {
	Solution1 obj1;
	cout << obj1.longestPalindrome("bab") << endl;

	Solution2 obj2;
	cout << obj2.longestPalindrome("bab") << endl;

	Solution3 obj3;
	cout << obj3.longestPalindrome("bab") << endl;

	Solution4 obj4;
	cout << obj4.longestPalindrome("bab") << endl;
	return 0;
}
