#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/*
    https://www.youtube.com/watch?v=zyTeznvXCtg
    https://www.youtube.com/watch?v=nztc9MKaask

    
    Problem Statement:
    ------------------
    LeetCode 1642 - Furthest Building You Can Reach

    You are given an integer array `heights` representing building heights,
    along with `bricks` and `ladders`.

    You start at building 0 and move to the next building each step:
        - Next building is shorter or equal → free (go down or flat).
        - Next building is taller → must use EITHER:
            - Bricks: costs exactly (heights[i+1] - heights[i]) bricks.
            - One ladder: covers any height difference for free.

    Return the index of the furthest building you can reach.

    Examples:
    ---------

    Example 1:
        Input:  heights = [4,2,7,6,9,14,12], bricks = 5, ladders = 1
        Output: 4
        Explanation:
            4→2: downhill, free.
            2→7: climb 5, use bricks (bricks=0) or ladder.
            7→6: downhill, free.
            6→9: climb 3.
            9→14: climb 5.
            With optimal use: ladder on climb 5 (2→7 or 9→14), bricks on the rest.
            Best: ladder on 9→14, bricks on 2→7 (5) and 6→9 (3) → need 8, have 5. 
            Or: ladder on 2→7, bricks on 6→9 (3) → bricks=2, then 9→14 costs 5. Stuck.
            Optimal: ladder on 9→14, bricks 5 on 2→7, need 3 for 6→9 but 0 left. Stuck at 4.
            Actually: use 5 bricks on climb 5 (2→7), ladder on climb 5 (9→14).
            6→9 costs 3 bricks but we have 0. Stuck at index 4.

    Example 2:
        Input:  heights = [4,12,2,7,3,18,20,3,19], bricks = 10, ladders = 2
        Output: 7

    Example 3:
        Input:  heights = [14,3,19,3], bricks = 17, ladders = 0
        Output: 3 (can reach the end: 3→19 costs 16 bricks, total=16 ≤ 17)

    Constraints:
    ------------
    - 1 <= heights.length <= 10^5
    - 1 <= heights[i] <= 10^6
    - 0 <= bricks <= 10^9
    - 0 <= ladders <= heights.length

    Key Insight:
    ------------
    Ladders are best saved for the BIGGEST climbs (they save the most
    bricks). Bricks should cover the small climbs. But we don't know
    which climbs are biggest until we encounter them.

    Approach 1: Min-Heap — Use ladders first, swap smallest to bricks
    ------------------------------------------------------------------
    Use a ladder for every climb. When out of ladders, take back the
    ladder from the SMALLEST climb and pay with bricks instead.

    Heap stores ladder-climbs. Top = smallest ladder-climb (first to swap).

    Algorithm:
        For each climb:
            1. Use a ladder → push climb to min-heap.
            2. If heap.size > ladders → pop smallest, pay with bricks.
            3. If bricks < 0 → stuck at building i.

    This ensures ladders are always on the largest climbs.

    Time:  O(n log L)  — heap capped at L (ladders) entries.
    Space: O(L)

    Dry Run (heights=[4,2,7,6,9,14,12], bricks=5, ladders=1):
    -----------------------------------------------------------

    Min-heap approach:
        i=0: 2-4=-2 → free.
        i=1: 7-2=5  → ladder. heap=[5]. size(1)==ladders(1).
        i=2: 6-7=-1 → free.
        i=3: 9-6=3  → ladder. heap=[3,5]. size(2)>1 → pop 3, bricks-=3=2.
        i=4: 14-9=5 → ladder. heap=[5,5]. size(2)>1 → pop 5, bricks-=5=-3.
             bricks<0 → return 4. ✓
*/

// Approach 1: Min-Heap (ladder first, swap smallest to bricks)
class Solution1 {
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        // Min-heap: stores climbs using ladders. Smallest on top.
        priority_queue<int, vector<int>, greater<int>> pq;

        for (int i = 0; i < (int)heights.size() - 1; i++) {
            int climb = heights[i + 1] - heights[i];

            // Downhill or flat — free
            if (climb <= 0) continue;

            // Use a ladder for this climb
            pq.push(climb);

            // More ladders used than available — swap smallest to bricks
            if (pq.size() > ladders) {
                bricks -= pq.top();  // pay for smallest climb with bricks
                pq.pop();            // free up that ladder
            }

            // Can't afford — stuck at building i
            if (bricks < 0) return i;
        }

        return heights.size() - 1;
    }
};

int main() {
    // Example 1
    vector<int> h1 = {4, 2, 7, 6, 9, 14, 12};

    Solution1 s1;
    cout << "Min-heap: " << s1.furthestBuilding(h1, 5, 1) << endl;  // 4

    // Example 2
    vector<int> h2 = {4, 12, 2, 7, 3, 18, 20, 3, 19};

    Solution1 s3;
    cout << "Min-heap: " << s3.furthestBuilding(h2, 10, 2) << endl; // 7

    // Example 3: no ladders, enough bricks
    vector<int> h3 = {14, 3, 19, 3};

    Solution1 s5;
    cout << "Min-heap: " << s5.furthestBuilding(h3, 17, 0) << endl; // 3

    return 0;
}
