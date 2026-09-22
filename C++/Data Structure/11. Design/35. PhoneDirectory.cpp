#include <iostream>
#include <set>
#include <queue>
#include <unordered_set>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 379 - Design Phone Directory

    Design a phone directory that initially has maxNumbers empty slots
    (numbered 0 to maxNumbers-1). It should support:
        - int get():           provide any available number, mark as used.
                               return -1 if none available.
        - bool check(number):  check if a number is available.
        - void release(number): recycle a number, making it available again.

    Examples:
    ---------

    Example 1:
        PhoneDirectory dir(3);   // slots: {0, 1, 2}
        dir.get();               // returns 0. available: {1, 2}
        dir.get();               // returns 1. available: {2}
        dir.check(2);            // true (available)
        dir.get();               // returns 2. available: {}
        dir.get();               // returns -1 (none available)
        dir.release(2);          // available: {2}
        dir.check(2);            // true
        dir.get();               // returns 2

    Constraints:
    ------------
    - 1 <= maxNumbers <= 10^4
    - 0 <= number < maxNumbers
    - At most 2 * 10^4 calls to get, check, release.

    Comparison with Smallest Infinite Set (LC 2336):
    --------------------------------------------------
    LC 2336: infinite set {1, 2, 3, ...} — use `current` + set.
    LC 379:  finite set {0, 1, ..., n-1} — can just store all
             available numbers in a set. No `current` trick needed
             since the set is small enough to enumerate.

    Approach 1 : Set of available numbers
    ------------------------------------
    Initialize a set with all numbers {0, 1, ..., maxNumbers-1}.
        get():     pop the smallest from the set. O(log n).
        check():   check if number is in the set. O(log n).
        release(): insert number back into the set. O(log n).

    The set automatically handles:
        - Sorted order (get returns smallest available).
        - No duplicates (release on an already-available number is safe).

    Dry Run (maxNumbers = 3):
    --------------------------
    Init:       available = {0, 1, 2}

    get():      pop 0.   available = {1, 2}.  return 0
    get():      pop 1.   available = {2}.     return 1
    check(2):   2 in set → true
    get():      pop 2.   available = {}.      return 2
    get():      empty → return -1
    release(2): available = {2}
    check(2):   2 in set → true
    get():      pop 2.   available = {}.      return 2

    Complexity Analysis:
    --------------------
    get:      O(log n) — set min access + erase.
    check:    O(log n) — set lookup.
    release:  O(log n) — set insert (ignores duplicates).
    Space:    O(n) — set stores at most n numbers.


    Approach 2 : Queue + Unordered Set — O(1) amortized
    ------------------------------------
    Faster than set approach: O(1) for all operations instead of O(log n).
    Queue provides the next available number.
    Unordered set tracks which numbers are currently available (for O(1) check
    and duplicate prevention on release).

    Trade-off: get() doesn't return the smallest — it returns whatever is
    at the front of the queue. The problem says "provide ANY available number,"
    so this is fine.
*/

class PhoneDirectory {
private:
    set<int> available;  // all currently available phone numbers

public:
    // Initialize with all numbers {0, 1, ..., maxNumbers-1}
    PhoneDirectory(int maxNumbers) {
        for (int i = 0; i < maxNumbers; i++)
            available.insert(i);
    }

    // Provide any available number and mark it as used.
    // Return -1 if none available.
    int get() {
        if (available.empty()) return -1;
        int number = *available.begin();  // smallest available
        available.erase(available.begin());  // mark as used
        return number;
    }

    // Check if a number is available (not assigned)
    bool check(int number) {
        return available.count(number) > 0;
    }

    // Recycle a number — make it available again.
    // set::insert ignores duplicates, so releasing an
    // already-available number is safely a no-op.
    void release(int number) {
        available.insert(number);
    }
};

// =============================================================
// Approach 2: Queue + Unordered Set — O(1) amortized
// =============================================================


class PhoneDirectory2 {
private:
    queue<int> available;            // numbers ready to be assigned
    unordered_set<int> availableSet; // O(1) lookup for check() and dedup

public:
    PhoneDirectory2(int maxNumbers) {
        for (int i = 0; i < maxNumbers; i++) {
            available.push(i);
            availableSet.insert(i);
        }
    }

    // Return any available number, mark as used. -1 if none.
    int get() {
        if (available.empty()) return -1;
        int number = available.front();
        available.pop();
        availableSet.erase(number);
        return number;
    }

    // Check if a number is available — O(1)
    bool check(int number) {
        return availableSet.count(number) > 0;
    }

    // Recycle a number. Only add if not already available (dedup).
    void release(int number) {
        if (availableSet.count(number) == 0) {
            available.push(number);
            availableSet.insert(number);
        }
    }
};

int main() {
    // === Approach 1: Set ===
    cout << "=== Set approach ===" << endl;
    PhoneDirectory dir(3);
    cout << dir.get() << endl;        // 0
    cout << dir.get() << endl;        // 1
    cout << dir.check(2) << endl;     // 1 (true)
    cout << dir.get() << endl;        // 2
    cout << dir.get() << endl;        // -1
    dir.release(2);
    cout << dir.check(2) << endl;     // 1 (true)
    cout << dir.get() << endl;        // 2

    // === Approach 2: Queue + Unordered Set ===
    cout << "=== Queue approach ===" << endl;
    PhoneDirectory2 dir2(3);
    cout << dir2.get() << endl;       // 0
    cout << dir2.get() << endl;       // 1
    cout << dir2.check(2) << endl;    // 1 (true)
    cout << dir2.get() << endl;       // 2
    cout << dir2.get() << endl;       // -1
    dir2.release(2);
    cout << dir2.check(2) << endl;    // 1 (true)
    cout << dir2.get() << endl;       // 2

    // Duplicate release test
    dir2.release(2);
    dir2.release(2);
    cout << dir2.get() << endl;       // 2 (only one copy)
    cout << dir2.get() << endl;       // -1

    return 0;
}
