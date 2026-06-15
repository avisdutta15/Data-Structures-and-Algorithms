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
	Write a function that reverses a string. The input string is given as an array of characters s.
	You must do this by modifying the input array in-place with O(1) extra memory.

 

	Examples:
	---------
	Input: s = ["h","e","l","l","o"]
	Output: ["o","l","l","e","h"]

	Input: s = ["H","a","n","n","a","h"]
	Output: ["h","a","n","n","a","H"]

	Constraints:
	------------
		1 <= s.length <= 2 * 10^5
		s consists only of printable ASCII characters


	Approach 
	--------


*/

class Solution {
public:
	void reverseString(vector<char>& s) {
		int i = 0, j = s.size() - 1;
		while (i < j) {
			char temp = s[i];
			s[i] = s[j];
			s[j] = temp;
			i++; j--;
		}
	}
};

int main() {
	Solution obj;
	vector<char> s = { 'h' ,'e','l','l','o' };
	obj.reverseString(s);
	for (auto c : s) {
		cout << c << " ";
	}
	return 0;
}
