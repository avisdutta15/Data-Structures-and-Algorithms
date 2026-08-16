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
	https://www.youtube.com/watch?v=ottPfSr3xls

	Problem Statement:
	------------------
	Given a directed acyclic graph, with n vertices numbered from 0 to n-1, 
    and an array edges where edges[i] = [fromi, toi] represents a directed 
    edge from node fromi to node toi.

    Find the smallest set of vertices from which all nodes in the graph are reachable. 
    It's guaranteed that a unique solution exists.

    Notice that you can return the vertices in any order.
    
	Example:
	--------
    0         3
    |  \      |
    v   v     v
    1    2 <--4
         |    
         |    
         v
         5

    Edges:
      0 → 1
      0 → 2
      2 → 5
      3 → 4
      4 → 2

    Input: n = 6, edges = [[0,1],[0,2],[2,5],[3,4],[4,2]]
    Output: [0,3]
    Explanation: It's not possible to reach all the nodes from a single vertex. 
    From 0 we can reach [0,1,2,5]. From 3 we can reach [3,4,2,5]. So we output [0,3].
	
	Approach: 
    ---------
	The answer is simply all nodes with in-degree 0.

    Why? A node with in-degree 0 has no incoming edges — no other node can reach it. 
    So it MUST be in our starting set. 
    
    Conversely, any node with in-degree > 0 can be reached from some other node, 
    so we don't need to include it.
*/

class DSU {
public:
    vector<int> parent;

    DSU(int n) {
        parent = vector<int>(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (x == parent[x]) {
            return x;
        }

        return parent[x] = find(parent[x]);
    }


    // This is a directed graph. So we for an edge u -> v
    // where cannot just put the v into u's parent.
    // We need to put u (the one which is pointing) into the v's parent.
    // We donot need rank here.
    void Union(int u, int v) {
        int parentU = find(u);
        parent[v] = parentU;
    }
};

class Solution1 {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        DSU dsu(n);
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            dsu.Union(u, v);
        }

        vector<int> vertices;
        for (int i = 0; i < n; i++) {
            if (i == dsu.parent[i]) {
                vertices.push_back(i);
            }
        }

        return vertices;
    }
};

// Indegree Approach
class Solution2 {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        vector<bool> hasIncoming(n, false);

        for (auto& e : edges) {
            hasIncoming[e[1]] = true;
        }

        vector<int> result;
        for (int i = 0; i < n; i++) {
            if (!hasIncoming[i])
                result.push_back(i);
        }

        return result;
    }
};

int main() {

	return 0;
}