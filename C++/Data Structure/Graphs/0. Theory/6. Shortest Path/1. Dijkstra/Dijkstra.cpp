#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <set>
using namespace std;

/*
*       https://www.youtube.com/watch?v=V6H1qAeB-l4
*       https://www.youtube.com/watch?v=PATgNiuTP20
*       https://www.youtube.com/watch?v=3dINsjyfooY
*       https://www.youtube.com/watch?v=XB4MIexjvY0
        Dijkstra's Algorithm:
        ---------------------
        Greedy shortest path algorithm for graphs with NON-NEGATIVE edge weights.
        Core invariant: always process the vertex with the smallest known distance next.
        Once a vertex is processed, its distance is FINAL and will never be updated again.
        This is guaranteed because all edge weights are non-negative — no future path
        through an unprocessed vertex can produce a shorter distance to an already-processed vertex.

        Why Set is better than Priority Queue:
        --------------------------------------
        Both give O(log N) min extraction. The difference is in how they handle UPDATES.

        When a shorter path to vertex V is found, dist[V] is updated.
        The old (larger) distance entry for V is now stale and needs to be discarded.

        Priority Queue (dijkstra3):
          Cannot remove or update an existing entry.
          So we just push the new (smaller dist, V) entry and leave the old one in.
          The PQ can contain the same vertex MULTIPLE TIMES with different distances.
          We handle stale entries lazily with: if (current_dist > dist[u]) continue;

          Example graph:

              A ---5--- B
               \       ^
                1\     /2
                  v   /
                   C

            Push (0,A). Process A => push (5,B) and (1,C).
            PQ = [(1,C), (5,B)]
            Process C => dist[B] updated to 3, push (3,B).
            PQ = [(3,B), (5,B)]   <-- B appears TWICE
            Process (3,B) => finalize B.
            Process (5,B) => 5 > dist[B]=3, SKIP (stale entry wasted space)

        Set (dijkstra4):
          set<pair<int,int>> is ordered by (dist, vertex) and supports O(log N) erase.
          When dist[V] is updated, we ERASE the old (dist, V) entry and INSERT the new one.
          The set always contains each vertex AT MOST ONCE.
          No stale entries, no wasted processing.

          Same example graph:

              A ---5--- B
               \       ^
                1\     /2
                  v   /
                   C

            Insert (0,A). Process A => insert (5,B) and (1,C).
            Set = [(1,C), (5,B)]
            Process C => erase old (5,B), insert new (3,B).
            Set = [(3,B)]         <-- B appears only ONCE, old entry gone
            Process (3,B) => finalize B. Done.

        Time Complexity Derivation for PQ (dijkstra3):
        -------------------------------------------------
          Let V = vertices, E = edges.

          pq.push() calls:
            Every edge relaxation triggers a push. Each of the E edges can cause
            at most one push per relaxation => at most E pushes total.
            => PQ size is bounded by O(E).

          pq.pop() calls:
            We pop every entry ever pushed, including stale duplicates.
            => at most E pops total.

          Cost per push/pop:
            PQ of size O(E) => each push/pop costs O(log E).
            Since E <= V^2, log E <= 2*log V => O(log E) = O(log V).

          Inner for-loop (neighbor iteration):
            Each vertex is FINALIZED once (stale pops are skipped via continue).
            When finalized, we scan its adjacency list.
            Summed across all vertices => O(E) total neighbor work.

          Total:
            E pops  * O(log V) = O(E log V)
            E pushes * O(log V) = O(E log V)
            Neighbor scan       = O(E)
            => O(E log V), written as O((V+E) log V) to account for V initial pushes.

        Summary:
          PQ:  O((V+E) log V) time, O(E) space (duplicate entries)
          Set: O((V+E) log V) time, O(V) space (no duplicates)
          Set is preferred when memory is a concern or E >> V (dense graphs).

        Graph used in main() (A=0, B=1, C=2, D=3):

              A ---1--- B
              |       / |
              5      1  3
              |     /   |
              C <--     D
               \       /
                2-----

          Edges: A-B:1, A-C:5, B-C:1, B-D:3, C-D:2
          Shortest paths from A: A=0, B=1, C=2, D=4


*/

