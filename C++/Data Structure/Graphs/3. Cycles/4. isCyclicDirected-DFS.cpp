#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

/*
	Reference: https://www.youtube.com/watch?v=M8H4F3fw2WE
			   https://www.geeksforgeeks.org/dsa/detect-cycle-in-a-graph/
			   https://www.geeksforgeeks.org/dsa/detect-cycle-direct-graph-using-colors/
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
	enum COLOUR {white, grey, black};

	bool DFS(Graph& g, int u, vector<COLOUR>& visited) {
		visited[u] = COLOUR::grey;
		for (int v : g.adj[u]) {
			if (visited[v] == COLOUR::white) {
				if (DFS(g, v, visited) == true)
					return true;
			}
			if (visited[v] == COLOUR::grey)
				return true;				
		}
		visited[u] = COLOUR::black;
		return false;
	}
public:
	bool cycleExists(Graph& g) {
		vector<COLOUR> visited(g.V, COLOUR::white);
		return DFS(g, 0, visited);
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