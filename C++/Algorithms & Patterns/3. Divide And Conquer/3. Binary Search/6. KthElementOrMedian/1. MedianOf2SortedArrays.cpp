#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

/*
    ============================================================================
    LeetCode 4 — Median of Two Sorted Arrays
    ============================================================================

    References:
        https://www.youtube.com/watch?v=6D9T2ZY8h5c
        https://www.youtube.com/watch?v=7nABqJCEMuY

    Problem
    -------
    Given two sorted arrays A (size m) and B (size n), return the median of
    the combined sorted sequence. Required time complexity: O(log(m+n)).

    Examples
    --------
    1) A = [1,3], B = [2]        →  merged = [1,2,3]       →  median = 2.0
    2) A = [1,2], B = [3,4]      →  merged = [1,2,3,4]     →  median = 2.5
    3) A = [1,3,8], B = [2,4,7,10,11] → merged = [1,2,3,4,7,8,10,11] → median = 5.5

    Constraints
    -----------
    • 0 ≤ m, n ≤ 1000      • 1 ≤ m + n ≤ 2000
    • −10^6 ≤ A[i], B[i] ≤ 10^6

    ============================================================================
    What Is a Median?
    ============================================================================

    The median splits a sorted sequence into two equal (or near-equal) halves:
        • Odd  length:  middle element.
        • Even length:  average of the two middle elements.

        temp = [0, 1, 2, 3, 4]       →  median = temp[5/2]           = temp[2] = 2
        temp = [0, 1, 2, 3, 4, 5]    →  median = (temp[2]+temp[3])/2 = 2.5

    ============================================================================
    Approach 1 — Concatenate + Sort                     O((m+n)log(m+n)) / O(m+n)
    ============================================================================
    Dump both arrays into temp[], sort, pick the middle element(s).
    Simple but ignores the fact that A and B are already sorted.

    ============================================================================
    Approach 2 — Merge Procedure (temp array)           O(m+n) / O(m+n)
    ============================================================================
    Use the merge step of merge-sort to build a sorted temp[] in one
    pass, then pick the middle element(s). Avoids re-sorting.

    ============================================================================
    Approach 3 — Merge Procedure (no temp array)        O(m+n) / O(1)
    ============================================================================
    Same merge walk, but instead of storing everything, just track the
    elements at positions idx1 = (m+n)/2 − 1 and idx2 = (m+n)/2 as we
    go. Constant space, still linear time.

    ============================================================================
    Approach 4 — Binary Search on Partition              O(log(min(m,n))) / O(1)
    ============================================================================

    This is the key approach that meets the O(log(m+n)) requirement.
    It deserves a deep walkthrough.

    ────────────────────────────────────────────────────────────────────
    CORE IDEA: PARTITION, DON'T MERGE
    ────────────────────────────────────────────────────────────────────

    Instead of actually merging the arrays, we ask:

        "Can we find a CUT in A and a CUT in B such that everything
         on the left of both cuts would form the left half of the
         merged array, and everything on the right would form the
         right half?"

    If yes, the median sits right at the boundary of that partition.

    ────────────────────────────────────────────────────────────────────
    STEP 1: DEFINE THE PARTITION SIZE
    ────────────────────────────────────────────────────────────────────

    The left half of the merged array must contain exactly:

        leftSize = (m + n + 1) / 2    elements

    Why +1?  Integer division floors the result. The +1 makes the left
    half absorb the extra element when the total is odd:
        • m+n = 7  →  leftSize = 4, rightSize = 3  →  median = max(left)
        • m+n = 8  →  leftSize = 4, rightSize = 4  →  median = avg(max(left), min(right))
    This lets us handle odd/even with the same formula.

    ────────────────────────────────────────────────────────────────────
    STEP 2: WHAT DOES A "CUT" LOOK LIKE?
    ────────────────────────────────────────────────────────────────────

    Suppose we take `i` elements from A and `j` elements from B for
    the left half, where j = leftSize − i.

        A:  [ a0  a1  ...  a(i-1) | a(i)  a(i+1) ...  a(m-1) ]
                 ← left A →             ← right A →

        B:  [ b0  b1  ...  b(j-1) | b(j)  b(j+1) ...  b(n-1) ]
                 ← left B →             ← right B →

    Define four boundary values:
        a1 = A[i−1]   (max of A's left)       a2 = A[i]     (min of A's right)
        b1 = B[j−1]   (max of B's left)       b2 = B[j]     (min of B's right)

    If i = 0 (nothing taken from A's left):  a1 = −∞
    If i = m (nothing in A's right):         a2 = +∞
    Same logic for j with B.

    ────────────────────────────────────────────────────────────────────
    STEP 3: WHEN IS A PARTITION VALID?
    ────────────────────────────────────────────────────────────────────

    For the partition to correctly split the merged array, every element
    on the left must be ≤ every element on the right. We need:

        a1 ≤ b2    (A's left max  ≤  B's right min)
        b1 ≤ a2    (B's left max  ≤  A's right min)

    Why only these two cross-checks?
    Because A and B are individually sorted, so:
        a1 ≤ a2   is already guaranteed  (sorted order within A)
        b1 ≤ b2   is already guaranteed  (sorted order within B)

    The only unknowns are the CROSS-ARRAY relationships: a1 vs b2
    and b1 vs a2. That's what we check.

    ────────────────────────────────────────────────────────────────────
    STEP 4: WHY BINARY SEARCH WORKS HERE
    ────────────────────────────────────────────────────────────────────

    The variable we binary-search on is `i` — the number of elements
    we take from A for the left half. Range: 0 ≤ i ≤ m.

    At each candidate `i`, exactly one of three things is true:

    CASE 1: a1 ≤ b2  AND  b1 ≤ a2   →  VALID partition. Done.
    ─────────────────────────────────────────────────────────────
        Everything on the left ≤ everything on the right.
        Median = max(a1,b1)                          if odd total
                 (max(a1,b1) + min(a2,b2)) / 2.0    if even total

    CASE 2: a1 > b2   →  We took TOO MANY from A.
    ─────────────────────────────────────────────────────────────
        A's left-side maximum (a1) is bigger than B's right-side
        minimum (b2). That means a1 would need to be on the right,
        so we've pushed A's cut too far right. Fix: move hi ← mid−1
        (take fewer from A).

        Visually:
            A:  [ ... 15 | 20 ... ]     a1=15
            B:  [ ... 8  | 10 ... ]     b2=10
            15 > 10 → a1 is too big for the left half → shrink A's contribution.

    CASE 3: b1 > a2   →  We took TOO FEW from A.
    ─────────────────────────────────────────────────────────────
        B's left-side maximum (b1) is bigger than A's right-side
        minimum (a2). That means we gave B too many elements on
        the left (because j = leftSize − i, taking fewer from A
        means taking more from B). Fix: move lo ← mid+1
        (take more from A, fewer from B).

        Visually:
            A:  [ ... 3  | 5  ... ]     a2=5
            B:  [ ... 12 | 18 ... ]     b1=12
            12 > 5 → b1 is too big for the left half → give more to A, less to B.

    KEY INSIGHT: Cases 2 and 3 are mutually exclusive and tell us a
    clear direction (left or right), which is exactly what binary
    search needs. There is always exactly one valid partition, and
    the search space is monotonic — moving `i` left makes a1 smaller
    and b1 larger, and vice versa. This monotonicity guarantees
    convergence.

    ────────────────────────────────────────────────────────────────────
    STEP 5: ALWAYS BINARY-SEARCH ON THE SMALLER ARRAY
    ────────────────────────────────────────────────────────────────────

    If m > n, swap A and B so we always binary-search on the shorter
    array. Two reasons:
        1. Fewer iterations: O(log(min(m,n))) instead of O(log(max(m,n))).
        2. Prevents invalid index: if m > n, then j = leftSize − i
           could go negative for large i, causing out-of-bounds on B.
           When m ≤ n, j stays in [0, n] for all valid i in [0, m].

    ────────────────────────────────────────────────────────────────────
    STEP 6: READING THE MEDIAN FROM THE PARTITION
    ────────────────────────────────────────────────────────────────────

    Once we find a valid partition:
        • max(a1, b1) is the largest element in the entire left half.
        • min(a2, b2) is the smallest element in the entire right half.

    Odd total  →  median = max(a1, b1)
        The left half has one more element, so its max IS the median.

    Even total →  median = (max(a1, b1) + min(a2, b2)) / 2.0
        The two middle elements straddle the partition boundary.

    ============================================================================
    Dry Run 1:  A = [1, 3, 8],  B = [2, 4, 7, 10, 11]
                m = 3,  n = 5,  leftSize = (3+5+1)/2 = 4
    ============================================================================

    Binary search on A (smaller array):  lo = 0,  hi = 3

    Iteration 1:  mid = 1  →  i = 1 from A,  j = 3 from B
    ┌─────────────────────────────────────────────────────────────┐
    │  A:   [ 1 | 3, 8 ]          a1 = A[0] = 1,  a2 = A[1] = 3   │
    │  B:   [ 2, 4, 7 | 10, 11 ]  b1 = B[2] = 7,  b2 = B[3] = 10  │
    │                                                             │
    │  Check:  a1(1) ≤ b2(10)?  YES  ✓                            │
    │          b1(7) ≤ a2(3)?   NO   ✗                            │
    │                                                             │
    │  b1 > a2  →  took too few from A  →  lo = mid + 1 = 2       │
    └─────────────────────────────────────────────────────────────┘
        Why? B contributed 7 to the left, but A's right starts at 3.
        7 > 3 breaks the partition. We need more from A (push the
        cut in A rightward so a2 grows and b1 shrinks).

    Iteration 2:  mid = 2  →  i = 2 from A,  j = 2 from B
    ┌─────────────────────────────────────────────────────────────┐
    │  A:   [ 1, 3 | 8 ]          a1 = A[1] = 3,  a2 = A[2] = 8   │
    │  B:   [ 2, 4 | 7, 10, 11 ]  b1 = B[1] = 4,  b2 = B[2] = 7   │
    │                                                             │
    │  Check:  a1(3) ≤ b2(7)?  YES  ✓                             │
    │          b1(4) ≤ a2(8)?  YES  ✓                             │
    │                                                             │
    │  VALID PARTITION!                                           │
    │  Left  half = {1, 3, 2, 4}    →  max(a1, b1) = max(3, 4) = 4│
    │  Right half = {8, 7, 10, 11}  →  min(a2, b2) = min(8, 7) = 7│
    │  Total = 8 (even) →  median = (4 + 7) / 2.0 = 5.5           │
    └─────────────────────────────────────────────────────────────┘

    Verify: merged = [1, 2, 3, 4, 7, 8, 10, 11]  →  (4+7)/2 = 5.5  ✓

    ============================================================================
    Dry Run 2:  A = [1, 3],  B = [2]
                m = 2,  n = 1,  leftSize = (2+1+1)/2 = 2
    ============================================================================

    Binary search on B (smaller, so we swap: search on the array of size 1).
    After swap:  A = [2],  B = [1, 3],  m = 1,  n = 2

    lo = 0,  hi = 1

    Iteration 1:  mid = 0  →  i = 0 from A,  j = 2 from B
    ┌──────────────────────────────────────────────────────────────┐
    │  A:   [ | 2 ]               a1 = −∞,       a2 = A[0] = 2     │
    │  B:   [ 1, 3 | ]            b1 = B[1] = 3, b2 = +∞           │
    │                                                              │
    │  Check:  a1(−∞) ≤ b2(+∞)?  YES  ✓                            │
    │          b1(3)  ≤ a2(2)?    NO   ✗                           │
    │                                                              │
    │  b1 > a2  →  lo = mid + 1 = 1                                │
    └──────────────────────────────────────────────────────────────┘

    Iteration 2:  mid = 1  →  i = 1 from A,  j = 1 from B
    ┌──────────────────────────────────────────────────────────────┐
    │  A:   [ 2 | ]               a1 = A[0] = 2, a2 = +∞           │
    │  B:   [ 1 | 3 ]             b1 = B[0] = 1, b2 = B[1] = 3     │
    │                                                              │
    │  Check:  a1(2) ≤ b2(3)?   YES  ✓                             │
    │          b1(1) ≤ a2(+∞)?  YES  ✓                             │
    │                                                              │
    │  VALID PARTITION!                                            │
    │  Left half = {2, 1}  →  max(2, 1) = 2                        │
    │  Total = 3 (odd)     →  median = 2                           │
    └──────────────────────────────────────────────────────────────┘

    Verify: merged = [1, 2, 3]  →  median = 2  ✓

    ============================================================================
    Dry Run 3 (edge case):  A = [1, 2],  B = [3, 4]
                            m = 2,  n = 2,  leftSize = (2+2+1)/2 = 2
    ============================================================================

    lo = 0,  hi = 2

    Iteration 1:  mid = 1  →  i = 1 from A,  j = 1 from B
    ┌──────────────────────────────────────────────────────────────┐
    │  A:   [ 1 | 2 ]             a1 = 1,  a2 = 2                  │
    │  B:   [ 3 | 4 ]             b1 = 3,  b2 = 4                  │
    │                                                              │
    │  Check:  a1(1) ≤ b2(4)?  YES  ✓                             │
    │          b1(3) ≤ a2(2)?  NO   ✗                             │
    │                                                              │
    │  b1 > a2  →  lo = mid + 1 = 2                                │
    └──────────────────────────────────────────────────────────────┘

    Iteration 2:  mid = 2  →  i = 2 from A,  j = 0 from B
    ┌──────────────────────────────────────────────────────────────┐
    │  A:   [ 1, 2 | ]            a1 = 2,   a2 = +∞                │
    │  B:   [ | 3, 4 ]            b1 = −∞,  b2 = 3                 │
    │                                                              │
    │  Check:  a1(2)  ≤ b2(3)?   YES  ✓                            │
    │          b1(−∞) ≤ a2(+∞)?  YES  ✓                            │
    │                                                              │
    │  VALID PARTITION!                                            │
    │  Left  = {1, 2}   →  max(2, −∞) = 2                          │
    │  Right = {3, 4}   →  min(+∞, 3)  = 3                         │
    │  Total = 4 (even) →  median = (2 + 3) / 2.0 = 2.5            │
    └──────────────────────────────────────────────────────────────┘

    Verify: merged = [1, 2, 3, 4]  →  (2+3)/2 = 2.5  ✓

    ============================================================================
    Complexity
    ============================================================================
    Time  : O(log(min(m, n)))  —  binary search on the shorter array.
    Space : O(1)               —  only a handful of variables.
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