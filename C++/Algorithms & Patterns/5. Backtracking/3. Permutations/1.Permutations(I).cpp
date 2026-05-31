#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
#include <string.h>

using namespace std;

/*
    Problem Statement:
    -----------------
    Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.
    

    Examples:
    ---------
    Example 1:
    Input: nums = [1,2,3]
    Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

    Example 2:
    Input: nums = [0,1]
    Output: [[0,1],[1,0]]

    Example 3:
    Input: nums = [1]
    Output: [[1]]
    

    Constraints:
    ------------
    1 <= nums.length <= 6
    -10 <= nums[i] <= 10
    All the integers of nums are unique.

    Approach:
    ---------
    For permutations, your thought process is: "I have an empty slot. Out of all the elements I haven't used yet, 
    which one should I put here?" Because you can pick any unused element (not just elements strictly to the right 
    of your current index), you use a for loop that always starts from 0, but you use a boolean array (or a set) 
    called used_in_current_perm to keep track of what is already in your current permutation.

                                              solve(perm=[], used_in_current_perm={})
                            /                               |                              \
                       pick 1                            pick 2                            pick 3
                  solve([1],{1})                     solve([2],{2})                     solve([3],{3})
                  /             \                /                  \               /                  \
             pick 2            pick 3           pick 1            pick 3          pick 1               pick 2
          solve([1,2]{1,2}) solve([1,3]{1,3}) solve([2,1]{2,1}) solve([2,3]{2,3}) solve([3,1]{3,1}) solve([3,2]{3,2})
              |                     |               |                   |                 |                |
           pick 3                 pick 2          pick 3              pick 1           pick 2            pick 1
          [1,2,3]✓               [1,3,2]✓        [2,1,3]✓           [2,3,1]✓         [3,1,2]✓          [3,2,1]✓

*/

class Solution {
private:
    void solve(const vector<int>& nums, vector<int>& current_permutation, vector<bool>& used_in_current_permutation, vector<vector<int>>& all_permutations) {
        if (current_permutation.size() == nums.size()) {
            all_permutations.push_back(current_permutation);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            // if character already used in the current permutation then continue
            if (used_in_current_permutation[i] == true)
                continue;

            // place this character in the current place
            current_permutation.push_back(nums[i]);
            used_in_current_permutation[i] = true;

            // recursively place other characters
            solve(nums, current_permutation, used_in_current_permutation, all_permutations);

            // backtrack
            current_permutation.pop_back();
            used_in_current_permutation[i] = false;
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> current_permutation;
        vector<vector<int>> all_permutations;
        vector<bool> used_in_current_permutation(nums.size(), false);

        solve(nums, current_permutation, used_in_current_permutation, all_permutations);

        return all_permutations;
    }
};

int main() {
    Solution obj;
    vector<int> A = { 1, 2, 3 };
    auto result = obj.permute(A);

    for(auto v : result) {
        for(int i : v)
            cout << i << " ";
        cout << endl;
    }

    return 0;
}
