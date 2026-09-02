#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 1631 - Path With Minimum Effort

    You are given a 2D array `heights` of size rows x cols, where
    heights[i][j] is the height of cell (i,j). You want to travel
    from the top-left (0,0) to the bottom-right (rows-1, cols-1).
    You can move up, down, left, or right.

    A route's EFFORT is the maximum absolute difference in heights
    between two consecutive cells along the route.

    Return the minimum effort required to travel from (0,0) to
    (rows-1, cols-1).

    Examples:
    ---------

    Example 1:
        Input:  heights = [[1,2,2],
                           [3,8,2],
                           [5,3,5]]
        Output: 2
        Explanation:
            Path: (0,0)→(0,1)→(0,2)→(1,2)→(2,2)
            Steps: |1-2|=1, |2-2|=0, |2-2|=0, |2-5|=3 → max = 3
            Better path: (0,0)→(1,0)→(2,0)→(2,1)→(2,2)
            Steps: |1-3|=2, |3-5|=2, |5-3|=2, |3-5|=2 → max = 2 ✓

    Example 2:
        Input:  heights = [[1,2,3],
                           [3,8,4],
                           [5,3,5]]
        Output: 1
        Explanation:
            Path: (0,0)→(0,1)→(0,2)→(1,2)→(2,2)
            Steps: |1-2|=1, |2-3|=1, |3-4|=1, |4-5|=1 → max = 1

    Example 3:
        Input:  heights = [[1,10,6,7,9,10,4,9]]
        Output: 9

    Constraints:
    ------------
    - rows == heights.length
    - cols == heights[i].length
    - 1 <= rows, cols <= 100
    - 1 <= heights[i][j] <= 10^6

    Approach: Modified Dijkstra
    ----------------------------

    How is this Dijkstra?
    ----------------------
    In standard Dijkstra:
        - "Distance" = sum of edge weights along the path.
        - Relaxation: dist[v] = min(dist[v], dist[u] + weight(u,v))
        - The heap gives us the node with smallest total distance.

    Here:
        - "Distance" = maximum edge weight (step difference) along the path.
            int absDiff = abs(heights[i][j] - heights[x][y]);       //weight between ij and xy
            int newEffort = max(distance[i][j], absDiff);           //effort to reach xy from src. effort is max

        - Relaxation: 
            if (newEffort < distance[x][y]) {
                distance[x][y] = newEffort;
                PQ.push({distance[x][y], {x, y}});
            }
        - The heap gives us the node with smallest maximum effort.

    Side-by-side comparison:

        Regular Dijkstra              This Problem
        ────────────────              ────────────
        dist[v] = dist[u] + w        effort[v] = max(effort[u], w)
        minimize total sum            minimize the bottleneck (max step)
        "cheapest path"               "smoothest path"

    Why does Dijkstra still work with max instead of sum?
    ------------------------------------------------------
    Dijkstra works as long as the "distance" function is monotonically
    non-decreasing as you extend a path. With sum, adding a positive
    edge can only increase the total. With max, adding a new edge can
    only keep the max the same or increase it — never decrease it.

    So when we pop a node from the heap, its effort is finalized (no
    future path can give a smaller max). This is the same greedy
    property that makes standard Dijkstra correct.

    Formally, this is because max() over a path is a "bottleneck"
    distance, and Dijkstra works for any distance metric where:
        extending a path never decreases the cost.

    Dry Run (heights = [[1,2,2],[3,8,2],[5,3,5]]):
    ------------------------------------------------

    effort[][] initialized to INT_MAX, effort[0][0] = 0.
    Heap: [(0, (0,0))]

    Pop (0, (0,0)):
        → (0,1): weight=|1-2|=1, max(0,1)=1 < INF → effort=1, push (1,(0,1))
        → (1,0): weight=|1-3|=2, max(0,2)=2 < INF → effort=2, push (2,(1,0))

    Pop (1, (0,1)):
        → (0,2): weight=|2-2|=0, max(1,0)=1 < INF → effort=1, push (1,(0,2))
        → (1,1): weight=|2-8|=6, max(1,6)=6 < INF → effort=6, push (6,(1,1))
        → (0,0): max(1,1)=1 > 0 → skip

    Pop (1, (0,2)):
        → (1,2): weight=|2-2|=0, max(1,0)=1 < INF → effort=1, push (1,(1,2))

    Pop (1, (1,2)):
        → (2,2): weight=|2-5|=3, max(1,3)=3 < INF → effort=3, push (3,(2,2))

    Pop (2, (1,0)):
        → (2,0): weight=|3-5|=2, max(2,2)=2 < INF → effort=2, push (2,(2,0))

    Pop (2, (2,0)):
        → (2,1): weight=|5-3|=2, max(2,2)=2 < INF → effort=2, push (2,(2,1))

    Pop (2, (2,1)):
        → (2,2): weight=|3-5|=2, max(2,2)=2 < 3 → effort=2, push (2,(2,2))

    Pop (2, (2,2)):
        Destination reached! Return 2 ✓

    Path: (0,0)→(1,0)→(2,0)→(2,1)→(2,2), max step = 2.

    Complexity Analysis:
    --------------------
    Time  : O(rows * cols * log(rows * cols)) — Dijkstra on a grid.

    V = total nodes = rows × cols
    E = total edges = rows × cols × 4  (each cell has up to 4 neighbors)

    But E simplifies: rows × cols × 4 = 4V = O(V)

    So:
    Dijkstra = O(E log V)
             = O(4V × log V)
             = O(V log V)
             = O(rows × cols × log(rows × cols))

    Space : O(rows * cols) — effort matrix + heap.


    for (auto dir : dirs) {
        int x = i + dir[0];
        int y = j + dir[1];
        if (x >= 0 && x < rows && y >= 0 && y < cols) {
            int absDiff = abs(heights[i][j] - heights[x][y]);
            int newEffort = max(distance[i][j], absDiff);

            if (newEffort < distance[x][y]) {
                distance[x][y] = newEffort;
                PQ.push({distance[x][y], {x, y}});
            }
        }
    }


