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

    Approach 1:
    Use cyclic sort to place every element at its correct position and then traverse the array to find the out-of-place element.

    Time Complexity: O(n)
    Space Complexity: O(1)

    Approach 2:
    If there exists a duplicate, then the array can be seen as a linked list with a cycle.
    Use Floyd's Cycle Detection Algorithm (tortoise and hare) to detect the cycle and find the starting point of the cycle.
    And since the duplicate element will be the start of the cycle, return that element.
     Steps:
    1. Use two pointers, slow and fast, both initialized to the first element index of the array.
    2. Move slow pointer by one step and fast pointer by two steps until they meet.
    3. Once they meet, initialize one of the pointers to the first element of the array.
    4. Move both pointers one step at a time until they meet again.
    5. The meeting point is the duplicate number.

    Time Complexity: O(n)
    Space Complexity: O(1)

    Let's do a dry run using this array: A       = {1, 3, 4, 2, 2}
    Indices:   0, 1, 2, 3, 4
    Values:    1, 3, 4, 2, 2
    
    If we map this out:
    0 points to A[0]=1 ➡️ 1 points to A[1]=3 ➡️ 3 points to A[3]=2 ➡️ 2 points to A[2]=4 ➡️ 4 points to A[4]=2 (Cycle!)
    
    Phase 1: Detect the Cycle
    We start by making slow take 1 step, and fast take 2 steps until they collide.
    
    Initialization:slow = 0, fast = 0
    Pre-loop step:
        slow = A[0] ➔ 1
        fast = A[A[0]] ➔ A[1] ➔ 3
    
    Entering the while(slow != fast) loop:
        Iteration           Check                   slow (moves 1 step: A[slow])            fast (moves 2 steps: A[A[fast]])
        1                   1 != 3 (True)           A[1] ➔ 3                                A[A[3]] ➔ A[2] ➔ 4
        2                   3 != 4 (True)           A[3] ➔ 2                                A[A[4]] ➔ A[2] ➔ 4
        3                   2 != 4 (True)           A[2] ➔ 4                                A[A[4]] ➔ A[2] ➔ 4
        4                   4 != 4 (False)          Loop Ends. They collided at 4.

    Phase 2: Find the Start of the Cycle (The Duplicate)
    Initialization for Phase 2:
        slow = 0, fast = 4 (from the previous phase)
    
    Entering the second while(slow != fast) loop:
        Iteration           Check                   slow (moves 1 step: A[slow])            fast (moves 1 step: A[fast])
        1                   0 != 4 (True)           A[0] ➔ 1                                A[4] ➔ 2    
        2                   1 != 2 (True)           A[1] ➔ 3                                A[2] ➔ 4
        3                   3 != 2 (True)           A[3] ➔ 2                                A[2] ➔ 4        
        4                   2 != 2 (False)          Loop Ends. They collided at 2.
    The function returns slow (which is 2).

*/


class Solution {
public:
    int findDuplicate(vector<int>& A) {
        int slow = 0, fast = 0;

        //Detect Cycle
        slow = A[slow];
        fast = A[A[fast]];

        while(slow != fast)
        {
            slow = A[slow];
            fast = A[A[fast]];
        }

        //Find the start of the cycle
        slow = 0;
        while(slow != fast)
        {
            slow = A[slow];
            fast = A[fast];
        }

        //return the duplicate number
        return slow;
    }
};


int main()
{
    Solution obj;
    vector<int> A = { 1,3,4,2,2 };
    cout << obj.findDuplicate(A) << endl;

    A = { 3,1,3,4,2 };
    cout << obj.findDuplicate(A) << endl;


    A = { 3,3,3,3,3 };
    cout << obj.findDuplicate(A) << endl;

    return 0;
}