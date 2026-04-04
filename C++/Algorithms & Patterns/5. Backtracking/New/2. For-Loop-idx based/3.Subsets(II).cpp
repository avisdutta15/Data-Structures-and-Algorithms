#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

/*
    Problem Statement:
    -----------------
    Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
    The solution set must not contain duplicate subsets. Return the solution in any order.

    Examples:
    ---------
    Input: nums = [1,2,2]
    Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]

    Input: nums = [0]
    Output: [[],[0]]

    Approach:
    ----------
    Sort the input and 
    1. Include/Exclude -> Skip duplicates and then call exclude
    2. For - loop based: start idx
*/

// Using Include/Exclude
class Solution {
    void solve(vector<int>& A, int i, vector<int>& subset, vector<vector<int>>& allSubsets) {
        if (i == A.size()) {
            allSubsets.push_back(subset);
            return;
        }

        //include
        subset.push_back(A[i]);
        solve(A, i + 1, subset, allSubsets);
        subset.pop_back();

        //                       i             i
        //skip the duplicates [1,2,2,3] and [1,2,3]
        while (i + 1 < A.size() && A[i] == A[i + 1])
            i++;

        solve(A, i + 1, subset, allSubsets);
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& A) {
        vector<int> subset;
        vector<vector<int>> allSubsets;
        sort(A.begin(), A.end());       //IMP: This helps to eliminate the dups 
        solve(A, 0, subset, allSubsets);
        return allSubsets;
    }
};

// Using For-loop
class Solution2 {
    void solve(vector<int>& A, int idx, vector<int>& subset, vector<vector<int>>& allSubsets) {
        allSubsets.push_back(subset);

        for (int i = idx; i < A.size(); i++) {
            //skip the duplicates
            if (i > idx && A[i - 1] == A[i])
                continue;
            subset.push_back(A[i]);
            solve(A, i + 1, subset, allSubsets);
            subset.pop_back();
        }
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& A) {
        vector<int> subset;
        vector<vector<int>> allSubsets;
        sort(A.begin(), A.end());       //IMP: This helps to eliminate the dups 
        solve(A, 0, subset, allSubsets);
        return allSubsets;
    }
};

int main() {
    Solution obj;
    vector<int> A = { 1, 2, 2, 3 };
    auto ans = obj.subsetsWithDup(A);
    for (auto v : ans) {
        for(auto i: v)
            cout << i << " ";
        cout << endl;
    }
    cout << endl;

    return 0;
}