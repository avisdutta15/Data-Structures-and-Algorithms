#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 1091 - Shortest Path in Binary Matrix

    Given an n x n binary matrix `grid`, return the length of the shortest
    clear path from top-left (0,0) to bottom-right (n-1, n-1).

    A clear path:
        - Only visits cells with value 0.
        - Moves in 8 directions (up, down, left, right, and 4 diagonals).
        - The path length includes both the start and end cells.

    If no such path exists, return -1.

    Examples:
    ---------

    Example 1:
        Input:  grid = [[0, 1],
                        [1, 0]]
        Output: 2
        Explanation:
            Path: (0,0) → (1,1). Length = 2 (diagonal move).

    Example 2:
        Input:  grid = [[0, 0, 0],
                        [1, 1, 0],
                        [1, 1, 0]]
        Output: 4
        Explanation:
            Path: (0,0) → (0,1) → (0,2) → (1,2) → (2,2). Length = 4.
            Wait, that's 5. Actual shortest:
            (0,0) → (0,1) → (1,2) → (2,2). Length = 4 (diagonal used).

    Example 3:
        Input:  grid = [[1, 0, 0],
                        [1, 1, 0],
                        [1, 1, 0]]
        Output: -1
        Explanation:
            grid[0][0] = 1, so we can't even start. Return -1.

    Example 4:
        Input:  grid = [[0]]
        Output: 1
        Explanation:
            Start == End. Path length = 1.

    Constraints:
    ------------
    - n == grid.length == grid[i].length
    - 1 <= n <= 100
    - grid[i][j] is 0 or 1

    Approach 1: Dijkstra's Algorithm
    --------------------------------
    Since this is a shortest path problem, Dijkstra is the first thing
    that comes to mind. It works on weighted graphs and always finds
    the shortest path.

    For this grid, each move costs 1. We use a min-heap (priority queue)
    sorted by distance. Pop the cell with the smallest distance, relax
    its neighbors.

    Code snippet:

        int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
            if (grid[0][0] != 0) return -1;
            int n = grid.size();

            // min-heap: (distance, row, col)
            priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> pq;

            vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
            int dirs[8][2] = {{0,1},{0,-1},{1,0},{-1,0},
                              {1,1},{1,-1},{-1,1},{-1,-1}};

            dist[0][0] = 1;
            pq.push({1, 0, 0});

            while (!pq.empty()) {
                auto [d, i, j] = pq.top();
                pq.pop();

                if (i == n-1 && j == n-1) return d;

                // Skip if we've already found a shorter path to (i,j)
                if (d > dist[i][j]) continue;

                for (auto& dir : dirs) {
                    int x = i + dir[0], y = j + dir[1];
                    if (x >= 0 && x < n && y >= 0 && y < n && grid[x][y] == 0){
                      // relax
                      if (dist[i][j] + 1 < dist[x][y]) {
                        dist[x][y] = dist[i][j] + 1;
                        pq.push({dist[x][y], x, y});
                    }
                }
            }
            return -1;
        }

    Time  : O(n^2 * log(n^2)) = O(n^2 * log n)
            Each cell can be pushed to the heap, and each push/pop is O(log n^2).
    Space : O(n^2) — distance array + heap.

    This works, but it's overkill. Here's why:

    Why BFS is better here:
    -----------------------
    Dijkstra uses a heap because different edges can have different weights,
    so it needs to always process the cheapest node first.

    But in this problem, EVERY move costs exactly 1. When all edge weights
    are the same, a simple queue already processes nodes in order of
    increasing distance — that's exactly what BFS does naturally.

        Dijkstra with a heap   →  O(n^2 * log n)  (heap overhead)
        BFS with a queue       →  O(n^2)           (no heap needed)

    The heap adds a log factor for no benefit. BFS gives the same
    shortest-path guarantee with less overhead. So we drop Dijkstra
    and use BFS.

    Rule of thumb:
        - All edges weight 1    → use BFS
        - Edges weight 0 or 1   → use 0-1 BFS (deque)
        - Arbitrary weights     → use Dijkstra (heap)

    Approach 2: BFS (Level-order traversal)
    -------------------------------------

    Intuition:
    ----------
    This is a shortest path problem on an unweighted grid. Every move
    (in any of the 8 directions) costs exactly 1 step. When all edge
    weights are equal, BFS finds the shortest path.

    Why BFS and not DFS?
    ---------------------
    BFS explores nodes level by level — first all cells at distance 1,
    then all at distance 2, etc. So the FIRST time we reach (n-1, n-1),
    we've found the shortest path. Guaranteed.

    DFS would explore one path deeply before trying others. It might
    find a long path first and has no way to guarantee the first path
    found is the shortest (without exploring all paths).

    Why 8 directions?
    ------------------
    Unlike typical grid problems that only allow 4 directions (up, down,
    left, right), this problem explicitly allows diagonal movement.
    Diagonal moves let you cover more ground — moving diagonally from
    (0,0) to (1,1) is 1 step, not 2.

    The 8 directions are:
        Right (0,1)   Left (0,-1)   Down (1,0)    Up (-1,0)
        Down-Right (1,1)   Down-Left (1,-1)
        Up-Right (-1,1)    Up-Left (-1,-1)

    Two approaches shown below:
    ----------------------------
    Approach 1 (Level-based BFS):
        Process all nodes at the same distance in one "level".
        Use a level counter. Each full level = one more step.

    Approach 2 (Distance-array BFS):
        Store the distance to each cell in a 2D array.
        When visiting a neighbor, set its distance = current + 1.
        No need for explicit level tracking.

    Both are O(n^2) time and space. Approach 2 avoids the inner
    levelSize loop and is slightly simpler.

    Dry Run (Approach 1, grid = [[0,0,0],[1,1,0],[1,1,0]]):
    --------------------------------------------------------

    8-dir BFS from (0,0):

    Level 1: Queue = [(0,0)]
        Process (0,0):
            Valid neighbors: (0,1) [right, grid=0]
            (1,0)=1, (1,1)=1 → blocked
        Queue after: [(0,1)]

    Level 2: Queue = [(0,1)]
        Process (0,1):
            Valid neighbors: (0,2) [right, grid=0], (1,2) [down-right, grid=0]
            Others blocked or visited
        Queue after: [(0,2), (1,2)]

    Level 3: Queue = [(0,2), (1,2)]
        Process (0,2):
            Neighbors: (1,2) already queued
        Process (1,2):
            Valid neighbor: (2,2) [down, grid=0]
        Queue after: [(2,2)]

    Level 4: Queue = [(2,2)]
        Process (2,2): this is (n-1, n-1) → return level = 4 ✓

    Complexity Analysis:
    --------------------
    Time  : O(n^2) — each cell is visited at most once.
    Space : O(n^2) — visited/distance array + queue can hold all cells.

    Why not DP?
    -----------
    In grid shortest-path problems like "Minimum Path Sum" (LC 64), DP
    works because you can only move RIGHT or DOWN. That means when you
    compute dp[i][j], you've already computed dp[i-1][j] and dp[i][j-1]
    — the subproblems are solved before you need them. There's a clear
    top-left to bottom-right order.

    Here, we can move in 8 directions, including UP, LEFT, and all
    diagonals. This breaks DP because:

        1. No valid fill order exists.
           To compute dp[i][j], you might need dp[i+1][j] (below) or
           dp[i][j-1] (left). But dp[i+1][j] might need dp[i][j] back.
           There's a circular dependency — no single pass order can
           resolve all directions.

        2. Concrete example:

                grid = [[0, 0, 0],
                        [1, 1, 0],
                        [0, 0, 0]]

           Shortest path: (0,0)→(0,1)→(0,2)→(1,2)→(2,2)→(2,1)→(2,0)

           The path goes RIGHT, then DOWN, then LEFT. A DP that fills
           top-to-bottom, left-to-right would never discover this path
           because it goes backwards (left) after going right and down.

        3. In general, DP works when the problem has a DAG structure
           (no cycles in the dependency graph). An 8-directional grid
           has cycles — cell A depends on cell B and cell B depends on
           cell A. BFS handles this naturally by exploring all
           directions simultaneously, level by level.

    Rule of thumb:
        - Movement restricted (only right/down)  → DP works
        - Movement in all directions             → BFS / Dijkstra

