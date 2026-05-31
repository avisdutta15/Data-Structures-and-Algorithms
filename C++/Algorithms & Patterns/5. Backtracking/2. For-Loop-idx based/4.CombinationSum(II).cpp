#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

/*
    Problem Statement:
    -----------------
    Given a collection of candidate numbers (candidates) and a target number (target), 
    find all unique combinations in candidates where the candidate numbers sum to target.
    Each number in candidates may only be used once in the combination.
    Note: The solution set must not contain duplicate combinations.

    Examples:
    ---------
    Input: candidates = [10,1,2,7,6,1,5], target = 8
    Output: 
    [
        [1,1,6],
        [1,2,5],
        [1,7],
        [2,6]
    ]

    Input: candidates = [2,5,2,1,2], target = 5
    Output:
    [
        [1,2,2],
        [5]
    ]

    Constraints:
        1 <= candidates.length <= 100
        1 <= candidates[i] <= 50
        1 <= target <= 30

    Approach:
    ----------
    Sort the input and 
    1. Include/Exclude -> Skip duplicates and then call exclude
    2. For - loop based: start idx
*/

//include/exclude based
class Solution {
private:
    void solve(vector<int>& A, int i, vector<int>& combination, vector<vector<int>>& allCombinations, int target) {
        //Base Case: 
        //1. Target became 0 i.e. target reached
        if (target == 0) {
            allCombinations.push_back(combination);
            return;
        }

        //2. target or index are out of bounds
        if (target < 0 || i>A.size()) {
            return;
        }

        //include A[i]
        if (target >= A[i]) {
            combination.push_back(A[i]);
            solve(A, i + 1, combination, allCombinations, target - A[i]);
            combination.pop_back();
        }

        //skip duplicates
        while (i + 1 < A.size() && A[i] == A[i + 1])
            i++;

        //exclude A[i]
        solve(A, i + 1, combination, allCombinations, target);
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& A, int target) {
        vector<vector<int>> allCombinations;
        vector<int> combination;
        sort(A.begin(), A.end());   //IMP: This helps to eliminate the dups 
        solve(A, 0, combination, allCombinations, target);
        return allCombinations;
    }
};

// For-loop based: start idx
class Solution2 {
private:
    void solve(vector<int>& A, int idx, vector<int>& combination, vector<vector<int>>& allCombinations, int target) {
        //Base Case: 
        //1. Target became 0 i.e. target reached
        if (target == 0) {
            allCombinations.push_back(combination);
            return;
        }

        //2. target or index are out of bounds
        if (target < 0 || idx>A.size()) {
            return;
        }

        for (int i = idx; i < A.size(); i++) {
            //skip duplicates
            if (i > idx && A[i] == A[i - 1])
                continue;

            //include if target can be reached
            if (target >= A[i]) {
                combination.push_back(A[i]);
                solve(A, i + 1, combination, allCombinations, target - A[i]);
                combination.pop_back();
            }
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& A, int target) {
        vector<vector<int>> allCombinations;
        vector<int> combination;
        sort(A.begin(), A.end());   //IMP: This helps to eliminate the dups 
        solve(A, 0, combination, allCombinations, target);
        return allCombinations;
    }
};
int main() {
    Solution obj;
    vector<int> A = { 1, 2, 2, 3 };
    auto ans = obj.combinationSum2(A);
    for (auto v : ans) {
        for(auto i: v)
            cout << i << " ";
        cout << endl;
    }
    cout << endl;

    return 0;
}