#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;

/*
	Problem Statement:
	-----------------
	Calculate prefix sum of the given array. prefix_sum[i] = sum (A[0], A[1],...A[i])

	A[]			 = [1, 2, 3,  4,  5]
	prefix_sum[] = [1, 3, 6, 10, 15] 

	Examples:
	---------


	Approach:
	---------

*/

class Solution {
public:
	vector<int> calculatePrefixSum(vector<int>& A) {
		vector<int> prefixSum(A.size(), 0);

		//initialize
		prefixSum[0] = A[0];

		//traverse rest of the array
		for (int i = 1; i < A.size(); i++) {
			prefixSum[i] = prefixSum[i - 1] + A[i];
		}

		return prefixSum;
	}
};

int main() {
	Solution obj;
	vector<int> A = {1, 2, 3, 4, 5};
	auto prefixSum = obj.calculatePrefixSum(A);
	
	cout << "Original Array: \t";
	for (int i : A)
		cout << i << "\t";

	cout << endl;
	
	cout << "Prefix Sum: \t\t";
	for (int i : prefixSum)
		cout << i << "\t";

	return 0;
}