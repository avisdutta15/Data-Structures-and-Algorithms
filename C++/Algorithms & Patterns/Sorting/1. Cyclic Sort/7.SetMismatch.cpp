#include <iostream>
#include <vector>

using namespace std;

/*
    Problem Statement:
    You have a set of integers s, which originally contains all the numbers from 1 to n. Unfortunately, due to some error, 
    one of the numbers in s got duplicated to another number in the set, which results in repetition of one number and loss of another number.
    You are given an integer array nums representing the data status of this set after the error.

    Find the number that occurs twice and the number that is missing and return them in the form of an array.

    Examples:
    Input: nums = [1,2,2,4]
    Output: [2,3]

    Input: nums = [1,1]
    Output: [1,2]

    Approach:
    Use cyclic sort to place every element at its correct position and then traverse the array to find the out-of-place element.
        1,2,2,4
        1,2,2,4
        if (i != A[i]-1) then i+1 is missing
        if (i != A[i]-1) then A[i] is duplicate

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
    vector<int> findErrorNums(vector<int>& A) {

        int N = A.size();
        for (int i = 0; i < N; i++) {
            int correctIndexOfAi = A[i] - 1;
            while (A[i] != A[correctIndexOfAi]) {
                swap(A[i], A[correctIndexOfAi]);
                correctIndexOfAi = A[i] - 1;
            }
        }

        vector<int> ans;
        for (int i = 0; i < N; i++) {
            if (i != A[i] - 1) {
                ans.push_back(A[i]);
                ans.push_back(i + 1);
            }
        }
        return ans;
    }
};


int main()
{
    Solution obj;
    vector<int> A = { 1,2,2,4 };
    vector<int> duplicates = obj.findErrorNums(A);
    for (int i : duplicates) {
        cout << i << " ";
    }
    cout << endl;
    
    A = { 1,1 };
    duplicates = obj.findErrorNums(A);
    for (int i : duplicates) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}