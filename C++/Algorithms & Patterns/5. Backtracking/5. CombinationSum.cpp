#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given an array of distinct integers candidates and a target integer target, return a list of all unique 
	combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.

	The same number may be chosen from candidates an unlimited number of times. 
	Two combinations are unique if the frequency of at least one of the chosen numbers is different.

	The test cases are generated such that the number of unique combinations that sum up to 
	target is less than 150 combinations for the given input.


	Examples:
	---------
	Input: candidates = [2,3,6,7], target = 7
	Output: [[2,2,3],[7]]
	Explanation:
	2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
	7 is a candidate, and 7 = 7.
	These are the only two combinations.


	Input: candidates = [2,3,5], target = 8
	Output: [[2,2,2,2],[2,3,3],[3,5]]

	Input: candidates = [2], target = 1
	Output: []

	Approach: 
	----------
	Include and exclude
*/

class Solution {
private:
	void combinationSumUtil(vector<int>& candidates, int i, vector<int>& combination, vector<vector<int>>& result, int &sum, int& target) {
		if (i == candidates.size()) {
			if (sum == target) {
				result.push_back(combination);
			}
			return;
		}

		//include
		//include only if this sum + candidate is less than or equal target else its of no use to pick this candidate.
		if (sum + candidates[i] <= target) {
			combination.push_back(candidates[i]);
			sum = sum + candidates[i];
			combinationSumUtil(candidates, i, combination, result, sum, target);		//not i+1 since I can pick this candidate multiple times
			combination.pop_back();
			sum = sum - candidates[i];
		}

		//exclude
		combinationSumUtil(candidates, i+1, combination, result, sum, target);
	}
public:
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		vector<vector<int>> result;
		vector<int> combination;
		int sum = 0;
		combinationSumUtil(candidates, 0, combination, result, sum, target);
		return result;
	}
};

int main()
{
	Solution obj;
	vector<int> A = { 2,3,6,7 };
	auto sums = obj.combinationSum(A, 7);
	for (vector<int> sum : sums) {
		for (int i : sum) cout << i << " ";
		cout << endl;
	}

	return 0;
}