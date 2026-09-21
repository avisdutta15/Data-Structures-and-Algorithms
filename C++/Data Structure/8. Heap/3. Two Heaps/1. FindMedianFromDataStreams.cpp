#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 295 - Find Median from Data Stream

    The median is the middle value in an ordered integer list.
    If the list has even size, the median is the average of the
    two middle values.

    Implement the MedianFinder class:
        - MedianFinder(): initializes the object.
        - void addNum(int num): adds num to the data stream.
        - double findMedian(): returns the median of all elements so far.

    Examples:
    ---------

    Example 1:
        addNum(1)  → stream = [1],       median = 1
        addNum(2)  → stream = [1, 2],    median = 1.5
        findMedian() → 1.5
        addNum(3)  → stream = [1, 2, 3], median = 2
        findMedian() → 2.0

    Constraints:
    ------------
    - -10^5 <= num <= 10^5
    - At most 5 * 10^4 calls to addNum and findMedian.
    - findMedian is called only after at least one addNum.

    Approach: Two Heaps (Max-Heap + Min-Heap)
    -------------------------------------------
    Split the sorted stream into two halves:

        [smaller half]  |  [larger half]
         lo (max-heap)      hi (min-heap)
         top = largest      top = smallest
         of smaller half    of larger half

    The median lives at the boundary:
        - Even count: average of lo.top() and hi.top()
        - Odd count:  lo.top() (lo has the extra element)

    Two invariants:
        1. Every element in lo <= every element in hi.
        2. lo.size() == hi.size() OR lo.size() == hi.size() + 1.

    Two approaches to maintain these invariants:

    Approach 1 — "Decide which heap" (MedianFinder1):
        Compare num with lo.top() to decide where it goes.
        Then rebalance sizes if needed.
        More intuitive — explicit decision about placement.

    Approach 2 — "Route through lo" (MedianFinder2):
        Always push to lo first, then move lo's max to hi.
        This auto-guarantees ordering. Then fix sizes.
        More elegant — fewer branches, ordering is automatic.

    Both are O(log n) per addNum, O(1) per findMedian.

    Dry Run (addNum: 5, 3, 8, 2):
    -------------------------------

    addNum(5):  lo=[5], hi=[]          median = 5
    addNum(3):  lo=[3], hi=[5]         median = (3+5)/2 = 4
    addNum(8):  lo=[5,3], hi=[8]       median = 5
    addNum(2):  lo=[3,2], hi=[5,8]     median = (3+5)/2 = 4

    Complexity Analysis:
    --------------------
    addNum:      O(log n) — heap push/pop.
    findMedian:  O(1) — just peek at heap tops.
    Space:       O(n) — two heaps store all elements.

*/

class MedianFinder1 {
private:
    // lo and hi represent the left and right halves of the data stream
    // lo holds the smaller half (max-heap), hi holds the larger half (min-heap)
    // lo is always == or 1 more in size of hi
    // if lo.size() == hi.size()  -> this means we have even number of data
    //      return lo.top() + hi.top() / 2.0
    // if lo.size() > hi.size() -> this means we have odd number of data
    //      return lo.top()

    priority_queue<int> lo;                             // max-heap for left half
    priority_queue<int, vector<int>, greater<int>> hi;  // min-heap for right half

    void rebalance() {
        // lo got too big has more than 1 elements than hi → move one to hi
        if (lo.size() > hi.size() + 1) {
            hi.push(lo.top());
            lo.pop();
        }
        // hi got too big (or equal but we want lo to have the extra) → move one to lo
        else if (hi.size() > lo.size()) {
            lo.push(hi.top());
            hi.pop();
        }
    }

public:
    MedianFinder1() {

    }

    void addNum(int num) {

        // 1. Add the number to the appropriate heap
        if (lo.empty() || num <= lo.top())
            lo.push(num);
        else
            hi.push(num);

        rebalance();
    }

    double findMedian() {
        if (lo.size() == hi.size())
            return (lo.top() + hi.top()) / 2.0;  // average of two middle values
        return lo.top();
    }
};

class MedianFinder2 {
private:
    // lo and hi represent the left and right halves of the data stream
    // lo holds the smaller half (max-heap), hi holds the larger half (min-heap)
    // lo is always == or 1 more in size of hi
    // if lo.size() == hi.size()  -> this means we have even number of data
    //      return lo.top() + hi.top() / 2.0
    // if lo.size() > hi.size() -> this means we have odd number of data
    //      return lo.top()

    priority_queue<int> lo;                             // max-heap for left half
    priority_queue<int, vector<int>, greater<int>> hi;  // min-heap for right half
public:
    MedianFinder2() {

    }

    void addNum(int num) {

        // 1. Add to left side
        lo.push(num);

        // 2. From left side transfer to right side to maintain the == size invariant
        hi.push(lo.top());
        lo.pop();

        // 3. If lo.size < hi.size then move from right to left to maintain lo.size > hi.size invariant
        if(lo.size() == hi.size())
            return;
        else if(lo.size() < hi.size()){
            lo.push(hi.top());
            hi.pop();
        }
    }

    double findMedian() {
        if(lo.size() == hi.size())
            return (lo.top() + hi.top())/2.0;  // average of two middle values
        return lo.top();
    }
};

int main() {
    // Test MedianFinder1 (decide which heap)
    cout << "MedianFinder1:" << endl;
    MedianFinder1 mf1;
    mf1.addNum(1);
    mf1.addNum(2);
    cout << mf1.findMedian() << endl;  // Expected: 1.5
    mf1.addNum(3);
    cout << mf1.findMedian() << endl;  // Expected: 2

    // Test MedianFinder2 (route through lo)
    cout << "MedianFinder2:" << endl;
    MedianFinder2 mf2;
    mf2.addNum(1);
    mf2.addNum(2);
    cout << mf2.findMedian() << endl;  // Expected: 1.5
    mf2.addNum(3);
    cout << mf2.findMedian() << endl;  // Expected: 2

    return 0;
}