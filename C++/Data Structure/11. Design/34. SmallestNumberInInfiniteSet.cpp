#include <iostream>
#include <set>
#include <vector>

using namespace std;

/*
    https://www.youtube.com/watch?v=qiSjBraBzLM
    
    Problem Statement:
    ------------------
    LeetCode 2336 - Smallest Number in Infinite Set

    You have a set containing all positive integers {1, 2, 3, ...}.
    Implement the SmallestInfiniteSet class:
        - SmallestInfiniteSet(): initializes the set with all positive integers.
        - int popSmallest():     removes and returns the smallest integer.
        - void addBack(int num): adds num back if it's not already present.

    Examples:
    ---------

    Example 1:
        SmallestInfiniteSet s;
        s.addBack(2);          // 2 already present, no-op
        s.popSmallest();       // returns 1
        s.popSmallest();       // returns 2
        s.popSmallest();       // returns 3
        s.addBack(1);          // 1 was popped, add it back
        s.popSmallest();       // returns 1 (it's back!)
        s.popSmallest();       // returns 4

    Constraints:
    ------------
    - 1 <= num <= 1000
    - At most 1000 calls to popSmallest and addBack.

    
    Approach:
    ----------
    popSmallest():
        If addedBack has elements → pop the smallest from it.
        Otherwise → return current and increment it.

    addBack(num):
        If num < current → insert into addedBack.
        (set handles duplicates automatically — ignores if present.)

    Dry Run:
    --------
    current = 1, addedBack = {}

    popSmallest(): addedBack empty → return 1, current=2
    popSmallest(): addedBack empty → return 2, current=3
    popSmallest(): addedBack empty → return 3, current=4

    addBack(2):   2 < 4 → addedBack = {2}
    addBack(1):   1 < 4 → addedBack = {1, 2}

    popSmallest(): addedBack = {1, 2} → pop 1. addedBack = {2}. return 1
    popSmallest(): addedBack = {2}    → pop 2. addedBack = {}. return 2
    popSmallest(): addedBack empty    → return 4, current=5

    Intuition — Why do we need `current` and `addedBack`?
    ------------------------------------------------------
    Think of the infinite set as a number line:

        [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, ...]

    When you pop, you remove from the left:

        Pop 1: [_, 2, 3, 4, 5, 6, 7, 8, ...]
        Pop 2: [_, _, 3, 4, 5, 6, 7, 8, ...]
        Pop 3: [_, _, _, 4, 5, 6, 7, 8, ...]

    At this point, `current = 4`. Everything from 4 onward is
    untouched. We don't need to store {4, 5, 6, 7, ...} — we
    just know "everything >= 4 exists." That's what `current`
    represents.

    Now someone calls addBack(2):

        [_, 2, _, 4, 5, 6, 7, 8, ...]

    2 is back, but it sits BELOW current. We can't represent
    this with just `current`. We need somewhere to store these
    added-back numbers. That's what the `addedBack` set is for.

        current = 4          → "everything >= 4 exists"
        addedBack = {2}      → "also, 2 exists (it was added back)"

    Together they fully describe which numbers are in the set
    without storing infinitely many elements.

    Why `if (num < current)` in addBack?
    -------------------------------------
    If num >= current, it was never popped — it's still in the
    infinite set. No need to add it back.

        current = 4 means: {1,2,3} popped, {4,5,6,...} still exist.

        addBack(2): 2 < 4 → was popped → needs to be added back ✓
        addBack(5): 5 >= 4 → never popped → already exists → skip
        addBack(4): 4 >= 4 → already exists → skip

    Complexity Analysis:
    --------------------
    popSmallest(): O(log n) — set min access + erase.
    addBack():     O(log n) — set insert.
    Space:         O(n) — at most n added-back elements.

*/


class SmallestInfiniteSet1 {
private:
    int smallest;            // smallest number never popped ("everything >= current exists")
    vector<bool> nums;
public:
    SmallestInfiniteSet1(){
        smallest = 1;
        nums = vector<bool> (1001, true);
    }

    int popSmallest() {
        int result = smallest;
        
        nums[smallest] = false;

        // find the next smallest
        for(int i=smallest + 1; i<nums.size(); i++){
            if(nums[i] == true){
                smallest = i;
                break;
            }
        }

        return result;
    }

    void addBack(int num) {
        nums[num] = true;

        // update smallest if needed
        if(num < smallest){
            smallest = num;
        }
    }
};

class SmallestInfiniteSet {
private:
    int current;            // smallest number never popped ("everything >= current exists")
    set<int> addedBack;     // numbers below current that were added back (sorted, no dups)

public:
    SmallestInfiniteSet(){
        current = 1;
    }

    int popSmallest() {
        // If there are added-back numbers smaller than current, pop the smallest
        if (!addedBack.empty()) {
            int smallest = *addedBack.begin();
            addedBack.erase(addedBack.begin());
            return smallest;
        }

        // Otherwise, pop from the infinite set and advance the boundary
        return current++;
    }

    void addBack(int num) {
        // Only add back if it was actually popped (num < current).
        // If num >= current, it's still in the infinite set — nothing to do.
        // set::insert handles duplicates automatically (ignores if present).
        if (num < current) {
            addedBack.insert(num);
        }
    }
};

int main() {
    SmallestInfiniteSet s;

    // Pop first three
    cout << s.popSmallest() << endl;   // 1
    cout << s.popSmallest() << endl;   // 2
    cout << s.popSmallest() << endl;   // 3

    // Add back 2 and 1
    s.addBack(2);
    s.addBack(1);

    // Pop — should get added-back numbers first (sorted)
    cout << s.popSmallest() << endl;   // 1
    cout << s.popSmallest() << endl;   // 2

    // Now back to the infinite set
    cout << s.popSmallest() << endl;   // 4

    // Add back something already present (5 >= current=5, no-op)
    s.addBack(5);
    cout << s.popSmallest() << endl;   // 5 (from infinite set, addBack was no-op)

    return 0;
}
