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
	In this problem, a tree is an undirected graph that is connected and has no cycles.
    You are given a graph that started as a tree with n nodes labeled from 1 to n, 
    with one additional edge added.

    The added edge has two different vertices chosen from 1 to n, and was not an edge 
    that already existed.
    
    The graph is represented as an array edges of length n where edges[i] = [ai, bi] 
    indicates that there is an edge between nodes ai and bi in the graph.

    Return an edge that can be removed so that the resulting graph is a tree of n nodes. 
    If there are multiple answers, return the answer that occurs last in the input.

	Example:
	--------
    Input: edges = [[1,2],[1,3],[2,3]]
    Output: [2,3]

    Input: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
    Output: [1,4]

    Approach 1 : DFS
    ----------------
    Process edges one by one. 
    Before adding each edge (u, v) to the graph, check if u and v are already connected using DFS. 
    If they are → this edge creates a cycle → it's the redundant edge.
	
    For each of the N edges, we potentially run a DFS that visits up to N nodes. So worst case: N edges × O(N) DFS = O(N²).

    Approach 2 : DSU
	----------------
    How DSU detects the redundant edge:
        Process edges one by one. For each edge (u, v):

        Find(u) ≠ Find(v): u and v are in different components → union them. 
        This edge is safe (connecting two separate parts).
        
        Find(u) == Find(v): u and v are already connected → adding this edge 
        creates a cycle. This is the redundant edge.

    Since we process edges in order, the last edge that creates a cycle is our answer.

    Time: O(N · α(N)) where N is the number of edges
    In Union by Rank and Path Compression.
        Union and Find takes α(N) time.

    α(N) is nearly constant (less than 5 for any practical value of N).
*/

// DFS
class Solution1 {
public:

    bool dfs(unordered_map<int, vector<int>>& adj, int u, int v, vector<bool>& visited) {
        visited[u] = true;

        if (u == v) {
            return true;
        }

        for (int& ngbr : adj[u]) {
            if (visited[ngbr]) continue;

            if (dfs(adj, ngbr, v, visited)) {
                return true;
            }
        }

        return false;

    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        //number of nodes = n
        //number of edges = n

        unordered_map<int, vector<int>> adj;

        // for every edge try to build the graph, 
        // before adding the edge check if u and v are already connected
        for (int i = 0; i < n; i++) {
            int u = edges[i][0];
            int v = edges[i][1];

            vector<bool> visited(n, false);
            if (adj.find(u) != adj.end() && adj.find(v) != adj.end() && dfs(adj, u, v, visited)) {
                return edges[i];
            }

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        return {};
    }
};


class DSU {
public:
    vector<int> parent;
    vector<int> rank;

    DSU(int n) {
        parent.resize(n + 1); //1, 2, 3, 4, 5.., n
        rank.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    // Recursively find parent
    int find(int x) {
        if (x == parent[x]) {
            return x;
        }

        return parent[x] = find(parent[x]); //path compression
    }

    void Union(int x, int y) {
        int x_parent = find(x);
        int y_parent = find(y);

        if (x_parent == y_parent) {
            return;
        }

        if (rank[x_parent] > rank[y_parent]) {
            parent[y_parent] = x_parent;
        }
        else if (rank[y_parent] > rank[x_parent]) {
            parent[x_parent] = y_parent;
        }
        else {
            parent[y_parent] = x_parent; //we made x as the parent
            rank[x_parent]++;
        }
    }
};

// DSU
class Solution2 {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();

        DSU dsu(n);
        //T.C : DSU = alpha(n)

        //T.C : O(n * alpha(n))
        for (auto& edge : edges) { //O(n)
            int u = edge[0];
            int v = edge[1];

            // if both have same parent, then they are already connected
            if (dsu.find(u) == dsu.find(v)) {
                return edge;
            }

            dsu.Union(u, v);
        }

        return {};
    }
};

int main() {


	return 0;
}