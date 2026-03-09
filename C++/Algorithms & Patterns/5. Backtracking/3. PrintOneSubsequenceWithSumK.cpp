#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given an array arr[] of length n and a number k, the task is to find only the subsequences of the array 
	with sum of its elements equal to k.
	
	Note: A subsequence is a subset that can be derived from an array by removing zero or more elements, 
	without changing the order of the remaining elements.



	Examples:
	---------
	Input: arr[] = [1, 2, 3], k = 3 
	Output: [ [1, 2] ]


	Input: arr[] = [1, 2, 3], k = 7
	Output: []

	Input: arr[] = [17, 18, 6, 11, 2, 4], k = 6  
	Output: [ [2, 4] ] 

	Approach: 
	----------
	Include and exclude
*/

class Solution {
private:
	bool printOneSubsequencesWithSumKUtil(vector<int>& A, int index, vector<int>& subsequence, vector<vector<int>>& allSubsequence, int &sum, int& K) {
		
		//base case: reached the end of the input list so push the current subsequnce to the result
		if (index == A.size()) {
			if (sum == K) {
				allSubsequence.push_back(subsequence);
				return true;
			}
			return false;
		}

		//include
		subsequence.push_back(A[index]);
		sum = sum + A[index];
		bool include = printOneSubsequencesWithSumKUtil(A, index + 1, subsequence, allSubsequence, sum, K);
		subsequence.pop_back();
		sum = sum - A[index];
		if (include == true)
			return true;

		//exclude
		bool exclude = printOneSubsequencesWithSumKUtil(A, index + 1, subsequence, allSubsequence, sum, K);
		return exclude;
	}
public:
	vector<vector<int>> printOneSubsequencesWithSumK(vector<int>& A, int K) {
		vector<vector<int>> allSubsequence;
		vector<int> subsequence;
		int sum = 0;
		printOneSubsequencesWithSumKUtil(A, 0, subsequence, allSubsequence, sum, K);
		return allSubsequence;
	}
};

int main()
{
	Solution obj;
	vector<int> A = { 1,2,3 };
	auto allSubsequences = obj.printOneSubsequencesWithSumK(A, 3);
	for (auto v : allSubsequences) {
		for(int i: v) cout << i << " ";
		cout << endl;
	}

	return 0;
}