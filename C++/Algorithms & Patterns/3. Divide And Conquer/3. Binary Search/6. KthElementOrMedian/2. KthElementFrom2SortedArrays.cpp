#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
    https://www.youtube.com/watch?v=SB6j8D95eHM

    Problem
    -------
    Given two sorted arrays A (size m) and B (size n) and an integer k,
    find the k-th smallest element in the combined sorted sequence
    (1-indexed).

    Examples
    --------
    1) A = [2, 3, 6, 7, 9],  B = [1, 4, 8, 10],  k = 5
       merged = [1, 2, 3, 4, 6, 7, 8, 9, 10]  →  5th element = 6

    2) A = [1, 2],  B = [3, 4, 5, 6],  k = 4
       merged = [1, 2, 3, 4, 5, 6]  →  4th element = 4

    3) A = [1, 3, 5],  B = [2, 4, 6],  k = 1
       merged = [1, 2, 3, 4, 5, 6]  →  1st element = 1

    Constraints
    -----------
    • 1 ≤ k ≤ m + n
    • A and B are sorted in non-decreasing order.

    ============================================================================
    Approach 1 — Merge Walk                              O(k) / O(1)
    ============================================================================

    Use two pointers to simulate the merge step of merge-sort.
    Advance the pointer that points to the smaller element. After k
    advances, the last element touched is the answer. No extra array
    needed — just count steps.

    ============================================================================
    Approach 2 — Binary Search on Partition              O(log(min(k, m, n))) / O(1)
    ============================================================================

    This is the same partitioning idea used in "Median of Two Sorted
    Arrays" (LeetCode 4), but generalized to any k instead of the
    midpoint.

    ────────────────────────────────────────────────────────────────────
    CORE IDEA
    ────────────────────────────────────────────────────────────────────

    We want to pick a total of k elements for the "left bucket" —
    some from A, the rest from B — such that every element we picked
    is ≤ every element we didn't pick. That boundary gives us the
    k-th smallest.

    Let:
        i = number of elements contributed by A  (0 ≤ i ≤ min(m, k))
        j = k − i  (the rest come from B)

    The partition looks like:

        A:  [ a0  a1 ... a(i-1) | a(i)  a(i+1) ... a(m-1) ]
                 ← left A →           ← right A →

        B:  [ b0  b1 ... b(j-1) | b(j)  b(j+1) ... b(n-1) ]
                 ← left B →           ← right B →

    Boundary values:
        a1 = A[i−1]   (max of A's left)       a2 = A[i]     (min of A's right)
        b1 = B[j−1]   (max of B's left)       b2 = B[j]     (min of B's right)

    Edge sentinels:
        i = 0  →  a1 = −∞       i = m  →  a2 = +∞
        j = 0  →  b1 = −∞       j = n  →  b2 = +∞

    ────────────────────────────────────────────────────────────────────
    VALID PARTITION CONDITION
    ────────────────────────────────────────────────────────────────────

    We need every element in the left bucket ≤ every element in the
    right bucket. Since each array is already sorted internally:
        a1 ≤ a2  (guaranteed by A's sort order)
        b1 ≤ b2  (guaranteed by B's sort order)

    So only the CROSS-ARRAY checks matter:
        a1 ≤ b2   AND   b1 ≤ a2

    ────────────────────────────────────────────────────────────────────
    BINARY SEARCH LOGIC
    ────────────────────────────────────────────────────────────────────

    We binary-search on `i` (how many elements A contributes to the
    left bucket). `j` is determined: j = k − i.

    hi = min(k, m)      // if A has 8 elements 
                        // and k=3 so
                        // at max the answer will lie upto k. Here m>k
                        // if A has 3 elements
                        // and k=8 so
                        // at max we can take m elements i.e. 3. Here m<k
                        // so hi = upto how many elements we can take from A?
                        // its either min(k, m) -> k when m>k and m when m<k
    
    lo = max(0, k-n)    // if A has 5 elements 
                        // and B has 1 elements
                        // and k = 6, then how many elements should we take from A? 
                        // We can take at max 1 elements from B. So remaining elements
                        // will come from A. So we have to take the remaining elements
                        // i.e. k-n = 6 - 1 = 5 elements from A.


    ── Why lo = 0, hi = m FAILS for arbitrary k ──────────────────────

    In the Median problem, k is always (m+n+1)/2 and we guarantee
    m ≤ n via a swap, so j = k − i naturally lands in [0, n] for any
    i in [0, m]. But for arbitrary k that safety net doesn't exist.

    FAILURE 1 — hi = m when k < m  (j goes NEGATIVE)
    ─────────────────────────────────────────────────
        A = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]     m = 10
        B = [20, 30, 40, 50, 60]                n = 5
        k = 3

        With hi = m = 10, binary search could try i = 5:
            j = k − i = 3 − 5 = −2        ← NEGATIVE INDEX INTO B!

        B[−2 − 1] and B[−2] are out-of-bounds → crash / undefined.

        Fix:  hi = min(k, m) = min(3, 10) = 3
              Now i can be at most 3, so j = 3 − 3 = 0 (safe, means
              we take nothing from B and use the −∞ sentinel).

    FAILURE 2 — lo = 0 when k > n  (j EXCEEDS n)
    ──────────────────────────────────────────────
        A = [1, 2, 3, 4, 5, 6, 7, 8]            m = 8
        B = [10, 20, 30]                        n = 3
        k = 6

        With lo = 0, binary search could try i = 0:
            j = k − i = 6 − 0 = 6             ← BUT B ONLY HAS 3 ELEMENTS!

        B[5] is out-of-bounds → crash / undefined.

        Fix:  lo = max(0, k − n) = max(0, 6 − 3) = 3
              Now i is at least 3, so j = 6 − 3 = 3 = n (safe, means
              we take ALL of B and use the +∞ sentinel for b2).

    ── Correct bounds ────────────────────────────────────────────────

    Combining both constraints on j = k − i:
        j ≥ 0   →  i ≤ k       →  hi = min(k, m)
        j ≤ n   →  i ≥ k − n   →  lo = max(0, k − n)

    These guarantee j stays in [0, n] for every candidate i, making
    the sentinel logic (−∞ / +∞) sufficient without any out-of-bounds
    access.

    Note: Both problems swap to ensure m ≤ n. The difference is the
    value of k. In the Median problem k = (m+n+1)/2, and with m ≤ n:
        lo = max(0, (m+n+1)/2 − n)
           = max(0, (m−n+1)/2)
           = 0                       (because m ≤ n → m−n+1 ≤ 1 ≤ 0 after int div)
        hi = min((m+n+1)/2, m)
           = m                       (because (m+n+1)/2 ≥ m when m ≤ n)
    So the general bounds collapse to lo = 0, hi = m automatically.

    Here, k is arbitrary — it can be 1, or m+n, or anything in between.
    The swap alone doesn't constrain k enough, so we need the full
    general bounds.

    Search bounds:
        lo = max(0, k − n)
        hi = min(k, m)

    At each mid:

    CASE 1: a1 ≤ b2  AND  b1 ≤ a2  →  VALID
    ──────────────────────────────────────────
        The left bucket has exactly k elements and everything in it is
        ≤ everything outside. The k-th smallest = max(a1, b1) — the
        largest element in the left bucket.

    CASE 2: a1 > b2  →  Took TOO MANY from A
    ──────────────────────────────────────────
        A's left max exceeds B's right min. We need to shrink A's
        contribution. Move hi = mid − 1.

        Example:
            A:  [ ... 15 | 20 ... ]     a1 = 15
            B:  [ ... 8  | 10 ... ]     b2 = 10
            15 > 10 → a1 is too large for the left bucket → take fewer from A.

    CASE 3: b1 > a2  →  Took TOO FEW from A
    ──────────────────────────────────────────
        B's left max exceeds A's right min. Since j = k − i, taking
        fewer from A means more from B, inflating b1. Fix: take more
        from A. Move lo = mid + 1.

        Example:
            A:  [ ... 3  | 5  ... ]     a2 = 5
            B:  [ ... 12 | 18 ... ]     b1 = 12
            12 > 5 → b1 is too large → give more to A, less to B.

    This is monotonic — increasing i makes a1 grow and b1 shrink,
    and decreasing i does the opposite — so binary search converges.

    ────────────────────────────────────────────────────────────────────
    WHY SEARCH ON THE SMALLER ARRAY
    ────────────────────────────────────────────────────────────────────

    If m > n, swap A and B. This:
        1. Reduces iterations: O(log(min(m, n, k))).
        2. Prevents j from going out of bounds: when m ≤ n, the
           constraint lo = max(0, k−n) ≤ i ≤ min(k, m) = hi keeps
           j = k − i within [0, n].

    ────────────────────────────────────────────────────────────────────
    RELATION TO MEDIAN OF TWO SORTED ARRAYS
    ────────────────────────────────────────────────────────────────────

    Median is just this problem with k = (m + n + 1) / 2. For even
    totals, you also need min(a2, b2) to average the two middle
    elements. Here we only need max(a1, b1).

    ============================================================================
    Dry Run 1:  A = [2, 3, 6, 7, 9],  B = [1, 4, 8, 10],  k = 5
                m = 5,  n = 4
                Search on B (smaller). After swap: A = [1, 4, 8, 10], B = [2, 3, 6, 7, 9]
                m = 4, n = 5
                lo = max(0, 5−5) = 0,  hi = min(5, 4) = 4
    ============================================================================

    Iteration 1:  mid = 2  →  i = 2 from A, j = 3 from B
    ┌───────────────────────────────────────────────────────┐
    │  A:  [ 1, 4 | 8, 10 ]       a1 = 4,   a2 = 8        │
    │  B:  [ 2, 3, 6 | 7, 9 ]     b1 = 6,   b2 = 7        │
    │                                                       │
    │  a1(4) ≤ b2(7)?  YES  ✓                              │
    │  b1(6) ≤ a2(8)?  YES  ✓                              │
    │                                                       │
    │  VALID! answer = max(a1, b1) = max(4, 6) = 6         │
    └───────────────────────────────────────────────────────┘

    Verify: merged = [1, 2, 3, 4, 6, 7, 8, 9, 10]  →  5th = 6  ✓

    ============================================================================
    Dry Run 2:  A = [1, 2],  B = [3, 4, 5, 6],  k = 4
                m = 2,  n = 4  (A already smaller)
                lo = max(0, 4−4) = 0,  hi = min(4, 2) = 2
    ============================================================================

    Iteration 1:  mid = 1  →  i = 1 from A, j = 3 from B
    ┌───────────────────────────────────────────────────────┐
    │  A:  [ 1 | 2 ]              a1 = 1,   a2 = 2         │
    │  B:  [ 3, 4, 5 | 6 ]        b1 = 5,   b2 = 6         │
    │                                                       │
    │  a1(1) ≤ b2(6)?  YES  ✓                              │
    │  b1(5) ≤ a2(2)?  NO   ✗                              │
    │                                                       │
    │  b1 > a2  →  too few from A  →  lo = 2               │
    └───────────────────────────────────────────────────────┘

    Iteration 2:  mid = 2  →  i = 2 from A, j = 2 from B
    ┌───────────────────────────────────────────────────────┐
    │  A:  [ 1, 2 | ]             a1 = 2,   a2 = +∞        │
    │  B:  [ 3, 4 | 5, 6 ]        b1 = 4,   b2 = 5         │
    │                                                       │
    │  a1(2)  ≤ b2(5)?   YES  ✓                            │
    │  b1(4)  ≤ a2(+∞)?  YES  ✓                            │
    │                                                       │
    │  VALID! answer = max(2, 4) = 4                        │
    └───────────────────────────────────────────────────────┘

    Verify: merged = [1, 2, 3, 4, 5, 6]  →  4th = 4  ✓

    ============================================================================
    Dry Run 3 (edge):  A = [1, 3, 5],  B = [2, 4, 6],  k = 1
                       m = 3,  n = 3
                       lo = max(0, 1−3) = 0,  hi = min(1, 3) = 1
    ============================================================================

    Iteration 1:  mid = 0  →  i = 0 from A, j = 1 from B
    ┌───────────────────────────────────────────────────────┐
    │  A:  [ | 1, 3, 5 ]          a1 = −∞,  a2 = 1         │
    │  B:  [ 2 | 4, 6 ]           b1 = 2,   b2 = 4         │
    │                                                       │
    │  a1(−∞) ≤ b2(4)?  YES  ✓                             │
    │  b1(2)  ≤ a2(1)?  NO   ✗                             │
    │                                                       │
    │  b1 > a2  →  lo = 1                                  │
    └───────────────────────────────────────────────────────┘

    Iteration 2:  mid = 1  →  i = 1 from A, j = 0 from B
    ┌───────────────────────────────────────────────────────┐
    │  A:  [ 1 | 3, 5 ]           a1 = 1,   a2 = 3         │
    │  B:  [ | 2, 4, 6 ]          b1 = −∞,  b2 = 2         │
    │                                                       │
    │  a1(1)  ≤ b2(2)?   YES  ✓                            │
    │  b1(−∞) ≤ a2(3)?   YES  ✓                            │
    │                                                       │
    │  VALID! answer = max(1, −∞) = 1                       │
    └───────────────────────────────────────────────────────┘

    Verify: merged = [1, 2, 3, 4, 5, 6]  →  1st = 1  ✓

    ============================================================================
    Complexity
    ============================================================================
    Approach 1 — Merge Walk:     Time O(k),              Space O(1)
    Approach 2 — Binary Search:  Time O(log(min(m,n,k))), Space O(1)
*/

// ============================================================================
// Approach 1: Merge Walk — O(k) / O(1)
// ============================================================================
class Solution1 {
public:
    int kthSmallest(vector<int>& A, vector<int>& B, int k) {
        int m = A.size(), n = B.size();
        int i = 0, j = 0, count = 0, ans = 0;

        while (i < m && j < n) {
            if (A[i] <= B[j]) {
                ans = A[i]; i++;
            } else {
                ans = B[j]; j++;
            }
            count++;
            if (count == k) return ans;
        }

        while (i < m) {
            ans = A[i]; i++; count++;
            if (count == k) return ans;
        }

        while (j < n) {
            ans = B[j]; j++; count++;
            if (count == k) return ans;
        }

        return ans;
    }
};

// ============================================================================
// Approach 2: Binary Search on Partition — O(log(min(m, n, k))) / O(1)
// ============================================================================
class Solution2 {
public:
    int kthSmallest(vector<int>& A, vector<int>& B, int k) {
        // Always binary-search on the smaller array
        if (A.size() > B.size())
            return kthSmallest(B, A, k);

        int m = A.size();
        int n = B.size();

        // i ranges: can't take negative from B, can't exceed m or k
        int lo = max(0, k - n);
        int hi = min(k, m);

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;

            int i = mid;          // elements from A in left bucket
            int j = k - i;        // elements from B in left bucket

            int a1 = (i == 0) ? INT_MIN : A[i - 1];   // max of A's left
            int a2 = (i == m) ? INT_MAX : A[i];        // min of A's right

            int b1 = (j == 0) ? INT_MIN : B[j - 1];   // max of B's left
            int b2 = (j == n) ? INT_MAX : B[j];        // min of B's right

            if (a1 <= b2 && b1 <= a2) {
                // Valid partition — k-th smallest is the largest in left bucket
                return max(a1, b1);
            }
            else if (a1 > b2) {
                // Took too many from A
                hi = mid - 1;
            }
            else {
                // Took too few from A (b1 > a2)
                lo = mid + 1;
            }
        }

        return -1; // should never reach here if 1 <= k <= m+n
    }
};

