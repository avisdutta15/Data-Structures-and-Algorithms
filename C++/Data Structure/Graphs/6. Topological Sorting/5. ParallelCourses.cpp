#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 1136 - Parallel Courses

    You are given an integer `n` which indicates there are n courses
    labeled from 1 to n. You are also given an array `relations` where
    relations[i] = [prevCourse, nextCourse] means prevCourse must be
    taken before nextCourse (prerequisite).

    In one semester, you can take ANY number of courses as long as all
    their prerequisites have been completed in a previous semester.

    Return the MINIMUM number of semesters needed to take all courses.
    If it is impossible (cycle in prerequisites), return -1.

    How is this different from Course Schedule?
    --------------------------------------------
    Course Schedule   → "Can you finish?" (yes/no) or "In what order?"
    Parallel Courses  → "How many semesters (levels) to finish everything?"

    Both use topological sort. The difference: here we care about the
    NUMBER OF LEVELS in the BFS, because each level = one semester
    (courses in the same level can be taken in parallel).

    Examples:
    ---------

    Example 1:
        Input:  n = 3, relations = [[1,3],[2,3]]
        Output: 2
        Explanation:
            Semester 1: take courses 1 and 2 (no prerequisites)
            Semester 2: take course 3 (after 1 and 2 are done)

            Graph:  1 → 3
                    2 → 3

    Example 2:
        Input:  n = 3, relations = [[1,2],[2,3],[3,1]]
        Output: -1
        Explanation:
            1 → 2 → 3 → 1. Cycle exists. Impossible.

    Example 3:
        Input:  n = 4, relations = [[1,2],[1,3],[2,4],[3,4]]
        Output: 3
        Explanation:
            Semester 1: course 1
            Semester 2: courses 2, 3 (both depend only on 1)
            Semester 3: course 4 (depends on 2 and 3)

            Graph:  1 → 2 → 4
                    1 → 3 → 4

    Constraints:
    ------------
    - 1 <= n <= 5000
    - 1 <= relations.length <= 5000
    - relations[i].length == 2
    - 1 <= prevCourse, nextCourse <= n
    - prevCourse != nextCourse
    - All pairs [prevCourse, nextCourse] are unique.
    - NOTE: courses are labeled 1 to n (1-indexed, not 0-indexed).

    Approach: BFS Topological Sort (Level by Level / Kahn's Algorithm)
    -------------------------------------------------------------------

    Intuition:
    ----------
    Think of it as a dependency chain. Courses with no prerequisites
    can be taken first (semester 1). After completing them, courses
    whose prerequisites are all in semester 1 become available
    (semester 2). And so on.

    This is exactly level-order BFS on the dependency graph:
        - Each BFS level = one semester
        - Courses at the same level are independent of each other
          (can be taken in parallel)
        - The total number of levels = minimum semesters

    Why does the number of BFS levels give the answer?
    ---------------------------------------------------
    BFS processes all nodes at distance d before any node at distance
    d+1. In this context, "distance" = how many prerequisite chains
    deep a course is. A course at depth d cannot be taken until
    semester d+1 (after all d prerequisite layers are done). So the
    number of levels = length of the longest prerequisite chain =
    minimum semesters.

    Cycle detection:
    ----------------
    If a cycle exists, some courses never reach indegree 0 (they're
    stuck waiting for each other). We count how many courses we
    actually process. If coursesTaken < n, there's a cycle → return -1.

    Dry Run (n=4, relations=[[1,2],[1,3],[2,4],[3,4]]):
    ----------------------------------------------------

    Graph:
        1 → {2, 3}
        2 → {4}
        3 → {4}

    Indegree: 1:0  2:1  3:1  4:2

    Queue = [1]  (only course with indegree 0)

    Semester 1: pop 1, coursesTaken=1
        1→2: indegree[2] = 1→0, push 2
        1→3: indegree[3] = 1→0, push 3
        Queue = [2, 3]
    numberOfSemesters = 1

    Semester 2: pop 2, coursesTaken=2
        2→4: indegree[4] = 2→1
               pop 3, coursesTaken=3
        3→4: indegree[4] = 1→0, push 4
        Queue = [4]
    numberOfSemesters = 2

    Semester 3: pop 4, coursesTaken=4
        No neighbors.
        Queue = []
    numberOfSemesters = 3

    coursesTaken (4) == n (4) → return 3 ✓

    Dry Run with CYCLE (n=3, relations=[[1,2],[2,3],[3,1]]):
    ---------------------------------------------------------

    Graph:  1→{2}, 2→{3}, 3→{1}

    Indegree: 1:1  2:1  3:1

    Queue = []  (no course has indegree 0)

    Loop never executes. coursesTaken = 0, numberOfSemesters = 0.

    coursesTaken (0) != n (3) → return -1 ✓

    Complexity Analysis:
    --------------------
    Time  : O(V + E) — V = n courses, E = number of relations.
                        Each course processed once, each edge once.
    Space : O(V + E) — adjacency list + indegree array + queue.

*/

class Solution {
public:
    int minimumSemesters(int n, vector<vector<int>>& relations) {

        // STEP 1: Build the directed graph and compute indegrees.
        // graph[u] = set of courses that depend on u
        unordered_map<int, unordered_set<int>> graph;
        // indegree[v] = number of prerequisites course v still needs
        // Size n+1 because courses are labeled 1 to n (1-indexed)
        vector<int> indegree(n + 1, 0);

        for (auto& relation : relations) {
            int prevCourse = relation[0];  // must be taken first
            int nextCourse = relation[1];  // depends on prevCourse
            graph[prevCourse].insert(nextCourse);  // edge: prev → next
            indegree[nextCourse]++;                // next has one more prerequisite
        }

        // STEP 2: Enqueue all courses with no prerequisites (indegree 0).
        // These can be taken in the first semester.
        queue<int> Q;
        for (int i = 1; i <= n; i++) {  // 1-indexed!
            if (indegree[i] == 0)
                Q.push(i);
        }

        int numberOfSemesters = 0;
        int coursesTaken = 0;

        // STEP 3: BFS level by level. Each level = one semester.
        while (!Q.empty()) {
            // Process all courses available this semester
            int levelSize = Q.size();
            while (levelSize--) {
                int course = Q.front();
                Q.pop();
                coursesTaken++;  // this course is now completed

                // Unlock dependent courses: reduce their prerequisites
                for (auto dependentCourse : graph[course]) {
                    indegree[dependentCourse]--;

                    // All prerequisites met → available next semester
                    if (indegree[dependentCourse] == 0)
                        Q.push(dependentCourse);
                }
            }
            // One semester completed
            numberOfSemesters++;
        }

        // STEP 4: If not all courses were taken, a cycle exists.
        // Some courses are stuck waiting for each other forever.
        return coursesTaken == n ? numberOfSemesters : -1;
    }
};

int main() {
    Solution obj;
}
