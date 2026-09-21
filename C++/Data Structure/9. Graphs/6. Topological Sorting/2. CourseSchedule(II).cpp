#include <iostream> 
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 210 - Course Schedule II

    There are a total of `numCourses` courses you have to take, labeled
    from 0 to numCourses - 1. You are given an array `prerequisites`
    where prerequisites[i] = [a, b] means you must take course b BEFORE
    you can take course a.

    Return the ordering of courses you should take to finish all courses.
    If there are multiple valid answers, return any of them.
    If it is impossible to finish all courses, return an empty array.

    How is this different from Course Schedule I (LC 207)?
    ------------------------------------------------------
    Course Schedule I  → just returns true/false (can you finish?).
    Course Schedule II → returns the actual ORDER in which to take them.

    The algorithm is the same (Kahn's BFS). The only difference is:
    we record the order in which we pop courses from the queue.

    Examples:
    ---------

    Example 1:
        Input:  numCourses = 2, prerequisites = [[1, 0]]
        Output: [0, 1]
        Explanation:
            Take course 0 first, then course 1.

    Example 2:
        Input:  numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
        Output: [0, 1, 2, 3]  (or [0, 2, 1, 3] — both valid)
        Explanation:
            0 has no prerequisites → take it first.
            Then 1 and 2 are unlocked (either order).
            Then 3 is unlocked.

    Example 3:
        Input:  numCourses = 2, prerequisites = [[1, 0], [0, 1]]
        Output: []
        Explanation:
            Cycle exists → impossible → return empty array.

    Example 4:
        Input:  numCourses = 1, prerequisites = []
        Output: [0]
        Explanation:
            Only one course, no prerequisites. Just take it.

    Constraints:
    ------------
    - 1 <= numCourses <= 2000
    - 0 <= prerequisites.length <= numCourses * (numCourses - 1)
    - prerequisites[i].length == 2
    - 0 <= a, b < numCourses
    - a != b
    - All prerequisite pairs are unique.

    Approach: Topological Sort using BFS (Kahn's Algorithm)
    -------------------------------------------------------

    Intuition:
    ----------
    Identical to Course Schedule I. We build a directed graph, compute
    indegrees, and BFS from indegree-0 nodes.

    The ONE addition: each time we pop a course from the queue, we
    append it to a `schedule` list. This records the topological order.

    At the end:
        - If schedule.size() == numCourses → return schedule.
        - Otherwise → cycle exists → return empty array.

    Why does the pop order give a valid schedule?
    -----------------------------------------------
    A course is only popped when its indegree reaches 0, meaning ALL
    its prerequisites have already been popped (and thus appear earlier
    in the schedule). So the schedule respects every prerequisite edge.

    Dry Run (numCourses=4, prerequisites=[[1,0],[2,0],[3,1],[3,2]]):
    ----------------------------------------------------------------

    Graph:
        0 → {1, 2}
        1 → {3}
        2 → {3}

    Indegree:  0:0  1:1  2:1  3:2

    Queue = [0], schedule = []

        Pop 0 → schedule = [0]
            Neighbor 1: indegree 1→0, enqueue.  Queue=[1]
            Neighbor 2: indegree 1→0, enqueue.  Queue=[1,2]

        Pop 1 → schedule = [0, 1]
            Neighbor 3: indegree 2→1.           Queue=[2]

        Pop 2 → schedule = [0, 1, 2]
            Neighbor 3: indegree 1→0, enqueue.  Queue=[3]

        Pop 3 → schedule = [0, 1, 2, 3]
            No neighbors.                       Queue=[]

    schedule.size()=4 == numCourses=4 → return [0, 1, 2, 3] ✓

    Complexity Analysis:
    --------------------
    Time  : O(V + E) — same as Course Schedule I.
    Space : O(V + E) — graph + indegree + queue + schedule.

*/

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {

        // STEP 1: Build the adjacency list and compute indegrees.
        // graph[u] = set of courses that depend on u
        unordered_map<int, unordered_set<int>> graph;

        // indegree[v] = number of prerequisites course v still needs
        vector<int> indegree(numCourses, 0);

        for(auto edge: prerequisites){
            int u = edge[1]; // prerequisite (must come first)
            int v = edge[0]; // dependent (needs u before it)
            graph[u].insert(v); // edge: u → v
            indegree[v]++;      // v gained one more prerequisite
        }

        queue<int> Q;
        unordered_set<int> visited;

        // This is the key difference from Course Schedule I:
        // we record the order in which courses are completed.
        vector<int> schedule;

        // STEP 2: Enqueue all courses with no prerequisites (indegree 0).
        for(int i=0; i<numCourses; i++){
            if(indegree[i] == 0) {
                Q.push(i);
                visited.insert(i);
            }
        }
        
        // STEP 3: BFS — process courses in topological order.
        while(!Q.empty()){
            int u = Q.front();
            Q.pop();

            // "Take" this course — append it to the schedule.
            schedule.push_back(u);
            
            // For every course v that depends on u:
            for(auto v: graph[u]){
                indegree[v]--; // u is done, v needs one less prerequisite

                // If all of v's prerequisites are done, it's ready.
                if(indegree[v] == 0 && visited.find(v) == visited.end()){
                    visited.insert(v);
                    Q.push(v);
                }
            }
        }

        // STEP 4: If we couldn't schedule all courses, a cycle exists.
        // Return empty array to signal "impossible".
        if(visited.size() != numCourses)
            return vector<int>();

        // Otherwise, return the valid topological order.
        return schedule;
    }
};

int main(){
    Solution obj;
}