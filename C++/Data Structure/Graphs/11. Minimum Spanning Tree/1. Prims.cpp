#include <iostream>
#include <queue>
#include <deque>
#include <vector>
#include <climits>

using namespace std;

/*
    https://www.youtube.com/watch?v=5M7bOXrn54A
    Problem Statement:
    ------------------
    Minimum Spanning Tree (Prim's Algorithm)

    Given a connected, undirected, weighted graph with V vertices and E edges,
    find the MST — a subset of edges that connects all vertices with the
    minimum total edge weight, using exactly V-1 edges and no cycles.

    Intuition:
    ----------
    - Grow the MST one node at a time.
    - Start from any node. At each step, pick the cheapest edge that
      connects a node IN the MST to a node NOT yet in the MST.
    - This is greedy — very similar to Dijkstra, but:
        Dijkstra: push {cumulative path cost, node}    → minimizes distance from source
        Prim's:   push {single edge weight, node}      → minimizes total tree weight


    WHAT DATA STRUCTURE ? MinHeap
    WHAT TO STORE?  edge_cost and the edge (start->end)
    

    Why single edge weight and not cumulative?
    - MST goal: minimize sum of ALL edges picked.
    - The "cut property" guarantees: for any cut separating the MST-so-far
      from the rest, the cheapest crossing edge MUST be in the MST.
    - Prim's always picks exactly that edge.

    Pseudocode:
    -----------
    1. Build adjacency list from edges.
    2. Initialize min-heap with {weight=0, startNode, parent=-1}.
    3. While heap is not empty:
        a. Pop {w, u, parent_u} with smallest weight.
        b. If u is already visited, skip (stale entry).
        c. Mark u as visited. Add w to total. Record parent[u].
        d. For each neighbor v of u:
            - If v is not visited, push {edge_weight(u,v), v, u} to heap.
    4. Return total weight.

    Time:  O((V + E) * log V)  — each edge pushed/popped from heap at most once
    Space: O(V + E)
*/

class Solution {
  public:
    int spanningTree(int V, vector<vector<int>>& edges, vector<int>& parent) {
        // Build adjacency list: {neighbor, weight}
        vector<vector<pair<int, int>>> graph(V, vector<pair<int, int>>());
        
        for(auto edge: edges){
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];

            graph[u].push_back({v, weight});       // undirected — add both directions
            graph[v].push_back({u, weight});
        }
        
        // Min-heap: {edge_weight, {start, end}}
        // The min heap contains the edges based on the minimum edge cost.  
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>>PQ;
        vector<bool> visited(V, false);            // tracks nodes already in MST
        parent.assign(V, -1);                      // parent[u] = node that connected u to MST
        int minEdgeWeightSum = 0;                  // total MST weight

        PQ.push({0, {-1, 0}});                     // start from node 0, cost 0, no parent  - edge -1 -> 0
        
        while(!PQ.empty()){
            auto[w, cell]= PQ.top();
            PQ.pop();

            int parent_u = cell.first;
            int u = cell.second;

            if(visited[u] == true)                 // already in MST — stale entry, skip
                continue;
            
            visited[u] = true;                     // add u to MST
            minEdgeWeightSum = minEdgeWeightSum + w;  // add this edge's weight to total
            parent[u] = parent_u;                  // record which node connected u to the MST

            for(auto neighbour: graph[u]){
                int v = neighbour.first;
                int weight = neighbour.second;
                if(visited[v] == false){           // only push nodes not yet in MST
                    PQ.push({weight, {u, v}});     // push single edge weight (NOT cumulative)
                }
            }
        }
        return minEdgeWeightSum;
    }
};

int main() {
    /*
        Example graph:
            0 ---1--- 1
            |       / |
            4     2   3
            |   /     |
            2 ---5--- 3

        Edges: (0,1)=1, (0,2)=4, (1,2)=2, (1,3)=3, (2,3)=5
        Expected MST: (0,1)=1, (1,2)=2, (1,3)=3 → total = 6
    */
    int V = 4;
    vector<vector<int>> edges = {
        {0, 1, 1},
        {0, 2, 4},
        {1, 2, 2},
        {1, 3, 3},
        {2, 3, 5}
    };

    Solution sol;
    vector<int> parent;
    int totalWeight = sol.spanningTree(V, edges, parent);

    cout << "MST total weight: " << totalWeight << endl;
    cout << "MST edges:" << endl;
    for (int i = 1; i < V; i++) {                  // skip node 0 (root, parent = -1)
        cout << "  " << parent[i] << " - " << i << endl;
    }

    return 0;
}
