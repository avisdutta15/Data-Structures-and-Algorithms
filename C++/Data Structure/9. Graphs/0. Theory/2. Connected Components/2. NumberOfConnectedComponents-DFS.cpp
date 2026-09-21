 #include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

class Graph {
private:
public:
	int V;
	unordered_map<int, vector<int>> adj;
	Graph(int vertices) : V(vertices), adj(vertices) {}

	void addEdge(int u, int v) {
		adj[u].push_back({ v });
		adj[v].push_back({ u });
	}
};

class Solution {
	void DFS(Graph& g, int u, vector<bool>& visited) {
		visited[u] = true;
		for (int v : g.adj[u]) {
			if (!visited[v])
				DFS(g, v, visited);
		}
	}
public:
	int numberOfConnectedComponents(Graph &g) {
		vector<bool> visited(g.V, false);

		int components = 0;
		for (int u = 0; u < g.V; u++) {
			if (visited[u] == false) {
				components++;
				DFS(g, u, visited);
			}
		}
		return components;
	}
};

int main() {
	Graph g(9); // A=0, B=1, C=2, D=3, E=4, F=5, G=6, H=7, I=8

	g.addEdge(0, 1); // A-B
	g.addEdge(0, 2); // A-C
	g.addEdge(1, 3); // B-D  
	g.addEdge(2, 3); // C-D
	g.addEdge(1, 4); // B-E
	g.addEdge(3, 4); // D-E
	g.addEdge(2, 5); // C-F
	g.addEdge(5, 6); // F-G
	g.addEdge(4, 6); // E-G
	g.addEdge(7, 8);

	Solution obj;
	cout << "Number Of Components : " << obj.numberOfConnectedComponents(g) << endl;

	return 0;
}