#include <iostream>
#include <stack>
#include <algorithm>
#include <unordered_set>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given an array arr[], find the Previous Smaller Element (PSE) for every element in the array.
		1. The Previous Smaller Element of an element x is defined as the first element to its left
		   in the array that is smaller than x.
		2. If no such element exists for a particular position, the PSE should be considered as -1.

	Examples:
	---------
	Input: arr[] = [1, 6, 2]
	Output: [-1, 1, 1]
	Explanation: For the first element 1, there is no element to its left, so the result is -1.
	For 6, the previous smaller element is 1. For 2, the previous smaller element is also 1, since
	it is the closest smaller number when looking left.

	Input: arr[] = [1, 5, 0, 3, 4, 5]
	Output: [-1, 1, -1, 0, 3, 4]
	Explanation:
	For 1, no element on the left → -1
	For 5, the previous smaller element is 1
	For 0, no smaller element on the left → -1
	For 3, the previous smaller element is 0
	For 4, the previous smaller element is 3
	For the last 5, the previous smaller element is 4

	Approach 1:
	-----------
	The idea is to use two loops: for each element, check the elements on its left to find the
	previous smaller one. If none exists, store -1.
	T.C. - O(N^2). S.C. - O(1)

	Approach 2:
	-----------
	The idea is to use a monotonic increasing stack. We traverse the array from left to right.
	For each element, we pop elements from the stack that are greater than or equal to it, since
	they cannot be the previous smaller element. If the stack is not empty, the top of the stack
	is the previous smaller element. Finally, we push the current element onto the stack.
	T.C. - O(N). S.C. - O(N)
*/

class Solution {
public:
	vector<int> previousSmallerElementToLeft(const vector<int>& A) {
		if (A.size() == 1)
			return vector<int>();

		vector<int> pgel(A.size(), -1);
		for (int i = 0; i < A.size(); i++) {
			for (int j = i - 1; j >= 0; j--) {
				if (A[j] < A[i]) {
					pgel[i] = A[j];
					break;
				}
			}
		}
		return pgel;
	}

	vector<int> previousSmallerElementToLeftOptimized(const vector<int>& A) {
		if (A.size() == 1)
			return vector<int>();

		vector<int> pgel(A.size(), -1);
		stack<int> stack;

		for (int i = 0; i < A.size(); i++) {
			if (stack.empty()) {
				pgel[i] = -1;
				stack.push(A[i]);
			}
			else if (stack.top() < A[i]) {
				pgel[i] = stack.top();
				stack.push(A[i]);
			}
			else {
				while (!stack.empty() && stack.top() >= A[i])
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
	auto nser = obj.previousSmallerElementToLeft(A);

	cout << "Original Array: \t\t";
	for (int i : A)
		cout << i << "\t";

	cout << endl;

	cout << "Previous Smaller To Left: \t";
	for (int i : nser)
		cout << i << "\t";

	cout << endl;
	//Test 2
	A = { 10, 4, 2, 10, 20, 40, 12 };
	nser = obj.previousSmallerElementToLeftOptimized(A);

	cout << "Original Array: \t\t";
	for (int i : A)
		cout << i << "\t";

	cout << endl;

	cout << "Previous Smaller To Left: \t";
	for (int i : nser)
		cout << i << "\t";
	return 0;
}