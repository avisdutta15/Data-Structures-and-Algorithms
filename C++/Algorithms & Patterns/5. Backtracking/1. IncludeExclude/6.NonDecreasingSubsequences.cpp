#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given an integer array nums, return all the different possible non-decreasing subsequences of 
	the given array with at least two elements. You may return the answer in any order.


	Examples:
	---------
	Input: nums = [4,6,7,7]
	Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]

	Input: nums = [2,2,2]
	Input: nums = [4,4,3,2,1]
	Output: [[4,4]]


	Approach:
	----------
	1. Include and exclude
		Keep a set of vectors.
		The set will discard the duplicates like [4,6,7] [4,6,7]

		Time Complexity: O(n^2 . 2^n)
			Every time you find a valid subsequence, you insert it into the std::set.
			Inserting an element into a balanced binary search tree (which std::set uses under the hood) 
			takes O(log S) time, where S is the size of the set. The maximum size of the set is 2^n, so log(2^n) = n.
			
			Furthermore, each comparison inside the BST involves comparing two vector<int> objects, 
			which takes up to O(n) time.Therefore, a single insertion takes O(n . n) = O(n^2) time. 
			
			Across 2^n elements, this becomes O(n^2 . 2^n).

		Space Complexity: O(n . 2^n)
			The global set stores up to 2^n subsequences, and each subsequence can have a maximum 
			length of n. This requires O(n . 2^n) space.

	2. For loop based: (starting from idx)
		If we look at the for loop based recursion tree:
									     i
										{4,6,7a,7b}                       ---- level : 0  [4,
									      /
								  i		 /
							  {4, 6, 7a, 7b}							  ---- level : 1  [4, 6
							      /
							     /
								i
						{4, 6, 7a, 7b}									  ---- level : 2  [4, 6, 7
						     /
							/   i
					{4, 6, 7a, 7b}										  ---- level : 3  [4, 6, 7, 7]

		After exploring level 3, when the control goes back to level 2, it processes 7b and adds it to the ans.
		This is where a duplicate subsequence is created. We already had {4, 6, 7a}, now we inserted {4, 6, 7b}
		How can we identify that at each level index, we only place distinct A[i]?
		If the input array would have been sorted, we could have used something like
			if(i > idx && A[i] == A[i-1])		//if this A[i] is a duplicate
				continue;
		But we know that the input will not be sorted. so we keep a hashset at each level.

		ans.push(subseq);
		unordered_set hs[]
		for(i=idx; i<n; i++)
			hs.contains(A[i])
				continue;
			hs.insert(A[i]);
			//other conditions
			subseq.insert(A[i]);
			solve(i+1);

		Time Complexity : O(n.2^n) -> 2^n subsequences and at each base case, we do a n times copy operation
		Space Complexity :
			Output Space: The final ans array still requires O(n . 2^n) space to store all the valid combinations.
			Auxiliary Space: The recursion depth is at most $n$, taking O(n) stack space.
							 Over n levels, each unordered_map is still just O(n) space.
							 Total n^2

*/

class Solution {
private:
	void solve(vector<int>& A, vector<int>& subsequence, set<vector<int>>& allSubsequences, int i) {
		if (i == A.size()) {
			if (subsequence.size() >= 2) {
				allSubsequences.insert(subsequence);
			}
			return;
		}

		//include
		//condition?=Yes canRepeat?=No
		if (subsequence.size() == 0 || (subsequence[subsequence.size() - 1] <= A[i])) {
			subsequence.push_back(A[i]);
			solve(A, subsequence, allSubsequences, i + 1);
			subsequence.pop_back();
		}

		//exclude
		solve(A, subsequence, allSubsequences, i + 1);
	}
public:
	vector<vector<int>> findSubsequences(vector<int>& nums) {
		int index = 0;
		vector<int> subsequence;
		set<vector<int>> allSubsequences;
		vector<vector<int>> ans;
		solve(nums, subsequence, allSubsequences, index);
		for (auto s : allSubsequences) {
			ans.push_back(s);
		}
		return ans;
	}
};

class Solution2 {
private:
	void solve(vector<int>& A, vector<int>& subsequence, vector<vector<int>>& allSubsequences, int idx) {
		if (idx > A.size())
			return;

		//collect the ans at each level
		if (subsequence.size() >= 2) {
			allSubsequences.push_back(subsequence);
		}

		//have a hash set to remove duplicate calls at each level
		unordered_set<int> hs;
		for (int i = idx; i < A.size(); i++) {

			//if this number is already seen at this level, so skip
			if (hs.find(A[i]) != hs.end())
				continue;
			
			if (subsequence.size() == 0 || subsequence[subsequence.size() - 1] <= A[i])
			{
				hs.insert(A[i]);
				subsequence.push_back(A[i]);
				solve(A, subsequence, allSubsequences, i + 1);
				subsequence.pop_back();
			}			
		}
	}
public:
	vector<vector<int>> findSubsequences(vector<int>& nums) {
		int index = 0;
		vector<int> subsequence;
		vector<vector<int>> allSubsequences;
		solve(nums, subsequence, allSubsequences, index);
		return allSubsequences;
	}
};


int main() {
	Solution obj;
	vector<int> A = { 4, 6, 7, 7 };
	vector<int> B = { 4, 4, 3, 2, 1 };
	auto ans = obj.findSubsequences(A);
	for (auto v : ans) {
		for (int i : v) cout << i << " ";
		cout << endl;
	}

	cout << endl;

	ans = obj.findSubsequences(B);
	for (auto v : ans) {
		for (int i : v) cout << i << " ";
		cout << endl;
	}
	
	cout << endl;

	Solution2 obj2;
	A = { 4, 6, 7, 7 };
	ans.clear();
	ans = obj2.findSubsequences(A);
	for (auto v : ans) {
		for (int i : v) cout << i << " ";
		cout << endl;
	}

	cout << endl;

	ans = obj2.findSubsequences(B);
	for (auto v : ans) {
		for (int i : v) cout << i << " ";
		cout << endl;
	}
	return 0;
}