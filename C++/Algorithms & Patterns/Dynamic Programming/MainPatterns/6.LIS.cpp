#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

/*
	https://www.youtube.com/watch?v=h9rm4N8XbL0
	Problem Statement:
	-----------------
	Given an array arr[] of size n, find the length of the Longest Increasing Subsequence (LIS) i.e., 
	the longest possible subsequence in which the elements of the subsequence are sorted in strictly 
	increasing order.

	Examples:
	---------
	Input: arr[] = [3, 10, 2, 1, 20]
	Output: 3
	Explanation: The longest increasing subsequence is 3, 10, 20

	Input: arr[] = [30, 20, 10]
	Output:1
	Explanation: The longest increasing subsequences are [30], [20] and [10]

	Input: arr[] = [2, 2, 2]
	Output: 1
	Explanation:  We consider only strictly increasing subsequences, therefore the longest increasing subsequence is [2].

	Input: arr[] = [3, 4, 5, 1, 2, 3, 4]
	Output: 4
	Explanation: The longest strictly increasing subsequence is [1, 2, 3, 4], which gives a maximum length of 4. 
	(Note: [3, 4, 5] is also an increasing subsequence, but its length is only 3).


	Approach 1 :
	---------
	The idea is to compute the LIS ending at each index i.
	This is achieved by recursion. At each index i, we have two choices:
	1. Include the current element in the subsequence, if it is greater than the previous element.
	   In this case, we add 1 to the result of the recursive call on the remaining array.
	2. Exclude the current element from the subsequence.

	The recurrence relation is as follows:
	LIS(i) = 1 + max(LIS(j)) where j < i and arr[j] < arr[i]


	Approach 2:
	-----------
	The idea is to maintain a 1D array LIS[], where LIS[i] stores the length of the longest increasing subsequence 
	that ends at index i. Initially, each element in LIS[] is set to 1, as the smallest possible subsequence for any 
	element is the element itself.

	The algorithm then iterates over each element of the array. For each element arr[i], it checks all previous 
	elements arr[0] to arr[i-1]. If arr[i] is greater than arr[prev] (ensuring the subsequence is increasing), 
	it updates LIS[i] to the maximum of its current value or LIS[prev] + 1, indicating that we can extend the 
	subsequence ending at arr[prev] by including arr[i].

	Finally, the length of the longest increasing subsequence is the maximum value in the LIS[] array.

	In this approach, we build the solution from smaller subproblems to larger ones. We start by assuming that the 
	LIS ending at each index is 1 (every single element is an LIS of length 1). Then, for each index i, we look at 
	all previous indices prev < i. If arr[prev] < arr[i], it means the subsequence ending at prev can be extended by arr[i]. 
	So we update LIS[i] using the best LIS found so far for all valid previous positions.

	By the time we reach the end of the array, LIS[i] already contains the correct LIS ending at i, because all 
	smaller subproblems (earlier indices) have been computed. Finally, the overall LIS is the maximum value in 
	the LIS array.
*/

class Solution1 {
private:
	int solve(vector<int>& A, int idx, int previousIdx) {
		// Base Case: If we have traversed all the elements of the array
		// return 0 as there are no more elements to process.
		if (idx == A.size())
			return 0;

		int include = 0;
		int exclude = 0;

		// If the current element is greater than or equal to the previous element,
		// we can include the current element in the subsequence
		if (previousIdx == -1 || A[previousIdx] < A[idx])
			include = 1 + solve(A, idx + 1, idx);

		// If the current element is less than the previous element,
		// we cannot include the current element in the subsequence
		exclude = solve(A, idx + 1, previousIdx);

		// return the maximum of including and excluding the current element
		return max(include, exclude);
	}

public:
	int LongestIncreasingSubsequence(vector<int>& A) {
		int idx = 0;
		int previousIdx = -1;
		return solve(A, idx, previousIdx);
	}
};

class Solution2 {
public:
	int LongestIncreasingSubsequence(vector<int>& A) {
		int N = A.size();
		vector<int> LIS(N + 1, 1);

		for (int i = 0; i < A.size(); i++) {
			for (int j = 0; j < i; j++) {
				if (A[j] < A[i]) {
					LIS[i] = max(LIS[i], 1 + LIS[j]);
				}
			}
		}

		return *max_element(LIS.begin(), LIS.end());
	}
};

int main() {
	Solution1 obj1;
	vector<int> A = { 3, 10, 2, 1, 20 };
	vector<int> B = { 30, 20, 10 };
	cout << obj1.LongestIncreasingSubsequence(A) << endl;
	cout << obj1.LongestIncreasingSubsequence(B) << endl;

	Solution2 obj2;
	A = { 3, 10, 2, 1, 20 };
	B = { 30, 20, 10 };
	cout << obj1.LongestIncreasingSubsequence(A) << endl;
	cout << obj1.LongestIncreasingSubsequence(B) << endl;

	return 0;
}

