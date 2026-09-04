#include <iostream>
#include <queue>
#include <deque>
#include <vector>
#include <climits>

using namespace std;

/*
    https://www.youtube.com/watch?v=ivcbaIhrcsE
    Kruskal's Algorithm:
    --------------------
    Intuition:
    - Sort ALL edges by weight (ascending).
    - Greedily pick edges smallest first.
    - Only add an edge if it connects two DIFFERENT components (no cycle).
    - Use Union-Find (DSU) to efficiently check/merge components.
    - Stop when we have V-1 edges.

    Prim's vs Kruskal's:
    - Prim's grows a single tree outward (node by node).
    - Kruskal's merges forests together (edge by edge, globally sorted).

    Pseudocode:
    -----------
    1. Sort edges by weight.
    2. Initialize DSU with V components.
    3. For each edge (u, v, w) in sorted order:
        a. If find(u) != find(v) → different components → add edge, union(u,v).
        b. Else → same component → skip (would create cycle).
    4. Stop after V-1 edges.

    Time:  O(E log E) for sorting + O(E * α(V)) for union-find ≈ O(E log E)
    Space: O(V + E)
*/

// Disjoint Set Union — with path compression and union by rank
class DSU {
public:
    vector<int> parent, rank_;

    DSU(int n) : parent(n), rank_(n, 0) {
        for (int i = 0; i < n; i++)
            parent[i] = i;                         // each node is its own root
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);           // path compression
        return parent[x];
    }

    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;                // already in same set — would form cycle

        if (rank_[px] < rank_[py]) {
            parent[px] = py;                       // px is shorter — attach under py
        }
        else if (rank_[px] > rank_[py]) {
            parent[py] = px;                       // py is shorter — attach under px
        }
        else {
            parent[py] = px;                       // same rank — arbitrary, increase rank
            rank_[px]++;
        }
        return true;                               // successfully merged
    }
};

class SolutionKruskal {
public:
    int spanningTree(int V, vector<vector<int>>& edges, vector<pair<int,int>>& mstEdges) {
        // Build edge list as {weight, u, v} for sorting
        vector<tuple<int,int,int>> edgeList;
        for (auto& e : edges) {
            edgeList.push_back({e[2], e[0], e[1]});  // {weight, u, v}
        }

        sort(edgeList.begin(), edgeList.end());    // sort by weight ascending — O(E log E)

        DSU dsu(V);
        int totalWeight = 0;
        int edgesUsed = 0;

        for (auto [w, u, v] : edgeList) {
            if (dsu.unite(u, v)) {                 // different components — no cycle
                totalWeight += w;                  // add edge weight to MST total
                mstEdges.push_back({u, v});        // record this MST edge
                edgesUsed++;
                if (edgesUsed == V - 1) break;     // MST complete — V-1 edges
            }
            // else: same component — skip to avoid cycle
        }
        return totalWeight;
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

    // --- Prim's ---
    Solution sol;
    vector<int> parent;
    int totalWeight = sol.spanningTree(V, edges, parent);

    cout << "=== Prim's ===" << endl;
    cout << "MST total weight: " << totalWeight << endl;
    cout << "MST edges:" << endl;
    for (int i = 1; i < V; i++) {
        cout << "  " << parent[i] << " - " << i << endl;
    }

    // --- Kruskal's ---
    SolutionKruskal kruskal;
    vector<pair<int,int>> mstEdges;
    int kruskalWeight = kruskal.spanningTree(V, edges, mstEdges);

    cout << "\n=== Kruskal's ===" << endl;
    cout << "MST total weight: " << kruskalWeight << endl;
    cout << "MST edges:" << endl;
    for (auto [u, v] : mstEdges) {
        cout << "  " << u << " - " << v << endl;
    }

    return 0;
}
