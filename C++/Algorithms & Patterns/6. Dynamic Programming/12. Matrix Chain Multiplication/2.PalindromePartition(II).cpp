#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given a string s, partition s such that every substring of the partition is a palindrome.
	Return the minimum cuts needed for a palindrome partitioning of s.. 

	Examples:
	---------
	Input: s = "aab"
	Output: 1
	Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.

	Input: s = "a"
	Output: 0
	
	Input: s = "ab"
	Output: 1

	Approach:
	---------
	Solution 1: Pure Brute Force Recursion
		Time Complexity: O(N * 2^N) (Exponential)
			For every interval, you are trying every possible split point k, and then branching into two separate recursive calls 
			(leftCut and rightCut). This overlapping subproblem tree grows exponentially (similar to Catalan numbers). 
			Additionally, calculating s.substr() and passing it to the O(N) isPalindrome function at every single node adds a 
			massive linear overhead.

		Space Complexity: O(N)
			There is no 2D array here. The space is solely consumed by the recursive call stack, which can go up to N frames deep, 
			and the temporary string copies created by substr().

	Solution 2: Recursion + Precomputed Palindrome Table
		Time Complexity: O(2^N) (Exponential)
			You successfully reduced the palindrome check from O(N) to an O(1) lookup by spending O(N^2) time upfront to build 
			the isPal table. However, because you are still not memoizing the solve function itself, the algorithm still 
			recursively branches out to re-evaluate the same floating intervals over and over.

		Space Complexity: O(N^2)
			You allocated an N x N boolean matrix isPal. The recursion stack is still O(N).

	Solution 3: Optimized Recursion (Prefix Checking)
		Time Complexity: O(2^N) (Exponential)
			You made a massive logical leap here by realizing you don't need to recursively split the left side if it isn't a 
			palindrome. By setting leftCut = 0 and only recursing on rightCut = solve(s, k + 1, j), your j variable gets 
			permanently locked at n - 1.

			However, because there is no dp cache, in the worst-case scenario (e.g., a string of all the same characters like "aaaaa"), 
			isPal[i][k] is always true. The recursion tree will still branch out to calculate the exact same suffixes repeatedly, 
			keeping it exponential.

		Space Complexity: O(N^2)
			O(N^2) for the isPal table + O(N) for the recursion stack.

	Solution 4: Top-Down Memoization (The "Secret" 1D DP)
		Time Complexity: O(N^2)
			This is the optimal time complexity! Here is why: Building the isPal table takes O(N^2). 
			Then, in your recursive function, because j is locked to n - 1, your function only ever evaluates suffixes. 
			Out of your entire N x N dp matrix, the recursion only actually visits N unique states 
			(specifically dp[0][n-1], dp[1][n-1], etc.). Inside each of those N states, the k loop runs up to N times. 
			N states * N iterations = O(N^2).

		Space Complexity: O(N^2)
			O(N^2) for the isPal table + O(N^2) for the dp table + O(N) for the recursion stack. 
			(Note: Even though you only use one column of the dp table, you still allocate a full 2D matrix in memory).

	Solution 5: Bottom-Up 2D Tabulation
		Time Complexity: O(N^3) (Will likely cause TLE)
			Unlike Solution 4, which dynamically skips useless states, your for loops here are "dumb" 
			(mathematically speaking). They blindly force the calculation of every single cell in the N x N matrix. 
			You have an i loop (N), a j loop (N), and an inner k loop (N). N * N * N = O(N^3).

		Space Complexity: O(N^2)
			O(N^2) for the isPal table + O(N^2) for the dp table. No recursion stack overhead.
*/


