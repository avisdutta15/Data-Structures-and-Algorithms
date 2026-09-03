#include <vector>
#include <deque>
#include <climits>

using namespace std;

// Assuming graph is represented as adjacency list of {neighbor, weight}
void zeroOneBFS(int start, int n, vector<vector<pair<int, int>>>& adj) {
    vector<int> dist(n, INT_MAX);
    deque<int> dq;

    dist[start] = 0;
    dq.push_back(start);

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            // Relaxation step
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                
                // The 0-1 Routing Logic
                if (weight == 0) {
                    dq.push_front(v);
                } else {
                    dq.push_back(v);
                }
            }
        }
    }
}