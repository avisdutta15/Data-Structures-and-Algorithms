#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	You are given a positive integer n.
    A binary string x is valid if all substrings of x of length 2 contain at least one "1".
    Return all valid strings with length n, in any order.
     

	Examples:
	---------
	Input: n = 3
    Output: ["010","011","101","110","111"]
    Explanation: The valid strings of length 3 are: "010", "011", "101", "110", and "111".

	Input: n = 1
    Output: ["0","1"]
    Explanation: The valid strings of length 1 are: "0" and "1".

	Approach:
	----------
	1. Include and exclude
        If the last digit is 0 then we have 1 choice:
            Include 1
        If the last digit is 1 then we have 2 choice:
            Include 0
            Or include 1
		
        |
        |- 0
        |  |- 1
        |     |-0 (010)
        |     |-1 (011)
        |
        |- 1
        |  |- 0
        |  |  |-1 (101)
        |  |  
        |  |- 1
        |  |  |-1 (111)
        |  |  |-0 (110)


            if string is empty or last digit in string is 0
                solve(string + "1", i+1)
            if string is empty or last digit in string is 1
                solve(string + "1", i+1)
                solve(string + "0", i+1)

        Here we are making 3 recursive call at each level. This will be slow.
        If we look closely, we can optimize it.
        string + "1" is called 2 times - when last digit is 0 and last digit is 1.

        lets change the order:
            if string is empty or last digit in string is 1
                solve(string + "1", i+1)
                solve(string + "0", i+1)
            if string is empty or last digit in string is 0
                solve(string + "1", i+1)
        
        take the common call out of the if 
            if string is empty or last digit in string is 1
                solve(string + "0", i+1)
            solve(string + "1", i+1)

*/

class Solution {
private:
    void solve(string s, unordered_set<string>& ans, int n, int i) {
        if (i == n) {
            ans.insert(s);
            return;
        }

        //if the last digit is 0 then we have 1 choice:
        //include 1
        if (s.length() == 0 || s[s.length() - 1] == '0') {
            solve(s + "1", ans, n, i + 1);
        }
        //if the last digit is 1 then we have 2 choice:
        //include 0
        //or include 1
        if (s.length() == 0 || s[s.length() - 1] == '1') {
            solve(s + "1", ans, n, i + 1);
            solve(s + "0", ans, n, i + 1);
        }

    }
public:
    vector<string> validStrings(int n) {
        unordered_set<string> set;
        string s = "";
        solve(s, set, n, 0);
        vector<string> ans;
        for (auto c : set) {
            ans.push_back(c);
        }
        return ans;
    }
};

class Solution2 {
private:
    void solve(string s, vector<string>& ans, int n, int i) {
        if (i == n) {
            ans.push_back(s);
            return;
        }

        if (s.length() == 0 || s[s.length() - 1] == '1') {
            solve(s + "0", ans, n, i + 1);
        }
        solve(s + "1", ans, n, i + 1);
    }
public:
    vector<string> validStrings(int n) {
        vector<string> ans;
        string s = "";
        solve(s, ans, n, 0);
        return ans;
    }
};

int main() {
	Solution obj;
	auto ans = obj.validStrings(3);
	for (auto s : ans) {
		cout << s << endl;
	}
	cout << endl;

	return 0;
}