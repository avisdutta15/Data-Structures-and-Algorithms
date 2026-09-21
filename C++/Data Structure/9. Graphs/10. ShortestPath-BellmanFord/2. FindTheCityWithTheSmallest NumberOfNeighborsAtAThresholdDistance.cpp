#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 1334 - Find the City With the Smallest Number of
    Neighbors at a Threshold Distance

    There are `n` cities numbered 0 to n-1. You are given an array
    `edges` where edges[i] = [u, v, weight] is a bidirectional weighted
    edge between cities u and v, and an integer `distanceThreshold`.

    Return the city with the smallest number of cities that are
    reachable through some path whose total distance is at most
    `distanceThreshold`. If there are multiple such cities, return
    the one with the greatest number.

    Examples:
    ---------

    Example 1:
        Input:  n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]],
                distanceThreshold = 4
        Output: 3
        Explanation:
            Reachable cities within distance 4:
                City 0: {1(3), 2(4)}         → 2 neighbors
                City 1: {0(3), 2(1), 3(2)}   → 3 neighbors
                City 2: {1(1), 3(1), 0(4)}   → 3 neighbors
                City 3: {1(2), 2(1)}         → 2 neighbors
            Cities 0 and 3 both have 2 neighbors. Return 3 (greatest number).

    Example 2:
        Input:  n = 5, edges = [[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]],
                distanceThreshold = 2
        Output: 0
        Explanation:
            City 0: {1(2)}     → 1 neighbor
            City 1: {0(2)}     → 1 neighbor  (2,4 are distance 3+)
            City 2: {3(1)}     → 1 neighbor
            City 3: {2(1),4(1)}→ 2 neighbors
            City 4: {3(1)}     → 1 neighbor
            Cities 0, 1, 2, 4 all have 1 neighbor. Return 4 (greatest number).

    Constraints:
    ------------
    - 2 <= n <= 100
    - 1 <= edges.length <= n*(n-1)/2
    - edges[i].length == 3
    - 0 <= u, v < n
    - 1 <= weight, distanceThreshold <= 10^4
    - No duplicate edges, no self-loops.
    - Graph is connected.

    Why do we need all-pairs shortest paths?
    -----------------------------------------
    For each city, we need to count how many OTHER cities are within
    the threshold distance. This requires knowing the shortest distance
    from every city to every other city — an all-pairs problem.

    Three approaches:
        1. Dijkstra from each node   → O(V * (V+E) log V)
        2. Bellman-Ford from each node → O(V^2 * E)
        3. Floyd-Warshall             → O(V^3)

    With V ≤ 100, all three are fast enough. Floyd-Warshall is the
    simplest to code for all-pairs.

    The Shortest Path Matrix:
    -------------------------
    All three approaches produce the same result: a 2D matrix where
    shortestPathMatrix[i][j] = shortest distance from city i to city j.

    For Example 1 (n=4, edges=[[0,1,3],[1,2,1],[1,3,4],[2,3,1]]):

                     to
                  0    1    2    3
             0 [  0    3    4    5  ]
    from     1 [  3    0    1    2  ]
             2 [  4    1    0    1  ]
             3 [  5    2    1    0  ]

    Each ROW is the shortest distances from that city to all others.

    How Dijkstra / Bellman-Ford fills the matrix:
    -----------------------------------------------
    They compute single-source shortest paths, so we run them V times
    (once per source). The trick: shortestPathMatrix[v] gives row v,
    which is a vector<int> of size n. We pass this row directly as
    the distance array.

        // Create the matrix — all INF except diagonal
        vector<vector<int>> shortestPathMatrix(n, vector<int>(n, INT_MAX));
        for (int i = 0; i < n; i++)
            shortestPathMatrix[i][i] = 0;

        // Run Dijkstra from each node, passing its row
        for (int v = 0; v < n; v++)
            dijkstra(v, graph, shortestPathMatrix[v]);
            //                 ^^^^^^^^^^^^^^^^^^^^
            //                 Row v — Dijkstra writes directly into it

    After dijkstra(0, ...):
        [ 0,   3,   4,   5   ]    ← row 0 filled
        [ INF, 0,   INF, INF ]
        [ INF, INF, 0,   INF ]
        [ INF, INF, INF, 0   ]

    After dijkstra(1, ...):
        [ 0,   3,   4,   5   ]
        [ 3,   0,   1,   2   ]    ← row 1 filled
        [ INF, INF, 0,   INF ]
        [ INF, INF, INF, 0   ]

    After all four runs:
        [ 0,   3,   4,   5   ]
        [ 3,   0,   1,   2   ]
        [ 4,   1,   0,   1   ]
        [ 5,   2,   1,   0   ]

    Since shortestPathMatrix[v] is passed by reference (vector<int>&),
    Dijkstra/Bellman-Ford writes directly into the matrix row. No
    copying needed.

    Floyd-Warshall is different — it works on the entire 2D matrix
    at once (all pairs simultaneously) via the triple loop. No
    per-source calls needed.

    Common helper — finding the answer:
    ------------------------------------
    After computing the shortest path matrix, iterate over each city,
    count how many other cities are within threshold, and pick the city
    with the fewest reachable neighbors (ties broken by greatest index).

