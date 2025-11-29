#include <iostream>
#include <stack>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given a circular integer array nums (i.e., the next element of nums[nums.length - 1] 
	is nums[0]), return the next greater number for every element in nums.

	The next greater number of a number x is the first greater number to its traversing-order 
	next in the array, which means you could search circularly to find its next greater number. 
	If it doesn't exist, return -1 for this number.

	Examples:
	---------
	Input: nums = [1,2,1]
	Output: [2,-1,2]
	Explanation: The first 1's next greater number is 2; 
	The number 2 can't find next greater number. 
	The second 1's next greater number needs to search circularly, which is also 2.

	Input: nums = [1,2,3,4,3]
	Output: [2,3,4,-1,4]

	Approach:
	--------
	This is a circular array:
	For circular array we imagine the array to be doubled.
	[i.....n-1][i......n-1]
	So there are 2n elements.
	nge[n]
	for(int i=2n; i>=0; i--)
		int j = i%n;		//this is the actual element we will calculate the nge for.
	
 	T.C. - O(2n). S.C. - O(2n)
*/

class Solution {
public:
	vector<int> nextGreaterElements(vector<int>& nums) {
		vector<int> nge(nums.size(), -1);
		stack<int> stack;
		int n = nums.size();
		for (int i = (2 * n) - 1; i >= 0; i--) {
			int j = i % n;
			if (stack.empty()) {
				nge[j] = -1;
				stack.push(nums[j]);
			}
			else if (stack.top() > nums[j]) {
				nge[j] = stack.top();
				stack.push(nums[j]);
			}
			else {
				while (!stack.empty() && stack.top() <= nums[j])
					stack.pop();
				if (stack.empty())
					nge[j] = -1;
				else
					nge[j] = stack.top();
				stack.push(nums[j]);
			}
		}
		return nge;
	}
};

int main() {
	Solution obj;
	//Test 1
	vector<int> nums1 = { 1,2,1 };
	auto ngtr = obj.nextGreaterElements(nums1);

	cout << "Original Array (nums1): \t";
	for (int i : nums1)
		cout << i << "\t";

	cout << endl;

	cout << "Next Greater To Right: \t\t";
	for (int i : ngtr)
		cout << i << "\t";

	cout << endl;

	//Test 2
	nums1 = { 1,2,3,4,3 };
	ngtr = obj.nextGreaterElements(nums1);

	cout << "Original Array (nums1): \t";
	for (int i : nums1)
		cout << i << "\t";

	cout << endl;

	cout << "Next Greater To Right: \t\t";
	for (int i : ngtr)
		cout << i << "\t";

	cout << endl;
	return 0;
}