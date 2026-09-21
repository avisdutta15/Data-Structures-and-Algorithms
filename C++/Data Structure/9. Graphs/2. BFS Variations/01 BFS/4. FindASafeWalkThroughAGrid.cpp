
#include <iostream>
#include <queue>
#include <deque>
#include <vector>
#include <climits>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 3286 - Find a Safe Walk Through a Grid

    You are given an m x n binary matrix `grid` and an integer `health`.
    You start at (0,0) and want to reach (m-1, n-1). You can move
    up, down, left, or right.

    Each cell has a value:
        0 = safe cell    (no health lost)
        1 = unsafe cell  (lose 1 health)

    You lose health equal to grid[i][j] when you STEP ON cell (i,j),
    including the starting cell (0,0). You must maintain health > 0
    at ALL times (including after stepping on the destination).

    Return true if you can reach (m-1, n-1) safely, false otherwise.

    Examples:
    ---------

    Example 1:
        Input:  grid = [[0,1,0,0,0],
                        [0,1,0,1,0],
                        [0,0,0,1,0]]
                health = 1
        Output: true
        Explanation:
            Path along safe cells: all 0s → no health lost.
            Final health = 1 > 0 ✓

    Example 2:
        Input:  grid = [[0,1,1,0,0,0],
                        [1,0,1,0,0,0],
                        [0,1,1,1,0,1],
                        [0,0,1,0,1,0]]
                health = 3
        Output: false

    Example 3:
        Input:  grid = [[1,1,1],
                        [1,0,1],
                        [1,1,1]]
                health = 5
        Output: true

    Constraints:
    ------------
    - m == grid.length, n == grid[i].length
    - 1 <= m, n <= 50
    - grid[i][j] is 0 or 1
    - 1 <= health <= m + n

    Key Insight:
    ------------
    The total health lost on a path = sum of grid values along the path.
    We need: health - (sum of grid values on path) > 0
    i.e.:    sum of grid values on path < health

    This means: find the path with MINIMUM total cost from (0,0) to
    (m-1, n-1), where cost = grid value (0 or 1). If that minimum
    cost < health, answer is true.

    This is a shortest path problem with weights 0 and 1.

    Identification:
    ----------------
    0. Graph (grid)
    1. start (0,0) -> end (m-1, n-1), finding path
    2. edge weights are 0 or 1 (grid cell values)
    3. path optimization — minimize total health lost (sum of weights)
    4. Dijkstra / 0-1 BFS

    Normal Dijkstra               This Problem
    ────────────────              ────────────
    Minimize distance             Minimize total health lost
    MinHeap                       MinHeap (or 0-1 BFS deque)
    dist[v] = dist[u] + w        dist[v] = dist[u] + grid[v]
    relax if newDist < dist[v]    relax if newDist < dist[v]
    return dist[dest]             return dist[dest] < health

    Approach 1: Brute Force DFS
    ----------------------------
    Try every path, subtract grid[x][y] from health at each step.
    Return true if any path reaches destination with health > 0.
    Time:  O(4^(m×n)) worst case
    Space: O(m × n)

    Approach 2: Dijkstra (min-heap)
    --------------------------------
    Standard shortest path on grid. Weights = grid cell values (0 or 1).
    Find minimum cost to reach (m-1, n-1), check if cost < health.
    Time:  O(m × n × log(m × n))
    Space: O(m × n)

    Approach 3: 0-1 BFS (deque) — optimal
    ----------------------------------------
    Weights are only 0 or 1 → deque replaces heap:
        - Weight 0 → push to FRONT
        - Weight 1 → push to BACK
    Time:  O(m × n)
    Space: O(m × n)

    Dry Run (grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]], health = 1):
    ----------------------------------------------------------------------

    Grid:   0  1  0  0  0
            0  1  0  1  0
            0  0  0  1  0

    Push (0,0) cost=0 (grid=0) to front.

    Pop (0,0) dist=0:
        → (0,1): w=1, newDist=1 → push back
        → (1,0): w=0, newDist=0 → push front

    Pop (1,0) dist=0:
        → (2,0): w=0, newDist=0 → push front

    Pop (2,0) dist=0:
        → (2,1): w=0, newDist=0 → push front

    Pop (2,1) dist=0:
        → (2,2): w=0, newDist=0 → push front

    Pop (2,2) dist=0:
        → (1,2): w=0, newDist=0 → push front
        → (2,3): w=1, newDist=1 → push back

    Pop (1,2) dist=0:
        → (0,2): w=0, newDist=0 → push front

    Pop (0,2) dist=0:
        → (0,3): w=0, newDist=0 → push front

    Pop (0,3) dist=0:
        → (0,4): w=0, newDist=0 → push front

    Pop (0,4) dist=0:
        → (1,4): w=0, newDist=0 → push front

    Pop (1,4) dist=0:
        → (2,4): w=0, newDist=0 → push front

    Pop (2,4) dist=0:
        destination! dist=0 < health=1 → return true ✓

    Path: (0,0)→(1,0)→(2,0)→(2,1)→(2,2)→(1,2)→(0,2)→(0,3)→(0,4)→(1,4)→(2,4)
    All safe cells, 0 health lost.