*/

// =============================================================
// Approach 1: Dijkstra from Each Node
// Time:  O(V * (V + E) * log V)
// Space: O(V^2) for the shortest path matrix + O(V + E) for graph
// =============================================================

class Solution1 {
private:
    // Standard Dijkstra: finds shortest distances from source S to all nodes
    void dijkstra(const int& S, const vector<vector<pair<int, int>>>& graph,
                  vector<int>& distance) {
        // Min-heap: {distance from S, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>,
                       greater<pair<int, int>>> PQ;

        distance[S] = 0;
        PQ.push({0, S});

        while (!PQ.empty()) {
            auto [currentDist, u] = PQ.top();
            PQ.pop();

            // Skip stale entries — we already found a shorter path to u
            if (currentDist > distance[u])
                continue;

            // Relax all neighbors of u
            for (auto& [v, weight] : graph[u]) {
                if (distance[v] > distance[u] + weight) {
                    distance[v] = distance[u] + weight;
                    PQ.push({distance[v], v});
                }
            }
        }
    }

    // Count reachable cities for each city, return the one with fewest
    int filterVerticesOnThresholdAndFindCity(
        const int& n, const vector<vector<int>>& shortestPathMatrix,
        const int& distanceThreshold) {

        int cityWithFewestReachable = -1;
        int fewestReachableCount = INT_MAX;

        for (int city = 0; city < n; city++) {
            int reachableCities = 0;

            for (int otherCity = 0; otherCity < n; otherCity++) {
                // Skip self, count if within threshold
                if (city != otherCity
                    && shortestPathMatrix[city][otherCity] <= distanceThreshold)
                    reachableCities++;
            }

            // <= ensures we pick the greatest-numbered city on tie
            if (reachableCities <= fewestReachableCount) {
                fewestReachableCount = reachableCities;
                cityWithFewestReachable = city;
            }
        }
        return cityWithFewestReachable;
    }

public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        // Build adjacency list: u → {v, weight}
        vector<vector<pair<int, int>>> graph(n);
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], weight = edge[2];
            // Undirected graph → add both directions
            graph[u].push_back({v, weight});
            graph[v].push_back({u, weight});
        }

        // Compute all-pairs shortest paths by running Dijkstra from each node
        vector<vector<int>> shortestPathMatrix(n, vector<int>(n, INT_MAX));
        for (int i = 0; i < n; i++) {
            shortestPathMatrix[i][i] = 0;
        }

        for (int v = 0; v < n; v++) {
            dijkstra(v, graph, shortestPathMatrix[v]);
        }

        return filterVerticesOnThresholdAndFindCity(n, shortestPathMatrix,
                                                     distanceThreshold);
    }
};

// =============================================================
// Approach 2: Bellman-Ford from Each Node
// Time:  O(V^2 * E) — V runs of Bellman-Ford, each O(V * E)
// Space: O(V^2) for the shortest path matrix
// =============================================================

class Solution2 {
private:
    // Bellman-Ford: handles negative weights (not needed here, but shown
    // for completeness). For undirected graphs, relax both directions.
    void bellman_ford(int V, const int& S, const vector<vector<int>>& edges,
                      vector<int>& distance) {
        distance[S] = 0;

        // Relax all edges V-1 times
        for (int i = 1; i <= V - 1; i++) {
            for (const auto& edge : edges) {
                int u = edge[0], v = edge[1], weight = edge[2];

                // Relax u → v
                if (distance[u] != INT_MAX && distance[v] > distance[u] + weight)
                    distance[v] = distance[u] + weight;

                // Relax v → u (undirected graph)
                if (distance[v] != INT_MAX && distance[u] > distance[v] + weight)
                    distance[u] = distance[v] + weight;
            }
        }
    }

