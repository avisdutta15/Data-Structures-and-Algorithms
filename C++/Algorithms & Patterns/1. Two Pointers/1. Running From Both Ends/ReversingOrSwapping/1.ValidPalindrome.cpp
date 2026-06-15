#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	A phrase is a palindrome if, after converting all uppercase letters into 
	lowercase letters and removing all non-alphanumeric characters, 
	it reads the same forward and backward. Alphanumeric characters include letters and numbers.
	
	Given a string s, return true if it is a palindrome, or false otherwise.

 

	Examples:
	---------
	Input: s = "A man, a plan, a canal: Panama"
	Output: true
	Explanation: "amanaplanacanalpanama" is a palindrome.

	Input: s = "race a car"
	Output: false
	Explanation: "raceacar" is not a palindrome.

	Input: s = " "
	Output: true
	Explanation: s is an empty string "" after removing non-alphanumeric characters.
	Since an empty string reads the same forward and backward, it is a palindrome.

	Constraints:
	------------
		1 <= s.length <= 2 * 10^5
		s consists only of printable ASCII characters


	Approach 
	--------


*/

class Solution {
private:
	bool isValidCharacter(char c) {
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
			return true;
		return false;
	}
public:
	bool isPalindrome(string s) {
		int left = 0;
		int right = s.length() - 1;

		while (left <= right) {

			// if left is not valid character then skip them
			if (isValidCharacter(s[left]) == false)
				left++;

			// if right is not valid character then skip them
			else if (isValidCharacter(s[right]) == false)
				right--;

			// for valid character if the characters(in lower or upper form) donot match return false
			else if (isValidCharacter(s[left]) && isValidCharacter(s[right])) {
				if (tolower(s[left]) != tolower(s[right]))
					return false;
				left++; right--;
			}
		}
		return true;
	}
};

int main() {
	Solution obj;
	cout << obj.isPalindrome("A man, a plan, a canal: Panama") << endl;

	cout << obj.isPalindrome("race a car") << endl;

	return 0;
}
