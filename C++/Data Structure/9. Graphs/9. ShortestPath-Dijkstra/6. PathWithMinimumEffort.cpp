#include <algorithm>
#include <iostream>
#include <set>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string.h>

using namespace std;


/*
    Problem Statement:
    ------------------
    LeetCode 1631 - Path With Minimum Effort

    You are a hiker preparing for an upcoming hike. 
    You are given heights, a 2D array of size rows x columns, where heights[row][col] 
    represents the height of cell (row, col). 
    You are situated in the top-left cell, (0, 0), and you hope to travel to the 
    bottom-right cell, (rows-1, columns-1) (i.e., 0-indexed). 
    You can move up, down, left, or right, and you wish to find a route that requires the minimum effort.

    A route's effort is the maximum absolute difference in heights between two 
    consecutive cells of the route.

    Return the minimum effort required to travel from the top-left cell to 
    the bottom-right cell.
    
    Examples:
    ---------

    Example 1:
        Input:  heights = [[1,2,2],
                           [3,8,2],
                           [5,3,5]]
        Output: 2
        Explanation: Path (0,0)→(1,0)→(2,0)→(2,1)→(2,2), max step = 2

    Example 2:
        Input:  heights = [[1,2,3],
                           [3,8,4],
                           [5,3,5]]
        Output: 1

    Example 3:
        Input:  heights = [[1,10,6,7,9,10,4,9]]
        Output: 9

    Constraints:
    ------------
    - 1 <= rows, cols <= 100
    - 1 <= heights[i][j] <= 10^6

    Intuition:
    ----------
    - "Effort" of a path = the maximum absolute height difference between
      any two consecutive cells on that path. It's NOT the sum — just the
      single worst step.

    - For each path, we carry a "running max" of edge costs as we walk.
      Each time we step to a neighbor, we ask: is this step worse than
      anything I've seen so far? If yes, it becomes the new effort for
      this path. If no, the old worst still holds.

          currentPathMax = max(currentPathMax, |heights[u] - heights[v]|)

    - We explore many paths. Each path ends with its own currentPathMax.
      Across all paths, we track the global minimum of these maxes:

          globalMinPathMax = min(globalMinPathMax, currentPathMax)

      This is the answer — the path whose worst step is the least bad.

    How DFS works (Brute Force):
    ----------------------------
    - Try every possible path from (0,0) to (m-1,n-1) using backtracking.
    - As we walk, carry a "running max" (currentPathMax) — the worst step
      seen so far on this particular path.
    - When we reach the destination, compare currentPathMax with globalMinPathMax
      and update it if this path is better.
    - Backtrack (unmark visited) to allow exploring other paths through the same cell.
    - Pruning: if currentPathMax already exceeds globalMinPathMax, skip — this
      path can't beat the best we've already found.
    - Time: O(4^(m*n)) — exponential because we explore all possible paths.

    How Binary Search + BFS works:
    ------------------------------
    - Instead of finding the answer directly, flip the question:
      "Can I reach the destination if I only allow effort ≤ X?"
    - This is a yes/no question — perfect for binary search.
    - Binary search on X (the effort limit): lo = 0, hi = 10^6.
    - For each mid, run BFS but only take edges where |diff| <= mid.
      If BFS reaches (m-1,n-1), then mid is feasible → try smaller.
      If not, mid is too small → try larger.
    - The smallest feasible mid is the answer.
    - Time: O(m*n * log(maxVal)) — BFS is O(m*n) and runs log(maxVal) times.

    How this is a Shortest Path problem — and how Dijkstra fits:
    ------------------------------------------------------------
    - Treat each cell as a node in a graph.
    - Edge weight between adjacent cells = |height difference|.
    - We want the path from source to destination that minimizes the
      maximum edge weight along the path (a "bottleneck shortest path").
    - Dijkstra works here because:
        • We use a min-heap, so we always expand the node reachable
          with the least effort so far.
        • Once a node is popped, its optimal effort is finalized — same
          greedy guarantee as classic Dijkstra.

    How it differs from normal Dijkstra:
    ------------------------------------
    Normal Dijkstra:
        - Minimizes the SUM of edge weights.
        - Relax:  if (dist[u] + weight(u,v) < dist[v])
                       dist[v] = dist[u] + weight(u,v)

    This problem's Dijkstra:
        - Minimizes the MAXIMUM edge weight on the path.
        - Relax:  if (max(dist[u], weight(u,v)) < dist[v])
                       dist[v] = max(dist[u], weight(u,v))
        - The only change: replace '+' with 'max' in the relaxation step.
        - dist[u] already summarizes the worst step from start to u.
          Extending to v, we just check if the new step is worse than that.
    - Time: O(m*n * log(m*n)) — standard Dijkstra with E edges and V vertices.

    Approaches:
    -----------
    1. Brute Force DFS        — O(4^(m*n))         try every path
    2. Binary Search + BFS    — O(m*n * log(1e6))  binary search on effort
    3. Dijkstra               — O(m*n * log(m*n))  min-heap on bottleneck cost
*/

