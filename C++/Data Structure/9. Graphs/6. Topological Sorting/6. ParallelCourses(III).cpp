#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

/*
    Problem Statement:
    ------------------
    LeetCode 2050 - Parallel Courses III

    You are given an integer `n` indicating n courses labeled 1 to n.
    You are given an array `relations` where relations[i] = [prev, next]
    means course `prev` must be completed before course `next`.
    You are also given an array `time` where time[i] is the number of
    months it takes to complete course (i+1).

    You can start multiple courses at the same time if their prerequisites
    are met. A course starts immediately when all prerequisites are done.

    Return the MINIMUM number of months needed to complete all courses.

    How is this different from Parallel Courses I?
    -----------------------------------------------
    Parallel Courses I  → every course takes 1 semester, answer = number
                           of BFS levels.
    Parallel Courses III → each course has its own duration. Answer =
                           longest path (by time) through the dependency
                           graph. This is the Critical Path.

    Examples:
    ---------

    Example 1:
        Input:  n = 3, relations = [[1,3],[2,3]], time = [3,2,5]
        Output: 8
        Explanation:
            Course 1 (3 months) and course 2 (2 months) start at month 0.
            Course 1 finishes at month 3, course 2 at month 2.
            Course 3 (5 months) needs both → starts at month 3 (waits
            for the slower prerequisite).
            Course 3 finishes at month 3 + 5 = 8.

            Timeline:
              Course 1: [0 ------- 3]
              Course 2: [0 ---- 2]
              Course 3:            [3 ------------ 8]

    Example 2:
        Input:  n = 5, relations = [[1,5],[2,5],[3,5],[3,4],[4,5]], time = [1,2,3,4,5]
        Output: 12
        Explanation:
            Course 3 (3 months): finishes at month 3.
            Course 4 (4 months, needs 3): starts at 3, finishes at 7.
            Course 5 (5 months, needs 1,2,3,4): starts at month 7
            (waits for course 4, the slowest prerequisite).
            Finishes at 7 + 5 = 12.

    Example 3:
        Input:  n = 2, relations = [], time = [3,5]
        Output: 5
        Explanation:
            No dependencies. Both start at month 0.
            Course 1 finishes at 3, course 2 at 5.
            Answer = max(3, 5) = 5.

    Constraints:
    ------------
    - 1 <= n <= 5 * 10^4
    - 0 <= relations.length <= min(n*(n-1)/2, 5*10^4)
    - relations[i].length == 2
    - 1 <= prev, next <= n
    - prev != next
    - All pairs are unique, no cycles (graph is a DAG).
    - time.length == n
    - 1 <= time[i] <= 10^4
    - NOTE: courses are 1-indexed, time[] is 0-indexed.

    Approach: Topological Sort + Critical Path (Kahn's BFS)
    -------------------------------------------------------

    Intuition:
    ----------
    In Parallel Courses I, every course took 1 unit of time, so
    counting BFS levels gave the answer. Now courses have different
    durations, so we need to track the actual finish time of each
    course.

    Key idea: for each course v, the earliest it can FINISH is:

        maxTime[v] = max(maxTime[u] + time[v])
                     for all prerequisites u of v

    Why max? Because v can't start until ALL prerequisites are done.
    The slowest prerequisite is the bottleneck. v starts when the
    slowest finishes, then takes time[v] more months.

    For courses with no prerequisites:
        maxTime[v] = time[v]  (starts immediately at month 0)

    The answer is max(maxTime[v]) across all courses — the last
    course to finish determines the total time.

    This is the "Critical Path Method" — the longest weighted path
    in a DAG determines the minimum project completion time.

    Why does topological order work here?
    --------------------------------------
    When we process course u in topological order, ALL of u's
    prerequisites have already been processed. So maxTime[u] is
    finalized. We can safely propagate maxTime[u] + time[v] to
    each dependent course v.

    By the time v reaches indegree 0 and enters the queue, it has
    received updates from ALL its prerequisites. So maxTime[v]
    holds the correct "earliest finish time" for v.

    Dry Run (n=3, relations=[[1,3],[2,3]], time=[3,2,5]):
    -----------------------------------------------------

    Graph:
        1 → {3}
        2 → {3}

    Indegree: 1:0  2:0  3:2

    Initialize:
        maxTime[1] = time[0] = 3
        maxTime[2] = time[1] = 2
        maxTime[3] = time[2] = 5
        Queue = [1, 2]

    Pop 1 (maxTime=3):
        Neighbor 3: maxTime[3] = max(5, 3+5) = 8
        indegree[3] = 2→1

    Pop 2 (maxTime=2):
        Neighbor 3: maxTime[3] = max(8, 2+5) = 8  (course 1 is bottleneck)
        indegree[3] = 1→0, push 3

    Pop 3 (maxTime=8):
        No neighbors.

    Answer: max(3, 2, 8) = 8 ✓

    Complexity Analysis:
    --------------------
    Time  : O(V + E) — each course processed once, each edge once.
    Space : O(V + E) — graph + indegree + maxTime arrays + queue.

*/

class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {

        // STEP 1: Build the directed graph and compute indegrees.
        // graph[u] = set of courses that depend on u
        unordered_map<int, unordered_set<int>> graph;
        // Courses are 1-indexed, so size n+1
        vector<int> indegree(n + 1, 0);

        for (auto& relation : relations) {
            int prevCourse = relation[0];  // must finish first
            int nextCourse = relation[1];  // depends on prevCourse
            graph[prevCourse].insert(nextCourse);
            indegree[nextCourse]++;
        }

        queue<int> Q;
        // maxTimeToFinishCourse[v] = earliest month course v can be completed
        vector<int> maxTimeToFinishCourse(n + 1, 0);

        // STEP 2: Initialize all courses with their own duration.
        // Courses with no prerequisites (indegree 0) go into the queue.
        for (int i = 1; i <= n; i++) {
            // Every course takes at least its own duration
            maxTimeToFinishCourse[i] = time[i - 1];  // time[] is 0-indexed

            if (indegree[i] == 0)
                Q.push(i);
        }

        // STEP 3: BFS in topological order.
        // When processing u, propagate u's finish time to all dependents.
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();

            for (int v : graph[u]) {
                // v can't finish before u finishes + v's own duration.
                // Take the max because v might have multiple prerequisites,
                // and it must wait for the SLOWEST one.
                maxTimeToFinishCourse[v] = max(
                    maxTimeToFinishCourse[v],
                    maxTimeToFinishCourse[u] + time[v - 1]
                );

                // Standard Kahn's: reduce indegree, enqueue when 0
                indegree[v]--;
                if (indegree[v] == 0)
                    Q.push(v);
            }
        }

        // STEP 4: The answer is the latest finish time across all courses.
        // The last course to complete determines the total project duration.
        return *max_element(maxTimeToFinishCourse.begin(), maxTimeToFinishCourse.end());
    }
};

int main() {
    Solution obj;
}
