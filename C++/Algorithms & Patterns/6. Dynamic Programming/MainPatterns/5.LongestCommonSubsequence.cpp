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
	Given a knapsack with a fixed capacity and a set of n items, where each item has an associated
	value val[i] and weight wt[i], determine the maximum profit that can be obtained by filling the
	knapsack. Each item can be selected an unlimited number of times.

	Note: We can either include an item completely or exclude it entirely - we cannot
		  include a fraction of an item.

	Examples:
	---------
	Input: capacity = 100, val[]  = [1, 30], wt[] = [1, 50]
	Output: 100
	Explanation: There are many ways to fill knapsack.
	Option 1: 2 instances of 50 unit weight item.
	Option 2: 100 instances of 1 unit weight item.
	Option 3: 1 instance of 50 unit weight item and 50 instances of 1 unit weight items.
	We get maximum value with option 2.

	Input: capacity = 8, val[] = [10, 40, 50, 70], wt[]  = [1, 3, 4, 5]
	Output : 110
	Explanation: We get maximum value with one unit of weight 5 and one unit of weight 3.


	Approach:
	---------
	The idea is to compare the last characters of s1 and s2. While comparing the strings s1 and s2 two cases arise:
	- Match : Make the recursion call for the remaining strings (strings of lengths m-1 and n-1) 
			  and add 1 to result.
	- Do not Match : Make two recursive calls. First for lengths m-1 and n, and second for m and n-1. 
			         Take the maximum of two results.
	- Base case : If any of the strings become empty, we return 0.
*/

// Backward Traversal of Input. Results bubble up from Recursion Tree leaf
class Solution1 {
private:
	int solve(string& s1, int N1, string& s2, int N2) {
		// Base Case: If either of the strings is empty, return no common subsequence.
		// return 0 as LCS.
		if (N1 == 0 || N2 == 0)
			return 0;

		// If the last character of string s1 and s2 matches
		// then the include current character in LCS and recur for remaining substrings
		if (s1[N1 - 1] == s2[N2 - 1])
			return 1 + solve(s1, N1 - 1, s2, N2 - 1);

		// If the last characters do not match
		// Recur for two cases:
		// 1. Exclude the last character of s1 
		// 2. Exclude the last character of s2 
		// Take the maximum of these two recursive calls

		int excludeS1 = solve(s1, N1 - 1, s2, N2);
		int excludeS2 = solve(s1, N1, s2, N2 - 1);
		return max(excludeS1, excludeS2);
	}

public:
	int LongestCommonSubsequence(string& s1, string& s2) {
		int N1 = s1.length();
		int N2 = s2.length();
		return solve(s1, N1, s2, N2);
	}
};

// Backward Traversal of Input. Results bubble up from Recursion Tree leaf
class Solution2 {
private:
	int solve(string& s1, int N1, string& s2, int N2, vector<vector<int>>& memo) {
		// Base Case: If either of the strings is empty, return no common subsequence.
		// return 0 as LCS.
		if (N1 == 0 || N2 == 0)
			return memo[N1][N2] = 0;

		// If the subproblem is already computed, return the result
		if (memo[N1][N2] != -1)
			return memo[N1][N2];

		// If the last character of string s1 and s2 matches
		// then the include current character in LCS and recur for remaining substrings
		if (s1[N1 - 1] == s2[N2 - 1])
			return memo[N1][N2] = 1 + solve(s1, N1 - 1, s2, N2 - 1, memo);

		// If the last characters do not match
		// Recur for two cases:
		// 1. Exclude the last character of s1 
		// 2. Exclude the last character of s2 
		// Take the maximum of these two recursive calls

		int excludeS1 = solve(s1, N1 - 1, s2, N2, memo);
		int excludeS2 = solve(s1, N1, s2, N2 - 1, memo);
		return memo[N1][N2] = max(excludeS1, excludeS2);
	}

public:
	int LongestCommonSubsequence(string& s1, string& s2) {
		int N1 = s1.length();
		int N2 = s2.length();

		// N1 and N2 are the variables that are changing states.
		// So we will create a cache - 2D vector of size (N1+1) * (N2+1).
		vector<vector<int>> memo(N1 + 1, vector<int>(N2 + 1, -1));
		return solve(s1, N1, s2, N2, memo);
	}
};

class Solution3 {
public:
	int LongestCommonSubsequence(string& s1, string& s2) {
		int N1 = s1.length();
		int N2 = s2.length();
		vector<vector<int>> dp(N1 + 1, vector<int>(N2 + 1, -1));

		for (int n1 = 0; n1 <= N1; n1++) {
			for (int n2 = 0; n2 <= N2; n2++) {
				// Base Case: If either of the strings is empty, return no common subsequence.
				// return 0 as LCS.
				if (n1 == 0 || n2 == 0)
					dp[n1][n2] = 0;

				// If the last character of string s1 and s2 matches
				// then the include current character in LCS and recur for remaining substrings
				else {
					if (s1[n1 - 1] == s2[n2 - 1])
						dp[n1][n2] = 1 + dp[n1 - 1][n2 - 1];

					// If the last characters do not match
					// Recur for two cases:
					// 1. Exclude the last character of s1 
					// 2. Exclude the last character of s2 
					// Take the maximum of these two recursive calls
					else {
						int excludeS1 = dp[n1 - 1][n2];
						int excludeS2 = dp[n1][n2 - 1];
						dp[n1][n2] = max(excludeS1, excludeS2);
					}
				}
			}
		}
		// dp[n1][n2] contains length of LCS for s1[0..n1-1]
		// and s2[0..n2-1]
		return dp[N1][N2];
	}
};

int main() {
	Solution1 obj1;
	string s1 = "AGGTAB";
	string s2 = "GXTXAYB";
	cout << obj1.LongestCommonSubsequence(s1, s2) << endl;

	Solution2 obj2;
	s1 = "AGGTAB";
	s2 = "GXTXAYB";
	cout << obj2.LongestCommonSubsequence(s1, s2) << endl;


	Solution3 obj3;
	s1 = "AGGTAB";
	s2 = "GXTXAYB";
	cout << obj3.LongestCommonSubsequence(s1, s2) << endl;

	return 0;
}