class Solution1 {
private:
	bool isPalindrome(string s) {
		int i = 0, j = s.length() - 1;
		while (i <= j) {
			if (s[i] != s[j])
				return false;
			i++;
			j--;
		}
		return true;
	}
	int solve(string s, int i, int j) {
		//1. BASE CASE
		//   if string is empty
		if (i > j)
			return 0;
		
		//   if string is of length 1, then we can't make any cut
		if (i == j)
			return 0;

		//   if string is palindrome, then we can't make any cut
		if (isPalindrome(s.substr(i, j - i + 1)) == true)
			return 0;

		//2. TRY EVERY POSSIBLE SPLIT/CUT
		//   AT EVERY K = I TO J-1 WE CAN MAKE A CUT POINT
		int minCuts = INT_MAX;
		for (int k = i; k <= j - 1; k++) {

			//3. SPLIT INTO LEFT AND RIGHT HALF AND THEN CALCULATE THE MERGE COST
			int leftCut = solve(s, i, k);
			int rightCut = solve(s, k + 1, j);

			// Calculate the mergeCut. We will do only 1 cut at kth position.
			int mergeCut = 1;

			//4. UPDATE THE ANSWER
			int total_cut_at_split_k = leftCut + rightCut + mergeCut;

			// Keep track of the minimum cost found
			minCuts = min(minCuts, total_cut_at_split_k);
		}
		return minCuts;
	}
public:
	int minCut(string s) {
		int i = 0;
		int j = s.length() - 1;
		return solve(s, i, j);
	}
};

// Can we optimize? 
// If we look carefully, we can observe that we are calling isPalindrome function again and again for the same substring.
// So, we can precompute it and store it in a 2D boolean array. In this way isPalindrome will become O(N) -> O(1) lookup.
class Solution2 {
private:
	void populateIsPal(string s, vector<vector<bool>>& isPal) {
		//Let's look at the dependencies:
		//	To know if isPal[i][j] is true, we need to look at isPal[i + 1][j - 1](the row below, and the column to the left).
		//	To calculate the cuts for isPal[i][j], we need isPal[i][k] and isPal[k + 1][j](values in the same row to the left, \
		//  and values in columns directly below).
		//Because our i loop goes from bottom to top, and our j loop goes from left to right, 
		//everything we need is mathematically guaranteed to be calculated already.
		//we must use our trusty "Bottom-to-Top, Left-to-Right" loop structure!

		int n = s.length();
		for (int i = n - 1; i >= 0; i--) {
			for (int j = i; j <= n - 1; j++) {
				if (s[i] == s[j]) {
					//If the string is 1, 2, or 3 characters long, meaning j - i <= 2, 
					//there is no meaningful inner string to check. If the outer characters match, 
					//it's automatically a palindrome!
					if(j-i<=2)
						isPal[i][j] = true;
					else if(isPal[i+1][j-1]==true)
						isPal[i][j] = true;
				}
			}
		}
	}

	int solve(string s, int i, int j, vector<vector<bool>> &isPal) {
		//1. BASE CASE
		//   if string is empty
		if (i > j)
			return 0;

		//   if string is of length 1, then we can't make any cut
		if (i == j)
			return 0;

		//   if string is palindrome, then we can't make any cut
		if (isPal[i][j] == true)
			return 0;

		//2. TRY EVERY POSSIBLE SPLIT/CUT
		//   AT EVERY K = I TO J-1 WE CAN MAKE A CUT POINT
		int minCuts = INT_MAX;
		for (int k = i; k <= j - 1; k++) {

			//3. SPLIT INTO LEFT AND RIGHT HALF AND THEN CALCULATE THE MERGE COST
			int leftCut = solve(s, i, k, isPal);
			int rightCut = solve(s, k + 1, j, isPal);

			// Calculate the mergeCut. We will do only 1 cut at kth position.
			int mergeCut = 1;

			//4. UPDATE THE ANSWER
			int total_cut_at_split_k = leftCut + rightCut + mergeCut;

			// Keep track of the minimum cost found
			minCuts = min(minCuts, total_cut_at_split_k);
		}
		return minCuts;
	}
public:
	int minCut(string s) {
		int n = s.length();
		int i = 0;
		int j = n - 1;
		vector<vector<bool>> isPal(n, vector<bool>(n, false));
		populateIsPal(s, isPal);
		return solve(s, i, j, isPal);
	}
};

