#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

/*
	Reference: https://www.youtube.com/watch?v=iTBaI90lpDQ
			   https://www.geeksforgeeks.org/dsa/detect-cycle-in-a-graph/
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

public:
	bool cycleExists(Graph& g) {
		vector<int> indegree(g.V, 0);
		queue<int> Q;
		int visited = 0;

		for (int u = 0; u < g.V; u++) {
			for (int v : g.adj[u]) {
				indegree[v]++;
			}
		}

		for (int u = 0; u < g.V; u++) {
			if (indegree[u] == 0)
				Q.push(u);
		}

		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			visited++;

			for (int v : g.adj[u]) {
				indegree[v]--;
				if (indegree[v] == 0)
					Q.push(v);
			}
		}

		/*either this*/
		for (int u = 0; u < g.V; u++) {
			if (indegree[u] != 0)
				return true;
		}

		/*or this*/
		//  If visited nodes != total nodes, a cycle exists
		//  if (visited != g.V) return true;
		
		return false;
	}
};

int main() {
	Graph g1(4); // A=0, B=1, C=2, D=3

	g1.addEdge(0, 1); // A-B
	g1.addEdge(0, 2); // A-C
	g1.addEdge(1, 3); // B-D
	g1.addEdge(2, 3); // C-D
	
	Solution obj;
	obj.cycleExists(g1) == true ? cout << "Cycle Exists" << endl : cout << "Cycle does not exist" << endl;

	Graph g2(4); // A=0, B=1, C=2, D=3, E=4, F=5, G=6

	g2.addEdge(0, 1); // A-B
	g2.addEdge(1, 2); // B-C
	g2.addEdge(2, 3); // C-D
	g2.addEdge(3, 1); // D-A

	obj.cycleExists(g2) == true ? cout << "Cycle Exists" << endl : cout << "Cycle does not exist" << endl;

	return 0;
}