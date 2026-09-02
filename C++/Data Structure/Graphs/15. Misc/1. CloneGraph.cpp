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
    LeetCode 133 - Clone Graph

    Given a reference of a node in a connected undirected graph,
    return a deep copy (clone) of the graph.

    Each node contains a val (int) and a list of its neighbors.
    The cloned graph must be a completely new set of nodes with
    the same structure and values — no shared pointers with the
    original.

    Examples:
    ---------

    Example 1:
        Input:  adjList = [[2,4],[1,3],[2,4],[1,3]]
        Output: [[2,4],[1,3],[2,4],[1,3]]
        Explanation:
            Node 1 connects to 2 and 4.
            Node 2 connects to 1 and 3.
            Node 3 connects to 2 and 4.
            Node 4 connects to 1 and 3.
            Clone has the same structure, but all new Node objects.

    Example 2:
        Input:  adjList = [[]]
        Output: [[]]
        Explanation:
            Single node with no neighbors.

    Example 3:
        Input:  adjList = []
        Output: []
        Explanation:
            Empty graph (null node).

    Constraints:
    ------------
    - Number of nodes: [0, 100]
    - 1 <= Node.val <= 100
    - Node.val is unique for each node.
    - No repeated edges, no self-loops.
    - Graph is connected (all nodes reachable from the given node).

    Approach: Parallel DFS
    ----------------------

    Intuition:
    ----------
    Walk through the original graph using DFS, and build the cloned
    graph alongside it. At every step we have two parallel nodes:
    the original `node` and its `clone`.

    For each neighbor of the original:
        - Not cloned yet → create the clone, record it in the map,
          link it to the current clone's neighbors, DFS deeper.
        - Already cloned → just link to the existing clone. Do NOT
          DFS again (it's already visited — DFS-ing would cause an
          infinite loop in cyclic graphs).

    The map (old node → cloned node) serves two purposes:
        1. Visited set — prevents infinite loops in cycles.
        2. Lookup table — retrieves the clone of any already-visited node
           so we can link to it without creating duplicates.

    Why not DFS into an already-cloned neighbor?
    ----------------------------------------------
    "Cloned already" = "visited already". If we DFS into it again,
    it would visit its neighbors again, which visit their neighbors —
    infinite loop. The DFS call that originally cloned it is either
    still on the stack (processing it) or already finished (all its
    neighbors are linked). Either way, re-entering it is wrong.

    Dry Run (adjList = [[2,4],[1,3],[2,4],[1,3]]):
    ------------------------------------------------

    cloneGraph(node1):
        Create clone1, map = {1→clone1}
        DFS(node1, clone1)

        DFS(node1, clone1):
            neighbor=node2: not in map → create clone2, map={1→c1, 2→c2}
                clone1.neighbors = [clone2]
                DFS(node2, clone2):
                    neighbor=node1: in map → clone2.neighbors = [clone1]
                    neighbor=node3: not in map → create clone3, map={.., 3→c3}
                        clone2.neighbors = [clone1, clone3]
                        DFS(node3, clone3):
                            neighbor=node2: in map → clone3.neighbors = [clone2]
                            neighbor=node4: not in map → create clone4, map={.., 4→c4}
                                clone3.neighbors = [clone2, clone4]
                                DFS(node4, clone4):
                                    neighbor=node1: in map → clone4.neighbors = [clone1]
                                    neighbor=node3: in map → clone4.neighbors = [clone1, clone3]

            neighbor=node4: in map → clone1.neighbors = [clone2, clone4]

    Result: all 4 cloned nodes, same neighbor structure ✓

    Complexity Analysis:
    --------------------
    Time  : O(V + E) — visit each node once, each edge once.
    Space : O(V)     — map stores V entries + recursion stack up to V deep.

*/

struct Node {
    int val;
    vector<Node*> neighbors;
    Node(int _val) : val(_val) {
        neighbors.clear();
    }
};

class Solution {
private:
    // Maps each original node to its clone.
    // Acts as both a visited set and a lookup table.
    unordered_map<Node*, Node*> mapping;

    // DFS with two parallel nodes: original `node` and its `clone`.
    // Builds the cloned graph by walking the original graph.
    void DFS(Node* node, Node* clone, unordered_map<Node*, Node*>& mapping) {
        if (node == nullptr)
            return;

        // Visit each neighbor of the original node
        for (auto neighbor : node->neighbors) {
            if (mapping.count(neighbor) == 0) {
                
                Node* neighborClone = new Node(neighbor->val);  // Neighbor hasn't been cloned yet — clone it
                mapping[neighbor] = neighborClone;  // Record in map (marks it as visited + stores the clone)
                clone->neighbors.push_back(neighborClone);  // Link: add the cloned neighbor to clone's neighbor list
                DFS(neighbor, neighborClone, mapping);  // DFS deeper: walk into the neighbor and its clone in parallel
            }
            else {
                // Neighbor already cloned — just link to the existing clone.
                // Do NOT DFS again (already visited → would cause infinite loop).
                Node* neighborClone = mapping[neighbor];
                clone->neighbors.push_back(neighborClone);
            }
        }
    }

public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr) return node;

        // Create the clone of the starting node
        Node* clone = new Node(node->val);
        // Register it in the map before DFS (so if a cycle leads back
        // to this node, we find it in the map and don't re-clone it)
        mapping[node] = clone;

        // Build the rest of the cloned graph via DFS
        DFS(node, clone, mapping);

        return clone;
    }
};
