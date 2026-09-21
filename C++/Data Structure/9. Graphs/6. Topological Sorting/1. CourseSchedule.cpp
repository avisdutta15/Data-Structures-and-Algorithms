#include <iostream> 
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 207 - Course Schedule

    There are a total of `numCourses` courses you have to take, labeled
    from 0 to numCourses - 1. You are given an array `prerequisites`
    where prerequisites[i] = [a, b] means you must take course b BEFORE
    you can take course a.

    Return true if you can finish all courses. Otherwise, return false.

    Examples:
    ---------

    Example 1:
        Input:  numCourses = 2, prerequisites = [[1, 0]]
        Output: true
        Explanation:
            You must take course 0 before course 1.
            Order: 0 → 1. Possible.

    Example 2:
        Input:  numCourses = 2, prerequisites = [[1, 0], [0, 1]]
        Output: false
        Explanation:
            Course 0 requires course 1, and course 1 requires course 0.
            Circular dependency — impossible.

    Example 3:
        Input:  numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
        Output: true
        Explanation:
            0 → 1 → 3
            0 → 2 → 3
            One valid order: 0, 1, 2, 3  (or 0, 2, 1, 3)

    Constraints:
    ------------
    - 1 <= numCourses <= 2000
    - 0 <= prerequisites.length <= 5000
    - prerequisites[i].length == 2
    - 0 <= a, b < numCourses
    - All prerequisite pairs are unique.

    Approach: Topological Sort using BFS (Kahn's Algorithm)
    -------------------------------------------------------

    Intuition — what is this problem really asking?
    ------------------------------------------------
    Each course is a NODE. Each prerequisite [a, b] is a directed EDGE
    from b → a (b must come before a). We now have a directed graph.

    The question becomes: can we find an ordering of all nodes such that
    for every edge b → a, b comes before a?

    This is a TOPOLOGICAL ORDER. It exists if and only if the graph
    has NO CYCLES.

    Why? If there's a cycle (A needs B, B needs C, C needs A), there's
    no valid starting point — every course in the cycle is waiting for
    another. If there's no cycle, we can always find some course with
    no prerequisites, take it first, remove it, and repeat.

    What is "indegree"?
    --------------------
    The indegree of a node = number of edges pointing INTO it
                           = number of prerequisites that course has.

    A course with indegree 0 has no prerequisites — we can take it
    right away. That's our starting point.

    Kahn's Algorithm — step by step:
    ---------------------------------

    STEP 1: Build the graph.
        For each [a, b] in prerequisites, add edge b → a.
        Count the indegree of each node.

    STEP 2: Initialize the queue.
        Add all nodes with indegree 0 to a queue.
        These are courses with no prerequisites — "ready to take".

    STEP 3: Process the queue (BFS).
        While the queue is not empty:
            a) Pop a course from the queue. This course is "taken".
            b) For each neighbor (course that depends on this one):
               - Decrease its indegree by 1 (one less prerequisite
                 to worry about).
               - If its indegree drops to 0, add it to the queue
                 (all its prerequisites are now fulfilled).

    STEP 4: Check the result.
        If visited.size() == numCourses → all courses finished → true.
        If visited.size() < numCourses → some courses are stuck in a
        cycle (their indegree never reached 0) → false.

    Why does this detect cycles?
    ----------------------------
    If there's a cycle, every node in the cycle has at least one edge
    coming from another node in the cycle. So none of them ever reaches
    indegree 0. They never enter the queue. They're never visited.
    So visited.size() < numCourses.

    Dry Run (numCourses=4, prerequisites=[[1,0],[2,0],[3,1],[3,2]]):
    ----------------------------------------------------------------

    Graph (adjacency list):
        0 → {1, 2}
        1 → {3}
        2 → {3}
        3 → {}

    Indegree:
        0: 0    1: 1    2: 1    3: 2

    STEP 2: Queue = [0], visited = {0}

    STEP 3:
        Pop 0
            Neighbor 1: indegree 1→0, add to queue.  Queue=[1], visited={0,1}
            Neighbor 2: indegree 1→0, add to queue.  Queue=[1,2], visited={0,1,2}

        Pop 1
            Neighbor 3: indegree 2→1, not 0 yet.     Queue=[2]

        Pop 2
            Neighbor 3: indegree 1→0, add to queue.  Queue=[3], visited={0,1,2,3}

        Pop 3
            No neighbors.                            Queue=[]

    STEP 4: visited.size()=4 == numCourses=4 → return true ✓

    Dry Run with a CYCLE (numCourses=2, prerequisites=[[1,0],[0,1]]):
    -----------------------------------------------------------------

    Graph:
        0 → {1}
        1 → {0}

    Indegree:
        0: 1    1: 1

    STEP 2: Queue = [], visited = {}  (no node has indegree 0)

    STEP 3: Nothing to process.

    STEP 4: visited.size()=0 != numCourses=2 → return false ✓

    Complexity Analysis:
    --------------------
    Time  : O(V + E) — V = numCourses, E = number of prerequisites.
                        We visit each node once and each edge once.
    Space : O(V + E) — adjacency list (graph) + indegree array + queue
                        + visited set.

*/

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {

        // STEP 1: Build the adjacency list and compute indegrees.
        // graph[u] = set of courses that depend on u (u must come before them)
        unordered_map<int, unordered_set<int>> graph;

        // indegree[v] = how many prerequisites course v still has
        vector<int> indegree(numCourses, 0);

        for(auto edge: prerequisites){
            int u = edge[1]; // prerequisite course (must be taken first)
            int v = edge[0]; // dependent course (needs u before it)
            graph[u].insert(v); // edge: u → v
            indegree[v]++;      // v has one more prerequisite
        }

        // STEP 2: Add all courses with indegree 0 to the queue.
        // These courses have no prerequisites — safe to take immediately.
        queue<int> Q;
        unordered_set<int> visited;

        for(int i=0; i<numCourses; i++){
            if(indegree[i] == 0) {
                Q.push(i);
                visited.insert(i);
            }
        }

        // STEP 3: BFS — process courses level by level.
        while(!Q.empty()){
            int u = Q.front(); // take this course
            Q.pop();
            
            // For every course v that depends on u:
            for(auto v: graph[u]){
                indegree[v]--; // u is done, so v has one less prerequisite

                // If v has no more prerequisites and hasn't been visited,
                // it's now ready to take — add it to the queue.
                if(indegree[v] == 0 && visited.find(v) == visited.end()){
                    visited.insert(v);
                    Q.push(v);
                }
            }
        }

        // STEP 4: If we visited all courses, no cycle exists.
        // If some courses were never visited, they're stuck in a cycle.
        cout<<"Visit" << visited.size()<<endl;
        return visited.size() == numCourses;
    }
};

int main(){
    Solution obj;
}