#include <iostream>
#include <queue>
#include <deque>
#include <vector>
#include <climits>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 778 - Swim in Rising Water

    You are given an n x n grid where grid[i][j] represents the
    elevation at cell (i,j). At time t, the water level is t.
    You can swim to an adjacent cell (up/down/left/right) only if
    BOTH the current cell and the target cell have elevation <= t
    (i.e., both are underwater at time t).

    Starting at (0,0) at time 0, find the minimum time t such that
    you can swim from (0,0) to (n-1, n-1).

    In other words: you can only be at cell (i,j) at time t if
    t >= grid[i][j]. Find the earliest time you can reach the
    bottom-right corner.

    Examples:
    ---------

    Example 1:
        Input:  grid = [[0,2],
                        [1,3]]
        Output: 3
        Explanation:
            t=0: can only be at (0,0) [elevation 0]
            t=1: can reach (1,0) [elevation 1]
            t=2: can reach (0,1) [elevation 2]
            t=3: can reach (1,1) [elevation 3] ✓

    Example 2:
        Input:  grid = [[0,1,2,3,4],
                        [24,23,22,21,5],
                        [12,13,14,15,16],
                        [11,17,18,19,20],
                        [10,9,8,7,6]]
        Output: 16

    Constraints:
    ------------
    - n == grid.length == grid[i].length
    - 1 <= n <= 50
    - 0 <= grid[i][j] < n²
    - Each value in grid is unique
    - grid[0][0] == 0 and grid[n-1][n-1] == n²-1... (not always, values are a permutation of [0, n²-1])

    Key Insight:
    ------------
    The time t needed to traverse a path = max(grid[i][j]) along
    that path. We must wait for the highest cell on our route to be
    submerged. So we want the path where the maximum elevation is
    minimized — a classic "minimax path" / bottleneck shortest path.

    Identification:
    ----------------
    0. Graph (grid)
    1. start (0,0) -> end (n-1, n-1), finding path
    2. constraint: can visit cell only when t >= grid[i][j]
    3. minimize time = minimize the max elevation on any path
    4. Bottleneck shortest path → Binary Search + BFS or Dijkstra (max)

    Comparison with standard Dijkstra:

        Normal Dijkstra               This Problem
        ────────────────              ────────────
        dist[v] = dist[u] + w        dist[v] = max(dist[u], grid[v])
        minimize sum of weights       minimize bottleneck (max elevation)
        combine via +                 combine via max()
        relax if newDist < dist[v]    relax if newDist < dist[v]

    Why max(dist[u], grid[v])?
    ---------------------------
    dist[u] = the minimum time needed to reach u (= max elevation
    seen so far on the best path to u). To step into v, we also
    need t >= grid[v]. So the time to reach v through u is:
        max(time to reach u, elevation of v) = max(dist[u], grid[v])

    Approach 1: Binary Search + BFS
    ---------------------------------
    Binary search on time t (0 to n²-1).
    For each t, BFS to check: "can we reach (n-1,n-1) visiting
    only cells with elevation <= t?"
    Smallest t where BFS succeeds = answer.
    Time:  O(n² × log(n²)) = O(n² × log n)
    Space: O(n²)

    Approach 2: Dijkstra (min-heap with max cost)
    -----------------------------------------------
    dist[i][j] = min over all paths of (max elevation on path).
    Relax: newCost = max(dist[i][j], grid[x][y]).
    Time:  O(n² × log(n²)) = O(n² × log n)
    Space: O(n²)

    Dry Run (grid = [[0,2],[1,3]]):
    ---------------------------------

    Dijkstra approach:
    dist[][] = [[0, INF],[INF, INF]],  MinHeap: [(0, (0,0))]

    Pop (0, (0,0)):
        → (0,1): newCost = max(0, 2) = 2 < INF → dist=2, push (2,(0,1))
        → (1,0): newCost = max(0, 1) = 1 < INF → dist=1, push (1,(1,0))

    Pop (1, (1,0)):
        → (1,1): newCost = max(1, 3) = 3 < INF → dist=3, push (3,(1,1))
        → (0,0): newCost = max(1, 0) = 1 > 0   → skip

    Pop (2, (0,1)):
        → (1,1): newCost = max(2, 3) = 3 = 3   → skip (not <)
        → (0,0): newCost = max(2, 0) = 2 > 0   → skip

    Pop (3, (1,1)):
        destination! return 3 ✓

    Binary Search approach:
    lo=0, hi=3
        mid=1: BFS with limit 1 → can reach (0,0),(1,0) but not (1,1) → false → lo=2
        mid=2: BFS with limit 2 → can reach (0,0),(0,1),(1,0) but not (1,1) → false → lo=3
        mid=3: BFS with limit 3 → can reach all cells → true → ans=3, hi=2
    Return 3 ✓
