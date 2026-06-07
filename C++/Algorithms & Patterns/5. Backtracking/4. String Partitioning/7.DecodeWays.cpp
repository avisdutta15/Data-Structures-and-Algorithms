#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

/*
	Problem Statement:
	-----------------
  You have intercepted a secret message encoded as a string of numbers. The message is decoded via the following mapping:
  "1" -> 'A'
  "2" -> 'B'
  ...
  "25" -> 'Y'
  "26" -> 'Z'

  However, while decoding the message, you realize that there are many different ways you can decode the message because some codes are contained in other codes ("2" and "5" vs "25").
  For example, "11106" can be decoded into:
	  "AAJF" with the grouping (1, 1, 10, 6)
	  "KJF" with the grouping (11, 10, 6)
  The grouping (1, 11, 06) is invalid because "06" is not a valid code (only "6" is valid).
  Note: there may be strings that are impossible to decode.


  Given a string s containing only digits, return the number of ways to decode it. If the entire string cannot be decoded in any valid way, return 0.

  The test cases are generated so that the answer fits in a 32-bit integer.

  Examples:
  ---------

  Input: s = "12"
  Output: 2
  Explanation:  "12" could be decoded as "AB" (1 2) or "L" (12).

  Input: s = "226"
  Output: 3
  Explanation:  "226" could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).

  Input: s = "06"
  Output: 0
  Explanation: "06" cannot be mapped to "F" because of the leading zero ("6" is different from "06"). In this case, the string is not a valid encoding, so return 0.

  Constraints:
  ------------
  1 <= s.length <= 100
  s contains only digits and may contain leading zero(s).

  Approach:
  ---------
  String Partitioning.
	Approach 1: Accumulation of totalways using global variable
		void solve(s, i, &total_ways){
		  if(i == s.length())
			total_ways++;
			return;

		  .....
		}
	Approach 2: Bubble up the totalWays. This is best for DP memo + tabulation
		int solve(s, i){
		  if(i == s.length())
			return 1;

		  .....
		}
	Approach 3: Bubble up the totalWays + Memoization.
		int solve(s, i, memo[]){
		  if(i == s.length())
			return 1;
		  if(momo[i] != -1) return memo[i];
		  .....
		}
	Approach 4: Without for loop
		How the "Without For Loop" Solution is Derived
		If you look closely at the for loop in Approach 2, you will notice an explicit break condition:

			for (int i = start_index; i < s.length(); i++) {
				// if the length of the prefix is greater than 2, then no point in proceeding ahead
				if (i >= start_index + 2) break; 
				// ...
			}
		
		Because valid mappings only exist from "1" (A) to "26" (Z), a valid decoding chunk can never be 
		longer than 2 characters. Therefore, this for loop will always run exactly 1 or 2 times.

		Instead of writing a dynamic loop, we can "unroll" the loop into two distinct, static choices. 

		This turns the problem into a variation of the classic "Climbing Stairs" pattern: from any index i, 
		you can either take a 1-step or a 2-step.
		Unrolling the Loop:
			- Loop Iteration 1 (Take 1 character): We look at s[i]. As long as it is not '0', it is a valid 
												   single-digit number (1-9). This gives us the number of ways 
												   from the rest of the string: solve(i + 1).
			- Loop Iteration 2 (Take 2 characters): We look at s[i...i+1]. As long as we haven't hit the end of 
													the string, and the 2-digit number is between 10 and 26, it 
													is valid. This gives us the number of ways from the rest of 
													the string skipping two characters: solve(i + 2).
		
		By eliminating the for loop and substring extractions, we avoid massive overhead, making the code much 
		faster and cleaner (which leads exactly to Approach 4).


*/

// Appraoch 1 : Accumulation of totalWays
class Solution1 {
private:
	void solve(int start_index, string& s, int& totalWays) {
		// Base Case: If reached end of the string, that means we were able to decode
		if (start_index == s.length()) {
			totalWays++;
			return;
		}

		for (int i = start_index; i < s.length(); i++) {

			// if the length of the prefix is greater than 2, then no point in proceeding ahead
			if (i >= start_index + 2)
				break;

			// extract the prefix
			string prefix = s.substr(start_index, i - start_index + 1);

			// if the prefix starts with 0 then come out of this branch. No need to go any further
			// e.g. "06"
			if (prefix[0] == '0')
				break;

			// the number should be between 1 and 26
			int num = stoi(prefix);

			if (num >= 1 && num <= 26) {
				// proceed ahead with the remaining string
				solve(i + 1, s, totalWays);
			}
		}
	}
public:
	int numDecodings(string s) {
		int start_index = 0;
		int totalWays = 0;
		solve(start_index, s, totalWays);
		return totalWays;
	}
};

