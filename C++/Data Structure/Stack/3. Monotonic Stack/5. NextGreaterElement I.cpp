#include <iostream>
#include <stack>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/*
	Problem Statement:
	-----------------
	The next greater element of some element x in an array is the first greater element that 
	is to the right of x in the same array.

	You are given two distinct 0-indexed integer arrays nums1 and nums2, where nums1 is a subset 
	of nums2.

	For each 0 <= i < nums1.length, find the index j such that nums1[i] == nums2[j] and determine 
	the next greater element of nums2[j] in nums2. If there is no next greater element, then the 
	answer for this query is -1.

	Return an array ans of length nums1.length such that ans[i] is the next greater element as 
	described above.

	Examples:
	---------
	Example 1:
	Input: nums1 = [4,1,2], 
		   nums2 = [1,3,4,2]
	Output: [-1,3,-1]
	Explanation: The next greater element for each value of nums1 is as follows:
	- 4 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.
	- 1 is underlined in nums2 = [1,3,4,2]. The next greater element is 3.
	- 2 is underlined in nums2 = [1,3,4,2]. There is no next greater element, so the answer is -1.
	
	Example 2:
	Input: nums1 = [2,4], 
		   nums2 = [1,2,3,4]
	Output: [3,-1]
	Explanation: The next greater element for each value of nums1 is as follows:
	- 2 is underlined in nums2 = [1,2,3,4]. The next greater element is 3.
	- 4 is underlined in nums2 = [1,2,3,4]. There is no next greater element, so the answer is -1.

	Approach:
	--------
	Find the NGE for nums2.
	Keep a map<int, int> for nge of nums2.
	For each element of nums1, find the corresponding element in nums2 and its nge.
	
 	T.C. - O(nums1.size() + nums2.size()). S.C. - O(nums1.size() + nums2.size())
*/

class Solution {
	unordered_map<int, int> getNextGreaterElementOfNums2(vector<int>& A) {
		if (A.size() == 0)
			return unordered_map<int, int>();

		stack<int> stack;
		unordered_map<int, int> nge;
		for (int i = A.size() - 1; i >= 0; i--) {
			if (stack.empty()) {
				nge[A[i]] = -1;
				stack.push(A[i]);
			}
			else if (stack.top() > A[i]) {
				nge[A[i]] = stack.top();
				stack.push(A[i]);
			}
			else {
				while (!stack.empty() && stack.top() <= A[i])
					stack.pop();
				if (stack.empty())
					nge[A[i]] = -1;
				else
					nge[A[i]] = stack.top();
				stack.push(A[i]);
			}
		}
		return nge;
	}
public:
	vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
		if (nums1.size() == 0)
			return vector<int>();
		
		auto ngeNums2 = getNextGreaterElementOfNums2(nums2);
		vector<int> nge(nums1.size(), -1);
		for (int i = 0; i < nums1.size(); i++) {
			nge[i] = ngeNums2[nums1[i]];
		}
		return nge;
	}
};

int main() {
	Solution obj;
	//Test 1
	vector<int> nums1 = { 4,1,2 };
	vector<int> nums2 = { 1,3,4,2 };
	auto ngtr = obj.nextGreaterElement(nums1, nums2);

	cout << "Original Array (nums1): \t";
	for (int i : nums1)
		cout << i << "\t";

	cout << endl;

	cout << "Original Array (nums2): \t";
	for (int i : nums2)
		cout << i << "\t";

	cout << endl;

	cout << "Next Greater To Right: \t\t";
	for (int i : ngtr)
		cout << i << "\t";

	cout << endl;

	//Test 2
	nums1 = { 2, 4 };
	nums2 = { 1,2,3,4 };
	ngtr = obj.nextGreaterElement(nums1, nums2);

	cout << "Original Array (nums1): \t";
	for (int i : nums1)
		cout << i << "\t";

	cout << endl;

	cout << "Original Array (nums2): \t";
	for (int i : nums2)
		cout << i << "\t";

	cout << endl;

	cout << "Next Greater To Right: \t\t";
	for (int i : ngtr)
		cout << i << "\t";

	cout << endl;
	return 0;
}