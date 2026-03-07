#include <iostream>
#include <vector>

using namespace std;

/*
	Problem Statement:
	Given an unsorted integer array nums. Return the smallest positive integer that is not present in nums.
	You must implement an algorithm that runs in O(n) time and uses O(1) auxiliary space.

	Examples:
	Input: nums = [1,2,0]
	Output: 3
	Explanation: The numbers in the range [1,2] are all in the array.

	Input: nums = [3,4,-1,1]
	Output: 2
	Explanation: 1 is in the array but 2 is missing.

	Input: nums = [7,8,9,11,12]
	Output: 1
	Explanation: The smallest positive integer 1 is missing.

	Approach:
	Use cyclic sort to place every element at its correct position and then traverse the array to find the out-of-place element.

	Time Complexity: O(n)
	Space Complexity: O(1)

*/


class Solution {
private:
	void swap(int& a, int& b) {
		int temp = a;
		a = b;
		b = temp;
	}
public:
	int firstMissingPositive(vector<int>& A) {

		int N = A.size();
		for (int i = 0; i < N; i++) {
			int correctIndexOfAi = A[i] - 1;

			while (A[i] > 0 && A[i] < N && A[i] != A[correctIndexOfAi]) {
				swap(A[i], A[correctIndexOfAi]);
				correctIndexOfAi = A[i] - 1;
			}
		}

		for (int i = 0; i < N; i++) {
			if (i != A[i] - 1) {
				return i + 1;
			}
		}
		return N+1;
	}
};


int main()
{
	Solution obj;
	vector<int> A = { 1,2,0 };
	cout << obj.firstMissingPositive(A) << endl;

	A = { 3,4,-1,1 };
	cout << obj.firstMissingPositive(A) << endl;

	A = { 7,8,9,11,12 };
	cout << obj.firstMissingPositive(A) << endl;

	A = { 1,2,3 };
	cout << obj.firstMissingPositive(A) << endl;

	return 0;
}