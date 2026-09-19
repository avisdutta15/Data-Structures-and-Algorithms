#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 1825 - Finding MK Average

    You are given two integers `m` and `k`, and a stream of integers.
    Implement the MKAverage class:
        - MKAverage(int m, int k): initializes the object.
        - void addElement(int num): adds num to the stream.
        - int calculateMKAverage(): calculates the MK average:
            1. Take the last m elements.
            2. Sort them.
            3. Remove the k smallest and k largest.
            4. Return the floor average of the remaining m - 2k elements.
          If fewer than m elements have been added, return -1.

    Examples:
    ---------

    Example 1:
        MKAverage(3, 1)
        addElement(1)     → stream=[1],     size < 3
        addElement(5)     → stream=[1,5],   size < 3
        addElement(3)     → stream=[1,5,3], sorted=[1,3,5]
                            remove k=1 smallest(1) and largest(5) → [3]
        calculateMKAverage() → 3

        addElement(9)     → stream=[5,3,9], sorted=[3,5,9]
                            remove 3 and 9 → [5]
        calculateMKAverage() → 5

    Example 2:
        MKAverage(3, 1)
        addElement(3), addElement(1)
        calculateMKAverage() → -1  (less than m elements)
        addElement(10)       → stream=[3,1,10], sorted=[1,3,10]
                               remove 1 and 10 → [3]
        calculateMKAverage() → 3

    Constraints:
    ------------
    - 3 <= m <= 10^5
    - 1 <= k, k * 2 < m
    - 1 <= num <= 10^5
    - At most 10^5 calls to addElement and calculateMKAverage.

    Approach: Three Multisets or buckets (lo, mid, hi)
    -----------------------------------------
    Maintain the last m elements split into three sorted groups:

        [ lo (k smallest) | mid (m-2k middle) | hi (k largest) ]

    midSum tracks the running sum of mid. The MK average is just
    midSum / (m - 2k).

    The size of the current stream and the three buckets should be m.
    i.e. lo.size() + mid.size() + hi.size() = m;
    if lo.size() == k and hi.size() == k
    then mid.size() = m - (lo.size() + hi.size())
                    = m - k - k
                    = m - 2k 

    Invariants:
        1. lo.size() == k, mid.size() == m-2k, hi.size() == k
        2. max(lo) <= min(mid) <= max(mid) <= min(hi)

    Why multiset?
        - We need to remove an arbitrary element (the oldest in the
          stream) from whichever group it belongs to. Multiset does
          this in O(log m). Heaps can't remove from the middle.
        - Multiset stays sorted, so we can access min/max in O(1)
          via begin()/rbegin().

    Algorithm for addElement(num):
    ------------------------------
    1. Push num into the stream queue. Insert num into mid bucket.

    2. If stream.size() == m (first time reaching m elements):
        - Move k smallest from mid to lo (using midToLo).
        - Move k largest from mid to hi (using midToHi).

    3. If stream.size() > m:
        a) Remove the oldest element from the stream and from
           whichever group (lo/mid/hi) it belongs to.
        b) Fix sizes: if lo or hi lost an element, refill from mid.
           Only one can be short (we removed one, added one to mid).
        c) Rebalance ordering: after the size fix, mid might have a
           value that violates lo < mid < hi. Swap to fix:
           - If lo's max > mid's min: swap them.
           - If mid's max > hi's min: swap them.

    When is rebalancing needed? (Example):
    ----------------------------------------

        m=3, k=1. State: lo=[1], mid=[3], hi=[5]
        addElement(9):
            mid = [3, 9]. Remove oldest = 1 from lo. lo = [], mid = [3,9], hi=[5].
            Fix size: midToLo → move 3 to lo. lo=[3], mid=[9], hi=[5].
            Now mid=[9], hi=[5]. 9 > 5! Ordering broken.
            Rebalance: swap 9 and 5. lo=[3], mid=[5], hi=[9] ✓

    Helper functions:
    ------------------
        loToMid:  move lo's largest  → mid  (midSum += val)
        midToLo:  move mid's smallest → lo  (midSum -= val)
        midToHi:  move mid's largest  → hi  (midSum -= val)
        hiToMid:  move hi's smallest  → mid (midSum += val)

    Important: use erase(find(element)), not erase(element).
    erase(element) removes ALL copies. find() gives an iterator
    to ONE copy — erase by iterator removes just that one.

    Complexity Analysis:
    --------------------
    addElement:          O(log m) — multiset insert/erase.
    calculateMKAverage:  O(1) — return midSum / (m - 2k).
    Space:               O(m) — three multisets + queue.

