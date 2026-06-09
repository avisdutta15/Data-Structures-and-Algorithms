#include <iostream>
#include <vector>

using namespace std;

/*
    Problem Statement:
    -----------------
    Given a sorted and rotated array (possibly with duplicates), determine if a given key 
    exists in it, returning true if found, otherwise false.

    Examples:
    --------
    Input: arr[] = [3, 3, 3, 1, 2, 3], key = 3 
    Output: true
    Explanation: 3 is present in the array.

    Input: arr[] = [3, 3, 3, 1, 2, 3], key = 11 
    Output: false
    Explanation: 11 is not present in the given array. 

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

    NOTE : For Duplicates
    ---------------------
    The issue here is taking the decision of which half is sorted based on comparing A[low] and A[mid].
    when A[low] == A[mid] == A[hi], we can't decide which half is sorted, so we shrink the search space.
        low++; hi--; continue;

    Time Complexity: O(log n) average case, O(n) worst case (when all elements are same)    

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

            //if A[left] == A[mid] == A[right] then we cannot make a 
            //decision that which part is sorted. So shrink the search space
            if (A[left] == A[mid] == A[right]) {
                left++;
                right--;
                continue;
            }


            //check if the left half is sorted
            if (A[left] <= A[mid]) {
                //check if the target lies on the left half then goto left
                if (A[left] <= target && target <= A[mid])
                    right = mid - 1;
                //else goto right half
                else
                    left = mid + 1;
            }
            //check if the right half is sorted
            else {
                //check if the target lies on the right half then goto right
                if (A[mid] <= target && target <= A[right])
                    left = mid + 1;
                //else goto left half
                else
                    right = mid - 1;
            }
        }

        //target not found
        return -1;
    }
};

int main() {
    Solution obj;
    vector<int> A = { 2, 2, 2, 0, 1, 2 };
    cout << obj.searchInRotatedSorted(A, 0) << endl;
    cout << obj.searchInRotatedSorted(A, 3) << endl;
}