*/

// ============================================================
// Approach 1: Level-based BFS (using level counter)
// ============================================================
class Solution1 {
private:
    // 8 possible directions: right, left, down, up, and 4 diagonals
    // vector<vector<int>> - heap allocated.
    // static - array is created only once and reused on all call.
    // constexpr - constexpr just means "compute this at compile time." 
    // It tells the compiler the values are known before the program even runs, 
    // so it can bake them directly into the binary. 
    static constexpr int dirs[8][2] = {
        {0,1},{0,-1},{-1,0},{1,0},{1,-1},{-1,1},{1,1},{-1,-1}
    };
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        // Edge case: start cell is blocked
        if (grid[0][0] != 0)
            return -1;

        int n = grid.size();
        queue<pair<int, int>> Q;
        vector<vector<bool>> visited(n, vector<bool>(n, false));

        // Start BFS from (0,0), path length starts at 1 (counting the start cell)
        Q.push({0, 0});
        visited[0][0] = true;
        int level = 1;

        while (!Q.empty()) {
            // Process all cells at the current distance (level) together
            int levelSize = Q.size();

            while (levelSize--) {
                auto [i, j] = Q.front();
                Q.pop();

                // If we've reached the bottom-right corner, return the current level
                if (i == n - 1 && j == n - 1)
                    return level;

                // Try all 8 directions
                for (const auto& dir : dirs) {
                    int x = i + dir[0];
                    int y = j + dir[1];

                    // Check bounds, cell is open (0), and not yet visited
                    if (x >= 0 && x < n && y >= 0 && y < n
                        && grid[x][y] == 0 && !visited[x][y]) {
                        visited[x][y] = true;
                        Q.push({x, y});
                    }
                }
            }
            // All cells at this distance are processed, move to the next level
            level++;
        }

