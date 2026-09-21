#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 743 - Network Delay Time

    You are given a network of `n` nodes, labeled 1 to n. You are given
    `times`, a list of travel times as directed edges times[i] = (u, v, w),
    where u is the source, v is the target, and w is the time it takes
    for a signal to travel from u to v.

    Send a signal from node `k`. Return the minimum time it takes for
    ALL nodes to receive the signal. If it is impossible for all nodes
    to receive the signal, return -1.

    In other words: find the shortest time to reach the FARTHEST node
    from source k. If any node is unreachable, return -1.

    Examples:
    ---------

    Example 1:
        Input:  times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
        Output: 2
        Explanation:
            From node 2:
                2→1: time 1
                2→3: time 1
                3→4: time 1 (total from 2: 1+1 = 2)
            All nodes reached. Farthest is node 4 at time 2.

    Example 2:
        Input:  times = [[1,2,1]], n = 2, k = 2
        Output: -1
        Explanation:
            From node 2, there's no edge to node 1. Node 1 unreachable.

    Example 3:
        Input:  times = [[1,2,1]], n = 2, k = 1
        Output: 1
        Explanation:
            From node 1: 1→2 takes 1. All nodes reached.

    Constraints:
    ------------
    - 1 <= k <= n <= 100
    - 1 <= times.length <= 6000
    - times[i].length == 3
    - 1 <= u, v <= n
    - u != v
    - 0 <= w <= 100
    - All pairs (u, v) are unique.
    - Nodes are 1-indexed.

    Approach: Dijkstra's Algorithm
    ------------------------------

    Intuition:
    ----------
    This is a single-source shortest path problem. We need the shortest
    time from source k to every other node. Dijkstra is the natural fit
    since all edge weights are non-negative.

    After Dijkstra, timeTaken[i] = shortest time from k to node i.
    The answer = max(timeTaken[i]) for all nodes — the signal reaches
    all nodes only when it reaches the farthest one.

    If any node has timeTaken = INF (unreachable), return -1.

    Why max and not sum?
    ---------------------
    The signal travels in parallel along all paths simultaneously
    (like a broadcast). It doesn't visit nodes sequentially. So the
    total time = time to reach the SLOWEST (farthest) node, not the
    sum of all times.

    Dry Run (times=[[2,1,1],[2,3,1],[3,4,1]], n=4, k=2):
    ------------------------------------------------------

    Graph:
        2 → {1, w=1}, {3, w=1}
        3 → {4, w=1}

    Initial: timeTaken = [_, INF, 0, INF, INF]  (index 0 unused, source=2 is 0)
    Heap: [(0, 2)]

    Pop (0, 2):
        Neighbor 1: timeTaken[1] = min(INF, 0+1) = 1, push (1, 1)
        Neighbor 3: timeTaken[3] = min(INF, 0+1) = 1, push (1, 3)
        Heap: [(1,1), (1,3)]

    Pop (1, 1):
        No neighbors.
        Heap: [(1,3)]

    Pop (1, 3):
        Neighbor 4: timeTaken[4] = min(INF, 1+1) = 2, push (2, 4)
        Heap: [(2,4)]

    Pop (2, 4):
        No neighbors.
        Heap: []

    timeTaken = [_, 1, 0, 1, 2]
    max(1, 0, 1, 2) = 2. All reachable. Answer: 2 ✓

    Complexity Analysis:
    --------------------
    Time  : O((V + E) * log V) — standard Dijkstra with a min-heap.
    Space : O(V + E) — adjacency list + timeTaken array + heap.

*/

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int S) {

        // Build directed adjacency list: node → {neighbor, weight}
        // Size n+1 because nodes are 1-indexed
        vector<vector<pair<int, int>>> graph(n + 1);
        for (const auto& time : times) {
            int u = time[0];
            int v = time[1];
            int weight = time[2];
            graph[u].push_back({ v, weight });
        }

        // Min-heap: {distance from source, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> PQ;

        // timeTaken[i] = shortest time for the signal to reach node i from S
        vector<int> timeTaken(n + 1, INT_MAX);

        // Initialize source: signal starts here at time 0
        timeTaken[S] = 0;
        PQ.push({ 0, S });

        while (!PQ.empty()) {
            auto [d, u] = PQ.top();
            PQ.pop();

            // Skip stale entries: if we already found a shorter time to u,
            // this heap entry is outdated — ignore it
            if (d > timeTaken[u]) continue;

            // Relax all neighbors of u
            for (const auto& [v, weight] : graph[u]) {
                // If reaching v through u is faster than the current best
                if (timeTaken[v] > timeTaken[u] + weight) {
                    timeTaken[v] = timeTaken[u] + weight;
                    PQ.push({ timeTaken[v], v });
                }
            }
        }

        // The answer = time to reach the FARTHEST node (signal travels in parallel).
        // If any node is unreachable (still INT_MAX), return -1.
        int minimumTime = -1;
        for (int i = 1; i <= n; i++) {
            if (timeTaken[i] == INT_MAX) return -1;  // unreachable node
            minimumTime = max(minimumTime, timeTaken[i]);
        }

        return minimumTime;
    }
};

int main() {
    return 0;
}
