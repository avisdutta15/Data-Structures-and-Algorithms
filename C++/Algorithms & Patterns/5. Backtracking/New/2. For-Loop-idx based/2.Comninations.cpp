#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

/*
	Problem Statement:
	-----------------
	Given two integers n and k, return all possible combinations of k numbers chosen from the range [1, n].
    You may return the answer in any order.
     

	Examples:
	---------
	Input: n = 4, k = 2
    Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
    Explanation: There are 4 choose 2 = 6 total combinations.
    Note that combinations are unordered, i.e., [1,2] and [2,1] are considered to be the same combination.

    Input: n = 1, k = 1
    Output: [[1]]
    Explanation: There is 1 choose 1 = 1 total combination.

	Approach:
	----------
	1. Include and exclude
    2. For-loop based
*/

// Using Include/Exclude
class Solution {
private:
    void solve(int num, vector<int>& combination, vector<vector<int>>& combinations, int n, int k)
    {
        //base case:
        //at the end of the recursion tree, check the size of the combination
        //we cannot short circuit like the for-loop.
        if (num > n) {
            if (combination.size() == k) {
                combinations.push_back(combination);
            }
            return;
        }

        //include num
        combination.push_back(num);
        solve(num + 1, combination, combinations, n, k);
        combination.pop_back();

        //exclude num
        solve(num + 1, combination, combinations, n, k);
    }
public:
    vector<vector<int>> combine(int n, int k) {
        vector<int> combination;
        vector<vector<int>> combinations;
        solve(1, combination, combinations, n, k);

        return combinations;
    }
};

// Using For-loop
class Solution2 {
private:
    void solve(int idx, vector<int>& combination, vector<vector<int>>& combinations, int n, int k)
    {
        //once we get a combination of size k, we add it to result
        //we then shortcircuit from here (return) we dont want to explore
        //any combination whose size will be > k
        if (combination.size() == k) {
            combinations.push_back(combination);
            return;
        }

        for (int i = idx; i <= n; i++) {
            combination.push_back(i);
            solve(i + 1, combination, combinations, n, k);
            combination.pop_back();
        }
    }
public:
    vector<vector<int>> combine(int n, int k) {
        vector<int> combination;
        vector<vector<int>> combinations;
        solve(1, combination, combinations, n, k);

        return combinations;
    }
};

int main() {
	Solution obj;
    auto ans = obj.combine(4, 2);
    for (auto v : ans) {
        for (auto i : v)
            cout << i << " ";
        cout << endl;
    }
	cout << endl;

    Solution2 obj2;
    ans = obj2.combine(4, 2);
    for (auto v : ans) {
        for (auto i : v)
            cout << i << " ";
        cout << endl;
    }
    cout << endl;

	return 0;
}