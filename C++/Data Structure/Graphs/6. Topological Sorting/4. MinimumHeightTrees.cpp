#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;

/*
    https://www.youtube.com/watch?v=ivl6BHJVcB0
    https://www.youtube.com/watch?v=ZXANlaEuYvQ

    Problem Statement:
    ------------------
    LeetCode 310 - Minimum Height Trees

    A tree is an undirected graph in which any two vertices are connected
    by exactly one path. Any node of the tree can be chosen as the root.
    When a node `r` is chosen as root, the height of the resulting rooted
    tree is the number of edges on the longest path from `r` to a leaf.

    Given a tree of `n` nodes labeled 0 to n-1, and an array `edges`
    where edges[i] = [a, b] is an undirected edge, find all nodes that
    give the minimum height when chosen as root. Return them in any order.

    These are called Minimum Height Tree (MHT) roots.

    Examples:
    ---------

    Example 1:
        Input:  n = 4, edges = [[1,0],[1,2],[1,3]]
        Output: [1]
        Explanation:
            Tree:   0
                    |
                    1
                   / \
                  2   3

            Root=0: height=2 (0→1→2 or 0→1→3)
            Root=1: height=1 (1→0, 1→2, 1→3)     ← minimum
            Root=2: height=2
            Root=3: height=2

    Example 2:
        Input:  n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
        Output: [3, 4]
        Explanation:
            Tree:   0   1   2
                     \  |  /
                       3
                       |
                       4
                       |
                       5

            Root=3: height=2 (3→4→5)
            Root=4: height=2 (4→3→0, 4→3→1, 4→3→2)
            Both give height 2 — minimum. All others give height 3.

    Example 3:
        Input:  n = 1, edges = []
        Output: [0]
        Explanation:
            Single node. It's the only possible root. Height = 0.

    Constraints:
    ------------
    - 1 <= n <= 2 * 10^4
    - edges.length == n - 1
    - 0 <= a, b < n
    - a != b
    - All pairs (a, b) are distinct.
    - The given input is guaranteed to be a tree.

    Approach: Leaf Peeling (Topological Sort on an Undirected Tree)
    ---------------------------------------------------------------

    Intuition:
    ----------
    Which node gives the minimum height? The one that's most "central"
    in the tree — farthest from all leaves. Think of it like finding
    the center of a rope: the midpoint minimizes the maximum distance
    to either end.

    Brute force would try every node as root and compute the height
    via BFS/DFS. That's O(n^2). Can we do better?

    Key Insight — Peel leaves from the outside in:
    -----------------------------------------------
    A leaf (degree 1 node) is the worst root choice — it's at the
    edge of the tree, giving maximum height. So we can safely
    eliminate all leaves. After removing them, some inner nodes
    become new leaves. We remove those too. We keep peeling until
    1 or 2 nodes remain.

    Why at most 2 nodes remain?
    ----------------------------
    A tree has either:
        - 1 center node (odd-length longest path): like the middle
          bead on a string of beads.
        - 2 center nodes (even-length longest path): like the two
          middle beads.

    It can never have 3+ center nodes. If it did, two of them would
    be adjacent, and one of them would be farther from some leaf —
    contradicting that both are centers.

    Connection to topological sort:
    --------------------------------
    In topo sort on a DAG, we peel nodes with indegree 0.
    Here, we peel nodes with degree 1 (leaves) from an undirected tree.
    Same "peel from the outside" idea — different context.

    The difference: in topo sort we process till the queue is empty.
    Here we STOP when <= 2 nodes remain.

    Algorithm:
    ----------
    1. Build the adjacency list and compute degrees.
    2. Add all leaves (degree == 1) to the queue.
    3. Track `remaining` = number of unpeeled nodes.
    4. While remaining > 2:
        a. Subtract the current layer size from remaining.
        b. Process current level (all current leaves).
        c. For each leaf, decrement its neighbors' degrees.
        d. If a neighbor's degree drops to 1, it's a new leaf — enqueue.
    5. Remaining nodes in the queue are the MHT roots.

    Why track `remaining` instead of checking Q.size() <= 2?
    ---------------------------------------------------------
    If the initial leaves already fill the queue with <= 2 nodes
    (e.g., tree 1—0—2 has leaves {1,2}), checking Q.size() would
    break immediately and return the LEAVES as roots — wrong!
    Tracking `remaining` ensures we peel those leaves first and
    let the center node(s) emerge.

    Dry Run (n=6, edges=[[3,0],[3,1],[3,2],[3,4],[5,4]]):
    ------------------------------------------------------

    Graph:
        0 — 3,  1 — 3,  2 — 3,  3 — 4,  4 — 5

    Degrees: 0:1  1:1  2:1  3:4  4:2  5:1

    Leaves (degree 1): {0, 1, 2, 5}
    Queue = [0, 1, 2, 5], remaining = 6

    remaining (6) > 2, continue
    remaining = 6 - 4 = 2

    Level 1: peel 0, 1, 2, 5
        Remove 0: neighbor 3, degree[3] = 4→3
        Remove 1: neighbor 3, degree[3] = 3→2
        Remove 2: neighbor 3, degree[3] = 2→1 → new leaf, push 3
        Remove 5: neighbor 4, degree[4] = 2→1 → new leaf, push 4
        Queue = [3, 4]

    remaining (2) <= 2, STOP.

    Answer: [3, 4] ✓

    Edge case dry run (n=3, edges=[[0,1],[0,2]]):
    -----------------------------------------------

    Tree: 1 — 0 — 2

    Degrees: 0:2  1:1  2:1

    Leaves: {1, 2}
    Queue = [1, 2], remaining = 3

    remaining (3) > 2, continue
    remaining = 3 - 2 = 1

    Level 1: peel 1, 2
        Remove 1: neighbor 0, degree[0] = 2→1 → push 0
        Remove 2: neighbor 0, degree[0] = 1→0
        Queue = [0]

    remaining (1) <= 2, STOP.

    Answer: [0] ✓
    (Without `remaining`, Q.size()=2 at the start would wrongly
     return [1,2])

    Complexity Analysis:
    --------------------
    Time  : O(n) — each node is processed (pushed and popped) at most once.
    Space : O(n) — adjacency list + degree array + queue.

*/

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        // Edge case: single node is the only root
        if (n == 1) return { 0 };

        // STEP 1: Build adjacency list and compute degrees.
        // Using unordered_set for O(1) neighbor removal (optional).
        unordered_map<int, unordered_set<int>> graph;
        // degree[i] = number of edges connected to node i
        // (in undirected graph, "indegree" and "outdegree" don't apply
        //  — we just call it "degree")
        vector<int> degree(n, 0);

        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            graph[u].insert(v);
            graph[v].insert(u);
            degree[u]++;
            degree[v]++;
        }

        // STEP 2: Add all leaf nodes (degree == 1) to the queue.
        // Leaves are the outermost nodes — worst root candidates.
        queue<int> Q;
        for (int i = 0; i < n; i++) {
            if (degree[i] == 1)
                Q.push(i);
        }

        // STEP 3: Peel leaves layer by layer until <= 2 nodes remain.
        // We track remaining node count instead of checking Q.size(),
        // because initial leaves might already have Q.size() <= 2
        // but they're NOT the roots (they're the outermost nodes).
        int remaining = n;

        while (!Q.empty()) {
            // The remaining nodes are the MHT roots
            // DONT: Q.size() <= 2.  Test Case: (0,1),(0,2) -> here 1 and 2 are leaves but 0 should be the root.
            if (remaining <= 2) break;

            // Remove this entire layer of leaves from the count
            int levelSize = Q.size();
            remaining -= levelSize;

            // Process all leaves at the current layer
            while (levelSize--) {
                int leaf = Q.front();
                Q.pop();

                // Remove this leaf from its neighbors' adjacency
                for (auto v : graph[leaf]) {
                    degree[v]--;

                    // If neighbor's degree dropped to 1, it became a new leaf
                    if (degree[v] == 1) {
                        Q.push(v);
                    }
                }
            }
        }

        // STEP 4: Collect the remaining nodes — these are the MHT roots.
        vector<int> roots;
        while (!Q.empty()) {
            roots.push_back(Q.front());
            Q.pop();
        }

        return roots;
    }
};

int main() {
    Solution obj;
}
