#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 1046 - Last Stone Weight

    You are given an array of integers `stones` where stones[i] is
    the weight of the ith stone.

    On each turn, choose the heaviest two stones and smash them:
        - If x == y, both stones are destroyed.
        - If x != y (x < y), the stone of weight x is destroyed,
          and the stone of weight y now has weight y - x.

    At the end, there is at most one stone left. Return its weight.
    If there are no stones left, return 0.

    Examples:
    ---------

    Example 1:
        Input:  stones = [2, 7, 4, 1, 8, 1]
        Output: 1
        Explanation:
            Smash 7 and 8 → 8-7 = 1 → stones = [2, 4, 1, 1, 1]
            Smash 2 and 4 → 4-2 = 2 → stones = [2, 1, 1, 1]
            Smash 2 and 1 → 2-1 = 1 → stones = [1, 1, 1]
            Smash 1 and 1 → destroyed → stones = [1]
            Return 1.

    Example 2:
        Input:  stones = [1]
        Output: 1

    Example 3:
        Input:  stones = [2, 2]
        Output: 0
        Explanation:
            Smash 2 and 2 → both destroyed → no stones left → return 0.

    Constraints:
    ------------
    - 1 <= stones.length <= 30
    - 1 <= stones[i] <= 1000

    Approach: Max Heap (Greedy)
    ----------------------------
    We always need the two heaviest stones. A max-heap gives us
    the largest element in O(1) and insertion/removal in O(log n).

    Algorithm:
        1. Push all stones into a max-heap.
        2. Keep smashing while there are at least 2 stones to pick:
            a. Pop two heaviest: y (heaviest) and x (second heaviest).
            b. If x == y → both destroyed, don't push anything.
            c. If x != y → push (y - x) back into the heap.
        3. If heap is empty → return 0. Otherwise return the last stone.

    Why greedy works:
    -----------------
    The problem says "choose the heaviest two." There's no choice to
    optimize — the strategy is fixed. We just need to efficiently
    find the two largest each time, which is what a max-heap does.

    Dry Run (stones = [2, 7, 4, 1, 8, 1]):
    ----------------------------------------
    Heap: [8, 7, 4, 2, 1, 1]

    Pop 8, 7 → 8-7=1, push 1.   Heap: [4, 2, 1, 1, 1]
    Pop 4, 2 → 4-2=2, push 2.   Heap: [2, 1, 1, 1]
    Pop 2, 1 → 2-1=1, push 1.   Heap: [1, 1, 1]
    Pop 1, 1 → equal, destroyed. Heap: [1]

    Heap size = 1 → return 1 ✓

    Complexity Analysis:
    --------------------
    Time:  O(n log n) — up to n rounds, each with O(log n) heap ops.
    Space: O(n) — the heap.

*/

class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        // Build max-heap from all stones
        priority_queue<int> maxHeap(stones.begin(), stones.end());

        // Keep smashing while there are at least 2 stones to pick
        while (maxHeap.size() >= 2) {
            // Pop the two heaviest stones (y >= x)
            int y = maxHeap.top(); maxHeap.pop();
            int x = maxHeap.top(); maxHeap.pop();

            // If equal, both destroyed — don't push anything
            if (x == y) continue;

            // Otherwise, the heavier stone survives with reduced weight
            maxHeap.push(y - x);
        }

        // If heap is empty, all stones cancelled out → return 0
        // Otherwise, return the last remaining stone
        return maxHeap.empty() ? 0 : maxHeap.top();
    }
};

int main() {
    Solution obj;

    vector<int> stones1 = {2, 7, 4, 1, 8, 1};
    cout << obj.lastStoneWeight(stones1) << endl;  // Expected: 1

    vector<int> stones2 = {1};
    cout << obj.lastStoneWeight(stones2) << endl;  // Expected: 1

    vector<int> stones3 = {2, 2};
    cout << obj.lastStoneWeight(stones3) << endl;  // Expected: 0

    return 0;
}
