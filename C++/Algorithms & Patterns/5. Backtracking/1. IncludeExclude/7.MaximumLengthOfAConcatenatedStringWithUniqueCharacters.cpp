#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	You are given an array of strings arr. A string s is formed by the concatenation of a subsequence 
	of arr that has unique characters.

	Return the maximum possible length of s.

	A subsequence is an array that can be derived from another array by deleting some or no elements 
	without changing the order of the remaining elements.


	Examples:
	---------
	Input: arr = ["un","iq","ue"]
	Output: 4
	Explanation: All the valid concatenations are:
	- ""
	- "un"
	- "iq"
	- "ue"
	- "uniq" ("un" + "iq")
	- "ique" ("iq" + "ue")
	Maximum length is 4.

	Input: arr = ["cha","r","act","ers"]
	Output: 6
	Explanation: Possible longest valid concatenations are "chaers" ("cha" + "ers") and "acters" ("act" + "ers").

	Input: arr = ["abcdefghijklmnopqrstuvwxyz"]
	Output: 26
	Explanation: The only string in arr has all 26 characters.

	Approach:
	----------

	1. Include and exclude
	2. For loop based: (starting from idx)
*/

class Solution {
private:
	bool isUnique(string s) {
		int charset[26] = { 0 };
		for (char c : s) {
			if (charset[c - 'a'] != 0)
				return false;
			charset[c - 'a'] = 1;
		}
		return true;
	}
	void solve(vector<string>& A, string currentSub, int& maxLen, int i) {

		//if the sub is not having unique chars then return
		if (isUnique(currentSub) == false)
			return;

		if (i == A.size()) {
			maxLen = max(maxLen, (int)currentSub.length());
			return;
		}

		//include
		solve(A, currentSub + A[i], maxLen, i + 1);

		//exclude
		solve(A, currentSub, maxLen, i + 1);
	}

public:
	int maxLength(vector<string>& arr) {
		int maxLen = 0, i = 0;
		string currentSub = "";
		solve(arr, currentSub, maxLen, i);
		return maxLen;
	}
};

class Solution2 {
private:
	bool isUnique(string s) {
		int charset[26] = { 0 };
		for (char c : s) {
			if (charset[c - 'a'] != 0)
				return false;
			charset[c - 'a'] = 1;
		}
		return true;
	}
	void solve(vector<string>& A, string currentSub, int& maxLen, int idx) {
		if (idx > A.size())
			return;

		if (isUnique(currentSub) == false)
			return;

		maxLen = max(maxLen, (int)currentSub.length());

		for (int i = idx; i < A.size(); i++) {
			solve(A, currentSub + A[i], maxLen, i + 1);
		}
	}

public:
	int maxLength(vector<string>& arr) {
		int maxLen = 0, i = 0;
		string currentSub = "";
		solve(arr, currentSub, maxLen, i);
		return maxLen;
	}
};

int main() {
	Solution obj;
	vector<string> A = { "un","iq","ue" };
	auto ans = obj.maxLength(A);
	cout << ans;

	cout << endl;

	Solution2 obj2;
	ans = obj2.maxLength(A);
	cout << ans;

	cout << endl;

	return 0;
}