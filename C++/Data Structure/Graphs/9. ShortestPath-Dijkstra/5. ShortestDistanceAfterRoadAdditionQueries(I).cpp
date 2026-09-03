#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 3243 - Shortest Distance After Road Addition Queries I

    You are given an integer `n` and a 2D array `queries`. There are
    `n` cities numbered 0 to n-1. Initially, there is a unidirectional
    road from city i to city i+1 for all 0 <= i < n-1 (a straight chain).

        0 → 1 → 2 → 3 → ... → n-1

    queries[i] = [u, v] means a new unidirectional road is added from
    city u to city v. After each query, find the shortest path length
    from city 0 to city n-1.

    Return an array where answer[i] is the shortest distance from 0 to
    n-1 after the first i+1 queries have been applied.

    Examples:
    ---------

    Example 1:
        Input:  n = 5, queries = [[2,4],[0,2],[0,4]]
        Output: [3, 2, 1]
        Explanation:
            Initial: 0→1→2→3→4 (distance = 4)

            After [2,4]: 0→1→2→4 (shortcut 2→4), distance = 3
            After [0,2]: 0→2→4, distance = 2
            After [0,4]: 0→4, distance = 1

    Example 2:
        Input:  n = 4, queries = [[0,3],[0,2]]
        Output: [1, 1]
        Explanation:
            After [0,3]: 0→3 (direct), distance = 1
            After [0,2]: 0→3 still best, distance = 1

    Constraints:
    ------------
    - 3 <= n <= 500
    - 1 <= queries.length <= 500
    - queries[i].length == 2
    - 0 <= u < v < n
    - 1 < v - u (no self-loops or adjacent duplicates)
    - No repeated queries.

    Approach 1: BFS after each query
    ---------------------------------
    Since all edges have weight 1, BFS gives the shortest path.
    After each query, add the new edge and run BFS from 0 to n-1.

    Time: O(Q * (V + E)) per query. Total O(Q * (V + E)).
    With V ≤ 500, E starts at n-1 and grows by 1 each query.

    Approach 2: Dijkstra after each query
    ---------------------------------------
    Since all weights are 1, Dijkstra is overkill (BFS suffices),
    but it works correctly. Shown for comparison.

    Time: O(Q * (V + E) * log V). Slightly slower than BFS.

    Why BFS is better here:
    -----------------------
    All edges have weight 1. BFS finds shortest path in O(V + E)
    without a heap. Dijkstra adds O(log V) overhead per edge for
    no benefit. BFS is the natural choice for unweighted graphs.

    Dry Run (n=5, queries=[[2,4],[0,2],[0,4]]):
    ---------------------------------------------

    Initial graph: 0→1→2→3→4

    Query [2,4]: add edge 2→4
        Graph: 0→1, 1→2, 2→3, 3→4, 2→4
        BFS from 0: 0→1(1) →2(2) →4(3)  [via shortcut 2→4]
        Answer: 3

    Query [0,2]: add edge 0→2
        Graph: + 0→2
        BFS from 0: 0→2(1) →4(2)  [0→2 then 2→4]
        Answer: 2

    Query [0,4]: add edge 0→4
        Graph: + 0→4
        BFS from 0: 0→4(1)  [direct]
        Answer: 1

    Result: [3, 2, 1] ✓

    Complexity Analysis:
    --------------------
                BFS approach         Dijkstra approach
    Per query   O(V + E)             O((V + E) log V)
    Total       O(Q * (V + E))       O(Q * (V + E) log V)

    With V ≤ 500 and Q ≤ 500, both are fast enough.
    BFS is preferred since edges are unweighted.

*/

// =============================================================
// Approach 1: BFS after each query
// =============================================================

class Solution1 {
private:
    // Standard BFS: finds shortest path (by hops) from src to dest.
    // Works because all edges have weight 1.
    int BFS(const vector<vector<int>>& graph, int n, int src, int dest) {
        queue<int> Q;
        vector<bool> visited(n, false);
        int levels = 0;

        Q.push(src);
        visited[src] = true;

        while (!Q.empty()) {
            int levelSize = Q.size();
            // Process all nodes at the current distance (level)
            while (levelSize--) {
                int u = Q.front();
                Q.pop();

                // Found destination — current level count is the distance
                if (u == dest)
                    return levels;

                // Explore all neighbors
                for (auto v : graph[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        Q.push(v);
                    }
                }
            }
            levels++;
        }
        return -1;  // destination unreachable
    }

public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        // Build initial chain: 0→1→2→...→(n-1)
        vector<vector<int>> graph(n);
        for (int i = 0; i <= n - 2; i++)
            graph[i].push_back(i + 1);

        vector<int> shortestPaths;

        for (const auto& edge : queries) {
            int u = edge[0], v = edge[1];
            // Add the new shortcut edge
            graph[u].push_back(v);
            // Run BFS to find new shortest distance
            shortestPaths.push_back(BFS(graph, n, 0, n - 1));
        }
        return shortestPaths;
    }
};

// =============================================================
// Approach 2: Dijkstra after each query
// (overkill since weights are all 1, but shown for comparison)
// =============================================================

class Solution2 {
private:
    // Dijkstra with all edges having weight 1.
    // Works correctly but BFS is simpler and faster for this case.
    int dijkstra(const vector<vector<int>>& graph, int n, int src, int dest) {
        // Min-heap: {distance, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>,
                       greater<pair<int, int>>> Q;
        vector<int> distance(n, INT_MAX);

        Q.push({ 0, src });
        distance[src] = 0;

        while (!Q.empty()) {
            auto [d, u] = Q.top();
            Q.pop();

            // Early exit: first time we pop destination = shortest path
            if (u == dest)
                return d;

            // Skip stale entries
            if (d > distance[u]) continue;

            // Relax neighbors — weight is always 1
            for (auto v : graph[u]) {
                if (distance[v] > distance[u] + 1) {
                    distance[v] = distance[u] + 1;
                    Q.push({ distance[v], v });
                }
            }
        }
        return distance[dest];  // destination unreachable
    }

public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        // Build initial chain: 0→1→2→...→(n-1)
        vector<vector<int>> graph(n);
        for (int i = 0; i <= n - 2; i++)
            graph[i].push_back(i + 1);

        vector<int> shortestPaths;

        for (const auto& edge : queries) {
            int u = edge[0], v = edge[1];
            graph[u].push_back(v);
            shortestPaths.push_back(dijkstra(graph, n, 0, n - 1));
        }
        return shortestPaths;
    }
};

int main() {
    return 0;
}
