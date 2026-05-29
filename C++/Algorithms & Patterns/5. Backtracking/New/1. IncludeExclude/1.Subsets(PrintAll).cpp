#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given an array arr[]. The task is to find all the possible subsequences of the given array using recursion.

	Examples:
	---------
	Input: arr[] = [1, 2, 3]
	Output : [3], [2], [2, 3], [1], [1, 3], [1, 2], [1, 2, 3], []

	Input: arr[] = [1, 2]
	Output : [2], [1], [1, 2], []

	Approach:
	----------
	For every element in the array, there are two choices, either to include it in the subsequence or not include it.
	Apply this for every element in the array starting from index 0 until we reach the last index.
	Print the subsequence once the last index is reached.

	Time Complexity: O(N.2^N)
	1. The Recursion Tree (2^N calls)
		At every single element in the array A, your recursive function makes a choice:
			- Include the element in the subsequence.
			- Exclude the element from the subsequence.
		Because there are 2 choices for every single one of the N elements, the total
		number of possible subsequences generated is 2^N.

		This means your recursion tree will have exactly 2^N leaf nodes (base cases).

	2. Work Done at the Base Case (O(N) time)
		In C++, pushing a vector into a vector<vector<int>> does not just pass a reference;
		it makes a deep copy of the entire subsequence vector.
	Total Time Complexity : O(N.2^N)

	Space Complexity:
		Call Stack: The maximum depth of the recursion tree is N, which takes O(N) auxiliary stack space.
*/

class Solution {
private:
	void backtrack(const vector<int>& A, vector<vector<int>>& allSubsets, vector<int>& current_subset, int i) {

		//base case: reached the end of the input list so push the current subsequnce to the result
		if (i == A.size()) {
			allSubsets.push_back(current_subset);
			return;
		}

		//include
		//condition? = No, canRepeat? = No
		current_subset.push_back(A[i]);
		backtrack(A, allSubsets, current_subset, i + 1);
		current_subset.pop_back();	//backtrack

		//exclude
		backtrack(A, allSubsets, current_subset, i + 1);
	}
public:
	void printAllSubsets(const vector<int>& A) {
		vector<vector<int>> allSubsets;
		vector<int> current_subset;
		backtrack(A, allSubsets, current_subset, 0);

		for (auto v : allSubsets) {
			// print the empty subset
			if (v.size() == 0){
				cout << "[]" << endl;
			}
			// print the subset
			else {
				for (auto i : v)
					cout << i << " ";
			}
			cout << endl;
		}
	}
};

int main() {
	Solution obj;
	vector<int> A = { 1, 2, 3 };
	obj.printAllSubsets(A);
}
