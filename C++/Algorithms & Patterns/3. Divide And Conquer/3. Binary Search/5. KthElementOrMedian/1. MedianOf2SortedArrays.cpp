#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

/*
    https://www.youtube.com/watch?v=6D9T2ZY8h5c
    https://www.youtube.com/watch?v=7nABqJCEMuY

	  Problem Statement:
	  -----------------
	  Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.
    The overall run time complexity should be O(log (m+n)).
	
    Examples:
	  ---------
	  Input: nums1 = [1,3], nums2 = [2]
    Output: 2.00000
    Explanation: merged array = [1,2,3] and median is 2.


    Input: nums1 = [1,2], nums2 = [3,4]
    Output: 2.50000
    Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.

	  Constraints:
	  ------------
    nums1.length == m
    nums2.length == n
    0 <= m <= 1000
    0 <= n <= 1000
    1 <= m + n <= 2000
    -10^6 <= nums1[i], nums2[i] <= 10^6

    Intuition:
    ---------
    If the total number of elements in both the arrays is odd  - Median = temp[total_elements/2]
    If the total number of elements in both the arrays is even - Median = (temp[total_elements/2 - 1] + temp[total_elements/2])/2.0
    e.g:
        temp[] = [0, 1, 2, 3, 4]
        total_elements = odd
        median = A[total_elements/2] 
               = A[5/2] 
               = A[2] 
               = 2

        temp[] = [0, 1, 2, 3, 4, 5]
        total_elements = even
        median = (A[total_elements/2] + A[total_elements/2 - 1])/2.0 
               = (A[5/2] + A[5/2 - 1])/2.0 
               = (A[2] + A[1])/2.0
               = (2+1)/2.0 
               = 1.5

	  Approach 1: Temp[] + Sort
	  -------------------------
    
    Approach 2: Temp[] + Insert using merge procedure to skip sorting
	  -----------------------------------------------------------------

    Approach 3: Variables to store target elements instead of temp[] + Insert using merge procedure to skip sorting
    ---------------------------------------------------------------------------------------------------------------

    Approach 4: Binary Search on the first array size
    -------------------------------------------------
    Key Idea: Partition both arrays such that:
      - Left partition has exactly (m+n+1)/2 elements
          The +1 ensures both odd and even totals are handled uniformly:
          - odd  total (e.g. m+n=7): (7+1)/2=4 -> left=4, right=3 -> median = max(left)
          - even total (e.g. m+n=8): (8+1)/2=4 -> left=4, right=4 -> median = (max(left)+min(right))/2
          Without +1, odd case gives 7/2=3 (integer division), putting the median
          element in the right partition and requiring extra handling.
      - All elements in left partition <= all elements in right partition

    For a valid partition, we need all the elements in the left partition to be smaller than
    all elements in the right partition. This gives us the conditions to validate a partition:
      a1 (max of A's left) <= b2 (min of B's right)
      b1 (max of B's left) <= a2 (min of A's right)

    Why are we not checking a1 <= a2 and b1 <=b2? 
    Because the arrays are already sorted, so we know:
    a1 <= a2 (because they're in sorted order in A)
    b1 <= b2 (because they're in sorted order in B)

    We binary search on the number of elements we take from A (smaller array).
    The rest are taken from B to fill the left partition.

    Example: A = [1, 3, 8], B = [2, 4, 7, 10, 11]  =>  m=3, n=5
    leftBucketSize = (3+5+1)/2 = 4

    Iteration 1: lo=0, hi=3, mid=1
      setASize=1, setBSize=3
      A:  | 1 | 3  8        =>  a1=A[0]=1,  a2=A[1]=3
      B:  | 2  4  7 | 10 11 =>  b1=B[2]=7,  b2=B[3]=10
      a1(1) <= b2(10)? YES
      b1(7) <= a2(3)?  NO  =>  lo = mid+1 = 2

    Iteration 2: lo=2, hi=3, mid=2
      setASize=2, setBSize=2
      A:  | 1  3 | 8        =>  a1=A[1]=3,  a2=A[2]=8
      B:  | 2  4 | 7 10 11  =>  b1=B[1]=4,  b2=B[2]=7
      a1(3) <= b2(7)?  YES
      b1(4) <= a2(8)?  YES  =>  Valid partition!

    merged left  = [1, 3, 2, 4]  =>  max(a1, b1) = max(3, 4) = 4
    merged right = [8, 7, 10, 11] =>  min(a2, b2) = min(8, 7) = 7
    (m+n)=8 is even => median = (max(a1,b1) + min(a2,b2)) / 2.0
                              = (4 + 7) / 2.0 = 5.5

    Verification: merged = [1,2,3,4,7,8,10,11] => median = (4+7)/2 = 5.5 ✓

*/

