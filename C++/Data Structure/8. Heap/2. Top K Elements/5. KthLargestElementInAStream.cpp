#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 703 - Kth Largest Element in a Stream

    Design a class to find the kth largest element in a stream.
    Note that it is the kth largest element in the sorted order,
    not the kth distinct element.

    Implement the KthLargest class:
        - KthLargest(int k, vector<int>& nums): Initializes the
          object with the integer k and the initial stream nums.
        - int add(int val): Appends val to the stream and returns
          the element representing the kth largest in the stream.

    Examples:
    ---------

    Example 1:
        Input:  k = 3, nums = [4, 5, 8, 2]
                add(3), add(5), add(10), add(9), add(4)
        Output: [null, null, 4, 5, 5, 8, 8]
        Explanation:
            Init with [4, 5, 8, 2], k=3
            Heap (min-heap of size 3): [4, 5, 8] (2 is too small)
            3rd largest = heap top = 4

            add(3): 3 < 4 (top), skip.          3rd largest = 4
            add(5): 5 > 4, pop 4, push 5.       Heap: [5, 5, 8]. 3rd largest = 5
            add(10): 10 > 5, pop 5, push 10.    Heap: [5, 8, 10]. 3rd largest = 5
            add(9): 9 > 5, pop 5, push 9.       Heap: [8, 9, 10]. 3rd largest = 8
            add(4): 4 < 8, skip.                 3rd largest = 8

    Constraints:
    ------------
    - 1 <= k <= 10^4
    - 0 <= nums.length <= 10^4
    - -10^4 <= nums[i] <= 10^4
    - -10^4 <= val <= 10^4
    - At most 10^4 calls will be made to add.
    - At the time of each add call, the stream has at least k elements.

    Approach: Min-Heap of size K
    -----------------------------
    Maintain a min-heap of exactly k elements. The heap top is
    always the kth largest element.

    Why min-heap and not max-heap?
    ------------------------------
    We want the kth LARGEST. If we keep only k elements in a
    min-heap, the smallest of those k is at the top — and that's
    exactly the kth largest overall.

    Everything below the heap top has been discarded (too small
    to be in the top k). Everything in the heap is >= the top.
    So the top = the kth largest.

    Why size k?
    -----------
    - If heap has < k elements: just push (not enough elements yet).
    - If heap has k elements and new val > top: the current top is
      no longer kth largest (it's now (k+1)th). Pop it, push val.
    - If heap has k elements and new val <= top: val is smaller than
      everything in the heap. It can't be in the top k. Ignore it.

    Complexity Analysis:
    --------------------
    Constructor: O(n log k) — push up to n elements, each O(log k).
    add():       O(log k) — one push/pop at most.
    Space:       O(k) — heap stores exactly k elements.

*/

class KthLargest {
private:
    // Min-heap: smallest of the top-k elements is always on top.
    // That smallest = the kth largest overall.
    priority_queue<int, vector<int>, greater<int>> pq;
    int k;

public:
    KthLargest(int k, vector<int>& nums) {
        this->k = k;

        for (int& num : nums) {
            // Heap not full yet — just push
            if (pq.size() < k) {
                pq.push(num);
            }
            // Heap full — only push if num is bigger than the current kth largest
            else if (pq.top() < num) {
                pq.pop();   // remove current kth largest (it's now (k+1)th)
                pq.push(num);
            }
            // If num <= top, it can't be in the top k. Skip.
        }
    }

    int add(int val) {
        // Heap not full yet — just push
        if (pq.size() < k) {
            pq.push(val);
        }
        // Heap full — replace top if val is larger
        else if (pq.top() < val) {
            pq.pop();
            pq.push(val);
        }

        // Top of min-heap = kth largest element
        return pq.top();
    }
};

int main() {
    int k = 3;
    vector<int> nums = {4, 5, 8, 2};
    KthLargest obj(k, nums);

    cout << obj.add(3)  << endl;  // 4  (heap: [4,5,8], 3 < 4 → skip)
    cout << obj.add(5)  << endl;  // 5  (heap: [5,5,8], popped 4)
    cout << obj.add(10) << endl;  // 5  (heap: [5,8,10], popped 5)
    cout << obj.add(9)  << endl;  // 8  (heap: [8,9,10], popped 5)
    cout << obj.add(4)  << endl;  // 8  (heap: [8,9,10], 4 < 8 → skip)

    return 0;
}