    int filterVerticesOnThresholdAndFindCity(
        const int& n, const vector<vector<int>>& shortestPathMatrix,
        const int& distanceThreshold) {

        int cityWithFewestReachable = -1;
        int fewestReachableCount = INT_MAX;

        for (int city = 0; city < n; city++) {
            int reachableCities = 0;
            for (int otherCity = 0; otherCity < n; otherCity++) {
                if (city != otherCity
                    && shortestPathMatrix[city][otherCity] <= distanceThreshold)
                    reachableCities++;
            }
            if (reachableCities <= fewestReachableCount) {
                fewestReachableCount = reachableCities;
                cityWithFewestReachable = city;
            }
        }
        return cityWithFewestReachable;
    }

public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        // Compute all-pairs shortest paths: run Bellman-Ford from each node
        vector<vector<int>> shortestPathMatrix(n, vector<int>(n, INT_MAX));
        for (int i = 0; i < n; i++) {
            shortestPathMatrix[i][i] = 0;
        }

        for (int v = 0; v < n; v++) {
            bellman_ford(n, v, edges, shortestPathMatrix[v]);
        }

        return filterVerticesOnThresholdAndFindCity(n, shortestPathMatrix,
                                                     distanceThreshold);
    }
};

// =============================================================
// Approach 3: Floyd-Warshall (simplest for all-pairs)
// Time:  O(V^3)
// Space: O(V^2) for the distance matrix
// =============================================================

class Solution3 {
private:
    int filterVerticesOnThresholdAndFindCity(
        const int& n, const vector<vector<int>>& dist,
        const int& distanceThreshold) {

        int cityWithFewestReachable = -1;
        int fewestReachableCount = INT_MAX;

        for (int city = 0; city < n; city++) {
            int reachableCities = 0;
            for (int otherCity = 0; otherCity < n; otherCity++) {
                if (city != otherCity
                    && dist[city][otherCity] <= distanceThreshold)
                    reachableCities++;
            }
            if (reachableCities <= fewestReachableCount) {
                fewestReachableCount = reachableCities;
                cityWithFewestReachable = city;
            }
        }
        return cityWithFewestReachable;
    }

public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        // STEP 1: Initialize the distance matrix.
        // dist[i][j] = weight of direct edge, or INT_MAX if no edge.
        vector<vector<int>> distance(n, vector<int>(n, INT_MAX));
        for (int i = 0; i < n; i++)
            distance[i][i] = 0;  // distance to self is 0

        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], weight = edge[2];
            distance[u][v] = weight;
            distance[v][u] = weight;  // undirected graph
        }

        // STEP 2: Floyd-Warshall — try every node k as intermediate.
        // After this, distance[i][j] = shortest path from i to j.
        for (int k = 0; k < n; k++) {          // intermediate node
            for (int i = 0; i < n; i++) {       // source
                for (int j = 0; j < n; j++) {   // destination
                    // Guard against INT_MAX overflow
                    if (distance[i][k] != INT_MAX && distance[k][j] != INT_MAX) {
                        // Is going through k shorter than the current best?
                        if (distance[i][j] > distance[i][k] + distance[k][j])
                            distance[i][j] = distance[i][k] + distance[k][j];
                    }
                }
            }
        }

        // STEP 3: Find the city with fewest reachable neighbors within threshold.
        return filterVerticesOnThresholdAndFindCity(n, distance, distanceThreshold);
    }
};

/*
    Complexity Comparison:
    ----------------------
                        Dijkstra × V          Bellman-Ford × V      Floyd-Warshall
    Time              O(V*(V+E)*log V)       O(V^2 * E)            O(V^3)
    Space             O(V^2 + V + E)         O(V^2)                O(V^2)
    Negative weights  No                     Yes                   Yes
    Code complexity   Medium                 Simple                Simplest

    For this problem (V ≤ 100, no negative weights):
    - All three work. Floyd-Warshall is the simplest to write.
    - On dense graphs (E ≈ V^2), Floyd-Warshall beats Dijkstra × V
      because Dijkstra × V becomes O(V^3 * log V).
    - On sparse graphs, Dijkstra × V is faster.
*/

int main() {
    Solution3 obj;
}