        // Queue is empty and we never reached (n-1, n-1)
        return -1;
    }
};

// ============================================================
// Approach 2: Distance-array BFS (no level counter needed)
// ============================================================

class Solution2 {
private:
    static constexpr int dirs[8][2] = {
        {0,1},{0,-1},{-1,0},{1,0},{1,-1},{-1,1},{1,1},{-1,-1}
    };
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        if (grid[0][0] != 0)
            return -1;

        int n = grid.size();
        queue<pair<int, int>> Q;

        // distance[i][j] = shortest path length from (0,0) to (i,j)
        // -1 means unvisited (also doubles as our visited check)
        vector<vector<int>> distance(n, vector<int>(n, -1));

        // Start cell: distance is 1 (path includes the start cell itself)
        distance[0][0] = 1;
        Q.push({0, 0});

        while (!Q.empty()) {
            auto [i, j] = Q.front();
            Q.pop();

            // Reached the destination — return its distance
            if (i == n - 1 && j == n - 1)
                return distance[n - 1][n - 1];

            for (const auto& dir : dirs) {
                int x = i + dir[0];
                int y = j + dir[1];

                // Bounds check + cell is open + not yet visited
                if (x >= 0 && x < n && y >= 0 && y < n
                    && grid[x][y] == 0 && distance[x][y] == -1) {
                    // Neighbor's distance = current cell's distance + 1
                    distance[x][y] = distance[i][j] + 1;
                    Q.push({x, y});
                }
            }
        }

        // Never reached (n-1, n-1)
        return -1;
    }
};

int main() {
    Solution1 obj;
}
