#include <iostream>
#include <stack>
#include <algorithm>
#include <unordered_set>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given an array arr[] of integers, determine the Next Greater Element (NGE) for 
    every element in the array, maintaining the order of appearance.

    1. The Next Greater Element for an element x is defined as the first element to the 
    right of x in the array that is strictly greater than x.
    
    2. If no such element exists for an element, its Next Greater Element is -1.

	Examples:
	---------
    Input: arr[] = [1, 3, 2, 4]
    Output: [3, 4, 4, -1]
    Explanation: The next larger element to 1 is 3, 3 is 4, 2 is 4 and for 4, since 
    it doesn't exist, it is -1.

    Input: arr[] = [6, 8, 0, 1, 3]
    Output: [8, -1, 1, 3, -1]
    Explanation: The next larger element to 6 is 8, for 8 there is no larger elements 
    hence it is -1, for 0 it is 1 , for 1 it is 3 and then for 3 there is no larger element on right 
    and hence -1.

	Approach 1:
	-----------
    The idea is to look at all the elements to its right and check if there's a larger element for 
    each element in the array. If we find one, we store it as the next greater element. If no greater 
    element is found, we store -1. This is done using two nested loops: the outer loop goes through 
    each element, and the inner loop searches the rest of the array for a greater element.


    Approach 2:
    -----------
    The idea is to use a monotonic decreasing stack (stack that maintains elements in decreasing order). 
    We traverse the array from right to left. For each element, we pop elements from the stack that are 
    smaller than or equal to it, since they cannot be the next greater element. If the stack is not empty, 
    the top of the stack is the next greater element. Finally, we push the current element onto the stack.
*/

class Solution {
public:
	vector<int> nextGreaterToRight(const vector<int>& A) {
		if (A.size() == 1)
			return vector<int>();

		vector<int> nger(A.size(), -1);
		for (int i = 0; i < A.size(); i++) {
			for (int j = i + 1; j < A.size(); j++) {
				if (A[j] > A[i]) {
					nger[i] = A[j];
					break;
				}
			}
		}
		return nger;
	}

	vector<int> nextGreaterToRightOptimized(const vector<int>& A) {
		if (A.size() == 1)
			return vector<int>();

		vector<int> nger(A.size(), -1);
		stack<int> stack;

		for (int i = A.size() - 1; i > 0; i--) {
			if (stack.empty()) {
				nger[i] = -1;
				stack.push(A[i]);
			}
			else if (stack.top() > A[i]) {
				nger[i] = stack.top();
				stack.push(A[i]);
			}
			else {
				while (!stack.empty() && stack.top() <= A[i])
					stack.pop();
				if (stack.empty())
					nger[i] = -1;
				else
					nger[i] = stack.top();
				stack.push(A[i]);
			}
		}
		return nger;
	}
};

int main() {
	Solution obj;
	//Test 1
	vector<int> A = { 8, 6, 8, 0, 1, 3 };
	auto nger = obj.nextGreaterToRight(A);

	cout << "Original Array: \t\t";
	for (int i : A)
		cout << i << "\t";

	cout << endl;

	cout << "Next Greater To Right: \t\t";
	for (int i : nger)
		cout << i << "\t";

	cout << endl;
	//Test 1
	A = { 8, 6, 8, 0, 1, 3 };
	nger = obj.nextGreaterToRightOptimized(A);

	cout << "Original Array: \t\t";
	for (int i : A)
		cout << i << "\t";

	cout << endl;

	cout << "Next Greater To Right: \t\t";
	for (int i : nger)
		cout << i << "\t";
	return 0;
}