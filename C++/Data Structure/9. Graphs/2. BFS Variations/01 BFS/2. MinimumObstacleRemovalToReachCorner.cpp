#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <climits>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 2290 - Minimum Obstacle Removal to Reach Corner

    You are given a 0-indexed 2D integer array `grid` of size m x n.
    Each cell has one of two values:
        - 0 represents an empty cell
        - 1 represents an obstacle

    You can move up, down, left, or right from one cell to an adjacent
    cell. You can remove an obstacle at any cell you visit (costs 1
    removal). An empty cell costs 0 to move into.

    Return the minimum number of obstacles to remove so you can move
    from (0, 0) to (m-1, n-1).

    Examples:
    ---------

    Example 1:
        Input:  grid = [[0, 1, 1],
                        [1, 1, 0],
                        [1, 1, 0]]
        Output: 2
        Explanation:
            Path: (0,0)→(1,0)→(2,0)→(2,1)→(2,2)
            Remove obstacles at (1,0) and (2,0). Two removals.

    Example 2:
        Input:  grid = [[0, 1, 0, 0, 0],
                        [0, 1, 0, 1, 0],
                        [0, 0, 0, 1, 0]]
        Output: 0
        Explanation:
            A path exists using only empty cells:
            (0,0)→(1,0)→(2,0)→(2,1)→(2,2)→(1,2)→(0,2)→(0,3)→(0,4)→(1,4)→(2,4)
            No obstacles removed.

    Example 3:
        Input:  grid = [[0, 1],
                        [1, 0]]
        Output: 1
        Explanation:
            (0,0)→(0,1)→(1,1) or (0,0)→(1,0)→(1,1). Either removes 1 obstacle.

    Constraints:
    ------------
    - m == grid.length
    - n == grid[i].length
    - 1 <= m, n <= 10^5
    - 2 <= m * n <= 10^5
    - grid[i][j] is either 0 or 1
    - grid[0][0] == 0 and grid[m-1][n-1] == 0

    Why is this a shortest path problem?
    -------------------------------------
    Think of the grid as a weighted graph:
        - Each cell is a node.
        - Moving to a 0-cell (empty)    → edge weight 0
        - Moving to a 1-cell (obstacle) → edge weight 1

    "Minimum obstacles to remove" = "shortest weighted path from
    (0,0) to (m-1, n-1)" where the weights are 0 and 1.

    Can we use normal BFS with a queue?
    ------------------------------------
    No. Normal BFS works only when all edges have the SAME weight.
    Here edges have weight 0 or 1. A regular queue processes cells
    in FIFO order, but a cell added later via a 0-cost edge might
    have a shorter distance than a cell added earlier via a 1-cost
    edge. FIFO doesn't respect this ordering, so BFS gives wrong
    answers.

    Approach 1: Dijkstra (min-heap)
    --------------------------------
    Dijkstra handles any non-negative edge weights. Use a min-heap
    sorted by distance. Always pop the cell with the smallest distance
    and relax its neighbors.

    Works correctly, but the heap adds O(log(m*n)) per operation.
    Time: O(m*n * log(m*n)). We can do better.

    Approach 2: 0-1 BFS (deque) — optimal
    --------------------------------------
    When edge weights are only 0 or 1, we can replace Dijkstra's heap
    with a deque:
        - 0-cost neighbor → push to FRONT (high priority, process soon)
        - 1-cost neighbor → push to BACK  (lower priority, process later)

    This keeps the deque sorted by distance at all times, so we always
    process the cheapest cell first — just like Dijkstra, but without
    the log factor.

    Why does the deque stay sorted?
    --------------------------------
    At any point, the deque contains cells with distance d or d+1
    (never a wider range). Pushing 0-cost neighbors to the front
    keeps them at distance d. Pushing 1-cost neighbors to the back
    puts them at distance d+1. So front-to-back = smallest to largest.

    This is the same property that makes regular BFS work for uniform
    weights — here it's extended to handle two weight levels.

    Dry Run (grid = [[0,1,1],[1,1,0],[1,1,0]]):
    ---------------------------------------------

    Start: distance[0][0] = 0, deque = [(0,0)]

    Pop (0,0), dist=0:
        (0,1): grid=1, dist=0+1=1, push_back    deque=[(0,1)]
        (1,0): grid=1, dist=0+1=1, push_back    deque=[(0,1),(1,0)]

    Pop (0,1), dist=1:
        (0,2): grid=1, dist=1+1=2, push_back    deque=[(1,0),(0,2)]
        (1,1): grid=1, dist=1+1=2, push_back    deque=[(1,0),(0,2),(1,1)]
        (0,0): already dist=0 ≤ 1, skip

    Pop (1,0), dist=1:
        (2,0): grid=1, dist=1+1=2, push_back    deque=[(0,2),(1,1),(2,0)]
        (1,1): already dist=2 ≤ 2, skip
        (0,0): already dist=0 ≤ 1, skip

    Pop (0,2), dist=2:
        (1,2): grid=0, dist=2+0=2, push_front   deque=[(1,2),(1,1),(2,0)]

    Pop (1,2), dist=2:
        (2,2): grid=0, dist=2+0=2, push_front   deque=[(2,2),(1,1),(2,0)]

    Pop (2,2), dist=2: this is (m-1, n-1) → return 2 ✓

    Complexity Analysis:
    --------------------
                    Dijkstra            0-1 BFS
    Time          O(m*n * log(m*n))    O(m*n)
    Space         O(m*n)               O(m*n)

    Both use a distance array of size m*n. Dijkstra has heap overhead;
    0-1 BFS avoids it by using a deque. Each cell is pushed/popped at
    most once from the deque, giving O(m*n) total work.

