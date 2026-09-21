#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 1765 - Map of Highest Peak

    You are given an m x n integer matrix `isWater` where:
        - isWater[i][j] == 1 means cell (i,j) is a water cell
        - isWater[i][j] == 0 means cell (i,j) is a land cell

    Assign heights to each cell such that:
        1. Water cells have height 0.
        2. Adjacent cells (up/down/left/right) differ by at most 1.
        3. The maximum height is maximized.

    Return the resulting height matrix.

    Examples:
    ---------

    Example 1:
        Input:  isWater = [[0, 1],
                           [0, 0]]
        Output:           [[1, 0],
                           [2, 1]]
        Explanation:
            Water at (0,1) has height 0.
            (0,0) is adjacent to water → height 1.
            (1,1) is adjacent to water → height 1.
            (1,0) is adjacent to (0,0) and (1,1) → height 2.

    Example 2:
        Input:  isWater = [[0, 0, 1],
                           [1, 0, 0],
                           [0, 0, 0]]
        Output:           [[1, 1, 0],
                           [0, 1, 1],
                           [1, 2, 2]]

    Constraints:
    ------------
    - m == isWater.length
    - n == isWater[i].length
    - 1 <= m, n <= 1000
    - isWater[i][j] is 0 or 1
    - There is at least one water cell.

    Approach: Multi-Source BFS
    --------------------------

    Intuition:
    ----------
    To maximize heights while keeping the "differ by at most 1"
    constraint, every land cell should get the height equal to its
    shortest distance to the nearest water cell.

    Why? If a land cell is d steps from the nearest water cell,
    its height can be at most d (each step away from water can
    increase by at most 1). And we CAN achieve exactly d (just
    increase by 1 each step along the shortest path from water).

    This is the same as "find shortest distance from any water cell
    to every land cell" — a classic multi-source BFS problem.

    Multi-source BFS:
    -----------------
    Instead of running BFS from each water cell separately (slow),
    we add ALL water cells to the queue at once as starting points.
    BFS then expands outward from all water cells simultaneously,
    like ripples from multiple stones dropped in a pond.

    Each land cell gets assigned its distance the FIRST time it's
    reached — which is guaranteed to be the shortest distance to
    any water cell.

    Why do we set land cells to -1?
    --------------------------------
    The original grid uses 0 for land and 1 for water. But in our
    result, 0 means "water cell (height 0)" and positive numbers
    mean heights. We need a way to tell "unvisited land" apart from
    "water with height 0".

    If we left land as 0, we couldn't distinguish between:
        - A water cell with height 0 (already processed)
        - A land cell that hasn't been visited yet

    By marking unvisited land as -1, the BFS check becomes clean:
        - isWater[x][y] == -1 → unvisited land → process it
        - isWater[x][y] >= 0  → already assigned (water or visited land) → skip

    Without -1, we'd need a separate visited[][] matrix, wasting
    O(m*n) extra space. Using -1 lets us reuse the input matrix
    as both the visited tracker and the output.

    Dry Run (isWater = [[0,1],[0,0]]):
    -----------------------------------

    After initialization:
        grid = [[-1,  0],      water at (0,1) → 0
                [-1, -1]]      land cells → -1
        Queue = [(0,1)]

    Pop (0,1), height=0:
        (0,0): -1 → set to 0+1=1, push.    grid=[[ 1, 0],[-1,-1]]
        (1,1): -1 → set to 0+1=1, push.    grid=[[ 1, 0],[-1, 1]]
        Queue = [(0,0), (1,1)]

    Pop (0,0), height=1:
        (1,0): -1 → set to 1+1=2, push.    grid=[[ 1, 0],[ 2, 1]]
        Queue = [(1,1), (1,0)]

    Pop (1,1), height=1:
        (1,0): already 2, skip.
        Queue = [(1,0)]

    Pop (1,0), height=2:
        No unvisited neighbors.
        Queue = []

    Result: [[1, 0],
             [2, 1]] ✓

    Similar problems:
    -----------------
    - LC 542 (01 Matrix) — same idea, find distance from nearest 0.
    - LC 994 (Rotting Oranges) — multi-source BFS from rotten oranges.
    - LC 286 (Walls and Gates) — fill rooms with distance to nearest gate.

    Complexity Analysis:
    --------------------
    Time  : O(m * n) — each cell is pushed and popped at most once.
    Space : O(m * n) — queue can hold all cells in worst case.
                        No extra matrix needed (we reuse isWater).

*/

class Solution {
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
        int rows = isWater.size();
        int cols = isWater[0].size();
        int dirs[4][2] = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };

        queue<pair<int, int>> Q;

        // STEP 1: Initialize — add all water cells as BFS sources,
        // mark land cells as -1 (unvisited).
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (isWater[i][j] == 1) {
                    // Water cell: height = 0, add to queue as BFS source
                    Q.push({ i, j });
                    isWater[i][j] = 0;
                }
                else {
                    // Land cell: mark as -1 (unvisited).
                    // We can't leave it as 0 because 0 now means
                    // "water / height 0". -1 = "not yet assigned".
                    isWater[i][j] = -1;
                }
            }
        }

        // STEP 2: Multi-source BFS — expand outward from all water
        // cells simultaneously. Each land cell gets height = its
        // shortest distance to the nearest water cell.
        while (!Q.empty()) {
            auto [i, j] = Q.front();
            Q.pop();

            // Try all 4 neighbors
            for (const auto& dir : dirs) {
                int x = i + dir[0];
                int y = j + dir[1];

                // Only process unvisited land cells (-1)
                if (x >= 0 && x < rows && y >= 0 && y < cols
                    && isWater[x][y] == -1) {
                    // Height = parent's height + 1 (one step farther from water)
                    isWater[x][y] = isWater[i][j] + 1;
                    Q.push({ x, y });
                }
            }
        }

        // The isWater matrix is now the height matrix — return it
        return isWater;
    }
};

int main() {
    Solution obj;
}
