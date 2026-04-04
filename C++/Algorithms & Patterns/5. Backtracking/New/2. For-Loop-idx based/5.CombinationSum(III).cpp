#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

/*
    Problem Statement:
    -----------------
    Find all valid combinations of k numbers that sum up to n such that the following conditions are true:
        - Only numbers 1 through 9 are used.
        - Each number is used at most once.
    Return a list of all possible valid combinations. The list must not contain the same combination twice, 
    and the combinations may be returned in any order.

    Examples:
    ---------
    Input: k = 3, n = 7
    Output: [[1,2,4]]
    Explanation:
    1 + 2 + 4 = 7
    There are no other valid combinations.

    Input: k = 3, n = 9
    Output: [[1,2,6],[1,3,5],[2,3,4]]
    Explanation:
    1 + 2 + 6 = 9
    1 + 3 + 5 = 9
    2 + 3 + 4 = 9
    There are no other valid combinations.

    Input: k = 4, n = 1
    Output: []
    Explanation: There are no valid combinations.
    Using 4 different numbers in the range [1,9], the smallest sum we can get is 
    1+2+3+4 = 10 and since 10 > 1, there are no valid combination.

    Constraints:
        2 <= k <= 9
        1 <= n <= 60

    Approach:
    ----------
    1. Include/Exclude -> short circuit when the size reaches k
    2. For - loop based: start idx -> short circuit when the size reaches k
*/

//include/exclude based
class Solution {
private:
    void solve(int i, int k, vector<int>& combination, vector<vector<int>>& allCombinations, int target) {
        
        //if combination size is K, we short-circuit. We dont go any further.
        if (combination.size() == k) {
            //check if the target has been reached?
            if (target == 0)
                allCombinations.push_back(combination);
            return;
        }

        //if target or the idx is out of bounds: return
        if (target < 0 || i>9)
            return;

        //include
        if (target >= i) {
            combination.push_back(i);
            solve(i + 1, k, combination, allCombinations, target - i);
            combination.pop_back();
        }

        //exclude        
        solve(i + 1, k, combination, allCombinations, target);
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        if (n < k)
            return vector<vector<int>>();

        vector<int> combination;
        vector<vector<int>> allCombinations;
        int total_nums = k;
        int target = n;
        solve(1, k, combination, allCombinations, target);
        return allCombinations;
    }
};
// For-loop based: start idx
class Solution {
private:
    void solve(int idx, int k, vector<int>& combination, vector<vector<int>>& allCombinations, int target) {
        
        //if combination size is K, we short-circuit. We dont go any further.
        if (combination.size() == k) {
            //check if the target has been reached?
            if (target == 0)
                allCombinations.push_back(combination);
            return;
        }

        //if target or the idx is out of bounds: return
        if (target < 0 || idx>9)
            return;
        
        for (int i = idx; i <= 9; i++) {
            if (target >= i) {
                combination.push_back(i);
                solve(i + 1, k, combination, allCombinations, target - i);
                combination.pop_back();
            }
        }
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        if (n < k)
            return vector<vector<int>>();

        vector<int> combination;
        vector<vector<int>> allCombinations;
        int total_nums = k;
        int target = n;
        solve(1, k, combination, allCombinations, target);
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