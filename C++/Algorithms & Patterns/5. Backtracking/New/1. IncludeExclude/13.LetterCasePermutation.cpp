#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given a string s, you can transform every letter individually to be lowercase or 
	uppercase to create another string.

	Return a list of all possible strings we could create. Return the output in any order.


	Example 1:
	Input: s = "a1b2"
	Output: ["a1b2","a1B2","A1b2","A1B2"]

	Example 2:
	Input: s = "3z4"
	Output: ["3z4","3Z4"]

	Constraints:
	------------
	1 <= s.length <= 12
	s consists of lowercase English letters, uppercase English letters, and digits.

	Approach 1 :
	----------
	Include and exclude

	Approach 2:
	----------
	For loop based
*/

class Solution1 {
private:
	void solve(string s, int i, string current_subset, vector<string>& allSubsets) {
		if (i == s.length()) {
			allSubsets.push_back(current_subset);
			return;
		}

		//if the current character is a alphabet
		//if lowercase then make it uppercase. if uppercase then make it lowercase
		if (isalpha(s[i])) {
			if (islower(s[i]))
				solve(s, i + 1, current_subset + (char)toupper(s[i]), allSubsets);
			else
				solve(s, i + 1, current_subset + (char)tolower(s[i]), allSubsets);
		}

		//either leave it as it is.        
		solve(s, i + 1, current_subset + s[i], allSubsets);
	}
public:
	vector<string> letterCasePermutation(string s) {
		vector<string> allSubsets;
		string current_subset;
		int i = 0;
		solve(s, i, current_subset, allSubsets);
		return allSubsets;
	}
};

class Solution2 {
private:
	void solve(string s, int start_index, string current_subset, vector<string>& allSubsets) {

		// In normal scenarios we add all the nodes, but here we need the nodes
		// whose size is equal to the size of the i/p string.
		if (current_subset.length() == s.length()) {
			allSubsets.push_back(current_subset);
			return;
		}

		for (int i = start_index; i < s.length(); i++) {
			//if the current character is a alphabet
			//if lowercase then make it uppercase. if uppercase then make it lowercase
			if (isalpha(s[i])) {
				if (islower(s[i]))
					solve(s, i + 1, current_subset + (char)toupper(s[i]), allSubsets);
				else
					solve(s, i + 1, current_subset + (char)tolower(s[i]), allSubsets);
			}

			//either leave it as it is.        
			solve(s, i + 1, current_subset + s[i], allSubsets);
		}
	}
public:
	vector<string> letterCasePermutation(string s) {
		vector<string> allSubsets;
		string current_subset;
		int i = 0;
		solve(s, i, current_subset, allSubsets);
		return allSubsets;
	}
};

int main() {
	Solution1 obj1;
	string str = "a1b2";
	vector<string> res = obj1.letterCasePermutation(str);

	for (string s : res)
		cout << s << " ";

	cout << endl;

	Solution1 obj2;
	str = "a1b2";
	res = obj2.letterCasePermutation(str);

	for (string s : res)
		cout << s << " ";

	cout << endl;
}
