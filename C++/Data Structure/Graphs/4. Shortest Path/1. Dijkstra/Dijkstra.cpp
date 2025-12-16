#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <set>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int vertices) : V(vertices), adj(vertices) {}

    void addEdge(int u, int v, int weight) {
        adj[u].push_back({ v, weight });
        adj[v].push_back({ u, weight });
    }

    // Queue WITHOUT visited[] - PROBLEMATIC!
    vector<int> dijkstraQueueNoVisited(int src) {
        vector<int> dist(V, INT_MAX);
        queue<int> q;

        dist[src] = 0;
        q.push(src);

        cout << "Queue without visited[] - Processing order:" << endl;
        int step = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            cout << "Step " << ++step << ": Processing vertex " << u
                << " with distance " << dist[u] << endl;

            // Process all neighbors
            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    q.push(v);
                    cout << "  Updated vertex " << v << " to distance " << dist[v] << endl;
                }
            }
        }

        return dist;
    }

    // Queue WITH visited[] - CORRECT!
    vector<int> dijkstraQueueWithVisited(int src) {
        vector<int> dist(V, INT_MAX);
        vector<bool> visited(V, false);
        queue<int> q;

        dist[src] = 0;
        q.push(src);

        cout << "\nQueue with visited[] - Processing order:" << endl;
        int step = 0;

        while (!q.empty()) {
            // Find min in queue (inefficient but necessary)
            int u = -1;
            int min_dist = INT_MAX;

            queue<int> temp = q;
            while (!temp.empty()) {
                int v = temp.front();
                temp.pop();
                if (!visited[v] && dist[v] < min_dist) {
                    min_dist = dist[v];
                    u = v;
                }
            }

            if (u == -1) break;

            visited[u] = true;
            cout << "Step " << ++step << ": Processing vertex " << u
                << " with distance " << dist[u] << " (MARKED VISITED)" << endl;

            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (!visited[v] && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    q.push(v);
                    cout << "  Updated vertex " << v << " to distance " << dist[v] << endl;
                }
            }
        }

        return dist;
    }

    // PriorityQueue WITHOUT visited[] - CORRECT!
    vector<int> dijkstraPriorityQueue(int src) {
        vector<int> dist(V, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[src] = 0;
        pq.push({ 0, src });

        cout << "\nPriorityQueue without visited[] - Processing order:" << endl;
        int step = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            int current_dist = pq.top().first;
            pq.pop();

            // Skip outdated entries
            if (current_dist > dist[u]) {
                cout << "Step " << ++step << ": Skipping vertex " << u
                    << " (outdated distance: " << current_dist
                    << ", current: " << dist[u] << ")" << endl;
                continue;
            }

            cout << "Step " << ++step << ": Processing vertex " << u
                << " with distance " << dist[u] << endl;

            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({ dist[v], v });
                    cout << "  Updated vertex " << v << " to distance " << dist[v] << endl;
                }
            }
        }

        return dist;
    }
};

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

        cout << "\nPriorityQueue without visited[] - Processing order:" << endl;
        int step = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            int current_dist = pq.top().first;
            pq.pop();

            // Skip outdated entries
            if (current_dist > dist[u]) {
                cout << "Step " << ++step << ": Skipping vertex " << u
                    << " (outdated distance: " << current_dist
                    << ", current: " << dist[u] << ")" << endl;
                continue;
            }

            cout << "Step " << ++step << ": Processing vertex " << u
                << " with distance " << dist[u] << endl;

            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({ dist[v], v });
                    cout << "  Updated vertex " << v << " to distance " << dist[v] << endl;
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
    Graph g(4); // A=0, B=1, C=2, D=3

    g.addEdge(0, 1, 1); // A-B:1
    g.addEdge(0, 2, 5); // A-C:5
    g.addEdge(1, 2, 1); // B-C:1  
    g.addEdge(1, 3, 3); // B-D:3
    g.addEdge(2, 3, 2); // C-D:2

    cout << "=== Queue WITHOUT visited[] ===" << endl;
    vector<int> dist1 = g.dijkstraQueueNoVisited(0);

    cout << "\n=== Queue WITH visited[] ===" << endl;
    vector<int> dist2 = g.dijkstraQueueWithVisited(0);

    cout << "\n=== PriorityQueue WITHOUT visited[] ===" << endl;
    vector<int> dist3 = g.dijkstraPriorityQueue(0);

    cout << "\n=== Final Results ===" << endl;
    cout << "Distances from vertex 0:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "Vertex " << i << ": " << dist1[i] << " (no visited) | "
            << dist2[i] << " (with visited) | " << dist3[i] << " (priority queue)" << endl;
    }

    return 0;
}