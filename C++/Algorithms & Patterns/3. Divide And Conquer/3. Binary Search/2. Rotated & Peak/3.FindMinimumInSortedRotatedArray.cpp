#include <iostream>
#include <vector>

using namespace std;

/*
    Problem Statement:
    -----------------
    Given a sorted array of distinct elements arr[] of size n that is rotated at some unknown point, the task is to find the minimum element in it. 

    Examples:
    --------
    Input: arr[] = [5, 6, 1, 2, 3, 4]
    Output: 1
    Explanation: 1 is the minimum element present in the array.

    Input: arr[] = [3, 1, 2]
    Output: 1
    Explanation: 1 is the minimum element present in the array.

    Input: arr[] = [4, 2, 3]
    Output: 2
    Explanation: 2 is the only minimum element in the array.

    Constraints:
    ------------

    Approach:
    ---------
    Instead of trying to find the exact "pivot point" where the rotation happened, this algorithm systematically 
    identifies the sorted half, extracts its smallest value, and then throws that half away.

    1. Identifying the Sorted Half

    Inside the while(left <= right) loop, it checks if (A[left] <= A[mid]).
    If true, it means the left half (from left to mid) is perfectly sorted.
    If false, it means the left half contains the rotation pivot, which forces the right half (from mid to right) to be perfectly sorted.

    2. Harvest and Discard (The Core Magic)
    Case A: The Left Half is Sorted             
        ans = min(ans, A[left]);
        left = mid + 1;

    If the left half is sorted, the smallest number in that entire half is sitting right at the front: A[left].
    Harvest: We take A[left] and compare it against our running ans.
    Discard: Since we have already extracted the absolute smallest number from the left half, there is no reason to 
    search the left half anymore! The global minimum is either what we just found, or it's hiding in the 
    unsorted right half. So, we move left = mid + 1.
                 l        m        r
                [4, 5, 6, 7, 0, 1, 2]
          left half is sorted. 
          So we save 4 as a candidate for minimum and discard the left half. (Why? Because the actual minimum lies on
          the right half [0].).
          We cannot certainly say that sorted half will have the minimum element.



    Case B: The Right Half is Sorted
        ans = min(A[mid], ans);
        right = mid - 1;

    If the right half is sorted, the smallest number in that half is sitting right at its beginning, which is A[mid].
    Harvest: We take A[mid] and update our running ans.
    Discard: Since we have extracted the smallest number from the right half, we throw the right half away. 
    The global minimum might be hiding in the unsorted left half (which contains the rotation pivot). 
    We move right = mid - 1.
                 l        m        r
                [5, 6, 0, 1, 2, 3, 4]
          right half is sorted.
          So we save 0 as a candidate for minimum and discard the right half. (Why? Because the actual minimum lies on
          the left half [0].).
          We cannot certainly say that sorted half will have the minimum element.
          

    Summary:
    AFTER IDENTIFYING THE SORTED HALF, WE CAN FIND THE MINIMUM ELEMENT IN THE SORTED HALF.
    BUT WE CANNOT CERTAINLY SAY THAT THE SORTED HALF WILL HAVE THE MINIMUM ELEMENT.
    SO WE STORE THE MINIMUM FROM THIS HALF AND DISCARD THIS HALF.
*/

class Solution {
public:
    int findMin(vector<int>& A) {
        int N = A.size();
        int left = 0, right = N - 1;
        int mid = 0;
        int ans = INT_MAX;

        // if the entire array is sorted then first element will be minimum
        if (A[left] < A[right])
            return A[left];

        while (left <= right) {
            // Calculate min
            mid = left + (right - left) / 2;

            // if left half is sorted (Harvest and Discard)
            if (A[left] <= A[mid]) {

                // store the minimum element till now
                ans = min(ans, A[left]);

                // the minimum may lie in the right half. So search there.
                left = mid + 1;
            }
            else {
                // Right half is sorted (Harvest and Discard)

                // store the minimum till now
                ans = min(A[mid], ans);

                // the minimum may lie in the left half. So search there.
                right = mid - 1;
            }
        }

        return ans;
    }
};

int main() {
    Solution obj;
    vector<int> A = { 4, 5, 6, 7, 0, 1, 2 };
    vector<int> B = { 5, 6, 0, 1, 2, 3, 4 };
    cout << obj.findMin(A) << endl;
    cout << obj.findMin(B) << endl;
}
