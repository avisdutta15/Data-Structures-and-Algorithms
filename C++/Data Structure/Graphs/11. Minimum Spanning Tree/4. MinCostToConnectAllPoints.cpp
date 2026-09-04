#include <iostream>
#include <queue>
#include <deque>
#include <vector>
#include <climits>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
    https://youtu.be/bmyyxNyZKzI?list=PLPaDsoN2Ogta7u1gNi4k-imso0Y2yQX8j&t=1102
    https://www.youtube.com/watch?v=6h1SucBNxgc

    Problem Statement:
    ------------------
    LeetCode 1584 - Min Cost to Connect All Points

    Given an array of points where points[i] = [xi, yi] represents a point
    on the 2D plane, return the minimum cost to make all points connected.
    The cost of connecting two points = Manhattan distance = |xi - xj| + |yi - yj|.
    All points have an implicit edge to every other point (complete graph).

    Examples:
    ---------
    Example 1:
        Input:  points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
        Output: 20

    Example 2:
        Input:  points = [[3,12],[-2,5],[-4,1]]
        Output: 18

    Constraints:
    ------------
    - 1 <= points.length <= 1000
    - -10^6 <= xi, yi <= 10^6
    - All pairs of (xi, yi) are distinct.

    Identification:
    ---------------
    - "Connect ALL points with minimum total cost" → MST.
    - Graph is implicit and complete (every pair connected) → dense graph, E = V*(V-1)/2.
    - No explicit edge list — compute Manhattan distance on the fly.

    Approach: Prim's Algorithm
    --------------------------
    - When a node is added to MST, compute distance to ALL unvisited nodes
      and push {cost, {parent, node}} to the min-heap.
    - No adjacency list needed — just loop over all points.

    Time:  O(V² log V) — V² edges total, each pushed to heap
    Space: O(V²) worst case for heap entries

    points[i] is the (x, y) coordinate of the i-th point.

        points[0] = [3, 12]    → point 0 is at x=3, y=12
        points[1] = [5, 7]     → point 1 is at x=5, y=7
    
    So points[0][0] is the x-coordinate of point 0, and points[0][1] is the y-coordinate of point 0.

    In the code, u and v are not coordinates — they're point indices (which point in the array). 
    The Manhattan distance between point u and point v is:

    abs(points[u][0] - points[v][0])    // |x_u - x_v|
    + abs(points[u][1] - points[v][1])  // |y_u - y_v|
    So points[u][0] = x of point u, points[v][1] = y of point v. Not u and v themselves.
*/

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();

        // Min-heap: {edge_cost, {parent, node}}
        priority_queue<pair<int, pair<int, int>>,vector<pair<int, pair<int, int>>> ,greater<pair<int, pair<int, int>>>> PQ;
        int totalCost = 0;
        int nodesInMST = 0;
        unordered_set<int> visited;

        PQ.push({0, {-1, 0}});                     // start from point 0, cost 0, no parent

        while(!PQ.empty()){
            auto[c, cell] = PQ.top();
            PQ.pop();

            int parent_u = cell.first;              // node that connected u to MST
            int u = cell.second;                    // node being added to MST

            if(visited.count(u) > 0) continue;      // already in MST — stale entry

            visited.insert(u);                       // add u to MST
            totalCost = totalCost + c;               // add this edge's cost to total
            nodesInMST++;
            if(nodesInMST == n)                      // all nodes in MST — done
                break;

            // push edges to ALL unvisited points (implicit complete graph)
            for(int v = 0; v < n; v++){
                if(visited.count(v) == 0){
                    int val = abs(points[u][0] - points[v][0])    // |x_u - x_v|
                            + abs(points[u][1] - points[v][1]);   // |y_u - y_v|
                    PQ.push({val, {u, v}});          // single edge weight, not cumulative
                }
            }
        }
        return totalCost;
    }
};

int main() {
    return 0;
}
