#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given an array of strings nums containing n unique binary strings each of length n, return a binary string 
    of length n that does not appear in nums. If there are multiple answers, you may return any of them.
     

	Examples:
	---------
	Input: nums = ["01","10"]
    Output: "11"
    Explanation: "11" does not appear in nums. "00" would also be correct.

	Input: nums = ["00","01"]
    Output: "11"
    Explanation: "11" does not appear in nums. "10" would also be correct.

    Input: nums = ["111","011","001"]
    Output: "101"
    Explanation: "101" does not appear in nums. "000", "010", "100", and "110" would also be correct.


	Approach:
	----------
	1. Include and exclude
        

*/

class Solution {
private:
    bool solve(string& s, unordered_set<string> set, int i, int n) {
        if (i >= n) {
            if (set.find(s) == set.end())
                return true;
            return false;
        }

        //include 0
        s = s + "0";
        bool l = solve(s, set, i + 1, n);
        if (l == true)
            return true;
        s.pop_back();

        //include 1
        s = s + "1";
        bool r = solve(s, set, i + 1, n);
        if (r == true)
            return true;
        s.pop_back();
        return r;
    }
public:
    string findDifferentBinaryString(vector<string>& nums) {
        unordered_set<string> set;
        for (auto s : nums) {
            set.insert(s);
        }

        string s = "";
        int i = 0;
        solve(s, set, i, nums.size());
        return s;
    }
};

int main() {
	Solution obj;
    auto nums = { "00", "11" };
    auto ans = obj.findDifferentBinaryString(nums);
    cout << ans;
	cout << endl;

	return 0;
}