// Can we optimize further?
// We will make the partition/cut only if the string till the partition 
// (till Kth position) is a valid palindrome.Because the question states that all
// partition must be a valid palindrome.If we dont check this, we will have to
// perform recursion on the left subproblem too(solve(str, i, k)) and we will waste
// a lot of time on subproblems that is not required.
class Solution3 {
private:
	void populateIsPal(string s, vector<vector<bool>>& isPal) {
		//Let's look at the dependencies:
		//	To know if isPal[i][j] is true, we need to look at isPal[i + 1][j - 1](the row below, and the column to the left).
		//	To calculate the cuts for isPal[i][j], we need isPal[i][k] and isPal[k + 1][j](values in the same row to the left, \
		//  and values in columns directly below).
		//Because our i loop goes from bottom to top, and our j loop goes from left to right, 
		//everything we need is mathematically guaranteed to be calculated already.
		//we must use our trusty "Bottom-to-Top, Left-to-Right" loop structure!

		int n = s.length();
		for (int i = n - 1; i >= 0; i--) {
			for (int j = i; j <= n - 1; j++) {
				if (s[i] == s[j]) {
					//If the string is 1, 2, or 3 characters long, meaning j - i <= 2, 
					//there is no meaningful inner string to check. If the outer characters match, 
					//it's automatically a palindrome!
					if (j - i <= 2)
						isPal[i][j] = true;
					else if (isPal[i + 1][j - 1] == true)
						isPal[i][j] = true;
				}
			}
		}
	}

	int solve(string s, int i, int j, vector<vector<bool>>& isPal) {
		//1. BASE CASE
		//   if string is empty
		if (i > j)
			return 0;

		//   if string is of length 1, then we can't make any cut
		if (i == j)
			return 0;

		//   if string is palindrome, then we can't make any cut
		if (isPal[i][j] == true)
			return 0;

		//2. TRY EVERY POSSIBLE SPLIT/CUT
		//   AT EVERY K = I TO J-1 WE CAN MAKE A CUT POINT
		int minCuts = INT_MAX;
		for (int k = i; k <= j - 1; k++) {

			//3. SPLIT/CUT INTO LEFT AND RIGHT HALF ONLY IF s[i..j] IS PALINDROME AND THEN CALCULATE THE MERGE COST
			if (isPal[i][k] == true) {
				//int leftCut = solve(s, i, k, isPal);
				int leftCut = 0;	//No need to recurse for left split. as the left split is already a palindrome (verified above)
									//the min cuts in that split will be 0.
				int rightCut = solve(s, k + 1, j, isPal);

				// Calculate the mergeCut. We will do only 1 cut at kth position.
				int mergeCut = 1;

				//4. UPDATE THE ANSWER
				int total_cut_at_split_k = leftCut + rightCut + mergeCut;

				// Keep track of the minimum cost found
				minCuts = min(minCuts, total_cut_at_split_k);
			}			
		}
		return minCuts;
	}
public:
	int minCut(string s) {
		int n = s.length();
		int i = 0;
		int j = n - 1;
		vector<vector<bool>> isPal(n, vector<bool>(n, false));
		populateIsPal(s, isPal);
		return solve(s, i, j, isPal);
	}
};


// TOP DOWN
class Solution4 {
private:
	void populateIsPal(string s, vector<vector<bool>>& isPal) {
		int n = s.length();
		for (int i = n - 1; i >= 0; i--) {
			for (int j = i; j <= n - 1; j++) {
				if (s[i] == s[j]) {
					//If the string is 1, 2, or 3 characters long, meaning j - i <= 2, 
					//there is no meaningful inner string to check. If the outer characters match, 
					//it's automatically a palindrome!
					if (j - i <= 2)
						isPal[i][j] = true;
					else if (isPal[i + 1][j - 1] == true)
						isPal[i][j] = true;
				}
			}
		}
	}