*/


class MKAverage {
private:
    multiset<int> lo, mid, hi;
    queue<int> stream;
    long long midSum;
    int m, k;

    void loToMid() {
        int element = *lo.rbegin();
        lo.erase(lo.find(element));     // not lo.erase(element); as this removes all copies of element.
        mid.insert(element);
        midSum = midSum + element;
    }

    void midToLo() {
        int element = *mid.begin();
        mid.erase(mid.find(element));
        lo.insert(element);
        midSum = midSum - element;
    }

    void midToHi() {
        int element = *mid.rbegin();
        mid.erase(mid.find(element));
        hi.insert(element);             // fixed: was lo.insert
        midSum = midSum - element;
    }

    void hiToMid() {
        int element = *hi.begin();
        hi.erase(hi.find(element));     // not lo.erase(element); as this removes all copies of element.
        mid.insert(element);
        midSum = midSum + element;
    }

public:
    MKAverage(int m, int k) {
        this->midSum = 0;
        this->m = m;
        this->k = k;
    }

    void addElement(int num) {
        // 1. Add to stream
        stream.push(num);

        // 2. Add to mid bucket
        mid.insert(num);
        midSum = midSum + num;

        // 3. if stream.size == m then for the first time insert into lo and hi
        if(stream.size() == m){
            while(lo.size()!=k){
                midToLo();
            }

            while(hi.size()!=k){
                midToHi();
            }
        }
        
        // 4. if stream.size > m then delete from stream and fix the size
        //    also rebalance lo-mid and mid-hi

        else if (stream.size() > m){
            // 1. Remove from stream
            int element = stream.front();
            stream.pop();
            
            // 2. Remove the element from the correct bucket
            if(lo.count(element) > 0)
                lo.erase(lo.find(element));
            else if(mid.count(element) > 0){
                mid.erase(mid.find(element));
                midSum = midSum - element;
            }
            else
                hi.erase(hi.find(element));


            // Fix the size and Rebalance
            // stream 1 3 5 9   m = 3 and k = 1
            // lo = [1]     mid = [3]     hi = [5]
            // num = 9
            // lo = [1]     mid = [3, 9]  hi = [5]
            // oldest element = 1
            // lo = []      mid = [3, 9]  hi = [5]
            // Fix size of lo
            // lo = [3]     mid = [9]     hi = [5]
            // Need to rebalance mid and hi
            // lo = [3]     mid = [5]     hi = [9]
            
            // 3. If the removed element belonged to either lo or hi, their size will come < k.
            //    Fix size of lo and hi buckets
            if(lo.size() < k){
                midToLo();
            }
            else if(hi.size() < k){
                midToHi();
            }

            // 4. Rebalance if invariant of lo < mid < hi is broken.
            //    This can happen if the new element added to mid broke the invariant.
            if(*lo.rbegin() > *mid.begin()){
                loToMid();
                midToLo();
            }
            if(*mid.rbegin() > *hi.begin()){
                midToHi();
                hiToMid();
            }
        }
    }
    
    int calculateMKAverage() {
        return stream.size() == m ? midSum / (m - 2 * k) : -1;
    }
};

int main() {
    // Test case from LeetCode:
    // m=3, k=1 → keep last 3, remove 1 smallest & 1 largest, average the middle 1
    MKAverage obj(3, 1);

    obj.addElement(3716);
    obj.addElement(51094);
    cout << obj.calculateMKAverage() << endl;   // -1 (only 2 elements, need 3)

    obj.addElement(56724);
    // stream=[3716,51094,56724], sorted=[3716,51094,56724]
    // remove 3716 and 56724 → middle=[51094]
    cout << obj.calculateMKAverage() << endl;   // 51094

    obj.addElement(79619);
    // stream=[51094,56724,79619], sorted=[51094,56724,79619]
    // remove 51094 and 79619 → middle=[56724]
    cout << obj.calculateMKAverage() << endl;   // 56724

    obj.addElement(99914);
    // stream=[56724,79619,99914], sorted=[56724,79619,99914]
    // remove 56724 and 99914 → middle=[79619]
    cout << obj.calculateMKAverage() << endl;   // 79619

    obj.addElement(277);
    // stream=[79619,99914,277], sorted=[277,79619,99914]
    // remove 277 and 99914 → middle=[79619]
    cout << obj.calculateMKAverage() << endl;   // 79619

    obj.addElement(91205);
    // stream=[99914,277,91205], sorted=[277,91205,99914]
    // remove 277 and 99914 → middle=[91205]
    cout << obj.calculateMKAverage() << endl;   // 91205

    return 0;
}