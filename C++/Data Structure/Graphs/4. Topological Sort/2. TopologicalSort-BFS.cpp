#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
using namespace std;

/*
	Reference: 
*/

class Graph {
private:
public:
	int V;
	unordered_map<int, vector<int>> adj;
	Graph(int vertices) : V(vertices), adj(vertices) {}

	void addEdge(int u, int v) {
		adj[u].push_back({ v });
	}
};

class Solution {
private:
	
public:
	vector<int> topologicalSort(Graph& g) {
		queue<int> Q;
		vector<int> indegree(g.V, 0);
		vector<int> topoOrder;

		for (int u = 0; u < g.V; u++) {
			for (int v : g.adj[u]) {
				indegree[v]++;
			}
		}

		// Add all nodes with indegree 0 into the queue
		for (int u = 0; u < g.V; u++) {
			if (indegree[u] == 0)
				Q.push(u);
		}

		while (Q.empty() == false) {
			int u = Q.front();
			Q.pop();

			topoOrder.push_back(u);

			for (int v : g.adj[u]) {
				indegree[v]--;
				if (indegree[v] == 0)
					Q.push(v);
			}
		}

		//if the graph has a cycle then return an empty array
		if (topoOrder.size() != g.V)
			return vector<int>();

		return topoOrder;
	}

};

int main() {
	Graph g1(5); // A=0, B=1, C=2, D=3, E=4

	g1.addEdge(0, 1); // A-B
	g1.addEdge(0, 2); // A-C
	g1.addEdge(1, 3); // B-D
	g1.addEdge(2, 3); // C-D
	g1.addEdge(3, 4); // C-D

	Solution obj;
	auto topoOrder = obj.topologicalSort(g1);
	for (int i : topoOrder) {
		cout << i << " ";
	}
	cout << endl;

	return 0;
}