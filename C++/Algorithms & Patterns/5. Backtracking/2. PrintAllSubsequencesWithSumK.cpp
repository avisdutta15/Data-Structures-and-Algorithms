#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given an array arr[] of length n and a number k, the task is to find all the subsequences of the array 
	with sum of its elements equal to k.
	
	Note: A subsequence is a subset that can be derived from an array by removing zero or more elements, 
	without changing the order of the remaining elements.



	Examples:
	---------
	Input: arr[] = [1, 2, 3], k = 3 
	Output: [ [1, 2], [3] ]
	Explanation: All the subsequences of the given array are:
	[ [1], [1, 2], [1, 2, 3], [1, 3], [2], [2, 3], [3], [] ]
	Out of which only two subsequences have sum of their elements equal to 3.

	Input: arr[] = [1, 2, 3], k = 7
	Output: []
	Explanation: Sum of all the elements of the array is 6, which is smaller than the required sum, 
	thus they are no subsequences with sum of its elements equal to 7.

	Input: arr[] = [17, 18, 6, 11, 2, 4], k = 6  
	Output: [ [2, 4], [6] ] 

	Approach: 
	----------
	Include and exclude
*/

class Solution {
private:
	void printAllSubsequencesUtil(vector<int>& A, int index, vector<int>& subsequence, vector<vector<int>>& allSubsequence, int &sum, int& K) {
		
		//base case: reached the end of the input list so push the current subsequnce to the result
		if (index == A.size()) {
			if(sum == K)
				allSubsequence.push_back(subsequence);
			return;
		}

		//include
		subsequence.push_back(A[index]);
		sum = sum + A[index];
		printAllSubsequencesUtil(A, index + 1, subsequence, allSubsequence, sum, K);
		subsequence.pop_back();
		sum = sum - A[index];

		//exclude
		printAllSubsequencesUtil(A, index + 1, subsequence, allSubsequence, sum, K);
	}
public:
	vector<vector<int>> printAllSubsequencesWithSumK(vector<int>& A, int K) {
		vector<vector<int>> allSubsequence;
		vector<int> subsequence;
		int sum = 0;
		printAllSubsequencesUtil(A, 0, subsequence, allSubsequence, sum, K);
		return allSubsequence;
	}
};

int main()
{
	Solution obj;
	vector<int> A = { 1,2,3 };
	auto allSubsequences = obj.printAllSubsequencesWithSumK(A, 3);
	for (auto v : allSubsequences) {
		for(int i: v) cout << i << " ";
		cout << endl;
	}

	return 0;
}