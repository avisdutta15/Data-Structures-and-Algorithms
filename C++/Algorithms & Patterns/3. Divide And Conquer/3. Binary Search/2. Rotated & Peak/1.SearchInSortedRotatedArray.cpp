#include <iostream>
#include <vector>

using namespace std;

/*
    Problem Statement:
    -----------------
    Given a sorted and rotated array arr[] of distinct elements, find the index 
    of given key in the array. If the key is not present in the array, return -1.

    Examples:
    --------
    Input: arr[] = [5, 6, 7, 8, 9, 10, 1, 2, 3], key = 3
    Output: 8
    Explanation: 3 is present at index 8.

    Input: arr[] = [3, 5, 1, 2], key = 6
    Output: -1
    Explanation: 6 is not present.

    Input: arr[] = [33, 42, 72, 99], key = 42
    Output: 1
    Explanation: 42 is found at index 1.

    Constraints:
    ------------

    Approach:
    ---------
    In normal binary search, we rely on the entire array being sorted to decide whether 
    to go left or right. But in this case, we adapt it slightly we don't require the whole 
    array to be sorted, just identify which part is sorted in the current range. 
    Compare A[lo] and A[mid].
    
    Once we know which part is sorted, we check if the target lies inside that sorted section. 
    If it does, we discard the other half. If not, we discard the sorted half and search the 
    remaining half. No matter how the array was rotated, the sorted structure on at least one 
    side of any middle point always helps us narrow down where to look next. 
    
    This lets us avoid scanning the whole array like in brute force, and instead bring down 
    the number of checks to logarithmic time.

    How to find sorted section?
        if(A[left] <= A[mid])        // left section is sorted
        else                         // right section is sorted


    Why A[left] <= A[mid] and not A[left] < A[mid] even thought the array has distinct elements?
    The reason you must use <= instead of < comes down to what happens when your search space shrinks to just two elements.
    When there are only two elements left (for example, left = 0 and right = 1), integer division makes the mid pointer land on the exact same index as the left pointer:
    mid = 0 + (1 - 0) / 2 = 0.    
    Because left and mid are at the exact same index, A[left] is equal to A[mid].
    
    If you use A[left] < A[mid]:
    The condition evaluates to false (because a number is not less than itself). Your code jumps to the else block, falsely assuming the right half is the sorted one, which ruins the search.
    Let's trace a failing example with <:
        - Array: [3, 1], Target: 1
        - Iteration 1: left = 0 (val 3), right = 1 (val 1). mid = 0 (val 3).
        - A[mid] == target -> 3 == 1 (False).
        - A[left] < A[mid] -> 3 < 3 -> FALSE.
        - Code jumps to the else block.
        - It checks if target is in the right half: A[mid] <= target && target <= A[right] -> 3 <= 1 && 1 <= 1 (False).
        - It executes right = mid - 1 -> right = -1.
        - Loop terminates and returns -1. It failed to find the target!
    
    If you use A[left] <= A[mid]:
        - A[left] <= A[mid] -> 3 <= 3 -> TRUE. (A single element is technically a sorted array).
        - It checks if the target is in this left half: 3 <= 1 && 1 <= 3 -> (False).
        - It executes left = mid + 1 -> left = 1.
        - Iteration 2: left = 1, right = 1. mid = 1.
        - A[mid] == target -> 1 == 1. Returns index 1. (Success!)
    
    In short: You need the = to handle the edge case where left and mid overlap. 
    Without it, your algorithm breaks on arrays of size 2.
*/

class Solution {
public:
    int searchInRotatedSorted(vector<int>& A, int target) {
        int N = A.size();
        int left = 0, right = N - 1, mid = 0;

        while (left <= right) {
            mid = left + (right - left) / 2;

            // if target found return index
            if (A[mid] == target)
                return mid;

            // Check if the left half is sorted
            if (A[left] <= A[mid]) {
                // Check if the target lies on the left half then goto left
                if (A[left] <= target && target <= A[mid])
                    right = mid - 1;
                // Else goto right half
                else
                    left = mid + 1;
            }
            // Check if the right half is sorted
            else {
                // Check if the target lies on the right half then goto right
                if (A[mid] <= target && target <= A[right])
                    left = mid + 1;
                // Else goto left half
                else
                    right = mid - 1;
            }
        }

        // Target not found
        return -1;
    }
};

int main() {
    Solution obj;
    vector<int> A = { 4, 5, 6, 7, 0, 1, 2 };
    cout << obj.searchInRotatedSorted(A, 2) << endl;
    cout << obj.searchInRotatedSorted(A, 3) << endl;
}
