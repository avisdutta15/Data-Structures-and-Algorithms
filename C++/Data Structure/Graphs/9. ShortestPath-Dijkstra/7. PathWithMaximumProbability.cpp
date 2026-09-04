#include <iostream>
#include <queue>
#include <deque>
#include <vector>
#include <climits>

using namespace std;

/*
    https://www.youtube.com/watch?v=zTM9k6jqpXI
    Problem Statement:
    ------------------
    LeetCode 1514 - Path with Maximum Probability

    You are given an undirected weighted graph of n nodes (0 to n-1)
    with edges and their success probabilities. Given two nodes
    start and end, find the path with the maximum probability of
    success. If there is no path, return 0.

    Examples:
    ---------

    Example 1:
        Input:  n = 3, edges = [[0,1],[1,2],[0,2]]
                succProb = [0.5, 0.5, 0.2]
                start = 0, end = 2
        Output: 0.25
        Explanation:
            Path 0→1→2: 0.5 × 0.5 = 0.25
            Path 0→2:   0.2
            Best = 0.25

    Example 2:
        Input:  n = 3, edges = [[0,1],[1,2],[0,2]]
                succProb = [0.5, 0.5, 0.3]
                start = 0, end = 2
        Output: 0.30

    Example 3:
        Input:  n = 3, edges = [[0,1]]
                succProb = [0.5]
                start = 0, end = 2
        Output: 0.0  (no path exists)

    Constraints:
    ------------
    - 2 <= n <= 10^4
    - 0 <= edges.length <= 2 * 10^4
    - 0 <= succProb[i] <= 1
    - 0 <= start, end < n

    How is this Dijkstra?
    ----------------------
    Side-by-side comparison:

        Normal Dijkstra               This Problem
        ────────────────              ────────────
        Minimize distance             Maximize probability
        MinHeap                       MaxHeap
        dist[] initialized to INF     prob[] initialized to 0 (start = 1)
        dist[v] = dist[u] + w        prob[v] = prob[u] * w
        relax if newDist < dist[v]    relax if newProb > prob[v]
        combine via +                 combine via ×

    Why Dijkstra works here:
    -------------------------
    Probabilities are in [0, 1]. Multiplying by another value in [0, 1]
    can only keep the product the same or decrease it — never increase it.
    So extending a path never improves the probability, which gives us
    the same monotonicity guarantee as standard Dijkstra with positive
    weights. When we pop a node from the max-heap, its probability is
    finalized.

    Approach: Modified Dijkstra (max-heap)
    ----------------------------------------
    Time:  O(E log V) where V = n, E = edges.length
    Space: O(V + E)

    Dry Run (Example 1: n=3, edges=[[0,1],[1,2],[0,2]], prob=[0.5,0.5,0.2]):
    --------------------------------------------------------------------------

    Graph:  0 --0.5-- 1 --0.5-- 2
            |                    |
            +-------0.2---------+

    prob[] = [1.0, 0, 0],  MaxHeap: [(1.0, 0)]

    Pop (1.0, 0):
        → node 1: newProb = 1.0 × 0.5 = 0.5 > 0   → prob[1]=0.5, push (0.5, 1)
        → node 2: newProb = 1.0 × 0.2 = 0.2 > 0   → prob[2]=0.2, push (0.2, 2)

    Pop (0.5, 1):
        → node 0: newProb = 0.5 × 0.5 = 0.25 < 1.0 → skip
        → node 2: newProb = 0.5 × 0.5 = 0.25 > 0.2 → prob[2]=0.25, push (0.25, 2)

    Pop (0.25, 2):
        u == end_node → return 0.25 ✓
*/

/*
    Identification:
    0. Graph
    1. start -> end. finding path
    2. graph is undirected with weights (probability).
    3. path optimzation - maximum probability. here probabilities are * multiplied not + summed
    4. Dijkstra 

    Normal Dijkstra
    1. Shortest Path (Minimum)  -> MinHeap
    2. Metric : Path is computed using distance. So metric is distance[]
    3. How add a new node to the path?  add (+) edge weight as distance to the already computed distance[u]
    4. What is the optimization we want? minimum.
       newDistance = ____ (dist[u], weight(u,v))        ->   sum of weights in a path: add the weight +
       if newDistance is ____ than dist[v]              ->   along all paths need minimum: smaller than <

    This Problem
    1. Maximum Probability  -> MaxHeap
    2. Metric : Probability is used for computation. So metric is probability[]
    3. How add a new node to the path?  multiply (*) edge weight as probability to the already computed probability[u]
    newProbability = ____ (probability[u], weight(u,v))        ->   product of weights in a path: multiply the weight *
    if newProbability is ____ than probability[v]              ->   along all paths need maximum: greater than >
*/

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {

        vector<vector<pair<int, double>>> graph(n, vector<pair<int, double>>());
        for(int i=0; i<edges.size(); i++){
            auto edge = edges[i];
            int u = edge[0];
            int v = edge[1];
            double weight = succProb[i];
            graph[u].push_back({v, weight});
            graph[v].push_back({u, weight});
        }

        // INITIALIZE SINGLE SOURCE
        //PQ[probability, node]
        priority_queue<pair<double, int>> PQ;
        vector<double> probability(n, INT_MIN);

        PQ.push({1, start_node});       // probability to reach start node is always 100% i.e. 1
        probability[start_node] = 1;

        while(!PQ.empty()){
            auto [p, u] = PQ.top();
            PQ.pop();

            if(u == end_node) return p;
            if(p < probability[u]) continue;

            for(auto cell: graph[u]){
                int v = cell.first;
                double weight = cell.second;

                double newProbability = probability[u] * weight;
                if(newProbability > probability[v]){
                    probability[v] = newProbability;
                    PQ.push({probability[v], v});
                }
            }
        }

        return probability[end_node] == INT_MIN ? 0 : probability[end_node];
    }
};

int main() {
    return 0;
}
