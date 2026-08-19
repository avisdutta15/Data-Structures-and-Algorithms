#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <stack>
#include <string>

using namespace std;

/*
	https://www.youtube.com/watch?v=HW-y3gvQTVQ
	Problem Statement:
	------------------
	You have intercepted a secret message encoded as a string of numbers. The message is decoded via the following mapping:
	"1" -> 'A'
	"2" -> 'B'
	...
	"25" -> 'Y'
	"26" -> 'Z'
	
	However, while decoding the message, you realize that there are many different ways you can decode 
	the message because some codes are contained in other codes ("2" and "5" vs "25").
	
	For example, "11106" can be decoded into:
	"AAJF" with the grouping (1, 1, 10, 6)
	"KJF" with the grouping (11, 10, 6)
	The grouping (1, 11, 06) is invalid because "06" is not a valid code (only "6" is valid).
	Note: there may be strings that are impossible to decode.
	
	Given a string s containing only digits, return the number of ways to decode it. 
	If the entire string cannot be decoded in any valid way, return 0.
	
	The test cases are generated so that the answer fits in a 32-bit integer.


	Examples:
	---------
	Input: s = "12"
	Output: 2
	Explanation:
	"12" could be decoded as "AB" (1 2) or "L" (12).

	Input: s = "226"
	Output: 3
	Explanation:
	"226" could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).

	Input: s = "06"
	Output: 0
	Explanation:
	"06" cannot be mapped to "F" because of the leading zero ("6" is different from "06"). 
	In this case, the string is not a valid encoding, so return 0.



	Constraints:
	------------
	1 <= s.length <= 100
	s contains only digits and may contain leading zero(s).

	Approach:
	--------
	At every index i
		for single digit, we can either include it and check (i+1).
		for double digit, if its valid (s[i] == '1' || (s[i+1] >= '2' && s[i+1] <= '6') then we either it and check(i+2)
			i.e. 10 to 26
		return total ways = ways single digit + ways double digit
*/

// Recursive
class Solution1 {
private:
	int solve(int i, string& s) {
		// if reached the end of the string then it means there is 1 way
		if (i == s.length())
			return 1;

		if (s[i] == '0')
			return 0;

		int total_ways_by_including_i = solve(i + 1, s);
		int total_ways_by_including_iPlus1 = 0;
		if (i + 1 < s.length()) {
			if (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6'))
				total_ways_by_including_iPlus1 = solve(i + 2, s);
		}


		return total_ways_by_including_i + total_ways_by_including_iPlus1;
	}

public:
	int numDecodings(string s) {
		return solve(0, s);
	}
};

// Top Down: Memoization
class Solution2 {
private:
	int solve(int i, string& s, vector<int>& dp) {
		// if reached the end of the string then it means there is 1 way
		if (i == s.length())
			return dp[i] = 1;

		if (s[i] == '0')
			return dp[i] = 0;

		if (dp[i] != -1)
			return dp[i];

		int total_ways_by_including_i = solve(i + 1, s, dp);
		int total_ways_by_including_iPlus1 = 0;
		if (i + 1 < s.length()) {
			if (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6'))
				total_ways_by_including_iPlus1 = solve(i + 2, s, dp);
		}

		return dp[i] = total_ways_by_including_i + total_ways_by_including_iPlus1;
	}

public:
	int numDecodings(string s) {
		int n = s.length();
		vector<int> dp(n + 1, -1);
		return solve(0, s, dp);
	}
};

// Bottom Up
class Solution3 {
public:
	int numDecodings(string s) {
		int n = s.length();

		// dp[i] = number of ways to decode string from i to n
		vector<int> dp(n + 1, -1);

		dp[n] = 1;

		for (int i = n - 1; i >= 0; i--) {
			if (s[i] == '0')
				dp[i] = 0;
			else {
				int total_ways_by_including_i = dp[i + 1];
				int total_ways_by_including_iPlus1 = 0;
				if (i + 1 < s.length()) {
					if (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6'))
						total_ways_by_including_iPlus1 = dp[i + 2];
				}

				dp[i] = total_ways_by_including_i + total_ways_by_including_iPlus1;
			}
		}

		return dp[0];
	}
};

// Bottom Up: O(N) time and O(1) space
// Can we use constant space? Yes. dp[i] depends on dp[i+1] and dp[i+2]
class Solution4 {
public:
	int numDecodings(string s) {
		int n = s.length();

		int next_next = 0;		// dp[i + 2]
		int next = 1;			// dp[i + 1]
		int current = 0;		// dp[i]

		for (int i = n - 1; i >= 0; i--) {
			if (s[i] == '0')
				current = 0;
			else {
				int total_ways_by_including_i = next;
				int total_ways_by_including_iPlus1 = 0;
				if (i + 1 < s.length()) {
					if (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6'))
						total_ways_by_including_iPlus1 = next_next;
				}

				current = total_ways_by_including_i + total_ways_by_including_iPlus1;
			}
			next_next = next;
			next = current;
		}

		return current;
	}
};

int main() {
    Solution1 obj;
	cout << obj.numDecodings("1") << endl;
	return 0;
}