// Appraoch 2 : Bubble up the totalWays
class Solution2 {
private:
	int solve(int start_index, string& s) {
		// Base Case: If reached end of the string, that means we were able to decode
		if (start_index == s.length())
			return 1;

		// the number of ways we are able to decode at index = start_index
		int ways = 0;
		for (int i = start_index; i < s.length(); i++) {

			// if the length of the prefix is greater than 2, then no point in proceeding ahead
			if (i >= start_index + 2)
				break;

			// extract the prefix
			string prefix = s.substr(start_index, i - start_index + 1);

			// if the prefix starts with 0 then come out of this branch. No need to go any further
			// e.g. "06"
			if (prefix[0] == '0')
				break;

			// the number should be between 1 and 26
			int num = stoi(prefix);

			if (num >= 1 && num <= 26) {
				// proceed ahead with the remaining string
				ways = ways + solve(i + 1, s);
			}
		}
		return ways;
	}
public:
	int numDecodings(string s) {
		int start_index = 0;
		return solve(start_index, s);
	}
};

// Approach 3: Bubble up TotalWays + Memoization
class Solution3 {
private:
	int solve(int start_index, string& s, vector<int>& memo) {
		// Base Case: If reached end of the string, that means we were able to decode
		if (start_index == s.length())
			return 1;

		// Check the cache
		if (memo[start_index] != -1)
			return memo[start_index];

		// the number of ways we are able to decode at index = start_index
		int ways = 0;
		for (int i = start_index; i < s.length(); i++) {

			// if the length of the prefix is greater than 2, then no point in proceeding ahead
			if (i >= start_index + 2)
				break;

			// extract the prefix
			string prefix = s.substr(start_index, i - start_index + 1);

			// if the prefix starts with 0 then come out of this branch. No need to go any further
			// e.g. "06"
			if (prefix[0] == '0')
				break;

			// the number should be between 1 and 26
			int num = stoi(prefix);

			if (num >= 1 && num <= 26) {
				// proceed ahead with the remaining string
				ways = ways + solve(i + 1, s, memo);
			}
		}
		return memo[start_index] = ways;
	}
public:
	int numDecodings(string s) {
		int start_index = 0;
		vector<int> memo(s.length(), -1);
		return solve(start_index, s, memo);
	}
};

// Approach 4: Without for loop
// https://www.youtube.com/watch?v=HW-y3gvQTVQ
class Solution4 {
private:
	int solve(int i, string& s) {
		// Base Case: If reached end of the string, that means we were able to decode
		if (i == s.length())
			return 1;


		// Check for single character
		if (s[i] == '0')
			return 0;	// not possible to split

		
		int only_ith_char = solve(i + 1, s);

		int ith_plus_iplus1th_char = 0;
		if (i + 1 < s.length()){
			int num = stoi(s.substr(i, 2));
			if (num >= 1 && num <= 26) {
				ith_plus_iplus1th_char = solve(i + 2, s);
			}
		}

		return only_ith_char + ith_plus_iplus1th_char;
	}
public:
	int numDecodings(string s) {
		int i = 0;
		return solve(i, s);
	}
};

// Approach 5: Without for loop + Memoization
// https://www.youtube.com/watch?v=HW-y3gvQTVQ
class Solution5 {
private:
	int solve(int i, string& s, vector<int> &memo) {
		// Base Case: If reached end of the string, that means we were able to decode
		if (i == s.length())
			return memo[i] = 1;

		// Check cache
		if(memo[i] != -1)
			return memo[i];

		// Check for single character
		if (s[i] == '0')
			return memo[i] = 0;	// not possible to split


		int only_ith_char = solve(i + 1, s, memo);

		int ith_plus_iplus1th_char = 0;
		if (i + 1 < s.length()) {
			int num = stoi(s.substr(i, 2));
			if (num >= 1 && num <= 26) {
				ith_plus_iplus1th_char = solve(i + 2, s, memo);
			}
		}

		return memo[i] = only_ith_char + ith_plus_iplus1th_char;
	}
public:
	int numDecodings(string s) {
		int i = 0;
		vector<int> memo(s.length() + 1, -1);
		return solve(i, s, memo);
	}
};