int main() {
    // Test 1
    vector<int> a1 = {2, 3, 6, 7, 9};
    vector<int> b1 = {1, 4, 8, 10};

    Solution1 s1;
    Solution2 s2;
    cout << "Merge walk:     k=5 -> " << s1.kthSmallest(a1, b1, 5) << endl;  // 6
    cout << "Binary search:  k=5 -> " << s2.kthSmallest(a1, b1, 5) << endl;  // 6

    // Test 2
    vector<int> a2 = {1, 2};
    vector<int> b2 = {3, 4, 5, 6};
    cout << "Merge walk:     k=4 -> " << s1.kthSmallest(a2, b2, 4) << endl;  // 4
    cout << "Binary search:  k=4 -> " << s2.kthSmallest(a2, b2, 4) << endl;  // 4

    // Test 3 — k=1 (edge)
    vector<int> a3 = {1, 3, 5};
    vector<int> b3 = {2, 4, 6};
    cout << "Merge walk:     k=1 -> " << s1.kthSmallest(a3, b3, 1) << endl;  // 1
    cout << "Binary search:  k=1 -> " << s2.kthSmallest(a3, b3, 1) << endl;  // 1

    // Test 4 — k = m+n (last element)
    cout << "Merge walk:     k=6 -> " << s1.kthSmallest(a3, b3, 6) << endl;  // 6
    cout << "Binary search:  k=6 -> " << s2.kthSmallest(a3, b3, 6) << endl;  // 6

    return 0;
}
