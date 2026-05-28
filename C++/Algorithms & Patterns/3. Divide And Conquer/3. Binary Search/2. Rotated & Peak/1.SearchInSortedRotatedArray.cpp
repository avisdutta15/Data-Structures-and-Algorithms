#include <iostream>
#include <vector>

using namespace std;

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
    vector<int> A = { 4, 5, 6, 7, 0, 1, 2 };
    cout << obj.searchInRotatedSorted(A, 2) << endl;
    cout << obj.searchInRotatedSorted(A, 3) << endl;
}