*/

// ============================================================
// Approach 1: Dijkstra (min-heap)
// ============================================================

class Solution1 {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        // Min-heap: (distance, (row, col))
        // Smallest distance is always on top
        priority_queue<
            pair<int, pair<int,int>>,
            vector<pair<int, pair<int,int>>>,
            greater<pair<int, pair<int,int>>>
        > pq;

        // distance[i][j] = min obstacles removed to reach (i,j)
        vector<vector<int>> distance(rows, vector<int>(cols, INT_MAX));

        // 4 directions: right, left, down, up
        int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        // Start at (0,0) with 0 obstacles removed
        pq.push({0, {0, 0}});
        distance[0][0] = 0;

        while (!pq.empty()) {
            auto [d, cell] = pq.top();
            pq.pop();
            int i = cell.first, j = cell.second;

            // Skip stale entries: if we've already found a shorter
            // path to (i,j), this entry is outdated — ignore it
            if (d > distance[i][j])
                continue;

            // Try all 4 neighbors
            for (const auto& dir : dirs) {
                int x = i + dir[0];
                int y = j + dir[1];

                if (x >= 0 && x < rows && y >= 0 && y < cols) {
                    // Weight = 0 (empty cell) or 1 (obstacle to remove)
                    int weight = grid[x][y];

                    // Relax: if going through (i,j) gives a cheaper path to (x,y)
                    if (distance[x][y] > distance[i][j] + weight) {
                        distance[x][y] = distance[i][j] + weight;
                        pq.push({distance[x][y], {x, y}});
                    }
                }
            }
        }

        return distance[rows - 1][cols - 1];
    }
};

// ============================================================
// Approach 2: 0-1 BFS (deque) — optimal
// ============================================================

class Solution2 {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        // Deque replaces the heap:
        // front = cells with smallest distance (highest priority)
        // back  = cells with larger distance (lower priority)
        deque<pair<int, int>> Q;

        // distance[i][j] = min obstacles removed to reach (i,j)
        // INT_MAX = unvisited (also serves as visited check)
        vector<vector<int>> distance(rows, vector<int>(cols, INT_MAX));

        int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        // Start at (0,0) with 0 obstacles removed
        Q.push_front({0, 0});
        distance[0][0] = 0;

        while (!Q.empty()) {
            // Always process the cell with the smallest distance first
            auto [i, j] = Q.front();
            Q.pop_front();

            // Early exit: reached the destination
            if (i == rows - 1 && j == cols - 1)
                return distance[i][j];

            for (const auto& dir : dirs) {
                int x = i + dir[0];
                int y = j + dir[1];

                if (x >= 0 && x < rows && y >= 0 && y < cols) {
                    // New distance = current distance + cost of moving to (x,y)
                    int newDist = distance[i][j] + grid[x][y];

                    // Only process if we found a shorter path to (x,y)
                    if (newDist < distance[x][y]) {
                        distance[x][y] = newDist;

                        // 0-cost edge → push front (same priority level)
                        // 1-cost edge → push back  (next priority level)
                        if (grid[x][y] == 0)
                            Q.push_front({x, y});
                        else
                            Q.push_back({x, y});
                    }
                }
            }
        }

        return distance[rows - 1][cols - 1];
    }
};

int main() {
    Solution1 obj;
}
