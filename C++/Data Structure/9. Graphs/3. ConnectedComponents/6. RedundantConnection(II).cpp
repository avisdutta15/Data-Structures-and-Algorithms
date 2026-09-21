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
	https://www.youtube.com/watch?v=d0tqBMRZ6UQ

	Problem Statement:
	------------------
	In this problem, a rooted tree is a directed graph such that, there is exactly one node 
	(the root) for which all other nodes are descendants of this node, plus every node has 
	exactly one parent, except for the root node which has no parents.

	The given input is a directed graph that started as a rooted tree with n nodes (with distinct 
	values from 1 to n), with one additional directed edge added. 
	
	The added edge has two different vertices chosen from 1 to n, and was not an edge that already existed.
	The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [ui, vi] 
	that represents a directed edge connecting nodes ui and vi, where ui is a parent of child vi.

	Return an edge that can be removed so that the resulting graph is a rooted tree of n nodes. 
	If there are multiple answers, return the answer that occurs last in the given 2D-array.

	Example:
	--------
	Input: edges = [[1,2],[1,3],[2,3]]
	Output: [2,3]
 

	Approach: 
    ---------
    The Three Cases:

    Case 1: There's a cycle, no node has two parents

        1 → 2 → 3 → 1  (cycle, all in-degrees = 1)
    Same as Redundant Connection I — find the edge that completes the cycle.

    Case 2: A node has two parents (in-degree 2), no cycle

        1 → 2
        ↓   ↑
        3 → 4
        and also 1 → 4  (node 4 has two parents: 3 and 1)
    Remove one of the two edges pointing to the node with in-degree 2.
    
    Case 3: A node has two parents AND there's a cycle

        1 → 2 → 3
             ↑   ↓
             +---+   (3 → 2 creates both: in-degree 2 for node 2, and a cycle)
    Remove the edge that's part of BOTH the cycle and the duplicate parent.
	
    Decision Tree
    -------------
            Does any node have in-degree 2?
            |                           |
           YES                          NO
            |                           |
      Set candidate_a, candidate_b    Run DSU on all edges
      Skip candidate_b in DSU          |
            |                       Cycle found → CASE 1
            |                       Return the cycle edge
       Cycle found?
        |          |
       YES         NO
        |          |
     CASE 3      CASE 2
     Return      Return
     candidate_a candidate_b

     Time Complexity:
     ----------------
        Step 1: Scan all edges to find in-degree 2 node → O(N)
        Step 2: Loop through N edges, each doing find + union → N × O(α(N))
        DSU initialization → O(N)
        Total: O(N) + O(N · α(N)) = O(N · α(N)) ≈ O(N)
*/

class DSU {
public:
    vector<int> parent;
    vector<int> rank;

    DSU(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int x) {
        if (x == parent[x]) {
            return x;
        }
        return parent[x] = find(parent[x]); // path compression
    }

    void Union(int x, int y) {
        int x_parent = find(x);
        int y_parent = find(y);
        if (x_parent == y_parent) return;

        if (rank[x_parent] > rank[y_parent]) {
            parent[y_parent] = x_parent;
        }
        else if (rank[y_parent] > rank[x_parent]) {
            parent[x_parent] = y_parent;
        }
        else {
            parent[y_parent] = x_parent;
            rank[x_parent]++;
        }
    }
};

class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size();

        // =================================================================
        // STEP 1: Detect if any node has in-degree 2 (two parents)
        // =================================================================
        // indegree[v] stores the INDEX of the first edge pointing to v
        vector<int> indegree(n + 1, -1);
        int candidate_edge_a = -1; // index of FIRST edge pointing to the in-degree-2 node
        int candidate_edge_b = -1; // index of SECOND edge pointing to the in-degree-2 node

        for (int i = 0; i < n; i++) {
            int u = edges[i][0];
            int v = edges[i][1];

            if (indegree[v] == -1) {
                indegree[v] = i;
            }
            else {
                // Node v has two parents!
                candidate_edge_a = indegree[v]; // first edge to v
                candidate_edge_b = i;           // second edge to v
                break;
            }
        }

        // =================================================================
        // STEP 2: Run Union-Find, skipping candidate_edge_b
        //
        // We temporarily remove the second candidate edge and check
        // if the remaining graph forms a valid tree (no cycle).
        //
        // Three possible outcomes:
        //
        // CASE 1: No node has in-degree 2 (candidates are -1) + cycle found
        //   → The edge forming the cycle is the answer.
        //     (Same as Redundant Connection I)
        //
        // CASE 2: A node has in-degree 2 + no cycle after removing candidate_b
        //   → candidate_b was the redundant edge. Removing it gives a valid tree.
        //
        // CASE 3: A node has in-degree 2 + cycle still exists after removing candidate_b
        //   → candidate_a is the redundant edge. It's part of the cycle AND
        //     contributes to the in-degree-2 problem. Removing it fixes both.
        // =================================================================

        DSU disjointSet(n);

        for (int i = 0; i < n; i++) {
            // Skip candidate_edge_b — we're testing if the graph works without it
            if (i == candidate_edge_b) continue;

            int u = edges[i][0];
            int v = edges[i][1];

            if (disjointSet.find(u) == disjointSet.find(v)) {
                // Cycle detected!
                if (candidate_edge_a == -1) {
                    // CASE 1: No in-degree-2 node exists, pure cycle
                    // The current edge completes the cycle → return it
                    return edges[i];
                }
                else {
                    // CASE 3: In-degree-2 node exists AND cycle persists
                    // even after removing candidate_b.
                    // → candidate_a is in the cycle, it's the real problem
                    return edges[candidate_edge_a];
                }
            }
            else {
                disjointSet.Union(u, v);
            }
        }

        // CASE 2: No cycle found after removing candidate_b
        // → candidate_b was the redundant edge causing in-degree 2
        return edges[candidate_edge_b];
    }
};


int main() {


	return 0;
}