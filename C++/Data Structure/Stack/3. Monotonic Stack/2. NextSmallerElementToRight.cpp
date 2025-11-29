#include <iostream>
#include <stack>
#include <algorithm>
#include <unordered_set>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given an array arr[] of integers, find the Next Smaller Element (NSE) for each element in the array.

	1. The Next Smaller Element of an element x is defined as the first element to the right of x in 
	   the array that is strictly smaller than x.
	2. If no such element exists for a particular position, the NSE should be considered as -1.

	Examples:
	---------
	Input: arr[] = [4, 8, 5, 2, 25]
	Output:		   [2, 5, 2, -1, -1]
	Explanation: 
	The first element smaller than 4 having index > 0 is 2.
	The first element smaller than 8 having index > 1 is 5.
	The first element smaller than 5 having index > 2 is 2.
	There are no elements smaller than 2 having index > 3.
	There are no elements smaller than 25 having index > 4.

	Input: arr[] = [13, 7, 6, 12]
	Output:		   [7, 6, -1, -1]
	Explanation: 
	The first element smaller than 13 having index > 0 is 7.
	The first element smaller than 7 having index > 1 is 6.
	There are no elements smaller than 6 having index > 2.
	There are no elements smaller than 12 having index > 3.

	Approach 1:
	-----------
	The idea is to look at all the elements to its right and check if there's a smaller element for
	each element in the array. If we find one, we store it as the next smaller element. If no smaller
	element is found, we store -1. This is done using two nested loops: the outer loop goes through
	each element, and the inner loop searches the rest of the array for a smaller element.
    T.C. - O(N^2). S.C. - O(1)

	Approach 2:
	-----------
	The idea is to use a monotonic increasing stack to find the next smaller element. We traverse the 
	array from right to left. For each element, we remove all elements from the stack that are greater 
	than or equal to it, since they cannot be the next smaller element. If the stack is not empty after
	this, the top element of the stack becomes the next smaller element for the current element. 
	We then push the current element onto the stack.
    T.C. - O(N). S.C. - O(N)
*/

class Solution {
public:
	vector<int> nextSmallerToRight(const vector<int>& A) {
		if (A.size() == 1)
			return vector<int>();

		vector<int> nser(A.size(), -1);
		for (int i = 0; i < A.size(); i++) {
			for (int j = i + 1; j < A.size(); j++) {
				if (A[j] < A[i]) {
					nser[i] = A[j];
					break;
				}
			}
		}
		return nser;
	}

	vector<int> nextSmallerToRightOptimized(const vector<int>& A) {
		if (A.size() == 1)
			return vector<int>();

		vector<int> nser(A.size(), -1);
		stack<int> stack;

		for (int i = A.size() - 1; i >= 0; i--) {
			if (stack.empty()) {
				nser[i] = -1;
				stack.push(A[i]);
			}
			else if(stack.top() < A[i]) {
				nser[i] = stack.top();
				stack.push(A[i]);
			}
			else {
				while (!stack.empty() && stack.top() >= A[i])
					stack.pop();
				if (stack.empty()) {
					nser[i] = -1;
					stack.push(A[i]);
				}
				else {
					nser[i] = stack.top();
					stack.push(A[i]);
				}
			}
		}
		return nser;
	}
};

int main() {
	Solution obj;
	//Test 1
	vector<int> A = { 4, 8, 5, 2, 25 };
	auto nser = obj.nextSmallerToRight(A);

	cout << "Original Array: \t\t";
	for (int i : A)
		cout << i << "\t";

	cout << endl;

	cout << "Next Smaller To Right: \t\t";
	for (int i : nser)
		cout << i << "\t";

	cout << endl;
	//Test 2
	A = { 4, 8, 5, 2, 25 };
	nser = obj.nextSmallerToRightOptimized(A);

	cout << "Original Array: \t\t";
	for (int i : A)
		cout << i << "\t";

	cout << endl;

	cout << "Next Smaller To Right: \t\t";
	for (int i : nser)
		cout << i << "\t";
	return 0;
}