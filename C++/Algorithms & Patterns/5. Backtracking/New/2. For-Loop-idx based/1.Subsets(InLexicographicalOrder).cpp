#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

/*
    Problem Statement:
    -----------------
    Print the powerset of a set in lexigcographic order.

    Examples:
    ---------
    Input: A = [1, 2, 3]
    Output: [[1],[1,2],[1,2,3],[1,3],[2],[2,3],[3]]

    Approach:
    ----------
    For - loop based: start idx

    Why start idx? A-[1,2,3]
    We know [2,1] is equal to [1,2].
    Since we have already seen [1,2] in the recursion tree, we dont want to 
    again start from i=0 and pick 1 (which will finally give [2,1]) 
    So start from idx(which was passed as i+1) i.e. 3 and process [2,3]


    NOTE: THIS PROBLEM ALSO SHOWS THAT WE CAN SOLVE THE SUBSETS(INCLUDE/EXCLUDE PATTERN)
    WITH FOR-LOOP PATTERN.

    WHERE IS THE INCLUDE? 
            subset.push_back(A[i]);
            solve(A, i + 1, subset, allSubsets);
    WHERE IS THE EXCLUDE - Pop + loop increment?
            1. subset.pop_back();

            2. Think about what a for loop does. Let's say your array is [A, B, C], and your loop is:
                for i=idx; i<n; i++:
            When i = 0, you include A, recurse down that branch, and eventually return.
            When the loop increments to i = 1, you are now including B.
            By the very nature of moving on to B, you have implicitly excluded A from this specific 
            position in your combination. You didn't need a recursive call to say "skip A"; the loop 
            simply skipping ahead to evaluate B accomplished the exact same thing.
*/

class Solution {
private:
    void solve(vector<int> &A, int idx, vector<int> &subset, vector<vector<int>> &allSubsets) {
        //collect the subset at every node of the recursion tree.
        allSubsets.push_back(subset);

        for (int i = idx; i < A.size(); i++) {
            subset.push_back(A[i]);
            solve(A, i + 1, subset, allSubsets);
            subset.pop_back();
        }
    }

public:
    vector<vector<int>> subsetsInLexicographicalOrder(vector<int> A) {
        vector<vector<int>> allSubsets;
        vector<int> subset;
        solve(A, 0, subset, allSubsets);
        return allSubsets;
    }
};


int main() {
    Solution obj;
    vector<int> A = { 1, 2, 3 };
    auto ans = obj.subsetsInLexicographicalOrder(A);
    for (auto v : ans) {
        for(auto i: v)
            cout << i << " ";
        cout << endl;
    }
    cout << endl;

    return 0;
}