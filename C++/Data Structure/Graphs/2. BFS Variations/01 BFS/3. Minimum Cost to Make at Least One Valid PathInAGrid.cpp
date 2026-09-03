#include <iostream>
#include <queue>
#include <deque>
#include <vector>
#include <climits>

using namespace std;

/*
    https://www.youtube.com/watch?v=NS3C4W_jJJM
    Problem Statement:
    ------------------
    LeetCode 1368 - Minimum Cost to Make at Least One Valid Path in a Grid

    Given an m x n grid where each cell has a sign pointing to a direction:
        1 = right  (→)
        2 = left   (←)
        3 = down   (↓)
        4 = up     (↑)

    You start at (0,0) and want to reach (m-1, n-1). You can move to any
    adjacent cell (up/down/left/right), but:
        - Following the sign costs 0  (the sign already points that way)
        - Going any other direction costs 1  (you change the sign)

    Return the minimum cost to make a valid path from (0,0) to (m-1, n-1).

    Examples:
    ---------

    Example 1:
        Input:  grid = [[1,1,1,1],
                        [2,2,2,2],
                        [1,1,1,1],
                        [2,2,2,2]]
        Output: 3

    Example 2:
        Input:  grid = [[1,1,3],
                        [3,2,2],
                        [1,1,4]]
        Output: 0

    Example 3:
        Input:  grid = [[2,2,2],
                        [2,2,2]]
        Output: 3

    Constraints:
    ------------
    - m == grid.length, n == grid[i].length
    - 1 <= m, n <= 100
    - 1 <= grid[i][j] <= 4

    How to visualize this as a GRAPH:
    ----------------------------------
    Every cell is a NODE. From each cell you have 4 EDGES (one per
    direction). Each edge has a weight:
        - 0 if that direction matches the cell's arrow
        - 1 if it doesn't

    How the weight is calculated:
    ------------------------------
    We check each of the 4 directions explicitly against the cell's
    arrow value (grid[i][j]):

        Direction     Arrow value that makes it FREE (cost 0)
        ─────────     ──────────────────────────────────────
        right         grid[i][j] == 1
        left          grid[i][j] == 2
        down          grid[i][j] == 3
        up            grid[i][j] == 4

    For example, cell (1,2) has grid[1][2] = 2 (arrow points LEFT):

        Moving right: grid = 2, not 1 → cost 1  (changing sign)
        Moving left:  grid = 2, is  2 → cost 0  (following sign ✓)
        Moving down:  grid = 2, not 3 → cost 1  (changing sign)
        Moving up:    grid = 2, not 4 → cost 1  (changing sign)

    In code, for direction d (0=right, 1=left, 2=down, 3=up):

        int gridDirection = grid[i][j];
        if ((gridDirection == 1 && d != 0) ||    // arrow=right but not going right
            (gridDirection == 2 && d != 1) ||    // arrow=left  but not going left
            (gridDirection == 3 && d != 2) ||    // arrow=down  but not going down
            (gridDirection == 4 && d != 3))      // arrow=up    but not going up
            weight = 1;
        else
            weight = 0;

    Approach 1: Dijkstra (min-heap)
    --------------------------------
    Standard shortest path. Weights are 0 or 1.
    Time:  O(m × n × log(m × n))
    Space: O(m × n)

    Approach 2: 0-1 BFS (deque) — optimal
    ----------------------------------------
    Weights are only 0 or 1, so deque replaces the heap:
        - Weight 0 → push to FRONT
        - Weight 1 → push to BACK
    Time:  O(m × n)
    Space: O(m × n)

    Dry Run (grid = [[1,1,3],[3,2,2],[1,1,4]]):
    ----------------------------------------------

    Arrows:   →  →  ↓
              ↓  ←  ←
              →  →  ↑

    Pop (0,0) cost=0, arrow=→(1):
        right (0,1): grid=1, d=0 → 1==1 && d==0 → weight 0, cost=0

    Pop (0,1) cost=0, arrow=→(1):
        right (0,2): grid=1, d=0 → weight 0, cost=0

    Pop (0,2) cost=0, arrow=↓(3):
        down (1,2): grid=3, d=2 → 3==3 && d==2 → weight 0, cost=0

    Pop (1,2) cost=0, arrow=←(2):
        left (1,1): grid=2, d=1 → 2==2 && d==1 → weight 0, cost=0

    Pop (1,1) cost=0, arrow=←(2):
        left (1,0): grid=2, d=1 → weight 0, cost=0

    Pop (1,0) cost=0, arrow=↓(3):
        down (2,0): grid=3, d=2 → weight 0, cost=0

    Pop (2,0) cost=0, arrow=→(1):
        right (2,1): grid=1, d=0 → weight 0, cost=0

    Pop (2,1) cost=0, arrow=→(1):
        right (2,2): grid=1, d=0 → weight 0, cost=0

    Pop (2,2) cost=0: destination! Return 0 ✓

*/

