#include <iostream>
#include <queue>
#include <deque>
#include <vector>
#include <climits>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 1192 - Critical Connections in a Network

    There are n servers numbered from 0 to n-1 connected by undirected
    connections. A critical connection (bridge) is a connection that, if
    removed, will make some servers unable to reach others.
    Return all critical connections in any order.

    Examples:
    ---------
    Example 1:
        Input:  n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
        Output: [[1,3]]

        0 --- 1 --- 3
        |     |
        +--2--+
        Edge (1,3) is a bridge. Removing it disconnects node 3.
        Edges (0,1), (1,2), (2,0) form a cycle — not bridges.

    Constraints:
    ------------
    - 2 <= n <= 10^5
    - n - 1 <= connections.length <= 10^5

    Intuition:
    ----------
    - Run DFS and classify edges into tree edges and back edges.
    - Track two arrays:
        disc[u] = discovery time (when DFS first visits u)
        dbe[u]  = "deepest back edge" — earliest disc[] reachable from
                  u's subtree through back edges.

    - For a tree edge u → v (v is child):
        After DFS(v) returns, propagate: dbe[u] = min(dbe[u], dbe[v])
        "If my child can reach something early, so can I."

    - For a back edge u → v (v is already-visited ancestor):
        Update: dbe[u] = min(dbe[u], disc[v])
        "I can reach this ancestor through a back edge."

    Bridge condition (only for tree edges u → v):
        if (dbe[v] > disc[u]) → BRIDGE
        Meaning: v's entire subtree cannot reach u or above through any
        back edge. Removing (u,v) disconnects v's subtree.

    Time:  O(V + E) — single DFS pass
    Space: O(V + E)
*/

class Solution {
private:
    int n;
    vector<int> disc;       // disc[u] = discovery time of node u
    vector<int> dbe;        // dbe[u] = earliest disc[] reachable from u's subtree via back edges
    vector<bool> visited;
    int time;               // global DFS timer

    void dfs(const vector<vector<int>> &graph, int u, int parentU, vector<vector<int>> &bridges){
        visited[u] = true;
        time = time + 1;
        disc[u] = time;                            // record discovery time
        dbe[u] = time;                             // initialize: earliest reachable is self

        for(auto v: graph[u]){
            // TREE EDGE: v is unvisited child of u
            if(visited[v] == false){
                dfs(graph, v, u, bridges);

                dbe[u] = min(dbe[u], dbe[v]);      // propagate: if child reaches earlier, so can I

                // BRIDGE CHECK (only for tree edges):
                // dbe[v] > disc[u] means v's subtree can't reach u or above
                // → removing (u,v) disconnects v's subtree
                if(dbe[v] > disc[u])
                    bridges.push_back({u, v});
            }
            // PARENT EDGE: skip — going back to parent isn't a back edge
            else if(v == parentU)
                continue;
            // BACK EDGE: v is already-visited ancestor
            else{
                dbe[u] = min(dbe[u], disc[v]);     // u can reach ancestor v via back edge
            }
        }
    }
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        this->n = n;
        vector<vector<int>> bridges;
        vector<vector<int>> graph(n, vector<int>());    // adjacency list

        disc.resize(n, -1);
        dbe.resize(n, -1);
        visited.resize(n, false);
        time = 0;

        // build undirected adjacency list from edge list
        for(auto connection : connections){
            int u = connection[0];
            int v = connection[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        // handle disconnected components
        for(int u=0; u<n; u++){
            if(visited[u] == false)
                dfs(graph, u, -1, bridges);
        }
        return bridges;
    }
};

int main() {
    return 0;
}