class Solution {
public:
    // Queue: Correct but processing too many times.
    vector<int> dijkstra1(int V, vector<vector<int>>& edges, int src) {
        vector<vector<pair<int, int>>> adj(V);
        for (const auto& e : edges) {
            if (e.size() < 3) continue;
            int u = e[0], v = e[1], w = e[2];
            adj[u].push_back({ v, w });
            adj[v].push_back({ u, w }); // remove if graph is directed
        }

        vector<int> dist(V, INT_MAX);
        queue<int> Q;

        dist[src] = 0;
        Q.push(src);

        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();

            for (auto neighbour : adj[u]) {
                int v = neighbour.first;
                int weight = neighbour.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    Q.push(v);
                }
            }
        }
        return dist;
    }

    // Queue + min dist edge extraction
    vector<int> dijkstra2(int V, vector<vector<int>>& edges, int src) {
        vector<vector<pair<int, int>>> adj(V);
        for (const auto& e : edges) {
            if (e.size() < 3) continue;
            int u = e[0], v = e[1], w = e[2];
            adj[u].push_back({ v, w });
            adj[v].push_back({ u, w }); // remove if graph is directed
        }

        vector<int> dist(V, INT_MAX);
        queue<int> Q;

        dist[src] = 0;
        Q.push(src);

        while (!Q.empty()) {
            // Find min in queue (inefficient but necessary)
            int u = -1;
            int min_dist = INT_MAX;

            queue<int> temp = Q;
            while (!temp.empty()) {
                int v = temp.front();
                temp.pop();
                if (dist[v] < min_dist) {
                    min_dist = dist[v];
                    u = v;
                }
            }

            if (u == -1) break;

            for (auto neighbour : adj[u]) {
                int v = neighbour.first;
                int weight = neighbour.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    Q.push(v);
                }
            }
        }
        return dist;
    }

    // Priority Queue : Can contain the vertex multiple times in the queue.
    vector<int> dijkstra3(int V, vector<vector<int>>& edges, int src) {
        vector<vector<pair<int, int>>> adj(V);
        for (const auto& e : edges) {
            if (e.size() < 3) continue;
            int u = e[0], v = e[1], w = e[2];
            adj[u].push_back({ v, w });
            adj[v].push_back({ u, w }); // remove if graph is directed
        }
        vector<int> dist(V, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[src] = 0;
        pq.push({ 0, src });

        while (!pq.empty()) {
            int u = pq.top().second;
            int current_dist = pq.top().first;
            pq.pop();

            // OPTIMIZATION: Skip outdated entries
            if (current_dist > dist[u]) {
                continue;
            }

            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({ dist[v], v });
                }
            }
        }

        return dist;
    }

    // Set : Will contain the vertex only once in the set.
    vector<int> dijkstra4(int V, vector<vector<int>>& edges, int src) {
        vector<vector<pair<int, int>>> adj(V);
        for (const auto& e : edges) {
            if (e.size() < 3)
                continue;
            int u = e[0], v = e[1], w = e[2];
            adj[u].push_back({ v, w });
            adj[v].push_back({ u, w }); // remove if graph is directed
        }

        vector<int> dist(V, INT_MAX);
        set<pair<int, int>> s;

        dist[src] = 0;
        s.insert({ 0, src });

        while (!s.empty()) {
            auto it = s.begin();
            int u = it->second;
            int current_dist = it->first;
            s.erase(it);

            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (dist[u] + weight < dist[v]) {
                    // erase old entry before updating
                    if (dist[v] != INT_MAX) {
                        s.erase({ dist[v], v });
                    }
                    dist[v] = dist[u] + weight;
                    s.insert({ dist[v], v });
                }
            }
        }

        return dist;
    }
};

int main() {

    return 0;
}