//T.C. - O(m) + O(n) + O((m+n)log(m+n))
//S.C. - O(m + n)
class Solution1 {
public:
    double findMedianSortedArrays(vector<int>& A, vector<int>& B) {
        
        vector<int> temp(A.begin(), A.end());           // O(m)
        temp.insert(temp.end(), B.begin(), B.end());    // O(n)

        
        sort(temp.begin(), temp.end());                 // O((m+n)log(m+n))
        
        int size = temp.size();
        if (size % 2 == 1)
            return temp[size / 2];

        return (temp[size / 2] + temp[(size / 2) - 1]) / 2.0;
    }
};

//T.C. - O(m) + O(n)
//S.C. - O(m + n)
class Solution2 {
public:
    double findMedianSortedArrays(vector<int>& A, vector<int>& B) {

        vector<int> temp(A.size() + B.size(), 0);

        int i = 0, j = 0, k = 0;
        while (i < A.size() && j < B.size()) {
            if (A[i] < B[j]) {
                temp[k] = A[i];
                i++;
            }
            else if(B[j] < A[i]) {
                temp[k] = B[j];
                j++;
            }
            else if (A[i] == B[j]) {
                temp[k] = A[i];
                k++; i++;
                temp[k] = B[j];
                j++;
            }
            k++;
        }

        while (i < A.size()) {
            temp[k] = A[i];
            k++; i++;
        }

        while (j < B.size()) {
            temp[k] = B[j];
            k++; j++;
        }

        int size = temp.size();
        if (size % 2 == 1)
            return temp[size / 2];

        return (temp[size / 2] + temp[(size / 2) - 1]) / 2.0;
    }
};

//T.C. - O(m) + O(n)
//S.C. - O(1)
class Solution3 {
public:
    double findMedianSortedArrays(vector<int>& A, vector<int>& B) {
        int m = A.size();
        int n = B.size();

        int i = 0, j = 0, k = 0;
        int idx1 = ((m + n) / 2) - 1;
        int idx2 = (m + n) / 2;
        int element1 = 0;   //element at idx1
        int element2 = 0;   //element at idx2


        while (i < m && j < n) {
            if (A[i] < B[j]) {
                if (k == idx1) {
                    element1 = A[i];
                }
                if (k == idx2) {
                    element2 = A[i];
                }
                i++;
            }
            else if (B[j] < A[i]) {
                if (k == idx1) {
                    element1 = B[j];
                }
                if (k == idx2) {
                    element2 = B[j];
                }
                j++;
            }
            else if (A[i] == B[j]) {
                if (k == idx1) {
                    element1 = B[j];
                }
                if (k == idx2) {
                    element2 = B[j];
                }
                k++; i++; 
                if (k == idx1) {
                    element1 = B[j];
                }
                if (k == idx2) {
                    element2 = B[j];
                }
                j++;
            }
            k++;
        }

        while (i < m) {
            if (k == idx1) {
                element1 = A[i];
            }
            if (k == idx2) {
                element2 = A[i];
            }
            k++; i++;
        }

        while (j < n) {
            if (k == idx1) {
                element1 = B[j];
            }
            if (k == idx2) {
                element2 = B[j];
            }
            k++; j++;
        }

        int size = (m + n);
        if (size % 2 == 1)
            return element2;

        return (element1 + element2) / 2.0;
    }
};

//T.C. - O(min(log(m,n)))
//S.C. - O(1)
class Solution4 {
public:
    double findMedianSortedArrays(vector<int>& A, vector<int>& B) {
        if (B.size() < A.size())
            return findMedianSortedArrays(B, A);

        int m = A.size();
        int n = B.size();
        int leftBucketSize = (m + n + 1) / 2;

        int lo = 0, hi = m;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;

            int setASize = mid;
            int setBSize = leftBucketSize - setASize;

            int a1 = setASize == 0 ? INT_MIN : A[setASize - 1];
            int a2 = setASize == m ? INT_MAX : A[setASize];

            int b1 = setBSize == 0 ? INT_MIN : B[setBSize - 1];
            int b2 = setBSize == n ? INT_MAX : B[setBSize];

            // check if median lies in this bucket
            if (a1 <= b2 && b1 <= a2) {
                // if odd count 
                if ((m + n) % 2 == 1)
                    return max(a1, b1);
                return (max(a1, b1) + min(a2, b2)) / 2.0;
            }
            // else we have overshoot
            else if (a1 > b2) {
                hi = mid - 1;
            }
            else
                lo = mid + 1;
        }

        return -1;
    }
};

int main() {
	Solution4 obj;
    vector<int> A = {2};
    vector<int> B = {};
	cout<<obj.findMedianSortedArrays(A, B)<<endl;

	return 0;
}
