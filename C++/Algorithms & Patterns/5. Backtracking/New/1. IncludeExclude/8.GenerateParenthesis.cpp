#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

	Examples:
	---------
	Input: n = 3
	Output: ["((()))","(()())","(())()","()(())","()()()"]

	Input: n = 1
	Output: ["()"]

	Approach:
	----------
	1. Include and exclude
		At any point:
			We can add '(' if we still have openings left
			We can add ')' only if it won’t break validity
		Valid condition:
			Number of ')' should never exceed '('
*/

class Solution {
private:
	void solve(const int& n, string parenthesis, vector<string>& ans, int opening, int closing) {
		if (opening == n && closing == n) {
			ans.push_back(parenthesis);
			return;
		}

		//if opening or closing brackets have exhausted then return.
		if (opening > n || closing > n)
			return;

		//include (
		//conditions?=Yes. do we have n left?
		if (opening < n)
			solve(n, parenthesis + "(", ans, opening + 1, closing);

		//include )
		//conditions?=Yes. is the count of ) < (
		if (closing < opening)
			solve(n, parenthesis + ")", ans, opening, closing + 1);
	}
public:
	vector<string> generateParenthesis(int n) {
		string parenthesis = "";
		vector<string> ans;
		solve(n, parenthesis, ans, 0, 0);
		return ans;
	}
};
int main() {
	Solution obj;
	auto ans = obj.generateParenthesis(3);
	for (auto s : ans) {
		cout << s << endl;
	}
	cout << endl;

	return 0;
}