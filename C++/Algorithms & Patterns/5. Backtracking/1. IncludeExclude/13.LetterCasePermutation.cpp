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
	At every recursive step i, you only make a decision for the current character at index i.
		- If it's a letter -> Branch twice 
			append lower, recurse, backtrack
			append upper, recurse, backtrack.
		- If it's a digit -> Branch once 
			append digit, recurse, backtrack.
	
	
	Approach 2:
	----------
	For loop based

	store the result only when current_subset.size == input_str.size
	for i=startidx to i<=input_str.size
		you only make a decision for the current character at index i.
		- If it's a letter -> Branch twice 
			append lower, recurse, backtrack
			append upper, recurse, backtrack.
		- If it's a digit -> Branch once 
			append digit, recurse, backtrack.
*/

// include / exclude
class Solution1 {
private:
	void solve(string s, int i, string &current_subset, vector<string>& allSubsets) {
		if (i == s.length()) {
			allSubsets.push_back(current_subset);
			return;
		}

		//if the current character is a alphabet
		//if lowercase then make it uppercase. if uppercase then make it lowercase
		if (isalpha(s[i])) {
            // branch 1: toupper
            current_subset = current_subset + (char)toupper(s[i]);
			solve(s, i + 1, current_subset, allSubsets);
            current_subset.pop_back();

            // branch 2: tolower
            current_subset = current_subset + (char)tolower(s[i]);
			solve(s, i + 1, current_subset, allSubsets);
            current_subset.pop_back();
		}
        else{
			// else it is a digit. add it to current_subset.
    		current_subset = current_subset + s[i];
		    solve(s, i + 1, current_subset, allSubsets);
            current_subset.pop_back();
        }
	}
public:
	vector<string> letterCasePermutation(string s) {
		vector<string> allSubsets;
		string current_subset;
		int start_index = 0;
		solve(s, start_index, current_subset, allSubsets);
		return allSubsets;
	}
};

// include / exclude + inplace
class Solution2 {
private:
	void solve(string &s, int i, vector<string>& allSubsets) {
		if (i == s.length()) {
			allSubsets.push_back(s);
			return;
		}

        char originalChar = s[i];	//track it to restore after each recursive call

		//if the current character is a alphabet
		//if lowercase then make it uppercase. if uppercase then make it lowercase
		if (isalpha(s[i])) {
            // branch 1: toupper
            s[i] = (char)toupper(s[i]);
			solve(s, i + 1, allSubsets);
            s[i] = originalChar;	// backtrack -> place the original character back

            // branch 2: tolower
            s[i] = (char)tolower(s[i]);
			solve(s, i + 1, allSubsets);
            s[i] = originalChar;	// backtrack -> place the original character back
		}
        else{
			// else it is a digit. leave it as it is.
    		solve(s, i + 1, allSubsets);
        }
	}
public:
	vector<string> letterCasePermutation(string s) {
		vector<string> allSubsets;
		int i = 0;
		solve(s, i, allSubsets);
		return allSubsets;
	}
};

// for-loop. Add only when the current_subset has length = original string length
class Solution3 {
private:
	void solve(string s, int start_index, string &current_subset, vector<string>& allSubsets) {
		// base case: 
		if (current_subset.length() == s.length()) {
			allSubsets.push_back(current_subset);
			return;
		}

        for (int i = start_index; i < s.length(); i++){
            //if the current character is a alphabet
            //if lowercase then make it uppercase. if uppercase then make it lowercase
            if (isalpha(s[i])) {
                // branch 1: toupper
                current_subset = current_subset + (char)toupper(s[i]);
                solve(s, i + 1, current_subset, allSubsets);
                current_subset.pop_back();

                // branch 2: tolower
                current_subset = current_subset + (char)tolower(s[i]);
                solve(s, i + 1, current_subset, allSubsets);
                current_subset.pop_back();
            }
            else{
				// else it is a digit. add it to current_subset.
                current_subset = current_subset + s[i];
                solve(s, i + 1, current_subset, allSubsets);
                current_subset.pop_back();
            }
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
