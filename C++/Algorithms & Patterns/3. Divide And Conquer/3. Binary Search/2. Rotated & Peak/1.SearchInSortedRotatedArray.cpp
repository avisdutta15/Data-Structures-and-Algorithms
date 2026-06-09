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
