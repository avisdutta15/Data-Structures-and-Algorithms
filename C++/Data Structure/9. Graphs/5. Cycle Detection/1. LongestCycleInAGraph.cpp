#include <iostream>
#include <queue>
#include <deque>
#include <vector>
#include <climits>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/*
    https://www.youtube.com/watch?v=m6cp4eHWLak
    Problem Statement:
    ------------------
    LeetCode 2360 - Longest Cycle in a Graph

    You are given a directed graph of n nodes numbered from 0 to n-1,
    where each node has at most one outgoing edge.
    edges[i] = next node from i, or -1 if no outgoing edge.
    Return the length of the longest cycle, or -1 if no cycle exists.

    Examples:
    ---------
    Example 1:
        Input:  edges = [3,3,4,2,3]
        Output: 3
        Explanation: cycle 3→2→4→3, length = 3

    Example 2:
        Input:  edges = [2,-1,3,1]
        Output: -1

    Constraints:
    ------------
    - 1 <= n <= 10^5
    - -1 <= edges[i] < n
    - Each node has at most one outgoing edge (functional graph)

    Intuition:
    ----------
    - This is a functional graph (out-degree ≤ 1).
    - Use DFS with three arrays:
        visited[u]     — globally processed, never revisit
        inRecursion[u] — currently on the DFS path (recursion stack)
        label[u]       — depth (distance from path's starting node) when we entered u

    - When we encounter a node v that is inRecursion:
        → v is on the current DFS path → cycle found
        → cycle length = currentLabel - label[v] + 1

    Example trace:
        edges = [3,3,4,2,3]
        DFS from 0:
          0 (label=1) → 3 (label=2) → 2 (label=3) → 4 (label=4) → 3 (inRecursion!)
          cycle length = 4 - 2 + 1 = 3  (nodes: 3→2→4→back to 3)

    Time:  O(V + E) — each node visited at most once
    Space: O(V)
*/

class Solution {
private:
    int maxCycleLength = -1;                       // -1 if no cycle found

    void dfs(vector<vector<int>> &graph, int u, vector<bool> &visited,
             vector<int> &label, vector<bool> &inRecursion, int currentLabel) {
        visited[u] = true;
        label[u] = currentLabel;                   // record depth when entering this node
        inRecursion[u] = true;                     // mark on current DFS path

        for (auto v : graph[u]) {
            if (!visited[v]) {
                // TREE EDGE: v is unvisited → continue DFS deeper
                dfs(graph, v, visited, label, inRecursion, currentLabel + 1);
            }
            else if (inRecursion[v]) {
                // BACK EDGE: v is on the current path → cycle found
                // cycle length = my depth - its depth + 1
                int cycleLength = currentLabel - label[v] + 1;
                maxCycleLength = max(maxCycleLength, cycleLength);
            }
            // else: v is visited but not on current path → cross edge, ignore
        }

        inRecursion[u] = false;                    // backtrack: remove from current path
    }

public:
    int longestCycle(vector<int>& edges) {
        int n = edges.size();
        vector<vector<int>> graph(n, vector<int>());

        // build adjacency list from edges array
        for (int i = 0; i < n; i++) {
            int u = i;
            int v = edges[i];
            if (v != -1) {
                graph[u].push_back(v);             // directed edge u → v
            }
        }

        vector<bool> visited(n, false);
        vector<int> label(n, 0);
        vector<bool> inRecursion(n, false);

        // try DFS from every unvisited node (graph may be disconnected)
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(graph, i, visited, label, inRecursion, 1);
            }
        }
        return maxCycleLength;
    }
};

int main() {
    return 0;
}