// =============================================================
// Approach 1: Dijkstra (min-heap)
// =============================================================

class Solution1 {
public:
    int minCost(vector<vector<int>>& grid) {
        int rows = grid.size(), cols = grid[0].size();

        // 4 directions: right, left, down, up
        //     d:          0      1     2     3
        int dirs[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

        // Min-heap: {cost, {row, col}}
        priority_queue<
            pair<int, pair<int, int>>,
            vector<pair<int, pair<int, int>>>,
            greater<pair<int, pair<int, int>>>
        > PQ;

        // cost[i][j] = minimum sign changes to reach (i,j) from (0,0)
        vector<vector<int>> cost(rows, vector<int>(cols, INT_MAX));

        cost[0][0] = 0;
        PQ.push({ 0, {0, 0} });

        while (!PQ.empty()) {
            auto [c, cell] = PQ.top();
            PQ.pop();
            int i = cell.first, j = cell.second;

            // First time we pop destination = optimal answer
            if (i == rows - 1 && j == cols - 1)
                return c;

            // Skip stale entries
            if (c > cost[i][j]) continue;

            // Try all 4 directions
            for (int d = 0; d < 4; d++) {
                int x = i + dirs[d][0];
                int y = j + dirs[d][1];

                if (x >= 0 && x < rows && y >= 0 && y < cols) {
                    // Check if direction d matches the arrow at (i,j).
                    // The arrow at the CURRENT cell determines if the move is free.
                    int gridDirection = grid[i][j];
                    int weight = 0;

                    if ((gridDirection == 1 && d != 0) ||   // arrow=right, not going right
                        (gridDirection == 2 && d != 1) ||   // arrow=left,  not going left
                        (gridDirection == 3 && d != 2) ||   // arrow=down,  not going down
                        (gridDirection == 4 && d != 3)) {   // arrow=up,    not going up
                        weight = 1;  // direction doesn't match → pay cost 1
                    }

                    int newCost = cost[i][j] + weight;

                    // Relax: found a cheaper path to (x,y)
                    if (newCost < cost[x][y]) {
                        cost[x][y] = newCost;
                        PQ.push({ newCost, {x, y} });
                    }
                }
            }
        }

        return cost[rows - 1][cols - 1];
    }
};

// =============================================================
// Approach 2: 0-1 BFS (deque) — optimal
// =============================================================

class Solution2 {
public:
    int minCost(vector<vector<int>>& grid) {
        int rows = grid.size(), cols = grid[0].size();
        int dirs[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

        // Deque replaces the heap:
        // Front = cells with smallest cost
        // Back  = cells with larger cost
        deque<pair<int, int>> dq;

        vector<vector<int>> cost(rows, vector<int>(cols, INT_MAX));

        cost[0][0] = 0;
        dq.push_front({0, 0});

        while (!dq.empty()) {
            auto [i, j] = dq.front();
            dq.pop_front();

            for (int d = 0; d < 4; d++) {
                int x = i + dirs[d][0];
                int y = j + dirs[d][1];

                if (x >= 0 && x < rows && y >= 0 && y < cols) {
                    // Explicit direction check against the arrow
                    int gridDirection = grid[i][j];
                    int weight = 0;

                    if ((gridDirection == 1 && d != 0) ||
                        (gridDirection == 2 && d != 1) ||
                        (gridDirection == 3 && d != 2) ||
                        (gridDirection == 4 && d != 3)) {
                        weight = 1;
                    }

                    int newCost = cost[i][j] + weight;

                    if (newCost < cost[x][y]) {
                        cost[x][y] = newCost;

                        // 0-cost → push front (same priority)
                        // 1-cost → push back  (next priority)
                        if (weight == 0)
                            dq.push_front({x, y});
                        else
                            dq.push_back({x, y});
                    }
                }
            }
        }

        return cost[rows - 1][cols - 1];
    }
};

int main() {
    return 0;
}