*/

class Solution {
private:
    int rows, cols;
    int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    bool canSwimBFS(const vector<vector<int>>& grid, int limit) {
        queue<pair<int, int>> Q;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        // Can we start?
        if(grid[0][0] > limit)  return false;   //  you can only be at cell (i,j) at time t if t >= grid[i][j].
        Q.push({0, 0});
        visited[0][0] = true;

        while (!Q.empty()) {
            auto [i, j] = Q.front();
            Q.pop();

            if (i == rows - 1 && j == cols - 1)
                return true;

            for (auto dir : dirs) {
                int x = i + dir[0];
                int y = j + dir[1];
                if (x >= 0 && x < rows && y >= 0 && y < cols &&
                    visited[x][y] == false) {
                    int weight = grid[x][y];
                    if (weight <= limit) {
                        visited[x][y] = true;
                        Q.push({x, y});
                    }
                }
            }
        }
        return false;
    }

public:
    int swimInWater(vector<vector<int>>& grid) {
        rows = grid.size();
        cols = grid[0].size();

        int lo = 0, hi = rows * cols - 1;
        int mid, ans = 0;
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (canSwimBFS(grid, mid) == true) {
                ans = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return ans;
    }
};

/*
    Identification:
    0. Graph (grid)
    1. start (0,0) -> end (n-1, n-1). finding path
    2. grid with elevations. can visit cell only when time t >= elevation.
    3. path optimization - minimize time = minimize max elevation on path. elevations are max()'d not summed
    4. Dijkstra

    Normal Dijkstra
    1. Shortest Path (Minimum)  -> MinHeap
    2. Metric : Path is computed using distance. So metric is distance[]
    3. How add a new node to the path?  add (+) edge weight as distance to the already computed distance[u]
    4. What is the optimization we want? minimum.
       newDistance = ____ (dist[u], weight(u,v))        ->   sum of weights in a path: add the weight +
       if newDistance is ____ than dist[v]              ->   along all paths need minimum: smaller than <

    This Problem
    1. Minimum time (bottleneck)  -> MinHeap
    2. Metric : Time/elevation is used for computation. So metric is distance[]
    3. How add a new node to the path?  max() of edge weight (elevation) with already computed distance[u]
       newCost = ____ (distance[u], grid[x][y])        ->   bottleneck of elevations in a path: take the max
       if newCost is ____ than distance[v]             ->   along all paths need minimum: smaller than <
*/

class Solution2{
private:
    int rows, cols;
    int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
public:
    int swimInWater(vector<vector<int>>& grid){
        rows = grid.size();
        cols = grid[0].size();

        priority_queue<pair<int, pair<int,int>>, vector<pair<int, pair<int,int>>>, greater<pair<int, pair<int,int>>>> PQ;
        vector<vector<int>> distance(rows, vector<int>(cols, INT_MAX));

        distance[0][0] = grid[0][0];
        PQ.push({distance[0][0], {0, 0}});
        while(!PQ.empty()){
            auto[d, cell] = PQ.top(); PQ.pop();
            
            int i = cell.first;
            int j = cell.second;

            if(i==rows-1 && j==cols-1)  return d;

            for (auto dir : dirs) {
                int x = i + dir[0];
                int y = j + dir[1];
                if (x >= 0 && x < rows && y >= 0 && y < cols){
                    int weight = grid[x][y];
                    int newCost = max(distance[i][j], weight);
                    if(newCost < distance[x][y]){
                        distance[x][y] = newCost;
                        PQ.push({newCost, {x, y}});
                    }
                }
            }
        }

        return distance[rows-1][cols-1];
    }
};

int main() {
    return 0;
}
