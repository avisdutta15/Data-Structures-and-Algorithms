#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 239 - Sliding Window Maximum

    You are given an array of integers `nums`, and there is a sliding window
    of size `k` which moves from the very left of the array to the very right.
    You can only see the `k` numbers in the window. Each time the sliding
    window moves one position to the right.

    Return an array containing the maximum element in each window position.

    Examples:
    ---------

    Example 1:
        Input:  nums = [1, 3, -1, -3, 5, 3, 6, 7], k = 3
        Output: [3, 3, 5, 5, 6, 7]
        Explanation:
            Window position                Max
            ---------------               -----
            [1  3  -1] -3  5  3  6  7       3
             1 [3  -1  -3] 5  3  6  7       3
             1  3 [-1  -3  5] 3  6  7       5
             1  3  -1 [-3  5  3] 6  7       5
             1  3  -1  -3 [5  3  6] 7       6
             1  3  -1  -3  5 [3  6  7]      7

    Example 2:
        Input:  nums = [1], k = 1
        Output: [1]

    Example 3:
        Input:  nums = [1, -1], k = 1
        Output: [1, -1]

    Constraints:
    ------------
    - 1 <= nums.length <= 10^5
    - -10^4 <= nums[i] <= 10^4
    - 1 <= k <= nums.length

    Approach: Monotonic Deque (Decreasing)
    ---------------------------------------

    Intuition:
    ----------
    The brute force way is: for every window of size k, scan all k elements
    to find the max. That's O(n*k). Can we do better?

    The key observation is that most of the work is redundant. When the window
    slides one step right, we add one new element and remove one old element.
    The max often stays the same. We need a data structure that:
        1. Gives us the current window's max in O(1).
        2. Lets us add/remove elements efficiently as the window slides.

    A Monotonic Decreasing Deque does exactly this.

    What is a Monotonic Decreasing Deque?
    --------------------------------------
    We maintain a deque (double-ended queue) that stores INDICES of elements,
    with a special invariant:

        The values at those indices are always in DECREASING order
        from front to back.

        deque front = index of the LARGEST element in the window
        deque back  = index of the SMALLEST "candidate" element

    So the front of the deque always holds the answer (the max) for the
    current window.

    Why store indices instead of values?
    -------------------------------------
    Because we need to know WHEN an element leaves the window. An element
    at index i leaves the window when start > i. Storing indices lets us
    check this with a simple comparison: if (Q.front() == start), pop it.

    Algorithm Step-by-Step:
    -----------------------
    For each new element nums[end]:

        STEP 1 — Clean the back (maintain decreasing order):
            While the deque is not empty AND nums[Q.back()] < nums[end]:
                pop_back()

            Why? If nums[end] is larger than elements at the back of the
            deque, those elements can NEVER be the maximum for any future
            window. The new element nums[end] is:
                - Larger in value (so it beats them)
                - Further right (so it stays in the window longer)
            They are completely dominated and useless. Remove them.

        STEP 2 — Add the new element:
            push_back(end)

        STEP 3 — Check if window has reached size k:
            If (end - start + 1 == k):
                a) Record result: nums[Q.front()] is the window max.
                b) Expire the leftmost: if Q.front() == start, pop_front().
                   (The element sliding out of the window might be our max.)
                c) Shrink window: start++.

        STEP 4 — Advance: end++.

    Why does the front always hold the max?
    ----------------------------------------
    Because of Step 1. Every time we add a new element, we remove all
    smaller elements from the back. So the deque is always sorted in
    decreasing order. The front is the largest. And because of Step 3b,
    we expire elements that have left the window. So the front is always
    the largest element WITHIN the current window.

    Dry Run (nums = [1, 3, -1, -3, 5, 3, 6, 7], k = 3):
    -----------------------------------------------------
    end=0: nums[0]=1
           Deque: [0]                   window=[1], size<3, no result

    end=1: nums[1]=3
           3 > nums[0]=1, pop 0
           Deque: [1]                   window=[1,3], size<3, no result

    end=2: nums[2]=-1
           -1 < nums[1]=3, keep
           Deque: [1, 2]               window=[1,3,-1], size==3
           Result: nums[1]=3           -> result=[3]
           front=1 != start=0, no pop
           start=1

    end=3: nums[3]=-3
           -3 < nums[2]=-1, keep
           Deque: [1, 2, 3]            window=[3,-1,-3], size==3
           Result: nums[1]=3           -> result=[3,3]
           front=1 == start=1, pop_front!
           Deque: [2, 3]
           start=2

    end=4: nums[4]=5
           5 > nums[3]=-3, pop 3
           5 > nums[2]=-1, pop 2
           Deque: [4]                  window=[-1,-3,5], size==3
           Result: nums[4]=5          -> result=[3,3,5]
           front=4 != start=2, no pop
           start=3

    end=5: nums[5]=3
           3 < nums[4]=5, keep
           Deque: [4, 5]              window=[-3,5,3], size==3
           Result: nums[4]=5          -> result=[3,3,5,5]
           front=4 != start=3, no pop
           start=4

    end=6: nums[6]=6
           6 > nums[5]=3, pop 5
           6 > nums[4]=5, pop 4
           Deque: [6]                 window=[5,3,6], size==3
           Result: nums[6]=6          -> result=[3,3,5,5,6]
           front=6 != start=4, no pop
           start=5

    end=7: nums[7]=7
           7 > nums[6]=6, pop 6
           Deque: [7]                 window=[3,6,7], size==3
           Result: nums[7]=7          -> result=[3,3,5,5,6,7]
           front=7 != start=5, no pop
           start=6

    Final answer: [3, 3, 5, 5, 6, 7]  ✓

    Complexity Analysis:
    --------------------
    Time  : O(n) — each element is pushed and popped from the deque at
                   most once. The inner while loop across ALL iterations
                   does at most n pops total (amortized O(1) per element).
    Space : O(k) — the deque holds at most k indices at any time.

*/

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> Q;

        int n = nums.size();
        int start = 0, end = 0;
        vector<int> result;
        while (end < n) {
            // STEP 1: Remove indices from back whose values are smaller
            // than the incoming element — they can never be the max
            while (!Q.empty() && nums[Q.back()] < nums[end]) {
                Q.pop_back();
            }

            // STEP 2: Add current index
            Q.push_back(end);

            int currentWindowLength = end - start + 1;
            if (currentWindowLength < k) {
                // Window not yet full, just expand
                end++;
            }
            else if (currentWindowLength == k) {
                // STEP 3a: Front of deque is the max for this window
                result.push_back(nums[Q.front()]);

                // STEP 3b: If the front index is sliding out, remove it
                if (Q.front() == start)
                    Q.pop_front();

                // Slide the window forward
                start++;
                end++;
            }
        }
        return result;
    }
};

int main() {
    Solution obj;
}