	int solve(string s, int i, int j, vector<vector<bool>>& isPal, vector<vector<int>> &dp) {
		//1. BASE CASE
		//   if string is empty
		if (i > j)
			return 0;

		//   if string is of length 1, then we can't make any cut
		if (i == j)
			return 0;

		//   if string is palindrome, then we can't make any cut
		if (isPal[i][j] == true)
			return dp[i][j] = 0;

		if (dp[i][j] != -1)
			return dp[i][j];

		//2. TRY EVERY POSSIBLE SPLIT/CUT
		//   AT EVERY K = I TO J-1 WE CAN MAKE A CUT POINT
		int minCuts = INT_MAX;
		for (int k = i; k <= j - 1; k++) {

			//3. SPLIT/CUT INTO LEFT AND RIGHT HALF ONLY IF s[i..j] IS PALINDROME AND THEN CALCULATE THE MERGE COST
			if (isPal[i][k] == true) {
				//int leftCut = solve(s, i, k, isPal);
				int leftCut = 0;	//No need to recurse for left split. as the left split is already a palindrome (verified above)
									//the min cuts in that split will be 0.
				int rightCut = solve(s, k + 1, j, isPal, dp);

				// Calculate the mergeCut. We will do only 1 cut at kth position.
				int mergeCut = 1;

				//4. UPDATE THE ANSWER
				int total_cut_at_split_k = leftCut + rightCut + mergeCut;

				// Keep track of the minimum cost found
				minCuts = min(minCuts, total_cut_at_split_k);
			}
		}
		return dp[i][j] = minCuts;
	}
public:
	int minCut(string s) {
		int n = s.length();
		int i = 0;
		int j = n - 1;
		vector<vector<bool>> isPal(n, vector<bool>(n, false));
		vector<vector<int>> dp(n, vector<int>(n, -1));
		populateIsPal(s, isPal);
		return solve(s, i, j, isPal, dp);
	}
};


// BOTTOM UP
class Solution5 {
private:
	void populateIsPal(string s, vector<vector<bool>>& isPal) {
		int n = s.length();
		for (int i = n - 1; i >= 0; i--) {
			for (int j = i; j <= n - 1; j++) {
				if (s[i] == s[j]) {
					//If the string is 1, 2, or 3 characters long, meaning j - i <= 2, 
					//there is no meaningful inner string to check. If the outer characters match, 
					//it's automatically a palindrome!
					if (j - i <= 2)
						isPal[i][j] = true;
					else if (isPal[i + 1][j - 1] == true)
						isPal[i][j] = true;
				}
			}
		}
	}
public:
	int minCut(string s) {
		int n = s.length();
		vector<vector<bool>> isPal(n, vector<bool>(n, false));
		vector<vector<int>> dp(n, vector<int>(n, -1));
		populateIsPal(s, isPal);

		for (int i = n - 1; i >= 0; i--) {
			for (int j = i; j <= n - 1; j++) {
				if (i == j)
					dp[i][j] = 0;
				if (isPal[i][j] == true)
					dp[i][j] = 0;
				else {
					int minCuts = INT_MAX;
					for (int k = i; k <= j - 1; k++) {
						if (isPal[i][k] == true) {
							int leftCut = 0;
							int rightCut = dp[k + 1][j];
							int mergeCut = 1;

							int total_cut_at_split_k = leftCut + rightCut + mergeCut;
							minCuts = min(minCuts, total_cut_at_split_k);
						}
					}
					dp[i][j] = minCuts;
				}
			}
		}
		return dp[0][n - 1];
	}
};



int main()
{
	Solution1 obj1;
	cout<<obj1.minCut("aab")<<endl;
	return 0;
}