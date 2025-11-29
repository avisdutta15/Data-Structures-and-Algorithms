#include <iostream>
#include <stack>
#include <algorithm>
#include <unordered_set>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given an array arr[], find the Previous Greater Element (PGE) for every element in the array.
		1. The Previous Greater Element of an element x is defined as the first element to its left
		   in the array that is greater than x.
		2. If no such element exists for a particular position, the PGE should be considered as -1.

	Examples:
	---------
	Input: arr[] = [10, 4, 2, 10, 20, 40, 12]
	Output:		   [-1, 10, 4,-1, -1, -1, 40]
	Explanation:
	For 10 → No elements on the left → -1
	For 4 → Previous greater element is 10 → 10
	For 2 → Previous greater element is 4 → 4
	For 10 → No elements on the left → -1
	For 20 → No element on the left greater than 20 → -1
	For 40 → No element on the left greater than 40 → -1
	For 12 → Previous greater element is 40 → 40

	Input: arr[] = [10, 20, 30, 40]
	Output: [-1, -1, -1, -1]
	Explanation: Since the array is strictly increasing, no element has a greater element
	before it. Hence, all positions are assigned -1.

	Approach 1:
	-----------
	The idea is to use two loops: for each element, check the remaining elements on its right
	to find the next greater one. If none exists, store -1.
	T.C. - O(N^2). S.C. - O(1)

	Approach 2:
	-----------
	The idea is to use a monotonic decreasing stack. We traverse the array from left to right.
	For each element, we pop elements from the stack that are smaller than or equal to it, since
	they cannot be the previous greater element. If the stack is not empty, the top of the stack
	is the previous greater element. Finally, we push the current element onto the stack.
	T.C. - O(N). S.C. - O(N)
*/

class Solution {
public:
	vector<int> previousGreaterElementToLeft(const vector<int>& A) {
		if (A.size() == 1)
			return vector<int>();

		vector<int> pgel(A.size(), -1);
		for (int i = 0; i < A.size(); i++) {
			for (int j = i - 1; j >= 0; j--) {
				if (A[j] > A[i]) {
					pgel[i] = A[j];
					break;
				}
			}
		}
		return pgel;
	}

	vector<int> previousGreaterElementToLeftOptimized(const vector<int>& A) {
		if (A.size() == 1)
			return vector<int>();

		vector<int> pgel(A.size(), -1);
		stack<int> stack;

		for (int i = 0; i < A.size(); i++) {
			if (stack.empty()) {
				pgel[i] = -1;
				stack.push(A[i]);
			}
			else if (stack.top() > A[i]) {
				pgel[i] = stack.top();
				stack.push(A[i]);
			}
			else {
				while (!stack.empty() && stack.top() <= A[i])
					stack.pop();
				if (stack.empty())
					pgel[i] = -1;
				else
					pgel[i] = stack.top();
				stack.push(A[i]);
			}
		}

		return pgel;
	}
};

int main() {
	Solution obj;
	//Test 1
	vector<int> A = { 10, 4, 2, 10, 20, 40, 12 };
	auto nser = obj.previousGreaterElementToLeft(A);

	cout << "Original Array: \t\t";
	for (int i : A)
		cout << i << "\t";

	cout << endl;

	cout << "Previous Greater To Left: \t";
	for (int i : nser)
		cout << i << "\t";

	cout << endl;
	//Test 2
	A = { 10, 4, 2, 10, 20, 40, 12 };
	nser = obj.previousGreaterElementToLeftOptimized(A);

	cout << "Original Array: \t\t";
	for (int i : A)
		cout << i << "\t";

	cout << endl;

	cout << "Previous Greater To Left: \t";
	for (int i : nser)
		cout << i << "\t";
	return 0;
}