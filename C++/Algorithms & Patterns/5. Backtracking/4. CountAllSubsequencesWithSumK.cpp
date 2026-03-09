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
	int countAllSubsequencesWithSumKUtil(vector<int>& A, int index, int &sum, int& K) {
		
		//base case: reached the end of the input list so push the current subsequnce to the result
		if (index == A.size()) {
			if (sum == K) {
				return 1;
			}
			return 0;
		}

		//include
		sum = sum + A[index];
		int include = countAllSubsequencesWithSumKUtil(A, index + 1, sum, K);
		sum = sum - A[index];
		
		//exclude
		int exclude = countAllSubsequencesWithSumKUtil(A, index + 1, sum, K);
		return include + exclude;
	}
public:
	int countAllSubsequencesWithSumK(vector<int>& A, int K) {
		int sum = 0;
		return countAllSubsequencesWithSumKUtil(A, 0, sum, K);
	}
};

int main()
{
	Solution obj;
	vector<int> A = { 1,2,3 };
	int allSubsequencesCount = obj.countAllSubsequencesWithSumK(A, 3);
	cout << allSubsequencesCount << endl;
	return 0;
}