// Approach 6: Bottom Up DP. We have mapped the solution as it is.
// https://www.youtube.com/watch?v=HW-y3gvQTVQ
class Solution6 {
public:
	int numDecodings(string s) {
		int N = s.length();
		vector<int> dp(N + 1, -1);
		dp[N] = 1;

		for (int i = N - 1; i >= 0; i--) {
			if (s[i] == '0')
				dp[i] = 0;
			else {
				int only_ith_char = dp[i + 1];	// solve(i+1)
				int ith_plus_iplus1th_char = 0;
				if (i + 1 < s.length()) {
					int num = stoi(s.substr(i, 2));
					if (num >= 1 && num <= 26) {
						ith_plus_iplus1th_char = dp[i + 2];	//solve(i+2)
					}
				}
				dp[i] = only_ith_char + ith_plus_iplus1th_char;
			}
		}

		return dp[0];
	}
};

class SolutionBottomUpForLoop {
public:
	int numDecodings(string s) {
		int N = s.length();

		// dp[i] stores the number of ways to decode the substring s[i...N-1]
		vector<int> dp(N + 1, 0);

		// Base Case: An empty string (or reaching the end) has 1 valid way
		dp[N] = 1;

		// Iterate backwards through the string
		for (int start_index = N - 1; start_index >= 0; start_index--) {

			// If the current character is '0', it can't start a valid code
			if (s[start_index] == '0') {
				dp[start_index] = 0;
				continue;
			}

			// Inner For-Loop (exactly like the Top-Down approach)
			int ways = 0;
			for (int i = start_index; i < N; i++) {

				// Max length of a valid code is 2
				if (i >= start_index + 2) {
					break;
				}

				// Extract prefix
				string prefix = s.substr(start_index, i - start_index + 1);
				int num = stoi(prefix);

				// If it's a valid letter code, add the ways from the remaining string
				if (num >= 1 && num <= 26) {
					ways += dp[i + 1];
				}
			}

			// Store the calculated ways for this index
			dp[start_index] = ways;
		}

		// The answer for the entire string is stored at index 0
		return dp[0];
	}
};

int main() {
	Solution1 obj1;
	cout << obj1.numDecodings("12") << endl;
	cout << obj1.numDecodings("226") << endl;
	cout << obj1.numDecodings("06") << endl;
	//cout << obj1.numDecodings("111111111111111111111111111111111111111111111") << endl;  // TLE

	Solution2 obj2;
	cout << obj2.numDecodings("12") << endl;
	cout << obj2.numDecodings("226") << endl;
	cout << obj2.numDecodings("06") << endl;
	//cout << obj2.numDecodings("111111111111111111111111111111111111111111111") << endl;  // TLE

	Solution3 obj3;
	cout << obj3.numDecodings("12") << endl;
	cout << obj3.numDecodings("226") << endl;
	cout << obj3.numDecodings("06") << endl;
	cout << obj3.numDecodings("111111111111111111111111111111111111111111111") << endl;

	Solution4 obj4;
	cout << obj4.numDecodings("12") << endl;
	cout << obj4.numDecodings("226") << endl;
	cout << obj4.numDecodings("06") << endl;
	//cout << obj4.numDecodings("111111111111111111111111111111111111111111111") << endl;

	Solution5 obj5;
	cout << obj5.numDecodings("12") << endl;
	cout << obj5.numDecodings("226") << endl;
	cout << obj5.numDecodings("06") << endl;
	cout << obj5.numDecodings("111111111111111111111111111111111111111111111") << endl;

	Solution6 obj6;
	cout << obj6.numDecodings("12") << endl;
	cout << obj6.numDecodings("226") << endl;
	cout << obj6.numDecodings("06") << endl;
	cout << obj6.numDecodings("111111111111111111111111111111111111111111111") << endl;

	return 0;
}