// Approach 1:  Just try every possible path, track the max difference along each, return the minimum.
// Time complexity : O(4^m*n)
class Solution{
private:
    int dirs[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
    int rows, cols;

    void DFS(const vector<vector<int>>& heights, int i, int j
        , vector<vector<bool>> &visited
        , int currentPathMax, int &globalMinPathMax){
        
        if(i == rows - 1 && j == cols - 1){
            globalMinPathMax = min(globalMinPathMax, currentPathMax);
            return;
        }

        visited[i][j] = true;
        for(auto dir: dirs){
            int x = i + dir[0];
            int y = j + dir[1];

            if(x >=0 && x < rows && y>=0 && y<cols && visited[x][y] == false){
                int edgeCost = abs(heights[i][j] - heights[x][y]);
                int newPathMax = max(currentPathMax, edgeCost);

                // early pruning
                if(newPathMax > globalMinPathMax)
                    continue;

                DFS(heights, x, y, visited, newPathMax, globalMinPathMax);
            }
        }
        visited[i][j] = false;
    }

public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        rows = heights.size();
        cols = heights[0].size();

        int currentPathMax = 0;
        int globalMinPathMax = INT_MAX;
        vector<vector<bool>> visited(rows, vector<bool> (cols, false));
        DFS(heights, 0, 0, visited, currentPathMax, globalMinPathMax);
        return globalMinPathMax;
    }
};

// Approach 2: Binary Search + BFS/DFS
/*
    Key Insight: Instead of finding the answer directly, 
    ask: "Can I reach the destination if I only allow effort ≤ X?"

    This turns it into a yes/no question — perfect for binary search.

    Binary search on the answer: lo = 0, hi = max possible diff (~1e6)
    For each mid, do a BFS/DFS allowing only moves where |diff| <= mid
    Find the smallest mid where you can reach the destination

    Time Complexity : Binary Search runs on the effort search space.
    effort search space - (0 to 10^6) i.e. - O(log(maxValue))
    for each mid we are calling BFS - i.e. O(m * n)
    Total - O(log(maxValue) * m * n)
*/

class Solution2{
private:
    const int dirs[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
    int rows, cols;
    bool canReachBFS(vector<vector<int>>& heights, int limit){
        queue<pair<int, int>> Q;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        Q.push({0,0});
        visited[0][0] = true;

        while(!Q.empty()){
            auto[i, j] = Q.front();
            Q.pop();

            if(i == rows-1 && j == cols-1)
                return true;

            for(auto dir: dirs){
                int x = i + dir[0];
                int y = j + dir[1];
                if(x>=0 && x<rows && y>=0 && y<cols){
                    int edgeCost = abs(heights[x][y] - heights[i][j]);
                    if(edgeCost <= limit && visited[x][y] == false){
                        Q.push({x, y});
                        visited[x][y] = true;
                    }
                }
            }
        }
        return false;
    }
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        rows = heights.size();
        cols = heights[0].size();

        // The range of effort (absolute difference) between two adjacent cells can be 0. (1-1 = 0)
        // to the highest limit of heights[i][j] i.e. 10^6. Why 10^6 ? (10^6 - 1 ~ 10^6)
        int lo = 0, hi = 1e6;
        int mid;
        int ans;
        while(lo <= hi){
            mid = lo + (hi - lo)/2;
            if(canReachBFS(heights, mid)){
                ans = mid;
                hi = mid - 1;
            }
            else{
                lo = mid + 1;
            }
        }
        return ans;
    }
};

