#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

/*
	https://www.youtube.com/watch?v=Ni9RwDZdzrU&list=PLpIkg8OmuX-JhFpkhgrAwZRtukO0SkwAt&index=41&pp=iAQB

	Problem Statement: 
	-----------------
	Given an array arr[] of non-negative integers and a value sum, the task is to check if there is a subset of the given array whose sum is equal to the given sum. 

	Examples:
	---------
	Input: arr[] = [3, 34, 4, 12, 5, 2], sum = 9
	Output: True
	Explanation: There is a subset (4, 5) with sum 9.

	Input: arr[] = [3, 34, 4, 12, 5, 2], sum = 30
	Output: False
	Explanation: There is no subset that add up to 30.

	
	Approach:
	---------
		for every item, we have two choices

			1. Include the current item (if its value is <= remaining sum)
			   in the subset and recur for remaining items
			2. Exclude the current item from the subset and recur for remaining items

			Base Case:
			if (no items left && sum becomes 0) or (items left && sum becomes 0)
				then subset sum is possible
			if (no items left && sum != 0) 
				then subset sum is not possible
*/

// Backward Traversal of Input. Results bubble up from Recursion Tree leaf
class Solution1 {
private:
	// can we reach the sum by including / excluding the current N elements ?
	bool solve(int N, vector<int>& A, int sum) {
		//base case: if no items left and sum = 0 we can make an empty set.
		//			 if items left but sum = 0 then we can make an empty set.
		if ((N == 0 && sum == 0) || (N != 0 && sum == 0))
			return true;

		//base case: if no items left and sum != 0 we cannot make any set.
		if (N == 0 && sum != 0)
			return false;

		bool include = false;
		bool exclude = false;

		// As we are traversing backwards, the current item under consideration
		// is at index N-1
		
		// Case 1. Include current item `A[n-1]` in the subset and recur for
		// remaining items with decreased sum `sum - A[n-1]`
		if (A[N-1] <= sum) {
			include = solve(N - 1, A, sum - A[N-1]);
		}

		// Case 2. Exclude current item `A[n-1]` and recur for remaining items
		exclude = solve(N - 1, A, sum);

		// return whether possible to get sum by including or excluding current item
		return include || exclude;
	}

public:
	int subsetSum(vector<int>& A, int sum) {
		int N = A.size();
		return solve(N, A, sum);
	}
};

// Backward Traversal of Input. Results bubble up from Recursion Tree leaf
class Solution2 {
private:
	// can we reach the sum by including / excluding the current N elements ?
	bool solve(int N, vector<int>& A, int sum, vector<vector<int>> &memo) {
		//base case: if no items left and sum = 0 we can make an empty set.
		//			 if items left but sum = 0 then we can make an empty set.
		if ((N == 0 && sum == 0) || (N != 0 && sum == 0))
			return memo[N][sum] = true;

		//base case: if no items left and sum != 0 we cannot make any set.
		if (N == 0 && sum != 0)
			return memo[N][sum] = false;

		// Check cache
		if(memo[N][sum] != -1)
			return memo[N][sum];

		bool include = false;
		bool exclude = false;

		// As we are traversing backwards, the current item under consideration
		// is at index N-1

		// Case 1. Include current item `A[n-1]` in the subset and recur for
		// remaining items with decreased sum `sum - A[n-1]`
		if (A[N - 1] <= sum) {
			include = solve(N - 1, A, sum - A[N - 1], memo);
		}

		// Case 2. Exclude current item `A[n-1]` and recur for remaining items
		exclude = solve(N - 1, A, sum, memo);

		// return whether possible to get sum by including or excluding current item
		return memo[N][sum] = (include || exclude);
	}

public:
	int subsetSum(vector<int>& A, int sum) {
		int N = A.size();
		// n and sum are changing states. So we need a 2D cache
		// n ranges from 0 to N
		// sum ranges from 0 to SUM
		vector<vector<int>> memo(N + 1, vector<int>(sum + 1, -1));
		return solve(N, A, sum, memo);
	}
};

class Solution3 {
public:
	int subsetSum(vector<int>& A, int SUM) {
		int N = A.size();

		// dp[n][sum] stores we reach the sum by including / excluding the current n elements ?
		vector<vector<bool>> dp(N + 1, vector<bool>(SUM + 1, false));

		// fill the dp table in a bottom-up manner
		for (int n = 0; n <= N; n++) {
			for (int sum = 0; sum <= SUM; sum++) {
				//base case: if no items left and sum = 0 we can make an empty set.
				//			 if items left but sum = 0 then we can make an empty set.
				if ((n == 0 && sum == 0) || (n != 0 && sum == 0))
					dp[n][sum] = true;

				//base case: if no items left and sum != 0 we cannot make any set.
				else if (n == 0 && sum != 0)
					dp[n][sum] = false;

				else {
					bool include = false;
					bool exclude = false;

					// As we are traversing backwards, the current item under consideration
					// is at index N-1

					// Case 1. Include current item `A[n-1]` in the subset and recur for
					// remaining items with decreased sum `sum - A[n-1]`
					if (A[n - 1] <= sum) {
						include = dp[n - 1][sum - A[n - 1]];
					}

					// Case 2. Exclude current item `A[n-1]` and recur for remaining items
					exclude = dp[n - 1][sum];

					// return whether possible to get sum by including or excluding current item
					dp[n][sum] = (include || exclude);
				}			
			}
		}

		// Return whether we can build a subset of sum = SUM using all the N items (including/excluding)
		return dp[N][SUM];
	}
};

int main() {
	Solution1 obj1;
	vector<int> A = { 3, 34, 4, 12, 5, 2 };
	cout << obj1.subsetSum(A, 9)<<endl;
	cout << obj1.subsetSum(A, 30) << endl;

	Solution2 obj2;
	A = { 3, 34, 4, 12, 5, 2 };
	cout << obj2.subsetSum(A, 9) << endl;
	cout << obj2.subsetSum(A, 30) << endl;

	Solution3 obj3;
	A = { 3, 34, 4, 12, 5, 2 };
	cout << obj3.subsetSum(A, 9) << endl;
	cout << obj3.subsetSum(A, 30) << endl;

	return 0;
}

