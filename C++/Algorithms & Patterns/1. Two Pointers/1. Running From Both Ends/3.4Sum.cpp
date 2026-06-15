#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

/*
	Problem Statement:
	------------------
	Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:
		- 0 <= a, b, c, d < n
		- a, b, c, and d are distinct.
		- nums[a] + nums[b] + nums[c] + nums[d] == target
	You may return the answer in any order.

	Examples:
	--------
	Example 1:
	Input: nums = [1,0,-1,0,-2,2], target = 0
	Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

	Example 2:
	Input: nums = [2,2,2,2,2], target = 8
	Output: [[2,2,2,2]]

	Constraints:
	------------
	1 <= nums.length <= 200
	-10^9 <= nums[i] <= 10^9
	-10^9 <= target <= 10^9

	Approach:
	----------
	- Sort the array first
	- Fix the first element, and use two pointers approach to find the other two elements
	- Skip duplicates at each step to avoid duplicate triplets.
	-    How to skip duplicates?
	-        We are standing at i. Ask have we seen this element before? If yes, that means we have
	-        already processed for this element. So skip it.
	-        [-2, -2, 1, 1, 0, 0]
	-          i      j        k
	-        Now we need to move j and k
	-        [-2, -2, 1, 1, 0, 0]
	-          i         j  k
	-        Should we process this j and k? No, because A[j] == A[j-1] and we have already
	-        processed A[j-1] so processing A[j] will yield a duplicate result. Hence we move j i.e. j++
	-        Similarly for k. Since A[k] == A[k+1] and we have already processed A[k+1], so processing
	-        it will yield a duplicate result. Hence we move k. i.e. k--
	-        We will follow the same thing for i.

	Time Complexity -
		Sorting - O(NlogN)
			  +
		for loop - O(N)
			  X
		for loop - O(N)
			  X
		while loop - O(N)
		= O(NlogN) + O(N^3)

	Space Complexity - O(1)
*/

class Solution {
public:
	vector<vector<int>> fourSum(vector<int>& A, int target) {
		sort(A.begin(), A.end());
		vector<vector<int>> ans;

		int N = A.size();

		// 4 Sum
		for (int i = 0; i <= N - 4; i++) {
			// skip duplicates for i
			if (i > 0 && A[i] == A[i - 1])
				continue;

			// 3 Sum
			for (int j = i + 1; j <= N - 3; j++) {
				// skip duplicates for j
				if (j != i + 1 && A[j] == A[j - 1])
					continue;

				int k = j + 1;
				int l = N - 1;

				// 2 Sum
				while (k < l) {
					// skip duplicates for k
					if (k != j + 1 && A[k] == A[k - 1])
						k++;
					else if (l != N - 1 && A[l] == A[l + 1])
						l--;
					else {
						long long sum = (long long)A[i] + (long long)A[j] + (long long)A[k] + (long long)A[l];
						if (sum == target) {
							ans.push_back({ A[i], A[j], A[k], A[l] });
							k++;
							l--;
						}
						else if (sum < target)
							k++;
						else
							l--;
					}
				}
			}
		}
		return ans;
	}
};

int main()
{
	Solution obj;
	vector<int> A = { 1,0,-1,0,-2,2 };
	auto ans = obj.fourSum(A, 0);
	for (auto v : ans) {
		for (auto i : v)
			cout << i << " ";
		cout << endl;
	}
}