// Approach 3: Dijkstra
/*
    The Real Insight: This is just a shortest path problem in disguise.
    - Treat each cell as a node
    - Edge weight between adjacent cells = |diff|
    - But we're not minimizing sum of edges (standard Dijkstra) — we're minimizing the maximum edge on a path
    - Dijkstra works perfectly here as dist[r][c] means "minimum possible max-effort to reach (r,c) from source"

    In traditional Dijkstra, at the relaxation step you ask:
        "Is the cost to reach neighbor through the current node cheaper than what I already know?"

        if (dist[u] + weight(u, v) < dist[v])
            dist[v] = dist[u] + weight(u, v)

    In this problem - 
        "Can I reach neighbor v with a lower max-effort by going through u?"
        
        newEffort = max(dist[u], |grid[v] - grid[u]|)
        if (newEffort < dist[v])
            dist[v] = newEffort

    How does this work?
    - effort[i][j] contains the maximum effort that is needed from start → ... → u
    - When we extend to v, we add one new step with edge cost / weight i.e. stepdiff = |grid[v] - grid[u]|.
    - The effort of the full path start → ... → u → v is the max of all steps.
    - But we don't need to look at every previous step individually.
        They're already summarized in dist[u].
        So max effort (start → ... → u → v):
            = max(worst step on start→...→u,  cost of u→v)
            = max(dist[u],  |grid[v] - grid[u]|)

    RELAX step:
    -   "Can I reach neighbor v with a lower max-effort by going through u?"
    -   This is because, we want to minimize the max effort.
        if(effort[x][y] > newEffort){
            effort[x][y] = newEffort;
            PQ.push({effort[x][y], {x, y}});
        }

    Why Dijkstra works: At each step, we greedily expand the cell reachable 
    with the least effort so far. Once we pop a cell from the min-heap, we've 
    found its optimal effort — same guarantee as classic Dijkstra.

    In the effort problem, you swap + for max:

    if (dist[u] + weight(u, v) < dist[v])
    dist[v] = dist[u] + weight(u, v)

    to

    if (max(dist[u], |grid[v] - grid[u]|) < dist[v])
    dist[v] = max(dist[u], |grid[v] - grid[u]|)

    Time Complexity : E log (V) -> (m*n)*log(m*n)
*/

/*  
    Identification:
    0. Graph (implicit grid graph)
    1. start (0,0) -> end (m-1,n-1). finding path
    2. graph is undirected with weights (absolute height difference).
    3. path optimization - minimum effort. effort is the max of edge weights, not sum
    4. Dijkstra

    Normal Dijkstra
    1. Shortest Path (Minimum)  -> MinHeap
    2. Metric : Path is computed using distance. So metric is distance[]
    3. How add a new node to the path?  add (+) edge weight to distance[u]
    4. What is the optimization we want? minimum.

    newDistance = ____ (dist[u], weight(u,v))        ->   sum of weights: +
    if newDistance is ____ than dist[v]              ->   minimize: <

    This Problem
    1. Minimum Effort  -> MinHeap
    2. Metric : Effort (worst step so far) is used for computation. So metric is effort[]
    3. How add a new node to the path?  take max of edge weight and already computed effort[u]
       (not adding — just checking if this step is worse than anything before)

    newEffort = ____ (effort[u], weight(u,v))       ->   bottleneck of weights in a path: max
    if newEffort is ____ than effort[v]             ->   along all paths need minimum: <
*/
class Solution3{
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int rows = heights.size();
        int cols = heights[0].size();
        int dirs[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

        priority_queue<pair<int, pair<int,int>>
        , vector<pair<int, pair<int,int>>>
        , greater<pair<int, pair<int,int>>>>PQ;

        vector<vector<int>> effort(rows, vector<int>(cols, INT_MAX));
        PQ.push({0, {0,0}});
        effort[0][0] = 0;

        while(!PQ.empty()){
            auto[e, cell] = PQ.top();
            PQ.pop();

            int i = cell.first;
            int j = cell.second;

            if(i == rows - 1 && j == cols - 1) return e;
            if(e > effort[i][j])  continue;

            for(auto dir : dirs){
                int x = i + dir[0];
                int y = j + dir[1];
                if(x >=0 && x<rows && y>=0 && y <cols){
                    int stepDiff = abs(heights[i][j] - heights[x][y]);      // weight of this edge

                    // effort[i][j] contains the maximum
                    // effort that is needed from start → ... → u
                    // When we extend to v, we add one new step with edge cost i.e. stepdiff = |grid[v] - grid[u]|.
                    // The effort of the full path start → ... → u → v is the max of all steps.
                    // But we don't need to look at every previous step individually.
                    // They're already summarized in dist[u].

                    // So max effort (start → ... → u → v):
                    // = max(worst step on start→...→u,  cost of u→v)
                    // = max(dist[u],  |grid[v] - grid[u]|)
                    int newEffort = max(effort[i][j], stepDiff);

                    // if some other path had populated the effort[x][y].
                    // and the maxEffort using this path is lower, we use this effort.
                    // "Can I reach neighbor v with a lower max-effort by going through u?"
                    // This is because, we want to minimize the max effort.
                    if(effort[x][y] > newEffort){
                        effort[x][y] = newEffort;
                        PQ.push({effort[x][y], {x, y}});
                    }
                }
            }
        }
        return effort[rows-1][cols-1];
    }
};


int main() {
	return 0;
}