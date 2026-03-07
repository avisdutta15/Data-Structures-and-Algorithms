#include <iostream>
#include <vector>

using namespace std;

/*
    Problem Statement:
    Given an integer array nums of length n where all the integers of nums are in the range [1, n] and each integer appears at most twice, 
    return an array of all the integers that appears twice.
    You must write an algorithm that runs in O(n) time and uses only constant auxiliary space, excluding the space needed to store the output

    Examples:
    Input: nums = [4,3,2,7,8,2,3,1]
    Output: [2,3]

    Input: nums = [1,1,2]
    Output: [1]

    Input: nums = [1]
    Output: []

    Approach:
    Use cyclic sort to place every element at its correct position and then traverse the array to find the out-of-place element.

    Time Complexity: O(n)
    Space Complexity: O(1)
    
*/


class Solution {
private:
    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }
public:
    vector<int> findDuplicates(vector<int>& A) {
        int N = A.size();

        // 1. Cyclic Sort logic
        for (int i = 0; i < N; i++) {
            int correctIndexOfAi = A[i] - 1;
            while (A[i] != A[correctIndexOfAi]) {
                swap(A[i], A[correctIndexOfAi]);
                correctIndexOfAi = A[i] - 1;
            }
        }

        // 2. Find the out-of-place elements
        vector<int> ans;
        for (int i = 0; i < N; i++) {
            if (A[i] != i + 1)
                ans.push_back(A[i]);
        }
        return ans;
    }
};


int main()
{
    Solution obj;
    vector<int> A = { 4,3,2,7,8,2,3,1 };
    vector<int> duplicates = obj.findDuplicates(A);
    for (int i : duplicates) {
        cout << i << " ";
    }
    cout << endl;
    
    A = { 1,1,2 };
    duplicates = obj.findDuplicates(A);
    for (int i : duplicates) {
        cout << i << " ";
    }
    cout << endl;

    A = { 1 };
    duplicates = obj.findDuplicates(A);
    for (int i : duplicates) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}