*/

class Solution1 {
private:
    int rows, cols;
    int dirs[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};

    bool DFS(const vector<vector<int>>& grid, int i, int j, vector<vector<bool>> &visited, int health){
        if(i == rows-1 && j == cols-1){
            return health > 0;
        }

        // Pruning
        if(health <=0)  return false;

        visited[i][j] = true;
        for(auto dir: dirs){
            int x = i + dir[0];
            int y = j + dir[1];

            if(x>=0 && x<rows && y>=0 && y<cols && visited[x][y] == false){
                if(DFS(grid, x, y, visited, health - grid[x][y]) == true)
                    return true;

                // else take another edge
            }
        }
        visited[i][j] = false;
        return false;
    }
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        rows = grid.size();
        cols = grid[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        return DFS(grid, 0, 0, visited, health - grid[0][0]);
    }
};


// Find the shortest path in the graph with edge weights either 0 or 1.
// if the length of the shortest path > health, then we can reach else not.
// why shortest path? Because any longer path is possible only by adding an edge
// with weight 1. If we add this edge then the health will be decreased by 1.
// So the shortest path is the gurantee.

class Solution2{
private:
    int rows, cols;
    int dirs[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        rows = grid.size();
        cols = grid[0].size();

        
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> PQ;
        vector<vector<int>> distance(rows, vector<int>(cols, INT_MAX));

        PQ.push({grid[0][0], {0, 0}});
        distance[0][0] = grid[0][0];

        while(!PQ.empty()){
            auto [d, cell] = PQ.top(); PQ.pop();
            
            int i = cell.first;
            int j = cell.second;

            if(d > distance[i][j])  continue;

            for(auto dir: dirs){
                int x = i + dir[0];
                int y = j + dir[1];

                if(x>=0 && x<rows && y>=0 && y<cols){
                    int weight = grid[x][y];
                    int newDistance = distance[i][j] + weight;
                    if(newDistance < distance[x][y]){
                        distance[x][y] = newDistance;
                        PQ.push({distance[x][y], {x, y}});
                    }
                }
            }
        }

        return distance[rows-1][cols-1] < health ? true : false;
    }
};


class Solution3{
private:
    int rows, cols;
    int dirs[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        rows = grid.size();
        cols = grid[0].size();
        
        deque<pair<int, int>> Q;
        vector<vector<int>> distance(rows, vector<int>(cols, INT_MAX));

        Q.push_back({0,0});
        distance[0][0] = grid[0][0];

        while(!Q.empty()){
            auto [i, j] = Q.front(); Q.pop_front();
            
            for(auto dir: dirs){
                int x = i + dir[0];
                int y = j + dir[1];

                if(x>=0 && x<rows && y>=0 && y<cols){
                    int weight = grid[x][y];
                    int newDistance = distance[i][j] + weight;
                    if(newDistance < distance[x][y]){
                        distance[x][y] = newDistance;
                        if(weight == 0)
                            Q.push_front({x, y});
                        else if(weight == 1)
                            Q.push_back({x, y});
                    }
                }
            }
        }

        return distance[rows-1][cols-1] < health ? true : false;
    }
};



int main() {
    return 0;
}
