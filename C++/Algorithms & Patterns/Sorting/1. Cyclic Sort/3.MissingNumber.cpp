#include <iostream>
#include <vector>

using namespace std;

/*
    Problem Statement:
    Given an array nums containing n distinct numbers in the range [0, n], return the only number in the range that is missing from the array.

    Examples:
    Input: nums = [3,0,1]
    Output: 2
    Explanation:
    n = 3 since there are 3 numbers, so all numbers are in the range [0,3]. 2 is the missing number in the range since it does not appear in nums.

    Input: nums = [0,1]
    Output: 2
    Explanation:
    n = 2 since there are 2 numbers, so all numbers are in the range [0,2]. 2 is the missing number in the range since it does not appear in nums.

    Input: nums = [9,6,4,2,3,5,7,0,1]
    Output: 8
    Explanation:
    n = 9 since there are 9 numbers, so all numbers are in the range [0,9]. 8 is the missing number in the range since it does not appear in nums.
    
    Approach:
    1. Using Hash Set
        T.C - O(n), S.C = O(n)
    2. Using Cyclic Sort
        T.C - O(2n), S.C = O(1)
    3. Using Bit Manipulation
        T.C - O(n), S.C = O(1)
*/


class Solution {
private:
    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }
public:
    int missingNumber(vector<int>& A) {
        
        int N = A.size();

        for (int i = 0; i < N; i++) {
            int correctIndexOfAi = A[i];
            while (A[i] != N && A[i] != A[correctIndexOfAi]) {
                swap(A[i], A[correctIndexOfAi]);
                correctIndexOfAi = A[i];
            }
        }
        
        // Case 1: When the missing number != N
        // Find the first index i where A[i] != i
        for (int i = 0; i < N; i++) {
            if (A[i] != i)
                return i;
        }

        // Case 2: When the missing number = N
        return N;
    }
};


class Solution2 {
private:
    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }
public:
    int missingNumber(vector<int>& A) {

        int N = A.size();
        int xorr = 0;

        for (int i = 0; i < N; i++) {
            xorr = xorr ^ i;
            xorr = xorr ^ A[i];
        }

        //xor the Nth number
        xorr = xorr ^ N;

        return xorr;
    }
};

int main()
{
    Solution obj;
    vector<int> A = { 3,0,1 };
    cout << obj.missingNumber(A) << endl;
    
    A = { 0, 1 };
    cout << obj.missingNumber(A) << endl;

    A = { 9,6,4,2,3,5,7,0,1 };
    cout << obj.missingNumber(A) << endl;

    return 0;
}