*/

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int rows = heights.size(), cols = heights[0].size();
        int dirs[4][2] = { {0,1}, {0,-1}, {-1,0}, {1,0} };

        // Min-heap: {effort to reach cell, {row, col}}
        // Effort = max absolute height difference along the path so far
        priority_queue<
            pair<int, pair<int, int>>,
            vector<pair<int, pair<int, int>>>,
            greater<pair<int, pair<int, int>>>
        > minHeap;

        // effort[i][j] = minimum possible "max step" to reach (i,j) from (0,0)
        // this is the distance[]
        vector<vector<int>> effort(rows, vector<int>(cols, INT_MAX));

        effort[0][0] = 0;
        minHeap.push({ 0, {0, 0} });

        while (!minHeap.empty()) {
            auto [currentEffort, cell] = minHeap.top();
            int i = cell.first, j = cell.second;
            minHeap.pop();

            if (i == rows - 1 && j == cols - 1)
                return currentEffort;

            // Skip stale entries: already found a path with less effort to (i,j)
            if (currentEffort > effort[i][j]) continue;

            // Try all 4 neighbors
            for (const auto& dir : dirs) {
                int x = i + dir[0];
                int y = j + dir[1];

                if (x >= 0 && x < rows && y >= 0 && y < cols) {
                    // The "edge weight" = absolute height difference between cells
                    int stepDiff = abs(heights[i][j] - heights[x][y]);

                    // KEY DIFFERENCE from regular Dijkstra:
                    // New effort = max(effort so far, this step)
                    // NOT sum. We care about the worst single step, not total.
                    int newEffort = max(effort[i][j], stepDiff);

                    // Relax: if this path gives a smaller max-step to (x,y)
                    if (newEffort < effort[x][y]) {
                        effort[x][y] = newEffort;
                        minHeap.push({ newEffort, {x, y} });
                    }
                }
            }
        }

        return effort[rows - 1][cols - 1];
    }
};

int main() {
    return 0;
}
