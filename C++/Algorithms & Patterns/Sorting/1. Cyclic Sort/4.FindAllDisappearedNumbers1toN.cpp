#include <iostream>
#include <vector>

using namespace std;

/*
    Problem Statement:
    Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the integers in the range [1, n] that do not appear in nums.

    Examples:
    Input: nums = [4,3,2,7,8,2,3,1]
    Output: [5,6]

    Input: nums = [1,1]
    Output: [2]

    Approach:
    Since we have numbers bound in a range, that means we can use cyclic sort
    to sort the array and then traverse it to find which index does not have correct value.

    After sorting:                              1 2 3 4 3 2 7 8
    Index:                                      0 1 2 3 4 5 6 7
    If no missing then we would have values:    1 2 3 4 5 6 7 8
        
    This means at index i do we have element with value i+1?
    if no then missing value is i+1

    Time Complexity: O(n)
    Space Complexity: O(1)
    
*/


class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& A) {
        int N = A.size();

        for (int i = 0; i < N; i++) {
            int correctIndexOfAi = A[i] - 1;

            //try to place Ai in its correct Place
            while (A[i] != A[correctIndexOfAi]) {
                swap(A[i], A[correctIndexOfAi]);
                correctIndexOfAi = A[i] - 1;
            }
        }

        //after sorting: 1 2 3 4 3 2 7 8 
        //index:         0 1 2 3 4 5 6 7
        //if no missing: 1 2 3 4 5 6 7 8
        vector<int> ans;
        //This means at index i do we have element with value i+1?
        //if no then missing value is i+1
        for (int i = 0; i < N; i++) {
            if (A[i] != i + 1)
                ans.push_back(i + 1);
        }

        return ans;
    }
};


int main()
{
    Solution obj;
    vector<int> A = { 4,3,2,7,8,2,3,1 };
    vector<int> missing = obj.findDisappearedNumbers(A);
    for (int i : missing) {
        cout << i << " ";
    }
    cout << endl;
    
    A = { 1,1 };
    missing = obj.findDisappearedNumbers(A);
    for (int i : missing) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}