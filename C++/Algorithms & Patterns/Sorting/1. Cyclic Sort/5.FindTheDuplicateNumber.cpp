#include <iostream>
#include <vector>

using namespace std;

/*
    Problem Statement:
    Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive.

    There is only one repeated number in nums, return this repeated number.

    You must solve the problem without modifying the array nums and using only constant extra space.

    Examples:
    Input: nums = [1,3,4,2,2]
    Output: 2

    Input: nums = [3,1,3,4,2]
    Output: 3

    Input: nums = [3,3,3,3,3]
    Output: 3

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
    int findDuplicate(vector<int>& A) {
        int N = A.size();

        // 1. Cyclic Sort logic
        for (int i = 0; i < N; i++) {
            int correctIndexOfAi = A[i] - 1;
            while (A[i] != A[correctIndexOfAi]) {
                swap(A[i], A[correctIndexOfAi]);
                correctIndexOfAi = A[i] - 1;
            }
        }

        // 2. Find the out-of-place element
        for (int i = 0; i < N; i++) {
            if (A[i] != i + 1)
                return A[i];
        }
        return -1;
    }
};


int main()
{
    Solution obj;
    vector<int> A = { 1,3,4,2,2 };
    cout << obj.findDuplicate(A) <<endl;
    
    A = { 3,1,3,4,2 };
    cout << obj.findDuplicate(A) << endl;


    A = { 3,3,3,3,3 };
    cout << obj.findDuplicate(A) << endl;

    return 0;
}